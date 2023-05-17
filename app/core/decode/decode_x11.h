//
// Created by dingjing on 23-5-12.
//

#ifndef XSCOPE_DECODE_X11_H
#define XSCOPE_DECODE_X11_H
#include <stdint.h>


char* decode_field      (const unsigned char* buf, int start, int length, int FieldType, const char* name);


// ...
void decode_event       (int fd, const unsigned char *buf, long n);
void decode_error       (int fd, const unsigned char *buf, long n);
void decode_reply       (int fd, const unsigned char *buf, long n);
void decode_request     (int fd, const unsigned char *buf, long n);

#endif //XSCOPE_DECODE_X11_H
