#============================================================================#
#                     GTO, IEETA/DETI, UNIVERSITY OF AVEIRO                  #
#============================================================================#
BIN    		= ../bin/
CC     		= gcc
CPLP   		= -ffast-math -msse2 #fgnu89-inline 
#-----------------------------------------------------------------------------
CFLAGS 		= -O3 -Wall $(CPLP)
#-----------------------------------------------------------------------------
LIBS   		= -lm
DEPS   		= defs.h
PROGS  	 	= $(BIN)/gto \
         	  $(BIN)/gto_fastq_to_fasta \
         	  $(BIN)/gto_fastq_to_mfasta \
         	  $(BIN)/gto_fasta_to_seq \
         	  $(BIN)/gto_seq_to_fasta \
         	  $(BIN)/gto_seq_to_fastq \

OBJS     	= argparse.o buffer.o mem.o misc.o parser.o
#-----------------------------------------------------------------------------
all:
	$(MAKE) progs
progs: $(PROGS)
$(BIN)/gto: GTO.c $(DEPS) $(OBJS) 
	$(CC) $(CFLAGS) -o $(BIN)/gto GTO.c $(OBJS) $(LIBS)
$(BIN)/gto_fastq_to_fasta: FastqToFasta.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_fastq_to_fasta FastqToFasta.c $(OBJS) $(LIBS)
$(BIN)/gto_fastq_to_mfasta: FastqToMFasta.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_fastq_to_mfasta FastqToMFasta.c $(OBJS) $(LIBS)
$(BIN)/gto_fasta_to_seq: FastaToSeq.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_fasta_to_seq FastaToSeq.c $(OBJS) $(LIBS)
$(BIN)/gto_seq_to_fasta: SeqToFasta.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_seq_to_fasta SeqToFasta.c $(OBJS) $(LIBS)
$(BIN)/gto_seq_to_fastq: SeqToFastq.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_seq_to_fastq SeqToFastq.c $(OBJS) $(LIBS)

argparse.o: argparse.c argparse.h $(DEPS)
	$(CC) -c $(CFLAGS) argparse.c
mem.o: mem.c mem.h $(DEPS)
	$(CC) -c $(CFLAGS) mem.c
misc.o: misc.c misc.h $(DEPS)
	$(CC) -c $(CFLAGS) misc.c
buffer.o: buffer.c buffer.h $(DEPS)
	$(CC) -c $(CFLAGS) buffer.c
parser.o: parser.c parser.h $(DEPS)
	$(CC) -c $(CFLAGS) parser.c

##############################################################################
clean: 
	/bin/rm -f *.o
cleanall:
	/bin/rm -f *.o $(PROGS)
##############################################################################
