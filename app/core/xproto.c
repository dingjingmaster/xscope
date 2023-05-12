//
// Created by dingjing on 23-5-12.
//

#include "xproto.h"

#include <stdio.h>

#include "core-log.h"
#include "xtype-builtin.h"


unsigned char   gRBf[2];
unsigned char   gSBf[4];
ConnState*      gCS = NULL;
TypeDef         gTD[MaxTypes];


Type define_type(short typeid, short class, const char *name, int (*printProc) (const unsigned char*))
{
    gTD[typeid].name = name;
    gTD[typeid].type = class;
    gTD[typeid].valueList = NULL;
    gTD[typeid].printProc = printProc;

    return (&gTD[typeid]);
}

void xproto_init()
{
    // init built in types
    xtype_builtin_init();

}
//
//static void defineValues(TYPE type, long value, short length, short ctype, const char *name)
//{
//    struct ValueListEntry *p;
//
//    p = malloc(sizeof(struct ValueListEntry));
//    if (p == NULL) {
//        panic("Can't allocate memory for ValueListEntry");
//    }
//    p->name = name;
//    p->type = ctype;
//    p->length = length;
//    p->value = value;
//
//    /* add an new value to the list. */
//    if (type->valueList == NULL || type->valueList->value > p->value) {
//        p->next = type->valueList;
//        type->valueList = p;
//    }
//    else {
//        /* keep the list sorted, smallest to largest  */
//        struct ValueListEntry *q = type->valueList;
//
//        while (q->next != NULL && q->next->value < p->value) {
//            q = q->next;
//        }
//        p->next = q->next;
//        q->next = p;
//    }
//}
//
//
//static void defineEValue(TYPE type, long value, const char *name)
//{
//    struct ValueListEntry *p;
//
//    /* define the new value */
//    p = malloc(sizeof(struct ValueListEntry));
//    if (p == NULL) {
//        panic("Can't allocate memory for Enum ValueListEntry");
//    }
//
//    p->name = name;
//    p->value = value;
//
//    /* add an new value to the list. */
//    if (type->valueList == NULL || type->valueList->value > p->value) {
//        p->next = type->valueList;
//        type->valueList = p;
//    }
//    else {
//        /* keep the list sorted, smallest to largest */
//        struct ValueListEntry *q = type->valueList;
//
//        while (q->next != NULL && q->next->value < p->value) {
//            q = q->next;
//        }
//        p->next = q->next;
//        q->next = p;
//    }
//}
//
//void xproto_buffer(const guchar *buf, gsize len)
//{
//
//}
//
//
//
//static int printCHAR2B(const unsigned char *buf)
//{
//    printField(buf, 0, 1, CARD8, "byte1");
//    printField(buf, 1, 1, CARD8, "byte2");
//
//    return (2);
//}
//
//static int printPOINT(const unsigned char *buf)
//{
//    printField(buf, 0, 2, INT16, "x");
//    printField(buf, 2, 2, INT16, "y");
//
//    return (4);
//}
//
//static int
//printRECTANGLE(const unsigned char *buf)
//{
//    printField(buf, 0, 2, INT16, "x");
//    printField(buf, 2, 2, INT16, "y");
//    printField(buf, 4, 2, CARD16, "width");
//    printField(buf, 6, 2, CARD16, "height");
//    return (8);
//}
//
//static int
//printARC(const unsigned char *buf)
//{
//    printField(buf, 0, 2, INT16, "x");
//    printField(buf, 2, 2, INT16, "y");
//    printField(buf, 4, 2, CARD16, "width");
//    printField(buf, 6, 2, CARD16, "height");
//    printField(buf, 8, 2, INT16, "angle1");
//    printField(buf, 10, 2, INT16, "angle2");
//    return (12);
//}
//
//static int
//printHOST(const unsigned char *buf)
//{
//    short n;
//
//    printField(buf, 0, 1, HOSTFAMILY, "family");
//    printField(buf, 2, 2, DVALUE2(n), "length of address");
//    n = IShort(&buf[2]);
//    switch (buf[0]) {
//        case 0:
//        {
//            struct in_addr ia;
//            char *addr;
//
//            memcpy(&ia, &buf[4], sizeof(ia));       /* Need to get alignment right */
//            addr = inet_ntoa(ia);
//            printString8((unsigned char *) addr, strlen(addr), "address");
//            break;
//        }
//#ifdef IPv6
//            case 6:
//    {
//        struct in6_addr i6a;
//        char addr[INET6_ADDRSTRLEN];
//
//        memcpy(&i6a, &buf[4], sizeof(i6a));     /* Need to get alignment right */
//        inet_ntop(AF_INET6, &i6a, addr, sizeof(addr));
//        printString8((unsigned char *) addr, strlen(addr), "address");
//        break;
//    }
//#endif
//
//        case 5:                    /* ServerInterpreted */
//        {
//            int i;
//
//            for (i = 0; buf[i + 4] != 0; i++) {
//                /* empty loop */
//            }
//            printString8(&buf[4], i, "type");
//            printString8(&buf[i + 5], n - i - 1, "value");
//            break;
//        }
//
//        case 254:
//            printString8(&buf[4], n, "address");
//            break;
//
//        default:
//            printList(&buf[4], (long) n, BYTE, "address");
//    }
//    return (pad((long) (4 + n)));
//}
//
//static int
//printTIMECOORD(const unsigned char *buf)
//{
//    printField(buf, 0, 4, TIMESTAMP, "time");
//    printField(buf, 4, 2, CARD16, "x");
//    printField(buf, 6, 2, CARD16, "y");
//    return (8);
//}
//
//static int
//printFONTPROP(const unsigned char *buf)
//{
//    printField(buf, 0, 4, ATOM, "name");
//    printField(buf, 4, 4, INT32, "value");
//    return (8);
//}
//
//static int
//printCHARINFO(const unsigned char *buf)
//{
//    printField(buf, 0, 2, INT16, "left-side-bearing");
//    printField(buf, 2, 2, INT16, "right-side-bearing");
//    printField(buf, 4, 2, INT16, "character-width");
//    printField(buf, 6, 2, INT16, "ascent");
//    printField(buf, 8, 2, INT16, "descent");
//    printField(buf, 10, 2, CARD16, "attributes");
//    return (12);
//}
//
//static int
//printSEGMENT(const unsigned char *buf)
//{
//    printField(buf, 0, 2, INT16, "x1");
//    printField(buf, 2, 2, INT16, "y1");
//    printField(buf, 4, 2, INT16, "x2");
//    printField(buf, 6, 2, INT16, "y2");
//    return (8);
//}
//
//static int printCOLORITEM(const unsigned char *buf)
//{
//    printField(buf, 0, 4, CARD32, "pixel");
//    printField(buf, 4, 2, CARD16, "red");
//    printField(buf, 6, 2, CARD16, "green");
//    printField(buf, 8, 2, CARD16, "blue");
//    printField(buf, 10, 1, COLORMASK, "component selector");
//    return (12);
//}
//
//static int
//printRGB(const unsigned char *buf)
//{
//    printField(buf, 0, 2, CARD16, "red");
//    printField(buf, 2, 2, CARD16, "green");
//    printField(buf, 4, 2, CARD16, "blue");
//    return (8);
//}
//
//static int
//printFORMAT(const unsigned char *buf)
//{
//    printField(buf, 0, 1, CARD8, "depth");
//    printField(buf, 1, 1, CARD8, "bits-per-pixel");
//    printField(buf, 2, 1, CARD8, "scanline-pad");
//    return (8);
//}
//
//static int
//printSCREEN(const unsigned char *buf)
//{
//    short n; /* number of elements in List of DEPTH */
//    long m; /* length (in bytes) of List of DEPTH */
//
//    printField(buf, 0, 4, WINDOW, "root");
//    printField(buf, 4, 4, COLORMAP, "default-colormap");
//    printField(buf, 8, 4, CARD32, "white-pixel");
//    printField(buf, 12, 4, CARD32, "black-pixel");
//    printField(buf, 16, 4, SETofEVENT, "current-input-masks");
//    printField(buf, 20, 2, CARD16, "width-in-pixels");
//    printField(buf, 22, 2, CARD16, "height-in-pixels");
//    printField(buf, 24, 2, CARD16, "width-in-millimeters");
//    printField(buf, 26, 2, CARD16, "height-in-millimeters");
//    printField(buf, 28, 2, CARD16, "min-installed-maps");
//    printField(buf, 30, 2, CARD16, "max-installed-maps");
//    printField(buf, 32, 4, VISUALID, "root-visual");
//    printField(buf, 36, 1, BACKSTORE, "backing-stores");
//    printField(buf, 37, 1, BOOL, "save-unders");
//    printField(buf, 38, 1, CARD8, "root-depth");
//    printField(buf, 39, 1, CARD8, "number of allowed-depths");
//    n = IByte(&buf[39]);
//    m = printList(&buf[40], (long) n, DEPTH, "allowed-depths");
//    return (40 + m);
//}
//
//static int
//printDEPTH(const unsigned char *buf)
//{
//    short n; /* number of elements in List of VISUALTYPE */
//    short m; /* length (in bytes) of List of VISUALTYPE */
//
//    printField(buf, 0, 1, CARD8, "depth");
//    printField(buf, 2, 2, DVALUE2(n), "number of visuals");
//    n = IShort(&buf[2]);
//    m = printList(&buf[8], (long) n, VISUALTYPE, "visuals");
//    return (8 + m);
//}
//
//static int
//printVISUALTYPE(const unsigned char *buf)
//{
//    printField(buf, 0, 4, VISUALID, "visual-id");
//    printField(buf, 4, 1, COLORCLASS, "class");
//    printField(buf, 5, 1, CARD8, "bits-per-rgb-value");
//    printField(buf, 6, 2, CARD16, "colormap-entries");
//    printField(buf, 8, 4, CARD32, "red-mask");
//    printField(buf, 12, 4, CARD32, "green-mask");
//    printField(buf, 16, 4, CARD32, "blue-mask");
//    return (24);
//}
//
//static void printField(const unsigned char *buf, short start, short length, short FieldType, const char *name)
//{
//    if (length == 0)
//        return;
//
//    fprintf(stdout, "%s%20s: ", Leader, name);
//
//    DumpHexBuffer(&(buf[start]), (long) length);
//
//    switch (TD[FieldType].type) {
//        case BUILTIN:
//            (*TD[FieldType].printProc) (&buf[start]);
//            break;
//
//        case ENUMERATED:
//            printENUMERATED(&buf[start], length, TD[FieldType].valueList);
//            break;
//
//        case SET:
//            printSET(&buf[start], length, TD[FieldType].valueList);
//            break;
//
//        case RECORD:
//            modifyIndentLevel(1);
//            fprintf(stdout, "\n");
//            (*TD[FieldType].printProc) (&buf[start]);
//            modifyIndentLevel(-1);
//            break;
//    }
//    fprintf(stdout, "\n");
//    fflush(stdout);
//}
//
//static long printList(const unsigned char *buf, long number, short ListType, const char *name)
//{
//    long n;
//    long i;
//    long sum;
//
//    if (number == 0)
//        return (0);
//
//    fprintf(stdout, "%s%20s: (%ld)\n", Leader, name, number);
//
//    modifyIndentLevel(1);
//    sum = 0;
//    for (i = 0; i < number; i++) {
//        switch (TD[ListType].type) {
//            case BUILTIN:
//                n = (*TD[ListType].printProc) (buf);
//                break;
//            case RECORD:
//                n = (*TD[ListType].printProc) (buf);
//                break;
//            default:
//                fprintf(stdout, "**INVALID**");
//                n = 0;
//                break;
//        }
//        buf = buf + n;
//        sum = sum + n;
//        fprintf(stdout, "%s---\n", Leader);
//    }
//
//    modifyIndentLevel(-1);
//
//    return (sum);
//}
//
//static long printListSTR(const unsigned char *buf, long number, const char *name)
//{
//    long n;
//    long i;
//    long sum;
//
//    if (number == 0)
//        return (0);
//
//    fprintf(stdout, "%s%20s: (%ld)\n", Leader, name, number);
//
//    modifyIndentLevel(1);
//    sum = 0;
//    for (i = 0; i < number; i++) {
//        fprintf(stdout, "%s", Leader);
//        n = printSTR(buf);
//        buf = buf + n;
//        sum = sum + n;
//        fprintf(stdout, "\n");
//    }
//
//    modifyIndentLevel(-1);
//
//    return (sum);
//}
//
//
//static int printBytes(const unsigned char *buf, long number, const char *name)
//{
//    /* print a list of BYTE -- 8-bit character */
//    long i;
//    short column;
//
//    if (number == 0)
//        return (0);
//
//    fprintf(stdout, "%s%20s: ", Leader, name);
//    column = SizeofLeader() + 25;
//    for (i = 0; i < number; i++) {
//        if (column > 80) {
//            fprintf(stdout, "\n%s%20s: ", Leader, "");
//            column = SizeofLeader() + 25;
//        }
//        fprintf(stdout, "%02x ", ((unsigned int) buf[i]));
//        column += 3;
//    }
//    fprintf(stdout, "\n");
//
//    return (number);
//}
//
//static int printString8(const unsigned char *buf, int number, const char *name)
//{
//    short i;
//
//    if (number == 0)
//        return (0);
//
//    fprintf(stdout, "%s%20s: \"", Leader, name);
//    for (i = 0; i < number; i++)
//        fprintf(stdout, "%s", printrep(buf[i]));
//    fprintf(stdout, "\"\n");
//
//    return (number);
//}
//
//static int printString16(const unsigned char *buf, int number, const char *name)
//{
//    long i;
//    unsigned short c;
//
//    if (number == 0)
//        return (0);
//
//    fprintf(stdout, "%s%20s: \"", Leader, name);
//    for (i = 0; i < number * 2; i += 2) {
//        c = IChar2B(&buf[i]);
//        fprintf(stdout, "%s", printrep(c));
//    }
//    fprintf(stdout, "\"\n");
//
//    return (number);
//}
//
//static void printTString8(const unsigned char *buf, long number, const char *name)
//{
//    long i;
//    int off;
//
//    if (number == 0)
//        return;
//
//    off = 0;
//    if (TranslateText)
//        off = 0x20;
//    fprintf(stdout, "%s%20s: \"", Leader, name);
//    for (i = 0; i < number; i++)
//        fprintf(stdout, "%s", printrep(buf[i] + off));
//    fprintf(stdout, "\"\n");
//}
//
//static void printTString16(const unsigned char *buf, long number, const char *name)
//{
//    long i;
//    unsigned short c;
//    int off;
//
//    if (number == 0)
//        return;
//
//    off = 0;
//    if (TranslateText)
//        off = 0x20;
//    fprintf(stdout, "%s%20s: \"", Leader, name);
//    for (i = 0; i < number * 2; i += 2) {
//        c = IChar2B(&buf[i]);
//        fprintf(stdout, "%s", printrep(c + off));
//    }
//    fprintf(stdout, "\"\n");
//}
//
//
//static void printValues(const unsigned char *control, int clength, int ctype, const unsigned char *values, const char *name)
//{
//    long cmask;
//    struct ValueListEntry *p;
//
//    /* first get the control mask */
//    if (clength == 1)
//        cmask = IByte(control);
//    else if (clength == 2)
//        cmask = IShort(control);
//    else
//        cmask = ILong(control);
//
//    /* now if it is zero, ignore and return */
//    if (cmask == 0)
//        return;
//
//    /* there are bits in the controlling bitmask, figure out which */
//    /* the ctype is a set type, so this code is similar to PrintSET */
//    fprintf(stdout, "%s%20s:\n", Leader, name);
//    ModifyIndentLevel(1);
//    for (p = TD[ctype].ValueList; p != NULL; p = p->Next) {
//        if ((p->Value & cmask) != 0) {
//            short m;
//
//            if (littleEndian)
//                m = 0;
//            else
//                m = 4 - p->Length;
//            PrintField(values, m, p->Length, p->Type, p->Name);
//            values += 4;
//        }
//    }
//    ModifyIndentLevel(-1);
//}
//
//
//static void printTextList8(const unsigned char *buf, int length, const char *name)
//{
//    short n;
//
//    fprintf(stdout, "%s%20s:\n", Leader, name);
//    while (length > 1) {
//        n = IByte(&buf[0]);
//        if (n != 255) {
//            PrintField(buf, 1, 1, INT8, "delta");
//            PrintTString8(&buf[2], (long) n, "text item 8 string");
//            buf += n + 2;
//            length -= n + 2;
//        }
//        else {
//            PrintField(buf, 1, 4, FONT, "font-shift-id");
//            buf += 4;
//            length -= 4;
//        }
//    }
//}
//
//
//static void printTextList16(const unsigned char *buf, int length, const char *name)
//{
//    short n;
//
//    fprintf(stdout, "%s%20s:\n", Leader, name);
//    while (length > 1) {
//        n = IByte(&buf[0]);
//        if (n != 255) {
//            printField(buf, 1, 1, INT8, "delta");
//            printTString16(&buf[2], (long) n, "text item 16 string");
//            buf += n + 2;
//            length -= n + 2;
//        }
//        else {
//            printField(buf, 1, 4, FONT, "font-shift-id");
//            buf += 4;
//            length -= 4;
//        }
//    }
//}
//
//static int printPropertyValues(const unsigned char *buf, uint32_t type /* atom */, uint8_t unit, uint32_t num, const char *name)
//{
//    short fieldType = 0;
//
//    switch (type) {
//        case 4: /* XA_ATOM */
//            fieldType = ATOM;
//            break;
//        case 6: /* XA_CARDINAL */
//            switch (unit) {
//                case 4: fieldType = CARD32; break;
//                case 2: fieldType = CARD16; break;
//                case 1: fieldType = CARD8;  break;
//                default:
//                    goto rawbytes;
//            }
//            break;
//        case 19: /* XA_INTEGER */
//            switch (unit) {
//                case 4: fieldType = INT32; break;
//                case 2: fieldType = INT16; break;
//                case 1: fieldType = INT8;  break;
//                default:
//                    goto rawbytes;
//            }
//            break;
//        case 31: /* XA_STRING */
//            return PrintString8(buf, num * unit, name);
//        case 33: /* XA_WINDOW */
//            fieldType = WINDOW;
//            break;
//        default:
//            /* Fall through to check for known non-builtin types below */
//            break;
//    }
//
//    if (fieldType != 0) {
//        if (num == 1) {
//            printField(buf, 0, unit, fieldType, name);
//            return unit;
//        }
//        else
//            return printList(buf, num, fieldType, name);
//    }
//    else {
//        const char *typename = FindAtomName(type);
//
//        if (typename) {
//            if (strcmp(typename, "UTF8_STRING") == 0) {
//                if (IsUTF8locale)
//                    return PrintString8(buf, num * unit, name);
//                else
//                    goto rawbytes;
//            }
//        }
//    }
//
//rawbytes:
//    /* When all else fails, print raw bytes */
//    return PrintBytes(buf, num * unit, name);
//}
//
//
//#define MAXline 78
//
//static void dumpHexBuffer(const unsigned char *buf, long n)
//{
//    long i;
//    short column;
//    char h[6]; /* one hex or octal character */
//
//    column = 27 + SizeofLeader();
//    for (i = 0; i < n; i++) {
//        /* get the hex representations */
//        snprintf(h, sizeof(h), "%02x", (0xff & buf[i]));
//
//        /* check if these characters will fit on this line */
//        if ((column + strlen(h) + 1) > MAXline) {
//            /* line will be too long -- print it */
//            fprintf(stdout, "\n");
//            column = 0;
//        }
//        fprintf(stdout, "%s ", h);
//        column += 3;
//    }
//}
//
//static void printValueRec(uint32_t key, uint32_t cmask, short ctype)
//{
//    unsigned char *values;
//    struct ValueListEntry *p;
//    ValuePtr value;
//
//    value = GetValueRec(key);
//    if (!value)
//        return;
//    values = (unsigned char *) value->values;
//
//    /* now if it is zero, ignore and return */
//    if (cmask == 0)
//        return;
//
//    /* there are bits in the controlling bitmask, figure out which */
//    /* the ctype is a set type, so this code is similar to PrintSET */
//    ModifyIndentLevel(1);
//    for (p = TD[ctype].ValueList; p != NULL; p = p->Next) {
//        if ((p->Value & cmask) != 0) {
//            short m;
//
//            if (littleEndian)
//                m = 0;
//            else
//                m = 4 - p->Length;
//            PrintField(values, m, p->Length, p->Type, p->Name);
//        }
//        values += 4;
//    }
//    ModifyIndentLevel(-1);
//}
