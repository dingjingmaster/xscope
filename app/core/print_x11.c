//
// Created by dingjing on 23-5-12.
//

#include "xproto.h"


static void printFailedSetUpReply(const unsigned char *buf);

static void printSuccessfulSetUpReply(const unsigned char *buf);

static void ListFontsWithInfoReply1(const unsigned char *buf);

static void ListFontsWithInfoReply2(const unsigned char *buf);


/* ************************************************************ */
/*								*/
/*								*/
/* ************************************************************ */

/*
  In printing the contents of the fields of the X11 packets, some
  fields are of obvious value, and others are of lesser value.  To
  control the amount of output, we generate our output according
  to the level of Verbose-ness that was selected by the user.

  Verbose = 0 ==  Headers only, time and request/reply/... names.

  Verbose = 1 ==  Very useful content fields.

  Verbose = 2 ==  Almost everything.

  Verbose = 3 ==  Every single bit and byte.

*/

/*
  To aid in making the choice between level 1 and level 2, we
  define the following define, which does not print relatively
  unimportant fields.
*/

#define printfield(a, b, c, d, e) if (Verbose > 1) printField(a,b,c,d,e)

/* ************************************************************ */
/*								*/
/*								*/
/* ************************************************************ */

void printSetUpMessage(const unsigned char *buf) {
    short n;
    short d;

    SetIndentLevel (PRINTCLIENT);
    printField (buf, 0, 1, BYTEMODE, "byte-order");
    printField (buf, 2, 2, CARD16, "major-version");
    printField (buf, 4, 2, CARD16, "minor-version");
    printfield(buf, 6, 2, DVALUE2 (n), "length of name");
    n = IShort (&buf[6]);
    printfield(buf, 8, 2, DVALUE2 (d), "length of data");
    d = IShort (&buf[8]);
    printString8 (&buf[12], n, "authorization-protocol-name");
    printString8 (&buf[pad ((long) (12 + n))], d, "authorization-protocol-data");
}

void printSetUpReply(const unsigned char *buf) {
    SetIndentLevel (PRINTSERVER);
    if (IByte (&buf[0]))
        printSuccessfulSetUpReply (buf);
    else
        printFailedSetUpReply (buf);
}

static void printFailedSetUpReply(const unsigned char *buf) {
    short n;

    printField (buf, 0, 1, 0, "SetUp Failed");

    printfield(buf, 1, 1, DVALUE1 (n), "length of reason in bytes");
    n = IByte (&buf[1]);
    printField (buf, 2, 2, CARD16, "major-version");
    printField (buf, 4, 2, CARD16, "minor-version");
    printfield(buf, 6, 2, DVALUE2 ((n + p) / 4), "length of data");
    printString8 (&buf[8], n, "reason");
}

static void printSuccessfulSetUpReply(const unsigned char *buf) {
    short v;
    short n;
    short m;

    printField (buf, 2, 2, CARD16, "protocol-major-version");
    printField (buf, 4, 2, CARD16, "protocol-minor-version");
    printfield(buf, 6, 2, DVALUE2 (8 + 2 * n + (v + p + m) / 4), "length of data");
    printField (buf, 8, 4, CARD32, "release-number");
    printField (buf, 12, 4, CARD32, "resource-id-base");
    printField (buf, 16, 4, CARD32, "resource-id-mask");
    printField (buf, 20, 4, CARD32, "motion-buffer-size");
    printfield(buf, 24, 2, DVALUE2 (v), "length of vendor");
    v = IShort (&buf[24]);
    printfield(buf, 26, 2, CARD16, "maximum-request-length");
    printfield(buf, 28, 1, CARD8, "number of roots");
    m = IByte (&buf[28]);
    printfield(buf, 29, 1, DVALUE1 (n), "number of pixmap-formats");
    n = IByte (&buf[29]);
    printField (buf, 30, 1, BYTEORDER, "image-byte-order");
    printField (buf, 31, 1, BYTEORDER, "bitmap-format-bit-order");
    printField (buf, 32, 1, CARD8, "bitmap-format-scanline-unit");
    printField (buf, 33, 1, CARD8, "bitmap-format-scanline-pad");
    printField (buf, 34, 1, KEYCODE, "min-keycode");
    printField (buf, 35, 1, KEYCODE, "max-keycode");
    printString8 (&buf[40], v, "vendor");
    printList (&buf[pad ((long) (40 + v))], (long) n, FORMAT, "pixmap-formats");
    printList (&buf[pad ((long) (40 + v) + 8 * n)], (long) m, SCREEN, "roots");
}


const char *REQUESTHEADER = "............REQUEST";
const char *EVENTHEADER = "..............EVENT";
const char *ERRORHEADER = "..............ERROR";
const char *REPLYHEADER = "..............REPLY";


void printErrorWithValue(const unsigned char *buf, short FieldType, const char *desc) {
    printField (buf, 1, 1, ERROR, ERRORHEADER);

    printfield(buf, 2, 2, CARD16, "sequence number");
    printField (buf, 4, 4, FieldType, desc);
    printField (buf, 8, 2, CARD16, "minor opcode");
    printField (buf, 10, 1, CARD8, "major opcode");
}


void printErrorNoValue(const unsigned char *buf) {
    printField (buf, 1, 1, ERROR, ERRORHEADER);

    printfield(buf, 2, 2, CARD16, "sequence number");
    /* 4 bytes unused */
    printField (buf, 8, 2, CARD16, "minor opcode");
    printField (buf, 10, 1, CARD8, "major opcode");
}

void RequestError(const unsigned char *buf) {
    printErrorNoValue (buf);
}

void ValueError(const unsigned char *buf) {
    printErrorWithValue (buf, INT32, "bad value");
}

void WindowError(const unsigned char *buf) {
    printErrorWithValue (buf, CARD32, "bad resource id");
}

void PixmapError(const unsigned char *buf) {
    printErrorWithValue (buf, CARD32, "bad resource id");
}

void AtomError(const unsigned char *buf) {
    printErrorWithValue (buf, CARD32, "bad atom id");
}

void CursorError(const unsigned char *buf) {
    printErrorWithValue (buf, CARD32, "bad resource id");
}

void FontError(const unsigned char *buf) {
    printErrorWithValue (buf, CARD32, "bad resource id");
}

void MatchError(const unsigned char *buf) {
    printErrorNoValue (buf);
}

void DrawableError(const unsigned char *buf) {
    printErrorWithValue (buf, CARD32, "bad resource id");
}

void AccessError(const unsigned char *buf) {
    printErrorNoValue (buf);
}

void AllocError(const unsigned char *buf) {
    printErrorNoValue (buf);
}

void ColormapError(const unsigned char *buf) {
    printErrorWithValue (buf, CARD32, "bad resource id");
}

void GContextError(const unsigned char *buf) {
    printErrorWithValue (buf, CARD32, "bad resource id");
}

void IDChoiceError(const unsigned char *buf) {
    printErrorWithValue (buf, CARD32, "bad resource id");
}

void NameError(const unsigned char *buf) {
    printErrorNoValue (buf);
}

void LengthError(const unsigned char *buf) {
    printErrorNoValue (buf);
}

void ImplementationError(const unsigned char *buf) {
    printErrorNoValue (buf);
}

void UnknownError(const unsigned char *buf) {
    printErrorWithValue (buf, CARD32, "bad resource id");
}

void KeyPressEvent(const unsigned char *buf) {
    printField (buf, 0, 1, EVENT, EVENTHEADER); /* KeyPress */

    printField (buf, 1, 1, KEYCODE, "detail");
    printfield(buf, 2, 2, CARD16, "sequence number");
    printField (buf, 4, 4, TIMESTAMP, "time");
    printField (buf, 8, 4, WINDOW, "root");
    printField (buf, 12, 4, WINDOW, "event");
    printField (buf, 16, 4, WINDOW, "child");
    printField (buf, 20, 2, INT16, "root-x");
    printField (buf, 22, 2, INT16, "root-y");
    printField (buf, 24, 2, INT16, "event-x");
    printField (buf, 26, 2, INT16, "event-y");
    printField (buf, 28, 2, SETofKEYBUTMASK, "state");
    printField (buf, 30, 1, BOOL, "same-screen");
}

void KeyReleaseEvent(const unsigned char *buf) {
    printField (buf, 0, 1, EVENT, EVENTHEADER); /* KeyRelease */

    printField (buf, 1, 1, KEYCODE, "detail");
    printfield(buf, 2, 2, CARD16, "sequence number");
    printField (buf, 4, 4, TIMESTAMP, "time");
    printField (buf, 8, 4, WINDOW, "root");
    printField (buf, 12, 4, WINDOW, "event");
    printField (buf, 16, 4, WINDOW, "child");
    printField (buf, 20, 2, INT16, "root-x");
    printField (buf, 22, 2, INT16, "root-y");
    printField (buf, 24, 2, INT16, "event-x");
    printField (buf, 26, 2, INT16, "event-y");
    printField (buf, 28, 2, SETofKEYBUTMASK, "state");
    printField (buf, 30, 1, BOOL, "same-screen");
}

void ButtonPressEvent(const unsigned char *buf) {
    printField (buf, 0, 1, EVENT, EVENTHEADER); /* ButtonPress */

    printField (buf, 1, 1, BUTTON, "detail");
    printfield(buf, 2, 2, CARD16, "sequence number");
    printField (buf, 4, 4, TIMESTAMP, "time");
    printField (buf, 8, 4, WINDOW, "root");
    printField (buf, 12, 4, WINDOW, "event");
    printField (buf, 16, 4, WINDOW, "child");
    printField (buf, 20, 2, INT16, "root-x");
    printField (buf, 22, 2, INT16, "root-y");
    printField (buf, 24, 2, INT16, "event-x");
    printField (buf, 26, 2, INT16, "event-y");
    printField (buf, 28, 2, SETofKEYBUTMASK, "state");
    printField (buf, 30, 1, BOOL, "same-screen");
}

void ButtonReleaseEvent(const unsigned char *buf) {
    printField (buf, 0, 1, EVENT, EVENTHEADER); /* ButtonRelease */

    printField (buf, 1, 1, BUTTON, "detail");
    printfield(buf, 2, 2, CARD16, "sequence number");
    printField (buf, 4, 4, TIMESTAMP, "time");
    printField (buf, 8, 4, WINDOW, "root");
    printField (buf, 12, 4, WINDOW, "event");
    printField (buf, 16, 4, WINDOW, "child");
    printField (buf, 20, 2, INT16, "root-x");
    printField (buf, 22, 2, INT16, "root-y");
    printField (buf, 24, 2, INT16, "event-x");
    printField (buf, 26, 2, INT16, "event-y");
    printField (buf, 28, 2, SETofKEYBUTMASK, "state");
    printField (buf, 30, 1, BOOL, "same-screen");
}

void MotionNotifyEvent(const unsigned char *buf) {
    printField (buf, 0, 1, EVENT, EVENTHEADER); /* MotionNotify */

    printField (buf, 1, 1, MOTIONDETAIL, "detail");
    printfield(buf, 2, 2, CARD16, "sequence number");
    printField (buf, 4, 4, TIMESTAMP, "time");
    printField (buf, 8, 4, WINDOW, "root");
    printField (buf, 12, 4, WINDOW, "event");
    printField (buf, 16, 4, WINDOW, "child");
    printField (buf, 20, 2, INT16, "root-x");
    printField (buf, 22, 2, INT16, "root-y");
    printField (buf, 24, 2, INT16, "event-x");
    printField (buf, 26, 2, INT16, "event-y");
    printField (buf, 28, 2, SETofKEYBUTMASK, "state");
    printField (buf, 30, 1, BOOL, "same-screen");
}

void EnterNotifyEvent(const unsigned char *buf) {
    printField (buf, 0, 1, EVENT, EVENTHEADER); /* EnterNotify */

    printField (buf, 1, 1, ENTERDETAIL, "detail");
    printfield(buf, 2, 2, CARD16, "sequence number");
    printField (buf, 4, 4, TIMESTAMP, "time");
    printField (buf, 8, 4, WINDOW, "root");
    printField (buf, 12, 4, WINDOW, "event");
    printField (buf, 16, 4, WINDOW, "child");
    printField (buf, 20, 2, INT16, "root-x");
    printField (buf, 22, 2, INT16, "root-y");
    printField (buf, 24, 2, INT16, "event-x");
    printField (buf, 26, 2, INT16, "event-y");
    printField (buf, 28, 2, SETofKEYBUTMASK, "state");
    printField (buf, 30, 1, BUTTONMODE, "mode");
    printField (buf, 31, 1, SCREENFOCUS, "same-screen, focus");
}

void LeaveNotifyEvent(const unsigned char *buf) {
    printField (buf, 0, 1, EVENT, EVENTHEADER); /* LeaveNotify */

    printField (buf, 1, 1, ENTERDETAIL, "detail");
    printfield(buf, 2, 2, CARD16, "sequence number");
    printField (buf, 4, 4, TIMESTAMP, "time");
    printField (buf, 8, 4, WINDOW, "root");
    printField (buf, 12, 4, WINDOW, "event");
    printField (buf, 16, 4, WINDOW, "child");
    printField (buf, 20, 2, INT16, "root-x");
    printField (buf, 22, 2, INT16, "root-y");
    printField (buf, 24, 2, INT16, "event-x");
    printField (buf, 26, 2, INT16, "event-y");
    printField (buf, 28, 2, SETofKEYBUTMASK, "state");
    printField (buf, 30, 1, BUTTONMODE, "mode");
    printField (buf, 31, 1, SCREENFOCUS, "same-screen, focus");
}

