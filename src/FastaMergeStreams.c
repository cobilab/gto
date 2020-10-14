#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "argparse.h"
#include <unistd.h>


/* 
 * This application merges FASTA into three channels of information: 
 *        - HEADERS;
 *        - EXTRA;
 *        - DNA.
 */
int main(int argc, char *argv[])
{

  FILE *HEADERS, *EXTRA, *DNA;
  int c, d = 0;
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
        OPT_BUFF('>', "output", "Output FASTA file format (stdout)"),
        OPT_END(),
  };
  struct argparse argparse;

  char usage[250] = "\nExample: "; 
  strcat(usage, programName);
  strcat(usage, " -e <filename> -d <filename> -H <filename> > output.fasta\n");

  argparse_init(&argparse, options, NULL, programName, 0);
  argparse_describe(&argparse, "\nIt merges the three channels of information (headers, extra and DNA) and writes it into a FASTA file.", usage);
  argc = argparse_parse(&argparse, argc, argv);

  if(argc != 0)
    argparse_help_cb(&argparse, options);

  if(output_headers == NULL)
    output_headers = "HEADERS.JV2";

  if((HEADERS = fopen (output_headers, "r")) == NULL)
  {
    fprintf(stderr, "Error: could not open file!");
    return 1;
  }

  if(output_extra == NULL)
    output_extra = "EXTRA.JV2";

  if((EXTRA = fopen (output_extra, "r")) == NULL)
  {
    fprintf(stderr, "Error: could not open file!");
    return 1;
  }

  if(output_dna == NULL)
    output_dna = "DNA.JV2";

  if((DNA = fopen (output_dna, "r")) == NULL)
  {
    fprintf(stderr, "Error: could not open file!");
    return 1;
  }

  while((c = fgetc(EXTRA)) != EOF)
  {
    
    if(c == '>')
    {
      fprintf(stdout, "%c", c);
      while((c = fgetc(HEADERS)) != EOF)
      {
        if(c == EOF) goto x;
        fprintf(stdout, "%c", c);
        if(c == '\n') break;
      }
      continue;
    }
    
    switch(c)
    {
      
      case 0:
        if((d = fgetc(DNA)) == EOF)
        {
          fprintf(stderr, "Error: invalid format!");
          return 1;
        }
        fprintf(stdout, "%c", d); 
        break;

      case 1:
        if((d = fgetc(DNA)) == EOF)
        {
          fprintf(stderr, "Error: invalid format!");
          return 1;
        }
        fprintf(stdout, "%c", tolower(d));
        break;
      
        default:
          fprintf(stdout, "%c", c);
        break;      
    }
  }

  x:

  if(!HEADERS) fclose(HEADERS);
  if(!EXTRA)   fclose(EXTRA);
  if(!DNA)     fclose(DNA);
  return EXIT_SUCCESS;
}