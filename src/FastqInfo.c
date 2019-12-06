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
 * This application analyses the basic information of FASTQ file format.
 */
int main(int argc, char *argv[])
{
  Read *Read = CreateRead(65536+GUARD, 65535+GUARD);
  int32_t sequenceSize = 0, index;
  uint64_t totalReads = 0, minSeq = 65535, maxSeq = 0;
  int minQS = 255, maxQS = 0, tmp_QS;

  char *programName = argv[0];
  struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_BUFF('<', "input.fastq", "Input FASTQ file format (stdin)"),
        OPT_BUFF('>', "output", "Output read information (stdout)"),
        OPT_END(),
  };
  struct argparse argparse;

  char usage[250] = "\nExample: "; 
  strcat(usage, programName);
  strcat(usage, " < input.fastq > output\n"
    "\nOutput example :\n"
    "Total reads     : value\n"
    "Max read length : value\n"
    "Min read length : value\n"
    "Min QS value    : value\n"
    "Max QS value    : value\n"
    "QS range        : value\n");

  argparse_init(&argparse, options, NULL, programName, 0);
  argparse_describe(&argparse, "\nIt analyses the basic information of FASTQ file format.", usage);
  argc = argparse_parse(&argparse, argc, argv);

  if(argc != 0 || ftell(stdin))
    argparse_help_cb(&argparse, options);

  while(GetRead(stdin, Read))
  {
    sequenceSize = strlen((char *) Read->bases) - 1;

    if(sequenceSize < minSeq)
      minSeq = sequenceSize;

    if(sequenceSize > maxSeq)
      maxSeq = sequenceSize;

    for(index = 0 ; index < sequenceSize ; ++index)
    {
      tmp_QS = (int) Read->scores[index];

      if(tmp_QS < minQS)
        minQS = tmp_QS;

      if(tmp_QS > maxQS)
        maxQS = tmp_QS;
    }

    ++totalReads;
  }

  fprintf(stdout, "Total reads     : %"PRIu64"\n", totalReads);
  fprintf(stdout, "Max read length : %"PRIu64"\n", maxSeq);
  fprintf(stdout, "Min read length : %"PRIu64"\n", minSeq);
  fprintf(stdout, "Min QS value    : %d\n", minQS);
  fprintf(stdout, "Max QS value    : %d\n", maxQS);
  fprintf(stdout, "QS range        : %d\n", maxQS-minQS + 1);

  FreeRead(Read);
  return EXIT_SUCCESS;
}