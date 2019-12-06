#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include "defs.h"
#include "misc.h"
#include "mem.h"
#include "reads.h"
#include "argparse.h"

/*
 * This application cuts read sequences in a FASTQ file.
 * It requires that the initial and end positions for the cut.
 */
int main(int argc, char *argv[])
{
  Read *Read = CreateRead(65536+GUARD, 65535+GUARD);
  uint32_t seqSize = 0, initial = UINT_MAX, end = UINT_MAX, n;

  char *programName = argv[0];
  struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_INTEGER('i', "initial", &initial, "Starting position to the cut"),
        OPT_INTEGER('e', "end", &end, "Ending position to the cut"),
        OPT_BUFF('<', "input.fastq", "Input FASTQ file format (stdin)"),
        OPT_BUFF('>', "output.fastq", "Output FASTQ file format (stdout)"),
        OPT_END(),
  };
  struct argparse argparse;

  char usage[250] = "\nExample: "; 
  strcat(usage, programName);
  strcat(usage, " -i <initial> -e <end> < input.fastq > output.fastq\n");

  argparse_init(&argparse, options, NULL, programName, 0);
  argparse_describe(&argparse, "\nIt cuts read sequences in a FASTQ file.", usage);
  argc = argparse_parse(&argparse, argc, argv);

  if(argc != 0 || ftell(stdin))
    argparse_help_cb(&argparse, options);

  if(initial == UINT_MAX || end == UINT_MAX)
  {
    fprintf(stderr, "\nERROR: The minimum average quality-score most be a positive unsigned int!\n");
    argparse_help_cb(&argparse, options);
    exit(1);
  }
 
  while(GetRead(stdin, Read))
  {
    seqSize = strlen((char *) Read->bases) - 1;

    // PRINT READ
    fprintf(stdout, "@");
    for(n = 0 ; n < strlen((char *) Read->header1) ; ++n)
      fprintf(stdout, "%c", Read->header1[n]);
    for(n = 0 ; n < seqSize ; ++n)
      if(n >= initial && n <= end)
        fprintf(stdout, "%c", Read->bases[n]);

    fprintf(stdout, "\n+\n");
    for(n = 0 ; n < seqSize ; ++n)
      if(n >= initial && n <= end)
        fprintf(stdout, "%c", Read->scores[n]);
        
    fprintf(stdout, "\n");
  }

  FreeRead(Read);
  return EXIT_SUCCESS;
}