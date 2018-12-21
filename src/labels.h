#ifndef LABELS_H_INCLUDED
#define LABELS_H_INCLUDED

#include "defs.h"
#include "common.h"
#include <stdlib.h>
#include <stdio.h>

#define SLCACHE  1000
#define SLMAXSTR 5000

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

typedef struct{
  char     **names;
  uint32_t maxH;
  uint32_t maxV;
  uint32_t idx;
  }
SLABELS;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

SLABELS    *CreateSLabels  (void);
void       AddSLabel       (SLABELS *, char *);
void       UpdateSLabels   (SLABELS *);
int        SearchSLabels   (SLABELS *, char *);
void       DeleteSLabels   (SLABELS *);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#endif
