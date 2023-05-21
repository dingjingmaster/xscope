//
// Created by dingjing on 23-5-12.
//

#ifndef XSCOPE_DECODE_X11_H
#define XSCOPE_DECODE_X11_H
#include <stdint.h>

void CreateWindow(const unsigned char *buf);
void ChangeWindowAttributes(const unsigned char *buf);
void GetWindowAttributes(const unsigned char *buf);
void GetWindowAttributesReply(const unsigned char *buf);
void DestroyWindow(const unsigned char *buf);
void DestroySubwindows(const unsigned char *buf);
void ChangeSaveSet(const unsigned char *buf);
void ReparentWindow(const unsigned char *buf);
void MapWindow(const unsigned char *buf);
void MapSubwindows(const unsigned char *buf);
void UnmapWindow(const unsigned char *buf);
void UnmapSubwindows(const unsigned char *buf);
void ConfigureWindow(const unsigned char *buf);
void CirculateWindow(const unsigned char *buf);
void GetGeometry(const unsigned char *buf);
void GetGeometryReply(const unsigned char *buf);
void QueryTree(const unsigned char *buf);
void QueryTreeReply(const unsigned char *buf);

#endif //XSCOPE_DECODE_X11_H
