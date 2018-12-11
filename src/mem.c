#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mem.h"
#include "defs.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// MEMORY VARIABLES
//
static size_t CM = 0; // CURRENT HEAP MEMORY
static size_t PM = 0; // PEAK HEAP MEMORY
static size_t RS = 0; // RESET HAS BEEN DONE

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// WARN ERROR AND QUIT
//
static void ErrorQuit(size_t s){
  fprintf(stderr, "[x] Error allocating %zu bytes.\n", s);
  exit(1);
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// MALLOC AND INCREMENT MEMORY TRACK
//
void *Malloc(size_t s){
  void *p = malloc(s);
  if(p == NULL) ErrorQuit(s);
  CM += s;
  PM = MAX(CM, PM);
  return p;
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// CALLOC AND INCREMENT MEMORY TRACK
//
void *Calloc(size_t n, size_t s){
  void *p = calloc(n, s);
  if(p == NULL) ErrorQuit(s);
  CM += n*s;
  PM  = MAX(CM, PM);
  return p;
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// REALLOC AND INCREMENT MEMORY TRACK
//
void *Realloc(void *r, size_t s, size_t a){
  void *p = realloc(r, s);
  if(p == NULL) ErrorQuit(s);
  CM += a;
  PM = MAX(CM, PM);
  return p;
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// FREE POINTER AND DECREMENT MEMORY VALUE
//
void Free(void *p, size_t s){
  CM -= s;
  free(p);
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// REMOVE A PIECE OF FREED MEMORY WITH S = 0
// 
void RemovePiece(size_t s){
  CM -= s;
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// RETURN CURRENT MEMORY USAGE
//
size_t CurrMem(void){
  return CM;
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// RETURN PEAK MEMORY USAGE
//
size_t PeakMem(void){
  return PM;
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// RESTART PEAK MEMORY USAGE USING THE CURRENT MEMORY VALUE
//
void RestartPeak(void){
  PM = CM;
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// RESTART PEAK MEMORY USAGE USING THE CURRENT MEMORY VALUE AND SET RS USED (1)
//
void RestartPeakAndRS(void){
  PM = CM;
  RS = 1;
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// HUMAN READABLE MEMORY PRINT
//
void PrintHRBytes(int64_t b){
  int32_t u = 1024, e;
  double s;
  uint8_t t[] = {'K','M','G','T','E','Z','Y'};
  if(b < u) fprintf(stderr, "%"PRIi64" B", b);
  else{
    e = log(b)/log(u);
    s = (double)b/pow((double)u, (double)e);
    fprintf(stderr, "%.1lf %cB", s, t[e-1]);
    }
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// PRINT CUMULATIVE MEMORY
//
void PrintCurrMem(void){
  fprintf(stderr, "[i] Current Heap memory: ");
  PrintHRBytes(CurrMem());
  fprintf(stderr, "\n");
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// PRINT MAXIMUM PEAK MEMORY
//
void PrintRAM(int64_t b){
  fprintf(stderr, "[i] Minimum RAM to uncompress the file: ");
  if(RS == 0) PrintHRBytes(PeakMem()); else PrintHRBytes(b);
  fprintf(stderr, "\n");
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
