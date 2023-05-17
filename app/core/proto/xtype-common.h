//
// Created by dingjing on 23-5-17.
//

#ifndef XSCOPE_XTYPE_COMMON_H
#define XSCOPE_XTYPE_COMMON_H
#include <stdint.h>
#include "proto/xproto.h"

#ifdef __cplusplus
extern "C"
{
#endif

char* get_str_INT8          (const unsigned char* buf);
char* get_str_INT16         (const unsigned char* buf);
char* get_str_INT32         (const unsigned char* buf);
char* get_str_CARD8         (const unsigned char* buf);
char* get_str_CARD16        (const unsigned char* buf);
char* get_str_CARD32        (const unsigned char* buf);
char* get_str_BYTE          (const unsigned char* buf);
char* get_str_CHAR8         (const unsigned char* buf);
char* get_str_STRING16      (const unsigned char* buf);
char* get_str_STR           (const unsigned char* buf);
char* get_str_WINDOW        (const unsigned char* buf);
char* get_str_WINDOWD       (const unsigned char* buf);
char* get_str_WINDOWNR      (const unsigned char* buf);
char* get_str_PIXMAP        (const unsigned char* buf);
char* get_str_PIXMAPNPR     (const unsigned char* buf);
char* get_str_PIXMAPC       (const unsigned char* buf);
char* get_str_CURSOR        (const unsigned char* buf);
char* get_str_FONT          (const unsigned char* buf);
char* get_str_GCONTEXT      (const unsigned char* buf);
char* get_str_COLORMAP      (const unsigned char* buf);
char* get_str_COLORMAPC     (const unsigned char* buf);
char* get_str_DRAWABLE      (const unsigned char* buf);
char* get_str_FONTABLE      (const unsigned char* buf);
char* get_str_ATOM          (const unsigned char* buf);
char* get_str_ATOMT         (const unsigned char* buf);
char* get_str_VISUALID      (const unsigned char* buf);
char* get_str_VISUALIDC     (const unsigned char* buf);
char* get_str_TIMESTAMP     (const unsigned char* buf);
char* get_str_RESOURCEID    (const unsigned char* buf);
char* get_str_KEYSYM        (const unsigned char* buf);
char* get_str_KEYCODE       (const unsigned char* buf);
char* get_str_KEYCODEA      (const unsigned char* buf);
char* get_str_BUTTON        (const unsigned char* buf);
char* get_str_BUTTONA       (const unsigned char* buf);
char* get_str_EVENTFORM     (const unsigned char* buf);
char* get_str_EVENT         (const unsigned char* buf);
char* get_str_CHAR2B        (const unsigned char* buf);
char* get_str_POINT         (const unsigned char* buf);
char* get_str_RECTANGLE     (const unsigned char* buf);
char* get_str_ARC           (const unsigned char* buf);
char* get_str_HOST          (const unsigned char* buf);
char* get_str_TIMECOORD     (const unsigned char* buf);
char* get_str_FONTPROP      (const unsigned char* buf);
char* get_str_CHARINFO      (const unsigned char* buf);
char* get_str_SEGMENT       (const unsigned char* buf);
char* get_str_COLORITEM     (const unsigned char* buf);
char* get_str_RGB           (const unsigned char* buf);
char* get_str_FORMAT        (const unsigned char* buf);


char* get_str_SET           (const unsigned char *buf, short length, struct ValueListEntry *ValueList);
char* get_str_ENUMERATED    (const unsigned char *buf, short length, struct ValueListEntry *ValueList);

char* get_str_field_by_string8      (const unsigned char* buf, int number, const char* name);
char* get_str_field_by_type         (const unsigned char *buf, short start, short length, short FieldType, const char *name);

#ifdef __cplusplus
}
#endif
#endif //XSCOPE_XTYPE_COMMON_H
