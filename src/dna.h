#ifndef DNA_H_INCLUDED
#define DNA_H_INCLUDED

#include "defs.h"

#define NSYM 4

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

uint8_t  N2S             (uint8_t);
uint8_t  S2N             (uint8_t);
uint8_t  Comp            (uint8_t);
uint64_t CalcMult        (uint32_t, uint32_t);
void     AssignLowerBase (uint8_t *, uint8_t);
uint8_t  CalcLessFreq    (uint8_t *);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#endif