void FocusInEvent(const unsigned char *buf) {
    printField (buf, 0, 1, EVENT, EVENTHEADER); /* FocusIn */

    printField (buf, 1, 1, ENTERDETAIL, "detail");
    printfield(buf, 2, 2, CARD16, "sequence number");
    printField (buf, 4, 4, WINDOW, "event");
    printField (buf, 8, 1, BUTTONMODE, "mode");
}

void FocusOutEvent(const unsigned char *buf) {
    printField (buf, 0, 1, EVENT, EVENTHEADER); /* FocusOut */

    printField (buf, 1, 1, ENTERDETAIL, "detail");
    printfield(buf, 2, 2, CARD16, "sequence number");
    printField (buf, 4, 4, WINDOW, "event");
    printField (buf, 8, 1, BUTTONMODE, "mode");
}

void KeymapNotifyEvent(const unsigned char *buf) {
    printField (buf, 0, 1, EVENT, EVENTHEADER); /* KeymapNotify */

    printBytes (&buf[1], (long) 31, "keys");
}

void ExposeEvent(const unsigned char *buf) {
    printField (buf, 0, 1, EVENT, EVENTHEADER); /* Expose */

    printfield(buf, 2, 2, CARD16, "sequence number");
    printField (buf, 4, 4, WINDOW, "window");
    printField (buf, 8, 2, CARD16, "x");
    printField (buf, 10, 2, CARD16, "y");
    printField (buf, 12, 2, CARD16, "width");
    printField (buf, 14, 2, CARD16, "height");
    printField (buf, 16, 2, CARD16, "count");
}

void GraphicsExposureEvent(const unsigned char *buf) {
    printField (buf, 0, 1, EVENT, EVENTHEADER); /* GraphicsExposure */

    printfield(buf, 2, 2, CARD16, "sequence number");
    printField (buf, 4, 4, DRAWABLE, "drawable");
    printField (buf, 8, 2, CARD16, "x");
    printField (buf, 10, 2, CARD16, "y");
    printField (buf, 12, 2, CARD16, "width");
    printField (buf, 14, 2, CARD16, "height");
    printField (buf, 16, 2, CARD16, "minor-opcode");
    printField (buf, 18, 2, CARD16, "count");
    printField (buf, 20, 1, CARD8, "major-opcode");
}

void NoExposureEvent(const unsigned char *buf) {
    printField (buf, 0, 1, EVENT, EVENTHEADER); /* NoExposure */

    printfield(buf, 2, 2, CARD16, "sequence number");
    printField (buf, 4, 4, DRAWABLE, "drawable");
    printField (buf, 8, 2, CARD16, "minor-opcode");
    printField (buf, 10, 1, CARD8, "major-opcode");
}

void VisibilityNotifyEvent(const unsigned char *buf) {
    printField (buf, 0, 1, EVENT, EVENTHEADER); /* VisibilityNotify */

    printfield(buf, 2, 2, CARD16, "sequence number");
    printField (buf, 4, 4, WINDOW, "window");
    printField (buf, 8, 1, VISIBLE, "state");
}

void CreateNotifyEvent(const unsigned char *buf) {
    printField (buf, 0, 1, EVENT, EVENTHEADER); /* CreateNotify */

    printfield(buf, 2, 2, CARD16, "sequence number");
    printField (buf, 4, 4, WINDOW, "parent");
    printField (buf, 8, 4, WINDOW, "window");
    printField (buf, 12, 2, INT16, "x");
    printField (buf, 14, 2, INT16, "y");
    printField (buf, 16, 2, CARD16, "width");
    printField (buf, 18, 2, CARD16, "height");
    printField (buf, 20, 2, CARD16, "border-width");
    printField (buf, 22, 1, BOOL, "override-redirect");
}

void DestroyNotifyEvent(const unsigned char *buf) {
    printField (buf, 0, 1, EVENT, EVENTHEADER); /* DestroyNotify */

    printfield(buf, 2, 2, CARD16, "sequence number");
    printField (buf, 4, 4, WINDOW, "event");
    printField (buf, 8, 4, WINDOW, "window");
}

void UnmapNotifyEvent(const unsigned char *buf) {
    printField (buf, 0, 1, EVENT, EVENTHEADER); /* UnmapNotify */

    printfield(buf, 2, 2, CARD16, "sequence number");
    printField (buf, 4, 4, WINDOW, "event");
    printField (buf, 8, 4, WINDOW, "window");
    printField (buf, 12, 1, BOOL, "from-configure");
}

void MapNotifyEvent(const unsigned char *buf) {
    printField (buf, 0, 1, EVENT, EVENTHEADER); /* MapNotify */

    printfield(buf, 2, 2, CARD16, "sequence number");
    printField (buf, 4, 4, WINDOW, "event");
    printField (buf, 8, 4, WINDOW, "window");
    printField (buf, 12, 1, BOOL, "override-redirect");
}

void MapRequestEvent(const unsigned char *buf) {
    printField (buf, 0, 1, EVENT, EVENTHEADER); /* MapRequest */

    printfield(buf, 2, 2, CARD16, "sequence number");
    printField (buf, 4, 4, WINDOW, "parent");
    printField (buf, 8, 4, WINDOW, "window");
}

void ReparentNotifyEvent(const unsigned char *buf) {
    printField (buf, 0, 1, EVENT, EVENTHEADER); /* ReparentNotify */

    printfield(buf, 2, 2, CARD16, "sequence number");
    printField (buf, 4, 4, WINDOW, "event");
    printField (buf, 8, 4, WINDOW, "window");
    printField (buf, 12, 4, WINDOW, "parent");
    printField (buf, 16, 2, INT16, "x");
    printField (buf, 18, 2, INT16, "y");
    printField (buf, 20, 1, BOOL, "override-redirect");
}

void ConfigureNotifyEvent(const unsigned char *buf) {
    printField (buf, 0, 1, EVENT, EVENTHEADER); /* ConfigureNotify */

    printfield(buf, 2, 2, CARD16, "sequence number");
    printField (buf, 4, 4, WINDOW, "event");
    printField (buf, 8, 4, WINDOW, "window");
    printField (buf, 12, 4, WINDOW, "above-sibling");
    printField (buf, 16, 2, INT16, "x");
    printField (buf, 18, 2, INT16, "y");
    printField (buf, 20, 2, CARD16, "width");
    printField (buf, 22, 2, CARD16, "height");
    printField (buf, 24, 2, CARD16, "border-width");
    printField (buf, 26, 1, BOOL, "override-redirect");
}

void ConfigureRequestEvent(const unsigned char *buf) {
    printField (buf, 0, 1, EVENT, EVENTHEADER); /* ConfigureRequest */

    printField (buf, 1, 1, STACKMODE, "stack-mode");
    printfield(buf, 2, 2, CARD16, "sequence number");
    printField (buf, 4, 4, WINDOW, "parent");
    printField (buf, 8, 4, WINDOW, "window");
    printField (buf, 12, 4, WINDOW, "sibling");
    printField (buf, 16, 2, INT16, "x");
    printField (buf, 18, 2, INT16, "y");
    printField (buf, 20, 2, CARD16, "width");
    printField (buf, 22, 2, CARD16, "height");
    printField (buf, 24, 2, CARD16, "border-width");
    printField (buf, 26, 2, CONFIGURE_BITMASK, "value-mask");
}

void GravityNotifyEvent(const unsigned char *buf) {
    printField (buf, 0, 1, EVENT, EVENTHEADER); /* GravityNotify */

    printfield(buf, 2, 2, CARD16, "sequence number");
    printField (buf, 4, 4, WINDOW, "event");
    printField (buf, 8, 4, WINDOW, "window");
    printField (buf, 12, 2, INT16, "x");
    printField (buf, 14, 2, INT16, "y");
}

void ResizeRequestEvent(const unsigned char *buf) {
    printField (buf, 0, 1, EVENT, EVENTHEADER); /* ResizeRequest */

    printfield(buf, 2, 2, CARD16, "sequence number");
    printField (buf, 4, 4, WINDOW, "window");
    printField (buf, 8, 2, CARD16, "width");
    printField (buf, 10, 2, CARD16, "height");
}

void CirculateNotifyEvent(const unsigned char *buf) {
    printField (buf, 0, 1, EVENT, EVENTHEADER); /* CirculateNotify */

    printfield(buf, 2, 2, CARD16, "sequence number");
    printField (buf, 4, 4, WINDOW, "event");
    printField (buf, 8, 4, WINDOW, "window");
    printField (buf, 12, 4, WINDOW, "parent");
    printField (buf, 16, 1, CIRSTAT, "place");
}

void CirculateRequestEvent(const unsigned char *buf) {
    printField (buf, 0, 1, EVENT, EVENTHEADER); /* CirculateRequest */

    printfield(buf, 2, 2, CARD16, "sequence number");
    printField (buf, 4, 4, WINDOW, "parent");
    printField (buf, 8, 4, WINDOW, "window");
    printField (buf, 16, 1, CIRSTAT, "place");
}

void PropertyNotifyEvent(const unsigned char *buf) {
    printField (buf, 0, 1, EVENT, EVENTHEADER); /* PropertyNotify */

    printfield(buf, 2, 2, CARD16, "sequence number");
    printField (buf, 4, 4, WINDOW, "window");
    printField (buf, 8, 4, ATOM, "atom");
    printField (buf, 12, 4, TIMESTAMP, "time");
    printField (buf, 16, 1, PROPCHANGE, "state");
}

void SelectionClearEvent(const unsigned char *buf) {
    printField (buf, 0, 1, EVENT, EVENTHEADER); /* SelectionClear */

    printfield(buf, 2, 2, CARD16, "sequence number");
    printField (buf, 4, 4, TIMESTAMP, "time");
    printField (buf, 8, 4, WINDOW, "owner");
    printField (buf, 12, 4, ATOM, "selection");
}

void SelectionRequestEvent(const unsigned char *buf) {
    printField (buf, 0, 1, EVENT, EVENTHEADER); /* SelectionRequest */

    printfield(buf, 2, 2, CARD16, "sequence number");
    printField (buf, 4, 4, TIMESTAMP, "time");
    printField (buf, 8, 4, WINDOW, "owner");
    printField (buf, 12, 4, WINDOW, "requestor");
    printField (buf, 16, 4, ATOM, "selection");
    printField (buf, 20, 4, ATOM, "target");
    printField (buf, 24, 4, ATOM, "property");
}

void SelectionNotifyEvent(const unsigned char *buf) {
    printField (buf, 0, 1, EVENT, EVENTHEADER); /* SelectionNotify */

    printfield(buf, 2, 2, CARD16, "sequence number");
    printField (buf, 4, 4, TIMESTAMP, "time");
    printField (buf, 8, 4, WINDOW, "requestor");
    printField (buf, 12, 4, ATOM, "selection");
    printField (buf, 16, 4, ATOM, "target");
    printField (buf, 20, 4, ATOM, "property");
}

void ColormapNotifyEvent(const unsigned char *buf) {
    printField (buf, 0, 1, EVENT, EVENTHEADER); /* ColormapNotify */

    printfield(buf, 2, 2, CARD16, "sequence number");
    printField (buf, 4, 4, WINDOW, "window");
    printField (buf, 8, 4, COLORMAP, "colormap");
    printField (buf, 12, 1, BOOL, "new");
    printField (buf, 13, 1, CMAPCHANGE, "state");
}

void ClientMessageEvent(const unsigned char *buf) {
    printField (buf, 0, 1, EVENT, EVENTHEADER); /* ClientMessage */

    printField (buf, 1, 1, CARD8, "format");
    printfield(buf, 2, 2, CARD16, "sequence number");
    printField (buf, 4, 4, WINDOW, "window");
    printField (buf, 8, 4, ATOM, "type");
    printBytes (&buf[12], (long) 20, "data");
}

void MappingNotifyEvent(const unsigned char *buf) {
    printField (buf, 0, 1, EVENT, EVENTHEADER); /* MappingNotify */

    printfield(buf, 2, 2, CARD16, "sequence number");
    printField (buf, 4, 1, MAPOBJECT, "request");
    printField (buf, 5, 1, KEYCODE, "first-keycode");
    printField (buf, 6, 1, CARD8, "count");
}

void UnknownGenericEvent(const unsigned char *buf) {
    long n;

    printField (buf, 0, 1, EVENT, EVENTHEADER); /* GenericEvent */

    printField (buf, 1, 1, EXTENSION, "extension");
    printfield(buf, 2, 2, CARD16, "sequence number");
    printfield(buf, 4, 4, DVALUE4 (n), "event length");
    printField (buf, 8, 2, CARD16, "event type");

    n = ILong (&buf[4]) + 5;
    (void) printList (&buf[12], n, CARD32, "data");
}

void UnknownEvent(const unsigned char *buf) {
    printField (buf, 0, 1, EVENT, EVENTHEADER);

    printField (buf, 1, 1, CARD8, "detail");
    printfield(buf, 2, 2, CARD16, "sequence number");
    printBytes (&buf[4], 28, "data");
}

/* Request and Reply printing procedures */
void ExtendedRequest(int fd, const unsigned char *buf) {
    short n;

    printField (buf, 0, 1, REQUEST, REQUESTHEADER);

    printField (SBf, 0, 4, CARD32, "sequence number");

    printField (buf, 1, 1, CARD8, "minor opcode");
    printreqlen (buf, fd, DVALUE2 (n - 1));

    n = CS[fd].requestLen - 1;
    (void) printList (&buf[4], n, CARD32, "data");
}

void UnknownReply(const unsigned char *buf) {
    long n;

    printField (RBf, 0, 1, REPLY, REPLYHEADER);

    printField (buf, 1, 1, CARD8, "data");
    printfield(buf, 2, 2, CARD16, "sequence number");
    printfield(buf, 4, 4, DVALUE4 (n), "reply length");
    n = ILong (&buf[4]) + 6;
    (void) printList (&buf[8], n, CARD32, "data");
}

