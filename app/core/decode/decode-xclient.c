//
// Created by dingjing on 23-5-18.
//

#include "decode-xclient.h"

#include <glib.h>
#include <gio/gio.h>

#include "tools.h"
#include "global.h"
#include "proto/xtype-common.h"



void xclient_start_setup_message (IOCache* cache)
{
    unsigned char* buf = cache->xReadCache;

    g_return_if_fail(buf);

    if (cache->xParsedReadStr) {
        g_free (cache->xParsedReadStr);
        cache->xParsedReadStr = NULL;
    }

    gLittleEndian = (buf[0] == 'l');

    short nameLen = (short) tools_short (&buf[6]);
    short dataLen = (short) tools_short (&buf[8]);

    g_autofree char* byteOrder = get_str_field_by_type(buf, 0, 1, BYTEMODE, "byte-order");
    g_autofree char* majorVersion = get_str_field_by_type(buf, 2, 2, CARD16, "major-version");
    g_autofree char* minorVersion = get_str_field_by_type(buf, 4, 2, CARD16, "minor-version");
//    g_autofree char* nameLenStr = get_str_field_by_type(buf, 6, 2, DVALUE2(0), "length of name");
//    g_autofree char* dataLenStr = get_str_field_by_type(buf, 8, 2, DVALUE2(0), "length of name");
    g_autofree char* authProtoName = get_str_field_by_string8(&buf[12], (int) nameLen, "authorization-protocol-name");
    g_autofree char* authProtoData = get_str_field_by_string8(&buf[pad((long)(12 + nameLen))], (int) dataLen, "authorization-protocol-data");

    if (cache->xParsedReadStr) {
        g_free (cache->xParsedReadStr);
        cache->xParsedReadStr = NULL;
    }

    cache->xParsedReadStr = g_strdup_printf ("                   byte-order : %s\n"
                                             "                major-version : %s\n"
                                             "                minor-version : %s\n"
                                             "  authorization-protocol-name : %s\n"
                                             "  authorization-protocol-data : %s\n",
                                             byteOrder, majorVersion, minorVersion, authProtoName, authProtoData);
#if 0
    g_info("%s", byteOrder);
    g_info("%s", majorVersion);
    g_info("%s", minorVersion);
    g_info("%s", nameLenStr);
    g_info("%s", dataLenStr);

    g_info("little: %s", gLittleEndian ? "true" : "false");
    g_info("name len: %d, data len: %d", nameLen, dataLen);
#endif
}

void xclient_finish_setup_message(IOCache *cache)
{
    unsigned char* buf = cache->xReadCache;

    g_return_if_fail(buf);

    if (cache->xParsedReadStr) {
        g_free (cache->xParsedReadStr);
        cache->xParsedReadStr = NULL;
    }

//    gLittleEndian = (buf[0] == 'l');


}

void xclient_start_request_message(IOCache *cache)
{

}
