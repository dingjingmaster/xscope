//
// Created by dingjing on 23-5-17.
//

#include <arpa/inet.h>
#include "xtype-common.h"

#include "tools.h"
#include "xproto.h"
#include "xtype-atom.h"
#include "global.h"


char* get_str_INT8(const unsigned char *buf)
{
    /* print a INT8 -- 8-bit signed integer */
    short n = tools_byte(buf);

    if (n > 127) {
        n = (short) (256 - n);
    }

    return g_strdup_printf ("%d", n);
}

char* get_str_INT16(const unsigned char *buf)
{
    /* print a INT16 -- 16-bit signed integer */
    long n = tools_short(buf);

    if (n > 32767) {
        n = 65536 - n;
    }

    return g_strdup_printf ("%d", n);
}

char* get_str_INT32(const unsigned char *buf)
{
    /* print a INT32 -- 32-bit signed integer */
    long n = tools_long(buf);

    return g_strdup_printf ("%d", n);
}

char* get_str_CARD8(const unsigned char *buf)
{
    /* print a CARD8 -- 8-bit unsigned integer */
    unsigned short n = tools_byte(buf);

    return g_strdup_printf ("%d", (n & 0xff));
}

char* get_str_CARD16(const unsigned char *buf)
{
    /* print a CARD16 -- 16-bit unsigned integer */
    unsigned long n = tools_short(buf);

    return g_strdup_printf ("%d", (n & 0xffff));
}

char* get_str_CARD32(const unsigned char *buf)
{
    /* print a CARD32 -- 32-bit unsigned integer */
    unsigned long n = tools_long(buf);

    return g_strdup_printf ("%d", n);
}

char* get_str_BYTE(const unsigned char *buf)
{
    /* print a BYTE -- 8-bit value */
    short n = tools_byte(buf);

    return g_strdup_printf ("%d", n);
}

char* get_str_CHAR8(const unsigned char *buf)
{
    /* print a CHAR8 -- 8-bit character */
    unsigned short n = tools_byte(buf);

    return g_strdup_printf ("%s", get_key_string(n));
}

char* get_str_STRING16(const unsigned char *buf)
{
    /* print a CHAR2B -- 16-bit character which is never byte-swapped */
    unsigned short n = tools_char2B(buf);

    return g_strdup_printf ("%s", get_key_string(n));
}

char* get_str_STR(const unsigned char *buf)
{
    /* STR have the length (1 byte) then a string of CHAR8 */
    short n = tools_byte(buf++);
    GString* str = g_string_new (NULL);

    for (short i = 0; i < n; i++) {
        g_string_append(str, get_key_string (buf[i]));
        g_string_append_c(str, ' ');
    }

    return g_string_free(str, false);
}

char* get_str_WINDOW(const unsigned char *buf)
{
    /* print a WINDOW -- CARD32  plus 0 = None */
    long n = tools_long(buf);

    if (n == 0) {
        return g_strdup("None");
    }
    else {
        return g_strdup_printf ("WIN %08lx", n);
    }
}

char* get_str_WINDOWD(const unsigned char *buf)
{
    /* print a WINDOWD -- CARD32  plus 0 = PointerWindow, 1 = InputFocus */
    long n = tools_long(buf);

    if (n == 0) {
        return g_strdup("PointerWindow");
    }
    else if (1 == n) {
        return g_strdup("InputFocus");
    }
    else {
        return get_str_WINDOW(buf);
    }
}

char* get_str_WINDOWNR(const unsigned char *buf)
{
    /* print a WINDOWNR -- CARD32  plus 0 = None, 1 = PointerRoot */
    long n = tools_long(buf);

    if (n == 0) {
        return g_strdup ("None");
    }
    else if (n == 1) {
        return g_strdup("PointerRoot");
    }
    else {
        return get_str_WINDOW(buf);
    }
}

char* get_str_PIXMAP(const unsigned char *buf)
{
    /* print a PIXMAP -- CARD32  plus 0 = None */
    long n = tools_long(buf);

    if (n == 0) {
        return g_strdup("None");
    }
    else {
        return g_strdup_printf("PXM %08lx", n);
    }
}

char* get_str_PIXMAPNPR(const unsigned char *buf)
{
    /* print a PIXMAPNPR -- CARD32  plus 0 = None, 1 = ParentRelative */
    long n = tools_long(buf);

    if (n == 0) {
        return g_strdup("None");
    }
    else if (n == 1) {
        return g_strdup("ParentRelative");
    }
    else {
        return get_str_PIXMAP(buf);
    }
}

