#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "defs.h"
#include "misc.h"
#include "mem.h"
#include "dna.h"
#include "csmodel.h"
#include "buffer.h"
#include "argparse.h"
#include <unistd.h>

#define DEF_CMORDER 8
#define MIN_CMORDER 1
#define MAX_CMORDER 20
#define MEM_INDEX   ((uint64_t)1<<20)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//  quickSort
//
//  This public-domain C implementation by Darel Rex Finley.
//  quickSort(&myArray[0],5); // sorts elements 0, 1, 2, 3, and 4
//  quickSort(&myArray[3],5); // sorts elements 3, 4, 5, 6, and 7
void QuickSort(int *arr, int elements)
{
  #define  MAX_LEVELS  300
  int piv, beg[MAX_LEVELS], end[MAX_LEVELS], i = 0, L, R, swap;
  beg[0] = 0; 
  end[0] = elements;

  while(i >=0){
    L = beg[i]; 
    R = end[i]-1;
    if(L < R){
      piv = arr[L];
      while(L < R){
        while (arr[R] >= piv && L < R) R--; 
        if(L < R) arr[L++] = arr[R];
        while (arr[L] <= piv && L < R) L++; 
        if(L < R) arr[R--] = arr[L]; 
        }
      arr[L] = piv; beg[i+1] = L+1; end[i+1] = end[i]; end[i++] = L;
      if(end[i]-beg[i] > end[i-1]-beg[i-1]){
        swap = beg[i]; beg[i] = beg[i-1]; beg[i-1] = swap;
        swap = end[i]; end[i] = end[i-1]; end[i-1] = swap; 
        }
      } 
    else{
      --i; 
      }
    }
  }

/*
 * This application agroups reads and creates an index file.
 * It cluster reads in therms of Seq k-mer Lexicographical order.
 */
int main(int argc, char *argv[])
{
  uint32_t k, i, p = 0, ctx;
  uint8_t  s, line = 0;
  BUF      *B;
  CSMODEL  *M;
  uint64_t *X, *Y;
  uint64_t size = MEM_INDEX, nReads = 0;
  ctx = DEF_CMORDER;

  char *programName = argv[0];
  struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_INTEGER('c', "ctx", &ctx, ""),
        OPT_BUFF('<', "input.fastq", "Input FASTQ file format (stdin)"),
        OPT_BUFF('>', "output.fastq", "Output FASTQ file format (stdout)"),
        OPT_END(),
  };
  struct argparse argparse;

  char usage[250] = "\nExample: "; 
  strcat(usage, programName);
  strcat(usage, " -c <ctx> < input.fastq > output.fastq\n");

  argparse_init(&argparse, options, NULL, programName, 0);
  argparse_describe(&argparse, "\nIt agroups reads and creates an index file.\n"
    "It cluster reads in therms of Seq k-mer Lexicographical order\n", usage);
  argc = argparse_parse(&argparse, argc, argv);

  if(argc != 0 || isatty(STDIN_FILENO))
    argparse_help_cb(&argparse, options);

  if(ctx < MIN_CMORDER || ctx > MAX_CMORDER)
  {
    fprintf(stderr, "\nERROR: The ctx values was set improperly!\n");
    argparse_help_cb(&argparse, options);
    exit(1);
  }

  B   = CreateBuffer(BUF_SIZE);
  X   = (uint64_t *) Calloc(size,  sizeof(uint64_t));
  Y   = (uint64_t *) Calloc(size,  sizeof(uint64_t));
  M   = CreateCSModel(ctx, 4);
  uint8_t *buf = (uint8_t *) Calloc((ctx+2), sizeof(uint8_t));

  while((k = fread(B->buf, 1, B->size, stdin)))
    for(i = 0 ; i < k ; ++i)
    {
      s = B->buf[i];
      switch(line)
      { 
        case 0: 
          if(s == '\n') 
          { 
            line = 1; 
            p = 0; 
          }
        break;
        case 1:
          // DNA SEQ HERE: //COMPLEMENTAR BINARY MODEL TO ENCODE INDEXES
          if(s == '\n') 
            line = 2;
          else 
            if(s == 'N') 
              break;
            else 
              if(p < ctx) 
                buf[p++] = S2N(s);
            
          if(p == ctx)
            X[nReads] = GetCSIdx(buf+p, M);
        break;
        case 2:
          if(s == '\n') 
            line = 3;
        break;
        case 3:
          if(s == '\n')
          { 
            line = 0;
            if(++nReads == size)
            {
              X = (uint64_t *) Realloc(X, (size+=MEM_INDEX) * sizeof(uint64_t),
                  MEM_INDEX * sizeof(uint64_t));
              Y = (uint64_t *) Realloc(Y, (size+=MEM_INDEX) * sizeof(uint64_t),
                  MEM_INDEX * sizeof(uint64_t));
            }
          }
        break;
      } 
    }

  Free(buf, (ctx+2) * sizeof(uint8_t));
  DeleteCSModel(M);
  Free(X, size * sizeof(uint64_t));
  Free(Y, size * sizeof(uint64_t));
  RemoveBuffer(B); 
  return EXIT_SUCCESS;
}