#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "argparse.h"

/*
 * This application converts a sequence of real numbers into a binary sequence
 * given a threshold. The numbers below to the threshold will be 0.
 */
int main(int argc, char *argv[])
{
  double  value, threshold = UINT_MAX;

  char *programName = argv[0];
  struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_DOUBLE('t', "threshold", &threshold, "The threshold in real format"),
        OPT_BUFF('<', "input.num", "Input numeric file (stdin)"),
        OPT_BUFF('>', "output.bin", "Output binary file (stdout)"),
        OPT_END(),
  };
  struct argparse argparse;

  char usage[250] = "\nExample: "; 
  strcat(usage, programName);
  strcat(usage, " -t <threshold> < input.num > output.bin\n");

  argparse_init(&argparse, options, NULL, programName, 0);
  argparse_describe(&argparse, "\nIt converts a sequence of real numbers into a binary sequence given a threshold.", usage);
  argc = argparse_parse(&argparse, argc, argv);

  if(argc != 0 || ftell(stdin))
    argparse_help_cb(&argparse, options);

  if(threshold == UINT_MAX)
  {
    fprintf(stderr, "\nERROR: The paramenter ''threshold'' is required!\n");
    argparse_help_cb(&argparse, options);
    exit(1);
  }

  while(fscanf(stdin, "%lf", &value) == 1)
    if(value > threshold)
      fprintf(stdout, "1\n");
    else
      fprintf(stdout, "0\n");  
  
  return 0;
}