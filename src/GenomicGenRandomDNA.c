#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "defs.h"
#include "argparse.h"

/*
 * This application generates a synthetic DNA
 */
int main(int argc, char *argv[])
{
  int index, indexAux, seqSize=100, seed = 0;
  char *bases = "ACGT";
  double freqs[4] = {0.25, 0.25, 0.25, 0.25}, cum[4], value, totalFreq;
  const char *frequency = NULL;


  char *programName = argv[0];
  struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_BUFF('>', "output.seq", "Output synthetic DNA sequence (stdout)"),
        OPT_GROUP("Optional"),
        OPT_INTEGER('s', "seed", &seed, "Starting point to the random generator (Default 0)"),
        OPT_INTEGER('n', "nSymbols", &seqSize, "Number of symbols generated (Default 100)"),
        OPT_STRING('f', "frequency", &frequency, "The frequency of each base. It should be represented in the following format: <fa,fc,fg,ft>."),
        OPT_END(),
  };
  struct argparse argparse;

  char usage[250] = "\nExample: "; 
  strcat(usage, programName);
  strcat(usage, " -s <seed> -n <nsybomls> -f <fa,fc,fg,ft> > output.seq\n");

  argparse_init(&argparse, options, NULL, programName, 0);
  argparse_describe(&argparse, "\nIt generates a synthetic DNA.", usage);
  argc = argparse_parse(&argparse, argc, argv);

  if(argc != 0)
    argparse_help_cb(&argparse, options);

  if(seed < 0 || seed > UINT_MAX)
  {
    fprintf(stderr, "\nERROR: The paramenter 'seed' most be a positive unsigned int!\n");
    argparse_help_cb(&argparse, options);
    exit(1);
  }

  if(seqSize <= 0 || seqSize > UINT_MAX)
  {
    fprintf(stderr, "\nERROR: The paramenter 'nSymbols' most be a positive unsigned int!\n");
    argparse_help_cb(&argparse, options);
    exit(1);
  }

  if(frequency != NULL)
  {
    if(sscanf(frequency, "%lf,%lf,%lf,%lf", &freqs[0], &freqs[1],
        &freqs[2], &freqs[3]) != 4)
        freqs[0] = freqs[1] = freqs[2] = freqs[3] = 0.25;

      totalFreq = freqs[0] + freqs[1] + freqs[2] + freqs[3];
      freqs[0] /= totalFreq;
      freqs[1] /= totalFreq;
      freqs[2] /= totalFreq;
      freqs[3] /= totalFreq;
  }

  cum[0] = freqs[0];
  cum[1] = cum[0] + freqs[1];
  cum[2] = cum[1] + freqs[2];
  cum[3] = 1;

  srand(seed);
  for(index = 0 ; index < seqSize ; index++)
  {
    value = rand() / (RAND_MAX + 1.0);
    for(indexAux = 0 ; indexAux < 4 ; indexAux++)
      if(value <= cum[indexAux])
        break;
    putchar(bases[indexAux]);
  }

  return 0;
}