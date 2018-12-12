#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "defs.h"
#include "misc.h"
#include "mem.h"
#include "reads.h"
#include "args.h"

void PrintArgs(char *name){
  
  // SE - SINGLE ENDED FASTQ
  // PE - PAIRED ENDED FASTQ : FORWARD READ vs REVERSE READ
  // 
  //
  // TODO:
  //
  // PAIRED ENDED FILE -> INVERT FOR
  // 
  // REMOVE ADAPTORS

  fprintf(stderr, "Usage: %s [OPTIONS] < input > output             \n"
                  "                                                 \n"
                  "  -n <int>       Maximum number of \"N\" in read,\n"
                  "  -m <int>       Minimum size of the read,       \n"
                  "  -a <int>       Discard read below average QS,  \n"
                  "                                                 \n"
                  "  -k <int>       Window size (sw) to filter QS,  \n"
                  "  -w <int>       Minimum average QS with k-sw.   \n"
                  "                                                 \n",
  name);
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int main(int argc, char *argv[]){

  Read *Read = CreateRead(65536+GUARD, 65535+GUARD);
  uint32_t seqSize = 0, totalQS = 0, N = 0, x, n;
  uint64_t okReads = 0, totalReads = 0;

  if(ArgBin(0, argv, argc, "-h") || ArgBin(0, argv, argc, "?")){
    PrintArgs(argv[0]);
    return EXIT_SUCCESS;
    }
  
  int max_n         = ArgNum(0,  argv, argc, "-n", 0, 9999999);
  int k             = ArgNum(5,  argv, argc, "-k", 0, 9999999);
  int min_QS_window = ArgNum(25, argv, argc, "-w", 0, 9999999);
  int min_avg_qs    = ArgNum(25, argv, argc, "-a", 0, 9999999);
  int min_read_size = ArgNum(35, argv, argc, "-m", 0, 9999999);
 
  // LOAD PARAMETERS
 
  while(GetRead(stdin, Read)){

    seqSize = strlen((char *) Read->bases) - 1;
    totalQS = 0;
    N       = 0;

    for(x = 0 ; x < seqSize ; ++x){
      if(Read->bases[x] == 'N'){
        ++N;
        }
      totalQS += ((int) Read->scores[x]) - 33; // PHRED +33

      if(x < seqSize - k){
        int tmp_QS = 0;
        for(n = 0 ; n < k ; ++n)
          tmp_QS += ((int) Read->scores[x + n]) - 33;
        if(tmp_QS / k < min_QS_window)
          break;
        }
      }

    ++totalReads;

    // EVALUATE TO DISCARD:
    if(N > max_n)                        continue;
    if((totalQS / seqSize) < min_avg_qs) continue;
    if(x < min_read_size)                continue;


    // PRINT READ
    for(n = 0 ; n < strlen((char *) Read->header1) ; ++n)
      fprintf(stdout, "%c", Read->header1[n]);
    for(n = 0 ; n < x ; ++n)
      fprintf(stdout, "%c", Read->bases[n]);
    fprintf(stdout, "\n+\n");
    for(n = 0 ; n < x ; ++n)
      fprintf(stdout, "%c", Read->scores[n]);
    fprintf(stdout, "\n");

    ++okReads;
    }

  fprintf(stderr, "Total reads    : %"PRIu64"\n", totalReads);
  fprintf(stderr, "Filtered reads : %"PRIu64"\n", totalReads-okReads);

  FreeRead(Read);
  return EXIT_SUCCESS;
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


