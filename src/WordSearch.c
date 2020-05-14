#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"
#include "misc.h"
#include "argparse.h"
#include <unistd.h>

/*
 * This applications search for a word in a file.
 * It is case sensitive.
 */
int main(int argc, char *argv[])
{
  uint64_t line = 0, found = 0;
  char     buf[BUFFER_SIZE_WS];
  const char *word = NULL;

  char *programName = argv[0];
  struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_STRING('w', "word", &word, "Word to search in the file"),
        OPT_BUFF('<', "input.txt", "Input text file (stdin)"),
        OPT_BUFF('>', "output.txt", "Output text file (stdout)"),
        OPT_END(),
  };
  struct argparse argparse;

  char usage[250] = "\nExample: "; 
  strcat(usage, programName);
  strcat(usage, " -w <word> < input.txt > output.txt\n");

  argparse_init(&argparse, options, NULL, programName, 0);
  argparse_describe(&argparse, "\nSearching for a word in a text file. It is case sensitive.", usage);
  argc = argparse_parse(&argparse, argc, argv);

  if(argc != 0 || isatty(STDIN_FILENO))
    argparse_help_cb(&argparse, options);

  if(word == NULL)
  {
    fprintf(stderr, "\nERROR: The word to search must be defined!\n");
    argparse_help_cb(&argparse, options);
    exit(1);
  }

  while(fgets(buf, BUFFER_SIZE_WS, stdin))
  {
    if(strstr(buf, word))
    {
      fprintf(stdout, "Found match in range [ %"PRIu64" : %"PRIu64" ]\n", 
      line*BUFFER_SIZE_WS, (line+1)*BUFFER_SIZE_WS);
      fprintf(stdout, "%s\n\n", buf);
      ++found;
    }
    ++line;
  }
  
  if(!found) 
    fprintf(stdout, "NO matches found!\n");

  return EXIT_SUCCESS;
}