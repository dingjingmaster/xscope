//
// Created by dingjing on 23-5-16.
//

#ifndef XSCOPE_IO_H
#define XSCOPE_IO_H
#include <glib.h>
#include <stdbool.h>
#include <gio/gio.h>

typedef struct IOCache      IOCache;
typedef struct IOContext    IOContext;

struct IOCache
{
    GSocket*                xIO;
    unsigned char*          xReadCache;
    gsize                   xReadCacheLen;
    char*                   xParsedReadStr;

    void*                   uData;

    GMutex                  lock;
};

struct IOContext
{
    IOCache                 xClient;
    IOCache                 xServer;
};

bool io_cache_is_valid (IOContext * ctx);

void io_cache_read_from_xclient (IOContext* ctx, GError** error);
void io_cache_write_to_xserver  (IOContext* ctx, GError** error);

void io_cache_read_from_xserver (IOContext* ctx, GError** error);
void io_cache_write_to_xclient  (IOContext* ctx, GError** error);

#endif //XSCOPE_IO_H
