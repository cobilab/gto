#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "defs.h"
#include "misc.h"
#include "mem.h"
#include "reads.h"
#include "argparse.h"

/*
 * This application splits Paired End files according to the direction of the strand ('/1' or '/2'). 
 * It writes by default singleton reads as forward stands.
 */
int main(int argc, char *argv[])
{
  Read      *Read = CreateRead(65536+GUARD, 65535+GUARD);
  uint64_t  total = 0, forward = 65535, reverse = 0, singleton = 0;
  const char *output_forward = NULL;
  const char *output_reverse = NULL;

  char *programName = argv[0];
  struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_STRING('f', "forward", &output_forward, "Output forward file"),
        OPT_STRING('r', "reverse", &output_reverse, "Output reverse file"),
        OPT_BUFF('<', "input.fastq", "Input FASTQ file format (stdin)"),
        OPT_BUFF('>', "output", "Output read information (stdout)"),
        OPT_END(),
  };
  struct argparse argparse;

  char usage[250] = "\nExample: "; 
  strcat(usage, programName);
  strcat(usage, " -t <output_forward.fastq> -r <output_reverse.fastq> < input.fastq > output\n"
    "\nOutput example :\n"
    "Total reads      : value\n"  
    "Singleton reads  : value\n"
    "Forward reads    : value\n"
    "Reverse reads    : value\n");

  argparse_init(&argparse, options, NULL, programName, 0);
  argparse_describe(&argparse, 
    "\nIt writes by default singleton reads as forward stands.", usage);
  argc = argparse_parse(&argparse, argc, argv);

  if(argc != 0)
    argparse_help_cb(&argparse, options);

  FILE *F = Fopen(output_forward, "w");
  FILE *R = Fopen(output_reverse, "w");

  while(GetRead(stdin, Read))
  {
    switch(Read->header1[strlen((char *) Read->header1)-2])
    {
      case '1':
        PrintRead(Read, F);
        ++forward;
      break;
      case '2':
        PrintRead(Read, R);
        ++reverse;   
      break;
      default:
        PrintRead(Read, F);
        ++singleton;
    }
    ++total;
  }

  fprintf(stderr, "Total reads     : %"PRIu64"\n", total);
  fprintf(stderr, "Singleton reads : %"PRIu64"\n", singleton);
  fprintf(stderr, "Forward reads   : %"PRIu64"\n", forward);
  fprintf(stderr, "Reverse reads   : %"PRIu64"\n", reverse);

  fclose(F);
  fclose(R);
  FreeRead(Read);
  return EXIT_SUCCESS;
}
