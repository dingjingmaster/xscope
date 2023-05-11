//
// Created by dingjing on 23-5-10.
//

#include "server.h"

#include <netdb.h>
#include <unistd.h>
#include <sys/un.h>             /* struct sockaddr_un */
#include <gio/gio.h>
#include <arpa/inet.h>
#include <netinet/in.h>         /* struct sockaddr_in */

#include "event.h"
#include "global.h"
#include "core-log.h"


static GSocket*             gXScopeServer = NULL;
static GSocketListener*     gXServer = NULL;


static GSocket* get_x_server_socket ();
static void set_client_socket (int fd);
static void scope_x_proto (gpointer data, gpointer udata);
static gsize read_all_data (GSocket* fr, char** out/*out*/);
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
    gsize strLen = 0;
    g_autoptr(GError) error = NULL;
    g_autofree char* binStr = NULL;
    GSocketConnection* conn = (GSocketConnection*) data;
    GSocket* socket = g_socket_connection_get_socket (conn);
    g_autoptr(GSocket) xServerSocket = get_x_server_socket();

    set_client_socket (g_socket_get_fd (socket));

    g_socket_set_blocking (socket, false);
    g_socket_set_blocking (xServerSocket, false);

    g_socket_set_keepalive (socket, true);
    g_socket_set_keepalive (xServerSocket, true);

#if 1
    g_autoptr(GMainLoop) main = NULL;
    g_autoptr(GMainContext) ctx = NULL;
    g_autoptr(GSource) xClientSource = NULL;
    g_autoptr(GSource) xServerSource = NULL;

    EventSource* clientEV = event_source_create (NULL, socket);
    if (NULL == clientEV) {
        g_warning("create client event error!");
        goto out;
    }

    EventSource* serverEV = event_source_create (NULL, socket);
    if (NULL == serverEV) {
        g_warning("create server event error!");
        goto out;
    }

    ctx = g_main_context_new ();
    main = g_main_loop_new (ctx, false);
    xClientSource = g_source_new (clientEV, sizeof (GSource));
    xServerSource = g_source_new (serverEV, sizeof (GSource));

    g_source_attach (xClientSource, ctx);
    g_source_attach (xServerSource, ctx);

    g_main_loop_run (main);

out:
    if (clientEV) event_source_destroy (clientEV);
    if (serverEV) event_source_destroy (serverEV);

#else

    while (true) {
        if (g_socket_is_closed (socket)) {
            g_info("x client close");
            break;
        }

        if (g_socket_is_closed (xServerSocket)) {
            g_info("x server close");
            break;
        }

        // client
        strLen = read_all_data (socket, &binStr);
        if (strLen > 0) {
            g_info("XClient To XServer[%d]:\n%s\n", strLen, binStr);

            g_socket_send_with_blocking(xServerSocket, binStr, strLen, true, NULL, &error);
            if (error) {
                g_warning("xclient write to xserver error: '%s'", error->message);
                break;
            }
        }

        //
        strLen = read_all_data (xServerSocket, &binStr);
        if (strLen > 0) {
            g_info("XServer To XClient[%d]:\n%s\n", strLen, binStr);

            g_socket_send_with_blocking(socket, binStr, strLen, true, NULL, &error);
            if (error) {
                g_warning("xserver write to xclient error: '%s'", error->message);
                break;
            }
        }
    }
#endif
}

static GSocket* get_x_server_socket ()
{
    struct sockaddr *saddr;
    struct sockaddr_un saun;
    g_autoptr(GError) error = NULL;

    saun.sun_family = AF_UNIX;
    snprintf (saun.sun_path, sizeof(saun.sun_path) - 1, "/tmp/.X11-unix/X%d", gXDefaultPort - DEFAULT_PORT);
    unsigned long salen = sizeof (saun.sun_family) + strlen (saun.sun_path) + 1;
    saddr = (struct sockaddr*) &saun;

    int serverFd = socket(saddr->sa_family, SOCK_STREAM, 0);
    if (serverFd < 0) {
        perror("socket() to Server failed");
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

static gsize read_all_data(GSocket* fr, char** out/*out*/)
{
    g_return_val_if_fail(out, 0);

    gsize len = 0;
    char* str = NULL;
    g_autoptr (GError) error = NULL;

    gsize readLen;
    char buf[1024] = {0};

    while ((readLen = g_socket_receive(fr, buf, sizeof(buf) - 1, NULL, &error)) > 0) {
        if (error) {
            g_warning("error: %s", error->message);
            break;
        }

        char* tmp = (gchar*) malloc (sizeof (char) * (len + readLen + 1));
        if (!tmp) {
            g_warning("malloc error!");
            break;
        }
        if (str && len > 0) {
            memcpy (tmp, str, len);
            g_free (str);
        }
        memcpy (tmp + len, buf, readLen);
        str = tmp;
        len += readLen;

        if (readLen < sizeof (buf) - 1) {
            break;
        }
    }

    if (*out) g_free (*out);
    *out = str;

    return len;
}

static void set_client_socket (int fd)
{
    int tmp = 1;
    (void) setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (char *) &tmp, sizeof(int));

    struct linger linger = {.l_onoff = 0, linger.l_linger = 0};
    (void) setsockopt(fd, SOL_SOCKET, SO_LINGER, (char *) &linger, sizeof linger);
}
