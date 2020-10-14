#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "argparse.h"
#include <unistd.h>

/* 
 * This application splits FASTA into three channels of information: 
 *        - HEADERS;
 *        - EXTRA;
 *        - DNA.
 */
int main(int argc, char *argv[])
{
  FILE *HEADERS, *EXTRA, *DNA;
  int c;
  const char *output_headers = NULL;
  const char *output_extra = NULL;
  const char *output_dna = NULL;

  char *programName = argv[0];
  struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_STRING('e', "extra", &output_extra, "Output file for the extra information"),
        OPT_STRING('d', "dna", &output_dna, "Output file for the DNA information"),
        OPT_STRING('H', "headers", &output_headers, "Output file for the headers information"),
        OPT_BUFF('<', "input.fastq", "Input FASTA file format (stdin)"),
        OPT_END(),
  };
  struct argparse argparse;

  char usage[250] = "\nExample: "; 
  strcat(usage, programName);
  strcat(usage, " -e <filename> -d <filename> -H <filename> < input.fastq\n");

  argparse_init(&argparse, options, NULL, programName, 0);
  argparse_describe(&argparse, "\nIt splits and writes a FASTA file into three channels of information: headers, extra and DNA.", usage);
  argc = argparse_parse(&argparse, argc, argv);

  if(argc != 0 || isatty(STDIN_FILENO))
    argparse_help_cb(&argparse, options);

  if(output_headers == NULL)
    output_headers = "HEADERS.JV2";

  if((HEADERS = fopen (output_headers, "w")) == NULL)
  {
    fprintf(stderr, "Error: could not open file!");
    return 1;
  }

  if(output_extra == NULL)
    output_extra = "EXTRA.JV2";

  if((EXTRA = fopen (output_extra, "w")) == NULL)
  {
    fprintf(stderr, "Error: could not open file!");
    return 1;
  }

  if(output_dna == NULL)
    output_dna = "DNA.JV2";

  if((DNA = fopen (output_dna, "w")) == NULL)
  {
    fprintf(stderr, "Error: could not open file!");
    return 1;
  }

  while((c = fgetc(stdin)) != EOF)
  {
    if(c == '>')
    {
      fprintf(EXTRA, "%c", c);
      while((c = fgetc(stdin)) != EOF)
      {
        if(c == EOF) goto x;
        fprintf(HEADERS, "%c", c);
        if(c == '\n') break;
      }
      continue;
    }
      
    switch(c)
    {
      case 'A': case 'C': case 'G': case 'T':
        fprintf(DNA,   "%c", c); 
        fprintf(EXTRA, "%c", 0); 
      break;

      case 'a': case 'c': case 'g': case 't':
        fprintf(DNA,   "%c", toupper(c));  
        fprintf(EXTRA, "%c", 1);
      break;
      
      default:
        fprintf(EXTRA, "%c", c);
      break;      
    }
  }

  x:

  if(!HEADERS) fclose(HEADERS);
  if(!EXTRA)   fclose(EXTRA);
  if(!DNA)     fclose(DNA);
  return EXIT_SUCCESS;
}