char* get_str_PIXMAPC(const unsigned char *buf)
{
    /* print a PIXMAPC -- CARD32  plus 0 = CopyFromParent */
    long n = tools_long(buf);

    if (n == 0) {
        return g_strdup("CopyFromParent");
    }
    else {
        return get_str_PIXMAP(buf);
    }
}

char* get_str_CURSOR(const unsigned char *buf)
{
    /* print a CURSOR -- CARD32  plus 0 = None */
    long n = tools_long(buf);

    if (n == 0) {
        return g_strdup("None");
    }
    else {
        return g_strdup_printf("CUR %08lx", n);
    }
}

char* get_str_FONT(const unsigned char *buf)
{
    /* print a FONT -- CARD32  plus 0 = None */
    long n = tools_long(buf);

    if (n == 0) {
        return g_strdup("None");
    }
    else {
        return g_strdup_printf("FNT %08lx", n);
    }
}

char* get_str_GCONTEXT(const unsigned char *buf)
{
    /* print a GCONTEXT -- CARD32 */
    long n = tools_long(buf);

    return g_strdup_printf("GXC %08lx", n);
}

char* get_str_COLORMAP(const unsigned char *buf)
{
    /* print a COLORMAP -- CARD32 plus 0 = None */
    long n = tools_long(buf);

    if (n == 0) {
        return g_strdup("None");
    }
    else {
        return g_strdup_printf("CMP %08lx", n);
    }
}

char* get_str_COLORMAPC(const unsigned char *buf)
{
    /* print a COLORMAPC -- CARD32 plus 0 = CopyFromParent */
    long n = tools_long(buf);

    if (n == 0) {
        return g_strdup("CopyFromParent");
    }
    else {
        return get_str_COLORMAP(buf);
    }
}

char* get_str_DRAWABLE(const unsigned char *buf)
{
    /* print a DRAWABLE -- CARD32 */
    long n = tools_long(buf);

    return g_strdup_printf("DWB %08lx", n);
}

char* get_str_FONTABLE(const unsigned char *buf)
{
    /* print a FONTABLE -- CARD32 */
    long n = tools_long(buf);

    return g_strdup_printf("FTB %08lx", n);
}

char* get_str_ATOM(const unsigned char *buf)
{
    /* print a ATOM -- CARD32 plus 0 = None */
    long n = tools_long(buf);
    const char* name = find_atom_name (n);

    if (name != NULL) {
        return g_strdup_printf("ATM %08lx <%s>", n, name);
    }
    else {
        return g_strdup_printf("ATM %08lx", n);
    }
}

char* get_str_ATOMT(const unsigned char *buf)
{
    /* print a ATOMT -- CARD32 plus 0 = AnyPropertyType */
    long n = tools_long(buf);

    if (n == 0) {
        return g_strdup("AnyPropertyType");
    }
    else {
        return get_str_ATOM(buf);
    }
}

char* get_str_VISUALID(const unsigned char *buf)
{
    /* print a VISUALID -- CARD32 plus 0 = None */
    long n = tools_long(buf);

    if (n == 0) {
        return g_strdup("None");
    }
    else {
        return g_strdup_printf("VIS %08lx", n);
    }
}

char* get_str_VISUALIDC(const unsigned char *buf)
{
    /* print a VISUALIDC -- CARD32 plus 0 = CopyFromParent */
    long n = tools_long(buf);

    if (n == 0) {
        return g_strdup("CopyFromParent");
    }
    else {
        return get_str_VISUALID(buf);
    }
}

char* get_str_TIMESTAMP(const unsigned char *buf)
{
    /* print a TIMESTAMP -- CARD32 plus 0 as the current time */
    long n = tools_long(buf);

    if (n == 0) {
        return g_strdup("CurrentTime");
    }
    else {
        return g_strdup_printf("TIM %08lx", n);
    }
}

char* get_str_RESOURCEID(const unsigned char *buf)
{
    /* print a RESOURCEID -- CARD32 plus 0 = AllTemporary */
    long n = tools_long(buf);

    if (n == 0) {
        return g_strdup("AllTemporary");
    }
    else {
        return g_strdup_printf("RID %08lx", n);
    }
}

char* get_str_KEYSYM(const unsigned char *buf)
{
    /* print a KEYSYM -- CARD32 */
    long n = tools_long(buf);

    return g_strdup_printf("KYS %08lx", n);
}

