#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"
#include "misc.h"
#include "argparse.h"

/*
 * This application computes the max value in each row between two files
 */
int MaxFile(const char *fn1, const char *fn2)
{	
  FILE *F1 = Fopen(fn1, "r"), *F2 = Fopen(fn2, "r");
  double max1, max2; 

  while(fscanf(F1, "%lf", &max1) == 1 && fscanf(F2, "%lf", &max2) == 1)
    fprintf(stdout, "%lf\n", max1 > max2 ? max1 : max2);

  if(F1) fclose(F1);
  if(F2) fclose(F2);
  return 0;
}

int main(int argc, char *argv[])
{
  const char *fn1 = NULL;
  const char *fn2 = NULL;


  char *programName = argv[0];
  struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_STRING('f', "first_file", &fn1, "File to compute the max"),
        OPT_STRING('s', "second_file", &fn2, "The second file to do the max computation"), 
        OPT_BUFF('>', "output.num", "Output numeric file (stdout)"),
        OPT_END(),
  };
  struct argparse argparse;

  char usage[250] = "\nExample: "; 
  strcat(usage, programName);
  strcat(usage, " -f input1.num -s input2.num > output.num\n");

  argparse_init(&argparse, options, NULL, programName, 0);
  argparse_describe(&argparse, "\nIt computes the max value in each row between two files.", usage);
  argc = argparse_parse(&argparse, argc, argv);

  if(argc != 0)
    argparse_help_cb(&argparse, options);
  
  if(MaxFile(fn1, fn2) == -1)
  {
    perror("Error on computing maximum!");
    exit(1);
  }
  return EXIT_SUCCESS;
}