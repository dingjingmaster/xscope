//
// Created by dingjing on 23-5-17.
//

#ifndef XSCOPE_TOOLS_H
#define XSCOPE_TOOLS_H
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

extern bool gLittleEndian;

static inline uint16_t tools_short(const unsigned char buf[])
{
    if (NULL == buf) {
        return 0;
    }
    /* check for byte-swapping */
    if (gLittleEndian) {
        return (buf[1] << 8) | buf[0];
    }

    return ((buf[0] << 8) | buf[1]);
}

static inline uint32_t tools_long(const unsigned char buf[])
{
    if (NULL == buf) {
        return 0;
    }

    /* check for byte-swapping */
    if (gLittleEndian) {
        return ((buf[3] << 24) | (buf[2] << 16) | (buf[1] << 8) | buf[0]);
    }

    return ((buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf[3]);
}

static inline uint16_t tools_char2B(const unsigned char buf[])
{
    if (NULL == buf) {
        return 0;
    }
    /* CHAR2B is like an IShort, but not byte-swapped */
    return ((buf[0] << 8) | buf[1]);
}

static inline uint8_t tools_byte(const unsigned char buf[])
{
    if (NULL == buf) {
        return 0;
    }
    return (buf[0]);
}

static inline bool tools_bool(const unsigned char buf[])
{
    if (NULL == buf) {
        return 0;
    }
    if (buf[0] != 0) {
        return (true);
    }
    else {
        return (false);
    }
}

#endif //XSCOPE_TOOLS_H