char* get_str_KEYCODE(const unsigned char *buf)
{
    /* print a KEYCODE -- CARD8 */
    unsigned short n = tools_byte(buf);

    return g_strdup_printf("%d (%s)", n, get_key_string(n));
}

char* get_str_KEYCODEA(const unsigned char *buf)
{
    /* print a KEYCODEA -- CARD8 plus 0 = AnyKey */
    long n = tools_byte(buf);

    if (n == 0) {
        return g_strdup("AnyKey");
    }
    else {
        return get_str_KEYCODE(buf);
    }
}

char* get_str_BUTTON(const unsigned char *buf)
{
    /* print a BUTTON -- CARD8 */
    unsigned short n = tools_byte(buf);

    return g_strdup_printf("%d (%s)", n, get_key_string(n));
}

char* get_str_BUTTONA(const unsigned char *buf)
{
    /* print a BUTTONA -- CARD8 plus 0 = AnyButton */
    long n = tools_byte(buf);

    if (n == 0) {
        return g_strdup("AnyButton");
    }
    else {
        return get_str_BUTTON(buf);
    }
}

char* get_str_EVENTFORM(const unsigned char *buf)
{
    /* print an EVENT_FORM -- event format */
//    decode_event(-1, buf, (long) -1);
    return NULL;
}

char* get_str_ENUMERATED (const unsigned char *buf, short length, struct ValueListEntry *ValueList)
{
    long n;
    struct ValueListEntry *p;

    if (length == 1) {
        n = tools_byte(buf);
    }
    else if (length == 2) {
        n = tools_short(buf);
    }
    else {
        n = tools_long(buf);
    }

    p = ValueList;
    while (p != NULL && p->value != n) {
        p = p->next;
    }

    if (p != NULL) {
        return g_strdup_printf("%s", p->name);
    }
    else {
        return g_strdup_printf("**INVALID** (%ld)", n);
    }
}

char *get_str_EVENT(const unsigned char *buf)
{
    uint8_t n = tools_byte(buf);
    long e = (long) (n & 0x7f);
    struct ValueListEntry *p;

    p = gTD[EVENT].valueList;
    while (p != NULL && p->value != e) {
        p = p->next;
    }

    if (p != NULL) {
        return g_strdup_printf("%s", p->name);
    }
    else {
        return g_strdup_printf("**INVALID** (%d)", n);
    }
}

char *get_str_SET(const unsigned char *buf, short length, struct ValueListEntry *ValueList)
{
    unsigned long n;
    bool FoundOne = false;
    bool matchesAll = false;
    struct ValueListEntry *p;
    GString* str = g_string_new (NULL);

    if (length == 1) {
        n = tools_byte(buf);
    }
    else if (length == 2) {
        n = tools_short(buf);
    }
    else {
        n = tools_long(buf);
    }

    if (n != 0) {
        /* first check if the value matches ALL of the bits. */
        matchesAll = true;
        for (p = ValueList; matchesAll && (p != NULL); p = p->next) {
            if ((p->value & n) == 0) {
                matchesAll = false;
            }
        }

        if (!matchesAll)
            /* if it matches some, but not all, print only those it matches */
            for (p = ValueList; p != NULL; p = p->next) {
                if ((p->value & n) != 0) {
                    if (FoundOne) {
                        g_string_append_c(str, '|');
                    }
                    g_string_append(str, p->name);
                    FoundOne = true;
                }
            }
    }

    if (matchesAll) {
        g_string_append(str, "<ALL>");
    }
    else if (!FoundOne) {
        g_string_append(str, "0");
    }

    return g_string_free(str, false);
}

char *get_str_CHAR2B(const unsigned char *buf)
{
    g_autofree char* byte1 = get_str_field_by_type (buf, 0, 1, CARD8, "byte1");
    g_autofree char* byte2 = get_str_field_by_type (buf, 1, 1, CARD8, "byte2");

    return g_strdup_printf ("(%s, %s)", byte1, byte2);
}

char *get_str_field_by_type(const unsigned char *buf, short start, short length, short FieldType, const char *name)
{
    (void) name;

    switch (gTD[FieldType].type) {
        case BUILTIN: {
            return (*gTD[FieldType].printProc) (&buf[start]);
        }
        case ENUMERATED: {
            return get_str_ENUMERATED(&buf[start], length, gTD[FieldType].valueList);
        }
        case SET: {
            return get_str_SET(&buf[start], length, gTD[FieldType].valueList);
        }
        case RECORD: {
            return (*gTD[FieldType].printProc) (&buf[start]);
        }
    }
    return NULL;
}

