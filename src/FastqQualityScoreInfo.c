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
 * This application analyses the quality-scores of a FASTQ file.
 */
int main(int argc, char *argv[])
{
  Read *Read = CreateRead(65536+GUARD, 65535+GUARD);
  int32_t seqSize = 0, x;
  uint64_t totalReads = 0, minSeq = 65535, maxSeq = 0;
  int minQS = 255, maxQS = 0, tmp_QS;
  uint64_t nScores = 0, *QS = (uint64_t *) Calloc(65536, sizeof(uint64_t)),
           *QN = (uint64_t *) Calloc(65536, sizeof(uint64_t));
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
  strcat(usage, " -m <max> < input.fastq > output\n"
    "\nOutput example :\n"
    "Total reads     : value\n"
    "Max read length : value\n"
    "Min read length : value\n"
    "Min QS value    : value\n"
    "Max QS value    : value\n"
    "QS range        : value\n");

  argparse_init(&argparse, options, NULL, programName, 0);
  argparse_describe(&argparse, "\nIt analyses the quality-scores of a FASTQ file.", usage);
  argc = argparse_parse(&argparse, argc, argv);

  if(argc != 0 || isatty(STDIN_FILENO))
    argparse_help_cb(&argparse, options);

  while(GetRead(stdin, Read))
  {
    seqSize = strlen((char *) Read->bases) - 1;

    if(seqSize < minSeq)
      minSeq = seqSize;

    if(seqSize > maxSeq)
      maxSeq = seqSize;
 

    for(x = 0 ; x < seqSize ; ++x)
    {
      tmp_QS = (int) Read->scores[x];

      if(tmp_QS < minQS)
        minQS = tmp_QS;

      if(tmp_QS > maxQS)
        maxQS = tmp_QS;

      if(x == 65535)
      {
        fprintf(stderr, "Error: read to long. Increase buffer!\n");
        exit(1);
      }
      
      QS[x] += tmp_QS;
      QN[x] += 1;
 
      ++nScores;
    }

    ++totalReads;
  }

  fprintf(stdout, "Total reads     : %"PRIu64"\n", totalReads);
  fprintf(stdout, "Max read length : %"PRIu64"\n", maxSeq);
  fprintf(stdout, "Min read length : %"PRIu64"\n", minSeq);
  fprintf(stdout, "Min QS value    : %d\n", minQS);
  fprintf(stdout, "Max QS value    : %d\n", maxQS);
  fprintf(stdout, "QS range        : %d\n", maxQS-minQS + 1);

  int tmp_min = maxQS;
  for(x = 0 ; x < maxs ; ++x)
  {
    QS[x] /= (double) QN[x];
    if(tmp_min > (int) QS[x])
      tmp_min = (int) QS[x];
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

  int line = (int) maxQS;
  while(line > tmp_min)
  {
    for(x = 0 ; x < maxs ; ++x)
    {
      if((int) QS[x] < line)
        fprintf(stdout, " * ");
      else
        fprintf(stdout, "   ");
    }

    fprintf(stdout, "\n");
    line -= 1;
  }

  Free(QS, 0);
  Free(QN, 0);
  FreeRead(Read);
  return EXIT_SUCCESS;
}