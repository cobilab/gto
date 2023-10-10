#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"
#include "misc.h"
#include "mem.h"
#include "buffer.h"
#include "argparse.h"
#include <unistd.h>


#define MAX_HEADER 4096
#define MAX_DNA 2999999

/*
 * This application filters reads from a Multi-FASTA file format given an exclusive alphabet in the DNA sequence.
 */
int main(int argc, char *argv[])
{
  uint32_t streamSize, index, headerIndex = 0, dnaIndex = 0;
  uint8_t  value, header = 1, dna = 1, write = 0;
  int invert = 0;
  uint8_t  *hName = (uint8_t *) Calloc(MAX_HEADER+1, sizeof(uint8_t));
  uint8_t  *dName = (uint8_t *) Calloc(MAX_DNA+1,    sizeof(uint8_t));
  const char *pattern = NULL;
  BUF *Buffer;

  char *programName = argv[0];
  struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_STRING('a', "alphabet", &pattern, "alphabet to search in the file DNA"),
        OPT_BOOLEAN('i', "invert", &invert, "When active, the application filters the reads that do not match with an exclusive alphabet"),
        OPT_BUFF('<', "input.mfasta", "Input Multi-FASTA file format (stdin)"),
        OPT_BUFF('>', "output.mfasta", "Output Multi-FASTA file format (stdout)"),
        OPT_END(),
  };
  struct argparse argparse;

  char usage[250] = "\nExample: "; 
  strcat(usage, programName);
  strcat(usage, " -a <alphabet> < input.mfasta > output.mfasta\n");

  argparse_init(&argparse, options, NULL, programName, 0);
  argparse_describe(&argparse, "\nIt filters reads from a Multi-FASTA file format that do not correspond to a provided alphabet in the DNA sequence.", usage);
  argc = argparse_parse(&argparse, argc, argv);

  if(argc != 0 || isatty(STDIN_FILENO))
    argparse_help_cb(&argparse, options);


/*  if(pattern == NULL)
  {
    fprintf(stderr, "\nERROR: The pattern must be defined!\n");
    argparse_help_cb(&argparse, options);
    exit(1);
  }
*/

  Buffer = CreateBuffer(BUF_SIZE);

  dna = 0;
  header = 0;

  while((streamSize = fread(Buffer->buf, 1, Buffer->size, stdin)))
    for(index = 0 ; index < streamSize ; ++index)
    {
      value = Buffer->buf[index];

      if(dna == 1 && value == '>')
      {
	if(write == 1)
	{
          fprintf(stdout, "%s\n", hName);
          fprintf(stdout, "%s", dName);
	}
       
       	dna = 0;
      }

      if(dna == 0 && value == '>' )
      { 
        dnaIndex = 0;
        headerIndex = 0;
        hName[headerIndex] = value;
        header = 1;
        write = 1;
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
	  dna = 1;
	  header = 0;
	  write = 1;
        }

      continue;
      }

      if(dna == 1)
      {
        if(++dnaIndex < MAX_DNA)
          dName[dnaIndex] = value;
        else
          dName[dnaIndex] = '\0';

        if(value != 'A' || value != 'C' || value != 'G' || value != 'T' 
	|| value != '\n')
          write = 0; 
      }
    }

  RemoveBuffer(Buffer); 
  Free(hName, 0);
  Free(dName, 0);
  return EXIT_SUCCESS;
}

