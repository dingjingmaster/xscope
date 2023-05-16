//
// Created by dingjing on 23-5-11.
//

#include "event.h"

#include <stdbool.h>

static gsize read_all_data(GSocket* fr, char** out/*out*/, GError** error);

//void event_stop(EventData *ev)
//{
//    g_return_if_fail(ev);
//
//    g_mutex_lock (&(ev->lock));
//
//    if (ev->xServer)    g_socket_close (ev->xServer, NULL);
//    if (ev->xClient)    g_socket_close (ev->xClient, NULL);
//
//    if (ev->mainLoop)   g_main_loop_quit (ev->mainLoop);
//
//    g_mutex_unlock (&(ev->lock));
//}
//
//bool event_write_to_xserver(EventData *ev, const gchar *buf, gsize bufLen)
//{
//    g_return_val_if_fail(ev, false);
//
//    bool ret = (bufLen > 0);
//    g_autoptr(GError) error = NULL;
//
//    g_mutex_lock (&(ev->lock));
//
//    g_socket_send_with_blocking (ev->xServer, buf, bufLen, true, NULL, &error);
//    if (error) {
//        ret = false;
//        g_warning("XClient to XServer [ERR]: '%s'", error->message);
//    }
//
//    g_mutex_unlock (&(ev->lock));
//
//    return ret;
//}
//
//bool event_write_to_xclient(EventData *ev, const gchar *buf, gsize bufLen)
//{
//    g_return_val_if_fail(ev, false);
//
//    bool ret = (bufLen > 0);
//    g_autoptr(GError) error = NULL;
//
//    g_mutex_lock (&(ev->lock));
//
//    g_socket_send_with_blocking (ev->xClient, buf, bufLen, true, NULL, NULL);
//    if (error) {
//        ret = false;
//        g_warning("XClient to XServer [ERR]: '%s'", error->message);
//    }
//
//    g_mutex_unlock (&(ev->lock));
//
//    return ret;
//}
//
//void event_read_from_xclient(EventData *ev, gchar **buf, gsize *bufLen, GError** error)
//{
//    g_return_if_fail(ev && buf && bufLen);
//
//    g_mutex_lock (&(ev->lock));
//
//    *bufLen = read_all_data (ev->xClient, buf, error);
//
//    g_mutex_unlock (&(ev->lock));
//}
//
//void event_read_from_xserver(EventData *ev, gchar **buf, gsize *bufLen, GError** error)
//{
//    g_return_if_fail(ev && buf && bufLen);
//
//    g_mutex_lock (&(ev->lock));
//
//    *bufLen = read_all_data (ev->xServer, buf, error);
//
//    g_mutex_unlock (&(ev->lock));
//}
//
//static gsize read_all_data(GSocket* fr, char** out/*out*/, GError** error)
//{
//    g_return_val_if_fail(out, 0);
//
//    gsize len = 0;
//    char* str = NULL;
//
//    gsize readLen;
//    char buf[1024] = {0};
//
//    while ((readLen = g_socket_receive(fr, buf, sizeof(buf) - 1, NULL, error)) > 0) {
//        if (readLen == -1) {
//            goto error;
//        }
//
//        char* tmp = (gchar*) malloc (sizeof (char) * (len + readLen + 1));
//        if (!tmp) {
//            g_warning("malloc error!");
//            goto error;
//        }
//        if (str && len > 0) {
//            memcpy (tmp, str, len);
//            g_free (str);
//        }
//        memcpy (tmp + len, buf, readLen);
//        str = tmp;
//        len += readLen;
//
//        if (readLen < sizeof (buf) - 1) {
//            break;
//        }
//    }
//
//    if (*out) g_free (*out);
//    *out = str;
//
//    return len;
//
//error:
//
//    len = 0;
//    if (str) { g_free (str); str = NULL;}
//
//    return len;
//}
