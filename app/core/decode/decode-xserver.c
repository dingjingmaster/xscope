//
// Created by dingjing on 23-5-18.
//

#include "decode-xserver.h"

#include <glib.h>
#include <gio/gio.h>

#include "tools.h"
#include "global.h"
#include "decode_x11.h"
#include "decode-extensions.h"
#include "proto/xtype-common.h"


void xserver_start_setup_message (IOCache* cache)
{
    unsigned char* buf = cache->xReadCache;

    g_return_if_fail(buf);

    if (cache->xParsedReadStr) {
        g_free (cache->xParsedReadStr);
        cache->xParsedReadStr = NULL;
    }

    if (tools_byte (&buf[0])) {
        g_autofree char* pav = get_str_field_by_type (buf, 2, 2, CARD16, "protocol-major-version");
        g_autofree char* piv = get_str_field_by_type (buf, 4, 2, CARD16, "protocol-minor-version");
        g_autofree char* lod = get_str_field_by_type (buf, 6, 2, DVALUE2(8 + 2 * n + (v + p + m) / 4), "length of data");
        g_autofree char* rnn = get_str_field_by_type (buf, 8, 4, CARD32, "release-number");
        g_autofree char* rib = get_str_field_by_type (buf, 12, 4, CARD32, "resource-id-base");
        g_autofree char* rim = get_str_field_by_type (buf, 16, 4, CARD32, "resource-id-mask");
        g_autofree char* mbs = get_str_field_by_type (buf, 20, 4, CARD32, "motion-buffer-size");
        g_autofree char* lov = get_str_field_by_type (buf, 24, 2, DVALUE2(v), "length of vendor");
        short v = (short) tools_short (&buf[24]);
        g_autofree char* mrl = get_str_field_by_type (buf, 26, 2, CARD16, "maximum-request-length");
        g_autofree char* nor = get_str_field_by_type (buf, 28, 1, CARD8, "number of roots");
        short m = (short) tools_short (&buf[28]);
        g_autofree char* nop = get_str_field_by_type (buf, 29, 1, DVALUE1(n), "number of pixmap-formats");
        short n = (short) tools_short (&buf[29]);
        g_autofree char* ibo = get_str_field_by_type (buf, 30, 1, BYTEORDER, "image-byte-order");
        g_autofree char* bfo = get_str_field_by_type (buf, 31, 1, BYTEORDER, "bitmap-format-bit-order");
        g_autofree char* bfs = get_str_field_by_type (buf, 32, 1, CARD8, "bitmap-format-scanline-unit");
        g_autofree char* bfp = get_str_field_by_type (buf, 33, 1, CARD8, "bitmap-format-scanline-pad");
        g_autofree char* mkc = get_str_field_by_type (buf, 34, 1, KEYCODE, "min-keycode");
        g_autofree char* akc = get_str_field_by_type (buf, 35, 1, KEYCODE, "max-keycode");
        g_autofree char* vor = get_str_field_by_string8 (&buf[40], v, "vendor");
//        g_autofree char* pfl = get_str_field_by_list (&buf[pad((long) (40 + v))], (long) n, FORMAT, "pixmap-formats");
//        g_autofree char* rol = get_str_field_by_list (&buf[pad((long) (40 + v) + 8 * n)], (long) m, SCREEN, "roots");

        cache->xParsedReadStr = g_strdup_printf (""
                                                 "     protocol-major-version: %s\n"
                                                 "     protocol-minor-version: %s\n"
                                                 "             length of data: %s\n"
                                                 "             release-number: %s\n"
                                                 "           resource-id-base: %s\n"
                                                 "           resource-id-mask: %s\n"
                                                 "         motion-buffer-size: %s\n"
                                                 "           length of vendor: %s\n"
                                                 "     maximum-request-length: %s\n"
                                                 "            number of roots: %s\n"
                                                 "   number of pixmap-formats: %s\n"
                                                 "           image-byte-order: %s\n"
                                                 "    bitmap-format-bit-order: %s\n"
                                                 "bitmap-format-scanline-unit: %s\n"
                                                 " bitmap-format-scanline-pad: %s\n"
                                                 "                min-keycode: %s\n"
                                                 "                max-keycode: %s\n"
                                                 "                     vendor: %s\n"
//                                                 "             pixmap-formats: %s\n"
//                                                 "                      roots: %s\n"
                                                 "",
                                                 pav, piv, lod, rnn, rib, rim, mbs, lov, mrl, nor, nop, ibo, bfo, bfs, bfp, mkc, akc, vor); //, pfl, rol);
    }
    else {
        g_autofree char* lrb = get_str_field_by_type (buf, 1, 1, DVALUE1(n), "length of reason in bytes");
        short n = (short) tools_short (&buf[1]);
        g_autofree char* mav = get_str_field_by_type (buf, 2, 2, CARD16, "major-version");
        g_autofree char* miv = get_str_field_by_type (buf, 4, 2, CARD16, "minor-version");
        g_autofree char* lod = get_str_field_by_type (buf, 6, 2, DVALUE2((n + p) / 4), "length of data");
        g_autofree char* res = get_str_field_by_string8 (&buf[8], n, "reason");

        cache->xParsedReadStr = g_strdup_printf (""
                                                 "length of reason in bytes: %s\n"
                                                 "            major-version: %s\n"
                                                 "            minor-version: %s\n"
                                                 "           length of data: %s\n"
                                                 "                   reason: %s\n"
                                                 "",
                                                 lrb, mav, miv, lod, res);
    }
}

