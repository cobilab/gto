#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>
#include "mem.h"
#include "defs.h"
#include "labels.h"
#include "common.h"
#include "parser.h"
#include "argparse.h"

/*
 * This application extracts unique reads from Multi-FASTA files.
 */
int main(int argc, char *argv[])
{
  char fname[8000];
  uint64_t nSeq, n, unique;
  uint32_t filtered;
  int sym;
  PARSER *Parser = CreateParser();

  char *programName = argv[0];
  struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_BUFF('<', "input.fasta", "Input Multi-FASTA file format (stdin)"),
        OPT_BUFF('>', "output.fasta", "Output FASTA or Multi-FASTA file format (stdout)"),
        OPT_END(),
  };
  struct argparse argparse;

  char usage[250] = "\nExample: "; 
  strcat(usage, programName);
  strcat(usage, " < input.fasta > output.fasta\n");

  argparse_init(&argparse, options, NULL, programName, 0);
  argparse_describe(&argparse, "\nIt extracts unique reads from Multi-FASTA files.", usage);
  argc = argparse_parse(&argparse, argc, argv);

  if(argc != 0)
    argparse_help_cb(&argparse, options);

  FileType(Parser, stdin);
  if(Parser->type != 1)
  {
    fprintf(stderr, "ERROR: This is not a FASTA file!\n");
    exit(1);
  }

  SLABELS *SL = CreateSLabels();
  // tested at: https://regex101.com/
  char *regexString = ".*\\|.*\\|.*\\|_([a-z A-Z]*_[a-z A-Z]*)";
  regex_t regexCompiled;
  regmatch_t groupArray[2];
  if(regcomp(&regexCompiled, regexString, REG_EXTENDED))
  {
    fprintf(stderr, "  [x] Error: regular expression compilation!\n");
    return 1;
  }

  nSeq = 0;
  unique = 0;
  filtered = 0;
  while((sym = fgetc(stdin)) != EOF)
  {
    if(sym == '>')
    {
      HD:
      if(fscanf(stdin, "%s", fname) != 1)
      {
        fprintf(stderr, "  [x] Error: unknown type of file!\n");
        exit(1);
      }

      if(regexec(&regexCompiled, fname, 2, groupArray, 0) == 0)
      {
        char sourceCopy[strlen(fname) + 1];
        strcpy(sourceCopy, fname);
        sourceCopy[groupArray[1].rm_eo] = 0;
        if(SearchSLabels(SL, sourceCopy + groupArray[1].rm_so) == 0)
        {
          ++unique;
          AddSLabel(SL, sourceCopy + groupArray[1].rm_so);
          UpdateSLabels(SL);
        }
        else
        {
          ++filtered;
          continue;
        }
      }
      ++nSeq;

      fprintf(stdout, ">%s", fname);
      while(((sym = fgetc(stdin)) != EOF))
      {
        if(sym == '>')
          goto HD;
        fputc(sym, stdout);
      }
    }
  }

  fprintf(stderr, "Number of unique existing species: %"PRIu64".\n", unique);
  fprintf(stderr, "Unique species:\n");
  for(n = 0 ; n < SL->idx ; ++n)
    fprintf(stderr, "  [+] %s\n", SL->names[n]);
  DeleteSLabels(SL);
  
  return EXIT_SUCCESS;
}
