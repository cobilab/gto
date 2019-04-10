#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "defs.h"
#include "misc.h"
#include "argparse.h"

/*
 * This application sets an upper bound in a file with a value per line.
 */
int main(int argc, char *argv[])
{
  double value;
  uint64_t upperbound = UINT_MAX;
  char *programName = argv[0];
  struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_INTEGER('u', "upperbound", &upperbound, "The upper bound value"),
        OPT_BUFF('<', "input.num", "Input numeric file (stdin)"),
        OPT_BUFF('>', "output.num", "Output numeric file (stdout)"),
        OPT_END(),
  };
  struct argparse argparse;

  char usage[250] = "\nExample: "; 
  strcat(usage, programName);
  strcat(usage, " -u <upperbound> < input.num > output.num\n");

  argparse_init(&argparse, options, NULL, programName, 0);
  argparse_describe(&argparse, "\nIt sets an upper bound in a file with a value per line.", usage);
  argc = argparse_parse(&argparse, argc, argv);

  if(argc != 0 || upperbound == UINT_MAX)
    argparse_help_cb(&argparse, options);
  
  fprintf(stderr, "Using upper bound: %ld\n", upperbound);
  while(fscanf(stdin, "%lf\n", &value) == 1)
    fprintf(stdout, "%lf\n", value > upperbound ? upperbound : value);

  return EXIT_SUCCESS;
}
