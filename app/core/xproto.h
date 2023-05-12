//
// Created by dingjing on 23-5-12.
//

#ifndef XSCOPE_XPROTO_H
#define XSCOPE_XPROTO_H
#include <glib.h>
#include <stdbool.h>
#include <inttypes.h>

#include "global.h"


/* Built-in Types */
#define BYTE 1                  /* 8-bit value */
#define INT8 2                  /* 8-bit signed integer */
#define INT16 3                 /* 16-bit signed integer */
#define INT32 4                 /* 32-bit signed integer */
#define CARD8 5                 /* 8-bit unsigned integer */
#define CARD16 6                /* 16-bit unsigned integer */
#define CARD32 7                /* 32-bit unsigned integer */
#define STRING8 8               /* List of CARD8 */
#define STRING16 9              /* List of CHAR2B */
#define TEXTITEM8 10            /* STRING8 or Font shift */
#define TEXTITEM16 11           /* STRING16 or Font shift */

#define WINDOW 12               /* CARD32  plus 0 = None */
#define WINDOWD 13              /* CARD32  plus 0 = PointerWindow, 1 = InputFocus */
#define WINDOWNR 14             /* CARD32  plus 0 = None, 1 = PointerRoot */

#define PIXMAP 15               /* CARD32  plus 0 = None */
#define PIXMAPNPR 16            /* CARD32  plus 0 = None, 1 = ParentRelative */
#define PIXMAPC 17              /* CARD32  plus 0 = CopyFromParent */

#define CURSOR 18               /* CARD32  plus 0 = None */

#define FONT 19                 /* CARD32  plus 0 = None */

#define GCONTEXT 20             /* CARD32 */

#define COLORMAP 21             /* CARD32 plus 0 = None */
#define COLORMAPC 22            /* CARD32 plus 0 = CopyFromParent */

#define DRAWABLE 23             /* CARD32 */
#define FONTABLE 24             /* CARD32 */

#define ATOM 25                 /* CARD32 plus 0 = None */
#define ATOMT 26                /* CARD32 plus 0 = AnyPropertyType */

#define VISUALID 27             /* CARD32 plus 0 = None */
#define VISUALIDC 28            /* CARD32 plus 0 = CopyFromParent */

#define TIMESTAMP 29            /* CARD32 plus 0 as the current time */

#define RESOURCEID 30           /* CARD32 plus 0 = AllTemporary */

#define KEYSYM 31               /* CARD32 */
#define KEYCODE 32              /* CARD8 */
#define KEYCODEA 33             /* CARD8 plus 0 = AnyKey */

#define BUTTON 34               /* CARD8 */
#define BUTTONA 35              /* CARD8 plus 0 = AnyButton */

#define EVENTFORM 36            /* event format */
#define CHAR8 37                /* CARD8 interpreted as a character */
#define STR 38                  /* String of CHAR8 with preceding length */



/* Defined types */

#define BITGRAVITY	 40
#define WINGRAVITY	 41
#define BOOL		 42
#define HOSTFAMILY	 43
#define PK_MODE		 44
#define NO_YES		 45
#define WINDOWCLASS	 46
#define BACKSTORE	 47
#define MAPSTATE	 48
#define STACKMODE	 49
#define CIRMODE	 	 50
#define CHANGEMODE	 51
#define GRABSTAT	 52
#define EVENTMODE	 53
#define FOCUSAGENT	 54
#define DIRECT		 55
#define GCFUNC		 56
#define LINESTYLE	 57
#define CAPSTYLE	 58
#define JOINSTYLE	 59
#define FILLSTYLE	 60
#define FILLRULE	 61
#define SUBWINMODE	 62
#define ARCMODE	 	 63
#define RECTORDER	 64
#define COORMODE	 65
#define POLYSHAPE	 66
#define IMAGEMODE	 67
#define ALLORNONE	 68
#define OBJECTCLASS	 69
#define OFF_ON		 70
#define INS_DEL	 	 71
#define DIS_EN		 72
#define CLOSEMODE	 73
#define SAVEMODE	 74
#define RSTATUS	 	 75
#define MOTIONDETAIL	 76
#define ENTERDETAIL	 77
#define BUTTONMODE	 78
#define SCREENFOCUS	 79
#define VISIBLE	 	 80
#define CIRSTAT	 	 81
#define PROPCHANGE	 82
#define CMAPCHANGE	 83
#define MAPOBJECT	 84
#define SETofEVENT	 85
#define SETofPOINTEREVENT	 86
#define SETofDEVICEEVENT	 87
#define SETofKEYBUTMASK	 	 88
#define SETofKEYMASK		 89
#define WINDOW_BITMASK		 90
#define CONFIGURE_BITMASK	 91
#define GC_BITMASK		 92
#define KEYBOARD_BITMASK	 93
#define COLORMASK		 94
#define CHAR2B		 95
#define POINT		 96
#define RECTANGLE	 97
#define ARC		 98
#define HOST		 99
#define TIMECOORD	100
#define FONTPROP	101
#define CHARINFO	102
#define SEGMENT		103
#define COLORITEM	104
#define RGB		105
#define BYTEMODE	110
#define BYTEORDER	111
#define COLORCLASS	112
#define FORMAT		113
#define SCREEN		114
#define DEPTH		115
#define VISUALTYPE	116

#define REQUEST		117
#define REPLY		118
#define ERROR		119
#define EVENT		120

