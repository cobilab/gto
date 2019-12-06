#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include "filter.h"
#include "argparse.h"
#include "misc.h"
#include "mem.h"

static double CalcMean(Entry *entries, int nEntries, int n, int M, double *w)
{
  int k;
  double sum = 0, wSum = 0;
  for(k = -M ; k <= M ; k++)
    if(n + k >= 0 && n + k < nEntries)
    {
      sum += w[M+k] * entries[n+k].value;
      wSum += w[M+k];
    }
  return sum / wSum;
}

/*
 * This application filters numerical sequences using a low-pass filter.
 */
int main(int argc, char *argv[]){
  int oneCol, p1, reverse;
  int n, k, nEntries, position, M, drop, wType;
  double value, *w;
  Entry *entries = NULL;
  M       = 0;
  drop    = 0;
  wType   = W_HAMMING;
  oneCol  = 0;
  p1      = 0;
  reverse = 0;

  char *programName = argv[0];
  struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_BUFF('<', "input.num", "Input numeric file (stdin)"),
        OPT_BUFF('>', "output.num", "Output numeric file (stdout)"),
        OPT_GROUP("Optional"),
        OPT_INTEGER('w', "windowsize", &M, "Window size (defaut 0)"),
        OPT_INTEGER('d', "drop", &drop, "Discard elements (default 0.0)"),
        OPT_INTEGER('t', "windowtype", &wType, "Window type (0=Hamm, 1=Hann, 2=Black, 3=rec) (default 0 (Hamm))"),
        OPT_BOOLEAN('c', "onecolumn", &oneCol, "Read from one column"),
        OPT_BOOLEAN('p', "printone", &p1, "Print one column"),
        OPT_BOOLEAN('r', "reverse", &reverse, "Reverse mode"),
        OPT_END(),
  };
  struct argparse argparse;

  char usage[250] = "\nExample: "; 
  strcat(usage, programName);
  strcat(usage, " -w <windowsize> -d <drop> -t <windowtype> -c -p -r < input.num > output.num\n");

  argparse_init(&argparse, options, NULL, programName, 0);
  argparse_describe(&argparse, "\nIt filters numerical sequences using a low-pass filter.", usage);
  argc = argparse_parse(&argparse, argc, argv);

  if(argc != 0 || ftell(stdin))
    argparse_help_cb(&argparse, options);

  if(M < 0 || M > 10000000)
  {
    fprintf(stderr, "ERROR: The window size must be a value between 0 and 10000000!\n");
    exit(1);
  }

  if(drop < 0 || drop > 10000000)
  {
    fprintf(stderr, "ERROR: The drop value must be between 0 and 10000000!\n");
    exit(1);
  }

  if(wType < 0 || wType > 3)
  {
    fprintf(stderr, "ERROR: The window type must be 0, 1, 2 or 3!\n");
    exit(1);
  }

  nEntries = 0;
  if(oneCol == 1)
  {
    while(fscanf(stdin, "%lf", &value) == 1)
    {
      entries = (Entry *) Realloc(entries, (nEntries+1) * sizeof(Entry), 
      sizeof(Entry));
      entries[nEntries].position = nEntries;
      entries[nEntries].value = value;
      ++nEntries;
    }
  }
  else
  {
    while(fscanf(stdin, "%d%lf", &position, &value) == 2)
    {
      entries = (Entry *) Realloc(entries, (nEntries+1) * sizeof(Entry),
      sizeof(Entry));
      entries[nEntries].position = position;
      entries[nEntries].value = value;
      ++nEntries;
    }
  }

  fprintf(stderr, "Got %d entries from file\n", nEntries);

  w = (double *) Malloc((2*M+1) * sizeof(double));

  switch(wType)
  {
    case W_HAMMING:
      for(k = -M ; k <= M ; k++)
        w[M+k] = 0.54 + 0.46 * cos((2 * M_PI * k) / (2 * M + 1));
    break;
    case W_HANN:
      for(k = -M ; k <= M ; k++)
        w[M+k] = 0.5 * (1 + cos((2 * M_PI * k) / (2 * M + 1)));
    break;
    case W_BLACKMAN:
      for(k = -M ; k <= M ; k++)
        w[M+k] = 0.42 + 0.5 * cos((2 * M_PI * k) / (2 * M + 1)) +
	0.08 * cos((4 * M_PI * k) / (2 * M + 1));
    break;
    case W_RECTANGULAR:
      for(k = -M ; k <= M ; k++)
        w[M+k] = 1;
    break;
  }

  if(reverse == 1)
  {
    for(n = nEntries - 1 ; n >= 0 ; n--)
      if(n % (drop + 1) == 0)
      {
        if(p1 == 0)
        {
          printf("%d\t%.3f\n", entries[nEntries - n - 1].position,
	  CalcMean(entries, nEntries, n, M, w));
        }
        else
        {
          printf("%.3f\n", CalcMean(entries, nEntries, n, M, w));
        }
      }
  }
  else
    for(n = 0 ; n < nEntries ; n++)
      if(n % (drop + 1) == 0)
      {
        if(p1 == 0)
        {
          printf("%d\t%.3f\n", entries[n].position, CalcMean(entries, nEntries, 
          n, M, w));
        }
        else
        {
          printf("%.3f\n", CalcMean(entries, nEntries, n, M, w));
        }
      }

  return 0;
}
