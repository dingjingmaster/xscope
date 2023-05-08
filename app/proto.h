//
// Created by dingjing on 23-5-8.
//

#ifndef XSCOPE_PROTO_H
#define XSCOPE_PROTO_H


extern void initialize_x11 (void);

extern void initialize_audio (void);

extern void stop_client_connection (FD fd);
extern void stop_server_connection (FD fd);

void report_from_client(FD fd, const unsigned char *buf, long n);
void report_from_server(FD fd, const unsigned char *buf, long n);

extern void print_time(void);

#endif //XSCOPE_PROTO_H
