//
// Created by dingjing on 23-5-6.
//
#include <stdio.h>
#include <string.h>
#include <locale.h>

#include "fd.h"
#include "proto.h"
#include "global.h"
#include "common.h"

static void setup_stdin ();
static void setup_raw_file (const char* fileName);
static void setup_raw_client (FD* returnClientFD, FD* returnServerFD);
static void setup_connection_socket (int iPort, void (*connFunc) (int));

static void set_raw_fd_map (FD origFD, FD currentFD);

static FD fd_pair (FD fd);
static FD client_half (FD fd);
static FD server_half (FD fd);
static inline FD get_raw_fd_map (FD origFD);
static void reset_pair (FD client, FD server);

static void unmap_raw_fd (FD currentFD);

static int client_number (FD fd);
static const char* client_name (FD fd);

static void read_stdin (FD fd);
static void close_connection (FD fd);
static void data_from_raw_file (FD fd);

static short get_scope_port (void);

static void new_audio (FD fd);
static void new_connection (FD fd);

/**
 * @brief
 *
 */

int main (int argc, char* argv[])
{
    setlocale(LC_CTYPE, "");

    initialize_fd();
    initialize_x11();

    if (gDoAudio) {
        initialize_audio();
    }
    setup_stdin();
    if (gRawFile) {
        setup_raw_file(gRawFile);
    }
    else {
        setup_connection_socket (get_scope_port(), new_connection);
        if (gDoAudio) {
            setup_connection_socket (2000 + get_scope_port(), new_audio);
        }
    }

    //
    set_signal_handling();

    return main_loop();
}

static void read_stdin (FD fd)
{
    char buf[2048] = {0};

    enter_procedure ("read_stdin");

    long n = read (fd, buf, sizeof (buf) - 1);

    debug(4, (stderr, "read %ld bytes from stdin\n", n));
}

static void setup_stdin ()
{
    enter_procedure ("setup_stdin");

    using_fd (fileno (stdin), read_stdin, NULL, NULL);
}

static void setup_raw_file (const char* fileName)
{
    FD fd;

    enter_procedure ("setup_raw_file");

    if (0 == strcmp("-", fileName)) {
        gRaw = stdin;
    }
    else {
        gRaw = fopen (fileName, "r");
    }

    if (NULL == gRaw) {
        perror (fileName);
        panic ("Can't open raw file for reading");
    }

    fd = fileno (gRaw);
    debug(4, (stderr, "Opened raw file %s: FD %d\n", fileName, fd));

    if (NULL == gFDInfo[fd].buffer) {
        gFDInfo[fd].buffer = calloc (1, BUFFER_SIZE);
        if (NULL == gFDInfo[fd].buffer) {
            panic ("unable to allocate client buffer");
        }
    }

    gFDInfo[fd].bufCount = 0;
    gFDInfo[fd].bufLimit = -1;
    gFDInfo[fd].bufDelivered = 0;

    using_fd (fd, data_from_raw_file, NULL, NULL);
}

static void setup_connection_socket (int iPort, void (*connFunc) (int));

static short get_scope_port (void)
{
    enter_procedure ("get_scope_port");

    short port = (short) (gServerBasePort + gServerInPort + gServerDisplay);

    debug(4, (stderr, "scope service is on port %d\n", port));

    return port;
}

