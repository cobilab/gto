#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <ctype.h>
#include "defs.h"
#include "misc.h"
#include "argparse.h"

#define UNDEF_BASE 1

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int GetBase(void)
{
  int  base;
  char *alphabet = "ACGT";

  while((base = fgetc(stdin)) != EOF)
  {
    if(base == '>')
    {
      while((base = fgetc(stdin)) != EOF && base != '\n')
        ;
      continue;
    }
    if(base == '\n') 
      continue;
    if(!(strchr(alphabet, toupper(base)))) 
      return UNDEF_BASE;
    else 
      return !UNDEF_BASE;
  }
  return EOF;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


/*
 * This application reports the 'N' regions in a sequence or FASTA (seq) file.
 */
int main(int argc, char *argv[])
{
  uint64_t start, nBases;
  int undefSegment = 0, base;

  char *programName = argv[0];
  struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_BUFF('<', "input.fasta", "Input FASTA file format or a sequence (stdin)"),
        OPT_BUFF('>', "output", "Output report of \'N\' positions (stdout)"),
        OPT_END(),
  };
  struct argparse argparse;

  char usage[250] = "\nExample: "; 
  strcat(usage, programName);
  strcat(usage, " < input.fasta > output\n\n"
    "The output obeys the following structure:\n"
    "Begin\tEnd\tPositions\n"
    "<value>\t<value>\t<value>\n");

  argparse_init(&argparse, options, NULL, programName, 0);
  argparse_describe(&argparse, 
    "\nIt reports the \'N\' regions in a sequence or FASTA (seq) file.", usage);
  argc = argparse_parse(&argparse, argc, argv);

  if(argc != 0)
    argparse_help_cb(&argparse, options);

  nBases = 1;
  while((base = GetBase()) != EOF)
  {
    if(base == UNDEF_BASE)
    {
      if(!undefSegment)
      {
        undefSegment = 1;
        start = nBases;
      }
    }
    else
    {
      if(undefSegment)
      {
        undefSegment = 0;
        fprintf(stdout, "%"PRIu64"\t%"PRIu64"\t%"PRIu64"\n", start, nBases-1, 
        nBases-start);
      }
    }
    nBases++;
  }
  return EXIT_SUCCESS;
}