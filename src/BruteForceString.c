#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mem.h"
#include "argparse.h"

// "abcdefghijklmnopqrstuvwxyz"
// "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
// "0123456789";
// "|!"#$%&/()=?»,.-~º'+«}][{¬½§£@¹¬"

void BruteForce(char *str, int idx, int max_depth, char *alpha, int alpha_size)
{
  int64_t x;

  for(x = 0 ; x < alpha_size ; ++x)
  {
    str[idx] = alpha[x];
    if(idx == max_depth - 1) 
      printf("%s\n", str);
    else 
      BruteForce(str, idx + 1, max_depth, alpha, alpha_size);
  }
}

void Brute(int max_k, char *alpha, int alpha_size)
{
  int64_t x;  
  char *buf = (char *) Malloc((max_k + 1) * sizeof(char));

  for(x = max_k ; x <= max_k ; ++x)
  { // x = 1 to generate from k=1 to k=max_k
    x = max_k;
    memset(buf, 0, max_k + 1);
    BruteForce(buf, 0, x, alpha, alpha_size);
  }

  Free(buf, 0);
}

/*
 * This application generates all combinations, line by line, for an inputted alphabet and specific size.
 */
int main(int argc, char *argv[])
{
  char *alphabet = NULL;
  int size = 0;

  char *programName = argv[0];
  struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_STRING('a', "alphabet", &alphabet, "The input alphabet"),
        OPT_INTEGER('s', "size", &size, "The combinations size"),
        OPT_BUFF('>', "output", "Output all the combinations (stdout)"),
        OPT_END(),
  };
  struct argparse argparse;

  char usage[250] = "\nExample: "; 
  strcat(usage, programName);
  strcat(usage, " -a <alphabet> -s <size> > output\n");

  argparse_init(&argparse, options, NULL, programName, 0);
  argparse_describe(&argparse, "\nIt generates all combinations, line by line, for an inputted alphabet and specific size.", usage);
  argc = argparse_parse(&argparse, argc, argv);

  if(argc != 0)
    argparse_help_cb(&argparse, options);

  int alphabetSize = strlen(alphabet);
  Brute(size, alphabet, alphabetSize);

  return EXIT_SUCCESS;
}