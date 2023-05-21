//
// Created by dingjing on 23-5-12.
//

#include "decode_x11.h"

#include "../tools.h"
#include "../global.h"
#include "../proto/xproto.h"
#include "../proto/xtype-common.h"


#define DUMP_REQUEST                0
#define DUMP_REPLY	                1
#define DUMP_EVENT                  2
#define DUMP_ERROR                  3

const char *REQUESTHEADER = "............REQUEST";
const char *EVENTHEADER   = "..............EVENT";
const char *ERRORHEADER   = "..............ERROR";
const char *REPLYHEADER   = "..............REPLY";



void CreateWindow(const unsigned char *buf)
{
    /* Request CreateWindow is opcode 1 */
    g_autofree char* r = get_str_field_by_type (buf, 0, 1, REQUEST, REQUESTHEADER); /* CreateWindow */
    g_autofree char* seqNum = get_str_field_by_type (gSBF, 0, 4, CARD32, "sequence number");

    g_autofree char* depth = get_str_field_by_type(buf, 1, 1, CARD8, "depth");
    g_autofree char* wid = get_str_field_by_type(buf, 4, 4, WINDOW, "wid");
    g_autofree char* par = get_str_field_by_type(buf, 8, 4, WINDOW, "parent");
    g_autofree char* x = get_str_field_by_type(buf, 12, 2, INT16, "x");
    g_autofree char* y = get_str_field_by_type(buf, 14, 2, INT16, "y");
    g_autofree char* w = get_str_field_by_type(buf, 16, 2, CARD16, "width");
    g_autofree char* h = get_str_field_by_type(buf, 18, 2, CARD16, "height");
    g_autofree char* bw = get_str_field_by_type(buf, 20, 2, CARD16, "border-width");
    g_autofree char* c = get_str_field_by_type(buf, 22, 2, WINDOWCLASS, "class");
    g_autofree char* v = get_str_field_by_type(buf, 24, 4, VISUALIDC, "visual");
    g_autofree char* vm = get_str_field_by_type(buf, 28, 4, WINDOW_BITMASK, "value-mask");
//    PrintValues(&buf[28], 4, WINDOW_BITMASK, &buf[32], "value-list");


}

void ChangeWindowAttributes(const unsigned char *buf)
{
    /* Request ChangeWindowAttributes is opcode 2 */
    g_autofree char* r = get_str_field_by_type(buf, 0, 1, REQUEST, REQUESTHEADER); /* ChangeWindowAttributes */
    g_autofree char* seqNum = get_str_field_by_type(gSBF, 0, 4, CARD32, "sequence number");

//    printreqlen(buf, fd, DVALUE2(3 + n));
    g_autofree char* win = get_str_field_by_type(buf, 4, 4, WINDOW, "window");
    g_autofree char* vm = get_str_field_by_type(buf, 8, 4, WINDOW_BITMASK, "value-mask");
//    PrintValues(&buf[8], 4, WINDOW_BITMASK, &buf[12], "value-list");
}

void GetWindowAttributes(const unsigned char *buf)
{
    /* Request GetWindowAttributes is opcode 3 */
    g_autofree char* r = get_str_field_by_type (buf, 0, 1, REQUEST, REQUESTHEADER); /* GetWindowAttributes */
    g_autofree char* seqNum = get_str_field_by_type (gSBF, 0, 4, CARD32, "sequence number");

//    printreqlen(buf, fd, CONST2(2));
    g_autofree char* win = get_str_field_by_type(buf, 4, 4, WINDOW, "window");
}

void GetWindowAttributesReply(const unsigned char *buf)
{
    g_autofree char* r = get_str_field_by_type(gSBF, 0, 1, REPLY, REPLYHEADER); /* GetWindowAttributes */
    g_autofree char* bst = get_str_field_by_type(buf, 1, 1, BACKSTORE, "backing-store");
    g_autofree char* seqNum = get_str_field_by_type(buf, 2, 2, CARD16, "sequence number");
    g_autofree char* rl = get_str_field_by_type(buf, 4, 4, CONST4(3), "reply length");
    g_autofree char* v = get_str_field_by_type(buf, 8, 4, VISUALID, "visual");
    g_autofree char* c = get_str_field_by_type(buf, 12, 2, WINDOWCLASS, "class");
    g_autofree char* bg = get_str_field_by_type(buf, 14, 1, BITGRAVITY, "bit-gravity");
    g_autofree char* wg = get_str_field_by_type(buf, 15, 1, WINGRAVITY, "win-gravity");
    g_autofree char* bp = get_str_field_by_type(buf, 16, 4, CARD32, "backing-planes");
    g_autofree char* bpx = get_str_field_by_type(buf, 20, 4, CARD32, "backing-pixel");
    g_autofree char* su = get_str_field_by_type(buf, 24, 1, BOOL, "save-under");
    g_autofree char* mi = get_str_field_by_type(buf, 25, 1, BOOL, "map-is-installed");
    g_autofree char* ms = get_str_field_by_type(buf, 26, 1, MAPSTATE, "map-state");
    g_autofree char* or = get_str_field_by_type(buf, 27, 1, BOOL, "override-redirect");
    g_autofree char* cm = get_str_field_by_type(buf, 28, 4, COLORMAP, "colormap");
    g_autofree char* am = get_str_field_by_type(buf, 32, 4, SETofEVENT, "all-event-masks");
    g_autofree char* ym = get_str_field_by_type(buf, 36, 4, SETofEVENT, "your-event-mask");
    g_autofree char* dm = get_str_field_by_type(buf, 40, 2, SETofDEVICEEVENT, "do-not-propagate-mask");
}

