#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "argparse.h"
#include <unistd.h>

typedef unsigned long long ULL;

/*
 * This application segments a filtered sequence.
 */
int main(int argc, char *argv[])
{
  double  val, threshold;
  ULL     pos, initPosition, lastPosition;
  int     region;
  initPosition = 0;
  lastPosition = 0;
  threshold = UINT_MAX;

  char *programName = argv[0];
  struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_DOUBLE('t', "threshold", &threshold, "The segment threshold"),
        OPT_BUFF('<', "input.num", "Input numeric file (stdin)"),
        OPT_BUFF('>', "output", "Output the segment file (stdout)"),
        OPT_END(),
  };
  struct argparse argparse;

  char usage[250] = "\nExample: "; 
  strcat(usage, programName);
  strcat(usage, " -t <threshold> < input.num > output\n");

  argparse_init(&argparse, options, NULL, programName, 0);
  argparse_describe(&argparse, "\nIt segments a filtered sequence.", usage);
  argc = argparse_parse(&argparse, argc, argv);

  if(argc != 0 || isatty(STDIN_FILENO))
    argparse_help_cb(&argparse, options);

  if(threshold == UINT_MAX)
  {
    fprintf(stderr, "\nERROR: The paramenter ''threshold'' is required!\n");
    argparse_help_cb(&argparse, options);
    exit(1);
  }

  if(fscanf(stdin, "%llu\t%lf", &pos, &val) == 2)
    region = val < threshold ? 0 : 1;
  else
  {
    fprintf(stderr, "Error: unknown format\n");
    exit(1);
  }

  while(fscanf(stdin, "%llu\t%lf", &pos, &val) == 2)
  {
    if(val > threshold && region == 0)
    {
      if(lastPosition != initPosition)
      {
        fprintf(stdout, "%llu:%llu\n", initPosition, lastPosition);
        region = 1;
      }
    }

    if(region == 1 && val < threshold)
    {
      region = 0;
      initPosition = pos;
    }
    lastPosition = pos;
  }

  if(region == 0 && (lastPosition > (initPosition + 10)))
    fprintf(stdout, "%llu:%llu\n", initPosition, lastPosition);

  return 0;
}