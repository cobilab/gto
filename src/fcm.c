#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "fcm.h"
#include "misc.h"
#include "dna.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static HCCs hzeroCnts = {0x00, 0x00, 0x00, 0x00};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// INITIALIZE 4 SYMBOL ARRAY TABLE
//
static void Init4DnaArrayTab(FCM *M){
  M->A.cnts = (ACC *) Calloc(M->nPMod<<2, sizeof(ACC));
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// RESET MODEL
//
void Reset4DnaModel(FCM *M){
  switch(M->mode){
    case HASH_TABLE:
      ResetPHash(M->H);
    break;
    default:
      Free(M->A.cnts, (M->nPMod<<2) * sizeof(ACC)); 
      Init4DnaArrayTab(M); 
    break;
    }
  M->idx = 0; M->idxRev = 0;
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// FREE MODEL
//
void Free4DnaModel(FCM *M){
  switch(M->mode){
    case HASH_TABLE:
      DeletePHash(M->H);
    break;
    default: 
      Free(M->A.cnts, (M->nPMod<<2) * sizeof(ACC));
    break;
    }
  Free(M->freqs, 5 * sizeof(uint32_t));
  Free(M, sizeof(FCM));  
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// UPDATE FCM COUNTERS
//
void Update4DnaFCM(FCM *M, uint32_t c, uint8_t ir){
  ACC *ac;
  uint64_t idx = (ir == 0) ? M->idx : M->idxRev;
  if(M->mode == HASH_TABLE){
    UpdatePHash(M->H, idx, c);
    }
  else{
    ac = &M->A.cnts[idx<<2];
    if(++ac[c] == MAXACC_C){ ac[0]>>=1; ac[1]>>=1; ac[2]>>=1; ac[3]>>=1; }
    }
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// CREATES 4 SYMBOL FCM
//
FCM *Create4DnaFCM(uint32_t c, uint32_t a, uint8_t i, uint8_t n){
  FCM    *M = (FCM *) Calloc(1, sizeof(FCM));
  M->nSym   = n;
  M->ctx    = c;
  M->rev    = i;
  M->aDen   = a;
  M->mult   = CalcMult(c, n);
  M->idx    = 0;
  M->idxRev = 0;
  M->freqs  = (uint32_t *) Calloc(M->nSym+1, sizeof(uint32_t));
  M->nPMod  = (uint64_t) pow(n,c);

  if(M->nPMod < DEEP_CTX){
    Init4DnaArrayTab(M);
    M->mode = 0;
    }
  else{
    M->H = CreatePHash();
    M->mode = 2;
    }

  return M;
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// COMPUTE SPECIFIC 4 SYMBOL FCM PROBABILITIES
//
void Compute4DnaFCM(FCM *M){
  HCC *h;
  ACC *a;
  if(M->mode == HASH_TABLE){
    if(!(h = GetPHashCounters(M->H, M->idx))) h = hzeroCnts;
    M->freqs[0] = 1+M->aDen*h[0]; M->freqs[1] = 1+M->aDen*h[1];
    M->freqs[2] = 1+M->aDen*h[2]; M->freqs[3] = 1+M->aDen*h[3];
    }
  else{
    a = &M->A.cnts[M->idx<<2];
    M->freqs[0] = 1+M->aDen*a[0]; M->freqs[1] = 1+M->aDen*a[1];
    M->freqs[2] = 1+M->aDen*a[2]; M->freqs[3] = 1+M->aDen*a[3];
    }
  M->freqs[4] = M->freqs[0]+M->freqs[1]+M->freqs[2]+M->freqs[3];
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// COMPUTE PROBABILITIES
//
uint32_t CompProbs(FCM *M, uint32_t s){
  return Log(M->freqs[M->nSym]/M->freqs[s]);
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// REVERSE COMPLEMENT INDEX BASED ON PAST SYMBOLS FOR FCM WITH 4 SYMBOLS
//
void GetIdx4DnaRev(uint8_t *p, FCM *M){
  M->idxRev = (M->idxRev>>2)+Comp(*p)*M->mult;
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// INDEX CALC BASED ON PAST SYMBOLS FOR FCM WITH 4 SYMBOLS
//
void GetIdx4Dna(uint8_t *p, FCM *M){
  M->idx = ((M->idx-*(p-M->ctx)*M->mult)<<2)+*p;
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

