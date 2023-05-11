//
// Created by dingjing on 23-5-10.
//

#ifndef XSCOPE_CORE_LOG_H
#define XSCOPE_CORE_LOG_H
#include <glib.h>

#ifdef __cplusplus
extern "C" {
#endif
#define panic(...) \
    {              \
        g_warning(__VA_ARGS__); \
        exit(1); \
    }

#ifdef __cplusplus
};
#endif

#endif //XSCOPE_CORE_LOG_H