void xserver_finish_setup_message(IOCache *cache)
{

}

void xserver_start_request_message(IOCache *cache)
{
    unsigned char* buf = cache->xReadCache;

    g_return_if_fail(buf);

    if (cache->xParsedReadStr) {
        g_free (cache->xParsedReadStr);
        cache->xParsedReadStr = NULL;
    }

    int req = (short) tools_short(&buf[0]);
    int reqMinor = req >= 128 ? tools_byte (&buf[1]) : 0;
    unsigned long seq = 0;

    if (98 == req) {
        extensions_process_query_request(buf);
    }

    if (req < 0 || 127 < req) {
        extensions_request(buf, req);
    }
    else {
        switch (req) {
            case 1:
                CreateWindow(buf);
                break;
            case 2:
                ChangeWindowAttributes(fd, buf);
                break;
            case 3:
                GetWindowAttributes(fd, buf);
//                ReplyExpected(Request);
                break;
            case 4:
                DestroyWindow(buf);
                break;
            case 5:
                DestroySubwindows(buf);
                break;
            case 6:
                ChangeSaveSet(buf);
                break;
            case 7:
                ReparentWindow(buf);
                break;
            case 8:
                MapWindow(buf);
                break;
            case 9:
                MapSubwindows(buf);
                break;
            case 10:
                UnmapWindow(buf);
                break;
            case 11:
                UnmapSubwindows(buf);
                break;
            case 12:
                ConfigureWindow(buf);
                break;
            case 13:
                CirculateWindow(buf);
                break;
            case 14:
                GetGeometry(buf);
//                ReplyExpected(fd, Request);
                break;
            case 15:
                QueryTree(buf);
//                ReplyExpected(fd, Request);
                break;
            case 16:
                InternAtom(fd, buf);
                ReplyExpected(fd, Request);
                break;
            case 17:
                GetAtomName(fd, buf);
                ReplyExpected(fd, Request);
                break;
            case 18:
                ChangeProperty(fd, buf);
                break;
            case 19:
                DeleteProperty(fd, buf);
                break;
            case 20:
                GetProperty(fd, buf);
                ReplyExpected(fd, Request);
                break;
            case 21:
                ListProperties(fd, buf);
                ReplyExpected(fd, Request);
                break;
            case 22:
                SetSelectionOwner(fd, buf);
                break;
            case 23:
                GetSelectionOwner(fd, buf);
                ReplyExpected(fd, Request);
                break;
            case 24:
                ConvertSelection(fd, buf);
                break;
            case 25:
                SendEvent(fd, buf);
                break;
            case 26:
                GrabPointer(fd, buf);
                ReplyExpected(fd, Request);
                break;
            case 27:
                UngrabPointer(fd, buf);
                break;
            case 28:
                GrabButton(fd, buf);
                break;
            case 29:
                UngrabButton(fd, buf);
                break;
            case 30:
                ChangeActivePointerGrab(fd, buf);
                break;
            case 31:
                GrabKeyboard(fd, buf);
                ReplyExpected(fd, Request);
                break;
            case 32:
                UngrabKeyboard(fd, buf);
                break;
            case 33:
                GrabKey(fd, buf);
                break;
            case 34:
                UngrabKey(fd, buf);
                break;
            case 35:
                AllowEvents(fd, buf);
                break;
            case 36:
                GrabServer(fd, buf);
                break;
            case 37:
                UngrabServer(fd, buf);
                break;
            case 38:
                QueryPointer(fd, buf);
                ReplyExpected(fd, Request);
                break;
            case 39:
                GetMotionEvents(fd, buf);
                ReplyExpected(fd, Request);
                break;
            case 40:
                TranslateCoordinates(fd, buf);
                ReplyExpected(fd, Request);
                break;
            case 41:
                WarpPointer(fd, buf);
                break;
            case 42:
                SetInputFocus(fd, buf);
                break;
            case 43:
                GetInputFocus(fd, buf);
                ReplyExpected(fd, Request);
                break;
            case 44:
                QueryKeymap(fd, buf);
                ReplyExpected(fd, Request);
                break;
            case 45:
                OpenFont(fd, buf);
                break;
            case 46:
                CloseFont(fd, buf);
                break;
            case 47:
                QueryFont(fd, buf);
                ReplyExpected(fd, Request);
                break;
            case 48:
                QueryTextExtents(fd, buf);
                ReplyExpected(fd, Request);
                break;
            case 49:
                ListFonts(fd, buf);
                ReplyExpected(fd, Request);
                break;
            case 50:
                ListFontsWithInfo(fd, buf);
                ReplyExpected(fd, Request);
                break;
            case 51:
                SetFontPath(fd, buf);
                break;
            case 52:
                GetFontPath(fd, buf);
                ReplyExpected(fd, Request);
                break;
            case 53:
                CreatePixmap(fd, buf);
                break;
            case 54:
                FreePixmap(fd, buf);
                break;
            case 55:
                CreateGC(fd, buf);
                break;
            case 56:
                ChangeGC(fd, buf);
                break;
            case 57:
                CopyGC(fd, buf);
                break;
            case 58:
                SetDashes(fd, buf);
                break;
            case 59:
                SetClipRectangles(fd, buf);
                break;
            case 60:
                FreeGC(fd, buf);
                break;
            case 61:
                ClearArea(fd, buf);
                break;
            case 62:
                CopyArea(fd, buf);
                break;
            case 63:
                CopyPlane(fd, buf);
                break;
            case 64:
                PolyPoint(fd, buf);
                break;
            case 65:
                PolyLine(fd, buf);
                break;
            case 66:
                PolySegment(fd, buf);
                break;
            case 67:
                PolyRectangle(fd, buf);
                break;
            case 68:
                PolyArc(fd, buf);
                break;
            case 69:
                FillPoly(fd, buf);
                break;
            case 70:
                PolyFillRectangle(fd, buf);
                break;
            case 71:
                PolyFillArc(fd, buf);
                break;
            case 72:
                PutImage(fd, buf);
                break;
            case 73:
                GetImage(fd, buf);
                ReplyExpected(fd, Request);
                break;
            case 74:
                PolyText8(fd, buf);
                break;
            case 75:
                PolyText16(fd, buf);
                break;
            case 76:
                ImageText8(fd, buf);
                break;
            case 77:
                ImageText16(fd, buf);
                break;
            case 78:
                CreateColormap(fd, buf);
                break;
            case 79:
                FreeColormap(fd, buf);
                break;
            case 80:
                CopyColormapAndFree(fd, buf);
                break;
            case 81:
                InstallColormap(fd, buf);
                break;
            case 82:
                UninstallColormap(fd, buf);
                break;
            case 83:
                ListInstalledColormaps(fd, buf);
                ReplyExpected(fd, Request);
                break;
            case 84:
                AllocColor(fd, buf);
                ReplyExpected(fd, Request);
                break;
            case 85:
                AllocNamedColor(fd, buf);
                ReplyExpected(fd, Request);
                break;
            case 86:
                AllocColorCells(fd, buf);
                ReplyExpected(fd, Request);
                break;
            case 87:
                AllocColorPlanes(fd, buf);
                ReplyExpected(fd, Request);
                break;
            case 88:
                FreeColors(fd, buf);
                break;
            case 89:
                StoreColors(fd, buf);
                break;
            case 90:
                StoreNamedColor(fd, buf);
                break;
            case 91:
                QueryColors(fd, buf);
                ReplyExpected(fd, Request);
                break;
            case 92:
                LookupColor(fd, buf);
                ReplyExpected(fd, Request);
                break;
            case 93:
                CreateCursor(fd, buf);
                break;
            case 94:
                CreateGlyphCursor(fd, buf);
                break;
            case 95:
                FreeCursor(fd, buf);
                break;
            case 96:
                RecolorCursor(fd, buf);
                break;
            case 97:
                QueryBestSize(fd, buf);
                ReplyExpected(fd, Request);
                break;
            case 98:
                QueryExtension(fd, buf);
                ReplyExpected(fd, Request);
                break;
            case 99:
                ListExtensions(fd, buf);
                ReplyExpected(fd, Request);
                break;
            case 100:
                ChangeKeyboardMapping(fd, buf);
                break;
            case 101:
                GetKeyboardMapping(fd, buf);
                ReplyExpected(fd, Request);
                break;
            case 102:
                ChangeKeyboardControl(fd, buf);
                break;
            case 103:
                GetKeyboardControl(fd, buf);
                ReplyExpected(fd, Request);
                break;
            case 104:
                Bell(fd, buf);
                break;
            case 105:
                ChangePointerControl(fd, buf);
                break;
            case 106:
                GetPointerControl(fd, buf);
                ReplyExpected(fd, Request);
                break;
            case 107:
                SetScreenSaver(fd, buf);
                break;
            case 108:
                GetScreenSaver(fd, buf);
                ReplyExpected(fd, Request);
                break;
            case 109:
                ChangeHosts(fd, buf);
                break;
            case 110:
                ListHosts(fd, buf);
                ReplyExpected(fd, Request);
                break;
            case 111:
                SetAccessControl(fd, buf);
                break;
            case 112:
                SetCloseDownMode(fd, buf);
                break;
            case 113:
                KillClient(fd, buf);
                break;
            case 114:
                RotateProperties(fd, buf);
                break;
            case 115:
                ForceScreenSaver(fd, buf);
                break;
            case 116:
                SetPointerMapping(fd, buf);
                ReplyExpected(fd, Request);
                break;
            case 117:
                GetPointerMapping(fd, buf);
                ReplyExpected(fd, Request);
                break;
            case 118:
                SetModifierMapping(fd, buf);
                ReplyExpected(fd, Request);
                break;
            case 119:
                GetModifierMapping(fd, buf);
                ReplyExpected(fd, Request);
                break;
            case 127:
                NoOperation(fd, buf);
                break;
            default:
                g_warning("Unimplemented request opcode");
                break;
        }
    }
}

void xserver_finish_request_message(IOCache *cache)
{

}
