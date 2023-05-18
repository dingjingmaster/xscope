//
// Created by dingjing on 23-5-16.
//

#ifndef XSCOPE_DECODE_H
#define XSCOPE_DECODE_H
#include <glib.h>
#include <stdbool.h>

#include "../io/io.h"


/**
 * @brief X协议解析主要入口
 *
 * @param buf 要解析的buf内容
 * @param print 要输出的内容，需要被释放
 *
 * @todo char** print 需要用结构化数据来代替
 */
bool decode_x_client (IOContext* ioCtx);

bool decode_x_server (IOContext* ioCtx);


#endif //XSCOPE_DECODE_H