#define LBXREQUEST	121
#define LBXREPLY	122
#define LBXEVENT	123
#define LBXERROR	124

#define NASREQUEST	125
#define NASREPLY	126
#define NASEVENT	127
#define NASERROR	128

#define WCPREQUEST	129
#define WCPREPLY	130
#define WCPERROR	131

#define RENDERREQUEST	132
#define RENDERREPLY	133
#define RENDERERROR	134

#define PICTURE		135
#define PICTFORMAT	136
#define PICTURE_BITMASK	137
#define PICTOP		138
#define GLYPHSET	139
#define RENDERCOLOR	140
#define PICTFORMINFO    141
#define TRAPEZOID      	142
#define TRIANGLE	143
#define POINTFIXED	144
#define FIXED		145
#define FILTERALIAS	146
#define RENDERTRANSFORM 147
#define SUBPIXEL	148

#define RANDRREQUEST	150
#define RANDRREPLY	151
#define RANDRERROR	152

#define MITSHMREQUEST	153
#define MITSHMREPLY	154
#define MITSHMEVENT	155
#define MITSHMERROR	156

#define BIGREQREQUEST	157
#define BIGREQREPLY	158

#define EXTENSION	159

#define GLXREQUEST	160
#define GLXREPLY	161
#define GLXEVENT	162
#define GLXERROR	163

/* More RandR */
#define SETofRREVENT	164
#define SETofROTATION	165
#define SCREENSIZE	166
#define REFRESH		167
#define SETofMODEFLAG	168
#define MODEINFO	169
#define MODE		170	/* XID/CARD32 plus 0 = None */
#define CRTC		171	/* XID/CARD32 plus 0 = None */
#define OUTPUT		172	/* XID/CARD32 plus 0 = None */
#define RANDREVENT      173     /* minor event code for RandR event base+1 */
#define CONNECTION	174
#define SETofPROVIDER_CAPS 175
#define MaxTypes 256


#define GC_function		                    0x00000001L
#define GC_plane_mask		                0x00000002L
#define GC_foreground		                0x00000004L
#define GC_background		                0x00000008L
#define GC_line_width		                0x00000010L
#define GC_line_style		                0x00000020L
#define GC_cap_style		                0x00000040L
#define GC_join_style		                0x00000080L
#define GC_fill_style		                0x00000100L
#define GC_fill_rule		                0x00000200L
#define GC_tile			                    0x00000400L
#define GC_stipple		                    0x00000800L
#define GC_tile_stipple_x_origin            0x00001000L
#define GC_tile_stipple_y_origin            0x00002000L
#define GC_font			                    0x00004000L
#define GC_subwindow_mode	                0x00008000L
#define GC_graphics_exposures               0x00010000L
#define GC_clip_x_origin	                0x00020000L
#define GC_clip_y_origin	                0x00040000L
#define GC_clip_mask		                0x00080000L
#define GC_dash_offset		                0x00100000L
#define GC_dashes		                    0x00200000L
#define GC_arc_mode		                    0x00400000L


/* Types of Types */
#define BUILTIN         1
#define ENUMERATED      2
#define SET             3
#define RECORD          5




typedef struct TypeDef              TypeDef;
typedef struct ValueListEntry       ValueListEntry;
typedef struct TypeDef*             Type;
typedef struct ConnState            ConnState;


typedef int (*PrintProcType) (const unsigned char *);

struct ValueListEntry
{
    struct ValueListEntry*  next;
    const char*             name;
    short                   type;
    short                   length;
    long                    value;
};


struct TypeDef
{
    const char*             name;
    short                   type;               // BUILTIN, ENUMERATED, SET, or RECORD
    struct ValueListEntry*  valueList;
    PrintProcType           printProc;
};

struct ConnState
{
    unsigned char*          savedBytes;
    int                     littleEndian;
    int                     bigReqEnabled;
    long                    requestLen;
    long                    sizeOfSavedBytes;
    long                    numberOfSavedBytes;

    long                    numberOfBytesNeeded;
    long                    numberOfBytesProcessed;
    long (*byteProcessing)  (int fd, const unsigned char *buf, long n);

    long                    sequenceNumber;
};



static inline long pad(long n)
{
    /* round up to next multiple of 4 */
    return ((n + 3) & ~0x3);
}

static inline uint32_t ILong(const unsigned char buf[])
{
    /* check for byte-swapping */
    if (gLittleEndian) {
        return ((buf[3] << 24) | (buf[2] << 16) | (buf[1] << 8) | buf[0]);
    }

    return ((buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf[3]);
}

static inline uint16_t IShort(const unsigned char buf[])
{
    /* check for byte-swapping */
    if (gLittleEndian) {
        return (buf[1] << 8) | buf[0];
    }

    return ((buf[0] << 8) | buf[1]);
}

static inline uint16_t IChar2B(const unsigned char buf[])
{
    /* CHAR2B is like an IShort, but not byte-swapped */
    return ((buf[0] << 8) | buf[1]);
}

static inline uint8_t IByte(const unsigned char buf[])
{
    return (buf[0]);
}

static inline bool IBool(const unsigned char buf[])
{
    if (buf[0] != 0) {
        return (true);
    }
    else {
        return (false);
    }
}





void xproto_init ();
void xproto_print (const guchar* buf, gsize len);



Type define_type(short typeID, short class, const char *name, int (*printProc) (const unsigned char *));


#endif //XSCOPE_XPROTO_H
