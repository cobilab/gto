#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reads.h"
#include "mem.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// BASE TO SOLID SYMBOL
//
uint8_t PseudoDna2Solid(uint8_t s){
  switch(s){
    case 'A': return '0';
    case 'C': return '1';
    case 'G': return '2';
    case 'T': return '3';
    case 'N': return '.';
    default :  
      fprintf(stderr, "Error: unexpected base value '%c'\n", s);
      exit(1);
    }
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// SOLID SYMBOL TO BASE
//
uint8_t Solid2PseudoDna(uint8_t s){
  switch(s){
    case '0': return 'A';
    case '1': return 'C';
    case '2': return 'G';
    case '3': return 'T';
    case '.': return 'N';
    default: 
      fprintf(stderr, "Error: unexpected cs value '%c'\n", s);
      exit(1);
    }
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// EOF ERROR WARNING AND PROGRAM TERMINATE
//
static void UEOF(void){
  fprintf(stderr, "Error: unexpected end of file\n");
  exit(1);
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// CREATE READ
//
Read *CreateRead(uint64_t HMax, uint64_t RMax){
  Read *R           = (Read *)    Calloc(1,                  sizeof(Read));
  R->header1        = (uint8_t *) Calloc(HMax + READ_LGUARD, sizeof(uint8_t));
  R->header2        = (uint8_t *) Calloc(HMax + READ_LGUARD, sizeof(uint8_t));
  R->bases          = (uint8_t *) Calloc(RMax + READ_LGUARD, sizeof(uint8_t));
  R->scores         = (uint8_t *) Calloc(RMax + READ_LGUARD, sizeof(uint8_t));
  R->headerMaxSize  = HMax;
  R->readMaxSize    = RMax;
  R->header1       += READ_LGUARD;
  R->header2       += READ_LGUARD;
  R->bases         += READ_LGUARD;
  R->scores        += READ_LGUARD;
  R->solidData      = 0;
  R->header2Present = 0;
  R->skipNs         = 0;
  R->lowestScore    = (uint8_t) 255;
  return R;
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// CREATE READ
//
void FreeRead(Read *R){
  Free(R->header1-READ_LGUARD, (R->headerMaxSize+READ_LGUARD) * 
  sizeof(uint8_t));
  Free(R->header2-READ_LGUARD, (R->headerMaxSize+READ_LGUARD) * 
  sizeof(uint8_t));
  Free(R->bases-READ_LGUARD,  (R->readMaxSize+READ_LGUARD) * sizeof(uint8_t));
  Free(R->scores-READ_LGUARD, (R->readMaxSize+READ_LGUARD) * sizeof(uint8_t));
  Free(R, sizeof(Read));
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// GET READ
//
Read *GetRead(FILE *F, Read *R){
  int n, c = fgetc(F);

  if(c == EOF) 
    return NULL;
  if(c != '@'){
    fprintf(stderr, "Error: failed to get the initial '@' char (%d)!\n", c);
    exit(1);
    }

  if(!fgets((char *)R->header1, R->headerMaxSize, F)) UEOF();
  if(!fgets((char *)R->bases,   R->readMaxSize,   F)) UEOF();
  if(!fgets((char *)R->header2, R->headerMaxSize, F)) UEOF();
  if(!fgets((char *)R->scores,  R->readMaxSize,   F)) UEOF();

  if(R->solidData){
    n = 1;
    while(R->bases[n] != '\n'){
      R->bases[n] = Solid2PseudoDna(R->bases[n]);
      n++;
      }
    }

  return R;
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// PRINT READ
//
void PrintRead(Read *R, FILE *F){
  fprintf(F, "@%s", R->header1);
  fprintf(F, "%s", R->bases);
  fprintf(F, "%s", R->header2);
  fprintf(F, "%s", R->scores);
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

