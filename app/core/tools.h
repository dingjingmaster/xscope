//
// Created by dingjing on 23-5-17.
//

#ifndef XSCOPE_TOOLS_H
#define XSCOPE_TOOLS_H
#include <stdint.h>
#include <stdbool.h>

uint32_t tools_long(const unsigned char buf[]);

uint16_t tools_short(const unsigned char buf[]);

uint16_t tools_char2B(const unsigned char buf[]);

uint8_t tools_byte(const unsigned char buf[]);

bool tools_bool(const unsigned char buf[]);


#endif //XSCOPE_TOOLS_H
