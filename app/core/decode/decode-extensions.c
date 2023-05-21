//
// Created by dingjing on 23-5-18.
//

#include "decode-extensions.h"


#include "tools.h"
#include "core-log.h"


ExtensionInfo*  gQueryList;
ExtensionInfo*  gExtByRequest[NUM_EXTENSIONS];
static ExtensionDecodeReqPtr   gExtensionRequestDecoder[NUM_EXTENSIONS];
static ExtensionDecodeReplyPtr gExtensionReplyDecoder[NUM_EXTENSIONS];
static ExtensionDecodeErrorPtr gExtensionErrorDecoder[NUM_EXTENSIONS];
static ExtensionDecodeEventPtr gExtensionEventDecoder[NUM_EXT_EVENTS];
static ExtensionDecodeEventPtr gGenericEventDecoder[NUM_EXTENSIONS];


void extensions_process_query_request(const unsigned char *buf)
{
    int namelen = tools_short (&buf[4]);
    char* extname = malloc (namelen + 1);
    ExtensionInfo*  qe;

    if (extname == NULL) {
        panic("Can't allocate memory for ExtensionRequest name");
    }

    memcpy(extname, &buf[8], namelen);
    extname[namelen] = '\0';

    for (qe = gQueryList; qe != NULL; qe = qe->next) {
        if (0 == strcmp(extname, qe->name)) {
            /* already in list, no need to add */
            free(extname);
            return;
        }
    }

    /* add to list */
    qe = malloc(sizeof(ExtensionInfo));
    if (qe == NULL) {
        panic("Can't allocate memory for extension_info");
    }

    qe->name = extname;
    qe->request = 0;
    qe->event = 0;
    qe->error = 0;
    qe->next = gQueryList;
    gQueryList = qe;
}

void extensions_request(const unsigned char *buf, short req)
{
    ExtensionDecodeReqPtr decodeReq = NULL;

    if ((req <= EXTENSION_MAX_REQ) && (req >= EXTENSION_MIN_REQ)) {
        decodeReq = gExtensionRequestDecoder[req - EXTENSION_MIN_REQ];
    }

    if (NULL != decodeReq) {
        decodeReq(buf);
    }
    else {
        g_warning("shixian ...");
    }
}
