//
// Created by dingjing on 23-5-17.
//

#include "xtype-enumerated.h"

#include <stdio.h>

#include "tools.h"
#include "xproto.h"
#include "xtype-common.h"



void xtype_enumerated_init(void)
{
    Type p;

    p = define_type(REQUEST, ENUMERATED, "REQUEST", (GetProcValueByType) get_str_ENUMERATED);
    define_evalue(p, 1L, "CreateWindow");
    define_evalue(p, 2L, "ChangeWindowAttributes");
    define_evalue(p, 3L, "GetWindowAttributes");
    define_evalue(p, 4L, "DestroyWindow");
    define_evalue(p, 5L, "DestroySubwindows");
    define_evalue(p, 6L, "ChangeSaveSet");
    define_evalue(p, 7L, "ReparentWindow");
    define_evalue(p, 8L, "MapWindow");
    define_evalue(p, 9L, "MapSubwindows");
    define_evalue(p, 10L, "UnmapWindow");
    define_evalue(p, 11L, "UnmapSubwindows");
    define_evalue(p, 12L, "ConfigureWindow");
    define_evalue(p, 13L, "CirculateWindow");
    define_evalue(p, 14L, "GetGeometry");
    define_evalue(p, 15L, "QueryTree");
    define_evalue(p, 16L, "InternAtom");
    define_evalue(p, 17L, "GetAtomName");
    define_evalue(p, 18L, "ChangeProperty");
    define_evalue(p, 19L, "DeleteProperty");
    define_evalue(p, 20L, "GetProperty");
    define_evalue(p, 21L, "ListProperties");
    define_evalue(p, 22L, "SetSelectionOwner");
    define_evalue(p, 23L, "GetSelectionOwner");
    define_evalue(p, 24L, "ConvertSelection");
    define_evalue(p, 25L, "SendEvent");
    define_evalue(p, 26L, "GrabPointer");
    define_evalue(p, 27L, "UngrabPointer");
    define_evalue(p, 28L, "GrabButton");
    define_evalue(p, 29L, "UngrabButton");
    define_evalue(p, 30L, "ChangeActivePointerGrab");
    define_evalue(p, 31L, "GrabKeyboard");
    define_evalue(p, 32L, "UngrabKeyboard");
    define_evalue(p, 33L, "GrabKey");
    define_evalue(p, 34L, "UngrabKey");
    define_evalue(p, 35L, "AllowEvents");
    define_evalue(p, 36L, "GrabServer");
    define_evalue(p, 37L, "UngrabServer");
    define_evalue(p, 38L, "QueryPointer");
    define_evalue(p, 39L, "GetMotionEvents");
    define_evalue(p, 40L, "TranslateCoordinates");
    define_evalue(p, 41L, "WarpPointer");
    define_evalue(p, 42L, "SetInputFocus");
    define_evalue(p, 43L, "GetInputFocus");
    define_evalue(p, 44L, "QueryKeymap");
    define_evalue(p, 45L, "OpenFont");
    define_evalue(p, 46L, "CloseFont");
    define_evalue(p, 47L, "QueryFont");
    define_evalue(p, 48L, "QueryTextExtents");
    define_evalue(p, 49L, "ListFonts");
    define_evalue(p, 50L, "ListFontsWithInfo");
    define_evalue(p, 51L, "SetFontPath");
    define_evalue(p, 52L, "GetFontPath");
    define_evalue(p, 53L, "CreatePixmap");
    define_evalue(p, 54L, "FreePixmap");
    define_evalue(p, 55L, "CreateGC");
    define_evalue(p, 56L, "ChangeGC");
    define_evalue(p, 57L, "CopyGC");
    define_evalue(p, 58L, "SetDashes");
    define_evalue(p, 59L, "SetClipRectangles");
    define_evalue(p, 60L, "FreeGC");
    define_evalue(p, 61L, "ClearArea");
    define_evalue(p, 62L, "CopyArea");
    define_evalue(p, 63L, "CopyPlane");
    define_evalue(p, 64L, "PolyPoint");
    define_evalue(p, 65L, "PolyLine");
    define_evalue(p, 66L, "PolySegment");
    define_evalue(p, 67L, "PolyRectangle");
    define_evalue(p, 68L, "PolyArc");
    define_evalue(p, 69L, "FillPoly");
    define_evalue(p, 70L, "PolyFillRectangle");
    define_evalue(p, 71L, "PolyFillArc");
    define_evalue(p, 72L, "PutImage");
    define_evalue(p, 73L, "GetImage");
    define_evalue(p, 74L, "PolyText8");
    define_evalue(p, 75L, "PolyText16");
    define_evalue(p, 76L, "ImageText8");
    define_evalue(p, 77L, "ImageText16");
    define_evalue(p, 78L, "CreateColormap");
    define_evalue(p, 79L, "FreeColormap");
    define_evalue(p, 80L, "CopyColormapAndFree");
    define_evalue(p, 81L, "InstallColormap");
    define_evalue(p, 82L, "UninstallColormap");
    define_evalue(p, 83L, "ListInstalledColormaps");
    define_evalue(p, 84L, "AllocColor");
    define_evalue(p, 85L, "AllocNamedColor");
    define_evalue(p, 86L, "AllocColorCells");
    define_evalue(p, 87L, "AllocColorPlanes");
    define_evalue(p, 88L, "FreeColors");
    define_evalue(p, 89L, "StoreColors");
    define_evalue(p, 90L, "StoreNamedColor");
    define_evalue(p, 91L, "QueryColors");
    define_evalue(p, 92L, "LookupColor");
    define_evalue(p, 93L, "CreateCursor");
    define_evalue(p, 94L, "CreateGlyphCursor");
    define_evalue(p, 95L, "FreeCursor");
    define_evalue(p, 96L, "RecolorCursor");
    define_evalue(p, 97L, "QueryBestSize");
    define_evalue(p, 98L, "QueryExtension");
    define_evalue(p, 99L, "ListExtensions");
    define_evalue(p, 100L, "ChangeKeyboardMapping");
    define_evalue(p, 101L, "GetKeyboardMapping");
    define_evalue(p, 102L, "ChangeKeyboardControl");
    define_evalue(p, 103L, "GetKeyboardControl");
    define_evalue(p, 104L, "Bell");
    define_evalue(p, 105L, "ChangePointerControl");
    define_evalue(p, 106L, "GetPointerControl");
    define_evalue(p, 107L, "SetScreenSaver");
    define_evalue(p, 108L, "GetScreenSaver");
    define_evalue(p, 109L, "ChangeHosts");
    define_evalue(p, 110L, "ListHosts");
    define_evalue(p, 111L, "SetAccessControl");
    define_evalue(p, 112L, "SetCloseDownMode");
    define_evalue(p, 113L, "KillClient");
    define_evalue(p, 114L, "RotateProperties");
    define_evalue(p, 115L, "ForceScreenSaver");
    define_evalue(p, 116L, "SetPointerMapping");
    define_evalue(p, 117L, "GetPointerMapping");
    define_evalue(p, 118L, "SetModifierMapping");
    define_evalue(p, 119L, "GetModifierMapping");
    define_evalue(p, 127L, "NoOperation");

    p = define_type(REPLY, ENUMERATED, "REPLY", (GetProcValueByType) get_str_ENUMERATED);
    define_evalue(p, 3L, "GetWindowAttributes");
    define_evalue(p, 14L, "GetGeometry");
    define_evalue(p, 15L, "QueryTree");
    define_evalue(p, 16L, "InternAtom");
    define_evalue(p, 17L, "GetAtomName");
    define_evalue(p, 20L, "GetProperty");
    define_evalue(p, 21L, "ListProperties");
    define_evalue(p, 23L, "GetSelectionOwner");
    define_evalue(p, 26L, "GrabPointer");
    define_evalue(p, 31L, "GrabKeyboard");
    define_evalue(p, 38L, "QueryPointer");
    define_evalue(p, 39L, "GetMotionEvents");
    define_evalue(p, 40L, "TranslateCoordinates");
    define_evalue(p, 43L, "GetInputFocus");
    define_evalue(p, 44L, "QueryKeymap");
    define_evalue(p, 47L, "QueryFont");
    define_evalue(p, 48L, "QueryTextExtents");
    define_evalue(p, 49L, "ListFonts");
    define_evalue(p, 50L, "ListFontsWithInfo");
    define_evalue(p, 52L, "GetFontPath");
    define_evalue(p, 73L, "GetImage");
    define_evalue(p, 83L, "ListInstalledColormaps");
    define_evalue(p, 84L, "AllocColor");
    define_evalue(p, 85L, "AllocNamedColor");
    define_evalue(p, 86L, "AllocColorCells");
    define_evalue(p, 87L, "AllocColorPlanes");
    define_evalue(p, 91L, "QueryColors");
    define_evalue(p, 92L, "LookupColor");
    define_evalue(p, 97L, "QueryBestSize");
    define_evalue(p, 98L, "QueryExtension");
    define_evalue(p, 99L, "ListExtensions");
    define_evalue(p, 101L, "GetKeyboardMapping");
    define_evalue(p, 103L, "GetKeyboardControl");
    define_evalue(p, 106L, "GetPointerControl");
    define_evalue(p, 108L, "GetScreenSaver");
    define_evalue(p, 110L, "ListHosts");
    define_evalue(p, 116L, "SetPointerMapping");
    define_evalue(p, 117L, "GetPointerMapping");
    define_evalue(p, 118L, "SetModifierMapping");
    define_evalue(p, 119L, "GetModifierMapping");

    p = define_type(ERROR, ENUMERATED, "ERROR", (GetProcValueByType) get_str_ENUMERATED);
    define_evalue(p, 1L, "Request");
    define_evalue(p, 2L, "Value");
    define_evalue(p, 3L, "Window");
    define_evalue(p, 4L, "Pixmap");
    define_evalue(p, 5L, "Atom");
    define_evalue(p, 6L, "Cursor");
    define_evalue(p, 7L, "Font");
    define_evalue(p, 8L, "Match");
    define_evalue(p, 9L, "Drawable");
    define_evalue(p, 10L, "Access");
    define_evalue(p, 11L, "Alloc");
    define_evalue(p, 12L, "Colormap");
    define_evalue(p, 13L, "GContext");
    define_evalue(p, 14L, "IDChoice");
    define_evalue(p, 15L, "Name");
    define_evalue(p, 16L, "Length");
    define_evalue(p, 17L, "Implementation");

    p = define_type(EVENT, BUILTIN, "EVENT", (GetProcValueByType) get_str_EVENT);
    define_evalue(p, 2L, "KeyPress");
    define_evalue(p, 3L, "KeyRelease");
    define_evalue(p, 4L, "ButtonPress");
    define_evalue(p, 5L, "ButtonRelease");
    define_evalue(p, 6L, "MotionNotify");
    define_evalue(p, 7L, "EnterNotify");
    define_evalue(p, 8L, "LeaveNotify");
    define_evalue(p, 9L, "FocusIn");
    define_evalue(p, 10L, "FocusOut");
    define_evalue(p, 11L, "KeymapNotify");
    define_evalue(p, 12L, "Expose");
    define_evalue(p, 13L, "GraphicsExposure");
    define_evalue(p, 14L, "NoExposure");
    define_evalue(p, 15L, "VisibilityNotify");
    define_evalue(p, 16L, "CreateNotify");
    define_evalue(p, 17L, "DestroyNotify");
    define_evalue(p, 18L, "UnmapNotify");
    define_evalue(p, 19L, "MapNotify");
    define_evalue(p, 20L, "MapRequest");
    define_evalue(p, 21L, "ReparentNotify");
    define_evalue(p, 22L, "ConfigureNotify");
    define_evalue(p, 23L, "ConfigureRequest");
    define_evalue(p, 24L, "GravityNotify");
    define_evalue(p, 25L, "ResizeRequest");
    define_evalue(p, 26L, "CirculateNotify");
    define_evalue(p, 27L, "CirculateRequest");
    define_evalue(p, 28L, "PropertyNotify");
    define_evalue(p, 29L, "SelectionClear");
    define_evalue(p, 30L, "SelectionRequest");
    define_evalue(p, 31L, "SelectionNotify");
    define_evalue(p, 32L, "ColormapNotify");
    define_evalue(p, 33L, "ClientMessage");
    define_evalue(p, 34L, "MappingNotify");
    define_evalue(p, 35L, "GenericEvent");

    p = define_type(BITGRAVITY, ENUMERATED, "BITGRAVITY", (GetProcValueByType) get_str_ENUMERATED);
    define_evalue(p, 0L, "Forget");
    define_evalue(p, 1L, "NorthWest");
    define_evalue(p, 2L, "North");
    define_evalue(p, 3L, "NorthEast");
    define_evalue(p, 4L, "West");
    define_evalue(p, 5L, "Center");
    define_evalue(p, 6L, "East");
    define_evalue(p, 7L, "SouthWest");
    define_evalue(p, 8L, "South");
    define_evalue(p, 9L, "SouthEast");
    define_evalue(p, 10L, "Static");

    p = define_type(WINGRAVITY, ENUMERATED, "WINGRAVITY", (GetProcValueByType) get_str_ENUMERATED);
    define_evalue(p, 0L, "Unmap");
    define_evalue(p, 1L, "NorthWest");
    define_evalue(p, 2L, "North");
    define_evalue(p, 3L, "NorthEast");
    define_evalue(p, 4L, "West");
    define_evalue(p, 5L, "Center");
    define_evalue(p, 6L, "East");
    define_evalue(p, 7L, "SouthWest");
    define_evalue(p, 8L, "South");
    define_evalue(p, 9L, "SouthEast");
    define_evalue(p, 10L, "Static");

    p = define_type(BOOL, ENUMERATED, "BOOL", (GetProcValueByType) get_str_ENUMERATED);
    define_evalue(p, 0L, "False");
    define_evalue(p, 1L, "True");

    p = define_type(HOSTFAMILY, ENUMERATED, "HOSTFAMILY", (GetProcValueByType) get_str_ENUMERATED);
    define_evalue(p, 0L, "Internet");
    define_evalue(p, 1L, "DECnet");
    define_evalue(p, 2L, "Chaos");
    define_evalue(p, 5L, "ServerInterpreted");
    define_evalue(p, 6L, "InternetV6");
    define_evalue(p, 252L, "LocalHost");
    define_evalue(p, 253L, "Kerberos5");
    define_evalue(p, 254L, "SecureRPC");

    p = define_type(PK_MODE, ENUMERATED, "PK_MODE", (GetProcValueByType) get_str_ENUMERATED);
    define_evalue(p, 0L, "Synchronous");
    define_evalue(p, 1L, "Asynchronous");

    p = define_type(NO_YES, ENUMERATED, "NO_YES", (GetProcValueByType) get_str_ENUMERATED);
    define_evalue(p, 0L, "No");
    define_evalue(p, 1L, "Yes");
    define_evalue(p, 2L, "Default");

    p = define_type(WINDOWCLASS, ENUMERATED, "WINDOWCLASS", (GetProcValueByType) get_str_ENUMERATED);
    define_evalue(p, 0L, "CopyFromParent");
    define_evalue(p, 1L, "InputOutput");
    define_evalue(p, 2L, "InputOnly");

    p = define_type(BACKSTORE, ENUMERATED, "BACKSTORE", (GetProcValueByType) get_str_ENUMERATED);
    define_evalue(p, 0L, "NotUseful");
    define_evalue(p, 1L, "WhenMapped");
    define_evalue(p, 2L, "Always");

    p = define_type(MAPSTATE, ENUMERATED, "MAPSTATE", (GetProcValueByType) get_str_ENUMERATED);
    define_evalue(p, 0L, "Unmapped");
    define_evalue(p, 1L, "Unviewable");
    define_evalue(p, 2L, "Viewable");

    p = define_type(STACKMODE, ENUMERATED, "STACKMODE", (GetProcValueByType) get_str_ENUMERATED);
    define_evalue(p, 0L, "Above");
    define_evalue(p, 1L, "Below");
    define_evalue(p, 2L, "TopIf");
    define_evalue(p, 3L, "BottomIf");
    define_evalue(p, 4L, "Opposite");

    p = define_type(CIRMODE, ENUMERATED, "CIRMODE", (GetProcValueByType) get_str_ENUMERATED);
    define_evalue(p, 0L, "RaiseLowest");
    define_evalue(p, 1L, "LowerHighest");

    p = define_type(CHANGEMODE, ENUMERATED, "CHANGEMODE", (GetProcValueByType) get_str_ENUMERATED);
    define_evalue(p, 0L, "Replace");
    define_evalue(p, 1L, "Prepend");
    define_evalue(p, 2L, "Append");

    p = define_type(GRABSTAT, ENUMERATED, "GRABSTAT", (GetProcValueByType) get_str_ENUMERATED);
    define_evalue(p, 0L, "Success");
    define_evalue(p, 1L, "AlreadyGrabbed");
    define_evalue(p, 2L, "InvalidTime");
    define_evalue(p, 3L, "NotViewable");
    define_evalue(p, 4L, "Frozen");

    p = define_type(EVENTMODE, ENUMERATED, "EVENTMODE", (GetProcValueByType) get_str_ENUMERATED);
    define_evalue(p, 0L, "AsyncPointer");
    define_evalue(p, 1L, "SyncPointer");
    define_evalue(p, 2L, "ReplayPointer");
    define_evalue(p, 3L, "AsyncKeyboard");
    define_evalue(p, 4L, "SyncKeyboard");
    define_evalue(p, 5L, "ReplayKeyboard");
    define_evalue(p, 6L, "AsyncBoth");
    define_evalue(p, 7L, "SyncBoth");

    p = define_type(FOCUSAGENT, ENUMERATED, "FOCUSAGENT", (GetProcValueByType) get_str_ENUMERATED);
    define_evalue(p, 0L, "None");
    define_evalue(p, 1L, "PointerRoot");
    define_evalue(p, 2L, "Parent");

    p = define_type(DIRECT, ENUMERATED, "DIRECT", (GetProcValueByType) get_str_ENUMERATED);
    define_evalue(p, 0L, "LeftToRight");
    define_evalue(p, 1L, "RightToLeft");

    p = define_type(GCFUNC, ENUMERATED, "GCFUNC", (GetProcValueByType) get_str_ENUMERATED);
    define_evalue(p, 0L, "Clear");
    define_evalue(p, 1L, "And");
    define_evalue(p, 2L, "AndReverse");
    define_evalue(p, 3L, "Copy");
    define_evalue(p, 4L, "AndInverted");
    define_evalue(p, 5L, "Noop");
    define_evalue(p, 6L, "Xor");
    define_evalue(p, 7L, "Or");
    define_evalue(p, 8L, "Nor");
    define_evalue(p, 9L, "Equiv");
    define_evalue(p, 10L, "Invert");
    define_evalue(p, 11L, "OrReverse");
    define_evalue(p, 12L, "CopyInverted");
    define_evalue(p, 13L, "OrInverted");
    define_evalue(p, 14L, "Nand");
    define_evalue(p, 15L, "Set");

    p = define_type(LINESTYLE, ENUMERATED, "LINESTYLE", (GetProcValueByType) get_str_ENUMERATED);
    define_evalue(p, 0L, "Solid");
    define_evalue(p, 1L, "OnOffDash");
    define_evalue(p, 2L, "DoubleDash");

    p = define_type(CAPSTYLE, ENUMERATED, "CAPSTYLE", (GetProcValueByType) get_str_ENUMERATED);
    define_evalue(p, 0L, "NotLast");
    define_evalue(p, 1L, "Butt");
    define_evalue(p, 2L, "Round");
    define_evalue(p, 3L, "Projecting");

    p = define_type(JOINSTYLE, ENUMERATED, "JOINSTYLE", (GetProcValueByType) get_str_ENUMERATED);
    define_evalue(p, 0L, "Miter");
    define_evalue(p, 1L, "Round");
    define_evalue(p, 2L, "Bevel");

    p = define_type(FILLSTYLE, ENUMERATED, "FILLSTYLE", (GetProcValueByType) get_str_ENUMERATED);
    define_evalue(p, 0L, "Solid");
    define_evalue(p, 1L, "Tiled");
    define_evalue(p, 2L, "Stippled");
    define_evalue(p, 3L, "OpaqueStippled");

    p = define_type(FILLRULE, ENUMERATED, "FILLRULE", (GetProcValueByType) get_str_ENUMERATED);
    define_evalue(p, 0L, "EvenOdd");
    define_evalue(p, 1L, "Winding");

    p = define_type(SUBWINMODE, ENUMERATED, "SUBWINMODE", (GetProcValueByType) get_str_ENUMERATED);
    define_evalue(p, 0L, "ClipByChildren");
    define_evalue(p, 1L, "IncludeInferiors");

    p = define_type(ARCMODE, ENUMERATED, "ARCMODE", (GetProcValueByType) get_str_ENUMERATED);
    define_evalue(p, 0L, "Chord");
    define_evalue(p, 1L, "PieSlice");

    p = define_type(RECTORDER, ENUMERATED, "RECTORDER", (GetProcValueByType) get_str_ENUMERATED);
    define_evalue(p, 0L, "UnSorted");
    define_evalue(p, 1L, "YSorted");
    define_evalue(p, 2L, "YXSorted");
    define_evalue(p, 3L, "YXBanded");

    p = define_type(COORMODE, ENUMERATED, "COORMODE", (GetProcValueByType) get_str_ENUMERATED);
    define_evalue(p, 0L, "Origin");
    define_evalue(p, 1L, "Previous");

    p = define_type(POLYSHAPE, ENUMERATED, "POLYSHAPE", (GetProcValueByType) get_str_ENUMERATED);
    define_evalue(p, 0L, "Complex");
    define_evalue(p, 1L, "Nonconvex");
    define_evalue(p, 2L, "Convex");

    p = define_type(IMAGEMODE, ENUMERATED, "IMAGEMODE", (GetProcValueByType) get_str_ENUMERATED);
    define_evalue(p, 0L, "Bitmap");
    define_evalue(p, 1L, "XYPixmap");
    define_evalue(p, 2L, "ZPixmap");

    p = define_type(ALLORNONE, ENUMERATED, "ALLORNONE", (GetProcValueByType) get_str_ENUMERATED);
    define_evalue(p, 0L, "None");
    define_evalue(p, 1L, "All");

    p = define_type(OBJECTCLASS, ENUMERATED, "OBJECTCLASS", (GetProcValueByType) get_str_ENUMERATED);
    define_evalue(p, 0L, "Cursor");
    define_evalue(p, 1L, "Tile");
    define_evalue(p, 2L, "Stipple");

    p = define_type(OFF_ON, ENUMERATED, "OFF_ON", (GetProcValueByType) get_str_ENUMERATED);
    define_evalue(p, 0L, "Off");
    define_evalue(p, 1L, "On");
    define_evalue(p, 2L, "Default");

    p = define_type(INS_DEL, ENUMERATED, "INS_DEL", (GetProcValueByType) get_str_ENUMERATED);
    define_evalue(p, 0L, "Insert");
    define_evalue(p, 1L, "Delete");

    p = define_type(DIS_EN, ENUMERATED, "DIS_EN", (GetProcValueByType) get_str_ENUMERATED);
    define_evalue(p, 0L, "Disabled");
    define_evalue(p, 1L, "Enabled");

    p = define_type(CLOSEMODE, ENUMERATED, "CLOSEMODE", (GetProcValueByType) get_str_ENUMERATED);
    define_evalue(p, 0L, "Destroy");
    define_evalue(p, 1L, "RetainPermanent");
    define_evalue(p, 2L, "RetainTemporary");

    p = define_type(SAVEMODE, ENUMERATED, "SAVEMODE", (GetProcValueByType) get_str_ENUMERATED);
    define_evalue(p, 0L, "Reset");
    define_evalue(p, 1L, "Activate");

    p = define_type(RSTATUS, ENUMERATED, "RSTATUS", (GetProcValueByType) get_str_ENUMERATED);
    define_evalue(p, 0L, "Success");
    define_evalue(p, 1L, "Busy");
    define_evalue(p, 2L, "Failed");

    p = define_type(MOTIONDETAIL, ENUMERATED, "MOTIONDETAIL", (GetProcValueByType) get_str_ENUMERATED);
    define_evalue(p, 0L, "Normal");
    define_evalue(p, 1L, "Hint");

    p = define_type(ENTERDETAIL, ENUMERATED, "ENTERDETAIL", (GetProcValueByType) get_str_ENUMERATED);
    define_evalue(p, 0L, "Ancestor");
    define_evalue(p, 1L, "Virtual");
    define_evalue(p, 2L, "Inferior");
    define_evalue(p, 3L, "Nonlinear");
    define_evalue(p, 4L, "NonlinearVirtual");
    define_evalue(p, 5L, "Pointer");
    define_evalue(p, 6L, "PointerRoot");
    define_evalue(p, 7L, "None");

    p = define_type(BUTTONMODE, ENUMERATED, "BUTTONMODE", (GetProcValueByType) get_str_ENUMERATED);
    define_evalue(p, 0L, "Normal");
    define_evalue(p, 1L, "Grab");
    define_evalue(p, 2L, "Ungrab");
    define_evalue(p, 3L, "WhileGrabbed");

    p = define_type(VISIBLE, ENUMERATED, "VISIBLE", (GetProcValueByType) get_str_ENUMERATED);
    define_evalue(p, 0L, "Unobscured");
    define_evalue(p, 1L, "PartiallyObscured");
    define_evalue(p, 2L, "FullyObscured");

    p = define_type(CIRSTAT, ENUMERATED, "CIRSTAT", (GetProcValueByType) get_str_ENUMERATED);
    define_evalue(p, 0L, "Top");
    define_evalue(p, 1L, "Bottom");

    p = define_type(PROPCHANGE, ENUMERATED, "PROPCHANGE", (GetProcValueByType) get_str_ENUMERATED);
    define_evalue(p, 0L, "NewValue");
    define_evalue(p, 1L, "Deleted");

    p = define_type(CMAPCHANGE, ENUMERATED, "CMAPCHANGE", (GetProcValueByType) get_str_ENUMERATED);
    define_evalue(p, 0L, "Uninstalled");
    define_evalue(p, 1L, "Installed");

    p = define_type(MAPOBJECT, ENUMERATED, "MAPOBJECT", (GetProcValueByType) get_str_ENUMERATED);
    define_evalue(p, 0L, "Modifier");
    define_evalue(p, 1L, "Keyboard");
    define_evalue(p, 2L, "Pointer");

    p = define_type(BYTEMODE, ENUMERATED, "BYTEMODE", (GetProcValueByType) get_str_ENUMERATED);
    define_evalue(p, 0x42L, "MSB first");
    define_evalue(p, 0x6CL, "LSB first");

    p = define_type(BYTEORDER, ENUMERATED, "BYTEORDER", (GetProcValueByType) get_str_ENUMERATED);
    define_evalue(p, 0L, "LSB first");
    define_evalue(p, 1L, "MSB first");

    p = define_type(COLORCLASS, ENUMERATED, "COLORCLASS", (GetProcValueByType) get_str_ENUMERATED);
    define_evalue(p, 0L, "StaticGray");
    define_evalue(p, 1L, "GrayScale");
    define_evalue(p, 2L, "StaticColor");
    define_evalue(p, 3L, "PseudoColor");
    define_evalue(p, 4L, "TrueColor");
    define_evalue(p, 5L, "DirectColor");

    p = define_type(EXTENSION, ENUMERATED, "EXTENSION", (GetProcValueByType) get_str_ENUMERATED);
}

