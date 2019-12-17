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
 * This application complements in the DNA sequence.
 * It works in sequence file formats.
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
        OPT_BUFF('>', "output.seq", "Output sequence file (stdout)"),
        OPT_END(),
  };
  struct argparse argparse;

  char usage[250] = "\nExample: "; 
  strcat(usage, programName);
  strcat(usage, " < input.seq > output.seq\n");

  argparse_init(&argparse, options, NULL, programName, 0);
  argparse_describe(&argparse, "\nIt replaces the ACGT bases with their complements in a DNA sequence.\nIt works in sequence file formats.\n", usage);
  argc = argparse_parse(&argparse, argc, argv);

  if(argc != 0)
    argparse_help_cb(&argparse, options);

  Buffer = CreateBuffer(BUF_SIZE);

  while((streamSize = fread(Buffer->buf, 1, Buffer->size, stdin)))
    for(index = 0 ; index < streamSize ; ++index)
    {
      value = Buffer->buf[index];
      if(value == '\n')
        continue;
      putchar(FindComplement(value));
    } 

  RemoveBuffer(Buffer); 
  return EXIT_SUCCESS;
}