//
// Created by dingjing on 23-5-10.
//

#include "server.h"

#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/un.h>             /* struct sockaddr_un */
#include <gio/gio.h>
#include <arpa/inet.h>
#include <netinet/in.h>         /* struct sockaddr_in */
#include <netinet/tcp.h>

#include "event.h"
#include "io/io.h"
#include "global.h"
#include "core-log.h"
#include "conn-context.h"
#include "decode/decode.h"


static GSocket*             gXScopeServer = NULL;
static GSocketListener*     gXServer = NULL;


static void set_socket (int fd);
static GSocket* get_x_server_socket ();
static void scope_x_proto (gpointer data, gpointer udata);
//static gsize read_all_data (GSocket* fr, char** out/*out*/);
static gboolean xclient_read(GIOChannel* src, GIOCondition cond, gpointer data);
static gboolean xserver_read(GIOChannel* src, GIOCondition cond, gpointer data);
static inline struct sockaddr_in get_scope_server_addr (const char* host, guint32 port);
static gboolean new_client_connect (GSocketService* ls, GSocketConnection* conn, GObject* srcObj, gpointer uData);


bool server_init(const char *xServerHost, guint32 xServerPort)
{
    g_autoptr(GError) error = NULL;

    gXDefaultPort = DEFAULT_PORT + gXServerPort + gXServerDisplay;
    gXScopeDefaultPort = DEFAULT_PORT + gXScopeServerPort + gXScopeServerDisplay;

    struct sockaddr_in addrT = get_scope_server_addr (xServerHost, xServerPort);

    g_autoptr (GSocketAddress) addr = g_socket_address_new_from_native(&addrT, sizeof (addrT));

    gXScopeServer = g_socket_new (G_SOCKET_FAMILY_IPV4, G_SOCKET_TYPE_STREAM, G_SOCKET_PROTOCOL_DEFAULT, &error);
    if (error) {
        panic("New socket error: %s\n", error->message);
    }
    g_socket_set_blocking (gXScopeServer, false);

    struct linger linger = {.l_linger = 0, .l_onoff = 0};
    setsockopt (g_socket_get_fd (gXScopeServer), SOL_SOCKET, SO_LINGER, &linger, sizeof(linger));

    if (!g_socket_bind (G_SOCKET(gXScopeServer), addr, true, &error)) {
        panic("socket bind error: '%s'\n", error->message);
    }

    if (!g_socket_listen (gXScopeServer, &error)) {
        panic("listen error: '%s'\n", error->message);
    }

    gXServer = g_socket_service_new();
    g_socket_listener_add_socket (gXServer, gXScopeServer, NULL, &error);
    if (error) {
        panic("socket listener error: '%s'\n", error->message);
    }

    GThreadPool* thread = g_thread_pool_new (scope_x_proto, NULL, 100, true, &error);

    g_signal_connect (G_SOCKET_LISTENER(gXServer), "incoming", (GCallback) new_client_connect, thread);

    return 0;
}

static inline struct sockaddr_in get_scope_server_addr (const char* host, guint32 port)
{
    (void) host;
    (void) port;

    char buf[256] = {0};
    struct sockaddr_in addr;
    g_autofree char* hostIp = NULL;
    g_autofree char* hostName = NULL;
    gXScopeDefaultPort = DEFAULT_PORT + gXScopeServerPort + gXScopeServerDisplay;

    if (gXScopeServerPort == gXServerPort) {
        panic("Try to change others port for xscope!\n");
    }

    memset (&addr, 0, sizeof (addr));

    (void) gethostname (buf, sizeof (buf) - 1);
    if (strlen (buf) <= 0) {
        panic ("Cannot get host name.\n");
    }
    hostName = g_strdup(buf);

    struct hostent* hp = gethostbyname (buf);
    if (NULL == hp) {
        panic ("Cannot get ip.");
    }
    (void) inet_ntop (hp->h_addrtype, hp->h_addr, buf, sizeof (buf) - 1);
    hostIp = g_strdup (buf);

    g_info("xscope host name: '%s' ip: '%s' port: '%d'\n", hostName, hostIp, gXScopeDefaultPort);

    {
        addr.sin_family = AF_INET;
        addr.sin_port = g_htons (gXScopeDefaultPort);
        addr.sin_addr.s_addr = INADDR_ANY;
    }

    return addr;
}

