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
 * This application discards the FASTQ reads with the minimum number of \"N\" symbols. 
 * If present, it will erase the second header (after +).
 */
int main(int argc, char *argv[])
{
  Read *Read = CreateRead(65536+GUARD, 65535+GUARD);
  uint32_t sequenceSize = 0, N_counter = 0, globalIndex, index;
  uint64_t okReads = 0, totalReads = 0;
  int max_n_read = 0;

  char *programName = argv[0];
  struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_INTEGER('m', "max", &max_n_read, "The maximum of of \"N\" symbols in the read"),
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
  argparse_describe(&argparse, "\nIt discards the FASTQ reads with the minimum number of \"N\" symbols."
    "If present, it will erase the second header (after +).", usage);
  argc = argparse_parse(&argparse, argc, argv);

  if(argc != 0)
    argparse_help_cb(&argparse, options);

  if(max_n_read <= 0 || max_n_read > UINT_MAX)
  {
    fprintf(stderr, "\nERROR: The number of \"N\" symbols most be a positive unsigned int!\n");
    argparse_help_cb(&argparse, options);
    exit(1);
  }
 
  // LOAD PARAMETERS
  while(GetRead(stdin, Read))
  {
    sequenceSize = strlen((char *) Read->bases) - 1;
    N_counter = 0;
    for(globalIndex = 0 ; globalIndex < sequenceSize ; ++globalIndex)
      if(Read->bases[globalIndex] == 'N')
        ++N_counter;

    ++totalReads;

    // Evaluate to discard
    if(N_counter > max_n_read) continue;

    // Print read
    fprintf(stdout, "@");
    for(index = 0 ; index < strlen((char *) Read->header1) ; ++index)
      fprintf(stdout, "%c", Read->header1[index]);
    for(index = 0 ; index < globalIndex ; ++index)
      fprintf(stdout, "%c", Read->bases[index]);
    fprintf(stdout, "\n+\n");
    for(index = 0 ; index < globalIndex ; ++index)
      fprintf(stdout, "%c", Read->scores[index]);
    fprintf(stdout, "\n");

    ++okReads;
  }

  fprintf(stderr, "Total reads    : %"PRIu64"\n", totalReads);
  fprintf(stderr, "Filtered reads : %"PRIu64"\n", totalReads-okReads);

  FreeRead(Read);
  return EXIT_SUCCESS;
}


