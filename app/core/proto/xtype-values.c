//
// Created by dingjing on 23-5-17.
//

#include "xtype-values.h"

#include "xtype-common.h"

void xtype_values_init(void)
{
    Type p;

    p = define_type(WINDOW_BITMASK, SET, "WINDOW_BITMASK", (GetProcValueByType) get_str_SET);

    define_values(p, 0x00000001L, 4, PIXMAPNPR, "background-pixmap");
    define_values(p, 0x00000002L, 4, CARD32, "background-pixel");
    define_values(p, 0x00000004L, 4, PIXMAPC, "border-pixmap");
    define_values(p, 0x00000008L, 4, CARD32, "border-pixel");
    define_values(p, 0x00000010L, 1, BITGRAVITY, "bit-gravity");
    define_values(p, 0x00000020L, 1, WINGRAVITY, "win-gravity");
    define_values(p, 0x00000040L, 1, BACKSTORE, "backing-store");
    define_values(p, 0x00000080L, 4, CARD32, "backing-planes");
    define_values(p, 0x00000100L, 4, CARD32, "backing-pixel");
    define_values(p, 0x00000200L, 1, BOOL, "override-redirect");
    define_values(p, 0x00000400L, 1, BOOL, "save-under");
    define_values(p, 0x00000800L, 4, SETofEVENT, "event-mask");
    define_values(p, 0x00001000L, 4, SETofDEVICEEVENT, "do-not-propagate-mask");
    define_values(p, 0x00002000L, 4, COLORMAPC, "colormap");
    define_values(p, 0x00004000L, 4, CURSOR, "cursor");

    p = define_type(CONFIGURE_BITMASK, SET, "CONFIGURE_BITMASK", (GetProcValueByType) get_str_SET);
    define_values(p, 0x0001L, 2, INT16, "x");
    define_values(p, 0x0002L, 2, INT16, "y");
    define_values(p, 0x0004L, 2, CARD16, "width");
    define_values(p, 0x0008L, 2, CARD16, "height");
    define_values(p, 0x0010L, 2, CARD16, "border-width");
    define_values(p, 0x0020L, 4, WINDOW, "sibling");
    define_values(p, 0x0040L, 1, STACKMODE, "stack-mode");

    p = define_type(GC_BITMASK, SET, "GC_BITMASK", (GetProcValueByType) get_str_SET);
    define_values(p, 0x00000001L, 1, GCFUNC, "function");
    define_values(p, 0x00000002L, 4, CARD32, "plane-mask");
    define_values(p, 0x00000004L, 4, CARD32, "foreground");
    define_values(p, 0x00000008L, 4, CARD32, "background");
    define_values(p, 0x00000010L, 2, CARD16, "line-width");
    define_values(p, 0x00000020L, 1, LINESTYLE, "line-style");
    define_values(p, 0x00000040L, 1, CAPSTYLE, "cap-style");
    define_values(p, 0x00000080L, 1, JOINSTYLE, "join-style");
    define_values(p, 0x00000100L, 1, FILLSTYLE, "fill-style");
    define_values(p, 0x00000200L, 1, FILLRULE, "fill-rule");
    define_values(p, 0x00000400L, 4, PIXMAP, "tile");
    define_values(p, 0x00000800L, 4, PIXMAP, "stipple");
    define_values(p, 0x00001000L, 2, INT16, "tile-stipple-x-origin");
    define_values(p, 0x00002000L, 2, INT16, "tile-stipple-y-origin");
    define_values(p, 0x00004000L, 4, FONT, "font");
    define_values(p, 0x00008000L, 1, SUBWINMODE, "subwindow-mode");
    define_values(p, 0x00010000L, 1, BOOL, "graphics-exposures");
    define_values(p, 0x00020000L, 2, INT16, "clip-x-origin");
    define_values(p, 0x00040000L, 2, INT16, "clip-y-origin");
    define_values(p, 0x00080000L, 4, PIXMAP, "clip-mask");
    define_values(p, 0x00100000L, 2, CARD16, "dash-offset");
    define_values(p, 0x00200000L, 1, CARD8, "dashes");
    define_values(p, 0x00400000L, 1, ARCMODE, "arc-mode");

    p = define_type(KEYBOARD_BITMASK, SET, "KEYBOARD_BITMASK", (GetProcValueByType) get_str_SET);
    define_values(p, 0x0001L, 1, INT8, "key-click-percent");
    define_values(p, 0x0002L, 1, INT8, "bell-percent");
    define_values(p, 0x0004L, 2, INT16, "bell-pitch");
    define_values(p, 0x0008L, 2, INT16, "bell-duration");
    define_values(p, 0x0010L, 1, CARD8, "led");
    define_values(p, 0x0020L, 1, OFF_ON, "led-mode");
    define_values(p, 0x0040L, 1, KEYCODE, "key");
    define_values(p, 0x0080L, 1, OFF_ON, "auto-repeat-mode");
}
