#ifndef FCM_H_INCLUDED
#define FCM_H_INCLUDED

#include <string.h>
#include "defs.h"
#include "mem.h"
#include "phash.h"

#define HASH_TABLE  2
#define ARRAY_TABLE 0
#define DEEP_CTX    268435457  // (4^14)+1

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// MODELS SCHEME
//
typedef uint16_t    ACC;        // SIZE OF COUNTERS FOR COUNTER TABLE [8|16|32]

#define MAXACC_C    (((uint64_t)1<<(sizeof(ACC)   *8))-1)

typedef struct{
  ACC      *cnts;     // TABLE COUNTERS
  }
ARRAY;

typedef struct{
  uint64_t nPMod;     // MAXIMUM NUMBER OF PROBABILITY MODELS
  uint64_t mult;      // MULTIPLICATOR TO CALCULATE INDEX
  uint64_t idx;       // CURRENT CONTEXT INDEX
  uint64_t idxRev;    // CURRENT INVERTED REPEAT CONTEXT INDEX
  uint32_t aDen;      // ESTIMATOR DENOMINATOR
  uint32_t ctx;       // CONTEXT ORDER FOR THE FCM
  uint32_t *freqs;    // FCM SYMBOL PROBABILITIES
  uint8_t  rev;       // INVERSIONS USAGE
  uint8_t  nSym;      // FCM NUMBER OF SYMBOLS
  uint8_t  mode;      // USING HASH-TABLES OR NOT [COUNTER=0]
  ARRAY    A;         // COUNTER-TABLE LINK
  PHASH    *H;        // HASH-TABLE LINK WITH 16 BITS
  }
FCM;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void        Reset4DnaModel  (FCM *);
void        Free4DnaModel   (FCM *);
void        Update4DnaFCM   (FCM *, uint32_t, uint8_t);
FCM         *Create4DnaFCM  (uint32_t, uint32_t, uint8_t, uint8_t);
void        Compute4DnaFCM  (FCM *);
uint32_t    CompProbs       (FCM *, uint32_t);
void        GetIdx4DnaRev   (uint8_t *, FCM *);
void        GetIdx4Dna      (uint8_t *, FCM *);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#endif




