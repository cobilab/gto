#include <string.h>
#include "parser.h"
#include "mem.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// CREATE PARSER
//
PARSER *CreateParser(void){
  PARSER *PA = (PARSER *) Calloc(1, sizeof(PARSER));
  PA->sym    = 0;
  PA->type   = 0;
  PA->header = 0;
  PA->line   = 0;
  PA->nRead  = 0;
  PA->dna    = 0;
  return PA;
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// FILE TYPE
//
void FileType(PARSER *PA, FILE *IN){
  rewind(IN);
  PA->sym = fgetc(IN);
    switch(PA->sym){
    case '>': PA->type = 1; break;
    case '@': PA->type = 2; break;
    default : PA->type = 0;
    }
  rewind(IN);
  } 

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// FILTER BASES 6 POLITICS
//
int FBasesPol(int b){
  switch(b){
    case 'A': return 'A';
    case 'C': return 'C';
    case 'G': return 'G';
    case 'T': return 'T';
    case 'U': return 'T';
    case 'a': return 'A';
    case 'c': return 'C';
    case 'g': return 'G';
    case 't': return 'T';
    default: return -1;
    }
  return -1;
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// FILTER BASES 6 POLITICS SPECIFIC TO CONSIDER N's
//
int FBasesPolN(int b){
  switch(b){
    case 'A': return 'A';
    case 'C': return 'C';
    case 'G': return 'G';
    case 'T': return 'T';
    case 'U': return 'T';
    case 'a': return 'A';
    case 'c': return 'C';
    case 'g': return 'G';
    case 't': return 'T';
    case 'n': return 'N';
    case 'N': return 'N';
    default: return -1;
    }
  return -1;
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// PARSE SYM
//
int32_t ParseSym(PARSER *PA, uint8_t sym){

  switch(PA->type){
    // IS A FASTA ">" FILE
    case 1:
      switch(sym){
        case '>':  PA->header = 1; return -1;
        case '\n': PA->header = 0; return -1;
        default:   if(PA->header==1) return -1;
        }
    break;

    // IS A FASTQ "@" FILE
    case 2:
      switch(PA->line){
        case 0: if(sym == '\n'){ PA->line = 1; PA->dna = 1; } break;
        case 1: if(sym == '\n'){ PA->line = 2; PA->dna = 0; } break;
        case 2: if(sym == '\n'){ PA->line = 3; PA->dna = 0; } break;
        case 3: if(sym == '\n'){ PA->line = 0; PA->dna = 0; } break;
        }
      if(PA->dna == 0 || sym == '\n') return -1;
    break;

    // OTHER (SUCH AS DNA SEQ)
    default: ; // DO NOTHING
    }

  return FBasesPol(sym);
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// PARSE SYM
//
int32_t ParseSymN(PARSER *PA, uint8_t sym){

  switch(PA->type){
    // IS A FASTA ">" FILE
    case 1:
      switch(sym){
        case '>':  PA->header = 1; return -1;
        case '\n': PA->header = 0; return -1;
        default:   if(PA->header==1) return -1;
        }
    break;

    // IS A FASTQ "@" FILE
    case 2:
      switch(PA->line){
        case 0: if(sym == '\n'){ PA->line = 1; PA->dna = 1; } break;
        case 1: if(sym == '\n'){ PA->line = 2; PA->dna = 0; } break;
        case 2: if(sym == '\n'){ PA->line = 3; PA->dna = 0; } break;
        case 3: if(sym == '\n'){ PA->line = 0; PA->dna = 0; } break;
        }
      if(PA->dna == 0 || sym == '\n') return -1;
    break;

    // OTHER (SUCH AS DNA SEQ)
    default: ; // DO NOTHING
    }

  return FBasesPolN(sym);
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// PARSE MULTI-FASTA
//
int32_t ParseMF(PARSER *PA, uint8_t sym){

  switch(sym){
    case '>':
      PA->header = 1;
      ++PA->nRead;
      return -1;
    case '\n':
      if(PA->header == 0){
        PA->header = 0;
        return -99;
        }
      else{
        PA->header = 0;
        return -2;
        }
    default:
      if(PA->header == 1)
        return -3;
    }

  return (FBasesPol(sym) == -1 ? -99 : sym);
  }


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// REMOVE PARSER
//
void RemoveParser(PARSER *PA){
  free(PA);
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