static void data_from_raw_file (FD rawFd)
{
    enter_procedure ("data_from_raw_file");

    bool fromClient = true;
    FD fd = -1;
    char* in = NULL;
    char* n = NULL;
    unsigned char* out;
    static FD newServerFD;


    gVerbose = gXVerbose;

    while (true) {
        // If we alread read a line last time, process it first.
        // else get the next line for processing
        if (0 == gFDInfo[rawFd].bufCount) {
            if (NULL == fgets (gFDInfo[rawFd].buffer, BUFFER_SIZE, gRaw)) {
                close_connection (rawFd);
                exit(0);
            }
            gFDInfo[rawFd].bufCount = (int) strlen (gFDInfo[rawFd].buffer);
            debug(16, (stderr, "raw input = %s", gFDInfo[rawFd].buffer));
        }
        in = gFDInfo[rawFd].buffer;

        /* lines starting with space indicate change of sender */
        if (isspace(*in)) {
            // if we already have data in buffer. process it
            if ((-1 != fd) && (gFDInfo[fd].bufCount > 0)) {
                debug(16, (stderr, "reporting %d bytes from: %s %s\n", gFDInfo[fd].bufCount, fromClient ? "client" : "server", client_name (fd)));
                if (fromClient) {
                    report_from_client (fd, gFDInfo[fd].buffer, gFDInfo[fd].bufCount);
                }
                else {
                    report_from_server (fd, gFDInfo[fd].buffer, gFDInfo[fd].bufCount);
                }
                gFDInfo[fd].bufCount = 0;
                return;
            }
            else {
                while (isspace(*in)) {
                    ++in;
                }
                if (0 == strncmp (in, "Client Connect (fd ", 19)) {
                    FD clientFD, serverFD, origFD;
                    origFD = (FD) strtol (in + 19, NULL, 10);
                    setup_raw_client (&clientFD, &serverFD);
                    set_raw_fd_map (origFD, clientFD);
                    fd = clientFD;
                    fromClient = true;
                    newServerFD = serverFD;
                }
                else if (0 == strncmp (in, "Server Connect (fd ", 19)) {
                    // new client connection
                    FD origFD;
                    if (0 == newServerFD) {
                        panic ("Server connection without matching client");
                    }
                    origFD = (FD) strtol (in + 19, NULL, 10);
                    set_raw_fd_map (origFD, newServerFD);
                    fd = newServerFD;
                    fromClient = false;
                    newServerFD = 0;
                }
                else if (strstr (in, " --> EOF")) {
                    // closing client connection
                    n = strstr (in, ": Client");
                    if (NULL != n) {
                        int clientID;

                        in = n + 8;
                        if (isdigit(*in)) {
                            clientID = (FD) strtol (in, NULL, 10);
                        }
                        else {
                            clientID = 1;
                        }

                        for (fd = 0; fd < gHighestFD; ++fd) {
                            if (gFDInfo[fd].clientNumber == clientID) {
                                if (gVerbose >= 0) {
                                    print_time();
                                    fprintf (stdout, "Client%s --> EOF\n", client_name (fd));
                                }
                                unmap_raw_fd (fd);
                                unmap_raw_fd (fd_pair (fd));
                                close_connection (fd);
                                break;
                            }
                        }
                    }
                    fd = -1;
                }
                else {
                    FD origFD;

                    if (0 == strncmp (in, "Request ", 8)) {
                        fromClient = true;
                    }
                    else {
                        fromClient = false;
                    }

                    in = strstr (in, "(fd ");
                    if (NULL == in) {
                        warn ("Did not find fd string in input entry");
                        warn (gFDInfo[rawFd].buffer);
                        gFDInfo[rawFd].bufCount = 0;
                        continue;
                    }

                    origFD = (FD) strtol (in + 4, NULL, 10);
                    fd = get_raw_fd_map (origFD);
                    if (-1 == fd) {
                        debug(16, (stderr, "origFD = %d\n", origFD));
                        warn ("Unknow fd in input entry");
                        gFDInfo[rawFd].bufCount = 0;
                        continue;
                    }
                }
                debug(16, (stderr, "raw data from: %s\n", fromClient ? "client" : "server"));
                n = strchr (in, ':');
                if (NULL != n) {
                    in = n + 1;
                }
                while (isspace(*in)) {
                    ++in;
                }
            }
        }

        if (-1 == fd) {
            gFDInfo[rawFd].bufCount = 0;
            continue;
        }

        out = gFDInfo[fd].buffer + gFDInfo[fd].bufCount;

        while (*in != '\0') {
            unsigned char val;

            if ((in[0] >= '0') && (in[0] <= '9')) {
                val = (in[0] - '0') << 4;
            }
            else if ((in[0] >= 'a') && (in[0] < 'f')) {
                val = (in[0] - 'a' + 0x0a) << 4;
            }
            else {
                warn (in);
                warn ("invalid raw file input");
                break;
            }

            if ((in[1] >= '0') && (in[1] <= '9')) {
                val += (in[1] - '0');
            }
            else if ((in[1] >= 'a') && (in[1] <= 'f')) {
                val += (in[1] - 'a' + 0x0a);
            }
            else {
                warn (in + 1);
                warn ("invalid raw file input");
                break;
            }

            if (in[2] == ' ') {
                in += 3;
            } else {
                in += 2;
            }
            while ((*in == '\r') || (*in == '\n')) {
                in++;
            }

            *out++ = val;
            ++gFDInfo[fd].bufCount;

            /* If buffer is full, process what we have now */
            if (gFDInfo[fd].bufCount >= BUFFER_SIZE) {
                if (fromClient) {
                    report_from_client (fd, gFDInfo[fd].buffer, gFDInfo[fd].bufCount);
                }
                else {
                    report_from_server(fd, gFDInfo[fd].buffer, gFDInfo[fd].bufCount);
                }
                gFDInfo[fd].bufCount = 0;
                out = gFDInfo[fd].buffer;
            }
        }
        gFDInfo[rawFd].bufCount = 0;
    }
}

static FD fd_pair (FD fd)
{
    return gFDInfo[fd].pair;
}

static FD client_half (FD fd)
{
    if (gFDInfo[fd].server) {
        return gFDInfo[fd].pair;
    }

    return fd;
}

static FD server_half (FD fd)
{
    if (gFDInfo[fd].server) {
        return fd;
    }

    return gFDInfo[fd].pair;
}

static void reset_pair (FD client, FD server)
{
    if (client >= 0) {
        free(gFDInfo[client].buffer);
        gFDInfo[client].buffer = NULL;
        gFDInfo[client].bufCount = 0;
        gFDInfo[client].bufLimit = -1;
        gFDInfo[client].bufDelivered = 0;
    }

    if (server >= 0) {
        free(gFDInfo[server].buffer);
        gFDInfo[server].buffer = NULL;
        gFDInfo[server].bufCount = 0;
        gFDInfo[server].bufLimit = -1;
        gFDInfo[server].bufDelivered = 0;
    }
}

static void close_connection (FD fd)
{
    debug(4, (stderr, "close %d and %d\n", fd, fd_pair (fd)));
    reset_pair (client_half (fd), server_half (fd));

    stop_client_connection (server_half (fd));
    stop_server_connection (client_half (fd));

    close_fd (fd);
    close_fd (fd_pair(fd));

    if (gTerminateClose) {
        exit (0);
    }
}

static int client_number (FD fd)
{
    return gFDInfo[fd].clientNumber;
}

static const char* client_name (FD fd)
{
    static char name[12] = {0};

    if (client_number (fd) <= 1) {
        return "";
    }

    snprintf (name, sizeof(name) - 1, " %d", gFDInfo[fd].clientNumber);

    return name;
}
