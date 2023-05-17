//
// Created by dingjing on 23-5-12.
//

#include "xproto.h"

#include <stdio.h>

#include "core-log.h"
#include "xtype-set.h"
#include "xtype-values.h"
#include "xtype-builtin.h"
#include "xtype-enumerated.h"


unsigned char   gRBf[2];
unsigned char   gSBf[4];
ConnState*      gCS = NULL;
TypeDef         gTD[MaxTypes];


Type define_type (short typeid, short class, const char *name, char* (*printProc) (const unsigned char*))
{
    gTD[typeid].name = name;
    gTD[typeid].type = class;
    gTD[typeid].valueList = NULL;
    gTD[typeid].printProc = printProc;

    return (&gTD[typeid]);
}

void xproto_init()
{
    // init built in types
    xtype_builtin_init();
    xtype_enumerated_init();
    xtype_set_init();
    xtype_values_init();

}

const char *get_key_string(unsigned short c)
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

void define_evalue(Type type, long value, const char *name)
{
    struct ValueListEntry *p;

    /* define the new value */
    p = malloc(sizeof(struct ValueListEntry));
    if (p == NULL) {
        panic("Can't allocate memory for Enum ValueListEntry");
    }

    p->name = name;
    p->value = value;

    /* add an new value to the list. */
    if (type->valueList == NULL || type->valueList->value > p->value) {
        p->next = type->valueList;
        type->valueList = p;
    }
    else {
        /* keep the list sorted, smallest to largest */
        struct ValueListEntry *q = type->valueList;

        while (q->next != NULL && q->next->value < p->value) {
            q = q->next;
        }
        p->next = q->next;
        q->next = p;
    }
}

void define_values(Type type, long value, short length, short ctype, const char *name)
{
    struct ValueListEntry *p;

    p = malloc(sizeof(struct ValueListEntry));
    if (p == NULL)
    panic("Can't allocate memory for ValueListEntry");
    p->name = name;
    p->type = ctype;
    p->length = length;
    p->value = value;

    /* add an new value to the list. */
    if (type->valueList == NULL || type->valueList->value > p->value) {
        p->next = type->valueList;
        type->valueList = p;
    }
    else {
        /* keep the list sorted, smallest to largest  */
        struct ValueListEntry *q = type->valueList;

        while (q->next != NULL && q->next->value < p->value) {
            q = q->next;
        }
        p->next = q->next;
        q->next = p;
    }
}
