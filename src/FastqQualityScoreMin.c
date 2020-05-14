#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "defs.h"
#include "misc.h"
#include "mem.h"
#include "reads.h"
#include "argparse.h"
#include <unistd.h>

/*
 * This application analyses the minimal quality-scores of a FASTQ file.
 */
int main(int argc, char *argv[])
{
  Read *Read = CreateRead(65536+GUARD, 65535+GUARD);
  int32_t  seqSize = 0, x;
  uint64_t *QS = (uint64_t *) Calloc(65536, sizeof(uint64_t));
  int maxs = 40;

  char *programName = argv[0];
  struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_BUFF('<', "input.fastq", "Input FASTQ file format (stdin)"),
        OPT_BUFF('>', "output", "Output read information (stdout)"),
        OPT_GROUP("Optional"),
        OPT_INTEGER('m', "max", &maxs, "The maximum window length (default 40)"),
        OPT_END(),
  };
  struct argparse argparse;

  char usage[250] = "\nExample: "; 
  strcat(usage, programName);
  strcat(usage, " -m <max> < input.fastq > output\n");

  argparse_init(&argparse, options, NULL, programName, 0);
  argparse_describe(&argparse, "\nIt analyses the minimal quality-scores of a FASTQ file.", usage);
  argc = argparse_parse(&argparse, argc, argv);

  if(argc != 0 || isatty(STDIN_FILENO))
    argparse_help_cb(&argparse, options);

  for(x = 0 ; x < 65535 ; ++x)
    QS[x] = 777;

  while(GetRead(stdin, Read))
  {
    seqSize = strlen((char *) Read->bases) - 1;
    for(x = 0 ; x < seqSize ; ++x)
    {
      int tmp_QS = (int) Read->scores[x];
      if(QS[x] > tmp_QS)
      QS[x] = tmp_QS;
      if(x == 65535)
      {
        fprintf(stderr, "Error: read to long. Increase buffer!\n");
        exit(1);
      }
    }
  }

  for(x = 0 ; x < maxs ; ++x)
    fprintf(stdout, "%2d ", x+1);
  fprintf(stdout, "\n");

  for(x = 0 ; x < maxs ; ++x)
    fprintf(stdout, "--+");
  fprintf(stdout, "\n");

  for(x = 0 ; x < maxs ; ++x)
    fprintf(stdout, "%2d ", (int) QS[x]);
  fprintf(stdout, "\n");

  Free(QS, 0);
  FreeRead(Read);
  return EXIT_SUCCESS;
}