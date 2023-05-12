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

typedef struct EventData            EventData;


struct EventData
{
    GMutex                  lock;
    GMainLoop*              mainLoop;

    GSocket*                xClient;
    GSocket*                xServer;
};

void event_stop (EventData* ev);

void event_read_from_xclient (EventData* ev, gchar** buf, gsize* bufLen, GError** error);
void event_read_from_xserver (EventData* ev, gchar** buf, gsize* bufLen, GError** error);

void event_write_to_xserver (EventData* ev, const gchar* buf, gsize bufLen);
void event_write_to_xclient (EventData* ev, const gchar* buf, gsize bufLen);


#ifdef __cplusplus
};
#endif
#endif //XSCOPE_EVENT_H
