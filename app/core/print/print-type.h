//
// Created by dingjing on 23-5-12.
//

#ifndef XSCOPE_PRINT_TYPE_H
#define XSCOPE_PRINT_TYPE_H

int sizeof_leader           (void);
void set_indent_level       (int which);
void modify_indent_level    (int amount);
void dump_hex_buffer        (const unsigned char *buf, long n);


//const char* print_rep       (unsigned short c);


#endif //XSCOPE_PRINT_TYPE_H
