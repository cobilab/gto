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
 * This application filters the FASTQ reads with the length higher than the value defined
 */
int main(int argc, char *argv[])
{
  Read *Read = CreateRead(65536+GUARD, 65535+GUARD);
  uint32_t sequenceSize = 0, index;
  uint64_t okReads = 0, totalReads = 0;
  int min_read_size = 0;

  char *programName = argv[0];
  struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_INTEGER('s', "size", &min_read_size, "The maximum read length"),
        OPT_BUFF('<', "input.fastq", "Input FASTQ file format (stdin)"),
        OPT_BUFF('>', "output", "Output read information (stdout)"),
        OPT_END(),
  };
  struct argparse argparse;

  char usage[250] = "\nExample: "; 
  strcat(usage, programName);
  strcat(usage, " < input.fastq > output\n"
    "\nOutput example :\n"
    "<FASTQ non-filtered reads>\n"
    "Total reads    : value\n"
    "Filtered reads : value\n");

  argparse_init(&argparse, options, NULL, programName, 0);
  argparse_describe(&argparse, "\nIt filters the FASTQ reads with the length higher than the value defined. "
    "If present, it will erase the second header (after +).", usage);
  argc = argparse_parse(&argparse, argc, argv);

  if(argc != 0)
    argparse_help_cb(&argparse, options);

  if(min_read_size <= 0 || min_read_size > UINT_MAX)
  {
    fprintf(stderr, "\nERROR: The size value most be a positive unsigned int!\n");
    argparse_help_cb(&argparse, options);
    exit(1);
  }
 
  while(GetRead(stdin, Read))
  {
    sequenceSize = strlen((char *) Read->bases) - 1;
    ++totalReads;

    // Evaluate to discard
    if(sequenceSize > min_read_size) continue;

    // Print the read
    fprintf(stdout, "@");
    for(index = 0 ; index < strlen((char *) Read->header1) ; ++index)
      fprintf(stdout, "%c", Read->header1[index]);
    for(index = 0 ; index < sequenceSize ; ++index)
      fprintf(stdout, "%c", Read->bases[index]);
    fprintf(stdout, "\n+\n");
    for(index = 0 ; index < sequenceSize ; ++index)
      fprintf(stdout, "%c", Read->scores[index]);
    fprintf(stdout, "\n");

    ++okReads;
  }

  fprintf(stderr, "Total reads    : %"PRIu64"\n", totalReads);
  fprintf(stderr, "Filtered reads : %"PRIu64"\n", totalReads-okReads);

  FreeRead(Read);
  return EXIT_SUCCESS;
}