void DestroyWindow(const unsigned char *buf)
{
    /* Request DestroyWindow is opcode 4 */
    g_autofree char* r = get_str_field_by_type (buf, 0, 1, REQUEST, REQUESTHEADER); /* DestroyWindow */
    g_autofree char* seqNum = get_str_field_by_type(gSBF, 0, 4, CARD32, "sequence number");

//    printreqlen(buf, fd, CONST2(2));
    g_autofree char* ww = get_str_field_by_type(buf, 4, 4, WINDOW, "window");
}

void DestroySubwindows(const unsigned char *buf)
{
    /* Request DestroySubwindows is opcode 5 */
    g_autofree char* r = get_str_field_by_type(buf, 0, 1, REQUEST, REQUESTHEADER); /* DestroySubwindows */
    g_autofree char* seqNum = get_str_field_by_type (gSBF, 0, 4, CARD32, "sequence number");

//    printreqlen(buf, fd, CONST2(2));
    g_autofree char* w = get_str_field_by_type(buf, 4, 4, WINDOW, "window");
}

void ChangeSaveSet(const unsigned char *buf)
{
    /* Request ChangeSaveSet is opcode 6 */
    g_autofree char* r = get_str_field_by_type(buf, 0, 1, REQUEST, REQUESTHEADER); /* ChangeSaveSet */
    g_autofree char* seqNum = get_str_field_by_type (gSBF, 0, 4, CARD32, "sequence number");

    g_autofree char* mode = get_str_field_by_type(buf, 1, 1, INS_DEL, "mode");
//    printreqlen(buf, fd, CONST2(2));
    g_autofree char* win = get_str_field_by_type(buf, 4, 4, WINDOW, "window");
}

void ReparentWindow(const unsigned char *buf)
{
    /* Request ReparentWindow is opcode 7 */
    g_autofree char* r = get_str_field_by_type(buf, 0, 1, REQUEST, REQUESTHEADER); /* ReparentWindow */
    g_autofree char* seqNum = get_str_field_by_type(gSBF, 0, 4, CARD32, "sequence number");

//    printreqlen(buf, fd, CONST2(4));
    g_autofree char* win = get_str_field_by_type(buf, 4, 4, WINDOW, "window");
    g_autofree char* par = get_str_field_by_type(buf, 8, 4, WINDOW, "parent");
    g_autofree char* x = get_str_field_by_type(buf, 12, 2, INT16, "x");
    g_autofree char* y = get_str_field_by_type(buf, 14, 2, INT16, "y");
}

void MapWindow(const unsigned char *buf)
{
    /* Request MapWindow is opcode 8 */
    g_autofree char* r = get_str_field_by_type(buf, 0, 1, REQUEST, REQUESTHEADER); /* MapWindow */
    g_autofree char* seqNum = get_str_field_by_type (gSBF, 0, 4, CARD32, "sequence number");

//    printreqlen(buf, fd, CONST2(2));
    g_autofree char* win = get_str_field_by_type(buf, 4, 4, WINDOW, "window");
}

void MapSubwindows(const unsigned char *buf)
{
    /* Request MapSubwindows is opcode 9 */
    g_autofree char* r = get_str_field_by_type (buf, 0, 1, REQUEST, REQUESTHEADER); /* MapSubwindows */
    g_autofree char* seqNum = get_str_field_by_type (gSBF, 0, 4, CARD32, "sequence number");

//    printreqlen(buf, fd, CONST2(2));
    g_autofree char* win = get_str_field_by_type(buf, 4, 4, WINDOW, "window");
}

void UnmapWindow(const unsigned char *buf)
{
    /* Request UnmapWindow is opcode 10 */
    g_autofree char* r = get_str_field_by_type(buf, 0, 1, REQUEST, REQUESTHEADER); /* UnmapWindow */
    g_autofree char* seqNum = get_str_field_by_type (gSBF, 0, 4, CARD32, "sequence number");

//    printreqlen(buf, fd, CONST2(2));
    g_autofree char* win = get_str_field_by_type(buf, 4, 4, WINDOW, "window");
}

