#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

int main(int argc, char *argv[]){
  fprintf(stdout, "\n  GTO - THE GENOMICS TOOLKIT v%u.%u, UNIVERSITY OF AVEIRO\n",
  VERSION, RELEASE);
  fprintf(stdout, "  A toolkit for DNA sequences analysis and manipulation\n\n");
  fprintf(stdout, "  Sub-programs:\n\n");
  fprintf(stdout, 
  "  GTO-Fastq2Fasta\n");
  fprintf(stdout, "\n");
  return EXIT_SUCCESS;
  }

