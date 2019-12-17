#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"
#include "misc.h"
#include "mem.h"
#include "buffer.h"
#include "argparse.h"

/*
 * This application reverses the ACGT bases order for each read in a sequence file
 */
int main(int argc, char *argv[])
{
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
  argparse_describe(&argparse, "\nIt reverses the ACGT bases order for each read in a sequence file.", usage);
  argc = argparse_parse(&argparse, argc, argv);

  if(argc != 0)
    argparse_help_cb(&argparse, options);

  Buffer = CreateBuffer(BUF_SIZE);
  while((streamSize = fread(Buffer->buf, 1, Buffer->size, stdin)))
  {
    for(index = streamSize ; index > 0 ; --index)
    {
      value = Buffer->buf[index-1];
      putchar(value);
    }
  }

  RemoveBuffer(Buffer); 
  return EXIT_SUCCESS;
}

