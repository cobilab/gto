#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "defs.h"
#include "misc.h"
#include "mem.h"
#include "parser.h"
#include "buffer.h"
#include "argparse.h"
/*
 * This application reverses the ACGT bases order for each read in FASTA or Multi-FASTA file format.
 */
int main(int argc, char *argv[])
{
  uint32_t streamSize, index, tmpIndex, basesIndex = 0;
  uint8_t  value, line = 0;
  PARSER *Parser = CreateParser();
  BUF *Buffer;

  char *programName = argv[0];
  struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_BUFF('<', "input.fasta", "Input FASTA or Multi-FASTA file format (stdin)"),
        OPT_BUFF('>', "output.fasta", "Output FASTA or Multi-FASTA file format (stdout)"),
        OPT_END(),
  };
  struct argparse argparse;

  char usage[250] = "\nExample: "; 
  strcat(usage, programName);
  strcat(usage, " < input.mfasta > output.mfasta\n");

  argparse_init(&argparse, options, NULL, programName, 0);
  argparse_describe(&argparse, "\nIt reverses the ACGT bases order for each read in a FASTA or Multi-FASTA file.", usage);
  argc = argparse_parse(&argparse, argc, argv);

  if(argc != 0 || ftell(stdin))
    argparse_help_cb(&argparse, options);

  FileType(Parser, stdin);
  if(Parser->type != 1)
  {
    fprintf(stderr, "ERROR: This is not a FASTA file!\n");
    exit(1);
  }

  Buffer = CreateBuffer(BUF_SIZE);
  while((streamSize = fread(Buffer->buf, 1, Buffer->size, stdin)))
  {
    uint8_t basesByRead[streamSize];
    basesIndex = 0;
    for(index = 0 ; index < streamSize ; ++index)
    {
      value = Buffer->buf[index];
      switch(line)
      {
        case 0: 
          if(value == '\n')
          {
            line = 1;
            fprintf(stdout, " (Reversed)");
          }
          putchar(value);
          break;

        case 1: 
          if(value == '\n')
          { 
            line = 2; 
            break; 
          }
          basesByRead[basesIndex++] = value;
          break;

        case 2:
          if(value == '>')
          {
            line = 0;
            for(tmpIndex = basesIndex ; tmpIndex > 0 ; --tmpIndex)
              putchar(basesByRead[tmpIndex-1]);
            basesIndex = 0;
            putchar('\n');
            putchar(value);
          }
          else
          {
            line = 1;
            basesByRead[basesIndex++] = value;
          }
          break;
      } 
      if (index == streamSize-1) //Last read
      {
        if(value != '\n')
          putchar(value);
        for(tmpIndex = basesIndex ; tmpIndex > 0 ; --tmpIndex)
          putchar(basesByRead[tmpIndex-1]);
        break;
      }
    }
  }

  RemoveBuffer(Buffer); 
  return EXIT_SUCCESS;
}