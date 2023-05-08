//
// Created by dingjing on 23-5-8.
//

#include "common.h"

#include <stdio.h>


void enter_procedure(const char *s)
{
    debug(2, (stderr, "-> %s\n", s));
}

void warn(const char *s)
{
    fprintf (stderr, "###### %s\n", s);
}

void panic(const char *s)
{
    fprintf (stderr, "panic==> %s\n", s);
    exit (1);
}

void set_signal_handling(void)
{
    enter_procedure ("set_signal_handling");

    (void) signal (SIGURG,  signal_URG);
    (void) signal (SIGPIPE, signal_PIPE);
    (void) signal (SIGINT,  signal_INT);
    (void) signal (SIGQUIT, signal_QUIT);
    (void) signal (SIGTERM, signal_TERM);
    (void) signal (SIGTSTP, signal_TSTP);
    (void) signal (SIGCONT, signal_CONT);

    if (gHandleSIGUSR1) {
        (void) signal (SIGUSR1, signal_USR1);
    }
}

void signal_URG(int sig)
{
    debug(1, (stderr, "==> SIGURG received\n"));

    (void) sig;
}

void signal_INT(int sig)
{
    debug(1, (stderr, "==> SIGINT received\n"));
    gInterrupt = 1;

    (void) sig;
}

void signal_PIPE(int sig)
{
    debug(1, (stderr, "==> SIGPIPE received\n"));

    (void) sig;
}

void signal_QUIT(int sig)
{
    debug(1, (stderr, "==> SIGQUIT received\n"));

    (void) sig;

    exit (1);
}

void signal_TERM(int sig)
{
    debug(1, (stderr, "==> SIGTERM received\n"));

    (void) sig;

    exit (1);
}

void signal_TSTP(int sig)
{
    debug(1, (stderr, "==> SIGTSTP received\n"));

    (void) sig;
}

void signal_CONT(int sig)
{
    debug(1, (stderr, "==> SIGCONT received\n"));

    (void) sig;
}

void signal_USR1(int sig)
{
    debug(1, (stderr, "==> SIGUSR1 received\n"));

    (void) sig;
}
