#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"
#include "misc.h"
#include "mem.h"
#include "buffer.h"
#include "argparse.h"

/*
 * This application splits a Multi-FASTA file to multiple FASTA files.
 */
int main(int argc, char *argv[])
{
  uint32_t streamSize, index;
  uint32_t indexHeader = 0;
  uint64_t indexSymbol = 0;
  uint8_t  value;
  char *location = ".";
  BUF *Buffer;

  char *programName = argv[0];
  struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_BUFF('<', "input.fasta", "Input Multi-FASTA file format (stdin)"),
        OPT_GROUP("Optional options"),
        OPT_STRING('l', "location", &location, "Location to store the files"),
        OPT_END(),
  };
  struct argparse argparse;

  char usage[250] = "\nExample: "; 
  strcat(usage, programName);
  strcat(usage, " < input.fasta\n");

  argparse_init(&argparse, options, NULL, programName, 0);
  argparse_describe(&argparse, 
    "\nIt splits a Multi-FASTA file to multiple FASTA files.", usage);
  argc = argparse_parse(&argparse, argc, argv);

  if(argc != 0)
    argparse_help_cb(&argparse, options);

  Buffer = CreateBuffer(BUF_SIZE);

  indexHeader = 0;
  FILE *OUT = NULL;

  while((streamSize = fread(Buffer->buf, 1, Buffer->size, stdin)))
    for(index = 0 ; index < streamSize ; ++index)
    {
      value = Buffer->buf[index];

      if(++indexSymbol == 1 && value == '\n')
        continue;

      if(value == '>')
      {
        if(++indexHeader > 1) 
          fclose(OUT);

        char name[500];
        char fileLocation[2048];
        sprintf(name, "out%u.fasta", indexHeader);
        strcpy(fileLocation, location);
        strcat(fileLocation, "/");
        strcat(fileLocation, name);

        fprintf(stderr, "%u : Splitting to file:%s\n", indexHeader, fileLocation);
        OUT = Fopen(fileLocation, "w");
      }
      fprintf(OUT, "%c", value);
    }

  if(!OUT) fclose(OUT);

  RemoveBuffer(Buffer); 
  return EXIT_SUCCESS;
}