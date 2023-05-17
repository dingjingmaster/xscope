//
// Created by dingjing on 23-5-12.
//

#include "xtype-builtin.h"

#include <stdio.h>

#include "tools.h"
#include "xproto.h"
#include "xtype-common.h"
#include "decode/decode_x11.h"


void xtype_builtin_init(void)
{
    (void) define_type(INT8,        BUILTIN, "INT8",        get_str_INT8);
    (void) define_type(INT16,       BUILTIN, "INT16",       get_str_INT16);
    (void) define_type(INT32,       BUILTIN, "INT32",       get_str_INT32);
    (void) define_type(CARD8,       BUILTIN, "CARD8",       get_str_CARD8);
    (void) define_type(CARD16,      BUILTIN, "CARD16",      get_str_CARD16);
    (void) define_type(CARD32,      BUILTIN, "CARD32",      get_str_CARD32);
    (void) define_type(BYTE,        BUILTIN, "BYTE",        get_str_BYTE);
    (void) define_type(CHAR8,       BUILTIN, "CHAR8",       get_str_CHAR8);
    (void) define_type(STRING16,    BUILTIN, "STRING16",    get_str_STRING16);
    (void) define_type(STR,         BUILTIN, "STR",         get_str_STR);
    (void) define_type(WINDOW,      BUILTIN, "WINDOW",      get_str_WINDOW);
    (void) define_type(WINDOWD,     BUILTIN, "WINDOWD",     get_str_WINDOWD);
    (void) define_type(WINDOWNR,    BUILTIN, "WINDOWNR",    get_str_WINDOWNR);
    (void) define_type(PIXMAP,      BUILTIN, "PIXMAP",      get_str_PIXMAP);
    (void) define_type(PIXMAPNPR,   BUILTIN, "PIXMAPNPR",   get_str_PIXMAPNPR);
    (void) define_type(PIXMAPC,     BUILTIN, "PIXMAPC",     get_str_PIXMAPC);
    (void) define_type(CURSOR,      BUILTIN, "CURSOR",      get_str_CURSOR);
    (void) define_type(FONT,        BUILTIN, "FONT",        get_str_FONT);
    (void) define_type(GCONTEXT,    BUILTIN, "GCONTEXT",    get_str_GCONTEXT);
    (void) define_type(COLORMAP,    BUILTIN, "COLORMAP",    get_str_COLORMAP);
    (void) define_type(COLORMAPC,   BUILTIN, "COLORMAPC",   get_str_COLORMAPC);
    (void) define_type(DRAWABLE,    BUILTIN, "DRAWABLE",    get_str_DRAWABLE);
    (void) define_type(FONTABLE,    BUILTIN, "FONTABLE",    get_str_FONTABLE);
    (void) define_type(ATOM,        BUILTIN, "ATOM",        get_str_ATOM);
    (void) define_type(ATOMT,       BUILTIN, "ATOMT",       get_str_ATOMT);
    (void) define_type(VISUALID,    BUILTIN, "VISUALID",    get_str_VISUALID);
    (void) define_type(VISUALIDC,   BUILTIN, "VISUALIDC",   get_str_VISUALIDC);
    (void) define_type(TIMESTAMP,   BUILTIN, "TIMESTAMP",   get_str_TIMESTAMP);
    (void) define_type(RESOURCEID,  BUILTIN, "RESOURCEID",  get_str_RESOURCEID);
    (void) define_type(KEYSYM,      BUILTIN, "KEYSYM",      get_str_KEYSYM);
    (void) define_type(KEYCODE,     BUILTIN, "KEYCODE",     get_str_KEYCODE);
    (void) define_type(KEYCODEA,    BUILTIN, "KEYCODEA",    get_str_KEYCODEA);
    (void) define_type(BUTTON,      BUILTIN, "BUTTON",      get_str_BUTTON);
    (void) define_type(BUTTONA,     BUILTIN, "BUTTONA",     get_str_BUTTONA);
    (void) define_type(EVENTFORM,   BUILTIN, "EVENTFORM",   get_str_EVENTFORM);
}
