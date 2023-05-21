//
// Created by dingjing on 23-5-17.
//

#include "xtype-atom.h"

#include <string.h>


#define ATOM_NUMBER                 68


static const char *const gSimpleNames[] =
    {
        "REQUEST",
        "REPLY  ",
        "EVENT  ",
        "ERROR  ",
    };

static const char* const gAtomTable [ATOM_NUMBER + 1] =
    {
        "NONE", "PRIMARY", "SECONDARY", "ARC", "ATOM", "BITMAP", "CARDINAL",
        "COLORMAP", "CURSOR", "CUT_BUFFER0", "CUT_BUFFER1", "CUT_BUFFER2",
        "CUT_BUFFER3", "CUT_BUFFER4", "CUT_BUFFER5", "CUT_BUFFER6",
        "CUT_BUFFER7", "DRAWABLE", "FONT", "INTEGER", "PIXMAP", "POINT",
        "RECTANGLE", "RESOURCE_MANAGER", "RGB_COLOR_MAP", "RGB_BEST_MAP",
        "RGB_BLUE_MAP", "RGB_DEFAULT_MAP", "RGB_GRAY_MAP", "RGB_GREEN_MAP",
        "RGB_RED_MAP", "STRING", "VISUALID", "WINDOW", "WM_COMMAND",
        "WM_HINTS", "WM_CLIENT_MACHINE", "WM_ICON_NAME", "WM_ICON_SIZE",
        "WM_NAME", "WM_NORMAL_HINTS", "WM_SIZE_HINTS", "WM_ZOOM_HINTS",
        "MIN_SPACE", "NORM_SPACE", "MAX_SPACE", "END_SPACE", "SUPERSCRIPT_X",
        "SUPERSCRIPT_Y", "SUBSCRIPT_X", "SUBSCRIPT_Y", "UNDERLINE_POSITION",
        "UNDERLINE_THICKNESS", "STRIKEOUT_ASCENT", "STRIKEOUT_DESCENT",
        "ITALIC_ANGLE", "X_HEIGHT", "QUAD_WIDTH", "WEIGHT", "POINT_SIZE",
        "RESOLUTION", "COPYRIGHT", "NOTICE", "FONT_NAME", "FAMILY_NAME",
        "FULL_NAME", "CAP_HEIGHT", "WM_CLASS", "WM_TRANSIENT_FOR"
    };


const char *find_atom_name(uint32_t atom)
{
    if (atom <= ATOM_NUMBER) {
        return gAtomTable[atom];
    }

    // FIXME:// DJ-


    return NULL;
}
