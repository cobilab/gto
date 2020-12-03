#============================================================================#
#                     GTO, IEETA/DETI, UNIVERSITY OF AVEIRO                  #
#============================================================================#

# Detect OS and add the os as #define C macro
# https://gist.github.com/sighingnow/deee806603ec9274fd47

OSFLAG :=
ifeq ($(OS),Windows_NT)
	OSFLAG += -D WIN32
	ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
		OSFLAG += -D AMD64
	endif
	ifeq ($(PROCESSOR_ARCHITECTURE),x86)
		OSFLAG += -D IA32
	endif
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		OSFLAG += -D LINUX
	endif
	ifeq ($(UNAME_S),Darwin)
		OSFLAG += -D OSX
	endif
		UNAME_P := $(shell uname -p)
	ifeq ($(UNAME_P),x86_64)
		OSFLAG += -D AMD64
	endif
	ifneq ($(filter %86,$(UNAME_P)),)
		OSFLAG += -D IA32
	endif
	ifneq ($(filter arm%,$(UNAME_P)),)
		OSFLAG += -D ARM
	endif
endif

BIN    		= ../bin/
CC     		= gcc
CPLP   		= -ffast-math -msse2 #fgnu89-inline 
#-----------------------------------------------------------------------------
CFLAGS 		= -O3 -Wall $(CPLP) $(OSFLAG)
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
              $(BIN)/gto_fastq_exclude_n \
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
              $(BIN)/gto_genomic_reverse \
              $(BIN)/gto_reverse \
	          $(BIN)/gto_fasta_split_reads \
	          $(BIN)/gto_fastq_split \
	          $(BIN)/gto_fastq_pack \
	          $(BIN)/gto_fastq_unpack \
	          $(BIN)/gto_upper_bound \
	          $(BIN)/gto_lower_bound \
	          $(BIN)/gto_fastq_quality_score_info \
	          $(BIN)/gto_fastq_quality_score_min \
	          $(BIN)/gto_fastq_quality_score_max \
	          $(BIN)/gto_fastq_cut \
	          $(BIN)/gto_fastq_minimum_local_quality_score_forward \
	          $(BIN)/gto_fastq_minimum_local_quality_score_reverse \
	          $(BIN)/gto_genomic_dna_mutate \
	          $(BIN)/gto_genomic_extract \
	          $(BIN)/gto_brute_force_string \
	          $(BIN)/gto_real_to_binary_with_threshold \
	          $(BIN)/gto_sum \
	          $(BIN)/gto_filter \
	          $(BIN)/gto_word_search \
	          $(BIN)/gto_permute_by_blocks \
	          $(BIN)/gto_fasta_extract_pattern_coords \
	          $(BIN)/gto_info \
	          $(BIN)/gto_segment \
	          $(BIN)/gto_fasta_get_unique \
	          $(BIN)/gto_genomic_period \
	          $(BIN)/gto_comparative_map \
	          $(BIN)/gto_genomic_count_bases \
	          $(BIN)/gto_max \
	          $(BIN)/gto_min \
         	  $(BIN)/gto_fastq_complement \
         	  $(BIN)/gto_fasta_complement \
         	  $(BIN)/gto_genomic_complement \
         	  $(BIN)/gto_fastq_reverse \
         	  $(BIN)/gto_fasta_reverse \
         	  $(BIN)/gto_amino_acid_from_fasta \
         	  $(BIN)/gto_amino_acid_from_fastq \
         	  $(BIN)/gto_amino_acid_from_seq \
         	  $(BIN)/gto_fasta_split_streams \
         	  $(BIN)/gto_fasta_merge_streams 
         	  #$(BIN)/gto_amino_acid_to_seq 
	         
	          

OBJS     	= argparse.o csmodel.o buffer.o mem.o misc.o parser.o reads.o \
			  labels.o common.o dna.o fcm.o phash.o 

