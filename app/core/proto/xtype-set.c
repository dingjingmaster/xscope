//
// Created by dingjing on 23-5-17.
//

#include "xtype-set.h"

#include "xtype-common.h"

void xtype_set_init(void)
{
    Type p = define_type(SETofEVENT, SET, "SETofEVENT", (GetProcValueByType) get_str_SET);

    define_evalue(p, 0x00000001L, "KeyPress");
    define_evalue(p, 0x00000002L, "KeyRelease");
    define_evalue(p, 0x00000004L, "ButtonPress");
    define_evalue(p, 0x00000008L, "ButtonRelease");
    define_evalue(p, 0x00000010L, "EnterWindow");
    define_evalue(p, 0x00000020L, "LeaveWindow");
    define_evalue(p, 0x00000040L, "PointerMotion");
    define_evalue(p, 0x00000080L, "PointerMotionHint");
    define_evalue(p, 0x00000100L, "Button1Motion");
    define_evalue(p, 0x00000200L, "Button2Motion");
    define_evalue(p, 0x00000400L, "Button3Motion");
    define_evalue(p, 0x00000800L, "Button4Motion");
    define_evalue(p, 0x00001000L, "Button5Motion");
    define_evalue(p, 0x00002000L, "ButtonMotion");
    define_evalue(p, 0x00004000L, "KeymapState");
    define_evalue(p, 0x00008000L, "Exposure");
    define_evalue(p, 0x00010000L, "VisibilityChange");
    define_evalue(p, 0x00020000L, "StructureNotify");
    define_evalue(p, 0x00040000L, "ResizeRedirect");
    define_evalue(p, 0x00080000L, "SubstructureNotify");
    define_evalue(p, 0x00100000L, "SubstructureRedirect");
    define_evalue(p, 0x00200000L, "FocusChange");
    define_evalue(p, 0x00400000L, "PropertyChange");
    define_evalue(p, 0x00800000L, "ColormapChange");
    define_evalue(p, 0x01000000L, "OwnerGrabButton");

    p = define_type(SETofPOINTEREVENT, SET, "SETofPOINTEREVENT", (GetProcValueByType) get_str_SET);
    define_evalue(p, 0x00000004L, "ButtonPress");
    define_evalue(p, 0x00000008L, "ButtonRelease");
    define_evalue(p, 0x00000010L, "EnterWindow");
    define_evalue(p, 0x00000020L, "LeaveWindow");
    define_evalue(p, 0x00000040L, "PointerMotion");
    define_evalue(p, 0x00000080L, "PointerMotionHint");
    define_evalue(p, 0x00000100L, "Button1Motion");
    define_evalue(p, 0x00000200L, "Button2Motion");
    define_evalue(p, 0x00000400L, "Button3Motion");
    define_evalue(p, 0x00000800L, "Button4Motion");
    define_evalue(p, 0x00001000L, "Button5Motion");
    define_evalue(p, 0x00002000L, "ButtonMotion");
    define_evalue(p, 0x00004000L, "KeymapState");

    p = define_type(SETofDEVICEEVENT, SET, "SETofDEVICEEVENT", (GetProcValueByType) get_str_SET);
    define_evalue(p, 0x00000001L, "KeyPress");
    define_evalue(p, 0x00000002L, "KeyRelease");
    define_evalue(p, 0x00000004L, "ButtonPress");
    define_evalue(p, 0x00000008L, "ButtonRelease");
    define_evalue(p, 0x00000040L, "PointerMotion");
    define_evalue(p, 0x00000100L, "Button1Motion");
    define_evalue(p, 0x00000200L, "Button2Motion");
    define_evalue(p, 0x00000400L, "Button3Motion");
    define_evalue(p, 0x00000800L, "Button4Motion");
    define_evalue(p, 0x00001000L, "Button5Motion");
    define_evalue(p, 0x00002000L, "ButtonMotion");

    p = define_type(SETofKEYBUTMASK, SET, "SETofKEYBUTMASK", (GetProcValueByType) get_str_SET);
    define_evalue(p, 0x0001L, "Shift");
    define_evalue(p, 0x0002L, "Lock");
    define_evalue(p, 0x0004L, "Control");
    define_evalue(p, 0x0008L, "Mod1");
    define_evalue(p, 0x0010L, "Mod2");
    define_evalue(p, 0x0020L, "Mod3");
    define_evalue(p, 0x0040L, "Mod4");
    define_evalue(p, 0x0080L, "Mod5");
    define_evalue(p, 0x0100L, "Button1");
    define_evalue(p, 0x0200L, "Button2");
    define_evalue(p, 0x0400L, "Button3");
    define_evalue(p, 0x0800L, "Button4");
    define_evalue(p, 0x1000L, "Button5");

    p = define_type(SETofKEYMASK, SET, "SETofKEYMASK", (GetProcValueByType) get_str_SET);
    define_evalue(p, 0x0001L, "Shift");
    define_evalue(p, 0x0002L, "Lock");
    define_evalue(p, 0x0004L, "Control");
    define_evalue(p, 0x0008L, "Mod1");
    define_evalue(p, 0x0010L, "Mod2");
    define_evalue(p, 0x0020L, "Mod3");
    define_evalue(p, 0x0040L, "Mod4");
    define_evalue(p, 0x0080L, "Mod5");
    define_evalue(p, 0x8000L, "AnyModifier");

    p = define_type(COLORMASK, SET, "COLORMASK", (GetProcValueByType) get_str_SET);
    define_evalue(p, 0x01L, "do-red");
    define_evalue(p, 0x02L, "do-green");
    define_evalue(p, 0x04L, "do-blue");

    p = define_type(SCREENFOCUS, SET, "SCREENFOCUS", (GetProcValueByType) get_str_SET);
    define_evalue(p, 0x01L, "focus");
    define_evalue(p, 0x02L, "same-screen");
}
