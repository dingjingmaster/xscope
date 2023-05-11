//
// Created by dingjing on 23-5-10.
//

#ifndef XSCOPE_SERVER_H
#define XSCOPE_SERVER_H
#include <glib.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

bool server_init(const char *xServerHost, guint32 xServerPort);

#ifdef __cplusplus
};
#endif
#endif //XSCOPE_SERVER_H
