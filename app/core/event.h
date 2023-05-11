//
// Created by dingjing on 23-5-11.
//

#ifndef XSCOPE_EVENT_H
#define XSCOPE_EVENT_H

#include <glib.h>
#include <gio/gio.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct EventSource EventSource;

struct EventSource
{
    gboolean (*prepare)  (GSource    *source,
                          gint       *timeout_);/* Can be NULL */
    gboolean (*check)    (GSource    *source);/* Can be NULL */
    gboolean (*dispatch) (GSource    *source,
                          GSourceFunc callback,
                          gpointer    user_data);
    void     (*finalize) (GSource    *source); /* Can be NULL */

    char*               name;               // 客户端进程名字
    GSocket*            socket;
    char*               buf;                // 读缓存区
};


EventSource* event_source_create (const char* name, GSocket* socket);
void event_source_destroy (EventSource* ev);


#ifdef __cplusplus
};
#endif
#endif //XSCOPE_EVENT_H
