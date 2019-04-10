#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "defs.h"
#include "misc.h"
#include "argparse.h"

/*
 * This application sets an lower bound in a file with a value per line.
 */
int main(int argc, char *argv[])
{
  double value;
  uint64_t lowerbound = UINT_MAX;
  char *programName = argv[0];
  struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_INTEGER('l', "lowerbound", &lowerbound, "The lower bound value."),
        OPT_BUFF('<', "input.num", "Input numeric file (stdin)"),
        OPT_BUFF('>', "output.num", "Output numeric file (stdout)"),
        OPT_END(),
  };
  struct argparse argparse;

  char usage[250] = "\nExample: "; 
  strcat(usage, programName);
  strcat(usage, " -l <lowerbound> < input.num > output.num\n");

  argparse_init(&argparse, options, NULL, programName, 0);
  argparse_describe(&argparse, "\nIt sets an lower bound in a file with a value per line.", usage);
  argc = argparse_parse(&argparse, argc, argv);

  if(argc != 0 || lowerbound == UINT_MAX)
    argparse_help_cb(&argparse, options);
  
  fprintf(stderr, "Using lower bound: %ld\n", lowerbound);
  while(fscanf(stdin, "%lf\n", &value) == 1)
    fprintf(stdout, "%lf\n", value < lowerbound ? lowerbound : value);

  return EXIT_SUCCESS;
}
