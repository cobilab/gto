#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "phash.h"
#include "misc.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static HCCs hauxCnts;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void StartPHash(PHASH *H){
  H->ent   = (ENTRY **) Calloc(HSIZE, sizeof(ENTRY *));
  H->cnts  = (HCCs  **) Calloc(HSIZE, sizeof(HCCs  *));
  H->size  = (ENTMAX *) Calloc(HSIZE, sizeof(ENTMAX ));
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void StopPHash(PHASH *H){
  uint32_t k;
  for(k = 0 ; k < HSIZE ; ++k){
    if(H->size[k]) Free(H->ent[k], H->size[k] * sizeof(ENTRY));
    if(H->cnts[k]) Free(H->cnts[k], sizeof(HCCs));
    }
  Free(H->ent,  HSIZE * sizeof(ENTRY *));
  Free(H->cnts, HSIZE * sizeof(HCCs  *));
  Free(H->size, HSIZE * sizeof(ENTMAX ));
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void ResetPHash(PHASH *H){
  StopPHash(H);
  StartPHash(H);
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

PHASH *CreatePHash(void){
  PHASH *H = (PHASH *) Calloc(1, sizeof(PHASH));
  StartPHash(H);
  return H;
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void DeletePHash(PHASH *H){
  StopPHash(H);
  Free(H, sizeof(PHASH));
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void InsertPHashKey(PHASH *T, uint32_t h, KEYP b){
  T->ent[h] = (ENTRY *) Realloc(T->ent[h], (T->size[h]+1) * sizeof(ENTRY),
  sizeof(ENTRY));
  T->ent[h][T->size[h]].key = b;
  T->size[h]++;
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void InsertPHashCounters(PHASH *T, uint32_t h, uint32_t n, uint32_t k,
uint32_t s){
  T->cnts[h] = (HCCs *) Realloc(T->cnts[h], (n+1)*sizeof(HCCs), sizeof(HCCs));
  if(k < n) memmove(T->cnts[h][k+1], T->cnts[h][k], (n-k)*sizeof(HCCs));
  T->cnts[h][k][0] =  s& 0x03;
  T->cnts[h][k][1] = (s&(0x03<<2))>>2;
  T->cnts[h][k][2] = (s&(0x03<<4))>>4;
  T->cnts[h][k][3] = (s&(0x03<<6))>>6;
  }
  
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  

HCC *GetPHashCounters(PHASH *T, uint64_t key){
  uint32_t k = 0, n, h = key % HSIZE;
  KEYP     b = key & 0xffff;

  for(n = 0 ; n < T->size[h] ; ++n){
    if(T->ent[h][n].key == b)
      switch(T->ent[h][n].cnts){
        case 0: return T->cnts[h][k];
        default:
        hauxCnts[0] =  T->ent[h][n].cnts& 0x03;
        hauxCnts[1] = (T->ent[h][n].cnts&(0x03<<2))>>2;
        hauxCnts[2] = (T->ent[h][n].cnts&(0x03<<4))>>4;
        hauxCnts[3] = (T->ent[h][n].cnts&(0x03<<6))>>6;
        return hauxCnts;
        }
    if(T->ent[h][n].cnts == 0) ++k;
    }
  return NULL;
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void UpdatePHash(PHASH *H, uint64_t idx, uint8_t c){
  uint8_t  s;
  uint32_t n, i, k = 0, nh, h = idx % HSIZE;
  KEYP     b = idx & 0xffff;

  if(H->size[h] == MAXHSIZE) return;  // DISCARD DATA LARGER THAN MAXHSIZE
  
  for(n = 0 ; n < H->size[h] ; ++n){
    if(H->ent[h][n].key == b){

      // UPDATE LARGE COUNTERS
      if(H->ent[h][n].cnts == 0){
        if(++H->cnts[h][k][c] == MAXHC){
          H->cnts[h][k][0] >>= 1; H->cnts[h][k][1] >>= 1;
          H->cnts[h][k][2] >>= 1; H->cnts[h][k][3] >>= 1;
          }
        return;
        }

      // UPDATE SMALL COUNTERS : IF REACHES MAXHH CHANGE TO LARGE COUNTERS
      if((s=(H->ent[h][n].cnts>>(c<<1))&0x03) == MAXHH){
        nh = k;
        for(i = n+1 ; i < H->size[h] ; ++i)
          if(H->ent[h][i].cnts == 0) ++nh;
        InsertPHashCounters(H, h, nh, k, H->ent[h][n].cnts);
        H->ent[h][n].cnts = 0; 
        H->cnts[h][k][c]++;
        return;
        }
      else{
        H->ent[h][n].cnts &= ~(0x03<<(c<<1));
        H->ent[h][n].cnts |= (++s<<(c<<1));
        return;
        }

      }
    if(!H->ent[h][n].cnts) ++k;
    }

  InsertPHashKey(H, h, b); // INSERT SMALL COUNTERS
  H->ent[h][H->size[h]-1].cnts = (0x01<<(c<<1));
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void PrintNEnt(PHASH *H){
  FILE *E = Fopen("ENT.txt", "w");
  int x;
    for(x = 0 ; x < HSIZE ; ++x)
    fprintf(E, "%u\n", H->size[x]);
  fclose(E);
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

