#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"
#include "misc.h"
#include "mem.h"
#include "buffer.h"
#include "argparse.h"


#define MAX_HEADER 4096

/*
 * This application extracts reads from a Multi-FASTA file format given a pattern in the header (ID).
 */
int main(int argc, char *argv[])
{
  uint32_t streamSize, index, headerIndex = 0;
  uint8_t  value, header = 1, write = 0;
  uint8_t  *hName = (uint8_t *) Calloc(MAX_HEADER+1, sizeof(uint8_t));
  const char *pattern = NULL;
  BUF *Buffer;

  char *programName = argv[0];
  struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_STRING('p', "pattern", &pattern, "Pattern to search in the file header"),
        OPT_BUFF('<', "input.fasta", "Input Multi-FASTA file format (stdin)"),
        OPT_BUFF('>', "output.fasta", "Output Multi-FASTA file format (stdout)"),
        OPT_END(),
  };
  struct argparse argparse;

  char usage[250] = "\nExample: "; 
  strcat(usage, programName);
  strcat(usage, "-p <pattern> < input.fasta > output.fasta\n");

  argparse_init(&argparse, options, NULL, programName, 0);
  argparse_describe(&argparse, "\nIt extracts reads from a Multi-FASTA file format given a pattern in the header (ID).", usage);
  argc = argparse_parse(&argparse, argc, argv);

  if(argc != 0)
    argparse_help_cb(&argparse, options);


  if(pattern == NULL)
  {
    fprintf(stderr, "\nERROR: The pattern must be defined!\n");
    argparse_help_cb(&argparse, options);
    exit(1);
  }

  Buffer = CreateBuffer(BUF_SIZE);

  while((streamSize = fread(Buffer->buf, 1, Buffer->size, stdin)))
    for(index = 0 ; index < streamSize ; ++index)
    {
      value = Buffer->buf[index];
      if(value == '>')
      { 
        headerIndex = 0;
        hName[headerIndex] = value;
        header = 1; 
        write = 0;
        continue; 
      }
      
      if(header == 1)
      {
        if(value != '\n')
        {
          if(++headerIndex < MAX_HEADER)
            hName[headerIndex] = value;
          else
            hName[headerIndex] = '\0';            
        }
        else
        {
          header = 0; 
          hName[headerIndex+1] = '\0';
          if(strcasestr((char *) hName,(char *) pattern) != NULL)
          {
            fprintf(stdout, "%s\n", hName);
            write = 1;
          }
        }
        continue;
      }

      if(write == 1) putchar(value);
    }

  RemoveBuffer(Buffer); 
  Free(hName, 0);
  return EXIT_SUCCESS;
}

