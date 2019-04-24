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
#   => MTDB.fa.gz (MITOCHONDRIAL)
#   => PLDB.fa.gz (PLASTID)
# 
# ==============================================================================
# NUMBER OF THREADS USED FOR DOWNLOAD
#
THREADS=8;
#
# ==============================================================================
# ONLY FLAGS WITH '1' WILL BE PROCESSED 
#
BUILD_VIRAL=0;
BUILD_BACTERIA=0;
BUILD_ARCHAEA=0;
BUILD_PROTOZOA=0;
BUILD_FUNGI=0;
BUILD_PLANT=0;
BUILD_INVER=0;
BUILD_VER_MAM=0;
BUILD_VER_OTH=0;
BUILD_MITO=0;
BUILD_PLAST=0;
SHOW_HELP=1;

for i in "$@"
do
  case $i in
    -h|--help)
      SHOW_HELP=1;
      shift
    ;;
    -vi|--build-viral)
      BUILD_VIRAL=1;
      SHOW_HELP=0;
      shift
    ;;
    -ba|--build-bacteria)
      BUILD_BACTERIA=1;
      SHOW_HELP=0;
      shift
    ;;
    -ar|--build-archaea)
      BUILD_ARCHAEA=1;
      SHOW_HELP=0;
      shift
    ;;
    -pr|--build-protozoa)
      BUILD_PROTOZOA=1;
      SHOW_HELP=0;
      shift
    ;;
    -fu|--build-fungi)
      BUILD_FUNGI=1;
      SHOW_HELP=0;
      shift
    ;;
    -pl|--build-plant)
      BUILD_PLANT=1;
      SHOW_HELP=0;
      shift
    ;;
    -in|--build-inver)
      BUILD_INVER=1;
      SHOW_HELP=0;
      shift
    ;;
    -vm|--build-ver-mam)
      BUILD_VER_MAM=1;
      SHOW_HELP=0;
      shift
    ;;
    -vo|--build-ver-oth)
      BUILD_VER_OTH=1;
      SHOW_HELP=0;
      shift
    ;;
    -mi|--build-mito)
      BUILD_MITO=1;
      SHOW_HELP=0;
      shift
    ;;
    -ps|--build-plast)
      BUILD_PLAST=1;
      SHOW_HELP=0;
      shift
    ;;
    *) # unknown option
    echo "Invalid arg "$1
    ;;
  esac
done
#
# ==============================================================================
# HELP
#
if [ "$SHOW_HELP" -eq "1" ];
  then
    echo "Usage: BUILD_DB.sh [options]"
    echo ""
    echo "It downloads and compresses the complete genomic sequences form the"
    echo "NCBI database that are labelled as 'Complete genome' or 'Chromosome'."
    echo ""
    echo "    -h,  --help             Show this help message and exit"
    echo "    -vi, --build-viral      Downloads and builds the viral database"
    echo "    -ba, --build-bacteria   Downloads and builds the bacteria database"
    echo "    -ar, --build-archaea    Downloads and builds the archaea database"
    echo "    -pr, --build-protozoa   Downloads and builds the protozoa database"
    echo "    -fu, --build-fungi      Downloads and builds the fungi database"
    echo "    -pl, --build-plant      Downloads and builds the plant database"
    echo "    -in, --build-inver      Downloads and builds the invertebrate database"
    echo "    -vm, --build-ver-mam    Downloads and builds the vertebrate mammalian database"
    echo "    -vo, --build-ver-oth    Downloads and builds the vertebrate other database"
    echo "    -mi, --build-mito       Downloads and builds the mitochondrion database"
    echo "    -ps, --build-plast      Downloads and builds the plastid database"
    echo ""
    echo "Example: BUILD_DB.sh -vi -ba "
    exit 1
  fi
#
# ==============================================================================
# VIRAL DB
#
if [ "$BUILD_VIRAL" -eq "1" ];
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
if [ "$BUILD_BACTERIA" -eq "1" ];
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
if [ "$BUILD_ARCHAEA" -eq "1" ];
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
if [ "$BUILD_PROTOZOA" -eq "1" ];
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
if [ "$BUILD_FUNGI" -eq "1" ];
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
if [ "$BUILD_PLANT" -eq "1" ];
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
if [ "$BUILD_INVER" -eq "1" ];
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
if [ "$BUILD_VER_MAM" -eq "1" ];
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
if [ "$BUILD_VER_OTH" -eq "1" ];
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
# MITOCHONDRIAL DB
#
if [ "$BUILD_MITO" -eq "1" ];
  then
  rm -f mitochondrion.1.1.genomic.fna.gz mitochondrion.2.1.genomic.fna.gz;
  wget ftp://ftp.ncbi.nlm.nih.gov/refseq/release/mitochondrion/mitochondrion.1.1.genomic.fna.gz
  wget ftp://ftp.ncbi.nlm.nih.gov/refseq/release/mitochondrion/mitochondrion.2.1.genomic.fna.gz
  zcat mitochondrion.1.1.genomic.fna.gz mitochondrion.2.1.genomic.fna.gz | gzip -9 > MTDB.fa.gz
  fi
#
# ==============================================================================
# PLASTID DB
#
if [ "$BUILD_PLAST" -eq "1" ];
  then
  rm -f plastid.1.1.genomic.fna.gz plastid.2.1.genomic.fna.gz
  wget ftp://ftp.ncbi.nlm.nih.gov/refseq/release/plastid/plastid.1.1.genomic.fna.gz
  wget ftp://ftp.ncbi.nlm.nih.gov/refseq/release/plastid/plastid.2.1.genomic.fna.gz
  zcat plastid.1.1.genomic.fna.gz plastid.2.1.genomic.fna.gz | gzip -9 > PLDB.fa.gz
  fi
#
# ==============================================================================
