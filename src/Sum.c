#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"
#include "misc.h"
#include "buffer.h"
#include "argparse.h"
#include <unistd.h>

/*
 * This application adds decimal values in file, line by line, splitted by spaces or tabs.
 */
int main(int argc, char *argv[])
{
  char* line = NULL;
  size_t len = 0;
  ssize_t read;
  double value = 0, sum = 0, sumAll = 0;
  int sumEverything = -1;
  int sumRows = 0;

  char *programName = argv[0];
  struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_BUFF('<', "input.num", "Input numeric file (stdin)"),
        OPT_BUFF('>', "output.num", "Output numeric file (stdout)"),
        OPT_GROUP("Optional"),
        OPT_BOOLEAN('r', "sumrows", &sumRows, "When active, the application adds all the values line by line"),
        OPT_BOOLEAN('a', "sumall", &sumEverything, "When active, the application adds all values"),
        OPT_END(),
  };
  struct argparse argparse;

  char usage[250] = "\nExample: "; 
  strcat(usage, programName);
  strcat(usage, " -a < input.num > output.num\n");

  argparse_init(&argparse, options, NULL, programName, 0);
  argparse_describe(&argparse, "\nIt adds decimal values in file, line by line, splitted by spaces or tabs.", usage);
  argc = argparse_parse(&argparse, argc, argv);

  if(argc != 0 || isatty(STDIN_FILENO))
    argparse_help_cb(&argparse, options);

  if(sumRows == 0 && sumEverything == -1)
    sumEverything = 1;

  while ((read = getline(&line, &len, stdin)) != -1) 
  {
      char * valueCharFormat;
      valueCharFormat = strtok (line," -\t");
      while (valueCharFormat != NULL)
      {
        value = 0; 
        sscanf(valueCharFormat, "%lf", &value);
        sumAll += value;
        sum += value;
        valueCharFormat = strtok (NULL, " ,.-\t");
      }

      if(sumRows == 1)
      {
        fprintf(stdout, "%lf\n", sum);
        sum = 0; 
      }
  }

  if(sumEverything == 1)
    fprintf(stdout, "%lf\n", sumAll);
  
  return EXIT_SUCCESS;
}