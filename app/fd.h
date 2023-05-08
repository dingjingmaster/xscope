//
// Created by dingjing on 23-5-8.
//

#ifndef XSCOPE_FD_H
#define XSCOPE_FD_H
#include <stdbool.h>



typedef int                             FD;
typedef struct FDInfo                   FDInfo;
typedef struct FDDescriptor             FDDescriptor;
typedef void*                           XtransConnInfo;

struct FDDescriptor
{
    bool                busy;
    void (*InputHandler) (int);
    void (*FlushHandler) (int);
};

struct FDInfo
{
    bool                server;
    int                 clientNumber;
    FD                  pair;
    unsigned char*      buffer;

    int                 bufCount;
    int                 bufStart;
    int                 bufLimit;
    int                 bufDelivered;
    bool                writeBlocked;
};


void initialize_fd (void);

void not_using_fd (FD fd);
void using_fd (FD fd, void (*Handler) (int), void (*FlushHandler) (int), XtransConnInfo transConn);

void close_fd (FD fd);

int main_loop (void);

#endif //XSCOPE_FD_H
