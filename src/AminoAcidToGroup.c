#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"
#include "misc.h"
#include "mem.h"
#include "buffer.h"
#include "argparse.h"

/*
 * This application converts a amino acid sequence to a group sequence.
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
        OPT_BUFF('>', "output.group", "Output group sequence file (stdout)"),
        OPT_END(),
  };
  struct argparse argparse;

  char usage[500] = "\nExample: "; 
  strcat(usage, programName);
  strcat(usage, " < input.prot > output.group\n");
  strcat(usage, "Table:\n");
  strcat(usage, "Prot\tGroup\n");
  strcat(usage, "R\tP\n");
  strcat(usage, "H\tP  Amino acids with electric charged side chains: POSITIVE\n");
  strcat(usage, "K\tP\n");
  strcat(usage, "-\t-\n");
  strcat(usage, "D\tN\n");
  strcat(usage, "E\tN  Amino acids with electric charged side chains: NEGATIVE\n");
  strcat(usage, "-\t-\n");
  strcat(usage, "S\tU\n");
  strcat(usage, "T\tU\n");
  strcat(usage, "N\tU  Amino acids with electric UNCHARGED side chains\n");
  strcat(usage, "Q\tU\n");
  strcat(usage, "-\t-\n");
  strcat(usage, "C\tS\n");
  strcat(usage, "U\tS\n");
  strcat(usage, "G\tS  Special cases\n");
  strcat(usage, "P\tS\n");
  strcat(usage, "-\t-\n");
  strcat(usage, "A\tH\n");
  strcat(usage, "V\tH\n");
  strcat(usage, "I\tH\n");
  strcat(usage, "L\tH\n");
  strcat(usage, "M\tH  Amino acids with hydrophobic side chains\n");
  strcat(usage, "F\tH\n");
  strcat(usage, "Y\tH\n");
  strcat(usage, "W\tH\n");
  strcat(usage, "-\t-\n");
  strcat(usage, "*\t*  Others\n");
  strcat(usage, "X\tX  Unknown\n");

  argparse_init(&argparse, options, NULL, programName, 0);
  argparse_describe(&argparse, "\nIt converts a amino acid sequence to a group sequence.", usage);
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
        case 'R': putchar('P'); break;
        case 'H': putchar('P'); break;
        case 'K': putchar('P'); break;

        case 'D': putchar('N'); break;
        case 'E': putchar('N'); break;

        case 'S': putchar('U'); break;
        case 'T': putchar('U'); break;
        case 'N': putchar('U'); break;
        case 'Q': putchar('U'); break;

        case 'C': putchar('S'); break;
        case 'U': putchar('S'); break;
        case 'G': putchar('S'); break;
        case 'P': putchar('S'); break;

        case 'A': putchar('H'); break;
        case 'V': putchar('H'); break;
        case 'I': putchar('H'); break;
        case 'L': putchar('H'); break;
        case 'M': putchar('H'); break;
        case 'F': putchar('H'); break;
        case 'Y': putchar('H'); break;
        case 'W': putchar('H'); break;

        case '*': putchar('*'); break;
        case 'X': putchar('X'); break;
      }
    }
  }

  RemoveBuffer(Buffer);

  return EXIT_SUCCESS;
}