OBJSCMAP    = common-cmap.o mem-cmap.o msg-cmap.o paint-cmap.o time-cmap.o
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
$(BIN)/gto_fastq_exclude_n: FastqExcludeN.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_fastq_exclude_n FastqExcludeN.c $(OBJS) $(LIBS)
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
$(BIN)/gto_genomic_reverse: Reverse.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_genomic_reverse Reverse.c $(OBJS) $(LIBS)
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
$(BIN)/gto_fastq_quality_score_info: FastqQualityScoreInfo.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_fastq_quality_score_info FastqQualityScoreInfo.c $(OBJS) $(LIBS)
$(BIN)/gto_fastq_quality_score_min: FastqQualityScoreMin.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_fastq_quality_score_min FastqQualityScoreMin.c $(OBJS) $(LIBS)
$(BIN)/gto_fastq_quality_score_max: FastqQualityScoreMax.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_fastq_quality_score_max FastqQualityScoreMax.c $(OBJS) $(LIBS)
$(BIN)/gto_fastq_cut: FastqCut.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_fastq_cut FastqCut.c $(OBJS) $(LIBS)
$(BIN)/gto_fastq_minimum_local_quality_score_forward: FastqMinimumQualityScoreForward.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_fastq_minimum_local_quality_score_forward FastqMinimumQualityScoreForward.c $(OBJS) $(LIBS)
$(BIN)/gto_fastq_minimum_local_quality_score_reverse: FastqMinimumQualityScoreReverse.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_fastq_minimum_local_quality_score_reverse FastqMinimumQualityScoreReverse.c $(OBJS) $(LIBS)
$(BIN)/gto_genomic_dna_mutate: GenomicDNAMutate.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_genomic_dna_mutate GenomicDNAMutate.c $(OBJS) $(LIBS)
$(BIN)/gto_genomic_extract: GenomicExtract.c $(DEPS) $(OBJS) 
	$(CC) $(CFLAGS) -o $(BIN)/gto_genomic_extract GenomicExtract.c $(OBJS) $(LIBS)
$(BIN)/gto_brute_force_string: BruteForceString.c $(DEPS) $(OBJS) 
	$(CC) $(CFLAGS) -o $(BIN)/gto_brute_force_string BruteForceString.c $(OBJS) $(LIBS)
$(BIN)/gto_real_to_binary_with_threshold: RealToBinaryWithThreshold.c $(DEPS) $(OBJS) 
	$(CC) $(CFLAGS) -o $(BIN)/gto_real_to_binary_with_threshold RealToBinaryWithThreshold.c $(OBJS) $(LIBS)
$(BIN)/gto_sum: Sum.c $(DEPS) $(OBJS) 
	$(CC) $(CFLAGS) -o $(BIN)/gto_sum Sum.c $(OBJS) $(LIBS)
$(BIN)/gto_filter: Filter.c $(DEPS) $(OBJS) 
	$(CC) $(CFLAGS) -o $(BIN)/gto_filter Filter.c $(OBJS) $(LIBS)
$(BIN)/gto_word_search: WordSearch.c $(DEPS) $(OBJS) 
	$(CC) $(CFLAGS) -o $(BIN)/gto_word_search WordSearch.c $(OBJS) $(LIBS)
$(BIN)/gto_permute_by_blocks: PermuteByBlocks.c $(DEPS) $(OBJS) 
	$(CC) $(CFLAGS) -o $(BIN)/gto_permute_by_blocks PermuteByBlocks.c $(OBJS) $(LIBS)
$(BIN)/gto_fasta_extract_pattern_coords: FastaExtractPatternCoords.c $(DEPS) $(OBJS) 
	$(CC) $(CFLAGS) -o $(BIN)/gto_fasta_extract_pattern_coords FastaExtractPatternCoords.c $(OBJS) $(LIBS)
$(BIN)/gto_info: Info.c $(DEPS) $(OBJS) 
	$(CC) $(CFLAGS) -o $(BIN)/gto_info Info.c $(OBJS) $(LIBS)
$(BIN)/gto_segment: Segment.c $(DEPS) $(OBJS) 
	$(CC) $(CFLAGS) -o $(BIN)/gto_segment Segment.c $(OBJS) $(LIBS)
$(BIN)/gto_fasta_get_unique: FastaGetUnique.c $(DEPS) $(OBJS) 
	$(CC) $(CFLAGS) -o $(BIN)/gto_fasta_get_unique FastaGetUnique.c $(OBJS) $(LIBS)
