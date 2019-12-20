#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"
#include "misc.h"
#include "mem.h"
#include "buffer.h"
#include "argparse.h"

static void RandIfExtra(uint8_t value, char *bases)
{
  if(value == 'A' || value == 'C' || value == 'G' || value == 'T')
  {
    putchar(value);
    return;
  }
  putchar(bases[rand()%4]);
}

/* 
 * This application substitues in the DNA sequence the outside ACGT chars by random ACGT symbols.
 */
int main(int argc, char *argv[]){
  uint32_t streamSize, index, seed = 0;
  uint8_t  value;
  char     *bases = "ACGT";
  BUF *Buffer;
  srand(seed);
  
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
  argparse_describe(&argparse, "\nIt substitues in the DNA sequence the outside "
    "ACGT chars by random ACGT symbols.\nIt works in sequence file formats\n", usage);
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
      RandIfExtra(value, bases);
    } 

  RemoveBuffer(Buffer); 
  return EXIT_SUCCESS;
}