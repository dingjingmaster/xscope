//
// Created by dingjing on 23-5-16.
//

#include "decode.h"

#include <glib.h>

#include "global.h"
#include "../tools.h"
#include "decode_x11.h"

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
    unsigned char* buf = cache->xReadCache;

    g_return_if_fail(buf);

    gLittleEndian = (buf[0] == 'l');

    g_autofree char* byteOrder = decode_field (buf, 0, 1, BYTEMODE, "byte-order");
    g_autofree char* majorVersion = decode_field (buf, 2, 2, CARD16, "major-version");
    g_autofree char* minorVersion = decode_field (buf, 4, 2, CARD16, "minor-version");
    g_autofree char* nameLenStr = decode_field (buf, 6, 2, DVALUE2(0), "length of name");
    gsize nameLen = tools_short (&buf[6]);
    g_autofree char* dataLenStr = decode_field (buf, 8, 2, DVALUE2(0), "length of name");
    gsize dataLen = tools_short (&buf[8]);
//    g_autofree char* authProtoName = decode_field (buf, 8, 2, DVALUE2(0), "length of name");

    g_info("%s", byteOrder);
    g_info("%s", majorVersion);
    g_info("%s", minorVersion);
    g_info("%s", nameLenStr);
    g_info("%s", dataLenStr);


    g_info("little: %s", gLittleEndian ? "true" : "false");
    g_info("name len: %d, data len: %d", nameLen, dataLen);
}
