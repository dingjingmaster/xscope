//
// Created by dingjing on 23-5-6.
//

#ifndef XSCOPE_GLOBAL_H
#define XSCOPE_GLOBAL_H
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <locale.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/uio.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <netinet/tcp.h>
#include <asm-generic/param.h>

#include "fd.h"
#include "x11.h"

// avoid conflicts with Solaris <sys/regset.h> #define of CS
#undef CS
extern struct ConnState*            CS;

static FILE*                        gRaw = 0;

static short                        gDebugLevel = 255;          // 2        : trace each procedure entry;
                                                                // 4        : I/O,connections;
                                                                // 8        : scope internals;
                                                                // 16       : Message protocol
                                                                // 32 - 64  : was malloc, now unused
                                                                // 128 - 256: really low level

static short                        gVerbose = 7;
static short                        gXVerbose = 1;
static short                        gNasVerbose = 1;

static int                          gScopePort = 0;
static char*                        gScopeHost = NULL;

static char                         gTranslateText = 1;
static char                         gIsUtf8Locale = 1;
static char                         gScopeEnabled = 1;
static char                         gHandleSIGUSR1 = 1;

static char                         gDoAudio = 1;
static char                         gInterrupt = 1;
static char                         gTerminateClose = 1;

static char                         gServerHostName[MAXHOSTNAMELEN];
static char                         gAudioServerHostName[MAXHOSTNAMELEN];

static long                         gServerInPort = 1;
static long                         gServerOutPort = 0;
static long                         gServerDisplay = 0;
static char*                        gRawFile = NULL;

static FDDescriptor*                gFDD = NULL;
static long                         gMaxFD = 0;
static FDInfo*                      gFDInfo = NULL;
static int                          gNFDsInUse = 0;
static fd_set                       gReadDescriptors;
static fd_set                       gWriteDescriptors;
static fd_set                       gBlockedReadDescriptors;
static int                          gHighestFD;

static long                         gServerBasePort = DEFAULT_PORT;

#endif //XSCOPE_GLOBAL_H
