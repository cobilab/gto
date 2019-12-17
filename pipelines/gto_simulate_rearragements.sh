#!/bin/bash
#
# ==============================================================================
# |                                                                            |
# |             THIS PROGRAM SIMULATES GENOME REARRANGEMENTS W GTO             |
# |             ==================================================             |
# |                                                                            |
# |                 ./simulate_rearragements.sh db.fa reads.fq                 |
# |                                                                            |
# |                      OUTPUT: A.fa , OUTPUT2: B.fa                          |
# |                                                                            |
# ==============================================================================
#
# ==============================================================================
# ================================ DEFINITIONS =================================
#
gto_genomic_gen_random_dna -s 0   -n 1000 > A.g
gto_genomic_gen_random_dna -s 7   -n 1000 > B.g
gto_genomic_gen_random_dna -s 11  -n 1000 > C.g
gto_genomic_gen_random_dna -s 63  -n 1000 > D.g
gto_genomic_gen_random_dna -s 102 -n 1000 > E.g
#
cat A.g B.g C.g D.g E.g | gto_fasta_from_seq -n A > A.fa
#
gto_genomic_reverse < B.g | gto_genomic_complement > R_B.g
gto_genomic_reverse < D.g | gto_genomic_complement > R_D.g
#
cat A.g R_B.g C.g R_D.g E.g > ALL.g
#
gto_permute_by_blocks -b 500 -s 0 < ALL.g | gto_fasta_from_seq -n B > B.fa
#
# ==============================================================================
# ==============================================================================
