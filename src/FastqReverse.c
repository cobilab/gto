#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include "defs.h"
#include "misc.h"
#include "parser.h"
#include "mem.h"
#include "reads.h"
#include "argparse.h"

/*
 * This application reverses the ACGT bases order for each read in a FASTQ file format.
 */
int main(int argc, char *argv[])
{
  Read *Read = CreateRead(65536+GUARD, 65535+GUARD);
  uint32_t seqSize = 0, index;
  PARSER *Parser = CreateParser();

  char *programName = argv[0];
  struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_BUFF('<', "input.fastq", "Input FASTQ file (stdin)"),
        OPT_BUFF('>', "output.fastq", "Output FASTQ file (stdout)"),
        OPT_END(),
  };
  struct argparse argparse;

  char usage[250] = "\nExample: "; 
  strcat(usage, programName);
  strcat(usage, " < input.fastq > output.fastq\n");

  argparse_init(&argparse, options, NULL, programName, 0);
  argparse_describe(&argparse, "\nIt reverses the ACGT bases order for each read in a FASTQ file.", usage);
  argc = argparse_parse(&argparse, argc, argv);

  if(argc != 0)
    argparse_help_cb(&argparse, options);

  FileType(Parser, stdin);
  if(Parser->type != 2)
  {
    fprintf(stderr, "ERROR: This is not a FASTQ file!\n");
    exit(1);
  }

  while(GetRead(stdin, Read))
  {
    seqSize = strlen((char *) Read->bases) - 1;

    fprintf(stdout, "@");
    for(index = 0 ; index < strlen((char *) Read->header1)-1 ; ++index)
      fprintf(stdout, "%c", Read->header1[index]);
    fprintf(stdout, " (Reversed)\n");
    for(index = seqSize ; index > 0 ; --index)
        fprintf(stdout, "%c", Read->bases[index-1]);

    fprintf(stdout, "\n+\n");
    for(index = seqSize ; index > 0 ; --index)
      fprintf(stdout, "%c", Read->scores[index-1]);
        
    fprintf(stdout, "\n");
  }

  FreeRead(Read);
  return EXIT_SUCCESS;
}