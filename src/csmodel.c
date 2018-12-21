#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mem.h"
#include "csmodel.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

CSMODEL *CreateCSModel(uint32_t ctx, uint32_t nSym){
  uint32_t n;
  uint64_t prod = 1;
  CSMODEL *M = (CSMODEL  *) Calloc(1,   sizeof(CSMODEL));
  M->mult    = (uint64_t *) Calloc(ctx, sizeof(uint64_t));
  M->ctx     = ctx;
  M->nSym    = nSym;
  for(n = 0 ; n < ctx ; ++n){
    M->mult[n] = prod;
    prod *= nSym;
    }
  return M;
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

uint64_t GetCSIdx(uint8_t *buf, CSMODEL *M){
  uint32_t n;
  uint64_t idx = 0;
  for(n = 1 ; n <= M->ctx ; ++n)
    idx += *--buf * M->mult[n-1];
  return idx;
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void DeleteCSModel(CSMODEL *M){
  Free(M->mult, M->ctx * sizeof(uint64_t));
  Free(M, sizeof(CSMODEL));
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