$(BIN)/gto_genomic_period: GenomicPeriod.c $(DEPS) $(OBJS) 
	$(CC) $(CFLAGS) -o $(BIN)/gto_genomic_period GenomicPeriod.c $(OBJS) $(LIBS)
$(BIN)/gto_comparative_map: ComparativeMap.c $(DEPSCMAP) $(OBJSCMAP)
	$(CC) $(CFLAGS) -o $(BIN)/gto_comparative_map ComparativeMap.c $(OBJSCMAP) $(LIBS)
$(BIN)/gto_genomic_count_bases: GenomicCountBases.c $(DEPS) $(OBJS) 
	$(CC) $(CFLAGS) -o $(BIN)/gto_genomic_count_bases GenomicCountBases.c $(OBJS) $(LIBS)
$(BIN)/gto_max: Max.c $(DEPS) $(OBJS) 
	$(CC) $(CFLAGS) -o $(BIN)/gto_max Max.c $(OBJS) $(LIBS)
$(BIN)/gto_min: Min.c $(DEPS) $(OBJS) 
	$(CC) $(CFLAGS) -o $(BIN)/gto_min Min.c $(OBJS) $(LIBS)
$(BIN)/gto_fastq_complement: FastqComplement.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_fastq_complement FastqComplement.c $(OBJS) $(LIBS)
$(BIN)/gto_fasta_complement: FastaComplement.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_fasta_complement FastaComplement.c $(OBJS) $(LIBS)
$(BIN)/gto_genomic_complement: GenomicComplement.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_genomic_complement GenomicComplement.c $(OBJS) $(LIBS)
$(BIN)/gto_fastq_reverse: FastqReverse.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_fastq_reverse FastqReverse.c $(OBJS) $(LIBS)
$(BIN)/gto_fasta_reverse: FastaReverse.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_fasta_reverse FastaReverse.c $(OBJS) $(LIBS)
$(BIN)/gto_amino_acid_from_fasta: AminoAcidFromFasta.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_amino_acid_from_fasta AminoAcidFromFasta.c $(OBJS) $(LIBS)
$(BIN)/gto_amino_acid_from_fastq: AminoAcidFromFastq.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_amino_acid_from_fastq AminoAcidFromFastq.c $(OBJS) $(LIBS)
$(BIN)/gto_amino_acid_from_seq: AminoAcidFromSeq.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_amino_acid_from_seq AminoAcidFromSeq.c $(OBJS) $(LIBS)
$(BIN)/gto_fasta_split_streams: FastaSplitStreams.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_fasta_split_streams FastaSplitStreams.c $(OBJS) $(LIBS)
$(BIN)/gto_fasta_merge_streams: FastaMergeStreams.c $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/gto_fasta_merge_streams FastaMergeStreams.c $(OBJS) $(LIBS)

#$(BIN)/gto_amino_acid_to_seq: AminoAcidToSeq.c $(DEPS) $(OBJS)
#	$(CC) $(CFLAGS) -o $(BIN)/gto_amino_acid_to_seq AminoAcidToSeq.c $(OBJS) $(LIBS)

geco:
	git clone https://github.com/cobilab/geco2.git
	mv geco2/src/Makefile.linux geco2/src/Makefile 
	cd geco2/src && make
	cp geco2/src/GeCo2 $(BIN)/gto_geco
	cp geco2/src/GeDe2 $(BIN)/gto_gede
	mv geco2/src/GeCo2 $(BIN)/gto_genomic_compressor
	mv geco2/src/GeDe2 $(BIN)/gto_genomic_decompressor
	rm -rf geco2

xs:
	git clone https://github.com/pratas/xs.git
	cd xs && make
	mv xs/XS $(BIN)/gto_fastq_xs
	rm -rf xs

ac:
	git clone https://github.com/cobilab/ac.git
	mv ac/src/Makefile.linux ac/src/Makefile
	cd ac/src/ && make
	mv ac/src/AC $(BIN)/gto_amino_acid_compressor
	mv ac/src/AD $(BIN)/gto_amino_acid_decompressor
	rm -rf ac