void UnmapSubwindows(const unsigned char *buf)
{
    /* Request UnmapSubwindows is opcode 11 */
    g_autofree char* req = get_str_field_by_type(buf, 0, 1, REQUEST, REQUESTHEADER); /* UnmapSubwindows */
    g_autofree char* seqNum = get_str_field_by_type(gSBF, 0, 4, CARD32, "sequence number");

//    printreqlen(buf, fd, CONST2(2));
    g_autofree char* win = get_str_field_by_type(buf, 4, 4, WINDOW, "window");
}

void ConfigureWindow(const unsigned char *buf)
{
    /* Request ConfigureWindow is opcode 12 */
    g_autofree char* req = get_str_field_by_type(buf, 0, 1, REQUEST, REQUESTHEADER); /* ConfigureWindow */
    g_autofree char* seqNum = get_str_field_by_type(gSBF, 0, 4, CARD32, "sequence number");

//    printreqlen(buf, fd, DVALUE2(3 + n));
    g_autofree char* win = get_str_field_by_type(buf, 4, 4, WINDOW, "window");
    g_autofree char* vmk = get_str_field_by_type(buf, 8, 2, CONFIGURE_BITMASK, "value-mask");
//    PrintValues(&buf[8], 2, CONFIGURE_BITMASK, &buf[12], "value-list");
}

void CirculateWindow(const unsigned char *buf)
{
    /* Request CirculateWindow is opcode 13 */
    g_autofree char* req = get_str_field_by_type(buf, 0, 1, REQUEST, REQUESTHEADER); /* CirculateWindow */
    g_autofree char* seqNum = get_str_field_by_type(gSBF, 0, 4, CARD32, "sequence number");

    g_autofree char* dir = get_str_field_by_type(buf, 1, 1, CIRMODE, "direction");
//    printreqlen(buf, fd, CONST2(2));
    g_autofree char* win = get_str_field_by_type(buf, 4, 4, WINDOW, "window");
}

void GetGeometry(const unsigned char *buf)
{
    /* Request GetGeometry is opcode 14 */
    g_autofree char* req = get_str_field_by_type(buf, 0, 1, REQUEST, REQUESTHEADER); /* GetGeometry */
    g_autofree char* seqNum = get_str_field_by_type(gSBF, 0, 4, CARD32, "sequence number");

//    printreqlen(buf, fd, CONST2(2));
    g_autofree char* draw = get_str_field_by_type(buf, 4, 4, DRAWABLE, "drawable");
}

void GetGeometryReply(const unsigned char *buf)
{
    g_autofree char* req = get_str_field_by_type(gSBF, 0, 1, REPLY, REPLYHEADER); /* GetGeometry */
    g_autofree char* depth = get_str_field_by_type(buf, 1, 1, CARD8, "depth");
    g_autofree char* seqNum = get_str_field_by_type(buf, 2, 2, CARD16, "sequence number");
    g_autofree char* replyLen = get_str_field_by_type(buf, 4, 4, CONST4(0), "reply length");

    g_autofree char* root = get_str_field_by_type(buf, 8, 4, WINDOW, "root");
    g_autofree char* x = get_str_field_by_type(buf, 12, 2, INT16, "x");
    g_autofree char* y = get_str_field_by_type(buf, 14, 2, INT16, "y");
    g_autofree char* w = get_str_field_by_type(buf, 16, 2, CARD16, "width");
    g_autofree char* h = get_str_field_by_type(buf, 18, 2, CARD16, "height");
    g_autofree char* bw = get_str_field_by_type(buf, 20, 2, CARD16, "border-width");
}

void QueryTree(const unsigned char *buf)
{
    /* Request QueryTree is opcode 15 */
    g_autofree char* req = get_str_field_by_type(buf, 0, 1, REQUEST, REQUESTHEADER); /* QueryTree */
    g_autofree char* seqNum = get_str_field_by_type(gSBF, 0, 4, CARD32, "sequence number");

//    printreqlen(buf, fd, CONST2(2));
    g_autofree char* win = get_str_field_by_type(buf, 4, 4, WINDOW, "window");
}

void QueryTreeReply(const unsigned char *buf)
{
    g_autofree char* req = get_str_field_by_type(gSBF, 0, 1, REPLY, REPLYHEADER); /* QueryTree */
    g_autofree char* seqNum = get_str_field_by_type(buf, 2, 2, CARD16, "sequence number");
    g_autofree char* replyLen = get_str_field_by_type(buf, 4, 4, DVALUE4(n), "reply length");
    g_autofree char* root = get_str_field_by_type(buf, 8, 4, WINDOW, "root");
    g_autofree char* parent = get_str_field_by_type(buf, 12, 4, WINDOW, "parent");
    g_autofree char* childNum = get_str_field_by_type(buf, 16, 2, DVALUE2(n), "number of children");
    short n = tools_short(&buf[16]);
//    PrintList(&buf[32], (long) n, WINDOW, "children");
}