void CreateWindow(FD fd, const unsigned char *buf) {
    /* Request CreateWindow is opcode 1 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* CreateWindow */

    printField (SBf, 0, 4, CARD32, "sequence number");

    printField (buf, 1, 1, CARD8, "depth");
    printreqlen (buf, fd, DVALUE2 (8 + n));
    printField (buf, 4, 4, WINDOW, "wid");
    printField (buf, 8, 4, WINDOW, "parent");
    printField (buf, 12, 2, INT16, "x");
    printField (buf, 14, 2, INT16, "y");
    printField (buf, 16, 2, CARD16, "width");
    printField (buf, 18, 2, CARD16, "height");
    printField (buf, 20, 2, CARD16, "border-width");
    printField (buf, 22, 2, WINDOWCLASS, "class");
    printField (buf, 24, 4, VISUALIDC, "visual");
    printField (buf, 28, 4, WINDOW_BITMASK, "value-mask");
    printValues (&buf[28], 4, WINDOW_BITMASK, &buf[32], "value-list");
}

void ChangeWindowAttributes(FD fd, const unsigned char *buf) {
    /* Request ChangeWindowAttributes is opcode 2 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* ChangeWindowAttributes */

    printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, DVALUE2 (3 + n));
    printField (buf, 4, 4, WINDOW, "window");
    printField (buf, 8, 4, WINDOW_BITMASK, "value-mask");
    printValues (&buf[8], 4, WINDOW_BITMASK, &buf[12], "value-list");
}

void GetWindowAttributes(FD fd, const unsigned char *buf) {
    /* Request GetWindowAttributes is opcode 3 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* GetWindowAttributes */

    printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (2));
    printField (buf, 4, 4, WINDOW, "window");
}

void GetWindowAttributesReply(const unsigned char *buf) {
    printField (RBf, 0, 1, REPLY, REPLYHEADER); /* GetWindowAttributes */

    printField (buf, 1, 1, BACKSTORE, "backing-store");
    printfield(buf, 2, 2, CARD16, "sequence number");
    printfield(buf, 4, 4, CONST4 (3), "reply length");
    printField (buf, 8, 4, VISUALID, "visual");
    printField (buf, 12, 2, WINDOWCLASS, "class");
    printField (buf, 14, 1, BITGRAVITY, "bit-gravity");
    printField (buf, 15, 1, WINGRAVITY, "win-gravity");
    printField (buf, 16, 4, CARD32, "backing-planes");
    printField (buf, 20, 4, CARD32, "backing-pixel");
    printField (buf, 24, 1, BOOL, "save-under");
    printField (buf, 25, 1, BOOL, "map-is-installed");
    printField (buf, 26, 1, MAPSTATE, "map-state");
    printField (buf, 27, 1, BOOL, "override-redirect");
    printField (buf, 28, 4, COLORMAP, "colormap");
    printField (buf, 32, 4, SETofEVENT, "all-event-masks");
    printField (buf, 36, 4, SETofEVENT, "your-event-mask");
    printField (buf, 40, 2, SETofDEVICEEVENT, "do-not-propagate-mask");
}

void DestroyWindow(FD fd, const unsigned char *buf) {
    /* Request DestroyWindow is opcode 4 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* DestroyWindow */

    printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (2));
    printField (buf, 4, 4, WINDOW, "window");
}

void DestroySubwindows(FD fd, const unsigned char *buf) {
    /* Request DestroySubwindows is opcode 5 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* DestroySubwindows */

    printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (2));
    printField (buf, 4, 4, WINDOW, "window");
}

void ChangeSaveSet(FD fd, const unsigned char *buf) {
    /* Request ChangeSaveSet is opcode 6 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* ChangeSaveSet */

    printField (SBf, 0, 4, CARD32, "sequence number");

    printField (buf, 1, 1, INS_DEL, "mode");
    printreqlen (buf, fd, CONST2 (2));
    printField (buf, 4, 4, WINDOW, "window");
}

void ReparentWindow(FD fd, const unsigned char *buf) {
    /* Request ReparentWindow is opcode 7 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* ReparentWindow */

    printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (4));
    printField (buf, 4, 4, WINDOW, "window");
    printField (buf, 8, 4, WINDOW, "parent");
    printField (buf, 12, 2, INT16, "x");
    printField (buf, 14, 2, INT16, "y");
}

void MapWindow(FD fd, const unsigned char *buf) {
    /* Request MapWindow is opcode 8 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* MapWindow */

    printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (2));
    printField (buf, 4, 4, WINDOW, "window");
}

void MapSubwindows(FD fd, const unsigned char *buf) {
    /* Request MapSubwindows is opcode 9 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* MapSubwindows */

    printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (2));
    printField (buf, 4, 4, WINDOW, "window");
}

void UnmapWindow(FD fd, const unsigned char *buf) {
    /* Request UnmapWindow is opcode 10 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* UnmapWindow */

    printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (2));
    printField (buf, 4, 4, WINDOW, "window");
}

void UnmapSubwindows(FD fd, const unsigned char *buf) {
    /* Request UnmapSubwindows is opcode 11 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* UnmapSubwindows */

    printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (2));
    printField (buf, 4, 4, WINDOW, "window");
}

void ConfigureWindow(FD fd, const unsigned char *buf) {
    /* Request ConfigureWindow is opcode 12 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* ConfigureWindow */

    printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, DVALUE2 (3 + n));
    printField (buf, 4, 4, WINDOW, "window");
    printField (buf, 8, 2, CONFIGURE_BITMASK, "value-mask");
    printValues (&buf[8], 2, CONFIGURE_BITMASK, &buf[12], "value-list");
}

void CirculateWindow(FD fd, const unsigned char *buf) {
    /* Request CirculateWindow is opcode 13 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* CirculateWindow */

    printField (SBf, 0, 4, CARD32, "sequence number");

    printField (buf, 1, 1, CIRMODE, "direction");
    printreqlen (buf, fd, CONST2 (2));
    printField (buf, 4, 4, WINDOW, "window");
}

void GetGeometry(FD fd, const unsigned char *buf) {
    /* Request GetGeometry is opcode 14 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* GetGeometry */

    printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (2));
    printField (buf, 4, 4, DRAWABLE, "drawable");
}

void GetGeometryReply(const unsigned char *buf) {
    printField (RBf, 0, 1, REPLY, REPLYHEADER); /* GetGeometry */

    printField (buf, 1, 1, CARD8, "depth");
    printfield(buf, 2, 2, CARD16, "sequence number");
    printfield(buf, 4, 4, CONST4 (0), "reply length");
    printField (buf, 8, 4, WINDOW, "root");
    printField (buf, 12, 2, INT16, "x");
    printField (buf, 14, 2, INT16, "y");
    printField (buf, 16, 2, CARD16, "width");
    printField (buf, 18, 2, CARD16, "height");
    printField (buf, 20, 2, CARD16, "border-width");
}

void QueryTree(FD fd, const unsigned char *buf) {
    /* Request QueryTree is opcode 15 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* QueryTree */

    printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (2));
    printField (buf, 4, 4, WINDOW, "window");
}

void QueryTreeReply(const unsigned char *buf) {
    short n;

    printField (RBf, 0, 1, REPLY, REPLYHEADER); /* QueryTree */

    printfield(buf, 2, 2, CARD16, "sequence number");
    printfield(buf, 4, 4, DVALUE4 (n), "reply length");
    printField (buf, 8, 4, WINDOW, "root");
    printField (buf, 12, 4, WINDOW, "parent");
    printfield(buf, 16, 2, DVALUE2 (n), "number of children");
    n = IShort (&buf[16]);
    printList (&buf[32], (long) n, WINDOW, "children");
}

/* Keep track of InternAtom & GetAtomName requests so we can add them to
   our tables */
struct atomic_req {
    uint32_t seq;
    uint32_t atom;
    char *name;
    struct atomic_req *next;
};

static struct atomic_req *pending_atom_reqs;

static void start_atom_request(uint32_t atom, char *name) {
    struct atomic_req *new_ar = malloc (sizeof (struct atomic_req));

    if (new_ar) {
        new_ar->seq = ILong (SBf);
        new_ar->atom = atom;
        new_ar->name = name;
        new_ar->next = NULL;

        if (pending_atom_reqs == NULL)
            pending_atom_reqs = new_ar;
        else {
            struct atomic_req *ar;
            for (ar = pending_atom_reqs; ar->next != NULL; ar = ar->next) {
                /* find list tail */
            }
            ar->next = new_ar;
        }
    }
}

static void finish_atom_request(uint32_t seq, uint32_t atom, char *name) {
    struct atomic_req *ar, *par, *next;

    for (ar = pending_atom_reqs, par = NULL; ar != NULL; ar = next) {
        next = ar->next;
        if (ar->seq == seq) {
            if (ar->atom == 0)
                ar->atom = atom;
            if (ar->name == NULL)
                ar->name = name;
            DefineAtom (ar->atom, ar->name);
            free (ar->name); /* DefineAtom makes a copy if needed */
            free (ar);
            if (par == NULL)
                pending_atom_reqs = next;
            else
                par->next = next;
        } else
            par = ar;
    }
}

void InternAtom(FD fd, const unsigned char *buf) {
    short n;

    /* Request InternAtom is opcode 16 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* InternAtom */

    printField (SBf, 0, 4, CARD32, "sequence number");

    printField (buf, 1, 1, BOOL, "only-if-exists");
    printreqlen (buf, fd, DVALUE2 (2 + (n + p) / 4));
    printfield(buf, 4, 2, DVALUE2 (n), "length of name");
    n = IShort (&buf[4]);
    printString8 (&buf[8], n, "name");

    if (n > 0) {
        char *name = malloc (n + 1);
        if (name != NULL) {
            memcpy (name, buf + 8, n);
            name[n] = 0;
            start_atom_request (0, name);
        }
    }
}

void InternAtomReply(const unsigned char *buf) {
    uint32_t seq, atom;

    printField (RBf, 0, 1, REPLY, REPLYHEADER); /* InternAtom */

    printfield(buf, 2, 2, CARD16, "sequence number");
    printfield(buf, 4, 4, CONST4 (0), "reply length");
    printField (buf, 8, 4, ATOM, "atom");

    seq = IShort (&buf[2]);
    atom = ILong (&buf[8]);
    finish_atom_request (seq, atom, NULL);
}

void GetAtomName(FD fd, const unsigned char *buf) {
    uint32_t atom;

    /* Request GetAtomName is opcode 17 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* GetAtomName */

    printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (2));
    printField (buf, 4, 4, ATOM, "atom");

    atom = ILong (&buf[4]);
    start_atom_request (atom, NULL);
}

void GetAtomNameReply(const unsigned char *buf) {
    short n;
    uint32_t seq;
    char *name;

    printField (RBf, 0, 1, REPLY, REPLYHEADER); /* GetAtomName */

    printfield(buf, 2, 2, CARD16, "sequence number");
    printfield(buf, 4, 4, DVALUE4 ((n + p) / 4), "reply length");
    printfield(buf, 8, 2, DVALUE2 (n), "length of name");
    n = IShort (&buf[8]);
    printString8 (&buf[32], n, "name");

    seq = IShort (&buf[2]);
    name = malloc (n + 1);
    if (name != NULL) {
        memcpy (name, buf + 32, n);
        name[n] = 0;
    }
    finish_atom_request (seq, 0, name);
}

void ChangeProperty(FD fd, const unsigned char *buf) {
    uint32_t n;
    uint8_t unit;
    uint32_t type;

    /* Request ChangeProperty is opcode 18 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* ChangeProperty */

    printField (SBf, 0, 4, CARD32, "sequence number");

    printField (buf, 1, 1, CHANGEMODE, "mode");
    printreqlen (buf, fd, DVALUE2 (6 + (n + p) / 4));
    printField (buf, 4, 4, WINDOW, "window");
    printField (buf, 8, 4, ATOM, "property");
    printField (buf, 12, 4, ATOM, "type");
    type = ILong (&buf[12]);
    printField (buf, 16, 1, CARD8, "format");
    unit = IByte (&buf[16]) / 8;
    printfield(buf, 20, 4, CARD32, "length of data");
    n = ILong (&buf[20]);
    printPropertyValues (&buf[24], type, unit, n, "data");
}

void DeleteProperty(FD fd, const unsigned char *buf) {
    /* Request DeleteProperty is opcode 19 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* DeleteProperty */

    printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (3));
    printField (buf, 4, 4, WINDOW, "window");
    printField (buf, 8, 4, ATOM, "property");
}

void GetProperty(FD fd, const unsigned char *buf) {
    /* Request GetProperty is opcode 20 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* GetProperty */

    printField (SBf, 0, 4, CARD32, "sequence number");

    printField (buf, 1, 1, BOOL, "delete");
    printreqlen (buf, fd, CONST2 (6));
    printField (buf, 4, 4, WINDOW, "window");
    printField (buf, 8, 4, ATOM, "property");
    printField (buf, 12, 4, ATOMT, "type");
    printField (buf, 16, 4, CARD32, "long-offset");
    printfield(buf, 20, 4, CARD32, "long-length");
}

void GetPropertyReply(const unsigned char *buf) {
    long n;
    short unit;
    long type;

    printField (RBf, 0, 1, REPLY, REPLYHEADER); /* GetProperty */

    printField (buf, 1, 1, CARD8, "format");
    unit = IByte (&buf[1]) / 8;
    printfield(buf, 2, 2, CARD16, "sequence number");
    printfield(buf, 4, 4, DVALUE4 ((n + p) / 4), "reply length");
    printField (buf, 8, 4, ATOM, "type");
    type = ILong (&buf[8]);
    printField (buf, 12, 4, CARD32, "bytes-after");
    printfield(buf, 16, 4, CARD32, "length of value");
    n = ILong (&buf[16]);
    printPropertyValues (&buf[32], type, unit, n, "value");
}

