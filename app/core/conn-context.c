//
// Created by dingjing on 23-5-16.
//

#include "conn-context.h"

#include <stdbool.h>

struct ConnContext
{
    GMainLoop*          mainLoop;
    GMainContext*       mainContext;

    void*               clientData;
    void*               serverData;
    void*               udata;
};

ConnContext *conn_context_new(void)
{
    ConnContext* cc = g_malloc0 (sizeof (ConnContext));

    cc->mainContext = g_main_context_new();
    if (NULL == cc->mainContext) {
        goto error;
    }

    cc->mainLoop = g_main_loop_new (cc->mainContext, false);
    if (NULL == cc->mainLoop) {
        goto error;
    }

    return cc;

error:
    conn_context_free(&cc);

    return NULL;
}

void conn_context_free(ConnContext **cc)
{
    g_return_if_fail((NULL != cc) && (NULL != *cc));

    if ((*cc)->mainLoop) {
        g_main_loop_quit (&((*cc)->mainLoop));
        g_main_loop_unref (&((*cc)->mainLoop));
    }

    if ((*cc)->mainContext) {
        g_object_unref ((*cc)->mainContext);
    }

    g_free (*cc);

    *cc = NULL;
}

void conn_context_run(ConnContext *cc)
{
    g_return_if_fail(cc);

    g_main_loop_run (cc->mainLoop);
}

void conn_context_quit(ConnContext* cc)
{
    g_return_if_fail(cc);

    g_main_loop_quit (cc->mainLoop);
}

void conn_context_add_gsource(ConnContext *cc, GSource *source)
{
    g_return_if_fail((NULL != cc) && (NULL != source));

    g_source_attach (source, cc->mainContext);
}

void *conn_context_peek_data(ConnContext *cc)
{
    g_return_val_if_fail(cc, NULL);

    return cc->udata;
}

void conn_context_set_data(ConnContext *cc, void *data)
{
    g_return_if_fail(cc);

    cc->udata = data;
}

void *conn_context_peek_client_data(ConnContext *cc)
{
    g_return_val_if_fail(cc, NULL);

    return cc->clientData;
}

void conn_context_set_client_data(ConnContext *cc, void *data)
{
    g_return_if_fail(cc);

    cc->clientData = data;
}

void *conn_context_peek_server_data(ConnContext *cc)
{
    g_return_val_if_fail(cc, NULL);

    return cc->serverData;
}

void conn_context_set_server_data(ConnContext *cc, void *data)
{
    g_return_if_fail(cc);

    cc->serverData = data;
}

