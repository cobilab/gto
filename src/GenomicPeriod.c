#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#include "fcm.h"
#include "dna.h"
#include "misc.h"
#include "mem.h"
#include "buffer.h"
#include "argparse.h"

/*
 * This application calculates the best order depth of a sequence, using FCMs.
 * It only works "ACGT", while the rest will be discarded.
 */
int main(int argc, char *argv[])
{
  uint32_t k, i, order = 1, max = 20;
  uint8_t  s;
  uint64_t info[2][max];
  BUF      *B;
  CBUF     *CB;
  FCM      *Fcm;
  FILE     *PLOT = popen("gnuplot -p", "w");

  char *programName = argv[0];
  struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_BUFF('<', "input.seq", "Input sequence file format (stdin)"),
        OPT_BUFF('>', "output", "Output is given by log_2(4)*K(x)/|x|) (stdout)"),
        OPT_END(),
  };
  struct argparse argparse;

  char usage[250] = "\nExample: "; 
  strcat(usage, programName);
  strcat(usage, " < input.seq > output\n");

  argparse_init(&argparse, options, NULL, programName, 0);
  argparse_describe(&argparse, "\nIt calculates the best order depth of a sequence, using FCMs."
                            "It only works \"ACGT\", while the rest will be discarded.", usage);
  argc = argparse_parse(&argparse, argc, argv);

  if(argc != 0 || ftell(stdin))
    argparse_help_cb(&argparse, options);

  // SEQUENCE
  for(order = 1 ; order <= max ; ++order)
  {
    fprintf(stderr, "Running order: %u ... ", order);
    rewind(stdin);
    info[0][order] = 0;
    info[1][order] = 0;
    B   = CreateBuffer (BUF_SIZE);
    CB  = CreateCBuffer(BUF_SIZE, GUARD);
    Fcm = Create4DnaFCM(order, 1, 0, 4);

    while((k = fread(B->buf, 1, B->size, stdin)))
      for(i = 0 ; i < k ; ++i)
      {
        s = B->buf[i];
        if(s == 'A' || s == 'C' || s == 'G' || s == 'T')
        {
          s = S2N(s);
          CB->buf[CB->idx] = s;
          GetIdx4Dna(CB->buf+CB->idx-1, Fcm);
          Compute4DnaFCM(Fcm);
          info[0][order] += CompProbs(Fcm, s);
          info[1][order]++;
          Update4DnaFCM(Fcm, s, 0);
          UpdateCBuffer(CB);
        }
      }

    fprintf(stderr, "Done!\n");
    RemoveBuffer (B);
    RemoveCBuffer(CB);
    Free4DnaModel(Fcm);
  }
  
  fprintf(PLOT, "plot '-' with lines\n");
  for(order = 1 ; order <= max ; ++order)
  {
    fprintf(stdout, "%2u\t%.4g\n", order, (double) (2 * info[0][order]) /
    info[1][order]); 
    fprintf(PLOT,   "%2u\t%.4g\n", order, (double) (2 * info[0][order]) /
    info[1][order]); 
  }

  fprintf(PLOT, "e\n");
  fflush(PLOT);
  fclose(PLOT);

  return EXIT_SUCCESS;
}