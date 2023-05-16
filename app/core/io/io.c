//
// Created by dingjing on 23-5-16.
//

#include "io.h"

static gsize read_all_data(GSocket* fr, char** out/*out*/, GError** error);


void io_cache_read_from_xclient(IOContext *ctx, GError **error)
{
    g_return_if_fail(ctx);

    g_mutex_lock (&(ctx->xClient.lock));

    g_autofree char* bin = NULL;
    gsize len = read_all_data (ctx->xClient.xIO, &bin, error);

    if (ctx->xClient.xReadCache) {
        g_autofree char* bbin = (char*) g_malloc0 (len + ctx->xClient.xReadCacheLen);
        if (NULL != bbin) {
            memcpy (bbin, ctx->xClient.xReadCache, ctx->xClient.xReadCacheLen);
            ctx->xClient.xReadCacheLen += len;
            memcpy (bbin + ctx->xClient.xReadCacheLen + 1, bin, ctx->xClient.xReadCacheLen);
            ctx->xClient.xReadCache = bbin;
        }
        else {
            g_free (ctx->xClient.xReadCache);
            ctx->xClient.xReadCacheLen = 0;
        }
    }
    else {
        ctx->xClient.xReadCache = bin;
        ctx->xClient.xReadCacheLen = len;
    }

    g_mutex_unlock (&(ctx->xClient.lock));
}


static gsize read_all_data(GSocket* fr, char** out/*out*/, GError** error)
{
    g_return_val_if_fail(out, 0);

    gsize len = 0;
    char* str = NULL;

    gsize readLen;
    char buf[1024] = {0};

    while ((readLen = g_socket_receive(fr, buf, sizeof(buf) - 1, NULL, error)) > 0) {
        if (readLen == -1) {
            goto error;
        }

        char* tmp = (gchar*) malloc (sizeof (char) * (len + readLen + 1));
        if (!tmp) {
            g_warning("malloc error!");
            goto error;
        }
        if (str && len > 0) {
            memcpy (tmp, str, len);
            g_free (str);
        }
        memcpy (tmp + len, buf, readLen);
        str = tmp;
        len += readLen;

        if (readLen < sizeof (buf) - 1) {
            break;
        }
    }

    if (*out) g_free (*out);
    *out = str;

    return len;

error:

    len = 0;
    if (str) { g_free (str); str = NULL;}

    return len;
}

bool io_cache_is_valid(IOContext* ctx)
{
    g_return_val_if_fail(NULL != ctx, false);

    g_return_val_if_fail(G_IS_SOCKET(ctx->xClient.xIO) && G_IS_SOCKET(ctx->xServer.xIO), false);

    g_return_val_if_fail(!g_socket_is_closed(ctx->xClient.xIO) && !g_socket_is_closed(ctx->xServer.xIO), false);

    return true;
}
