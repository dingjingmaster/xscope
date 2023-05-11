//
// Created by dingjing on 23-5-11.
//

#include "event.h"


EventSource* event_source_create (const char* name, GSocket* socket)
{
    EventSource* ev = (EventSource*) malloc (sizeof (EventSource));
    g_return_val_if_fail(ev, NULL);

    if (NULL != name) {
        ev->name = g_strdup(name);
    }
    ev->socket = g_object_ref(socket);
    ev->buf = NULL;

    return ev;
}

void event_source_destroy(EventSource *ev)
{
    g_return_if_fail(ev);

    g_socket_close (ev->socket, NULL);

    if (ev->buf)        g_free (ev->buf);
    if (ev->name)       g_free (ev->name);
    if (ev->socket)     g_object_unref (ev->socket);

    g_free (ev);
}
