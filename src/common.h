#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#include "defs.h"
#include "misc.h"

typedef struct{
  uint64_t size;
  uint64_t bytes;
  }
INF;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int32_t     Strcasecmp       (const char *, const char *);
double      BoundDouble      (double, double, double);
int         FileExists       (const char *);
uint8_t     DNASymToNum      (uint8_t  );
uint8_t     NumToDNASym      (uint8_t  );
uint8_t     GetCompNum       (uint8_t  );
uint8_t     GetCompSym       (uint8_t  );
uint64_t    NDNASyminFile    (FILE *);
uint64_t    NDNASymInFastq   (FILE *);
uint64_t    NDNASymInFasta   (FILE *);
uint64_t    NBytesInFile     (FILE *);
uint64_t    FopenBytesInFile (const char *);
void        TestReadFile     (char *);
void        CalcProgress     (uint64_t , uint64_t);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#endif
