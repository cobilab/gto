#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "defs.h"
#include "misc.h"
#include "mem.h"
#include "reads.h"
#include "argparse.h"

void PrintStream(uint8_t *b, uint32_t n, uint8_t terminator)
{
  int k;
  for(k = 0 ; k < n ; ++k)
    if(b[k] == '\n' || k == (n-1)) 
      putchar(127);
    else 
      putchar(b[k]);
}

void PrintID(uint32_t i)
{
  fprintf(stdout, "\t%u\n", i);
}

/* 
 * This application packages each FASTQ read in a single line. 
 * It can show the read score first or the dna sequence.
 */
int main(int argc, char *argv[])
{
  Read *Read = CreateRead(65536+GUARD, 65535+GUARD);
  uint32_t index = 0, scores = 0;

  char *programName = argv[0];
  struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_BUFF('<', "input.fastq", "Input FASTQ file format (stdin)"),
        OPT_BUFF('>', "output.fastq", "Output FASTQ file format (stdout)"),
        OPT_GROUP("Optional"),
        OPT_BOOLEAN('s', "scores", &scores, "When active, the application show the scores first"),
        OPT_END(),
  };
  struct argparse argparse;

  char usage[250] = "\nExample: "; 
  strcat(usage, programName);
  strcat(usage, " -s < input.fastq > output.fastq\n");

  argparse_init(&argparse, options, NULL, programName, 0);
  argparse_describe(&argparse, "\nIt packages each FASTQ read in a single line.", usage);
  argc = argparse_parse(&argparse, argc, argv);

  if(argc != 0)
    argparse_help_cb(&argparse, options);
  
  while(GetRead(stdin, Read))
  {
    if(scores == 0)
    {
      PrintStream(Read->bases,  strlen((char *) Read->bases ),  0);
      PrintStream(Read->scores, strlen((char *) Read->scores),  0);
    }
    else
    {
      PrintStream(Read->scores, strlen((char *) Read->scores),  0);
      PrintStream(Read->bases,  strlen((char *) Read->bases ),  0);
    }

    PrintStream(Read->header1,  strlen((char *) Read->header1), 0);
    PrintStream(Read->header2,  strlen((char *) Read->header2), 0);
    PrintID(index++);
  }

  FreeRead(Read);
  return EXIT_SUCCESS;
}