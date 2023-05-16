//
// Created by dingjing on 23-5-12.
//

#include "xtype-builtin.h"

#include <stdio.h>

#include "xproto.h"
#include "print/print-type.h"
#include "decode/decode_x11.h"


int print_INT8      (const unsigned char *buf);
int print_INT16     (const unsigned char *buf);
int print_INT32     (const unsigned char *buf);
int print_CARD8     (const unsigned char *buf);
int print_CARD16    (const unsigned char *buf);
int print_CARD32    (const unsigned char *buf);
int print_BYTE      (const unsigned char *buf);
int print_CHAR8     (const unsigned char *buf);
int print_STRING16  (const unsigned char *buf);
int print_STR       (const unsigned char *buf);

int print_WINDOW    (const unsigned char *buf);
int print_WINDOWD   (const unsigned char *buf);
int print_WINDOWNR  (const unsigned char *buf);

int print_PIXMAP    (const unsigned char *buf);
int print_PIXMAPNPR (const unsigned char *buf);
int print_PIXMAPC   (const unsigned char *buf);

int print_CURSOR    (const unsigned char *buf);
int print_FONT      (const unsigned char *buf);
int print_GCONTEXT  (const unsigned char *buf);
int print_COLORMAP  (const unsigned char *buf);
int print_COLORMAPC (const unsigned char *buf);
int print_DRAWABLE  (const unsigned char *buf);
int print_FONTABLE  (const unsigned char *buf);
int print_ATOM      (const unsigned char *buf);
int print_ATOMT     (const unsigned char *buf);
int print_VISUALID  (const unsigned char *buf);
int print_VISUALIDC (const unsigned char *buf);
int print_TIMESTAMP (const unsigned char *buf);
int print_RESOURCEID(const unsigned char *buf);
int print_KEYSYM    (const unsigned char *buf);
int print_KEYCODE   (const unsigned char *buf);
int print_KEYCODEA  (const unsigned char *buf);
int print_BUTTON    (const unsigned char *buf);
int print_BUTTONA   (const unsigned char *buf);
int print_EVENTFORM (const unsigned char *buf);


void xtype_builtin_init(void)
{
    (void) define_type(INT8, BUILTIN, "INT8", print_INT8);
    (void) define_type(INT16, BUILTIN, "INT16", print_INT16);
    (void) define_type(INT32, BUILTIN, "INT32", print_INT32);
    (void) define_type(CARD8, BUILTIN, "CARD8", print_CARD8);
    (void) define_type(CARD16, BUILTIN, "CARD16", print_CARD16);
    (void) define_type(CARD32, BUILTIN, "CARD32", print_CARD32);
    (void) define_type(BYTE, BUILTIN, "BYTE", print_BYTE);
    (void) define_type(CHAR8, BUILTIN, "CHAR8", print_CHAR8);
    (void) define_type(STRING16, BUILTIN, "STRING16", print_STRING16);
    (void) define_type(STR, BUILTIN, "STR", print_STR);
    (void) define_type(WINDOW, BUILTIN, "WINDOW", print_WINDOW);
    (void) define_type(WINDOWD, BUILTIN, "WINDOWD", print_WINDOWD);
    (void) define_type(WINDOWNR, BUILTIN, "WINDOWNR", print_WINDOWNR);
    (void) define_type(PIXMAP, BUILTIN, "PIXMAP", print_PIXMAP);
    (void) define_type(PIXMAPNPR, BUILTIN, "PIXMAPNPR", print_PIXMAPNPR);
    (void) define_type(PIXMAPC, BUILTIN, "PIXMAPC", print_PIXMAPC);
    (void) define_type(CURSOR, BUILTIN, "CURSOR", print_CURSOR);
    (void) define_type(FONT, BUILTIN, "FONT", print_FONT);
    (void) define_type(GCONTEXT, BUILTIN, "GCONTEXT", print_GCONTEXT);
    (void) define_type(COLORMAP, BUILTIN, "COLORMAP", print_COLORMAP);
    (void) define_type(COLORMAPC, BUILTIN, "COLORMAPC", print_COLORMAPC);
    (void) define_type(DRAWABLE, BUILTIN, "DRAWABLE", print_DRAWABLE);
    (void) define_type(FONTABLE, BUILTIN, "FONTABLE", print_FONTABLE);
    (void) define_type(ATOM, BUILTIN, "ATOM", print_ATOM);
    (void) define_type(ATOMT, BUILTIN, "ATOMT", print_ATOMT);
    (void) define_type(VISUALID, BUILTIN, "VISUALID", print_VISUALID);
    (void) define_type(VISUALIDC, BUILTIN, "VISUALIDC", print_VISUALIDC);
    (void) define_type(TIMESTAMP, BUILTIN, "TIMESTAMP", print_TIMESTAMP);
    (void) define_type(RESOURCEID, BUILTIN, "RESOURCEID", print_RESOURCEID);
    (void) define_type(KEYSYM, BUILTIN, "KEYSYM", print_KEYSYM);
    (void) define_type(KEYCODE, BUILTIN, "KEYCODE", print_KEYCODE);
    (void) define_type(KEYCODEA, BUILTIN, "KEYCODEA", print_KEYCODEA);
    (void) define_type(BUTTON, BUILTIN, "BUTTON", print_BUTTON);
    (void) define_type(BUTTONA, BUILTIN, "BUTTONA", print_BUTTONA);
    (void) define_type(EVENTFORM, BUILTIN, "EVENTFORM", print_EVENTFORM);
}

