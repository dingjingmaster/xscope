//
// Created by dingjing on 23-5-16.
//

#include "decode.h"

#include <glib.h>

#include "global.h"

typedef enum XClientProcess             XClientProcess;
typedef struct XClientDecodeContext     XClientDecodeContext;

enum XClientProcess
{
    XC_START_SETUP_MESSAGE      = 0,
};

struct XClientDecodeContext
{
    GList*                  parsedKeyValue;
    XClientProcess          clientProcess;
};

void xclient_start_setup_message (IOCache* cache, XClientDecodeContext* ctx);

bool decode_x_server(const char *buf, gsize bufLen, char **print)
{

    return true;
}

bool decode_x_client(IOContext *ioCtx)
{
    g_return_val_if_fail(ioCtx, false);

    IOCache* client = &ioCtx->xClient;
    if (!client->uData) {
        XClientDecodeContext* ctx = g_malloc0 (sizeof (XClientDecodeContext));
        client->uData = ctx;
        // FIXME://
        ctx->clientProcess = XC_START_SETUP_MESSAGE;
    }

    XClientDecodeContext* ctx = client->uData;

    switch (ctx->clientProcess) {
        case XC_START_SETUP_MESSAGE: {
            xclient_start_setup_message (client, ctx);
            break;
        }
        default: {
            break;
        }
    }




    return true;
}

char* start_setup_message (const char* buf, gsize bufLen)
{

}

void xclient_start_setup_message (IOCache* cache, XClientDecodeContext* ctx)
{
    gLittleEndian = (cache->xReadCache[0] == 'l');

}
