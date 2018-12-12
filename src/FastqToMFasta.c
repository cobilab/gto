#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"
#include "misc.h"
#include "mem.h"
#include "buffer.h"
#include "argparse.h"

/*
 * This application converts a FASTQ file format to a pseudo Multi-FASTA file.
 */
int main(int argc, char *argv[])
{
  uint32_t streamSize, index;
  uint8_t  value, line = 0, pos = 0;
  BUF *Buffer;

  char *programName = argv[0];
  struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_BUFF('<', "input.fastq", "Input FASTQ file format (stdin)"),
        OPT_BUFF('>', "output.mfasta", "Output Multi-FASTA file format (stdout)"),
        OPT_END(),
  };
  struct argparse argparse;

  char usage[250] = "\nExample: "; 
  strcat(usage, programName);
  strcat(usage, " < input.fastq > output.mfasta\n");

  argparse_init(&argparse, options, NULL, programName, 0);
  argparse_describe(&argparse, 
    "\nIt converts a FASTQ file format to a pseudo Multi-FASTA file.\n"
    "It does NOT align the sequence.\n"
    "It extracts the sequence and adds each header in a Multi-FASTA format.\n", usage);
  argc = argparse_parse(&argparse, argc, argv);

  if(argc != 0)
    argparse_help_cb(&argparse, options);

  Buffer = CreateBuffer(BUF_SIZE);

  while((streamSize = fread(Buffer->buf, 1, Buffer->size, stdin)))
    for(index = 0 ; index < streamSize ; ++index)
    {
      value = Buffer->buf[index];
      switch(line)
      { 
        case 0: 
          if(value == '\n') line = 1;
          if(value == '@' && pos++ == 0)
            putchar('>');
          else
            putchar(value);
          break;
        case 1: 
          if(value == '\n') line = 2;
          putchar(value);
          break;
        case 2:
          if(value == '\n') line = 3;
          break;
        case 3:
          if(value == '\n')
          { 
            line = 0;
            pos  = 0;
          }
          break;
      } 
    }

  RemoveBuffer(Buffer); 
  return EXIT_SUCCESS;
}

