#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include <ctype.h>
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/uio.h>
#include <sys/mman.h>
#include "mem.h"
#include "defs.h"
#include "parser.h"
#include "buffer.h"
#include "common.h"
#include "argparse.h"

/*
 * This application counts the number of bases in sequence, FASTA or FASTQ files.
 */
int main(int argc, char *argv[])
{
  uint64_t nBases = 0, info[6] = {0, 0, 0, 0, 0, 0};
  char     type[4][20] = {"DNA", "FASTA", "FASTQ", "UNKNOWN"};
  uint8_t  sym, *buf;
  struct   stat s;
  size_t   size, streamSize;
  long     fd=0;

  char *programName = argv[0];
  struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_BUFF('<', "input", "Input sequence, FASTA or FASTQ file format (stdin)"),
        OPT_BUFF('>', "output", "Output read information (stdout)"),
        OPT_END(),
  };
  struct argparse argparse;

  char usage[350] = "\nExample: "; 
  strcat(usage, programName);
  strcat(usage, " < input.seq > output\n"
    "\nOutput example :\n"
    "File type        : value\n"
    "Number of bases  : value\n"
    "Number of a/A    : value\n"
    "Number of c/C    : value\n"
    "Number of g/G    : value\n"
    "Number of t/T    : value\n"
    "Number of n/N    : value\n"
    "Number of others : value\n");

  argparse_init(&argparse, options, NULL, programName, 0);
  argparse_describe(&argparse, "\nIt counts the number of bases in sequence, FASTA or FASTQ files.", usage);
  argc = argparse_parse(&argparse, argc, argv);

  if(argc != 0)
    argparse_help_cb(&argparse, options);

  PARSER   *Parser = CreateParser();
  FileType(Parser, stdin);
  fstat(fd, &s);
  size = s.st_size;
  
  #if defined(OSX)
    // OSX doesnt have a MAP_POPULATE flag
    #define MAP_FLAGS MAP_PRIVATE
  #else
    #define MAP_FLAGS MAP_PRIVATE|MAP_POPULATE
  #endif
  buf = (uint8_t *) mmap(0, size, PROT_READ, MAP_FLAGS, fd, 0);
  #undef MAP_FLAGS

  madvise(buf, s.st_size, MADV_SEQUENTIAL);
  for(streamSize = 0 ; streamSize < size ; ++streamSize)
  {
    if(ParseSym(Parser, (sym = *buf++)) == -1)
      continue; 
    info[DNASymToNum(sym)]++;
    ++nBases;
  }

  fprintf(stdout, "File type        : %s\n", type[Parser->type]);
  fprintf(stdout, "Number of bases  : %"PRIu64"\n", nBases);
  fprintf(stdout, "Number of a/A    : %"PRIu64"\n", info[0]);
  fprintf(stdout, "Number of c/C    : %"PRIu64"\n", info[1]);
  fprintf(stdout, "Number of g/G    : %"PRIu64"\n", info[2]);
  fprintf(stdout, "Number of t/T    : %"PRIu64"\n", info[3]);
  fprintf(stdout, "Number of n/N    : %"PRIu64"\n", info[4]);
  fprintf(stdout, "Number of others : %"PRIu64"\n", info[5]);

  RemoveParser(Parser);
  close(fd);

  return EXIT_SUCCESS;
}