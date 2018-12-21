#include <stdio.h>
#include <stdlib.h>
#define _GNU_SOURCE
#include <string.h>
#include <ctype.h>
#include "labels.h"
#include "mem.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

SLABELS *CreateSLabels(void){
  uint32_t n;
  SLABELS *SL = (SLABELS *) Calloc(1, sizeof(SLABELS));
  SL->idx     = 0;
  SL->maxV    = SLCACHE;
  SL->maxH    = SLMAXSTR;
  SL->names   = (char **) Calloc(SL->maxV, sizeof(char *));
  for(n = 0 ; n < SL->maxV ; ++n)
    SL->names[n] = (char *) Calloc(SL->maxH+1, sizeof(char));
  return SL;
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void AddSLabel(SLABELS *SL, char *str){
  uint32_t n;
  char c;
  for(n = 0 ; n < SL->maxH ; ++n){
    if((c = str[n]) == '\0')
      break;
    SL->names[SL->idx][n] = tolower(c);  
    }
  SL->names[SL->idx][n] = '\0';
  SL->idx++;
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void UpdateSLabels(SLABELS *SL){
  uint32_t n;
  if(SL->idx == SL->maxV){
    SL->maxV += SLCACHE;
    SL->names = (char **) 
    Realloc(SL->names, SL->maxV * sizeof(char *), 0);
    for(n = SL->idx ; n < SL->maxV ; ++n)
      SL->names[n] = (char *) Calloc(SL->maxH+1, sizeof(char));
    }
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int SearchSLabels(SLABELS *SL, char *str){
  uint32_t n;
  for(n = 0 ; n < SL->idx ; ++n)
    if(Strcasecmp(SL->names[n], str) == 0)
      return 1;
  return 0;
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void DeleteSLabels(SLABELS *SL){
  uint32_t n;
  for(n = 0 ; n < SL->maxV ; ++n)
    Free(SL->names[n], 0);
  Free(SL->names, 0);
  Free(SL, 0);
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