void ListProperties(FD fd, const unsigned char *buf) {
    /* Request ListProperties is opcode 21 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* ListProperties */

    printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (2));
    printField (buf, 4, 4, WINDOW, "window");
}

void ListPropertiesReply(const unsigned char *buf) {
    short n;

    printField (RBf, 0, 1, REPLY, REPLYHEADER); /* ListProperties */

    printfield(buf, 2, 2, CARD16, "sequence number");
    printfield(buf, 4, 4, DVALUE4 (n), "reply length");
    printfield(buf, 8, 2, DVALUE2 (n), "number of atoms");
    n = IShort (&buf[8]);
    printList (&buf[32], (long) n, ATOM, "atoms");
}

void SetSelectionOwner(FD fd, const unsigned char *buf) {
    /* Request SetSelectionOwner is opcode 22 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* SetSelectionOwner */

    printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (4));
    printField (buf, 4, 4, WINDOW, "owner");
    printField (buf, 8, 4, ATOM, "selection");
    printField (buf, 12, 4, TIMESTAMP, "time");
}

void GetSelectionOwner(FD fd, const unsigned char *buf) {
    /* Request GetSelectionOwner is opcode 23 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* GetSelectionOwner */

    printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (2));
    printField (buf, 4, 4, ATOM, "selection");
}

void GetSelectionOwnerReply(const unsigned char *buf) {
    printField (RBf, 0, 1, REPLY, REPLYHEADER); /* GetSelectionOwner */

    printfield(buf, 2, 2, CARD16, "sequence number");
    printfield(buf, 4, 4, CONST4 (0), "reply length");
    printField (buf, 8, 4, WINDOW, "owner");
}

void ConvertSelection(FD fd, const unsigned char *buf) {
    /* Request ConvertSelection is opcode 24 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* ConvertSelection */

    printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (6));
    printField (buf, 4, 4, WINDOW, "requestor");
    printField (buf, 8, 4, ATOM, "selection");
    printField (buf, 12, 4, ATOM, "target");
    printField (buf, 16, 4, ATOM, "property");
    printField (buf, 20, 4, TIMESTAMP, "time");
}

void SendEvent(FD fd, const unsigned char *buf) {
    /* Request SendEvent is opcode 25 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* SendEvent */

    printField (SBf, 0, 4, CARD32, "sequence number");

    printField (buf, 1, 1, BOOL, "propagate");
    printreqlen (buf, fd, CONST2 (11));
    printField (buf, 4, 4, WINDOWD, "destination");
    printField (buf, 8, 4, SETofEVENT, "event-mask");
    printField (buf, 12, 32, EVENTFORM, "event");
}

void GrabPointer(FD fd, const unsigned char *buf) {
    /* Request GrabPointer is opcode 26 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* GrabPointer */

    printField (SBf, 0, 4, CARD32, "sequence number");

    printField (buf, 1, 1, BOOL, "owner-events");
    printreqlen (buf, fd, CONST2 (6));
    printField (buf, 4, 4, WINDOW, "grab-window");
    printField (buf, 8, 2, SETofPOINTEREVENT, "event-mask");
    printField (buf, 10, 1, PK_MODE, "pointer-mode");
    printField (buf, 11, 1, PK_MODE, "keyboard-mode");
    printField (buf, 12, 4, WINDOW, "confine-to");
    printField (buf, 16, 4, CURSOR, "cursor");
    printField (buf, 20, 4, TIMESTAMP, "time");
}

void GrabPointerReply(const unsigned char *buf) {
    printField (RBf, 0, 1, REPLY, REPLYHEADER); /* GrabPointer */

    printField (buf, 1, 1, GRABSTAT, "status");
    printfield(buf, 2, 2, CARD16, "sequence number");
    printfield(buf, 4, 4, CONST4 (0), "reply length");
}

void UngrabPointer(FD fd, const unsigned char *buf) {
    /* Request UngrabPointer is opcode 27 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* UngrabPointer */

    printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (2));
    printField (buf, 4, 4, TIMESTAMP, "time");
}

void GrabButton(FD fd, const unsigned char *buf) {
    /* Request GrabButton is opcode 28 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* GrabButton */

    printField (SBf, 0, 4, CARD32, "sequence number");

    printField (buf, 1, 1, BOOL, "owner-events");
    printreqlen (buf, fd, CONST2 (6));
    printField (buf, 4, 4, WINDOW, "grab-window");
    printField (buf, 8, 2, SETofPOINTEREVENT, "event-mask");
    printField (buf, 10, 1, PK_MODE, "pointer-mode");
    printField (buf, 11, 1, PK_MODE, "keyboard-mode");
    printField (buf, 12, 4, WINDOW, "confine-to");
    printField (buf, 16, 4, CURSOR, "cursor");
    printField (buf, 20, 1, BUTTONA, "button");
    printField (buf, 22, 2, SETofKEYMASK, "modifiers");
}

void UngrabButton(FD fd, const unsigned char *buf) {
    /* Request UngrabButton is opcode 29 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* UngrabButton */

    printField (SBf, 0, 4, CARD32, "sequence number");

    printField (buf, 1, 1, BUTTONA, "button");
    printreqlen (buf, fd, CONST2 (3));
    printField (buf, 4, 4, WINDOW, "grab-window");
    printField (buf, 8, 2, SETofKEYMASK, "modifiers");
}

void ChangeActivePointerGrab(FD fd, const unsigned char *buf) {
    /* Request ChangeActivePointerGrab is opcode 30 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* ChangeActivePointerGrab */

    printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (4));
    printField (buf, 4, 4, CURSOR, "cursor");
    printField (buf, 8, 4, TIMESTAMP, "time");
    printField (buf, 12, 2, SETofPOINTEREVENT, "event-mask");
}

void GrabKeyboard(FD fd, const unsigned char *buf) {
    /* Request GrabKeyboard is opcode 31 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* GrabKeyboard */

    printField (SBf, 0, 4, CARD32, "sequence number");

    printField (buf, 1, 1, BOOL, "owner-events");
    printreqlen (buf, fd, CONST2 (4));
    printField (buf, 4, 4, WINDOW, "grab-window");
    printField (buf, 8, 4, TIMESTAMP, "time");
    printField (buf, 12, 1, PK_MODE, "pointer-mode");
    printField (buf, 13, 1, PK_MODE, "keyboard-mode");
}

void GrabKeyboardReply(const unsigned char *buf) {
    printField (RBf, 0, 1, REPLY, REPLYHEADER); /* GrabKeyboard */

    printField (buf, 1, 1, GRABSTAT, "status");
    printfield(buf, 2, 2, CARD16, "sequence number");
    printfield(buf, 4, 4, CONST4 (0), "reply length");
}

void UngrabKeyboard(FD fd, const unsigned char *buf) {
    /* Request UngrabKeyboard is opcode 32 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* UngrabKeyboard */

    printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (2));
    printField (buf, 4, 4, TIMESTAMP, "time");
}

void GrabKey(FD fd, const unsigned char *buf) {
    /* Request GrabKey is opcode 33 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* GrabKey */

    printField (SBf, 0, 4, CARD32, "sequence number");

    printField (buf, 1, 1, BOOL, "owner-events");
    printreqlen (buf, fd, CONST2 (4));
    printField (buf, 4, 4, WINDOW, "grab-window");
    printField (buf, 8, 2, SETofKEYMASK, "modifiers");
    printField (buf, 10, 1, KEYCODEA, "key");
    printField (buf, 11, 1, PK_MODE, "pointer-mode");
    printField (buf, 12, 1, PK_MODE, "keyboard-mode");
}

void UngrabKey(FD fd, const unsigned char *buf) {
    /* Request UngrabKey is opcode 34 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* UngrabKey */

    printField (SBf, 0, 4, CARD32, "sequence number");

    printField (buf, 1, 1, KEYCODEA, "key");
    printreqlen (buf, fd, CONST2 (3));
    printField (buf, 4, 4, WINDOW, "grab-window");
    printField (buf, 8, 2, SETofKEYMASK, "modifiers");
}

void AllowEvents(FD fd, const unsigned char *buf) {
    /* Request AllowEvents is opcode 35 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* AllowEvents */

    printField (SBf, 0, 4, CARD32, "sequence number");

    printField (buf, 1, 1, EVENTMODE, "mode");
    printreqlen (buf, fd, CONST2 (2));
    printField (buf, 4, 4, TIMESTAMP, "time");
}

void GrabServer(FD fd, const unsigned char *buf) {
    /* Request GrabServer is opcode 36 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* GrabServer */

    printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (1));
}

void UngrabServer(FD fd, const unsigned char *buf) {
    /* Request UngrabServer is opcode 37 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* UngrabServer */

    printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (1));
}

void QueryPointer(FD fd, const unsigned char *buf) {
    /* Request QueryPointer is opcode 38 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* QueryPointer */

    printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (2));
    printField (buf, 4, 4, WINDOW, "window");
}

void QueryPointerReply(const unsigned char *buf) {
    printField (RBf, 0, 1, REPLY, REPLYHEADER); /* QueryPointer */

    printField (buf, 1, 1, BOOL, "same-screen");
    printfield(buf, 2, 2, CARD16, "sequence number");
    printfield(buf, 4, 4, CONST4 (0), "reply length");
    printField (buf, 8, 4, WINDOW, "root");
    printField (buf, 12, 4, WINDOW, "child");
    printField (buf, 16, 2, INT16, "root-x");
    printField (buf, 18, 2, INT16, "root-y");
    printField (buf, 20, 2, INT16, "win-x");
    printField (buf, 22, 2, INT16, "win-y");
    printField (buf, 24, 2, SETofKEYBUTMASK, "mask");
}

void GetMotionEvents(FD fd, const unsigned char *buf) {
    /* Request GetMotionEvents is opcode 39 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* GetMotionEvents */

    printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (4));
    printField (buf, 4, 4, WINDOW, "window");
    printField (buf, 8, 4, TIMESTAMP, "start");
    printField (buf, 12, 4, TIMESTAMP, "stop");
}

void GetMotionEventsReply(const unsigned char *buf) {
    long n;

    printField (RBf, 0, 1, REPLY, REPLYHEADER); /* GetMotionEvents */

    printfield(buf, 2, 2, CARD16, "sequence number");
    printfield(buf, 4, 4, DVALUE4 (2 * n), "reply length");
    printfield(buf, 8, 4, DVALUE4 (n), "number of events");
    n = ILong (&buf[8]);
    printList (&buf[32], n, TIMECOORD, "events");
}

void TranslateCoordinates(FD fd, const unsigned char *buf) {
    /* Request TranslateCoordinates is opcode 40 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* TranslateCoordinates */

    printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (4));
    printField (buf, 4, 4, WINDOW, "src-window");
    printField (buf, 8, 4, WINDOW, "dst-window");
    printField (buf, 12, 2, INT16, "src-x");
    printField (buf, 14, 2, INT16, "src-y");
}

void TranslateCoordinatesReply(const unsigned char *buf) {
    printField (RBf, 0, 1, REPLY, REPLYHEADER); /* TranslateCoordinates */

    printField (buf, 1, 1, BOOL, "same-screen");
    printfield(buf, 2, 2, CARD16, "sequence number");
    printfield(buf, 4, 4, CONST4 (0), "reply length");
    printField (buf, 8, 4, WINDOW, "child");
    printField (buf, 12, 2, INT16, "dst-x");
    printField (buf, 14, 2, INT16, "dst-y");
}

void WarpPointer(FD fd, const unsigned char *buf) {
    /* Request WarpPointer is opcode 41 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* WarpPointer */

    printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (6));
    printField (buf, 4, 4, WINDOW, "src-window");
    printField (buf, 8, 4, WINDOW, "dst-window");
    printField (buf, 12, 2, INT16, "src-x");
    printField (buf, 14, 2, INT16, "src-y");
    printField (buf, 16, 2, CARD16, "src-width");
    printField (buf, 18, 2, CARD16, "src-height");
    printField (buf, 20, 2, INT16, "dst-x");
    printField (buf, 22, 2, INT16, "dst-y");
}

void SetInputFocus(FD fd, const unsigned char *buf) {
    /* Request SetInputFocus is opcode 42 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* SetInputFocus */

    printField (SBf, 0, 4, CARD32, "sequence number");

    printField (buf, 1, 1, FOCUSAGENT, "revert-to");
    printreqlen (buf, fd, CONST2 (3));
    printField (buf, 4, 4, WINDOWNR, "focus");
    printField (buf, 8, 4, TIMESTAMP, "time");
}

void GetInputFocus(FD fd, const unsigned char *buf) {
    /* Request GetInputFocus is opcode 43 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* GetInputFocus */

    printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (1));
}

void GetInputFocusReply(const unsigned char *buf) {
    printField (RBf, 0, 1, REPLY, REPLYHEADER); /* GetInputFocus */
    if (Verbose < 1)
        return;
    printField (buf, 1, 1, FOCUSAGENT, "revert-to");
    printfield(buf, 2, 2, CARD16, "sequence number");
    printfield(buf, 4, 4, CONST4 (0), "reply length");
    printField (buf, 8, 4, WINDOWNR, "focus");
}

void QueryKeymap(FD fd, const unsigned char *buf) {
    /* Request QueryKeymap is opcode 44 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* QueryKeymap */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (1));
}

void QueryKeymapReply(const unsigned char *buf) {
    printField (RBf, 0, 1, REPLY, REPLYHEADER); /* QueryKeymap */
    if (Verbose < 1)
        return;
    printfield(buf, 2, 2, CARD16, "sequence number");
    printfield(buf, 4, 4, CONST4 (2), "reply length");
    printBytes (&buf[8], 32L, "keys");
}

