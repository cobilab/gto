#!/bin/bash
# ==============================================================================
# |                                                                            |
# |             THIS PROGRAM INFERS METAGENOMIC COMPOSITION W/ GTO             |
# |             ==================================================             |
# |                                                                            |
# |              ./gto_metagenomics.sh reads1.fq reads2.fq VDB.fa              |
# |                                                                            |
# |                     FILE NEEDED TO THE COMPUTATION:                        |
# |                                                                            |
# |                 $3: FILE WITH THE DATABASE IN FASTA FORMAT                 |
# |                 $2: FILE WITH THE READS #2 IN FASTQ FORMAT                 |
# |                 $1: FILE WITH THE READS #1 IN FASTQ FORMAT                 |
# |                                                                            |
# ==============================================================================
#
# ==============================================================================
# ================================ DEFINITIONS =================================
#
GET_GTO=0;
RUN_COMPARISON=1;
CREATE_DATABASE=0;
#
# ==============================================================================
# ================================== GET GTO ===================================
#
if [[ "$GET_GTO" -eq "1" ]];
  then
  conda install -c cobilab gto --yes
  fi
#
# ==============================================================================
# =============================== CREATE DATABASE ==============================
#
if [[ "$CREATE_DATABASE" -eq "1" ]];
  then
  gto_build_dbs.sh -vi
  fi
#
# ==============================================================================
# =============================== RUN COMPARISON ===============================
#
if [[ "$RUN_COMPARISON" -eq "1" ]];
  then
  #
  gto_fastq_minimum_local_quality_score_forward -k 5 -w 25 -m 33 < $1 \
  | gto_fastq_exclude_n -m 5 \
  | gto_fastq_minimum_read_size -s 30 > filt-$1
  #
  gto_fastq_minimum_local_quality_score_forward -k 5 -w 25 -m 33 < $2 \
  | gto_fastq_exclude_n -m 5 \
  | gto_fastq_minimum_read_size -s 30 > filt-$2
  #
  gto_fastq_metagenomics -F -t 200 -v -n 8 filt-$1:filt-$2 $3
  #
  fi
#
# ==============================================================================
# ==============================================================================
