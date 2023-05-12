//
// Created by dingjing on 23-5-12.
//

#include "print-type.h"

#include <stdio.h>
#include <string.h>

#include "../global.h"

#define MAX_INDENT                      10
#define DUMP_HEX_BUFFER_MAX_LINE        78

static int      gCurrentLevel = 0;
char            gLeader[MAX_INDENT + 1];


void set_indent_level (int which)
{
    short i;

    if (which > MAX_INDENT) {
        which = MAX_INDENT;
    }

    if (which < 0) {
        which = 0;
    }

    if (which == gCurrentLevel) {
        return;
    }

    /* set the indent level to <which> */
    /* -> set the Print gLeader to <which> tabs */
    for (i = 0; i < which; i++) {
        gLeader[i] = '\t';
    }

    gLeader[which] = '\0';
    gCurrentLevel = which;
}

void modify_indent_level (int amount)
{
    set_indent_level (gCurrentLevel + amount);
}

int sizeof_leader (void)
{
    return (gCurrentLevel * 8);
}

void dump_item (const char *name, int fd, const unsigned char *buf, long n)
{
    if (n == 0) {
        return;
    }

    fprintf(stdout, "%s%20s (fd %d): ", gLeader, name, fd);

    dump_hex_buffer (buf, n);

    fprintf(stdout, "\n");
}

const char* print_rep(unsigned short c)
{
    static char pr[8];

    if (c < 32) {
        /* control characters */
        pr[0] = '^';
        pr[1] = c + 64;
        pr[2] = '\0';
    }
    else if (c < 127) {
        /* printing characters */
        pr[0] = (char) c;
        pr[1] = '\0';
    }
    else if (c == 127) {
        return ("<del>");
    }
    else if (c <= 0377) {
        /* upper 128 codes from 128 to 255;  print as \ooo - octal  */
        pr[0] = '\\';
        pr[3] = '0' + (c & 7);
        c = c >> 3;
        pr[2] = '0' + (c & 7);
        c = c >> 3;
        pr[1] = '0' + (c & 3);
        pr[4] = '\0';
    }
    else {
        /* very large number -- print as 0xffff - 4 digit hex */
        snprintf(pr, sizeof(pr), "0x%04x", c);
    }

    return (pr);
}


void dump_hex_buffer (const unsigned char *buf, long n)
{
    long i;
    short column;
    char h[6]; /* one hex or octal character */

    column = 27 + sizeof_leader();
    for (i = 0; i < n; i++) {
        /* get the hex representations */
        snprintf(h, sizeof(h), "%02x", (0xff & buf[i]));

        /* check if these characters will fit on this line */
        if ((column + strlen(h) + 1) > DUMP_HEX_BUFFER_MAX_LINE) {
            /* line will be too long -- print it */
            fprintf(stdout, "\n");
            column = 0;
        }
        fprintf(stdout, "%s ", h);
        column += 3;
    }
}