void OpenFont(FD fd, const unsigned char *buf) {
    short n;

    /* Request OpenFont is opcode 45 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* OpenFont */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, DVALUE2 (3 + (n + p) / 4));
    printField (buf, 4, 4, FONT, "font-id");
    printfield(buf, 8, 2, DVALUE2 (n), "length of name");
    n = IShort (&buf[8]);
    printString8 (&buf[12], n, "name");
}

void CloseFont(FD fd, const unsigned char *buf) {
    /* Request CloseFont is opcode 46 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* CloseFont */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (2));
    printField (buf, 4, 4, FONT, "font");
}

void QueryFont(FD fd, const unsigned char *buf) {
    /* Request QueryFont is opcode 47 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* QueryFont */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (2));
    printField (buf, 4, 4, FONTABLE, "font");
}

void QueryFontReply(const unsigned char *buf) {
    short n;
    long m;
    long k;

    printField (RBf, 0, 1, REPLY, REPLYHEADER); /* QueryFont */
    if (Verbose < 1)
        return;
    printfield(buf, 2, 2, CARD16, "sequence number");
    printfield(buf, 4, 4, DVALUE4 (7 + 2 * n + 3 * m), "reply length");
    printField (buf, 8, 12, CHARINFO, "min-bounds");
    printField (buf, 24, 12, CHARINFO, "max-bounds");
    printField (buf, 40, 2, CARD16, "min-char-or-byte2");
    printField (buf, 42, 2, CARD16, "max-char-or-byte2");
    printField (buf, 44, 2, CARD16, "default-char");
    printfield(buf, 46, 2, DVALUE2 (n), "number of FONTPROPs");
    n = IShort (&buf[46]);
    printField (buf, 48, 1, DIRECT, "draw-direction");
    printField (buf, 49, 1, CARD8, "min-byte1");
    printField (buf, 50, 1, CARD8, "max-byte1");
    printField (buf, 51, 1, BOOL, "all-chars-exist");
    printField (buf, 52, 2, INT16, "font-ascent");
    printField (buf, 54, 2, INT16, "font-descent");
    printfield(buf, 56, 4, DVALUE4 (m), "number of CHARINFOs");
    m = ILong (&buf[56]);
    k = printList (&buf[60], (long) n, FONTPROP, "properties");
    printList (&buf[60 + k], (long) m, CHARINFO, "char-infos");
}

void QueryTextExtents(FD fd, const unsigned char *buf) {
    uint32_t n;

    /* Request QueryTextExtents is opcode 48 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* QueryTextExtents */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printfield(buf, 1, 1, BOOL, "odd length?");
    n = (getreqlen (fd, buf) - 2) * 4 / 2;
    printreqlen (buf, fd, DVALUE2 (2 + (2 * n + p) / 4));
    if (IBool (&buf[1]))
        n -= 1;
    printField (buf, 4, 4, FONTABLE, "font");
    printString16 (&buf[8], n, "string");
}

void QueryTextExtentsReply(const unsigned char *buf) {
    printField (RBf, 0, 1, REPLY, REPLYHEADER); /* QueryTextExtents */
    if (Verbose < 1)
        return;
    printField (buf, 1, 1, DIRECT, "draw-direction");
    printfield(buf, 2, 2, CARD16, "sequence number");
    printfield(buf, 4, 4, CONST4 (0), "reply length");
    printField (buf, 8, 2, INT16, "font-ascent");
    printField (buf, 10, 2, INT16, "font-descent");
    printField (buf, 12, 2, INT16, "overall-ascent");
    printField (buf, 14, 2, INT16, "overall-descent");
    printField (buf, 16, 4, INT32, "overall-width");
    printField (buf, 20, 4, INT32, "overall-left");
    printField (buf, 24, 4, INT32, "overall-right");
}

void ListFonts(FD fd, const unsigned char *buf) {
    short n;

    /* Request ListFonts is opcode 49 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* ListFonts */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, DVALUE2 (2 + (n + p) / 4));
    printField (buf, 4, 2, CARD16, "max-names");
    printfield(buf, 6, 2, DVALUE2 (n), "length of pattern");
    n = IShort (&buf[6]);
    printString8 (&buf[8], n, "pattern");
}

void ListFontsReply(const unsigned char *buf) {
    short n;

    printField (RBf, 0, 1, REPLY, REPLYHEADER); /* ListFonts */
    if (Verbose < 1)
        return;
    printfield(buf, 2, 2, CARD16, "sequence number");
    printfield(buf, 4, 4, DVALUE4 ((n + p) / 4), "reply length");
    printfield(buf, 8, 2, CARD16, "number of names");
    n = IShort (&buf[8]);
    printListSTR (&buf[32], (long) n, "names");
}

void ListFontsWithInfo(FD fd, const unsigned char *buf) {
    short n;

    /* Request ListFontsWithInfo is opcode 50 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* ListFontsWithInfo */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, DVALUE2 (2 + (n + p) / 4));
    printField (buf, 4, 2, CARD16, "max-names");
    printfield(buf, 6, 2, DVALUE2 (n), "length of pattern");
    n = IShort (&buf[6]);
    printString8 (&buf[8], n, "pattern");
}

void ListFontsWithInfoReply(const unsigned char *buf) {
    short which;

    printField (RBf, 0, 1, REPLY, REPLYHEADER); /* ListFontsWithInfo */
    if (Verbose < 1)
        return;
    which = IByte (&buf[1]);
    if (which != 0) {
        ListFontsWithInfoReply1 (buf);
        KeepLastReplyExpected ();
    } else
        ListFontsWithInfoReply2 (buf);
}

static void ListFontsWithInfoReply1(const unsigned char *buf) {
    short n;
    short m;

    printfield(buf, 1, 1, DVALUE1 (n), "length of name in bytes");
    n = IByte (&buf[1]);
    printfield(buf, 2, 2, CARD16, "sequence number");
    printfield(buf, 4, 4, DVALUE4 (7 + 2 * m + (n + p) / 4), "reply length");
    printField (buf, 8, 12, CHARINFO, "min-bounds");
    printField (buf, 24, 12, CHARINFO, "max-bounds");
    printField (buf, 40, 2, CARD16, "min-char-or-byte2");
    printField (buf, 42, 2, CARD16, "max-char-or-byte2");
    printField (buf, 44, 2, CARD16, "default-char");
    printfield(buf, 46, 2, DVALUE2 (m), "number of FONTPROPs");
    m = IShort (&buf[46]);
    printField (buf, 48, 1, DIRECT, "draw-direction");
    printField (buf, 49, 1, CARD8, "min-byte1");
    printField (buf, 50, 1, CARD8, "max-byte1");
    printField (buf, 51, 1, BOOL, "all-chars-exist");
    printField (buf, 52, 2, INT16, "font-ascent");
    printField (buf, 54, 2, INT16, "font-descent");
    printField (buf, 56, 4, CARD32, "replies-hint");
    printList (&buf[60], (long) m, FONTPROP, "properties");
    printString8 (&buf[60 + 8 * m], n, "name");
}

static void ListFontsWithInfoReply2(const unsigned char *buf) {
    printField (buf, 1, 1, CONST1 (0), "last-reply indicator");
    printfield(buf, 2, 2, CARD16, "sequence number");
    printfield(buf, 4, 4, CONST4 (7), "reply length");
}

void SetFontPath(FD fd, const unsigned char *buf) {
    short n;

    /* Request SetFontPath is opcode 51 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* SetFontPath */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, DVALUE2 (2 + (n + p) / 4));
    printfield(buf, 4, 2, CARD16, "number of paths");
    n = IShort (&buf[4]);
    printListSTR (&buf[8], (long) n, "paths");
}

void GetFontPath(FD fd, const unsigned char *buf) {
    /* Request GetFontPath is opcode 52 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* GetFontPath */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printField (buf, 2, 2, CONST2 (1), "request list");
}

void GetFontPathReply(const unsigned char *buf) {
    short n;

    printField (RBf, 0, 1, REPLY, REPLYHEADER); /* GetFontPath */
    if (Verbose < 1)
        return;
    printfield(buf, 2, 2, CARD16, "sequence number");
    printfield(buf, 4, 4, DVALUE4 ((n + p) / 4), "reply length");
    printfield(buf, 8, 2, CARD16, "number of paths");

    n = IShort (&buf[8]);
    printListSTR (&buf[32], (long) n, "paths");
}

void CreatePixmap(FD fd, const unsigned char *buf) {
    /* Request CreatePixmap is opcode 53 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* CreatePixmap */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printField (buf, 1, 1, CARD8, "depth");
    printreqlen (buf, fd, CONST2 (4));
    printField (buf, 4, 4, PIXMAP, "pixmap-id");
    printField (buf, 8, 4, DRAWABLE, "drawable");
    printField (buf, 12, 2, CARD16, "width");
    printField (buf, 14, 2, CARD16, "height");
}

void FreePixmap(FD fd, const unsigned char *buf) {
    /* Request FreePixmap is opcode 54 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* FreePixmap */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (2));
    printField (buf, 4, 4, PIXMAP, "pixmap");
}

static const uint32_t GCDefaults[] = {3,                          /* function GXcopy */
                                      (uint32_t) ~0,              /* planemask */
                                      0,                          /* foreground */
                                      1,                          /* background */
                                      0,                          /* line width */
                                      0,                          /* line style Solid */
                                      1,                          /* cap style Butt */
                                      0,                          /* join style Miter */
                                      0,                          /* fill style Solid */
                                      0,                          /* fill rule EvenOdd */
                                      0,                          /* tile */
                                      0,                          /* stipple */
                                      0,                          /* ts org x */
                                      0,                          /* ts org y */
                                      0,                          /* font */
                                      0,                          /* sub window mode ClipByChildren */
                                      1,                          /* graphics expose True */
                                      0,                          /* clip x org */
                                      0,                          /* clip y org */
                                      0,                          /* clip mask */
                                      0,                          /* dash offset */
                                      4,                          /* dashes */
                                      1,                          /* arc mode PieSlice */
};

void CreateGC(FD fd, const unsigned char *buf) {
    CreateValueRec (ILong (buf + 4), 23, GCDefaults);
    SetValueRec (ILong (buf + 4), &buf[12], 4, GC_BITMASK, &buf[16]);

    /* Request CreateGC is opcode 55 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* CreateGC */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, DVALUE2 (4 + n));
    printField (buf, 4, 4, GCONTEXT, "graphic-context-id");
    printField (buf, 8, 4, DRAWABLE, "drawable");
    printField (buf, 12, 4, GC_BITMASK, "value-mask");
    printValues (&buf[12], 4, GC_BITMASK, &buf[16], "value-list");
}

void ChangeGC(FD fd, const unsigned char *buf) {
    SetValueRec (ILong (buf + 4), &buf[8], 4, GC_BITMASK, &buf[12]);

    /* Request ChangeGC is opcode 56 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* ChangeGC */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, DVALUE2 (3 + n));
    printField (buf, 4, 4, GCONTEXT, "gc");
    printField (buf, 8, 4, GC_BITMASK, "value-mask");
    printValues (&buf[8], 4, GC_BITMASK, &buf[12], "value-list");
}

void CopyGC(FD fd, const unsigned char *buf) {
    /* Request CopyGC is opcode 57 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* CopyGC */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (4));
    printField (buf, 4, 4, GCONTEXT, "src-gc");
    printField (buf, 8, 4, GCONTEXT, "dst-gc");
    printField (buf, 12, 4, GC_BITMASK, "value-mask");
}

void SetDashes(FD fd, const unsigned char *buf) {
    short n;

    /* Request SetDashes is opcode 58 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* SetDashes */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, DVALUE2 (3 + (n + p) / 4));
    printField (buf, 4, 4, GCONTEXT, "gc");
    printField (buf, 8, 2, CARD16, "dash-offset");
    printfield(buf, 10, 2, DVALUE2 (n), "length of dashes");
    n = IShort (&buf[10]);
    printBytes (&buf[12], (long) n, "dashes");
}

void SetClipRectangles(FD fd, const unsigned char *buf) {
    uint32_t n;

    /* Request SetClipRectangles is opcode 59 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* SetClipRectangles */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printField (buf, 1, 1, RECTORDER, "ordering");
    n = (getreqlen (fd, buf) - 3) / 2;
    printreqlen (buf, fd, DVALUE2 (3 + 2 * n));
    printField (buf, 4, 4, GCONTEXT, "gc");
    printField (buf, 8, 2, INT16, "clip-x-origin");
    printField (buf, 10, 2, INT16, "clip-y-origin");
    printList (&buf[12], (long) n, RECTANGLE, "rectangles");
}

void FreeGC(FD fd, const unsigned char *buf) {
    DeleteValueRec (ILong (&buf[4]));

    /* Request FreeGC is opcode 60 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* FreeGC */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (2));
    printField (buf, 4, 4, GCONTEXT, "gc");
}

void ClearArea(FD fd, const unsigned char *buf) {
    /* Request ClearArea is opcode 61 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* ClearArea */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printField (buf, 1, 1, BOOL, "exposures");
    printreqlen (buf, fd, CONST2 (4));
    printField (buf, 4, 4, WINDOW, "window");
    printField (buf, 8, 2, INT16, "x");
    printField (buf, 10, 2, INT16, "y");
    printField (buf, 12, 2, CARD16, "width");
    printField (buf, 14, 2, CARD16, "height");
}

