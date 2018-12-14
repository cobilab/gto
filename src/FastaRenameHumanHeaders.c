#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"
#include "misc.h"
#include "mem.h"
#include "buffer.h"
#include "argparse.h"

/*
 * It changes the headers of FASTA or Multi-FASTA file to simple chr$1 by order.
 */
int main(int argc, char *argv[])
{
  BUF *Buffer;
  int64_t header = 0, streamSize = 0, index = 0;
  uint8_t value; 
  uint8_t chrs[30][4] = {"1", "2", "3", "4", "5", "6", "7", "8", 
                       "9", "10", "11", "12", "13", "14", "15",
                       "16", "17", "18", "19", "20", "21", "22",
                       "X", "Y", "M", "UN", "UP", "?", "?", "?"};

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
  strcat(usage, " < input.fasta > output.fasta\n");

  argparse_init(&argparse, options, NULL, programName, 0);
  argparse_describe(&argparse, "\nIt changes the headers of FASTA or Multi-FASTA file to simple chr$1 by order.", usage);
  argc = argparse_parse(&argparse, argc, argv);

  if(argc != 0)
    argparse_help_cb(&argparse, options);

  Buffer = CreateBuffer(BUF_SIZE);
  int indexHeader = 0;
  while((streamSize = fread(Buffer->buf, 1, Buffer->size, stdin)))
    for(index = 0 ; index < streamSize ; ++index)
    {
      value = Buffer->buf[index];
      if(value == '>')
        header = 1;
        

      if(header == 1 && value == '\n')
      {   
        fprintf(stdout, ">chr%s\n", chrs[indexHeader]);
        if(indexHeader < 29)
          ++indexHeader;
        header = 0;
        continue;
      }

      if(header == 0)
        putchar(value);
    }
  RemoveBuffer(Buffer);

  return EXIT_SUCCESS;
}

