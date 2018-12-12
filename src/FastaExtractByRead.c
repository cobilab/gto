#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "defs.h"
#include "misc.h"
#include "buffer.h"
#include "parser.h"
#include "argparse.h"

#define END  100

/*
 * This application extracts sequences from each read in a FASTA or Multi-FASTA file (splited by \n).
 */
int main(int argc, char *argv[])
{
  uint32_t streamSize, index;
  uint64_t counter = 0, init = 0, end = END;
  uint8_t  value, header = 1;
  PARSER *Parser = CreateParser();
  BUF *Buffer;

  char *programName = argv[0];
  struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_INTEGER('i', "init", &init, "The first position to start the extraction (default 0)"),
        OPT_INTEGER('e', "end", &end, "The last extract position (default 100)"),
        OPT_BUFF('<', "input.fasta", "Input FASTA or Multi-FASTA file format (stdin)"),
        OPT_BUFF('>', "output.fasta", "Output FASTA or Multi-FASTA file format (stdout)"),
        OPT_END(),
  };
  struct argparse argparse;

  char usage[250] = "\nExample: "; 
  strcat(usage, programName);
  strcat(usage, " -i <init> -e <end> < input.fasta > output.fasta\n");

  argparse_init(&argparse, options, NULL, programName, 0);
  argparse_describe(&argparse, "\nIt extracts sequences from each read in a FASTA or Multi-FASTA file (splited by \\n)", usage);
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

      if(value == '>')
      { 
        header = 1;
        if(counter != 0)
          putchar('\n');
        putchar(value); 
        continue; 
      }

      if(value == '\n' && header == 1)
      { 
        header = 0; 
        putchar('\n');
        counter = 0;
        continue; 
      }

      if(value == '\n') continue;

      if(header == 1) 
      {
        putchar(value);
        continue;
      }
      if(value < 65 || value > 122) continue;

      if(init <= counter && end > counter)
        putchar(value);

      ++counter;
    }
  }

  RemoveBuffer(Buffer);
  return EXIT_SUCCESS;
}