static void scope_x_proto (gpointer data, gpointer udata)
{
    GSocketConnection* conn = (GSocketConnection*) data;
    GSocket* socket = g_socket_connection_get_socket (conn);
    g_autoptr(GSocket) xServerSocket = get_x_server_socket();

    set_socket (g_socket_get_fd (socket));
    set_socket (g_socket_get_fd (xServerSocket));

    ConnContext* cc = conn_context_new();

//    g_autoptr(GMainContext) ctx = g_main_context_new ();
//    g_autoptr(GMainLoop) main = g_main_loop_new (ctx, false);

    // free
//    IOContext* ioContext = g_malloc0 (sizeof (IOContext));

//    EventData event = {
//        .mainLoop = main,
//        .xServer = xServerSocket,
//        .xClient = socket,
//        .ioContext = ioContext
//    };
//    g_mutex_init (&(event.lock));

    g_autoptr(GIOChannel) clientIO = g_io_channel_unix_new (g_socket_get_fd(socket));
    g_autoptr(GIOChannel) serverIO = g_io_channel_unix_new (g_socket_get_fd(xServerSocket));

    g_autoptr(GSource) clientSource = g_io_create_watch (clientIO, G_IO_IN | G_IO_ERR);
    g_source_set_callback (clientSource, G_SOURCE_FUNC(xclient_read), cc, NULL);

    g_autoptr(GSource) serverSource = g_io_create_watch (serverIO, G_IO_IN | G_IO_ERR);
    g_source_set_callback (serverSource, G_SOURCE_FUNC(xserver_read), cc, NULL);

    conn_context_add_gsource (cc, clientSource);
    conn_context_add_gsource (cc, serverSource);


    IOContext* ic = (IOContext*) g_malloc0 (sizeof (IOContext));
    ic->xClient.xIO = socket;
    ic->xServer.xIO = xServerSocket;
    conn_context_set_data (cc, ic);

    conn_context_run(cc);

    // free
    conn_context_free (&cc);
}

static GSocket* get_x_server_socket ()
{
    struct sockaddr *saddr;
    struct sockaddr_un saun;
    g_autoptr(GError) error = NULL;

    saun.sun_family = AF_UNIX;
    g_snprintf (saun.sun_path, sizeof(saun.sun_path) - 1, "/tmp/.X11-unix/X%d", gXDefaultPort - DEFAULT_PORT);
    unsigned long salen = sizeof (saun.sun_family) + strlen (saun.sun_path) + 1;
    saddr = (struct sockaddr*) &saun;

    int serverFd = socket(saddr->sa_family, SOCK_STREAM, 0);
    if (serverFd < 0) {
        g_error("socket() to Server failed");
        panic("Can't open connection to Server\n");
    }
    (void) setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR, (char *) NULL, 0);

    int tmp = 1;
    (void) setsockopt(serverFd, IPPROTO_TCP, TCP_NODELAY, (char *) &tmp, sizeof(int));

    struct linger linger = {.l_onoff = 0, linger.l_linger = 0};
    (void) setsockopt(serverFd, SOL_SOCKET, SO_LINGER, (char *) &linger, sizeof linger);

    g_autoptr(GSocket) serverSocket = g_socket_new_from_fd (serverFd, &error);
    if (error) {
        g_warning("Create x server fd failed! error: '%s'", error->message);
        return NULL;
    }

    errno = 0;
    if (connect (serverFd, saddr, salen) < 0) {
        g_warning("Connect X server error: '%s'", g_strerror (errno));
        if (0 != errno) {
            switch (errno) {
                case ECONNREFUSED: {
                    (void) close (serverFd);
                    panic("No Server\n");
                }
                default: {
                    (void) close (serverFd);
                    panic("Can't open connection to Server\n");
                }
            }
        }
    }

    g_socket_set_blocking (serverSocket, true);

    return g_object_ref(serverSocket);
}

