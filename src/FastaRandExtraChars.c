#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#include "misc.h"
#include "mem.h"
#include "buffer.h"
#include "parser.h"
#include "argparse.h"
#include <string.h>
#include <unistd.h>

/* 
 * This application substitues in the DNA sequence the outside ACGT chars by random ACGT symbols.
 * It works both in FASTA and Multi-FASTA file formats.
 */
static void RandIfExtra(uint8_t value, char *bases)
{
  if(value == 'A' || value == 'C' || value == 'G' || value == 'T')
  {
    putchar(value);
    return;
  }
  putchar(bases[rand()%4]);
}

int main(int argc, char *argv[])
{
  uint32_t streamSize, index, seed = 0;
  uint8_t  value, line = 0, position = 1;
  char     *bases = "ACGT";
  PARSER *Parser = CreateParser();
  BUF *Buffer;
  srand(seed);

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
  argparse_describe(&argparse, "\nIt substitues in the DNA sequence the outside "
    "ACGT chars by random ACGT symbols.\nIt works both in FASTA and Multi-FASTA " 
    "file formats\n", usage);
  argc = argparse_parse(&argparse, argc, argv);

  if(argc != 0 || isatty(STDIN_FILENO))
    argparse_help_cb(&argparse, options);

  FileType(Parser, stdin);
  if(Parser->type != 1)
  {
    fprintf(stderr, "ERROR: This is not a FASTA file!\n");
    exit(1);
  }

  Buffer = CreateBuffer(BUF_SIZE);

  uint8_t header = 0, sym;
  while((streamSize = fread(Buffer->buf, 1, Buffer->size, stdin)))
  {
    for(index = 0 ; index < streamSize ; ++index)
    {
      sym = Buffer->buf[index];

      if(sym == '>'){ header = 1; putchar(sym); continue; }
      if(sym == '\n' && header == 1){ header = 0; putchar(sym); continue; }
      if(sym == '\n'){ putchar(sym); continue; }
      if(header == 1){ putchar(sym); continue; }

      RandIfExtra(sym, bases);
    }
  }

  RemoveBuffer(Buffer); 
  return EXIT_SUCCESS;
}

