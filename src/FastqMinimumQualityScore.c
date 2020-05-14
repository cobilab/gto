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
#include <unistd.h>

/*
 * This application discards reads with average quality-score below value.
 */
int main(int argc, char *argv[])
{
  Read *Read = CreateRead(65536+GUARD, 65535+GUARD);
  uint32_t seqSize = 0, totalQS = 0, globalIndex, index;
  uint64_t okReads = 0, totalReads = 0;
  int min_avg_qs = 0;

  char *programName = argv[0];
  struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_INTEGER('m', "min", &min_avg_qs, "The minimum average quality-score (Value 25 or 30 is commonly used)"),
        OPT_BUFF('<', "input.fastq", "Input FASTQ file format (stdin)"),
        OPT_BUFF('>', "output.fastq", "Output FASTQ file format (stdout)"),
        OPT_END(),
  };
  struct argparse argparse;

  char usage[250] = "\nExample: "; 
  strcat(usage, programName);
  strcat(usage, " -m <min> < input.fastq > output.fastq\n"
    "\nConsole output example:\n"
    "<FASTQ non-filtered reads>\n"
    "Total reads    : value\n"
    "Filtered reads : value\n");

  argparse_init(&argparse, options, NULL, programName, 0);
  argparse_describe(&argparse, "\nIt discards reads with average quality-score below value.", usage);
  argc = argparse_parse(&argparse, argc, argv);

  if(argc != 0 || isatty(STDIN_FILENO))
    argparse_help_cb(&argparse, options);

  if(min_avg_qs <= 0 || min_avg_qs > UINT_MAX)
  {
    fprintf(stderr, "\nERROR: The minimum average quality-score most be a positive unsigned int!\n");
    argparse_help_cb(&argparse, options);
    exit(1);
  }
 
  while(GetRead(stdin, Read))
  {
    seqSize = strlen((char *) Read->bases) - 1;

    totalQS = 0;
    for(globalIndex = 0 ; globalIndex < seqSize ; ++globalIndex)
    {
      totalQS += ((int) Read->scores[globalIndex]) - 33; // PHRED +33
    }

    ++totalReads;

    // Evaluate to discard
    if((totalQS / seqSize) < min_avg_qs) continue;

    // Print read
    fprintf(stdout, "@");
    for(index = 0 ; index < strlen((char *) Read->header1) ; ++index)
      fprintf(stdout, "%c", Read->header1[index]);
    for(index = 0 ; index < seqSize ; ++index)
      fprintf(stdout, "%c", Read->bases[index]);
    fprintf(stdout, "\n+\n");
    for(index = 0 ; index < seqSize ; ++index)
      fprintf(stdout, "%c", Read->scores[index]);
    fprintf(stdout, "\n");

    ++okReads;
  }

  fprintf(stderr, "Total reads    : %"PRIu64"\n", totalReads);
  fprintf(stderr, "Filtered reads : %"PRIu64"\n", totalReads-okReads);

  FreeRead(Read);
  return EXIT_SUCCESS;
}