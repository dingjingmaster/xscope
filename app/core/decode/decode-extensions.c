//
// Created by dingjing on 23-5-18.
//

#include "decode-extensions.h"

void extensions_process_query_request(long seq, const unsigned char *buf)
{
    int namelen = IShort(&buf[4]);
    char *extname = malloc(namelen + 1);
    struct extension_info *qe;

    if (extname == NULL)
        panic("Can't allocate memory for ExtensionRequest name");
    memcpy(extname, &buf[8], namelen);
    extname[namelen] = '\0';

    for (qe = query_list; qe != NULL; qe = qe->next) {
        if (strcmp(extname, qe->name) == 0) {
            /* already in list, no need to add */
            free(extname);
            return;
        }
    }

    /* add to list */
    qe = malloc(sizeof(struct extension_info));
    if (qe == NULL)
        panic("Can't allocate memory for extension_info");
    qe->name = extname;
    qe->request = 0;
    qe->event = 0;
    qe->error = 0;
    qe->query_seq = seq;
    qe->next = query_list;
    query_list = qe;
}
