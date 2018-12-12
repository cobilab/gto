#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "defs.h"
#include "misc.h"
#include "mem.h"
#include "buffer.h"
#include "argparse.h"

#define BREAKER 100

/*
 * This application converts a genomic sequence to pseudo FASTA file format.
 */
int main(int argc, char *argv[])
{
  uint32_t sequenceSize, index, pos = 0, lineSize = BREAKER;
  uint8_t  value;
  BUF *Buffer;
  const char *readTitle = NULL;

  char *programName = argv[0];
  struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_BUFF('<', "input.seq", "Input sequence file (stdin)"),
        OPT_BUFF('>', "output.fasta", "Output FASTA file format (stdout)"),
        OPT_GROUP("Optional options"),
        OPT_STRING('n', "name", &readTitle, "The read's header"),
        OPT_INTEGER('l', "lineSize", &lineSize, "The maximum of chars for line"),
        OPT_END(),
  };
  struct argparse argparse;

  char usage[250] = "\nExample: "; 
  strcat(usage, programName);
  strcat(usage, " -l <lineSize> -n <name> < input.seq > output.fasta\n");

  argparse_init(&argparse, options, NULL, programName, 0);
  argparse_describe(&argparse, "\nIt converts a genomic sequence to pseudo FASTA file format.", usage);
  argc = argparse_parse(&argparse, argc, argv);

  if(argc != 0)
    argparse_help_cb(&argparse, options);

  if(lineSize <= 0 || lineSize > UINT_MAX)
  {
    fprintf(stderr, "\nERROR: The paramenter ''lineSize'' most be a positive unsigned int!\n");
    argparse_help_cb(&argparse, options);
    exit(1);
  }

  if(readTitle != NULL)
    fprintf(stdout, ">%s\n", readTitle);
  else
    fprintf(stdout, ">Computed_with_%s\n", programName);

  Buffer = CreateBuffer(BUF_SIZE);
  while((sequenceSize = fread(Buffer->buf, 1, Buffer->size, stdin)))
    for(index = 0 ; index < sequenceSize ; ++index)
    {
      value = Buffer->buf[index];

      if(value == '\n')
        continue; 

      putchar(value);
      if(++pos == lineSize)
      {
        putchar('\n');
        pos = 0;
      }
    }
  RemoveBuffer(Buffer); 

  return EXIT_SUCCESS;
}