#ifndef READS_H_INCLUDED
#define READS_H_INCLUDED

#include "defs.h"

#define DEF_HEADER_SIZE  4096
#define DEF_READ_SIZE    4096
#define READ_LGUARD      32

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

typedef struct{
  uint8_t    *header1;
  uint8_t    *bases;
  uint8_t    *header2;
  uint8_t    *scores;
  uint64_t   headerMaxSize;
  uint64_t   readMaxSize;
  uint64_t   solidData;
  uint64_t   header2Present;
  uint64_t   skipNs;
  uint8_t    lowestScore;
  }
Read;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

uint8_t  PseudoDna2Solid  (uint8_t);
uint8_t  Solid2PseudoDna  (uint8_t);
Read     *CreateRead      (uint64_t, uint64_t);
void     FreeRead         (Read *);
void     PrintRead        (Read *, FILE *);
Read     *GetRead         (FILE *, Read *);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#endif