int print_INT8(const unsigned char *buf)
{
    /* print a INT8 -- 8-bit signed integer */
    short n = IByte(buf);

    if (n > 127) {
        n = 256 - n;
    }

    fprintf(stdout, "%d", n);

    return 1;
}

int print_INT16(const unsigned char *buf)
{
    /* print a INT16 -- 16-bit signed integer */
    long n = IShort(buf);

    if (n > 32767)
        n = 65536 - n;
    fprintf(stdout, "%ld", n);
    return 2;
}

int print_INT32(const unsigned char *buf)
{
    /* print a INT32 -- 32-bit signed integer */
    long n = ILong(buf);

    fprintf(stdout, "%ld", n);
    return 4;
}

int print_CARD8(const unsigned char *buf)
{
    /* print a CARD8 -- 8-bit unsigned integer */
    unsigned short n = IByte(buf);

    fprintf(stdout, "%02x", (unsigned) (n & 0xff));
    return 1;
}

int print_CARD16(const unsigned char *buf)
{
    /* print a CARD16 -- 16-bit unsigned integer */
    unsigned long n = IShort(buf);

    fprintf(stdout, "%04x", (unsigned) (n & 0xffff));
    return 1;
}

int print_CARD32(const unsigned char *buf)
{
    /* print a CARD32 -- 32-bit unsigned integer */
    unsigned long n = ILong(buf);

    fprintf(stdout, "%08lx", n);
    return (4);
}

int print_BYTE(const unsigned char *buf)
{
    /* print a BYTE -- 8-bit value */
    short n = IByte(buf);

    fprintf(stdout, "%02x", n);
    return (1);
}

int print_CHAR8(const unsigned char *buf)
{
    /* print a CHAR8 -- 8-bit character */
    unsigned short n = IByte(buf);

    fprintf(stdout, "%s", print_rep(n));
    return (1);
}

int print_STRING16(const unsigned char *buf)
{
    /* print a CHAR2B -- 16-bit character which is never byte-swapped */
    unsigned short n = IChar2B(buf);

    fprintf(stdout, "%s", print_rep(n));
    return 2 + n;
}

int print_STR(const unsigned char *buf)
{
    /* STR have the length (1 byte) then a string of CHAR8 */
    short n;

    short i;

    n = IByte(buf++);
    for (i = 0; i < n; i++)
        fprintf(stdout, "%s", print_rep(buf[i]));
    return (n + 1);
}

int print_WINDOW(const unsigned char *buf)
{
    /* print a WINDOW -- CARD32  plus 0 = None */
    long n = ILong(buf);

    if (n == 0)
        fprintf(stdout, "None");
    else
        fprintf(stdout, "WIN %08lx", n);
    return (4);
}

int print_WINDOWD(const unsigned char *buf)
{
    /* print a WINDOWD -- CARD32  plus 0 = PointerWindow, 1 = InputFocus */
    long n = ILong(buf);

    if (n == 0)
        fprintf(stdout, "PointerWindow");
    else if (n == 1)
        fprintf(stdout, "InputFocus");
    else
        (void) print_WINDOW(buf);
    return 4;
}

int print_WINDOWNR(const unsigned char *buf)
{
    /* print a WINDOWNR -- CARD32  plus 0 = None, 1 = PointerRoot */
    long n = ILong(buf);

    if (n == 0)
        fprintf(stdout, "None");
    else if (n == 1)
        fprintf(stdout, "PointerRoot");
    else
        (void) print_WINDOW(buf);
    return 4;
}

int print_PIXMAP(const unsigned char *buf)
{
    /* print a PIXMAP -- CARD32  plus 0 = None */
    long n = ILong(buf);

    if (n == 0)
        fprintf(stdout, "None");
    else
        fprintf(stdout, "PXM %08lx", n);
    return 4;
}

int print_PIXMAPNPR(const unsigned char *buf)
{
    /* print a PIXMAPNPR -- CARD32  plus 0 = None, 1 = ParentRelative */
    long n = ILong(buf);

    if (n == 0)
        fprintf(stdout, "None");
    else if (n == 1)
        fprintf(stdout, "ParentRelative");
    else
        print_PIXMAP(buf);
    return 4;
}

int print_PIXMAPC(const unsigned char *buf)
{
    /* print a PIXMAPC -- CARD32  plus 0 = CopyFromParent */
    long n = ILong(buf);

    if (n == 0)
        fprintf(stdout, "CopyFromParent");
    else
        print_PIXMAP(buf);
    return 4;
}

int print_CURSOR(const unsigned char *buf)
{
    /* print a CURSOR -- CARD32  plus 0 = None */
    long n = ILong(buf);

    if (n == 0)
        fprintf(stdout, "None");
    else
        fprintf(stdout, "CUR %08lx", n);
    return 4;
}

