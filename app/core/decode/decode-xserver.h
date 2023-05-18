//
// Created by dingjing on 23-5-18.
//

#ifndef XSCOPE_DECODE_XSERVER_H
#define XSCOPE_DECODE_XSERVER_H

#include "io/io.h"


typedef enum XServerProcess             XServerProcess;


enum XServerProcess
{
    XS_START_SETUP_MESSAGE      = 0,
    XS_FINISH_SETUP_MESSAGE     = 1,
    XS_START_REQUEST_MESSAGE    = 2,
    XS_FINISH_REQUEST_MESSAGE   = 3,
};


void xserver_start_setup_message    (IOCache* cache);
void xserver_finish_setup_message   (IOCache* cache);

void xserver_start_request_message  (IOCache* cache);
void xserver_finish_request_message (IOCache* cache);



#endif //XSCOPE_DECODE_XSERVER_H
