#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "defs.h"
#include "misc.h"
#include "mem.h"
#include "reads.h"
#include "buffer.h"
#include "argparse.h"
#include <unistd.h>

#define ESCAPE 127

/* 
 * This application unpacks the FASTQ reads packaged using the gto_fastq_pack tool.
 */
int main(int argc, char *argv[])
{
  uint8_t value, scores = 0;
  uint32_t index, streamSize, position = 0, line = 0;
  BUF  *B = CreateBuffer(BUF_SIZE);
  Read *R = CreateRead(65536+GUARD, 65535+GUARD);

  char *programName = argv[0];
  struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_BUFF('<', "input.fastqpack", "Input packaged FASTQ file format (stdin)"),
        OPT_BUFF('>', "output.fastq", "Output FASTQ file format (stdout)"),
        OPT_GROUP("Optional"),
        OPT_BOOLEAN('s', "scores", &scores, "When active, the application show the scores first"),
        OPT_END(),
  };
  struct argparse argparse;

  char usage[250] = "\nExample: "; 
  strcat(usage, programName);
  strcat(usage, " -s < input.fastqpack > output.fastq\n");

  argparse_init(&argparse, options, NULL, programName, 0);
  argparse_describe(&argparse, "\nIt unpacks the FASTQ reads packaged using the gto_fastq_pack tool.", usage);
  argc = argparse_parse(&argparse, argc, argv);

  if(argc != 0 || isatty(STDIN_FILENO))
    argparse_help_cb(&argparse, options);

  if(scores == 0)
  {
    while((streamSize = fread(B->buf, 1, B->size, stdin)))
      for(index = 0 ; index < streamSize ; ++index)
      {
        value = B->buf[index];
        switch(line)
        {
          case 0: 
            if(value == ESCAPE || value == '\n')
            {
              R->bases[position++] = '\n';
              R->bases[position]   = '\0';
              position  = 0;
              line = 1;
              break;
            }
            else
              R->bases[position++] = value;
          break;       

          case 1:  
            if(value == ESCAPE || value == '\n')
            {
              R->scores[position++] = '\n';
              R->scores[position]   = '\0';
              position  = 0;
              line = 2;
              break;
            }
            else
              R->scores[position++] = value;
          break;
  
          case 2:        
            if(value == ESCAPE || value == '\n')
            {
              R->header1[position++] = '\n';
              R->header1[position]   = '\0';
              position  = 0;
              line = 3;
              break;
            }
            else
              R->header1[position++] = value;
          break;

          case 3:        
            if(value == ESCAPE || value == '\n')
            {
              R->header2[position++] = '\n';
              R->header2[position]   = '\0';
              position  = 0;
              line = 4;
              fprintf(stdout, "@%s", R->header1);
              fprintf(stdout, "%s",  R->bases);
              fprintf(stdout, "%s",  R->header2);
              fprintf(stdout, "%s",  R->scores);
              break;
            }
            else
              R->header2[position++] = value;
          break;

          case 4:
            if(value == '\n')
            {
              position  = 0;
              line = 0;
              break;
            }
          break;
        }
      }
  }
  else
  {
    while((streamSize = fread(B->buf, 1, B->size, stdin)))
      for(index = 0 ; index < streamSize ; ++index)
      {
        value = B->buf[index];
        switch(line)
        {
          case 1:
            if(value == ESCAPE || value == '\n')
            {
              R->bases[position++] = '\n';
              R->bases[position]   = '\0';
              position  = 0;
              line = 2;
              break;
            }
            else
              R->bases[position++] = value;
          break;

          case 0:
            if(value == ESCAPE || value == '\n')
            {
              R->scores[position++] = '\n';
              R->scores[position]   = '\0';
              position  = 0;
              line = 1;
              break;
            }
            else
              R->scores[position++] = value;
          break;

          case 2:
            if(value == ESCAPE || value == '\n')
            {
              R->header1[position++] = '\n';
              R->header1[position]   = '\0';
              position  = 0;
              line = 3;
              break;
            }
            else
              R->header1[position++] = value;
          break;

          case 3:
            if(value == ESCAPE || value == '\n')
            {
              R->header2[position++] = '\n';
              R->header2[position]   = '\0';
              position  = 0;
              line = 4;
              fprintf(stdout, "@%s", R->header1);
              fprintf(stdout, "%s",  R->bases);
              fprintf(stdout, "%s",  R->header2);
              fprintf(stdout, "%s",  R->scores);
              break;
            }
            else
              R->header2[position++] = value;
          break;

          case 4:
            if(value == '\n')
            {
              position  = 0;
              line = 0;
              break;
            }
          break;
        }
      }
  }

  FreeRead(R);
  RemoveBuffer(B);
  return EXIT_SUCCESS;
}