char *get_str_POINT(const unsigned char *buf)
{
    g_autofree char* x = get_str_field_by_type (buf, 0, 2, INT16, "x");
    g_autofree char* y = get_str_field_by_type (buf, 2, 2, INT16, "y");

    return g_strdup_printf ("(%s, %s)", x, y);
}

char *get_str_RECTANGLE(const unsigned char *buf)
{
    g_autofree char* x = get_str_field_by_type (buf, 0, 2, INT16,   "x");
    g_autofree char* y = get_str_field_by_type (buf, 2, 2, INT16,   "y");
    g_autofree char* w = get_str_field_by_type (buf, 4, 2, CARD16,  "width");
    g_autofree char* h = get_str_field_by_type (buf, 6, 2, CARD16,  "height");

    return g_strdup_printf ("(%s, %s, %s, %s)", x, y, w, h);
}

char *get_str_ARC(const unsigned char *buf)
{
    g_autofree char* x = get_str_field_by_type (buf, 0, 2, INT16,   "x");
    g_autofree char* y = get_str_field_by_type (buf, 2, 2, INT16,   "y");
    g_autofree char* w = get_str_field_by_type (buf, 4, 2, CARD16,  "width");
    g_autofree char* h = get_str_field_by_type (buf, 6, 2, CARD16,  "height");
    g_autofree char* angle1 = get_str_field_by_type (buf, 8, 2,  INT16,  "angle1");
    g_autofree char* angle2 = get_str_field_by_type (buf, 10, 2, INT16,  "angle2");

    return g_strdup_printf ("(%s, %s, %s, %s, %s, %s)", x, y, w, h, angle1, angle2);
}

char *get_str_HOST(const unsigned char *buf)
{
    g_autofree char* familyStr = get_str_field_by_type(buf, 0, 1, HOSTFAMILY, "family");
    g_autofree char* addrLen = get_str_field_by_type(buf, 2, 2, DVALUE2(n), "length of address");
    g_autofree char* addr = NULL;
    g_autofree char* type = NULL;
    g_autofree char* value = NULL;
    short n = tools_short(&buf[2]);
    switch (buf[0]) {
        case 0: {
            struct in_addr ia;
            char* addrT;

            memcpy(&ia, &buf[4], sizeof(ia));       /* Need to get alignment right */
            addrT = inet_ntoa(ia);
            addr = get_str_field_by_string8 ((unsigned char *) addrT, (int) strlen(addrT), "address");
            break;
        }
#ifdef IPv6
        case 6: {
        struct in6_addr i6a;
        char addr[INET6_ADDRSTRLEN];

        memcpy(&i6a, &buf[4], sizeof(i6a));     /* Need to get alignment right */
        inet_ntop(AF_INET6, &i6a, addr, sizeof(addr));
        PrintString8((unsigned char *) addr, strlen(addr), "address");
        break;
    }
#endif
        case 5: {
            int i;

            for (i = 0; buf[i + 4] != 0; i++) {
                /* empty loop */
            }
            type = get_str_field_by_string8 (&buf[4], i, "type");
            value = get_str_field_by_string8(&buf[i + 5], n - i - 1, "value");
            break;
        }
        case 254: {
            addr = get_str_field_by_string8(&buf[4], n, "address");
            break;
        }
        default: {
//            PrintList(&buf[4], (long) n, BYTE, "address");
        }
    }

    return g_strdup_printf ("(%s, %s)", familyStr ? familyStr : "<null>", addr ? addr : "<null>");
}

char *get_str_field_by_string8(const unsigned char *buf, int number, const char *name)
{
    if (number == 0 || NULL == buf) {
        return NULL;
    }

    GString* str = g_string_new (NULL);
    for (int i = 0; i < number; i++) {
        const char* ss = get_key_string (buf[i]);
        g_string_append(str, ss);
    }

    return g_string_free(str, false);
}

char *get_str_TIMECOORD(const unsigned char *buf)
{
    g_autofree char* tim = get_str_field_by_type (buf, 0, 4, TIMESTAMP, "time");
    g_autofree char* x = get_str_field_by_type (buf, 4, 2, CARD16, "x");
    g_autofree char* y = get_str_field_by_type (buf, 6, 2, CARD16, "y");

    return g_strdup_printf ("(time:%s, x:%s, y:%s)", tim, x, y);
}

