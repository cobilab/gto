#ifndef MISC_H_INCLUDED
#define MISC_H_INCLUDED

#include "defs.h"

#define MPW           1072632447
#define DEF_BUF_GUARD 32
#define DEF_BUF_SIZE  65535
#define GUARD         30
#define BUF_SIZE      65535

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

char     *ReplaceSubStr (char *, char *, char *);
uint32_t Log            (uint64_t);
double   PW             (double, double);
FILE     *Fopen         (const char *, const char *);
void     CheckFile      (uint8_t, char *);
uint64_t FNBytes        (FILE *);
void     Progress       (uint64_t, uint64_t);
void     ReverseStr     (uint8_t *, uint8_t *, uint32_t);
uint8_t  Pack8bits      (uint8_t *);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#endif

