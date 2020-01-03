#!/bin/bash
#
efetch -db nucleotide -format fasta -id "AY386330.1" > B19.fa
efetch -db nucleotide -format fasta -id "DQ279927.1" > HV1.fa
efetch -db nucleotide -format fasta -id "JN561323.2" > HV2.fa
efetch -db nucleotide -format fasta -id "X04370.1"   > HV3.fa
efetch -db nucleotide -format fasta -id "DQ279927.1" > HV4.fa
efetch -db nucleotide -format fasta -id "X69198.1"   > VARV.fa
efetch -db nucleotide -format fasta -id "AB041963.1" > TTV.fa
efetch -db nucleotide -format fasta -id "MG921180.1" > HPV.fa
# SUBSTITUTIONS
gto_fasta_mutate -e 0.01 < B19.fa > B19_1.fa
gto_fasta_mutate -e 0.05 < HV1.fa > HV5_5.fa
gto_fasta_mutate -e 0.05 < TTV.fa > TTV_5.fa
gto_fasta_mutate -e 0.05 < HPV.fa > HPV_5.fa
gto_fasta_mutate -e 0.10 < HV1.fa > HV1_10.fa
#
# PERMUTATIONS
gto_permute_by_blocks -b 500 -s 0 < B19.fa > B19_P.fa
gto_permute_by_blocks -b 300 -s 0 < HV4.fa > HV4_P.fa
gto_permute_by_blocks -b 300 -s 0 < HPV_5.fa > HPV_5_P.fa
gto_permute_by_blocks -b 100 -s 0 < HV2.fa > HV2_P.fa
#
gto_genomic_gen_random_dna -n 500000 -s 0 | gto_fasta_from_seq -l 100 > trash.fa
#
cat trash.fa B19_P.fa HPV_5_P.fa B19_1.fa HV4_P.fa TTV_5.fa HV5_5.fa B19_1.fa HV3.fa HV2_P.fa HV1.fa > data.fa
#
art_illumina -ss HS25 -sam -i data.fa -p -l 150 -f 30 -m 200 -s 10 -o reads
#
# gto_build_dbs.sh -vi
#
