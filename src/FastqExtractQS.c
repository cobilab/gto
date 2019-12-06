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
 * This application extracts all the quality-scores from FASTQ reads.
 */
int main(int argc, char *argv[])
{
  Read *Read = CreateRead(65536+GUARD, 65535+GUARD);
  uint32_t sequenceSize = 0, index;
  uint64_t totalReads = 0, totalQS = 0;

  char *programName = argv[0];
  struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_BUFF('<', "input.fastq", "Input FASTQ file format (stdin)"),
        OPT_BUFF('>', "output.fastq", "Output FASTQ file format (stdout)"),
        OPT_END(),
  };
  struct argparse argparse;

  char usage[250] = "\nExample: "; 
  strcat(usage, programName);
  strcat(usage, " < input.fastq > output.fastq\n"
    "\nConsole output example:\n"
    "<FASTQ quality scores>\n"
    "Total reads          : value\n"
    "Total Quality-Scores : value\n");

  argparse_init(&argparse, options, NULL, programName, 0);
  argparse_describe(&argparse, "\nIt extracts all the quality-scores from FASTQ reads.", usage);
  argc = argparse_parse(&argparse, argc, argv);

  if(argc != 0 || ftell(stdin))
    argparse_help_cb(&argparse, options);
  
  while(GetRead(stdin, Read))
  {
    sequenceSize = strlen((char *) Read->scores) - 1;
    ++totalReads;
    for(index = 0 ; index < sequenceSize ; ++index)
    {
      fprintf(stdout, "%c", Read->scores[index]);
      ++totalQS;
    }
    fprintf(stdout, "\n");
  }

  fprintf(stderr, "Total reads          : %"PRIu64"\n", totalReads);
  fprintf(stderr, "Total Quality-Scores : %"PRIu64"\n", totalQS);

  FreeRead(Read);
  return EXIT_SUCCESS;
}