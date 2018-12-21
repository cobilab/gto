#ifndef PHASH_H_INCLUDED
#define PHASH_H_INCLUDED

#include "defs.h"
#include "mem.h"

typedef uint16_t    KEYP;      // PRECISION OF EACH KEY
typedef uint8_t     HCC;       // SIZE OF COUNTERS FOR HASH TABLE
typedef uint8_t     ENTMAX;    // ENTRY SIZE (NKEYS FOR EACH HINDEX)
typedef HCC         HCCs[4];   // DEFAULT HASH COUNTERS

#define HSIZE       25165843 //33554471   // USE VALUE HIGHER THAN 24 BITS
#define MAXHSIZE    (((uint64_t)1<<(sizeof(ENTMAX)*8))-1)
#define MAXHC       (((uint64_t)1<<(sizeof(HCC)   *8))-1)
#define MAXHH       3

typedef struct{     // ENTRY FOR 4 SYMBOLS
  KEYP     key;     // THE KEY (INDEX / HASHSIZE) STORED IN THIS ENTRY
  HCC      cnts;    // SMALL COUNTERS [2 BITS P/ SYMBOL]
  }
ENTRY;

typedef struct{     // HASH FOR 4 SYMBOLS
  ENTMAX   *size;   // NUMBER OF KEYS FOR EACH ENTRY
  ENTRY    **ent;   // THE HEADS OF THE HASH TABLE LISTS
  HCCs     **cnts;  // THE CONTEXT COUNTERS
  }
PHASH;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void     ResetPHash         (PHASH *);
PHASH    *CreatePHash       (void);
void     DeletePHash        (PHASH *);
HCC      *GetPHashCounters  (PHASH *, uint64_t);
void     UpdatePHash        (PHASH *, uint64_t, uint8_t);
void     PrintNEnt          (PHASH *);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#endif
