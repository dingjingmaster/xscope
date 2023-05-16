//
// Created by dingjing on 23-5-16.
//

#ifndef XSCOPE_CONN_CONTEXT_H
#define XSCOPE_CONN_CONTEXT_H
#include <glib.h>
#include <gio/gio.h>

typedef struct ConnContext      ConnContext;


ConnContext* conn_context_new (void);

void conn_context_run (ConnContext* cc);
void conn_context_quit (ConnContext* cc);
void conn_context_free (ConnContext** cc);

void* conn_context_peek_data (ConnContext* cc);
void conn_context_set_data (ConnContext* cc, void* data);

//void* conn_context_peek_client_data (ConnContext* cc);
//void conn_context_set_client_data (ConnContext* cc, void* data);

//void* conn_context_peek_server_data (ConnContext* cc);
//void conn_context_set_server_data (ConnContext* cc, void* data);

void conn_context_add_gsource (ConnContext* cc, GSource* source);


#endif //XSCOPE_CONN_CONTEXT_H
