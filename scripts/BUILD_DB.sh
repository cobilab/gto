#!/bin/bash
#
# ==============================================================================
#
#   IT DOWNLOADS AND COMPRESSES THE COMPLETE GENOMIC SEQUENCES FROM THE 
#   NCBI DATABASE THAT ARE LABELLED AS "COMPLETE GENOME" OR "CHROMOSOME".
#
#   THE OUTPUT FILES ARE:
#
#   => VDB.fa.gz  (VIRAL)
#   => BDB.fa.gz  (BACTERIA)
#   => ADB.fa.gz  (ARCHAEA)
#   => PDB.fa.gz  (PROTOZOA)
#   => FDB.fa.gz  (FUNGI)
#   => TDB.fa.gz  (PLANT)
#   => IDB.fa.gz  (INVERTEBRATE)
#   => VMDB.fa.gz (VERTEBRATE MAMMALIAN)
#   => VODB.fa.gz (VERTEBRATE OTHER)
# 
# ==============================================================================
# NUMBER OF THREADS USED FOR DOWNLOAD
#
THREADS=8;
#
# ==============================================================================
# ONLY FLAGS WITH '1' WILL BE PROCESSED 
#
BUILD_VIRAL=1;
BUILD_BACTERIA=1;
BUILD_ARCHAEA=1;
BUILD_PROTOZOA=1;
BUILD_FUNGI=1;
BUILD_PLANT=1;
BUILD_INVER=1;
BUILD_VER_MAM=1;
BUILD_VER_OTH=1;
#
# ==============================================================================
# VIRAL DB
#
if [[ "$BUILD_VIRAL" -eq "1" ]];
  then
  rm -f assembly_summary.txt;
  wget ftp://ftp.ncbi.nlm.nih.gov/genomes/genbank/viral/assembly_summary.txt
  awk -F '\t' '{if($12=="Complete Genome"||$12=="Chromosome") print $20}' assembly_summary.txt > ASCG.txt
  mkdir -p GB_DB_VIRAL/
  rm -f GB_DB_VIRAL/*.fa.gz
  cat ASCG.txt | xargs -I{} -n1 -P$THREADS wget -P GB_DB_VIRAL {}/*_genomic.fna.gz
  mkdir -p GB_DB_VIRAL_CDS/
  mkdir -p GB_DB_VIRAL_RNA/
  rm -f GB_DB_VIRAL_CDS/*.fa.gz
  rm -f GB_DB_VIRAL_RNA/*.fa.gz
  mv GB_DB_VIRAL/*_cds_from_genomic.fna.gz GB_DB_VIRAL_CDS/
  mv GB_DB_VIRAL/*_rna_from_genomic.fna.gz GB_DB_VIRAL_RNA/
  rm -f VDB.fa.gz;
  zcat GB_DB_VIRAL/*.fna.gz | gzip -9 > VDB.fa.gz
  fi
#
# ==============================================================================
# BACTERIA DB
#
if [[ "$BUILD_BACTERIA" -eq "1" ]];
  then
  rm -f assembly_summary.txt;
  wget ftp://ftp.ncbi.nlm.nih.gov/genomes/genbank/bacteria/assembly_summary.txt
  awk -F '\t' '{if($12=="Complete Genome"||$12=="Chromosome") print $20}' assembly_summary.txt > ASCG.txt
  mkdir -p GB_DB_BACTERIA/
  rm -f GB_DB_BACTERIA/*.fa.gz
  cat ASCG.txt | xargs -I{} -n1 -P$THREADS wget -P GB_DB_BACTERIA {}/*_genomic.fna.gz
  mkdir -p GB_DB_BACTERIA_CDS/
  mkdir -p GB_DB_BACTERIA_RNA/
  rm -f GB_DB_BACTERIA_CDS/*.fa.gz
  rm -f GB_DB_BACTERIA_RNA/*.fa.gz
  mv GB_DB_BACTERIA/*_cds_from_genomic.fna.gz GB_DB_BACTERIA_CDS/
  mv GB_DB_BACTERIA/*_rna_from_genomic.fna.gz GB_DB_BACTERIA_RNA/
  rm -f BDB.fa.gz;
  zcat GB_DB_BACTERIA/*.fna.gz | gzip -9 > BDB.fa.gz
  fi
#
# ==============================================================================
# ARCHAEA DB
#
if [[ "$BUILD_ARCHAEA" -eq "1" ]];
  then
  rm -f assembly_summary.txt;
  wget ftp://ftp.ncbi.nlm.nih.gov/genomes/genbank/archaea/assembly_summary.txt
  awk -F '\t' '{if($12=="Complete Genome"||$12=="Chromosome") print $20}' assembly_summary.txt > ASCG.txt
  mkdir -p GB_DB_ARCHAEA/
  rm -f GB_DB_ARCHAEA/*.fa.gz
  cat ASCG.txt | xargs -I{} -n1 -P$THREADS wget -P GB_DB_ARCHAEA {}/*_genomic.fna.gz
  mkdir -p GB_DB_ARCHAEA_CDS/
  mkdir -p GB_DB_ARCHAEA_RNA/
  rm -f GB_DB_ARCHAEA_CDS/*.fa.gz
  rm -f GB_DB_ARCHAEA_RNA/*.fa.gz
  mv GB_DB_ARCHAEA/*_cds_from_genomic.fna.gz GB_DB_ARCHAEA_CDS/
  mv GB_DB_ARCHAEA/*_rna_from_genomic.fna.gz GB_DB_ARCHAEA_RNA/
  rm -f ADB.fa.gz;
  zcat GB_DB_ARCHAEA/*.fna.gz | gzip -9 > ADB.fa.gz
  fi
#
# ==============================================================================
# PROTOZOA DB
#
if [[ "$BUILD_PROTOZOA" -eq "1" ]];
  then
  rm -f assembly_summary.txt;
  wget ftp://ftp.ncbi.nlm.nih.gov/genomes/genbank/protozoa/assembly_summary.txt
  awk -F '\t' '{if($12=="Complete Genome"||$12=="Chromosome") print $20}' assembly_summary.txt > ASCG.txt
  mkdir -p GB_DB_PROTOZOA/
  rm -f GB_DB_PROTOZOA/*.fa.gz
  cat ASCG.txt | xargs -I{} -n1 -P$THREADS wget -P GB_DB_PROTOZOA {}/*_genomic.fna.gz
  mkdir -p GB_DB_PROTOZOA_CDS/
  mkdir -p GB_DB_PROTOZOA_RNA/
  rm -f GB_DB_PROTOZOA_CDS/*.fa.gz
  rm -f GB_DB_PROTOZOA_RNA/*.fa.gz
  mv GB_DB_PROTOZOA/*_cds_from_genomic.fna.gz GB_DB_PROTOZOA_CDS/
  mv GB_DB_PROTOZOA/*_rna_from_genomic.fna.gz GB_DB_PROTOZOA_RNA/
  rm -f PDB.fa.gz;
  zcat GB_DB_PROTOZOA/*.fna.gz | gzip -9 > PDB.fa.gz
  fi
#
# ==============================================================================
# FUNGI DB
#
if [[ "$BUILD_FUNGI" -eq "1" ]];
  then
  rm -f assembly_summary.txt;
  wget ftp://ftp.ncbi.nlm.nih.gov/genomes/genbank/fungi/assembly_summary.txt
  awk -F '\t' '{if($12=="Complete Genome"||$12=="Chromosome") print $20}' assembly_summary.txt > ASCG.txt
  mkdir -p GB_DB_FUNGI/
  rm -f GB_DB_FUNGI/*.fa.gz
  cat ASCG.txt | xargs -I{} -n1 -P$THREADS wget -P GB_DB_FUNGI {}/*_genomic.fna.gz
  mkdir -p GB_DB_FUNGI_CDS/
  mkdir -p GB_DB_FUNGI_RNA/
  rm -f GB_DB_FUNGI_CDS/*.fa.gz
  rm -f GB_DB_FUNGI_RNA/*.fa.gz
  mv GB_DB_FUNGI/*_cds_from_genomic.fna.gz GB_DB_FUNGI_CDS/
  mv GB_DB_FUNGI/*_rna_from_genomic.fna.gz GB_DB_FUNGI_RNA/
  rm -f FDB.fa.gz;
  zcat GB_DB_FUNGI/*.fna.gz | gzip -9 > FDB.fa.gz
  fi
#
# ==============================================================================
# PLANT DB
#
if [[ "$BUILD_PLANT" -eq "1" ]];
  then
  rm -f assembly_summary.txt;
  wget ftp://ftp.ncbi.nlm.nih.gov/genomes/genbank/fungi/assembly_summary.txt
  awk -F '\t' '{if($12=="Complete Genome"||$12=="Chromosome") print $20}' assembly_summary.txt > ASCG.txt
  mkdir -p GB_DB_PLANT/
  rm -f GB_DB_PLANT/*.fa.gz
  cat ASCG.txt | xargs -I{} -n1 -P$THREADS wget -P GB_DB_PLANT {}/*_genomic.fna.gz
  mkdir -p GB_DB_PLANT_CDS/
  mkdir -p GB_DB_PLANT_RNA/
  rm -f GB_DB_PLANT_CDS/*.fa.gz
  rm -f GB_DB_PLANT_RNA/*.fa.gz
  mv GB_DB_PLANT/*_cds_from_genomic.fna.gz GB_DB_PLANT_CDS/
  mv GB_DB_PLANT/*_rna_from_genomic.fna.gz GB_DB_PLANT_RNA/
  rm -f TDB.fa.gz;
  zcat GB_DB_PLANT/*.fna.gz | gzip -9 > TDB.fa.gz
  fi
#
# ==============================================================================
# INVERTEBRATE DB
#
if [[ "$BUILD_INVER" -eq "1" ]];
  then
  rm -f assembly_summary.txt;
  wget ftp://ftp.ncbi.nlm.nih.gov/genomes/genbank/invertebrate/assembly_summary.txt
  awk -F '\t' '{if($12=="Complete Genome"||$12=="Chromosome") print $20}' assembly_summary.txt > ASCG.txt
  mkdir -p GB_DB_INVER/
  rm -f GB_DB_INVER/*.fa.gz
  cat ASCG.txt | xargs -I{} -n1 -P$THREADS wget -P GB_DB_INVER {}/*_genomic.fna.gz
  mkdir -p GB_DB_INVER_CDS/
  mkdir -p GB_DB_INVER_RNA/
  rm -f GB_DB_INVER_CDS/*.fa.gz
  rm -f GB_DB_INVER_RNA/*.fa.gz
  mv GB_DB_INVER/*_cds_from_genomic.fna.gz GB_DB_INVER_CDS/
  mv GB_DB_INVER/*_rna_from_genomic.fna.gz GB_DB_INVER_RNA/
  rm -f IDB.fa.gz;
  zcat GB_DB_INVER/*.fna.gz | gzip -9 > IDB.fa.gz
  fi
#
# ==============================================================================
# VERTEBRATE MAMMALIAN DB
#
if [[ "$BUILD_VER_MAM" -eq "1" ]];
  then
  rm -f assembly_summary.txt;
  wget ftp://ftp.ncbi.nlm.nih.gov/genomes/genbank/vertebrate_mammalian/assembly_summary.txt
  awk -F '\t' '{if($12=="Complete Genome"||$12=="Chromosome") print $20}' assembly_summary.txt > ASCG.txt
  mkdir -p GB_DB_VER_MAM/
  rm -f GB_DB_VER_MAM/*.fa.gz
  cat ASCG.txt | xargs -I{} -n1 -P$THREADS wget -P GB_DB_VER_MAM {}/*_genomic.fna.gz
  mkdir -p GB_DB_VER_MAM_CDS/
  mkdir -p GB_DB_VER_MAM_RNA/
  rm -f GB_DB_VER_MAM_CDS/*.fa.gz
  rm -f GB_DB_VER_MAM_RNA/*.fa.gz
  mv GB_DB_VER_MAM/*_cds_from_genomic.fna.gz GB_DB_VER_MAM_CDS/
  mv GB_DB_VER_MAM/*_rna_from_genomic.fna.gz GB_DB_VER_MAM_RNA/
  rm -f VMDB.fa.gz;
  zcat GB_DB_VER_MAM/*.fna.gz | gzip -9 > VMDB.fa.gz
  fi
#
# ==============================================================================
# VERTEBRATE OTHER DB
#
if [[ "$BUILD_VER_OTH" -eq "1" ]];
  then
  rm -f assembly_summary.txt;
  wget ftp://ftp.ncbi.nlm.nih.gov/genomes/genbank/vertebrate_other/assembly_summary.txt
  awk -F '\t' '{if($12=="Complete Genome"||$12=="Chromosome") print $20}' assembly_summary.txt > ASCG.txt
  mkdir -p GB_DB_VER_OTH/
  rm -f GB_DB_VER_OTH/*.fa.gz
  cat ASCG.txt | xargs -I{} -n1 -P$THREADS wget -P GB_DB_VER_OTH {}/*_genomic.fna.gz
  mkdir -p GB_DB_VER_OTH_CDS/
  mkdir -p GB_DB_VER_OTH_RNA/
  rm -f GB_DB_VER_OTH_CDS/*.fa.gz
  rm -f GB_DB_VER_OTH_RNA/*.fa.gz
  mv GB_DB_VER_OTH/*_cds_from_genomic.fna.gz GB_DB_VER_OTH_CDS/
  mv GB_DB_VER_OTH/*_rna_from_genomic.fna.gz GB_DB_VER_OTH_RNA/
  rm -f VODB.fa.gz;
  zcat GB_DB_VER_OTH/*.fna.gz | gzip -9 > VODB.fa.gz
  fi
#
# ==============================================================================
