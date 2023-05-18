//
// Created by dingjing on 23-5-18.
//

#ifndef XSCOPE_DECODE_XCLIENT_H
#define XSCOPE_DECODE_XCLIENT_H

#include "io/io.h"


typedef enum XClientProcess             XClientProcess;

enum XClientProcess
{
    XC_START_SETUP_MESSAGE      = 0,
    XC_FINISH_SETUP_MESSAGE     = 1,
    XC_START_REQUEST_MESSAGE    = 2,
    XC_FINISH_REQUEST_MESSAGE   = 3,
};


void xclient_start_setup_message    (IOCache* cache);
void xclient_finish_setup_message   (IOCache* cache);

void xclient_start_request_message  (IOCache* cache);
void xclient_finish_request_message (IOCache* cache);


#endif //XSCOPE_DECODE_XCLIENT_H
