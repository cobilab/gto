#!/bin/bash
#
# ==============================================================================
# |                                                                            |
# |             THIS PROGRAM FINDS AND LOCALIZES A MOTIF WITH GTO              |
# |             =================================================              |
# |                                                                            |
# |                  ./gto_find_motif.sh <motif> sequence.fa                   |
# |                                                                            |
# |                     FILE NEEDED TO THE COMPUTATION:                        |
# |                                                                            |
# |                     $1: MOTIF IN SEQUENCE FORMAT (ACGT)                    |
# |                     $2: SEQUENCE FILE IN FASTA FORMAT                      |
# |                                                                            |
# ==============================================================================
#
# ==============================================================================
# ================================ DEFINITIONS =================================
#
GET_GTO=0;
ENLARGE=1000;
WINDOW=10;
RUN_COMPARISON=1;
PARAM=" -rm 13:20:1:0:0.9/3:1:0.94 ";
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
# =============================== RUN COMPARISON ===============================
#
if [[ "$RUN_COMPARISON" -eq "1" ]];
  then
  #
  echo "$1" > motif.seq;
  gto_fasta_rand_extra_chars < $2 | gto_fasta_to_seq > sequence.seq;
  #
  gto_geco -v -e $PARAM -r motif.seq sequence.seq;
  #
  gto_real_to_binary_with_threshold -t 1.5 < sequence.seq.iae | tr -d -c "01" > sequence.bin
  gto_fasta_variation_filter -v -w $WINDOW -u 5 -t 0.5 sequence.bin
  gto_fasta_variation_visual -e $ENLARGE sequence.bin.seg
  #
  fi
#
# ==============================================================================
# ==============================================================================