void CopyArea(FD fd, const unsigned char *buf) {
    /* Request CopyArea is opcode 62 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* CopyArea */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (7));
    printField (buf, 4, 4, DRAWABLE, "src-drawable");
    printField (buf, 8, 4, DRAWABLE, "dst-drawable");
    printField (buf, 12, 4, GCONTEXT, "gc");
    if (Verbose > 2)
        printValueRec (ILong (&buf[12]), GC_function | GC_plane_mask | GC_graphics_exposures, GC_BITMASK);
    printField (buf, 16, 2, INT16, "src-x");
    printField (buf, 18, 2, INT16, "src-y");
    printField (buf, 20, 2, INT16, "dst-x");
    printField (buf, 22, 2, INT16, "dst-y");
    printField (buf, 24, 2, CARD16, "width");
    printField (buf, 26, 2, CARD16, "height");
}

void CopyPlane(FD fd, const unsigned char *buf) {
    /* Request CopyPlane is opcode 63 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* CopyPlane */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (8));
    printField (buf, 4, 4, DRAWABLE, "src-drawable");
    printField (buf, 8, 4, DRAWABLE, "dst-drawable");
    printField (buf, 12, 4, GCONTEXT, "gc");
    if (Verbose > 2)
        printValueRec (ILong (&buf[12]),
                       GC_function | GC_plane_mask | GC_foreground | GC_background | GC_graphics_exposures, GC_BITMASK);
    printField (buf, 16, 2, INT16, "src-x");
    printField (buf, 18, 2, INT16, "src-y");
    printField (buf, 20, 2, INT16, "dst-x");
    printField (buf, 22, 2, INT16, "dst-y");
    printField (buf, 24, 2, CARD16, "width");
    printField (buf, 26, 2, CARD16, "height");
    printField (buf, 28, 4, CARD32, "bit-plane");
}

void PolyPoint(FD fd, const unsigned char *buf) {
    uint32_t n;

    /* Request PolyPoint is opcode 64 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* PolyPoint */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printField (buf, 1, 1, COORMODE, "coordinate-mode");
    n = (getreqlen (fd, buf) - 3);
    printreqlen (buf, fd, DVALUE2 (3 + n));
    printField (buf, 4, 4, DRAWABLE, "drawable");
    printField (buf, 8, 4, GCONTEXT, "gc");
    if (Verbose > 2)
        printValueRec (ILong (&buf[8]), GC_function | GC_plane_mask | GC_foreground, GC_BITMASK);
    (void) printList (&buf[12], (long) n, POINT, "points");
}

void PolyLine(FD fd, const unsigned char *buf) {
    uint32_t n;

    /* Request PolyLine is opcode 65 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* PolyLine */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printField (buf, 1, 1, COORMODE, "coordinate-mode");
    n = (getreqlen (fd, buf) - 3);
    printreqlen (buf, fd, DVALUE2 (3 + n));
    printField (buf, 4, 4, DRAWABLE, "drawable");
    printField (buf, 8, 4, GCONTEXT, "gc");
    if (Verbose > 2)
        printValueRec (ILong (&buf[8]),
                       GC_function | GC_plane_mask | GC_line_width | GC_line_style | GC_cap_style | GC_join_style |
                       GC_fill_style | GC_foreground | GC_background | GC_tile | GC_stipple, GC_BITMASK);
    (void) printList (&buf[12], (long) n, POINT, "points");
}

void PolySegment(FD fd, const unsigned char *buf) {
    uint32_t n;

    /* Request PolySegment is opcode 66 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* PolySegment */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    n = (getreqlen (fd, buf) - 3) / 2;
    printreqlen (buf, fd, DVALUE2 (3 + 2 * n));
    printField (buf, 4, 4, DRAWABLE, "drawable");
    printField (buf, 8, 4, GCONTEXT, "gc");
    if (Verbose > 2)
        printValueRec (ILong (&buf[8]),
                       GC_function | GC_plane_mask | GC_line_width | GC_line_style | GC_cap_style | GC_fill_style |
                       GC_foreground | GC_background | GC_tile | GC_stipple, GC_BITMASK);
    (void) printList (&buf[12], (long) n, SEGMENT, "segments");
}

void PolyRectangle(FD fd, const unsigned char *buf) {
    uint32_t n;

    /* Request PolyRectangle is opcode 67 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* PolyRectangle */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    n = (getreqlen (fd, buf) - 3) / 2;
    printreqlen (buf, fd, DVALUE2 (3 + 2 * n));
    printField (buf, 4, 4, DRAWABLE, "drawable");
    printField (buf, 8, 4, GCONTEXT, "gc");
    if (Verbose > 2)
        printValueRec (ILong (&buf[8]),
                       GC_function | GC_plane_mask | GC_line_width | GC_line_style | GC_cap_style | GC_join_style |
                       GC_fill_style | GC_foreground | GC_background | GC_tile | GC_stipple, GC_BITMASK);
    (void) printList (&buf[12], (long) n, RECTANGLE, "rectangles");
}

void PolyArc(FD fd, const unsigned char *buf) {
    uint32_t n;

    /* Request PolyArc is opcode 68 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* PolyArc */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    n = (getreqlen (fd, buf) - 3) / 3;
    printreqlen (buf, fd, DVALUE2 (3 + 3 * n));
    printField (buf, 4, 4, DRAWABLE, "drawable");
    printField (buf, 8, 4, GCONTEXT, "gc");
    if (Verbose > 2)
        printValueRec (ILong (&buf[8]),
                       GC_function | GC_plane_mask | GC_line_width | GC_line_style | GC_cap_style | GC_join_style |
                       GC_fill_style | GC_foreground | GC_background | GC_tile | GC_stipple, GC_BITMASK);
    (void) printList (&buf[12], (long) n, ARC, "arcs");
}

void FillPoly(FD fd, const unsigned char *buf) {
    uint32_t n;

    /* Request FillPoly is opcode 69 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* FillPoly */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    n = (getreqlen (fd, buf) - 4);
    printreqlen (buf, fd, DVALUE2 (4 + n));
    printField (buf, 4, 4, DRAWABLE, "drawable");
    printField (buf, 8, 4, GCONTEXT, "gc");
    if (Verbose > 2)
        printValueRec (ILong (buf + 8),
                       GC_function | GC_plane_mask | GC_fill_style | GC_fill_rule | GC_foreground | GC_background |
                       GC_tile | GC_stipple, GC_BITMASK);
    printField (buf, 12, 1, POLYSHAPE, "shape");
    printField (buf, 13, 1, COORMODE, "coordinate-mode");
    printList (&buf[16], (long) n, POINT, "points");
}

void PolyFillRectangle(FD fd, const unsigned char *buf) {
    uint32_t n;

    /* Request PolyFillRectangle is opcode 70 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* PolyFillRectangle */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    n = (getreqlen (fd, buf) - 3) / 2;
    printreqlen (buf, fd, DVALUE2 (3 + 2 * n));
    printField (buf, 4, 4, DRAWABLE, "drawable");
    printField (buf, 8, 4, GCONTEXT, "gc");
    if (Verbose > 2)
        printValueRec (ILong (buf + 8),
                       GC_function | GC_plane_mask | GC_fill_style | GC_foreground | GC_background | GC_tile |
                       GC_stipple, GC_BITMASK);
    (void) printList (&buf[12], (long) n, RECTANGLE, "rectangles");
}

void PolyFillArc(FD fd, const unsigned char *buf) {
    uint32_t n;

    /* Request PolyFillArc is opcode 71 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* PolyFillArc */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    n = (getreqlen (fd, buf) - 3) / 3;
    printreqlen (buf, fd, DVALUE2 (3 + 3 * n));
    printField (buf, 4, 4, DRAWABLE, "drawable");
    printField (buf, 8, 4, GCONTEXT, "gc");
    if (Verbose > 2)
        printValueRec (ILong (&buf[8]),
                       GC_function | GC_plane_mask | GC_arc_mode | GC_fill_style | GC_foreground | GC_background |
                       GC_tile | GC_stipple, GC_BITMASK);
    (void) printList (&buf[12], (long) n, ARC, "arcs");
}

void PutImage(FD fd, const unsigned char *buf) {
    uint32_t n;

    /* Request PutImage is opcode 72 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* PutImage */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printField (buf, 1, 1, IMAGEMODE, "format");

    /* the size of the Image is overestimated by the following computation of n,
       because we ignore that padding of the request to a multiple of 4 bytes.
       The image may not be a multiple of 4 bytes.  The actual size of the image
       is determined as follows: for format = Bitmap or format = XYPixmap, the
       size is (left-pad + width) [ pad to multiple of bitmap-scanline-pad from
       SetUpReply ] divide by 8 to get bytes times height times depth for format
       = ZPixmap, take the depth and use it to find the bits-per-pixel and
       scanline-pad given in one of the SetUpReply DEPTH records. width *
       bits-per-pixel pad to multiple of scanline-pad divide by 8 to get bytes
       times height times depth For simplicity, we ignore all this and just use
       the request length to (over)estimate the size of the image */

    n = (getreqlen (fd, buf) - 6) * 4;
    printreqlen (buf, fd, DVALUE2 (6 + (n + p) / 4));
    printField (buf, 4, 4, DRAWABLE, "drawable");
    printField (buf, 8, 4, GCONTEXT, "gc");
    if (Verbose > 2)
        printValueRec (ILong (&buf[8]), GC_function | GC_plane_mask | GC_foreground | GC_background, GC_BITMASK);
    printField (buf, 12, 2, CARD16, "width");
    printField (buf, 14, 2, CARD16, "height");
    printField (buf, 16, 2, INT16, "dst-x");
    printField (buf, 18, 2, INT16, "dst-y");
    printField (buf, 20, 1, CARD8, "left-pad");
    printField (buf, 21, 1, CARD8, "depth");

    if (Verbose > 3)
        printBytes (&buf[24], (long) n, "data");
}

void GetImage(FD fd, const unsigned char *buf) {
    /* Request GetImage is opcode 73 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* GetImage */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printField (buf, 1, 1, IMAGEMODE, "format");
    printreqlen (buf, fd, CONST2 (5));
    printField (buf, 4, 4, DRAWABLE, "drawable");
    printField (buf, 8, 2, INT16, "x");
    printField (buf, 10, 2, INT16, "y");
    printField (buf, 12, 2, CARD16, "width");
    printField (buf, 14, 2, CARD16, "height");
    printField (buf, 16, 4, CARD32, "plane-mask");
}

void GetImageReply(const unsigned char *buf) {
    long n;

    printField (RBf, 0, 1, REPLY, REPLYHEADER); /* GetImage */
    if (Verbose < 1)
        return;
    printField (buf, 1, 1, CARD8, "depth");
    printfield(buf, 2, 2, CARD16, "sequence number");
    printfield(buf, 4, 4, DVALUE4 ((n + p) / 4), "reply length");

    /* to properly compute the actual size of the image, we have to remember the
       width and height values from the request.  Again, we (over)estimate its
       length from the length of the reply */
    n = ILong (&buf[4]) * 4;
    printField (buf, 8, 4, VISUALID, "visual");
    if (Verbose > 3)
        printBytes (&buf[32], n, "data");
}

void PolyText8(FD fd, const unsigned char *buf) {
    uint32_t n;

    /* Request PolyText8 is opcode 74 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* PolyText8 */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    n = (getreqlen (fd, buf) - 4) * 4;
    printreqlen (buf, fd, DVALUE2 (4 + (n + p) / 4));
    printField (buf, 4, 4, DRAWABLE, "drawable");
    printField (buf, 8, 4, GCONTEXT, "gc");
    if (Verbose > 2)
        printValueRec (ILong (&buf[8]),
                       GC_function | GC_plane_mask | GC_fill_style | GC_font | GC_foreground | GC_background | GC_tile |
                       GC_stipple, GC_BITMASK);
    printField (buf, 12, 2, INT16, "x");
    printField (buf, 14, 2, INT16, "y");
    printTextList8 (&buf[16], n, "items");
}

void PolyText16(FD fd, const unsigned char *buf) {
    uint32_t n;

    /* Request PolyText16 is opcode 75 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* PolyText16 */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    n = (getreqlen (fd, buf) - 4) * 4;
    printreqlen (buf, fd, DVALUE2 (4 + (n + p) / 4));
    printField (buf, 4, 4, DRAWABLE, "drawable");
    printField (buf, 8, 4, GCONTEXT, "gc");
    if (Verbose > 2)
        printValueRec (ILong (&buf[8]),
                       GC_function | GC_plane_mask | GC_fill_style | GC_font | GC_foreground | GC_background | GC_tile |
                       GC_stipple, GC_BITMASK);
    printField (buf, 12, 2, INT16, "x");
    printField (buf, 14, 2, INT16, "y");
    printTextList16 (&buf[16], n, "items");
}

void ImageText8(FD fd, const unsigned char *buf) {
    short n;

    /* Request ImageText8 is opcode 76 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* ImageText8 */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printfield(buf, 1, 1, DVALUE1 (n), "length of string");
    n = IByte (&buf[1]);
    printreqlen (buf, fd, DVALUE2 (4 + (n + p) / 4));
    printField (buf, 4, 4, DRAWABLE, "drawable");
    printField (buf, 8, 4, GCONTEXT, "gc");
    if (Verbose > 2)
        printValueRec (ILong (&buf[8]), GC_plane_mask | GC_font | GC_foreground | GC_background, GC_BITMASK);
    printField (buf, 12, 2, INT16, "x");
    printField (buf, 14, 2, INT16, "y");
    printTString8 (&buf[16], (long) n, "string");
}

void ImageText16(FD fd, const unsigned char *buf) {
    short n;

    /* Request ImageText16 is opcode 77 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* ImageText16 */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printfield(buf, 1, 1, DVALUE1 (n), "length of string");
    n = IByte (&buf[1]);
    printreqlen (buf, fd, DVALUE2 (4 + (2 * n + p) / 4));
    printField (buf, 4, 4, DRAWABLE, "drawable");
    printField (buf, 8, 4, GCONTEXT, "gc");
    if (Verbose > 2)
        printValueRec (ILong (&buf[8]), GC_plane_mask | GC_font | GC_foreground | GC_background, GC_BITMASK);
    printField (buf, 12, 2, INT16, "x");
    printField (buf, 14, 2, INT16, "y");
    printTString16 (&buf[16], (long) n, "string");
}

