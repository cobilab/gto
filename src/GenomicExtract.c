#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "defs.h"
#include "misc.h"
#include "argparse.h"

#define END  100

/*
 * This application extracts sequences from a sequence file.
 */
int main(int argc, char *argv[])
{
  //uint32_t n;
  uint64_t count = 0, init = 0, end = END;
  char value;

  char *programName = argv[0];
  struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_INTEGER('i', "init", &init, "The first position to start the extraction (default 0)"),
        OPT_INTEGER('e', "end", &end, "The last extract position (default 100)"),
        OPT_BUFF('<', "input.seq", "Input sequence file (stdin)"),
        OPT_BUFF('>', "output.seq", "Output sequence file (stdout)"),
        OPT_END(),
  };
  struct argparse argparse;

  char usage[250] = "\nExample: "; 
  strcat(usage, programName);
  strcat(usage, " -i <init> -e <end> < input.seq > output.seq\n");

  argparse_init(&argparse, options, NULL, programName, 0);
  argparse_describe(&argparse, "\nIt extracts sequences from a sequence file.", usage);
  argc = argparse_parse(&argparse, argc, argv);

  if(argc != 0)
    argparse_help_cb(&argparse, options);

  do
  {
    value = fgetc(stdin);
    
    if(init <= count && end > count)
      fprintf(stdout, "%c", value);		
    
    if(count++ >= end) break;
  }
  while(value != EOF);

  return EXIT_SUCCESS;
}