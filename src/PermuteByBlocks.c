#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <ctype.h>
#include "defs.h"
#include "misc.h"
#include "argparse.h"
#include "mem.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

typedef struct{
  uint8_t  *buf;
  uint64_t size;
  }
Seq;

typedef struct{
  int      idx;
  uint64_t x;
  }
Pair;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int Compare(const Pair *a, const Pair *b){
  return a->x>b->x;
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void ReadSeq(Seq *seq){
  int c;
  uint64_t size = BUF_SIZE;
  seq->buf  = (uint8_t *) Calloc(BUF_SIZE, sizeof(uint8_t));
  seq->size = 0;
  while((c = getc(stdin)) != EOF){
    if(c == '>'){
      while((c = fgetc(stdin)) != EOF && c != '\n')
        ;
      continue;
      }
    if(c == '\n')
      continue;

    if(seq->size == size)
      seq->buf = (uint8_t *) Realloc(seq->buf, (size += BUF_SIZE) * 
      sizeof(uint8_t), BUF_SIZE * sizeof(uint8_t));

    seq->buf[seq->size++] = c;
    }
  }

/*
 * This application permutates by block sequence, FASTA and Multi-FASTA files.
 */
int main(int argc, char *argv[])
{
  int n, k, numBases = 100, nBlocks;
  uint32_t seed = 0;
  Pair *pair;
  Seq  *seq = (Seq *) Calloc(1, sizeof(Seq));

  char *programName = argv[0];
  struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_INTEGER('b', "numbases", &numBases, "The number of bases in each block (default 100)"),
        OPT_INTEGER('s', "seed", &seed, "Starting point to the random generator"),
        OPT_BUFF('<', "input", "Input sequence, FASTA or Multi-FASTA file format (stdin)"),
        OPT_BUFF('>', "output", "Output sequence, FASTA or Multi-FASTA file format (stdout)"),
        OPT_END(),
  };
  struct argparse argparse;

  char usage[250] = "\nExample: "; 
  strcat(usage, programName);
  strcat(usage, " -b <numbases> -s <seed> < input.fasta > output.fasta\n");

  argparse_init(&argparse, options, NULL, programName, 0);
  argparse_describe(&argparse, "\nIt permutates by block sequence, FASTA and Multi-FASTA files.", usage);
  argc = argparse_parse(&argparse, argc, argv);

  if(argc != 0)
    argparse_help_cb(&argparse, options);

  if(numBases <= 0 || numBases > UINT_MAX)
  {
    fprintf(stderr, "\nERROR: The numbases value most be a positive unsigned int!\n");
    argparse_help_cb(&argparse, options);
    exit(1);
  }

  if(seed < 0 || seed > UINT_MAX)
  {
    fprintf(stderr, "ERROR: The seed value most be a unsigned int!\n");
    argparse_help_cb(&argparse, options);
    exit(1);
  }
  
  srand(seed);

  ReadSeq(seq);
  nBlocks = (seq->size - 1) / numBases + 1;

  pair = (Pair *) Calloc(nBlocks, sizeof(Pair));
  for(n = 0 ; n < nBlocks ; ++n)
  {
    pair[n].idx = n;
    pair[n].x   = rand();
  }

  qsort(pair, nBlocks, sizeof(Pair), (int (*) (const void *, const void *)) 
  Compare);

  for(n = 0 ; n < nBlocks ; ++n)
    for(k = 0 ; k < numBases ; ++k)
      if(numBases * pair[n].idx + k < seq->size)
        putchar(seq->buf[numBases * pair[n].idx + k]);

  Free(seq->buf, seq->size * sizeof(uint8_t));
  Free(seq, sizeof(Seq));
  Free(pair, nBlocks * sizeof(Pair));
  return EXIT_SUCCESS;
}