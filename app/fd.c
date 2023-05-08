//
// Created by dingjing on 23-5-8.
//

#include "fd.h"

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/uio.h>
#include <sys/ioctl.h>

#include "global.h"
#include "common.h"

void initialize_fd (void)
{
    enter_procedure ("initializeFD");

    gMaxFD = sysconf (_SC_OPEN_MAX);
    if (gMaxFD > FD_SETSIZE) {
        gMaxFD = FD_SETSIZE;
    }

    gFDD = calloc (gMaxFD, sizeof (struct FDDescriptor));
    if (NULL == gFDD) {
        panic ("Can't allocate memory for file descriptor table");
    }

    gFDInfo = calloc (gMaxFD, sizeof (FDInfo));
    if (NULL == gFDInfo) {
        panic ("Can't allocate memory for file descriptor info table");
    }

    for (int i = 0; i < gMaxFD; ++i) {
        if (i > 2) {
            close (i);
        }
    }

    gMaxFD -= 4;

    gNFDsInUse = 0;
    FD_ZERO(&gReadDescriptors);
    gHighestFD = 0;

    using_fd (fileno (stdin),  NULL, NULL, NULL);
    using_fd (fileno (stdout), NULL, NULL, NULL);
    using_fd (fileno (stderr), NULL, NULL, NULL);

}

void using_fd(FD fd, void (*handler)(int), void (*flushHandler)(int), XtransConnInfo transConn)
{
    if (gFDD[fd].busy) {
        not_using_fd (fd);
    }

    gNFDsInUse += 1;
    gFDD[fd].busy = true;
    gFDD[fd].InputHandler = handler;
    gFDD[fd].FlushHandler = flushHandler;

    if (NULL == handler) {
        FD_CLR(fd, &gReadDescriptors);
    }
    else {
        FD_SET(fd, &gReadDescriptors);
    }

    if (fd > gHighestFD) {
        gHighestFD = fd;
    }

    if (gNFDsInUse >= gMaxFD) {
        panic ("no more FDs");
    }

    debug(128, (stderr, "Using FD %d, %d of %d in use\n", fd, gNFDsInUse, gMaxFD));
}

void not_using_fd(FD fd)
{
    debug(128, (stderr, "Not Using FD %d\n", fd));

    if (gFDD[fd].busy) {
        gNFDsInUse -= 1;
    }

    gFDD[fd].busy = false;
    FD_CLR(fd, &gReadDescriptors);

    while (!gFDD[gHighestFD].busy && gHighestFD > 0) {
        gHighestFD -= 1;
    }

    debug(128, (stderr, "Highest FD: %d, in use %d\n", gHighestFD, gNFDsInUse));
}

int main_loop(void)
{
    return 0;
}