void CreateColormap(FD fd, const unsigned char *buf) {
    /* Request CreateColormap is opcode 78 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* CreateColormap */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printField (buf, 1, 1, ALLORNONE, "alloc");
    printreqlen (buf, fd, CONST2 (4));
    printField (buf, 4, 4, COLORMAP, "color-map-id");
    printField (buf, 8, 4, WINDOW, "window");
    printField (buf, 12, 4, VISUALID, "visual");
}

void FreeColormap(FD fd, const unsigned char *buf) {
    /* Request FreeColormap is opcode 79 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* FreeColormap */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (2));
    printField (buf, 4, 4, COLORMAP, "cmap");
}

void CopyColormapAndFree(FD fd, const unsigned char *buf) {
    /* Request CopyColormapAndFree is opcode 80 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* CopyColormapAndFree */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (3));
    printField (buf, 4, 4, COLORMAP, "color-map-id");
    printField (buf, 8, 4, COLORMAP, "src-cmap");
}

void InstallColormap(FD fd, const unsigned char *buf) {
    /* Request InstallColormap is opcode 81 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* InstallColormap */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (2));
    printField (buf, 4, 4, COLORMAP, "cmap");
}

void UninstallColormap(FD fd, const unsigned char *buf) {
    /* Request UninstallColormap is opcode 82 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* UninstallColormap */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (2));
    printField (buf, 4, 4, COLORMAP, "cmap");
}

void ListInstalledColormaps(FD fd, const unsigned char *buf) {
    /* Request ListInstalledColormaps is opcode 83 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* ListInstalledColormaps */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (2));
    printField (buf, 4, 4, WINDOW, "window");
}

void ListInstalledColormapsReply(const unsigned char *buf) {
    short n;

    printField (RBf, 0, 1, REPLY, REPLYHEADER); /* ListInstalledColormaps */
    if (Verbose < 1)
        return;
    printfield(buf, 2, 2, CARD16, "sequence number");
    printfield(buf, 4, 4, DVALUE4 (n), "reply length");
    printfield(buf, 8, 2, DVALUE2 (n), "number of cmaps");
    n = IShort (&buf[8]);
    printList (&buf[32], (long) n, COLORMAP, "cmaps");
}

void AllocColor(FD fd, const unsigned char *buf) {
    /* Request AllocColor is opcode 84 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* AllocColor */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (4));
    printField (buf, 4, 4, COLORMAP, "cmap");
    printField (buf, 8, 2, CARD16, "red");
    printField (buf, 10, 2, CARD16, "green");
    printField (buf, 12, 2, CARD16, "blue");
}

void AllocColorReply(const unsigned char *buf) {
    printField (RBf, 0, 1, REPLY, REPLYHEADER); /* AllocColor */
    if (Verbose < 1)
        return;
    printfield(buf, 2, 2, CARD16, "sequence number");
    printfield(buf, 4, 4, CONST4 (0), "reply length");
    printField (buf, 8, 2, CARD16, "red");
    printField (buf, 10, 2, CARD16, "green");
    printField (buf, 12, 2, CARD16, "blue");
    printField (buf, 16, 4, CARD32, "pixel");
}

void AllocNamedColor(FD fd, const unsigned char *buf) {
    short n;

    /* Request AllocNamedColor is opcode 85 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* AllocNamedColor */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, DVALUE2 (3 + (n + p) / 4));
    printField (buf, 4, 4, COLORMAP, "cmap");
    printfield(buf, 8, 2, DVALUE2 (n), "length of name");
    n = IShort (&buf[8]);
    printString8 (&buf[12], n, "name");
}

void AllocNamedColorReply(const unsigned char *buf) {
    printField (RBf, 0, 1, REPLY, REPLYHEADER); /* AllocNamedColor */
    if (Verbose < 1)
        return;
    printfield(buf, 2, 2, CARD16, "sequence number");
    printfield(buf, 4, 4, CONST4 (0), "reply length");
    printField (buf, 8, 4, CARD32, "pixel");
    printField (buf, 12, 2, CARD16, "exact-red");
    printField (buf, 14, 2, CARD16, "exact-green");
    printField (buf, 16, 2, CARD16, "exact-blue");
    printField (buf, 18, 2, CARD16, "visual-red");
    printField (buf, 20, 2, CARD16, "visual-green");
    printField (buf, 22, 2, CARD16, "visual-blue");
}

void AllocColorCells(FD fd, const unsigned char *buf) {
    /* Request AllocColorCells is opcode 86 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* AllocColorCells */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printField (buf, 1, 1, BOOL, "contiguous");
    printreqlen (buf, fd, CONST2 (3));
    printField (buf, 4, 4, COLORMAP, "cmap");
    printField (buf, 8, 2, CARD16, "colors");
    printField (buf, 10, 2, CARD16, "planes");
}

void AllocColorCellsReply(const unsigned char *buf) {
    short n;
    short m;
    short k;

    printField (RBf, 0, 1, REPLY, REPLYHEADER); /* AllocColorCells */
    if (Verbose < 1)
        return;
    printfield(buf, 2, 2, CARD16, "sequence number");
    printfield(buf, 4, 4, DVALUE4 (n + m), "reply length");
    printfield(buf, 8, 2, DVALUE2 (n), "number of pixels");
    n = IShort (&buf[8]);
    printfield(buf, 10, 2, DVALUE2 (m), "number of masks");
    m = IShort (&buf[10]);
    k = printList (&buf[32], (long) n, CARD32, "pixels");
    printList (&buf[32 + k], (long) m, CARD32, "masks");
}

void AllocColorPlanes(FD fd, const unsigned char *buf) {
    /* Request AllocColorPlanes is opcode 87 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* AllocColorPlanes */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printField (buf, 1, 1, BOOL, "contiguous");
    printreqlen (buf, fd, CONST2 (4));
    printField (buf, 4, 4, COLORMAP, "cmap");
    printField (buf, 8, 2, CARD16, "colors");
    printField (buf, 10, 2, CARD16, "reds");
    printField (buf, 12, 2, CARD16, "greens");
    printField (buf, 14, 2, CARD16, "blues");
}

void AllocColorPlanesReply(const unsigned char *buf) {
    short n;

    printField (RBf, 0, 1, REPLY, REPLYHEADER); /* AllocColorPlanes */
    if (Verbose < 1)
        return;
    printfield(buf, 2, 2, CARD16, "sequence number");
    printfield(buf, 4, 4, DVALUE4 (n), "reply length");
    printfield(buf, 8, 2, DVALUE2 (n), "number of pixels");
    n = IShort (&buf[8]);
    printField (buf, 12, 4, CARD32, "red-mask");
    printField (buf, 16, 4, CARD32, "green-mask");
    printField (buf, 20, 4, CARD32, "blue-mask");
    printList (&buf[32], (long) n, CARD32, "pixels");
}

void FreeColors(FD fd, const unsigned char *buf) {
    uint32_t n;

    /* Request FreeColors is opcode 88 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* FreeColors */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    n = getreqlen (fd, buf) - 3;
    printreqlen (buf, fd, DVALUE2 (3 + n));
    printField (buf, 4, 4, COLORMAP, "cmap");
    printField (buf, 8, 4, CARD32, "plane-mask");
    printList (&buf[12], (long) n, CARD32, "pixels");
}

void StoreColors(FD fd, const unsigned char *buf) {
    uint32_t n;

    /* Request StoreColors is opcode 89 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* StoreColors */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    n = (getreqlen (fd, buf) - 2) / 3;
    printreqlen (buf, fd, DVALUE2 (2 + 3 * n));
    printField (buf, 4, 4, COLORMAP, "cmap");
    printList (&buf[8], (long) n, COLORITEM, "items");
}

void StoreNamedColor(FD fd, const unsigned char *buf) {
    short n;

    /* Request StoreNamedColor is opcode 90 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* StoreNamedColor */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printField (buf, 1, 1, COLORMASK, "which colors?");
    printreqlen (buf, fd, DVALUE2 (4 + (n + p) / 4));
    printField (buf, 4, 4, COLORMAP, "cmap");
    printField (buf, 8, 4, CARD32, "pixel");
    printfield(buf, 12, 2, DVALUE2 (n), "length of name");
    n = IShort (&buf[12]);
    printString8 (&buf[16], n, "name");
}

void QueryColors(FD fd, const unsigned char *buf) {
    uint32_t n;

    /* Request QueryColors is opcode 91 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* QueryColors */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    n = getreqlen (fd, buf) - 2;
    printreqlen (buf, fd, DVALUE2 (2 + n));
    printField (buf, 4, 4, COLORMAP, "cmap");
    printList (&buf[8], (long) n, CARD32, "pixels");
}

void QueryColorsReply(const unsigned char *buf) {
    short n;

    printField (RBf, 0, 1, REPLY, REPLYHEADER); /* QueryColors */
    if (Verbose < 1)
        return;
    printfield(buf, 2, 2, CARD16, "sequence number");
    printfield(buf, 4, 4, DVALUE4 (2 * n), "reply length");
    printfield(buf, 8, 2, DVALUE2 (n), "number of colors");
    n = IShort (&buf[8]);
    printList (&buf[32], (long) n, RGB, "colors");
}

void LookupColor(FD fd, const unsigned char *buf) {
    short n;

    /* Request LookupColor is opcode 92 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* LookupColor */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, DVALUE2 (3 + (n + p) / 4));
    printField (buf, 4, 4, COLORMAP, "cmap");
    printfield(buf, 8, 2, DVALUE2 (n), "length of name");
    n = IShort (&buf[8]);
    printString8 (&buf[12], n, "name");
}

void LookupColorReply(const unsigned char *buf) {
    printField (RBf, 0, 1, REPLY, REPLYHEADER); /* LookupColor */
    if (Verbose < 1)
        return;
    printfield(buf, 2, 2, CARD16, "sequence number");
    printfield(buf, 4, 4, CONST4 (0), "reply length");
    printField (buf, 8, 2, CARD16, "exact-red");
    printField (buf, 10, 2, CARD16, "exact-green");
    printField (buf, 12, 2, CARD16, "exact-blue");
    printField (buf, 14, 2, CARD16, "visual-red");
    printField (buf, 16, 2, CARD16, "visual-green");
    printField (buf, 18, 2, CARD16, "visual-blue");
}

void CreateCursor(FD fd, const unsigned char *buf) {
    /* Request CreateCursor is opcode 93 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* CreateCursor */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (8));
    printField (buf, 4, 4, CURSOR, "cursor-id");
    printField (buf, 8, 4, PIXMAP, "source");
    printField (buf, 12, 4, PIXMAP, "mask");
    printField (buf, 16, 2, CARD16, "fore-red");
    printField (buf, 18, 2, CARD16, "fore-green");
    printField (buf, 20, 2, CARD16, "fore-blue");
    printField (buf, 22, 2, CARD16, "back-red");
    printField (buf, 24, 2, CARD16, "back-green");
    printField (buf, 26, 2, CARD16, "back-blue");
    printField (buf, 28, 2, CARD16, "x");
    printField (buf, 30, 2, CARD16, "y");
}

void CreateGlyphCursor(FD fd, const unsigned char *buf) {
    /* Request CreateGlyphCursor is opcode 94 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* CreateGlyphCursor */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (8));
    printField (buf, 4, 4, CURSOR, "cursor-id");
    printField (buf, 8, 4, FONT, "source-font");
    printField (buf, 12, 4, FONT, "mask-font");
    printField (buf, 16, 2, CARD16, "source-char");
    printField (buf, 18, 2, CARD16, "mask-char");
    printField (buf, 20, 2, CARD16, "fore-red");
    printField (buf, 22, 2, CARD16, "fore-green");
    printField (buf, 24, 2, CARD16, "fore-blue");
    printField (buf, 26, 2, CARD16, "back-red");
    printField (buf, 28, 2, CARD16, "back-green");
    printField (buf, 30, 2, CARD16, "back-blue");
}

void FreeCursor(FD fd, const unsigned char *buf) {
    /* Request FreeCursor is opcode 95 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* FreeCursor */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (2));
    printField (buf, 4, 4, CURSOR, "cursor");
}

void RecolorCursor(FD fd, const unsigned char *buf) {
    /* Request RecolorCursor is opcode 96 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* RecolorCursor */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (5));
    printField (buf, 4, 4, CURSOR, "cursor");
    printField (buf, 8, 2, CARD16, "fore-red");
    printField (buf, 10, 2, CARD16, "fore-green");
    printField (buf, 12, 2, CARD16, "fore-blue");
    printField (buf, 14, 2, CARD16, "back-red");
    printField (buf, 16, 2, CARD16, "back-green");
    printField (buf, 18, 2, CARD16, "back-blue");
}

void QueryBestSize(FD fd, const unsigned char *buf) {
    /* Request QueryBestSize is opcode 97 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* QueryBestSize */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printField (buf, 1, 1, OBJECTCLASS, "class");
    printreqlen (buf, fd, CONST2 (3));
    printField (buf, 4, 4, DRAWABLE, "drawable");
    printField (buf, 8, 2, CARD16, "width");
    printField (buf, 10, 2, CARD16, "height");
}

void QueryBestSizeReply(const unsigned char *buf) {
    printField (RBf, 0, 1, REPLY, REPLYHEADER); /* QueryBestSize */
    if (Verbose < 1)
        return;
    printfield(buf, 2, 2, CARD16, "sequence number");
    printfield(buf, 4, 4, CONST4 (0), "reply length");
    printField (buf, 8, 2, CARD16, "width");
    printField (buf, 10, 2, CARD16, "height");
}

