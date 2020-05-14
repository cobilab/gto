#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "defs.h"
#include "misc.h"
#include "buffer.h"
#include "argparse.h"
#include <unistd.h>

/*
 * This application creates a synthetic mutation of a sequence file given specific 
 * rates of editions, deletions and additions
 */
int main(int argc, char *argv[])
{
  uint32_t streamSize, index;
  int value, randomValue, seed = 0, nSymbols = 4, useACGTN = 0;
  double mutationRate = 0, deletionRate = 0, insertionRate = 0;
  char *bases = "ACGT";
  BUF *Buffer;

  char *programName = argv[0];
  struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_BUFF('<', "input.seq", "Input sequence file (stdin)"),
        OPT_BUFF('>', "output.seq", "Output sequence file (stdout)"),
        OPT_GROUP("Optional"),
        OPT_INTEGER('s', "seed", &seed, "Starting point to the random generator"),
        OPT_DOUBLE('m', "mutation-rate", &mutationRate, "Defines the mutation rate (default 0.0)"),
        OPT_DOUBLE('d', "deletion-rate", &deletionRate, "Defines the deletion rate (default 0.0)"),
        OPT_DOUBLE('i', "insertion-rate", &insertionRate, "Defines the insertion rate (default 0.0)"),
        OPT_BOOLEAN('a', "ACGTN-alphabet", &useACGTN, "When active, the application uses the ACGTN alphabet"),
        OPT_END(),
  };
  struct argparse argparse;

  char usage[250] = "\nExample: "; 
  strcat(usage, programName);
  strcat(usage, " -s <seed> -m <mutation rate> -d <deletion rate> -i <insertion rate> -a < input.seq > output.seq\n");

  argparse_init(&argparse, options, NULL, programName, 0);
  argparse_describe(&argparse, "\nCreates a synthetic mutation of a sequence file given specific rates of mutations, deletions and additions", usage);
  argc = argparse_parse(&argparse, argc, argv);

  if(argc != 0 || isatty(STDIN_FILENO))
    argparse_help_cb(&argparse, options);

  if(useACGTN == 1)
  {
    bases = "ACGTN";
    nSymbols = 5;
  }

  if(seed < 0 || seed > UINT_MAX)
  {
    fprintf(stderr, "ERROR: The seed value most be a unsigned int!\n");
    exit(1);
  }

  if(mutationRate < 0 || mutationRate > 1)
  {
    fprintf(stderr, "ERROR: Mutation rate must be a value between 0 and 1!\n");
    exit(1);
  }

  if(deletionRate < 0 || deletionRate > 1)
  {
    fprintf(stderr, "ERROR: Deletion rate must be a value between 0 and 1!\n");
    exit(1);
  }

  if(insertionRate < 0 || insertionRate > 1)
  {
    fprintf(stderr, "ERROR: Insertion rate must be a value between 0 and 1!\n");
    exit(1);
  }

  srand(seed);
  Buffer = CreateBuffer(BUF_SIZE);
  while((streamSize = fread(Buffer->buf, 1, Buffer->size, stdin)))
    for(index = 0 ; index < streamSize ; ++index)
    {
      value = Buffer->buf[index];
      if(rand() / (RAND_MAX + 1.0) < mutationRate)
      {
        while((randomValue = bases[rand() % nSymbols]) == value)
          ;
        putchar(randomValue);
        continue;
      }
      
      if(rand() / (RAND_MAX + 1.0) < deletionRate)
        continue;
      
      if(rand() / (RAND_MAX + 1.0) < insertionRate)
        putchar(bases[rand() % nSymbols]);
      
      putchar(value);
    }

  RemoveBuffer(Buffer);
  return 0;
}