//
// Created by dingjing on 23-5-8.
//

#ifndef XSCOPE_COMMON_H
#define XSCOPE_COMMON_H
#include <stdio.h>

#define __USE_BSD_SIGNAL
#include <signal.h>

#include "global.h"

#define debug(n, f)     (void)((gDebugLevel & n) ? (fprintf f, fflush(stderr)) : 0)

void enter_procedure (const char* s);

void warn (const char* s);
void panic (const char* s);

void signal_URG (int sig);
void signal_INT (int sig);
void signal_PIPE (int sig);
void signal_QUIT (int sig);
void signal_TERM (int sig);
void signal_TSTP (int sig);
void signal_CONT (int sig);
void signal_USR1 (int sig);

void set_signal_handling (void);


#endif //XSCOPE_COMMON_H
