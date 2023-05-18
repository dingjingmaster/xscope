//
// Created by dingjing on 23-5-16.
//

#include "decode.h"

#include <glib.h>

#include "global.h"
#include "../tools.h"
#include "decode_x11.h"
#include "decode-xclient.h"
#include "decode-xserver.h"
#include "../proto/xtype-common.h"



bool decode_x_server(IOContext* ioCtx)
{
    g_return_val_if_fail(ioCtx, false);

    IOCache* server = &ioCtx->xServer;
    if (!server->uData) {
        server->uData = XS_START_SETUP_MESSAGE;
    }

    switch ((int)(server->uData)) {
        case XS_START_SETUP_MESSAGE:
        case XS_FINISH_SETUP_MESSAGE: {
            xserver_start_setup_message (server);
            server->uData = (void*) XS_START_REQUEST_MESSAGE;
            break;
        }
        case XS_START_REQUEST_MESSAGE:
        case XS_FINISH_REQUEST_MESSAGE: {
            xserver_start_request_message (server);
            server->uData = (void*) XS_START_REQUEST_MESSAGE;
            break;
        }
        default: {
            break;
        }
    }

    return true;
}

bool decode_x_client(IOContext *ioCtx)
{
    g_return_val_if_fail(ioCtx, false);

    IOCache* client = &ioCtx->xClient;
    if (!client->uData) {
        client->uData = XC_START_SETUP_MESSAGE;
    }

    switch ((int)(client->uData)) {
        case XC_START_SETUP_MESSAGE:
        case XC_FINISH_SETUP_MESSAGE: {
            xclient_start_setup_message (client);
            client->uData = (void*) XC_START_REQUEST_MESSAGE;
            break;
        }
        case XC_START_REQUEST_MESSAGE:
        case XC_FINISH_REQUEST_MESSAGE: {
            xclient_start_request_message (client);
            client->uData = (void*) XC_START_REQUEST_MESSAGE;
            break;
        }
        default: {
            break;
        }
    }

    return true;
}
