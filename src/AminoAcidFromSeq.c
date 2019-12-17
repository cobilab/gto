#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"
#include "misc.h"
#include "mem.h"
#include "parser.h"
#include "buffer.h"
#include "argparse.h"

/* 
 * This application converts DNA sequences to an amino acid sequence.
 */
int main(int argc, char *argv[]){
  uint32_t streamSize, index;
  uint8_t  value;
  BUF *Buffer;
  
  char *programName = argv[0];
  struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_BUFF('<', "input.seq", "Input sequence file (stdin)"),
        OPT_BUFF('>', "output.prot", "Output amino acid sequence file (stdout)"),
        OPT_END(),
  };
  struct argparse argparse;

  char usage[250] = "\nExample: "; 
  strcat(usage, programName);
  strcat(usage, " < input.seq > output.prot\n");

  argparse_init(&argparse, options, NULL, programName, 0);
  argparse_describe(&argparse, "\nIt converts DNA sequence to an amino acid sequence.\n", usage);
  argc = argparse_parse(&argparse, argc, argv);

  if(argc != 0 || ftell(stdin))
    argparse_help_cb(&argparse, options);

  Buffer = CreateBuffer(BUF_SIZE);

  while((streamSize = fread(Buffer->buf, 1, Buffer->size, stdin)))
    for(index = 0 ; index < streamSize ; ++index)
    {
      value = Buffer->buf[index];
      if(value == '\n')
        continue;
      //HERE
      //putchar(value);
    } 

  RemoveBuffer(Buffer); 
  return EXIT_SUCCESS;
}