gboolean new_client_connect (GSocketService* ls, GSocketConnection* conn, GObject* srcObj, gpointer uData)
{
    g_info("new connect");

    g_autoptr (GError) error = NULL;

    GThreadPool* thread = (GThreadPool*) uData;

    g_object_ref(conn);

    g_thread_pool_push (thread, conn, &error);
    if (error) {
        g_warning("error: %s", error->message);
        g_object_unref (conn);
        return false;
    }

    (void) ls;
    (void) srcObj;

    return true;
}


static void set_socket (int fd)
{
    int tmp = 1;
    (void) setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (char *) &tmp, sizeof(int));

    struct linger linger = {.l_onoff = 0, linger.l_linger = 0};
    (void) setsockopt(fd, SOL_SOCKET, SO_LINGER, (char *) &linger, sizeof linger);

    (void) fcntl(fd, F_SETFL, O_NONBLOCK);
    (void) fcntl(fd, F_SETFD, FD_CLOEXEC);
}

static gboolean xclient_read(GIOChannel* src, GIOCondition cond, gpointer data)
{
    (void) src;

    ConnContext* connCtx = (ConnContext*) (data);
    IOContext* ioCtx = conn_context_peek_data (connCtx);

    switch (cond) {
        case G_IO_IN: {
            g_autoptr(GError) error = NULL;

            const IOCache* client = &ioCtx->xClient;

            io_cache_read_from_xclient (ioCtx, &error);
            if (error) {
                g_warning("XClient To XServer[ERR]: '%s'", error->message);
                conn_context_quit(connCtx);
                return false;
            }

            if (!io_cache_is_valid (ioCtx) || !decode_x_client (ioCtx)) {
                g_info("XClient Closed!");
                return false;
            }
            g_info("XClient To XServer[%-ld %s]:\n%s\n", client->xReadCacheLen, (client->xReadCacheLen > 1 ? "bytes" : "byte"), client->xParsedReadStr);
            io_cache_write_to_xserver (ioCtx, &error);
            if (error) {
                g_warning("XClient To XServer[ERR]: '%s'", error->message);
                conn_context_quit(connCtx);
                return false;
            }
            break;
        }
        case G_IO_PRI:
        case G_IO_OUT:
        case G_IO_ERR:
        case G_IO_HUP:
        case G_IO_NVAL:
        default: {
            break;
        }
    }

    if (!io_cache_is_valid (ioCtx)) {
        g_info("XClient Closed!");
        conn_context_quit(connCtx);
        return false;
    }

    return true;
}

static gboolean xserver_read(GIOChannel* src, GIOCondition cond, gpointer data)
{
    (void) src;

    ConnContext* connCtx = (ConnContext*) (data);
    IOContext* ioCtx = conn_context_peek_data (connCtx);

    switch (cond) {
        case G_IO_IN: {
            g_autoptr(GError) error = NULL;

            const IOCache* server = &ioCtx->xServer;

            io_cache_read_from_xserver(ioCtx, &error);
            if (error) {
                g_warning("XServer To XClient[ERR]: '%s'", error->message);
                conn_context_quit(connCtx);
                return false;
            }

            if (server->xReadCacheLen <= 0) {
                g_warning("XServer read null");
                conn_context_quit(connCtx);
                return false;
            }

            if (!io_cache_is_valid (ioCtx) || !decode_x_server (ioCtx)) {
                g_info("XServer Closed!");
                return false;
            }
            g_info("XServer To XClient[%-ld %s]:\n%s\n", server->xReadCacheLen, (server->xReadCacheLen > 1 ? "bytes" : "byte"), server->xParsedReadStr);
            io_cache_write_to_xclient(ioCtx, &error);
            if (error) {
                g_warning("XServer To XClient[ERR]: '%s'", error->message);
                conn_context_quit(connCtx);
                return false;
            }

            break;
        }
        case G_IO_PRI:
        case G_IO_OUT:
        case G_IO_ERR:
        case G_IO_HUP:
        case G_IO_NVAL:
        default: {
            break;
        }
    }

    if (!io_cache_is_valid (ioCtx)) {
        g_info("XServer Closed!");
        conn_context_quit(connCtx);
        return false;
    }

    return true;
}