char *get_str_FONTPROP(const unsigned char *buf)
{
    g_autofree char* name = get_str_field_by_type (buf, 0, 4, ATOM, "name");
    g_autofree char* value = get_str_field_by_type (buf, 4, 4, INT32, "value");

    return g_strdup_printf ("(name:%s, value:%s)", name, value);
}

char *get_str_CHARINFO(const unsigned char *buf)
{
    g_autofree char* l = get_str_field_by_type (buf, 0, 2, INT16, "left-side-bearing");
    g_autofree char* r = get_str_field_by_type (buf, 2, 2, INT16, "right-side-bearing");
    g_autofree char* c = get_str_field_by_type (buf, 4, 2, INT16, "character-width");
    g_autofree char* a = get_str_field_by_type (buf, 6, 2, INT16, "ascent");
    g_autofree char* d = get_str_field_by_type (buf, 8, 2, INT16, "descent");
    g_autofree char* t = get_str_field_by_type (buf, 10, 2, CARD16, "attributes");

    return g_strdup_printf ("(left-side-bearing:%s, right-side-bearing:%s, character-width:%s, ascent:%s, descent:%s, attributes:%s)", l, r, c, a, d, t);
}

char *get_str_SEGMENT(const unsigned char *buf)
{
    g_autofree char* x1 = get_str_field_by_type (buf, 0, 2, INT16, "x1");
    g_autofree char* y1 = get_str_field_by_type (buf, 2, 2, INT16, "y1");
    g_autofree char* x2 = get_str_field_by_type (buf, 4, 2, INT16, "x2");
    g_autofree char* y2 = get_str_field_by_type (buf, 6, 2, INT16, "y2");

    return g_strdup_printf ("(x1:%s, y1:%s, x2:%s, y2:%s)", x1, y1, x2, y2);
}

char *get_str_COLORITEM(const unsigned char *buf)
{
    g_autofree char* p = get_str_field_by_type (buf, 0, 4, CARD32, "pixel");
    g_autofree char* r = get_str_field_by_type (buf, 4, 2, CARD16, "red");
    g_autofree char* g = get_str_field_by_type (buf, 6, 2, CARD16, "green");
    g_autofree char* b = get_str_field_by_type (buf, 8, 2, CARD16, "blue");
    g_autofree char* c = get_str_field_by_type (buf, 10, 2, COLORMASK, "component selector");

    return g_strdup_printf ("(pixel:%s, red:%s, green:%s, blue:%s, component selector:%s)", p, r, g, b, c);
}

char *get_str_RGB(const unsigned char *buf)
{
    g_autofree char* r = get_str_field_by_type (buf, 0, 2, CARD16, "red");
    g_autofree char* g = get_str_field_by_type (buf, 2, 2, CARD16, "green");
    g_autofree char* b = get_str_field_by_type (buf, 4, 2, CARD16, "blue");

    return g_strdup_printf ("(red: %s, green: %s, blue: %s)", r, g, b);
}

char *get_str_FORMAT(const unsigned char *buf)
{
    g_autofree char* d = get_str_field_by_type (buf, 0, 1, CARD8, "depth");
    g_autofree char* b = get_str_field_by_type (buf, 1, 1, CARD8, "bits-per-pixel");
    g_autofree char* s = get_str_field_by_type (buf, 2, 1, CARD8, "scanline-pad");

    return g_strdup_printf ("(depth: %s, bits-per-pixel: %s, scanline-pad: %s)", d, b, s);
}

