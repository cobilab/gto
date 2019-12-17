#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"
#include "misc.h"
#include "mem.h"
#include "buffer.h"
#include "argparse.h"
#include "parser.h"

char TranslateCodon(char *codon)
  {
  if(!strcmp(codon, "ATA")) { return 'I';}
  else if(!strcmp(codon, "ATC")) { return 'I';}
  else if(!strcmp(codon, "ATT")) { return 'I';}
  else if(!strcmp(codon, "ATG")) { return 'M';}
  else if(!strcmp(codon, "ACA")) { return 'T';}
  else if(!strcmp(codon, "ACC")) { return 'T';}
  else if(!strcmp(codon, "ACG")) { return 'T';}
  else if(!strcmp(codon, "ACT")) { return 'T';}
  else if(!strcmp(codon, "AAC")) { return 'N';}
  else if(!strcmp(codon, "AAT")) { return 'N';}
  else if(!strcmp(codon, "AAA")) { return 'K';}
  else if(!strcmp(codon, "AAG")) { return 'K';}
  else if(!strcmp(codon, "AGC")) { return 'S';}
  else if(!strcmp(codon, "AGT")) { return 'S';}
  else if(!strcmp(codon, "AGA")) { return 'R';}
  else if(!strcmp(codon, "AGG")) { return 'R';}
  else if(!strcmp(codon, "CTA")) { return 'L';}
  else if(!strcmp(codon, "CTC")) { return 'L';}
  else if(!strcmp(codon, "CTG")) { return 'L';}
  else if(!strcmp(codon, "CTT")) { return 'L';}
  else if(!strcmp(codon, "CCA")) { return 'P';}
  else if(!strcmp(codon, "CCC")) { return 'P';}
  else if(!strcmp(codon, "CCG")) { return 'P';}
  else if(!strcmp(codon, "CCT")) { return 'P';}
  else if(!strcmp(codon, "CAC")) { return 'H';}
  else if(!strcmp(codon, "CAT")) { return 'H';}
  else if(!strcmp(codon, "CAA")) { return 'Q';}
  else if(!strcmp(codon, "CAG")) { return 'Q';}
  else if(!strcmp(codon, "CGA")) { return 'R';}
  else if(!strcmp(codon, "CGC")) { return 'R';}
  else if(!strcmp(codon, "CGG")) { return 'R';}
  else if(!strcmp(codon, "CGT")) { return 'R';}
  else if(!strcmp(codon, "GTA")) { return 'V';}
  else if(!strcmp(codon, "GTC")) { return 'V';}
  else if(!strcmp(codon, "GTG")) { return 'V';}
  else if(!strcmp(codon, "GTT")) { return 'V';}
  else if(!strcmp(codon, "GCA")) { return 'A';}
  else if(!strcmp(codon, "GCC")) { return 'A';}
  else if(!strcmp(codon, "GCG")) { return 'A';}
  else if(!strcmp(codon, "GCT")) { return 'A';}
  else if(!strcmp(codon, "GAC")) { return 'D';}
  else if(!strcmp(codon, "GAT")) { return 'D';}
  else if(!strcmp(codon, "GAA")) { return 'E';}
  else if(!strcmp(codon, "GAG")) { return 'E';}
  else if(!strcmp(codon, "GGA")) { return 'G';}
  else if(!strcmp(codon, "GGC")) { return 'G';}
  else if(!strcmp(codon, "GGG")) { return 'G';}
  else if(!strcmp(codon, "GGT")) { return 'G';}
  else if(!strcmp(codon, "TCA")) { return 'S';}
  else if(!strcmp(codon, "TCC")) { return 'S';}
  else if(!strcmp(codon, "TCG")) { return 'S';}
  else if(!strcmp(codon, "TCT")) { return 'S';}
  else if(!strcmp(codon, "TTC")) { return 'F';}
  else if(!strcmp(codon, "TTT")) { return 'F';}
  else if(!strcmp(codon, "TTA")) { return 'L';}
  else if(!strcmp(codon, "TTG")) { return 'L';}
  else if(!strcmp(codon, "TAC")) { return 'Y';}
  else if(!strcmp(codon, "TAT")) { return 'Y';}
  else if(!strcmp(codon, "TAA")) { return '-';}
  else if(!strcmp(codon, "TAG")) { return '-';}
  else if(!strcmp(codon, "TGC")) { return 'C';}
  else if(!strcmp(codon, "TGT")) { return 'C';}
  else if(!strcmp(codon, "TGA")) { return '-';}
  else if(!strcmp(codon, "TGG")) { return 'W';}

  return '*';
  }

/*
 * This application converts FASTA or Multi-FASTA file format in amino acid sequences (translation).
 */
int main(int argc, char *argv[])
{
  uint32_t streamSize, index, frame=1;
  uint8_t  value, header = 1;
  PARSER *Parser = CreateParser();
  BUF *Buffer;

  char *programName = argv[0];
  struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_BUFF('<', "input.mfasta", "Input FASTA or Multi-FASTA file format (stdin)"),
        OPT_BUFF('>', "output.prot", "Output amino acid sequence file (stdout)"),
        OPT_GROUP("Optional"),
        OPT_INTEGER('f', "frame", &frame, "Translation codon frame (1, 2 or 3)"),
        OPT_END(),
  };
  struct argparse argparse;

  char usage[250] = "\nExample: "; 
  strcat(usage, programName);
  strcat(usage, " < input.mfasta > output.prot\n");

  argparse_init(&argparse, options, NULL, programName, 0);
  argparse_describe(&argparse, "\nIt converts FASTA or Multi-FASTA file format to an amino acid sequence (translation).", usage);
  argc = argparse_parse(&argparse, argc, argv);

  if(argc != 0 || ftell(stdin))
    argparse_help_cb(&argparse, options);  

  if(frame < 1 || frame > 3)
  {
    fprintf(stderr, "\nERROR: The codon frame value most be 1, 2 or 3!\n");
    argparse_help_cb(&argparse, options);
    exit(1);
  }

  FileType(Parser, stdin);
  if(Parser->type != 1)
  {
    fprintf(stderr, "ERROR: This is not a FASTA file!\n");
    exit(1);
  }
  
  Buffer = CreateBuffer(BUF_SIZE);

  uint8_t i = 0;
  char codon[4];
  codon[3] = '\0';
  int32_t tempFrame = frame;

  while((streamSize = fread(Buffer->buf, 1, Buffer->size, stdin)))
  {
    for(index = 0 ; index < streamSize ; ++index)
    {
      value = Buffer->buf[index];
      if(value == '>'){ 
        header = 1; 
        i = 0;
        tempFrame = frame;
        continue; 
      }
      if(value == '\n' && header == 1){ header = 0; continue; }
      if(value == '\n') continue;
      if(header == 1) continue;
      if(value < 65 || value > 122) continue;

      if (--tempFrame > 0)
        continue;
      
      switch(value)
      {
        case 'U': case 'u': case 't':
      	value = 'T';
      	break;
      	case 'c':
      	value = 'C';
        break;
      	case 'g':
      	value = 'G';
      	break;
      	case 'a':
      	value = 'A';
      	break;
      }

      codon[i] = value;

      if(++i == 3)
      {
        fprintf(stdout, "%c", TranslateCodon(codon));
        i = 0;
      }
    }
  }

  RemoveBuffer(Buffer); 
  return EXIT_SUCCESS;
}

