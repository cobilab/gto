#ifndef FILTER_H_INCLUDED
#define FILTER_H_INCLUDED

#include "defs.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#define W_HAMMING       0
#define W_HANN          1
#define W_BLACKMAN      2
#define W_RECTANGULAR   3

typedef struct{
  int    position;
  double value;
  }
Entry;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#endif

