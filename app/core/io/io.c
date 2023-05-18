//
// Created by dingjing on 23-5-16.
//

#include "io.h"

static gsize read_all_data(GSocket* fr, char** out/*out*/, GError** error);


void io_cache_read_from_xclient(IOContext *ctx, GError **error)
{
    g_return_if_fail(ctx);

    g_mutex_lock (&(ctx->xClient.lock));

    char* bin = NULL;
    gsize len = read_all_data (ctx->xClient.xIO, &bin, error);
    if (ctx->xClient.xReadCache) {
        char* bbin = (char*) g_malloc0 (len + ctx->xClient.xReadCacheLen + 1);
        if (NULL != bbin) {
            memcpy (bbin, ctx->xClient.xReadCache, ctx->xClient.xReadCacheLen);
            g_free (ctx->xClient.xReadCache);
            ctx->xClient.xReadCacheLen += len;
            memcpy (bbin + ctx->xClient.xReadCacheLen, bin, len);
            ctx->xClient.xReadCache = bbin;
        }
        else {
            g_free (ctx->xClient.xReadCache);
            ctx->xClient.xReadCache = NULL;
            ctx->xClient.xReadCacheLen = 0;
        }

        if (bin) {g_free (bin);}
    }
    else {
        ctx->xClient.xReadCache = bin;
        ctx->xClient.xReadCacheLen = len;
    }

    g_mutex_unlock (&(ctx->xClient.lock));
}

bool io_cache_is_valid(IOContext* ctx)
{
    g_return_val_if_fail(NULL != ctx, false);

    g_return_val_if_fail(G_IS_SOCKET(ctx->xClient.xIO) && G_IS_SOCKET(ctx->xServer.xIO), false);

    g_return_val_if_fail(!g_socket_is_closed(ctx->xClient.xIO) && !g_socket_is_closed(ctx->xServer.xIO), false);

    return true;
}

void io_cache_write_to_xserver(IOContext *ctx, GError **error)
{
    g_return_if_fail(ctx);

    g_mutex_lock (&(ctx->xClient.lock));
    g_mutex_lock (&(ctx->xServer.lock));

    if (!G_IS_SOCKET(ctx->xClient.xIO) || !G_IS_SOCKET(ctx->xServer.xIO)
        || g_socket_is_closed (ctx->xClient.xIO) || g_socket_is_closed (ctx->xServer.xIO)) {
        g_warning("client or server closed!");
        return;
    }

    g_socket_send_with_blocking (ctx->xServer.xIO, ctx->xClient.xReadCache, ctx->xClient.xReadCacheLen, true, NULL, error);
    if (ctx->xClient.xReadCache) {g_free (ctx->xClient.xReadCache); ctx->xClient.xReadCache = NULL;}
    ctx->xClient.xReadCacheLen = 0;

    g_mutex_unlock (&(ctx->xServer.lock));
    g_mutex_unlock (&(ctx->xClient.lock));
}

void io_cache_read_from_xserver(IOContext *ctx, GError **error)
{
    g_return_if_fail(ctx);

    g_mutex_lock (&(ctx->xServer.lock));

    char* bin = NULL;
    gsize len = read_all_data (ctx->xServer.xIO, &bin, error);
    if (ctx->xServer.xReadCache) {
        char* bbin = (char*) g_malloc0 (len + ctx->xServer.xReadCacheLen + 1);
        if (NULL != bbin) {
            memcpy (bbin, ctx->xServer.xReadCache, ctx->xServer.xReadCacheLen);
            g_free (ctx->xServer.xReadCache);
            ctx->xServer.xReadCacheLen += len;
            memcpy (bbin + ctx->xServer.xReadCacheLen, bin, len);
            ctx->xServer.xReadCache = bbin;
        }
        else {
            g_free (ctx->xServer.xReadCache);
            ctx->xServer.xReadCache = NULL;
            ctx->xServer.xReadCacheLen = 0;
        }

        if (bin) {g_free (bin);}
    }
    else {
        ctx->xServer.xReadCache = bin;
        ctx->xServer.xReadCacheLen = len;
    }

    g_mutex_unlock (&(ctx->xServer.lock));
}

void io_cache_write_to_xclient(IOContext *ctx, GError **error)
{
    g_return_if_fail(ctx);

    g_mutex_lock (&(ctx->xServer.lock));
    g_mutex_lock (&(ctx->xClient.lock));

    if (!G_IS_SOCKET(ctx->xClient.xIO) || !G_IS_SOCKET(ctx->xServer.xIO)
        || g_socket_is_closed (ctx->xClient.xIO) || g_socket_is_closed (ctx->xServer.xIO)) {
        g_warning("client or server closed!");
        return;
    }

    g_socket_send_with_blocking (ctx->xClient.xIO, ctx->xServer.xReadCache, ctx->xServer.xReadCacheLen, true, NULL, error);
    if (ctx->xServer.xReadCache) {g_free (ctx->xServer.xReadCache); ctx->xServer.xReadCache = NULL;}
    ctx->xServer.xReadCacheLen = 0;

    g_mutex_unlock (&(ctx->xClient.lock));
    g_mutex_unlock (&(ctx->xServer.lock));
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
