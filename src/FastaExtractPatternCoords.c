#include <stdio.h>
#include <stdlib.h>
#define _GNU_SOURCE
#include <string.h>
#include "defs.h"
#include "misc.h"
#include "mem.h"
#include "buffer.h"
#include "argparse.h"

#define MAX_HEADER 16384
/*
 * This application extracts the header and coordinates from a Multi-FASTA
 * file format given a pattern/motif in the sequence.
 */
int main(int argc, char *argv[])
{
  uint32_t streamSize, index, indexHeader = 0, len = 0, x;
  uint64_t position = 0;
  uint8_t  value, header = 1, write = 0;
  uint8_t  *hName = (uint8_t *) Calloc(MAX_HEADER+1, sizeof(uint8_t));
  const char *pattern = NULL;
  BUF  *Buffer;
  CBUF *DNA;

  char *programName = argv[0];
  struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_STRING('p', "pattern", &pattern, "Pattern to search in the file header"),
        OPT_BUFF('<', "input.mfasta", "Input Multi-FASTA file format (stdin)"),
        OPT_BUFF('>', "output.coords", "Output coordinates (stdout)"),
        OPT_END(),
  };
  struct argparse argparse;

  char usage[250] = "\nExample: "; 
  strcat(usage, programName);
  strcat(usage, " -p <pattern> < input.mfasta > output.coords\n");

  argparse_init(&argparse, options, NULL, programName, 0);
  argparse_describe(&argparse, "\nIt extracts the header and coordinates from a Multi-FASTA file format given a pattern/motif in the sequence.", usage);
  argc = argparse_parse(&argparse, argc, argv);

  if(argc != 0 || ftell(stdin))
    argparse_help_cb(&argparse, options);


  if(pattern == NULL)
  {
    fprintf(stderr, "\nERROR: The pattern must be defined!\n");
    argparse_help_cb(&argparse, options);
    exit(1);
  }

  len = strlen(pattern);
  Buffer   = CreateBuffer(BUF_SIZE);
  DNA = CreateCBuffer(BUF_SIZE, len+1);

  while((streamSize = fread(Buffer->buf, 1, Buffer->size, stdin)))
    for(index = 0 ; index < streamSize ; ++index)
    {
      value = Buffer->buf[index];
      if(value == '>')
      { 
        indexHeader = 0;
        hName[indexHeader] = value;
        header = 1; 
        position = 0;
        write = 0;
        continue; 
      }
      
      if(header == 1)
      {
        if(value != '\n')
        {
          if(++indexHeader < MAX_HEADER)
          {
            hName[indexHeader] = value;
          }
          else
          {
            hName[indexHeader] = '\0';
          }            
        }
        else
        {
          header = 0; 
          hName[indexHeader+1] = '\0';
        }
        continue;
      }

      DNA->buf[DNA->idx] = value;

      if(++position >= len)
      {
        write = 1;
        for(x = 0 ; x < len ; ++x)
        {
          if(DNA->buf[DNA->idx-len+1+x] != pattern[x])// REVERSE PATTERN
          { 
            write = 0;
            break;
          }
        }       
 
        if(write == 1)
        {
          fprintf(stdout, "%"PRIu64"\t%"PRIu64"\t%s\n", position-len+1, position, hName);
        }
      }
      
      UpdateCBuffer(DNA);
    }

  RemoveBuffer(Buffer); 
  RemoveCBuffer(DNA); 
  Free(hName, 0);
  return EXIT_SUCCESS;
}