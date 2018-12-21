#ifndef CSMODEL_H_INCLUDED
#define CSMODEL_H_INCLUDED

#include "defs.h"

typedef struct{
  uint64_t *mult;
  uint32_t ctx;
  uint32_t nSym;
  }
CSMODEL;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

CSMODEL         *CreateCSModel    (uint32_t, uint32_t);
uint64_t        GetCSIdx          (uint8_t *, CSMODEL *);
void            DeleteCSModel     (CSMODEL *);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#endif

