#!/bin/bash
#
TAG="X";
RUN="0";
THREADS="4";
REFERENCE="";
FORWARD="o_fw_pr.fq";
REVERSE="o_rv_pr.fq";
UNPAIRED="o_fw_unpr.fq,o_rv_unpr.fq";
#
################################################################################
#
SHOW_MENU () {
  echo " ------------------------------------------------------- ";
  echo " ";
  echo " gto_align_reads.sh >> FASTQ reads alignment pipeline     ";
  echo "        with sort, duplications removal, and indexes. ";
  echo " ";
  echo " Program options --------------------------------------- ";
  echo " ";
  echo " -h, --help                     Show this, ";
  echo " -c, --install                  Installation (w/ conda), ";
  echo " ";
  echo " -n <STR>, --name <STR>         TAG name for uniqueness,  ";
  echo " -t <INT>, --threads <INT>      Number of threads.        ";
  echo " ";
  echo " Input options ----------------------------------------- ";
  echo " ";
  echo " -r <FILE>, --reference <FILE>  FASTA Reference filename, ";
  echo " ";
  echo " -1 <FILE>, --forward <FILE>    FASTQ forward filename,   ";
  echo " -2 <FILE>, --reverse <FILE>    FASTQ reverse filename,   ";
  echo " -U <FILE>, --unpaired <FILE>   FASTQ unpaired filename.  ";
  echo " ";
  echo " Example ----------------------------------------------- ";
  echo " ";
  echo " gto_align_reads.sh --threads 8 --reference B19.fa \\ ";
  echo " --forward FW.fq --reverse RV.fq -U FW_U.fq,RV_U.fq ";
  echo " ";
  echo " ------------------------------------------------------- ";
  }
#
################################################################################
#
CHECK_INPUT () {
  FILE=$1
  if [ -f "$FILE" ];
    then
    echo "Input filename: $FILE"
    else
    echo -e "\e[31mERROR: input file not found ($FILE)!\e[0m";
    SHOW_MENU;
    exit;
    fi
  }
#
################################################################################
#
PROGRAM_EXISTS () {
  if ! [ -x "$(command -v $1)" ];
    then
    echo -e "\e[41mERROR\e[49m: $1 is not installed." >&2;
    echo -e "\e[42mTIP\e[49m: Try: gto_align_reads.sh --install" >&2;
    exit 1;
    fi
  }
#
################################################################################
#
if [[ "$#" -lt 1 ]];
  then
  HELP=1;
  fi
#
POSITIONAL=();
#
while [[ $# -gt 0 ]]
  do
  i="$1";
  case $i in
    -h|--help|?)
      HELP=1;
      shift
    ;;
    -c|--install|--compile)
      INSTALL=1;
      shift
    ;;
    -n|--name|--tag)
      TAG="$2";
      shift 2;
    ;;
    -t|--threads)
      THREADS="$2";
      shift 2;
    ;;
    -r|--reference)
      REFERENCE="$2";
      RUN=1;
      shift 2;
    ;;
    -1|--forward)
      FORWARD="$2";
      shift 2;
    ;;
    -2|--reverse)
      REVERSE="$2";
      shift 2;
    ;;
    -U|--unpaired)
      UNPAIRED="$2";
      shift 2;
    ;;
    -*) # unknown option with small
    echo "Invalid arg ($1)!";
    echo "For help, try: gto_align_reads.sh -h"
    exit 1;
    ;;
  esac
  done
#
set -- "${POSITIONAL[@]}" # restore positional parameters
#
################################################################################
#
if [[ "$HELP" -eq "1" ]];
  then
  SHOW_MENU;
  exit;
  fi
#
################################################################################
#
if [[ "$INSTALL" -eq "1" ]];
  then
  conda install -c bioconda samtools --yes
  conda install -c bioconda bowtie2 --yes
  exit;
  fi
#
################################################################################
#
if [[ "$RUN" -eq "1" ]];
  then
  #
  echo "Using $THREADS threads ...";
  #
  PROGRAM_EXISTS "bowtie2";
  PROGRAM_EXISTS "samtools";
  #
  CHECK_INPUT "$REFERENCE";
  #
  CHECK_INPUT "$FORWARD";
  CHECK_INPUT "$REVERSE";
  CHECK_INPUT "$UNPAIRED";
  #
  rm -f index_file_$TAG* aligned_sorted-$TAG.bam aligned_sorted-$TAG.bam.bai aligned_sorted-$TAG.bam
  #
  bowtie2-build $REFERENCE index_file_$TAG
  bowtie2 -a --threads $THREADS --very-sensitive -x index_file_$TAG -1 $FORWARD -2 $REVERSE -U $UNPAIRED > aligned-$TAG.sam
  samtools sort --threads $THREADS aligned-$TAG.sam > aligned_sorted-$TAG.bam
  samtools sort --threads $THREADS -n aligned_sorted-$TAG.bam > aligned_sorted_sorted-$TAG.bam
  samtools fixmate --threads $THREADS -m aligned_sorted_sorted-$TAG.bam aligned_sorted_sorted-$TAG-fixmate.bam
  samtools sort --threads $THREADS -o aligned_sorted_sorted-$TAG-fixmate-sort.bam aligned_sorted_sorted-$TAG-fixmate.bam
  samtools markdup --threads $THREADS -r aligned_sorted_sorted-$TAG-fixmate-sort.bam aligned_sorted-$TAG.bam
  samtools index -@ $THREADS aligned_sorted-$TAG.bam aligned_sorted-$TAG.bam.bai
  samtools flagstat -@ $THREADS aligned_sorted-$TAG.bam > Alignments-Stats-$TAG.txt
  #
  rm -f *.bt2 aligned-$TAG.sam aligned_sorted_sorted-$TAG.bam aligned_sorted_sorted-$TAG-fixmate.bam aligned_sorted_sorted-$TAG-fixmate-sort.bam
  #
  echo "Reference  : $REFERENCE (index included)";
  echo "Alignments : aligned_sorted-$TAG.bam (index included)";
  #
  fi
#
################################################################################
# 