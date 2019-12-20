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

static uint8_t FindComplement(uint8_t value)
{
  switch(tolower(value)){
    case 'a': return 'T';
    case 't': return 'A';
    case 'c': return 'G';
    case 'g': return 'C';
    default:  return value;
  }
}

/* 
 * This application replaces the ACGT bases with their complements in FASTA or Multi-FASTA file format.
 */
int main(int argc, char *argv[])
{
  uint32_t streamSize, index;
  uint8_t  value, line = 0, position = 1;
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
  argparse_describe(&argparse, "\nIt replaces the ACGT bases with their complements in FASTA or Multi-FASTA file format.\n", usage);
  argc = argparse_parse(&argparse, argc, argv);

  if(argc != 0)
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
    for(index = 0 ; index < streamSize ; ++index)
    {
      value = Buffer->buf[index];
      switch(line)
      {
        case 0: 
          if(position == 0 && value != '>')
          {
            putchar(FindComplement(value));
            line = 1;
            break;
          }

          if(value == '\n')
          { 
            line = 1;
            putchar(value);
            break;
          }

          if(position++ == 0 && value == '>')
          {
            putchar(value);
            break;
          }
          putchar(value);
          break;
        case 1: 
          if(value == '\n')
          { 
            line   = 0; 
            position    = 0;
            putchar(value);
            break; 
          }
          putchar(FindComplement(value));
          break;
      } 
    }
  }

  RemoveBuffer(Buffer); 
  return EXIT_SUCCESS;
}