falcon:
	git clone https://github.com/cobilab/falcon.git
	cd falcon/src/ && cmake . && make
	mv falcon/src/FALCON $(BIN)/gto_fastq_metagenomics
	rm -rf falcon

chester:
	git clone https://github.com/cobilab/chester.git
	cd chester/src/ && cmake . && make
	cp chester/src/CHESTER-map $(BIN)/gto_fasta_variation_map 
	cp chester/src/CHESTER-filter $(BIN)/gto_fasta_variation_filter
	cp chester/src/CHESTER-visual $(BIN)/gto_fasta_variation_visual
	cp chester/src/CHESTER-map $(BIN)/gto_fastq_variation_map 
	cp chester/src/CHESTER-filter $(BIN)/gto_fastq_variation_filter
	cp chester/src/CHESTER-visual $(BIN)/gto_fastq_variation_visual
	cp chester/src/CHESTER-map $(BIN)/gto_genomic_variation_map 
	cp chester/src/CHESTER-filter $(BIN)/gto_genomic_variation_filter
	cp chester/src/CHESTER-visual $(BIN)/gto_genomic_variation_visual
	rm -rf chester

fastp:
	git clone https://github.com/OpenGene/fastp.git
	cd fastp && make
	cp fastp/fastp $(BIN)/gto_external_fastp
	rm -rf fastp

copmem:
	git clone https://github.com/wbieniec/copmem.git
	cd copmem && make all
	cp copmem/copmem $(BIN)/gto_external_copmem
	cp copmem/memoryfill $(BIN)/gto_external_memoryfill
	rm -rf copmem

bfmem:
	git clone https://github.com/yuansliu/bfmem.git
	cd bfmem && make
	cp bfmem/bfmem $(BIN)/gto_external_bfmem
	cp bfmem/compareMEM $(BIN)/gto_external_compareMEM
	cp bfmem/formatconvert $(BIN)/gto_external_formatconvert
	rm -rf bfmem

qvz:
	git clone https://github.com/mikelhernaez/qvz.git
	cd qvz && make
	cp qvz/bin/qvz $(BIN)/gto_external_qvz
	rm -rf qvz

minicom:
	git clone https://github.com/yuansliu/minicom.git
	cd minicom && sh install.sh
	cp minicom/minicom $(BIN)/gto_external_minicom
	rm -rf minicom

spring:
	git clone https://github.com/shubhamchandak94/Spring.git
	cd Spring && mkdir build && cd build && cmake .. && make
	cp Spring/build/spring $(BIN)/gto_external_spring
	rm -rf Spring

externalProgs: 
	make geco xs ac falcon chester fastp copmem bfmem qvz minicom spring

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
labels.o: labels.c labels.h $(DEPS)
	$(CC) -c $(CFLAGS) labels.c
dna.o: dna.c dna.h $(DEPS)
	$(CC) -c $(CFLAGS) dna.c
fcm.o: fcm.c fcm.h $(DEPS)
	$(CC) -c $(CFLAGS) fcm.c
phash.o: phash.c phash.h $(DEPS)
	$(CC) -c $(CFLAGS) phash.c
csmodel.o: csmodel.c csmodel.h $(DEPS)
	$(CC) -c $(CFLAGS) csmodel.c

common-cmap.o: common-cmap.c common-cmap.h $(DEPSCMAP)
	$(CC) -c $(CFLAGS) common-cmap.c
mem-cmap.o: mem-cmap.c mem-cmap.h $(DEPSCMAP)
	$(CC) -c $(CFLAGS) mem-cmap.c
msg-cmap.o: msg-cmap.c msg-cmap.h $(DEPSCMAP)
	$(CC) -c $(CFLAGS) msg-cmap.c
paint-cmap.o: paint-cmap.c paint-cmap.h $(DEPSCMAP)
	$(CC) -c $(CFLAGS) paint-cmap.c
time-cmap.o: time-cmap.c time-cmap.h $(DEPSCMAP)
	$(CC) -c $(CFLAGS) time-cmap.c


##############################################################################
clean: 
	/bin/rm -f *.o
cleanall:
	/bin/rm -f *.o $(PROGS)
##############################################################################
