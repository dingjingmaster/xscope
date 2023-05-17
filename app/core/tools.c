//
// Created by dingjing on 23-5-17.
//

#include "tools.h"

#include "global.h"

uint32_t tools_long(const unsigned char buf[])
{
    /* check for byte-swapping */
    if (gLittleEndian) {
        return ((buf[3] << 24) | (buf[2] << 16) | (buf[1] << 8) | buf[0]);
    }

    return ((buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf[3]);
}

uint16_t tools_short(const unsigned char buf[])
{
    /* check for byte-swapping */
    if (gLittleEndian) {
        return (buf[1] << 8) | buf[0];
    }

    return ((buf[0] << 8) | buf[1]);
}

uint16_t tools_char2B(const unsigned char buf[])
{
    /* CHAR2B is like an IShort, but not byte-swapped */
    return ((buf[0] << 8) | buf[1]);
}

uint8_t tools_byte(const unsigned char buf[])
{
    return (buf[0]);
}

bool tools_bool(const unsigned char buf[])
{
    if (buf[0] != 0) {
        return (true);
    }
    else {
        return (false);
    }
}

