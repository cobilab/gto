#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <ctype.h>
#include <string.h>
#include "defs.h"
#include "mem.h"
#include "misc.h"
#include "argparse.h"

/*
 * This application gives the basic properties of the file, namely
 * size, cardinality, distribution percentage of the symbols, among others.
 */
int main(int argc, char *argv[])
{
  uint32_t  n, streamSize, idxPos, nSym;
  uint64_t  nBytes, *counts;
  uint8_t   *buf, *mask, *norm_alp, *alp, sym;
  int showASCII = 0;

  buf       = (uint8_t  *) Calloc(BUFFER_SIZE,  sizeof(uint8_t ));
  alp       = (uint8_t  *) Calloc(MAX_ALPHABET, sizeof(uint8_t ));
  norm_alp  = (uint8_t  *) Calloc(MAX_ALPHABET, sizeof(uint8_t ));
  mask      = (uint8_t  *) Calloc(MAX_ALPHABET, sizeof(uint8_t ));
  counts    = (uint64_t *) Calloc(MAX_ALPHABET, sizeof(uint64_t));
  nBytes    = 0;

  char *programName = argv[0];
  struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_BUFF('<', "input", "Input file (stdin)"),
        OPT_BUFF('>', "output", "Output read information (stdout)"),
        OPT_GROUP("Optional"),
        OPT_BOOLEAN('a', "ascii", &showASCII, "When active, the application shows the ASCII codes"),
        OPT_END(),
  };
  struct argparse argparse;

  char usage[250] = "\nExample: "; 
  strcat(usage, programName);
  strcat(usage, " < input > output\n"
    "\nOutput example :\n"
    "Number of symbols  : value\n"
    "Alphabet size      : value\n"
    "Alphabet           : value\n"
    "Symbol distribution:\n"
    "<Symbol/Code ASCII>  <Symbol count>  <Distribution percentage>\n");

  argparse_init(&argparse, options, NULL, programName, 0);
  argparse_describe(&argparse, "\nIt gives the basic properties of the file, namely size, cardinality, "
                                "distribution percentage of the symbols, among others.", usage);
  argc = argparse_parse(&argparse, argc, argv);

  if(argc != 0 || ftell(stdin))
    argparse_help_cb(&argparse, options);

  while((streamSize = fread(buf, 1, BUFFER_SIZE, stdin)))
    for(idxPos = 0 ; idxPos != streamSize ; ++idxPos)
    {
      sym = *(buf+idxPos);
      mask[sym] = 1;
      ++counts[sym];
      ++nBytes;
    }

  nSym = 0;
  for(n = MAX_ALPHABET ; --n ; )
    if(mask[n] == 1)
    {
      norm_alp[nSym] = n;
      alp[n] = nSym++;
    }
    else 
      alp[n] = MAX_ALPHABET-1;

  printf("Number of symbols  : %"PRIu64"\n", nBytes);
  printf("Alphabet size      : %u\n", nSym);
  printf("Alphabet           :");

  for(n = 0 ; n != nSym ; ++n)
    norm_alp[n] == 10 ? printf("\\n") : printf("%c", norm_alp[n]);
  printf("\n");
  printf("Symbol distribution:\n");

  for(n = 0 ; n < nSym ; ++n)
    if(showASCII == 0)
      norm_alp[n] == 10 ? printf("\\n : %"PRIu64"\t%.8g\n", counts[norm_alp[n]], (double) counts[norm_alp[n]]/nBytes*100) : 
      printf("%-2c : %"PRIu64"\t%.8g\n", norm_alp[n], counts[norm_alp[n]], (double) counts[norm_alp[n]]/nBytes*100);
    else
      printf("%-2d : %"PRIu64"\t%.8g\n", norm_alp[n], counts[norm_alp[n]], (double) counts[norm_alp[n]]/nBytes*100);

  Free(buf,      BUFFER_SIZE  * sizeof(uint8_t ));
  Free(alp,      MAX_ALPHABET * sizeof(uint8_t ));
  Free(norm_alp, MAX_ALPHABET * sizeof(uint8_t ));
  Free(mask,     MAX_ALPHABET * sizeof(uint8_t ));
  Free(counts,   MAX_ALPHABET * sizeof(uint64_t));
      
  return EXIT_SUCCESS;
}