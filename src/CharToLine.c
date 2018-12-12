#include <stdio.h>
#include <string.h>
#include "argparse.h"

/*
 * This application splits a sequence into lines, creating an output sequence which has a char for each line.
 */
int main(int argc, char *argv[])
{
	char character;
  char *programName = argv[0];
  struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_BUFF('<', "input.seq", "Input sequence file (stdin)"),
        OPT_BUFF('>', "output.seq", "Output sequence file (stdout)"),
        OPT_END(),
  };
  struct argparse argparse;

  char usage[250] = "\nExample: "; 
  strcat(usage, programName);
  strcat(usage, " < input.seq > output.seq\n");

  argparse_init(&argparse, options, NULL, programName, 0);
  argparse_describe(&argparse, "\nIt splits a sequence into lines, creating an output sequence which has a char for each line.", usage);
  argc = argparse_parse(&argparse, argc, argv);

  if(argc != 0)
    argparse_help_cb(&argparse, options);

  	while((character = fgetc(stdin)) != EOF)
    	fprintf(stdout, "%c\n", character);
  	return 0;
}
