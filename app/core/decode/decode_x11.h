//
// Created by dingjing on 23-5-12.
//

#ifndef XSCOPE_DECODE_X11_H
#define XSCOPE_DECODE_X11_H

void decode_event       (int fd, const unsigned char *buf, long n);
void decode_error       (int fd, const unsigned char *buf, long n);
void decode_reply       (int fd, const unsigned char *buf, long n);
void decode_request     (int fd, const unsigned char *buf, long n);

#endif //XSCOPE_DECODE_X11_H