void QueryExtension(FD fd, const unsigned char *buf) {
    short n;

    /* Request QueryExtension is opcode 98 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* QueryExtension */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, DVALUE2 (2 + (n + p) / 4));
    printfield(buf, 4, 2, DVALUE2 (n), "length of name");
    n = IShort (&buf[4]);
    printString8 (&buf[8], (long) n, "name");
}

void QueryExtensionReply(const unsigned char *buf) {
    printField (RBf, 0, 1, REPLY, REPLYHEADER); /* QueryExtension */
    if (Verbose < 1)
        return;
    printfield(buf, 2, 2, CARD16, "sequence number");
    printfield(buf, 4, 4, CONST4 (0), "reply length");
    printField (buf, 8, 1, BOOL, "present");
    printField (buf, 9, 1, CARD8, "major-opcode");
    printField (buf, 10, 1, CARD8, "first-event");
    printField (buf, 11, 1, CARD8, "first-error");
}

void ListExtensions(FD fd, const unsigned char *buf) {
    /* Request ListExtensions is opcode 99 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* ListExtensions */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (1));
}

void ListExtensionsReply(const unsigned char *buf) {
    short n;

    printField (RBf, 0, 1, REPLY, REPLYHEADER); /* ListExtensions */
    if (Verbose < 1)
        return;
    printfield(buf, 1, 1, CARD8, "number names");
    n = IByte (&buf[1]);
    printfield(buf, 2, 2, CARD16, "sequence number");
    printfield(buf, 4, 4, DVALUE4 ((n + p) / 4), "reply length");
    printListSTR (&buf[32], (long) n, "names");
}

void ChangeKeyboardMapping(FD fd, const unsigned char *buf) {
    short n;
    short m;

    /* Request ChangeKeyboardMapping is opcode 100 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* ChangeKeyboardMapping */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printField (buf, 1, 1, DVALUE1 (n), "keycode-count");
    n = IByte (&buf[1]);
    printreqlen (buf, fd, DVALUE2 (2 + nm));
    printField (buf, 4, 1, KEYCODE, "first-keycode");
    printField (buf, 5, 1, DVALUE1 (m), "keysyms-per-keycode");
    m = IByte (&buf[5]);
    printList (&buf[8], (long) (n * m), KEYSYM, "keysyms");
}

void GetKeyboardMapping(FD fd, const unsigned char *buf) {
    /* Request GetKeyboardMapping is opcode 101 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* GetKeyboardMapping */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (2));
    printField (buf, 4, 1, KEYCODE, "first-keycode");
    printField (buf, 5, 1, CARD8, "count");
}

void GetKeyboardMappingReply(const unsigned char *buf) {
    long n;

    printField (RBf, 0, 1, REPLY, REPLYHEADER); /* GetKeyboardMapping */
    if (Verbose < 1)
        return;
    printField (buf, 1, 1, DVALUE1 (n), "keysyms-per-keycode");
    printfield(buf, 2, 2, CARD16, "sequence number");
    printfield(buf, 4, 4, DVALUE4 (n * m), "reply length");
    n = ILong (&buf[4]);
    printList (&buf[32], n, KEYSYM, "keysyms");
}

void ChangeKeyboardControl(FD fd, const unsigned char *buf) {
    /* Request ChangeKeyboardControl is opcode 102 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* ChangeKeyboardControl */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, DVALUE2 (2 + n));
    printField (buf, 4, 4, KEYBOARD_BITMASK, "value-mask");
    printValues (&buf[4], 4, KEYBOARD_BITMASK, &buf[8], "value-list");
}

void GetKeyboardControl(FD fd, const unsigned char *buf) {
    /* Request GetKeyboardControl is opcode 103 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* GetKeyboardControl */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (1));
}

void GetKeyboardControlReply(const unsigned char *buf) {
    printField (RBf, 0, 1, REPLY, REPLYHEADER); /* GetKeyboardControl */
    if (Verbose < 1)
        return;
    printField (buf, 1, 1, OFF_ON, "global-auto-repeat");
    printfield(buf, 2, 2, CARD16, "sequence number");
    printfield(buf, 4, 4, CONST4 (5), "reply length");
    printField (buf, 8, 4, CARD32, "led-mask");
    printField (buf, 12, 1, CARD8, "key-click-percent");
    printField (buf, 13, 1, CARD8, "bell-percent");
    printField (buf, 14, 2, CARD16, "bell-pitch");
    printField (buf, 16, 2, CARD16, "bell-duration");
    printBytes (&buf[20], 32L, "auto-repeats");
}

void Bell(FD fd, const unsigned char *buf) {
    /* Request Bell is opcode 104 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* Bell */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printField (buf, 1, 1, INT8, "percent");
    printreqlen (buf, fd, CONST2 (1));
}

void ChangePointerControl(FD fd, const unsigned char *buf) {
    /* Request ChangePointerControl is opcode 105 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* ChangePointerControl */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (3));
    printField (buf, 4, 2, INT16, "acceleration-numerator");
    printField (buf, 6, 2, INT16, "acceleration-denominator");
    printField (buf, 8, 2, INT16, "threshold");
    printField (buf, 10, 1, BOOL, "do-acceleration");
    printField (buf, 11, 1, BOOL, "do-threshold");
}

void GetPointerControl(FD fd, const unsigned char *buf) {
    /* Request GetPointerControl is opcode 106 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* GetPointerControl */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (1));
}

void GetPointerControlReply(const unsigned char *buf) {
    printField (RBf, 0, 1, REPLY, REPLYHEADER); /* GetPointerControl */
    if (Verbose < 1)
        return;
    printfield(buf, 2, 2, CARD16, "sequence number");
    printfield(buf, 4, 4, CONST4 (0), "reply length");
    printField (buf, 8, 2, CARD16, "acceleration-numerator");
    printField (buf, 10, 2, CARD16, "acceleration-denominator");
    printField (buf, 12, 2, CARD16, "threshold");
}

void SetScreenSaver(FD fd, const unsigned char *buf) {
    /* Request SetScreenSaver is opcode 107 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* SetScreenSaver */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (3));
    printField (buf, 4, 2, INT16, "timeout");
    printField (buf, 6, 2, INT16, "interval");
    printField (buf, 8, 1, NO_YES, "prefer-blanking");
    printField (buf, 9, 1, NO_YES, "allow-exposures");
}

void GetScreenSaver(FD fd, const unsigned char *buf) {
    /* Request GetScreenSaver is opcode 108 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* GetScreenSaver */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (1));
}

void GetScreenSaverReply(const unsigned char *buf) {
    printField (RBf, 0, 1, REPLY, REPLYHEADER); /* GetScreenSaver */
    if (Verbose < 1)
        return;
    printfield(buf, 2, 2, CARD16, "sequence number");
    printfield(buf, 4, 4, CONST4 (0), "reply length");
    printField (buf, 8, 2, CARD16, "timeout");
    printField (buf, 10, 2, CARD16, "interval");
    printField (buf, 12, 1, NO_YES, "prefer-blanking");
    printField (buf, 13, 1, NO_YES, "allow-exposures");
}

void ChangeHosts(FD fd, const unsigned char *buf) {
    short n;

    /* Request ChangeHosts is opcode 109 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* ChangeHosts */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printField (buf, 1, 1, INS_DEL, "mode");
    printreqlen (buf, fd, DVALUE2 (2 + (n + p) / 4));
    n = IShort (&buf[6]);
    printField (buf, 4, 4 + n, HOST, "host");
}

void ListHosts(FD fd, const unsigned char *buf) {
    /* Request ListHosts is opcode 110 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* ListHosts */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (1));
}

void ListHostsReply(const unsigned char *buf) {
    short n;

    printField (RBf, 0, 1, REPLY, REPLYHEADER); /* ListHosts */
    if (Verbose < 1)
        return;
    printField (buf, 1, 1, DIS_EN, "mode");
    printfield(buf, 2, 2, CARD16, "sequence number");
    printfield(buf, 4, 4, DVALUE4 (n / 4), "reply length");
    printfield(buf, 8, 2, CARD16, "number of hosts");

    n = IShort (&buf[8]);
    printList (&buf[32], (long) n, HOST, "hosts");
}

void SetAccessControl(FD fd, const unsigned char *buf) {
    /* Request SetAccessControl is opcode 111 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* SetAccessControl */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printField (buf, 1, 1, DIS_EN, "mode");
    printreqlen (buf, fd, CONST2 (1));
}

void SetCloseDownMode(FD fd, const unsigned char *buf) {
    /* Request SetCloseDownMode is opcode 112 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* SetCloseDownMode */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printField (buf, 1, 1, CLOSEMODE, "mode");
    printreqlen (buf, fd, CONST2 (1));
}

void KillClient(FD fd, const unsigned char *buf) {
    /* Request KillClient is opcode 113 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* KillClient */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (2));
    printField (buf, 4, 4, RESOURCEID, "resource");
}

void RotateProperties(FD fd, const unsigned char *buf) {
    short n;

    /* Request RotateProperties is opcode 114 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* RotateProperties */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, DVALUE2 (3 + n));
    printField (buf, 4, 4, WINDOW, "window");
    printfield(buf, 8, 2, DVALUE2 (n), "number of properties");
    n = IShort (&buf[8]);
    printField (buf, 10, 2, INT16, "delta");
    printList (&buf[12], (long) n, ATOM, "properties");
}

void ForceScreenSaver(FD fd, const unsigned char *buf) {
    /* Request ForceScreenSaver is opcode 115 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* ForceScreenSaver */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printField (buf, 1, 1, SAVEMODE, "mode");
    printreqlen (buf, fd, CONST2 (1));
}

void SetPointerMapping(FD fd, const unsigned char *buf) {
    short n;

    /* Request SetPointerMapping is opcode 116 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* SetPointerMapping */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printfield(buf, 1, 1, DVALUE1 (n), "length of map");
    n = IByte (&buf[1]);
    printreqlen (buf, fd, DVALUE2 (1 + (n + p) / 4));
    printBytes (&buf[4], (long) n, "map");
}

void SetPointerMappingReply(const unsigned char *buf) {
    printField (RBf, 0, 1, REPLY, REPLYHEADER); /* SetPointerMapping */
    if (Verbose < 1)
        return;
    printField (buf, 1, 1, RSTATUS, "status");
    printfield(buf, 2, 2, CARD16, "sequence number");
    printfield(buf, 4, 4, CONST4 (0), "reply length");
}

void GetPointerMapping(FD fd, const unsigned char *buf) {
    /* Request GetPointerMapping is opcode 117 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* GetPointerMapping */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (1));
}

void GetPointerMappingReply(const unsigned char *buf) {
    short n;

    printField (RBf, 0, 1, REPLY, REPLYHEADER); /* GetPointerMapping */
    if (Verbose < 1)
        return;
    printfield(buf, 1, 1, DVALUE1 (n), "length of map");
    n = IByte (&buf[1]);
    printfield(buf, 2, 2, CARD16, "sequence number");
    printfield(buf, 4, 4, DVALUE4 ((n + p) / 4), "reply length");
    printBytes (&buf[32], (long) n, "map");
}

void SetModifierMapping(FD fd, const unsigned char *buf) {
    short n;

    /* Request SetModifierMapping is opcode 118 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* SetModifierMapping */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printField (buf, 1, 1, DVALUE1 (n), "keycodes-per-modifier");
    n = IByte (&buf[1]);
    printreqlen (buf, fd, DVALUE2 (1 + 2 * n));
    printBytes (&buf[4 + 0 * n], (long) n, "Shift keycodes");
    printBytes (&buf[4 + 1 * n], (long) n, "Lock keycodes");
    printBytes (&buf[4 + 2 * n], (long) n, "Control keycodes");
    printBytes (&buf[4 + 3 * n], (long) n, "Mod1 keycodes");
    printBytes (&buf[4 + 4 * n], (long) n, "Mod2 keycodes");
    printBytes (&buf[4 + 5 * n], (long) n, "Mod3 keycodes");
    printBytes (&buf[4 + 6 * n], (long) n, "Mod4 keycodes");
    printBytes (&buf[4 + 7 * n], (long) n, "Mod5 keycodes");
}

void SetModifierMappingReply(const unsigned char *buf) {
    printField (RBf, 0, 1, REPLY, REPLYHEADER); /* SetModifierMapping */
    if (Verbose < 1)
        return;
    printField (buf, 1, 1, RSTATUS, "status");
    printfield(buf, 2, 2, CARD16, "sequence number");
    printfield(buf, 4, 4, CONST4 (0), "reply length");
}

void GetModifierMapping(FD fd, const unsigned char *buf) {
    /* Request GetModifierMapping is opcode 119 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* GetModifierMapping */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (1));
}

void GetModifierMappingReply(const unsigned char *buf) {
    short n;

    printField (RBf, 0, 1, REPLY, REPLYHEADER); /* GetModifierMapping */
    if (Verbose < 1)
        return;
    printField (buf, 1, 1, DVALUE1 (n), "keycodes-per-modifier");
    n = IByte (&buf[1]);
    printfield(buf, 2, 2, CARD16, "sequence number");
    printfield(buf, 4, 4, DVALUE4 (2 * n), "reply length");
    printList (&buf[32], (long) n, KEYCODE, "keycodes");
}

void NoOperation(FD fd, const unsigned char *buf) {
    /* Request NoOperation is opcode 127 */
    printField (buf, 0, 1, REQUEST, REQUESTHEADER); /* NoOperation */
    if (Verbose < 1)
        return;
    if (Verbose > 1)
        printField (SBf, 0, 4, CARD32, "sequence number");

    printreqlen (buf, fd, CONST2 (1));
}
