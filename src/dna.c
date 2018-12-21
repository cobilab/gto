#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "dna.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// CONVERSION FROM NUMERICAL {0,1,2,3} TO SYMBOLICAL DNA {A,C,G,T}
//
uint8_t N2S(uint8_t x){
  switch(x){
    case 0: return 'A'; case 1: return 'C';
    case 2: return 'G'; case 3: return 'T';
    }
  printf("[x] Unknown numercial symbol!\n");
  exit(1);
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// CONVERSION FROM SYMBOLICAL DNA {A,C,G,T} TO NUMERICAL{0,1,2,3}
//
uint8_t S2N(uint8_t x){
  switch(x){
    case 'A': return 0; case 'C': return 1;
    case 'G': return 2; case 'T': return 3;
    }
  printf("[x] Dound ascii index: %d. Alphabet is limited to {ACGT}!\n", x);
  exit(1);
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// NUMERICAL COMPLEMENT CONVERSION {0,1,2,3} -> {3,2,1,0} (SAME AS: 3-BASE)
//
uint8_t Comp(uint8_t x){
  switch(x){
    case 0: return 3; case 1: return 2; case 2: return 1; case 3: return 0;
    default: return x;
    }
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// CALCULATION OF CONTEXT MULTIPLICATOR FOR INDEX FUNCTION USAGE
//
uint64_t CalcMult(uint32_t c, uint32_t s){
  uint32_t n;
  uint64_t x[c], p = 1;
  for(n = 0 ; n < c ; ++n){ x[n] = p; p *= s; }
  return x[c-1];
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// ASSIGN COUNTER BASES TO DNA
//
void AssignLowerBase(uint8_t *b, uint8_t c){
  switch(c){
    case 'A': b[0]++; break;
    case 'C': b[1]++; break;
    case 'G': b[2]++; break;
    case 'T': b[3]++; break;
    default: return;
    }
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// CALCULATE LOWER FREQUENT BASE
//
uint8_t CalcLessFreq(uint8_t *b){
  uint8_t x, min = b[0], i = 0;
  for(x = 1 ; x < NSYM ; ++x)
    if(min > b[x]){
      min = b[x];
      i = x;
      }
  return i;
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
