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
			  $(BIN)/gto_char_to_line \
			  $(BIN)/gto_amino_acid_to_group \
              $(BIN)/gto_extract_read_by_pattern \
         	  $(BIN)/gto_fasta_extract \
         	  $(BIN)/gto_fasta_extract_by_read \
              $(BIN)/gto_fasta_info \
              $(BIN)/gto_fastq_exclude_N \
	          $(BIN)/gto_fastq_extract_quality_scores \
	          $(BIN)/gto_fastq_info \
	          $(BIN)/gto_fastq_maximum_read_size \
	          $(BIN)/gto_fastq_minimum_read_size \
	          $(BIN)/gto_fastq_minimum_quality_score \
	          $(BIN)/gto_find_n_pos \
              $(BIN)/gto_gen_random_dna \
	          $(BIN)/gto_mutate_fasta \
	          $(BIN)/gto_mutate_fastq \
              $(BIN)/gto_new_line_on_new_x \
			  $(BIN)/gto_protein_to_pseudo_dna \
	          $(BIN)/gto_rand_fasta_extra_chars \
	          $(BIN)/gto_rand_fastq_extra_chars \
	          $(BIN)/gto_rand_seq_extra_chars \
	          $(BIN)/gto_rename_human_headers \
              $(BIN)/gto_reverse \
	          $(BIN)/gto_split_reads \
	         
	          

OBJS     	= argparse.o buffer.o mem.o misc.o parser.o reads.o
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
$(BIN)/gto_char_to_line: CharToLine.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_char_to_line CharToLine.c $(OBJS) $(LIBS)
$(BIN)/gto_amino_acid_to_group: AminoAcidToGroup.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_amino_acid_to_group AminoAcidToGroup.c $(OBJS) $(LIBS)
$(BIN)/gto_extract_read_by_pattern: ExtractFastaReadByIdPattern.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_extract_read_by_pattern ExtractFastaReadByIdPattern.c $(OBJS) $(LIBS)
$(BIN)/gto_fasta_extract: FastaExtract.c $(DEPS) $(OBJS) 
	$(CC) $(CFLAGS) -o $(BIN)/gto_fasta_extract FastaExtract.c $(OBJS) $(LIBS)
$(BIN)/gto_fasta_extract_by_read: FastaExtractByRead.c $(DEPS) $(OBJS) 
	$(CC) $(CFLAGS) -o $(BIN)/gto_fasta_extract_by_read FastaExtractByRead.c $(OBJS) $(LIBS)
$(BIN)/gto_fasta_info: FastaInfo.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_fasta_info FastaInfo.c $(OBJS) $(LIBS)
$(BIN)/gto_fastq_exclude_N: FastqExcludeN.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_fastq_exclude_N FastqExcludeN.c $(OBJS) $(LIBS)
$(BIN)/gto_fastq_extract_quality_scores: FastqExtractQS.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_fastq_extract_quality_scores FastqExtractQS.c $(OBJS) $(LIBS)
$(BIN)/gto_fastq_info: FastqInfo.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_fastq_info FastqInfo.c $(OBJS) $(LIBS)
$(BIN)/gto_fastq_maximum_read_size: FastqMaximumReadSize.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_fastq_maximum_read_size FastqMaximumReadSize.c $(OBJS) $(LIBS)
$(BIN)/gto_fastq_minimum_read_size: FastqMinimumReadSize.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_fastq_minimum_read_size FastqMinimumReadSize.c $(OBJS) $(LIBS)
$(BIN)/gto_fastq_minimum_quality_score: FastqMinimumQualityScore.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_fastq_minimum_quality_score FastqMinimumQualityScore.c $(OBJS) $(LIBS)
$(BIN)/gto_find_n_pos: FindNPos.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_find_n_pos FindNPos.c $(OBJS) $(LIBS)
$(BIN)/gto_gen_random_dna: GenRandomDNA.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_gen_random_dna GenRandomDNA.c $(OBJS) $(LIBS)
$(BIN)/gto_mutate_fasta: MutateFasta.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_mutate_fasta MutateFasta.c $(OBJS) $(LIBS)
$(BIN)/gto_mutate_fastq: MutateFastq.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_mutate_fastq MutateFastq.c $(OBJS) $(LIBS)
$(BIN)/gto_new_line_on_new_x: NewLineForNewValue.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_new_line_on_new_x NewLineForNewValue.c $(OBJS) $(LIBS)
$(BIN)/gto_protein_to_pseudo_dna: ProteinToPseudoDNA.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_protein_to_pseudo_dna ProteinToPseudoDNA.c $(OBJS) $(LIBS)
$(BIN)/gto_rand_fasta_extra_chars: RandFastaExtraChars.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_rand_fasta_extra_chars RandFastaExtraChars.c $(OBJS) $(LIBS)
$(BIN)/gto_rand_fastq_extra_chars: RandFastqExtraChars.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_rand_fastq_extra_chars RandFastqExtraChars.c $(OBJS) $(LIBS)
$(BIN)/gto_rand_seq_extra_chars: RandSeqExtraChars.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_rand_seq_extra_chars RandSeqExtraChars.c $(OBJS) $(LIBS)
$(BIN)/gto_rename_human_headers: RenameMFasta.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_rename_human_headers RenameMFasta.c $(OBJS) $(LIBS)
$(BIN)/gto_reverse: Reverse.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_reverse Reverse.c $(OBJS) $(LIBS)
$(BIN)/gto_split_reads: SplitReads.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_split_reads SplitReads.c $(OBJS) $(LIBS)	


argparse.o: argparse.c argparse.h $(DEPS)
	$(CC) -c $(CFLAGS) argparse.c
mem.o: mem.c mem.h $(DEPS)
	$(CC) -c $(CFLAGS) mem.c
misc.o: misc.c misc.h $(DEPS)
	$(CC) -c $(CFLAGS) misc.c
buffer.o: buffer.c buffer.h $(DEPS)
	$(CC) -c $(CFLAGS) buffer.c
reads.o: reads.c reads.h $(DEPS)
	$(CC) -c $(CFLAGS) reads.c
parser.o: parser.c parser.h $(DEPS)
	$(CC) -c $(CFLAGS) parser.c

##############################################################################
clean: 
	/bin/rm -f *.o
cleanall:
	/bin/rm -f *.o $(PROGS)
##############################################################################