int print_FONT(const unsigned char *buf)
{
    /* print a FONT -- CARD32  plus 0 = None */
    long n = ILong(buf);

    if (n == 0)
        fprintf(stdout, "None");
    else
        fprintf(stdout, "FNT %08lx", n);
    return 4;
}

int print_GCONTEXT(const unsigned char *buf)
{
    /* print a GCONTEXT -- CARD32 */
    long n = ILong(buf);

    fprintf(stdout, "GXC %08lx", n);
    return 4;
}

int print_COLORMAP(const unsigned char *buf)
{
    /* print a COLORMAP -- CARD32 plus 0 = None */
    long n = ILong(buf);

    if (n == 0)
        fprintf(stdout, "None");
    else
        fprintf(stdout, "CMP %08lx", n);
    return (4);
}

int print_COLORMAPC(const unsigned char *buf)
{
    /* print a COLORMAPC -- CARD32 plus 0 = CopyFromParent */
    long n = ILong(buf);

    if (n == 0)
        fprintf(stdout, "CopyFromParent");
    else
        (void) print_COLORMAP(buf);
    return 4;
}

int print_DRAWABLE(const unsigned char *buf)
{
    /* print a DRAWABLE -- CARD32 */
    long n = ILong(buf);

    fprintf(stdout, "DWB %08lx", n);
    return 4;
}

int print_FONTABLE(const unsigned char *buf)
{
    /* print a FONTABLE -- CARD32 */
    long n = ILong(buf);

    fprintf(stdout, "FTB %08lx", n);
    return 4;
}

int print_ATOM(const unsigned char *buf)
{
    /* print a ATOM -- CARD32 plus 0 = None */
    long n = ILong(buf);
    const char *name = find_atom_name (n);

    if (name != NULL) {
        fprintf(stdout, "ATM %08lx <%s>", n, name);
    }
    else {
        fprintf(stdout, "ATM %08lx", n);
    }

    return (4);
}

int print_ATOMT(const unsigned char *buf)
{
    /* print a ATOMT -- CARD32 plus 0 = AnyPropertyType */
    long n = ILong(buf);

    if (n == 0) {
        fprintf(stdout, "AnyPropertyType");
    }
    else {
        (void) print_ATOM(buf);
    }

    return 4;
}

int print_VISUALID(const unsigned char *buf)
{
    /* print a VISUALID -- CARD32 plus 0 = None */
    long n = ILong(buf);

    if (n == 0)
        fprintf(stdout, "None");
    else
        fprintf(stdout, "VIS %08lx", n);
    return 4;
}

int print_VISUALIDC(const unsigned char *buf)
{
    /* print a VISUALIDC -- CARD32 plus 0 = CopyFromParent */
    long n = ILong(buf);

    if (n == 0)
        fprintf(stdout, "CopyFromParent");
    else
        print_VISUALID(buf);
    return 4;
}

int print_TIMESTAMP(const unsigned char *buf)
{
    /* print a TIMESTAMP -- CARD32 plus 0 as the current time */
    long n = ILong(buf);

    if (n == 0)
        fprintf(stdout, "CurrentTime");
    else
        fprintf(stdout, "TIM %08lx", n);
    return 4;
}

int print_RESOURCEID(const unsigned char *buf)
{
    /* print a RESOURCEID -- CARD32 plus 0 = AllTemporary */
    long n = ILong(buf);

    if (n == 0)
        fprintf(stdout, "AllTemporary");
    else
        fprintf(stdout, "RID %08lx", n);
    return 4;
}

int print_KEYSYM(const unsigned char *buf)
{
    /* print a KEYSYM -- CARD32 */
    long n = ILong(buf);

    fprintf(stdout, "KYS %08lx", n);
    return (4);
}

int print_KEYCODE(const unsigned char *buf)
{
    /* print a KEYCODE -- CARD8 */
    unsigned short n = IByte(buf);

    fprintf(stdout, "%d (%s)", n, print_rep(n));
    return (1);
}

int print_KEYCODEA(const unsigned char *buf)
{
    /* print a KEYCODEA -- CARD8 plus 0 = AnyKey */
    long n = IByte(buf);

    if (n == 0)
        fprintf(stdout, "AnyKey");
    else
        (void) print_KEYCODE(buf);
    return 1;
}

int print_BUTTON(const unsigned char *buf)
{
    /* print a BUTTON -- CARD8 */
    unsigned short n = IByte(buf);

    fprintf(stdout, "%d (%s)", n, print_rep(n));
    return 1;
}

int print_BUTTONA(const unsigned char *buf)
{
    /* print a BUTTONA -- CARD8 plus 0 = AnyButton */
    long n = IByte(buf);

    if (n == 0)
        fprintf(stdout, "AnyButton");
    else
        print_BUTTON(buf);
    return 1;
}

int print_EVENTFORM(const unsigned char *buf)
{
    /* print an EVENT_FORM -- event format */
    decode_event(-1, buf, (long) -1);
    return 32;
}

