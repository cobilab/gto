#!/bin/bash
#
echo "Downloading data ...";
efetch -db nucleotide -format fasta -id "AY386330.1" > B19.fa
efetch -db nucleotide -format fasta -id "JN561323.2" > HV2.fa
efetch -db nucleotide -format fasta -id "X04370.1"   > HV3.fa
efetch -db nucleotide -format fasta -id "MT007544"   > SARS2.fa
efetch -db nucleotide -format fasta -id "AB041963.1" > TTV.fa
efetch -db nucleotide -format fasta -id "MG921180.1" > HPV.fa
efetch -db nucleotide -format fasta -id "NC_012920.1" > MT.fa
#
# SUBSTITUTIONS
echo "Applying SNPs ...";
gto_fasta_mutate -e 0.01 < MT.fa  > MT_1.fa
gto_fasta_mutate -e 0.01 < B19.fa > B19_1.fa
gto_fasta_mutate -e 0.05 < TTV.fa > TTV_5.fa
gto_fasta_mutate -e 0.05 < HPV.fa > HPV_5.fa
#
# PERMUTATIONS
echo "Applying permutations ...";
gto_permute_by_blocks -b 500 -s 0 < B19.fa > B19_P.fa
gto_permute_by_blocks -b 300 -s 0 < HPV_5.fa > HPV_5_P.fa
gto_permute_by_blocks -b 100 -s 0 < HV2.fa > HV2_P.fa
#
echo "Simulating trash dna ...";
gto_genomic_gen_random_dna -n 300000 -s 0 | gto_fasta_from_seq -l 100 > trash.fa
#
echo "Joinning data ...";
cat trash.fa MT_1.fa B19_P.fa HPV_5_P.fa B19_1.fa TTV_5.fa SARS2.fa HV3.fa > data.fa
#
echo "Simulating reads ...";
art_illumina -ss HS25 -sam -i data.fa -p -l 150 -f 30 -m 200 -s 10 -o reads 1>> art_info
#
