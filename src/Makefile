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
         	  $(BIN)/gto_fasta_from_seq \
         	  $(BIN)/gto_fastq_from_seq \
			  $(BIN)/gto_char_to_line \
			  $(BIN)/gto_amino_acid_to_group \
              $(BIN)/gto_fasta_extract_read_by_pattern \
         	  $(BIN)/gto_fasta_extract \
         	  $(BIN)/gto_fasta_extract_by_read \
              $(BIN)/gto_fasta_info \
              $(BIN)/gto_fastq_exclude_N \
	          $(BIN)/gto_fastq_extract_quality_scores \
	          $(BIN)/gto_fastq_info \
	          $(BIN)/gto_fastq_maximum_read_size \
	          $(BIN)/gto_fastq_minimum_read_size \
	          $(BIN)/gto_fastq_minimum_quality_score \
	          $(BIN)/gto_fasta_find_n_pos \
              $(BIN)/gto_genomic_gen_random_dna \
	          $(BIN)/gto_fasta_mutate \
	          $(BIN)/gto_fastq_mutate \
              $(BIN)/gto_new_line_on_new_x \
			  $(BIN)/gto_amino_acid_to_pseudo_dna \
	          $(BIN)/gto_fasta_rand_extra_chars \
	          $(BIN)/gto_fastq_rand_extra_chars \
	          $(BIN)/gto_genomic_rand_seq_extra_chars \
	          $(BIN)/gto_fasta_rename_human_headers \
              $(BIN)/gto_reverse \
	          $(BIN)/gto_fasta_split_reads \
	          $(BIN)/gto_fastq_split \
	          $(BIN)/gto_fastq_pack \
	          $(BIN)/gto_fastq_unpack \
	          $(BIN)/gto_upper_bound\
	          $(BIN)/gto_lower_bound
	         
	          

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
$(BIN)/gto_fasta_from_seq: FastaFromSeq.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_fasta_from_seq FastaFromSeq.c $(OBJS) $(LIBS)
$(BIN)/gto_fastq_from_seq: FastqFromSeq.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_fastq_from_seq FastqFromSeq.c $(OBJS) $(LIBS)
$(BIN)/gto_char_to_line: CharToLine.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_char_to_line CharToLine.c $(OBJS) $(LIBS)
$(BIN)/gto_amino_acid_to_group: AminoAcidToGroup.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_amino_acid_to_group AminoAcidToGroup.c $(OBJS) $(LIBS)
$(BIN)/gto_fasta_extract_read_by_pattern: FastaExtractReadByIdPattern.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_fasta_extract_read_by_pattern FastaExtractReadByIdPattern.c $(OBJS) $(LIBS)
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
$(BIN)/gto_fasta_find_n_pos: FastaFindNPos.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_fasta_find_n_pos FastaFindNPos.c $(OBJS) $(LIBS)
$(BIN)/gto_genomic_gen_random_dna: GenomicGenRandomDNA.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_genomic_gen_random_dna GenomicGenRandomDNA.c $(OBJS) $(LIBS)
$(BIN)/gto_fasta_mutate: FastaMutate.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_fasta_mutate FastaMutate.c $(OBJS) $(LIBS)
$(BIN)/gto_fastq_mutate: FastqMutate.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_fastq_mutate FastqMutate.c $(OBJS) $(LIBS)
$(BIN)/gto_new_line_on_new_x: NewLineForNewValue.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_new_line_on_new_x NewLineForNewValue.c $(OBJS) $(LIBS)
$(BIN)/gto_amino_acid_to_pseudo_dna: AminoAcidToPseudoDNA.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_amino_acid_to_pseudo_dna AminoAcidToPseudoDNA.c $(OBJS) $(LIBS)
$(BIN)/gto_fasta_rand_extra_chars: FastaRandExtraChars.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_fasta_rand_extra_chars FastaRandExtraChars.c $(OBJS) $(LIBS)
$(BIN)/gto_fastq_rand_extra_chars: FastqRandExtraChars.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_fastq_rand_extra_chars FastqRandExtraChars.c $(OBJS) $(LIBS)
$(BIN)/gto_genomic_rand_seq_extra_chars: GenomicRandSeqExtraChars.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_genomic_rand_seq_extra_chars GenomicRandSeqExtraChars.c $(OBJS) $(LIBS)
$(BIN)/gto_fasta_rename_human_headers: FastaRenameHumanHeaders.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_fasta_rename_human_headers FastaRenameHumanHeaders.c $(OBJS) $(LIBS)
$(BIN)/gto_reverse: Reverse.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_reverse Reverse.c $(OBJS) $(LIBS)
$(BIN)/gto_fasta_split_reads: FastaSplitReads.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_fasta_split_reads FastaSplitReads.c $(OBJS) $(LIBS)	
$(BIN)/gto_fastq_split: FastqSplit.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_fastq_split FastqSplit.c $(OBJS) $(LIBS)	
$(BIN)/gto_fastq_pack: FastqPack.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_fastq_pack FastqPack.c $(OBJS) $(LIBS)
$(BIN)/gto_fastq_unpack: FastqUnpack.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_fastq_unpack FastqUnpack.c $(OBJS) $(LIBS)
$(BIN)/gto_upper_bound: UpperBound.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_upper_bound UpperBound.c $(OBJS) $(LIBS)
$(BIN)/gto_lower_bound: LowerBound.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_lower_bound LowerBound.c $(OBJS) $(LIBS)


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
