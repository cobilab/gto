#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "defs.h"
#include "misc.h"
#include "mem.h"
#include "reads.h"
#include "argparse.h"

/*
 * This application filters the reverse reads, considering the average 
 * window size score defined by the bases.
 */
int main(int argc, char *argv[])
{
  Read *Read = CreateRead(65536+GUARD, 65535+GUARD);
  int32_t seqSize = 0, x, n;
  uint64_t cutted = 0, totalReads = 0;
  int windowsize = 5, min_QS_window = 25, min_QS = 33;

  char *programName = argv[0];
  struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_INTEGER('k', "windowsize", &windowsize, "The window size of bases (default 5)"),
        OPT_INTEGER('w', "minavg", &min_QS_window, "The minimum average of quality score (default 25)"),
        OPT_INTEGER('m', "minqs", &min_QS, "The minimum value of the quality score (default 33)"),
        OPT_BUFF('<', "input.fastq", "Input FASTQ file format (stdin)"),
        OPT_BUFF('>', "output.fastq", "Output FASTQ file format (stdout)"),
        OPT_END(),
  };
  struct argparse argparse;

  char usage[250] = "\nExample: "; 
  strcat(usage, programName);
  strcat(usage, " -k <windowsize> -w <minavg> -m <minqs> < input.fastq > output.fastq\n"
    "\nConsole output example:\n"
    "Minimum QS       : value\n"
    "<FASTQ output>\n"
    "Total reads      : value\n"
    "Trimmed reads    : value\n");

  argparse_init(&argparse, options, NULL, programName, 0);
  argparse_describe(&argparse, "\nIt filters the reverse reads, considering the average window size score defined by the bases.", usage);
  argc = argparse_parse(&argparse, argc, argv);

  if(argc != 0)
    argparse_help_cb(&argparse, options);

  fprintf(stderr, "Minimum QS: %d\n", min_QS);
 
  uint32_t position = 0;
  while(GetRead(stdin, Read))
  {
    seqSize = strlen((char *) Read->bases) - 1;

    for(x = seqSize ; x >= 0 ; x--)
    {
      if(x >= windowsize)
      {
        int tmp_QS = 0;
        for(n = 0 ; n < windowsize ; ++n)
          tmp_QS += ((int) Read->scores[x - 1 - n]) - min_QS;

        if(((double) tmp_QS / windowsize) < (double) min_QS_window)
        {
          ++cutted;
          position = x;
          break;
        }
      }
    }

    ++totalReads;

    if(x > seqSize - windowsize) continue;

    // PRINT READ
    fprintf(stdout, "@");
    for(n = 0 ; n < strlen((char *) Read->header1) ; ++n)
      fprintf(stdout, "%c", Read->header1[n]);
    
    for(n = position ; n < seqSize ; ++n)
      fprintf(stdout, "%c", Read->bases[n]);
    
    fprintf(stdout, "\n+\n");
    
    for(n = position ; n < seqSize ; ++n)
      fprintf(stdout, "%c", Read->scores[n]);
    fprintf(stdout, "\n");
  }

  fprintf(stderr, "Total reads    : %"PRIu64"\n", totalReads);
  fprintf(stderr, "Trimmed reads  : %"PRIu64"\n", cutted);

  FreeRead(Read);
  return EXIT_SUCCESS;
}