char* get_str_SCREEN(const unsigned char *buf)
{
//    short n; /* number of elements in List of DEPTH */
//    long m; /* length (in bytes) of List of DEPTH */

    g_autofree char* rt = get_str_field_by_type (buf, 0, 4, WINDOW, "root");
    g_autofree char* dc = get_str_field_by_type (buf, 4, 4, COLORMAP, "default-colormap");
    g_autofree char* wp = get_str_field_by_type (buf, 8, 4, CARD32, "white-pixel");
    g_autofree char* bp = get_str_field_by_type (buf, 12, 4, CARD32, "black-pixel");
    g_autofree char* ci = get_str_field_by_type (buf, 16, 4, SETofEVENT, "current-input-masks");
    g_autofree char* wi = get_str_field_by_type (buf, 20, 2, CARD16, "width-in-pixels");
    g_autofree char* hi = get_str_field_by_type (buf, 22, 2, CARD16, "height-in-pixels");
    g_autofree char* wm = get_str_field_by_type (buf, 24, 2, CARD16, "width-in-millimeters");
    g_autofree char* hm = get_str_field_by_type (buf, 26, 2, CARD16, "height-in-millimeters");
    g_autofree char* mi = get_str_field_by_type (buf, 28, 2, CARD16, "min-installed-maps");
    g_autofree char* ma = get_str_field_by_type (buf, 30, 2, CARD16, "max-installed-maps");
    g_autofree char* rv = get_str_field_by_type (buf, 32, 4, VISUALID, "root-visual");
    g_autofree char* bs = get_str_field_by_type (buf, 36, 1, BACKSTORE, "backing-stores");
    g_autofree char* su = get_str_field_by_type (buf, 37, 1, BOOL, "save-unders");
    g_autofree char* rd = get_str_field_by_type (buf, 38, 1, CARD8, "root-depth");
    g_autofree char* na = get_str_field_by_type (buf, 39, 1, CARD8, "number of allowed-depths");
//    n = IByte(&buf[39]);
//    m = PrintList(&buf[40], (long) n, DEPTH, "allowed-depths");
//    return (40 + m);

    return g_strdup_printf ("(root: %s, default-colormap: %s, white-pixel: %s, black-pixel: %s, "
                            "current-input-masks: %s, width-in-pixels: %s, height-in-pixels: %s, "
                            "width-in-millimeters: %s, height-in-millimeters: %s, "
                            "min-installed-maps: %s, max-installed-maps: %s, "
                            "root-visual: %s, backing-stores: %s, "
                            "save-unders: %s, root-depth: %s, number of allowed-depths: %s)",
                            rt, dc, wp, bp, ci, wi, hi, wm, hm, mi, ma, rv, bs, su, rd, na);
}

char* get_str_DEPTH (const unsigned char *buf)
{
//    short n; /* number of elements in List of VISUALTYPE */
//    short m; /* length (in bytes) of List of VISUALTYPE */

    g_autofree char* dp = get_str_field_by_type (buf, 0, 1, CARD8, "depth");
    g_autofree char* nv = get_str_field_by_type (buf, 2, 2, DVALUE2(n), "number of visuals");
//    n = IShort(&buf[2]);
//    m = PrintList(&buf[8], (long) n, VISUALTYPE, "visuals");
//    return (8 + m);
    return g_strdup_printf ("(depth: %s, number of visuals: %s)", dp, nv);
}

char* get_str_VISUALTYPE (const unsigned char *buf)
{
    g_autofree char* vi = get_str_field_by_type(buf, 0, 4, VISUALID, "visual-id");
    g_autofree char* cs = get_str_field_by_type(buf, 4, 1, COLORCLASS, "class");
    g_autofree char* bp = get_str_field_by_type(buf, 5, 1, CARD8, "bits-per-rgb-value");
    g_autofree char* ce = get_str_field_by_type(buf, 6, 2, CARD16, "colormap-entries");
    g_autofree char* rm = get_str_field_by_type(buf, 8, 4, CARD32, "red-mask");
    g_autofree char* gm = get_str_field_by_type(buf, 12, 4, CARD32, "green-mask");
    g_autofree char* bm = get_str_field_by_type(buf, 16, 4, CARD32, "blue-mask");
//    return (24);
    return g_strdup_printf ("(visual-id: %s, class: %s, bits-per-rgb-value: %s, "
                            "colormap-entries: %s, red-mask: %s, green-mask: %s, "
                            "blue-mask: %s)", vi, cs, bp, ce, rm, gm, bm);
}

char *get_str_field_by_list(const unsigned char *buf, long number, short listType, const char *name)
{
    if (0 == number) {
        return NULL;
    }

    GString* str = g_string_new (NULL);

    for (int i = 0; i < number; ++i) {
        long len = 0;
        switch (gTD[listType].type) {
            case BUILTIN:
            case RECORD: {
                g_autofree char* ll = (*gTD[listType].printProc) (buf);
                len = (long) strlen (ll);
                g_string_append(str, ll);
                g_string_append(str, ", ");
                break;
            }
            default:
                g_string_append(str, "**INVALID**");
                break;
        }
        buf = buf + len;
    }

    g_autofree char* strT = g_string_free(str, false);

    if (g_str_has_suffix(strT, ", ")) {
        strT[strlen (strT) - 2] = '\0';
    }

    return g_strdup_printf ("(%s: %s)", name, strT);
}
