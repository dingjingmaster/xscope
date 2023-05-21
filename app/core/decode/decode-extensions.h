//
// Created by dingjing on 23-5-18.
//

#ifndef XSCOPE_DECODE_EXTENSIONS_H
#define XSCOPE_DECODE_EXTENSIONS_H

#include <malloc.h>

#define EXTENSION_MIN_REQ                       128     // lowest possible extension request code
#define EXTENSION_MAX_REQ                       255     // highest possible extension request code
#define EXTENSION_MIN_EV                        64      // lowest possible extension event code
#define EXTENSION_MAX_EV                        127     // highest possible extension event code
#define EXTENSION_MIN_ERR                       128     // lowest possible extension error code
#define EXTENSION_MAX_ERR                       255     // highest possible extension error code
#define NUM_EXTENSIONS                          128     // maximum possible number of extensions
#define NUM_EXT_EVENTS                          64      // maximum possible number of extension events

typedef void (*ExtensionDecodeReqPtr)   (const unsigned char *buf);
typedef void (*ExtensionDecodeErrorPtr) (const unsigned char *buf);
typedef void (*ExtensionDecodeEventPtr) (const unsigned char *buf);
typedef void (*ExtensionDecodeReplyPtr) (const unsigned char *buf, short RequestMinor);


typedef struct ExtensionInfo                    ExtensionInfo;
typedef struct ExtensionDecoders                ExtensionDecoders;

struct ExtensionInfo
{
    const char*             name;
    unsigned char           request;
    unsigned char           event;
    unsigned char           error;
//    long                    querySeq;       // sequence id of QueryExtension request
    ExtensionInfo*          next;
};

struct ExtensionDecoders
{
    const char*     name;
    void (*initFunc) (const unsigned char* buf);
};





void extensions_request(const unsigned char *buf, short req);
void extensions_process_query_request(const unsigned char *buf);

#endif //XSCOPE_DECODE_EXTENSIONS_H
