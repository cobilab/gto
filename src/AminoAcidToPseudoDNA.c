#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"
#include "misc.h"
#include "mem.h"
#include "buffer.h"
#include "argparse.h"

/*
 * This application converts a protein sequence to a pseudo DNA sequence.
 */
int main(int argc, char *argv[])
{
  int64_t streamSize, index;
  char value;
  BUF *Buffer;


  char *programName = argv[0];
  struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_BUFF('<', "input.prot", "Input amino acid sequence file (stdin)"),
        OPT_BUFF('>', "output.dna", "Output DNA sequence file (stdout)"),
        OPT_END(),
  };
  struct argparse argparse;

  char usage[500] = "\nExample: "; 
  strcat(usage, programName);
  strcat(usage, " < input.prot > output.dna\n");
  strcat(usage, "Table:\n");
  strcat(usage, "Prot\tDNA\n");
  strcat(usage, "A\tGCA\n");
  strcat(usage, "C\tTGC\n");
  strcat(usage, "D\tGAC\n");
  strcat(usage, "E\tGAG\n");
  strcat(usage, "F\tTTT\n");
  strcat(usage, "G\tGGC\n");
  strcat(usage, "H\tCAT\n");
  strcat(usage, "I\tATC\n");
  strcat(usage, "K\tAAA\n");
  strcat(usage, "L\tCTG\n");
  strcat(usage, "M\tATG\n");
  strcat(usage, "N\tAAC\n");
  strcat(usage, "P\tCCG\n");
  strcat(usage, "Q\tCAG\n");
  strcat(usage, "R\tCGT\n");
  strcat(usage, "S\tTCT\n");
  strcat(usage, "T\tACG\n");
  strcat(usage, "V\tGTA\n");
  strcat(usage, "W\tTGG\n");
  strcat(usage, "Y\tTAC\n");
  strcat(usage, "*\tTAG\n");
  strcat(usage, "X\tGGG\n");

  argparse_init(&argparse, options, NULL, programName, 0);
  argparse_describe(&argparse, "\nIt converts a protein sequence to a pseudo DNA sequence.", usage);
  argc = argparse_parse(&argparse, argc, argv);

  if(argc != 0)
    argparse_help_cb(&argparse, options);

  Buffer = CreateBuffer(BUF_SIZE);
  while((streamSize = fread(Buffer->buf, 1, Buffer->size, stdin)))
  {
    for(index = 0 ; index < streamSize ; ++index)
    {
      value = Buffer->buf[index];
      switch(value)
      {
        case 'A': fprintf(stdout, "GCA"); break;
        case 'C': fprintf(stdout, "TGC"); break;
        case 'D': fprintf(stdout, "GAC"); break;
        case 'E': fprintf(stdout, "GAG"); break;
        case 'F': fprintf(stdout, "TTT"); break;
        case 'G': fprintf(stdout, "GGC"); break;
        case 'H': fprintf(stdout, "CAT"); break;
        case 'I': fprintf(stdout, "ATC"); break;
        case 'K': fprintf(stdout, "AAA"); break;
        case 'L': fprintf(stdout, "CTG"); break;
        case 'M': fprintf(stdout, "ATG"); break;
        case 'N': fprintf(stdout, "AAC"); break;
        case 'P': fprintf(stdout, "CCG"); break;
        case 'Q': fprintf(stdout, "CAG"); break;
        case 'R': fprintf(stdout, "CGT"); break;
        case 'S': fprintf(stdout, "TCT"); break;
        case 'T': fprintf(stdout, "ACG"); break;
        case 'V': fprintf(stdout, "GTA"); break;
        case 'W': fprintf(stdout, "TGG"); break;
        case 'Y': fprintf(stdout, "TAC"); break;
        case '*': fprintf(stdout, "TAG"); break;
        case 'X': fprintf(stdout, "GGG"); break;
      }
    }
  }

  RemoveBuffer(Buffer);

  return EXIT_SUCCESS;
}


