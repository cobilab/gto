#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "argparse.h"

/*
 * This application splits different rows with a new empty row.
 */

int main(int argc, char *argv[])
{
  double fix = 0, x, y, z;
  int new = 1;

  char *programName = argv[0];
  struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_BUFF('<', "input", "Input file with 3 column matrix format (stdin)"),
        OPT_BUFF('>', "output", "Output file with 3 column matrix format (stdout)"),
        OPT_END(),
  };
  struct argparse argparse;

  char usage[250] = "\nExample: "; 
  strcat(usage, programName);
  strcat(usage, " < input > output\n");

  argparse_init(&argparse, options, NULL, programName, 0);
  argparse_describe(&argparse, "\nIt splits different rows with a new empty row.", usage);
  argc = argparse_parse(&argparse, argc, argv);

  if(argc != 0)
    argparse_help_cb(&argparse, options);

  while(fscanf(stdin, "%lf %lf %lf\n", &x, &y, &z) == 3)
  {
    if(x != fix)
    {
      if(new == 0)
        fprintf(stdout, "\n");
      fix = x;
      new = 0;
    }
    fprintf(stdout, "%lf\t%lf\t%lf\n", x, y, z);
  }

  return EXIT_SUCCESS;
}