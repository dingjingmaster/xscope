//
// Created by dingjing on 23-5-17.
//

#include "xtype-record.h"

#include "xtype-common.h"

void xtype_record_init(void)
{
    (void) define_type(CHAR2B,      RECORD, "CHAR2B",       get_str_CHAR2B);
    (void) define_type(POINT,       RECORD, "POINT",        get_str_POINT);
    (void) define_type(RECTANGLE,   RECORD, "RECTANGLE",    get_str_RECTANGLE);
    (void) define_type(ARC,         RECORD, "ARC",          get_str_ARC);
    (void) define_type(HOST,        RECORD, "HOST",         get_str_HOST);
    (void) define_type(TIMECOORD,   RECORD, "TIMECOORD",    get_str_TIMECOORD);
    (void) define_type(FONTPROP,    RECORD, "FONTPROP",     get_str_FONTPROP);
    (void) define_type(CHARINFO,    RECORD, "CHARINFO",     get_str_CHARINFO);
    (void) define_type(SEGMENT,     RECORD, "SEGMENT",      get_str_SEGMENT);
    (void) define_type(COLORITEM,   RECORD, "COLORITEM",    get_str_COLORITEM);
    (void) define_type(RGB,         RECORD, "RGB",          get_str_RGB);
    (void) define_type(FORMAT,      RECORD, "FORMAT",       get_str_FORMAT);
    (void) define_type(SCREEN,      RECORD, "SCREEN",       get_str_SCREEN);
    (void) define_type(DEPTH,       RECORD, "DEPTH",        get_str_DEPTH);
    (void) define_type(VISUALTYPE,  RECORD, "VISUALTYPE",   get_str_VISUALTYPE);
}
