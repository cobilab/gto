#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "misc.h"
#include "mem.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// REPLACE STRING
//
char *ReplaceSubStr(char *str, char *a, char *b){
  char *buf = (char *) Calloc(MAX_STR, sizeof(char));
  char *p;
  if(strlen(str) > MAX_STR){
    fprintf(stderr, "[x] Error: string too long!\n");
    exit(1);
    }
  if(!(p = strstr(str, a))) 
    return str;
  strncpy(buf, str, p-str);
  buf[p-str] = '\0';
  sprintf(buf+(p-str), "%s%s", b, p+strlen(a));
  return buf;
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// APPROXIMATE FUNCTION FOR LOG
//
uint32_t Log(uint64_t i){
  uint32_t n, m, k = 32, o = (i&(i-1))?1:0;
  static const uint64_t sizes[6] =
  { 0x0000000000000002ull, 0x000000000000000Cull, 0x00000000000000F0ull,
    0x000000000000FF00ull, 0x00000000FFFF0000ull, 0xFFFFFFFF00000000ull };
  for(n = 6 ; n-- ; ){
    o += (m=(i&*(sizes+n))?k:0);
    i >>= m;
    k >>= 1;
    }
  return o * 0.69314718f;
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// APPROXIMATED POWER FUNCTION [A LOT FASTER] http://martin.ankerl.com/
// 2007/10/04/optimized-pow-approximation-for-java-and-c-c/
//
double PW(double a, double b){
  int32_t t = (*(1+(int32_t *)&a)), u = (int32_t)(b*(t-MPW)+MPW);
  double p = 0;
  *(1+(int32_t *)&p) = u;
  return p;
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// SIMPLE STRINGS CONCATENATION FUNCTION 
//
char *Cat(char *a, char *b){
  char *c = (char *) Malloc(strlen(a)+strlen(b)+1);
  strcpy(c, a);
  strcat(c, b);
  return c;
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// SIMPLE OPEN FILE
//
FILE *Fopen(const char *p, const char *m){
  FILE *F = fopen(p, m);
  if(F == NULL){
    fprintf(stderr, "[x] Error opening: %s (mode %s). Does it exists?\n", p, m);
    exit(1);
    }
  return F;
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// CHECK IF FILE EXISTS WHEN PARAM FORCE IS NOT ON
//
void CheckFile(uint8_t s, char *fn){
  if(access(fn, F_OK) != -1 && s == 0){
    fprintf(stderr, "[x] Error: file %s already exists!\n", fn);
    if(access(fn, W_OK) != -1)
      fprintf(stderr, "[i] Note: file has write permission.\n[i] Tip: to force "
      "writing rerun with \"-f\" option.\n[i] On forcing, the old file will be "
      "deleted permanently.\n");
    exit(1);
    }
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// NUMBER OF BYTES IN A FILE
//
uint64_t FNBytes(FILE *F){
  uint64_t n = 0;
  fseeko(F, 0, SEEK_END);
  n = ftello(F);
  rewind(F);
  return n;
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// PROGRESS PERCENTAGE OF A COMPUTATION
//
void Progress(uint64_t s, uint64_t i){
  if(i%(s/100) == 0 && s > 99)
    fprintf(stderr, "Progress:%3d %%\r", (uint8_t) (i/(s/100)));
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// REVERSE A STRING
//
void ReverseStr(uint8_t *a, uint8_t *b, uint32_t s){
  uint64_t n;
  for(n = 0 ; n < s ; ++n)
    b[s-n-1] = a[n];
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// PACK 8 BITS IN 1 BYTE
//
uint8_t Pack8bits(uint8_t *b){
  return b[7]|b[6]<<1|b[5]<<2|b[4]<<3|b[3]<<4|b[2]<<5|b[1]<<6|b[0]<<7;
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

