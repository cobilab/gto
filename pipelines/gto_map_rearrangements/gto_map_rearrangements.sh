#!/bin/bash
#
# ==============================================================================
# |                                                                            |
# |             THIS PROGRAM MAPS & VISUALIZES REARRANGEMETS W GTO             |
# |             ==================================================             |
# |                                                                            |
# |                ./gto_map_rearrangements.sh seq1.fa seq2.fa                 |
# |                                                                            |
# |                     FILE NEEDED TO THE COMPUTATION:                        |
# |                                                                            |
# |             REF:   $1: FILE WITH THE GENOME #1 IN FASTA FORMAT             |
# |             CON:   $2: FILE WITH THE GENOME #2 IN FASTA FORMAT             |
# |                                                                            |
# ==============================================================================
#
# ==============================================================================
# ================================ DEFINITIONS =================================
#
PARAM=" -rm 13:50:0:0:0.9/0:10:0.94 ";
PARAM_R=" -rm 13:50:2:0:0.9/0:10:0.94 ";
WINDOW="5";
REFERENCE="";
TARGET="";
THRESHOLD="1.5";
LINK="5";
WIDTH="30";
SPACE="120";
RUN="0";
# 
# ==============================================================================
#
SHOW_MENU () {
  echo " -------------------------------------------------------   ";
  echo "                                                           ";
  echo " gto_map_rearrangements.sh >> maps and creates an image    ";
  echo "                              w possible rearrangements    ";
  echo "                                                           ";
  echo " Program options ---------------------------------------   ";
  echo "                                                           ";
  echo " -h, --help                      Show this,                ";
  echo " -c, --install                   Installation (conda),     ";
  echo "                                                           ";
  echo " -w <INT>, --window <INT>        Low-pass filter size,     ";
  echo " -th <REAL>, --threshold <REAL>  Segmentation threshold,   ";
  echo "                                                           ";
  echo " -l <INT>, --link <INT>          Link type [0;4],          ";
  echo " -w <INT>, --width <INT>         Width size,               ";
  echo " -s <INT>, --space <INT>         Space size.               ";
  echo "                                                           ";
  echo " Input options -----------------------------------------   ";
  echo "                                                           ";
  echo " -r <FILE>, --reference <FILE>   FASTA Ref. filename,      ";
  echo " -t <FILE>, --target <FILE>      FASTA target filename     ";
  echo "                                 (represented with CON)    ";
  echo "                                                           ";
  echo " Example -----------------------------------------------   ";
  echo "                                                           ";
  echo " gto_map_rearrangements.sh --window 5 --target CON.fa \\   ";
  echo " --reference REF.fa                                        ";
  echo "                                                           ";
  echo " -------------------------------------------------------   ";
  }
#
# ==============================================================================
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
# ==============================================================================
#
PROGRAM_EXISTS () {
  if ! [ -x "$(command -v $1)" ];
    then
    echo -e "\e[41mERROR\e[49m: $1 is not installed." >&2;
    echo -e "\e[42mTIP\e[49m: Try: gto_map_rearrangements.sh --install" >&2;
    exit 1;
    fi
  }
#
# ==============================================================================
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
    -r|--reference)
      REFERENCE="$2";
      RUN=1;
      shift 2;
    ;;
    -th|--threshold)
      THRESHOLD="$2";
      shift 2;
    ;;
    -t|--target)
      TARGET="$2";
      shift 2;
    ;;
    -w|--width)
      WIDTH="$2";
      shift 2;
    ;;
    -l|--link)
      LINK="$2";
      shift 2;
    ;;
    -s|--space)
      SPACE="$2";
      shift 2;
    ;;
    -w|--window)
      WINDOW="$2";
      shift 2;
    ;;
    -*) # unknown option with small
    echo "Invalid arg ($1)!";
    echo "For help, try: gto_map_rearrangements.sh -h"
    exit 1;
    ;;
  esac
  done
#
set -- "${POSITIONAL[@]}" # restore positional parameters
#
# ==============================================================================
#
if [[ "$HELP" -eq "1" ]];
  then
  SHOW_MENU;
  exit;
  fi
#
# ==============================================================================
#
if [[ "$INSTALL" -eq "1" ]];
  then
  conda install -c cobilab gto --yes
  exit;
  fi
#
# ==============================================================================
#
if [[ "$RUN" -eq "1" ]];
  then
  #
  PROGRAM_EXISTS "gto";
  #
  CHECK_INPUT "$REFERENCE";
  CHECK_INPUT "$TARGET";
  #
  gto_fasta_rand_extra_chars < $REFERENCE | gto_fasta_to_seq > SEQ1;
  gto_fasta_rand_extra_chars < $TARGET | gto_fasta_to_seq > SEQ2;
  #
  # GET WINDOW SIZE BY SEQUENCE SIZE FOR 1
  LENGTH1=`gto_info < SEQ1 | grep "Number of sym" | awk '{ print $5}'`;
  LENGTH2=`gto_info < SEQ2 | grep "Number of sym" | awk '{ print $5}'`;
  #
  echo "#SCF $LENGTH2 $LENGTH1" > rearrangements-$REFERENCE-$TARGET.csv;
  #
  echo "WINDOW SIZE: $WINDOW";
  #
  gto_geco -v $PARAM -e -r SEQ1 SEQ2
  gto_upper_bound -u 2 < SEQ2.iae > SEQ_2_UB
  gto_filter -d 0 -w $WINDOW -c < SEQ_2_UB > PROFILE_N2
  gto_segment -t $THRESHOLD < PROFILE_N2 > $TARGET.positions
  #
  mapfile -t LINES < $TARGET.positions
  for line in "${LINES[@]}" # 
    do
    #
    I_POS=`echo $line | tr ':' '\t' | awk '{ print $1 }'`;
    E_POS=`echo $line | tr ':' '\t' | awk '{ print $2 }'`;
    #
    gto_genomic_extract -i $I_POS -e $E_POS < SEQ2 > REGION.g
    #
    gto_geco -v $PARAM -e -r REGION.g SEQ1
    gto_upper_bound -u 2 < SEQ1.iae > SEQ1-UB
    gto_filter -d 0 -w $WINDOW -c < SEQ1-UB > PROFILE-SEQ1-$I_POS-$E_POS
    gto_segment -t $THRESHOLD < PROFILE-SEQ1-$I_POS-$E_POS > tmp-positions.csv
    #
    mapfile -t TMP < tmp-positions.csv
    #
    for y in "${TMP[@]}" #
      do
      #
      I_TMP=`echo $y | tr ':' '\t' | awk '{ print $1 }'`;
      E_TMP=`echo $y | tr ':' '\t' | awk '{ print $2 }'`;
      #
      printf "r\t%u\t%u\t%u\t%u\tt\t%u\t%u\t%u\t%u\n" "$I_POS" "$E_POS" "$I_POS" "$E_POS" "$I_TMP" "$E_TMP" "$I_TMP" "$E_TMP" >> rearrangements-$REFERENCE-$TARGET.csv
      #
      done
    #
    done
  #
  # REVERSE PROFILES
  #
  gto_geco -v $PARAM_R -e -r SEQ1 SEQ2
  gto_upper_bound -u 2 < SEQ2.iae > SEQ_2_UB
  gto_filter -d 0 -w $WINDOW -c < SEQ_2_UB > PROFILE_N2
  gto_segment -t $THRESHOLD < PROFILE_N2 > $TARGET.positions
  #
  mapfile -t LINES < $TARGET.positions
  for line in "${LINES[@]}" # 
    do
    #
    I_POS=`echo $line | tr ':' '\t' | awk '{ print $1 }'`;
    E_POS=`echo $line | tr ':' '\t' | awk '{ print $2 }'`;
    #
    gto_genomic_extract -i $I_POS -e $E_POS < SEQ2 > REGION.g
    #
    gto_geco -v $PARAM_R -e -r REGION.g SEQ1
    gto_upper_bound -u 2 < SEQ1.iae > SEQ1-UB
    gto_filter -d 0 -w $WINDOW -c < SEQ1-UB > PROFILE-SEQ1-$I_POS-$E_POS
    gto_segment -t $THRESHOLD < PROFILE-SEQ1-$I_POS-$E_POS > tmp-positions.csv
    #
    mapfile -t TMP < tmp-positions.csv
    #
    for y in "${TMP[@]}" #
      do
      #
      I_TMP=`echo $y | tr ':' '\t' | awk '{ print $1 }'`;
      E_TMP=`echo $y | tr ':' '\t' | awk '{ print $2 }'`;
      #
      printf "r\t%u\t%u\t%u\t%u\tt\t%u\t%u\t%u\t%u\n" "$I_POS" "$E_POS" "$I_POS" "$E_POS" "$E_TMP" "$I_TMP" "$E_TMP" "$I_TMP" >> rearrangements-$REFERENCE-$TARGET.csv
      #
      done
    #
    done
  #
  gto_comparative_map -s $SPACE -w $WIDTH -l $LINK -o map.svg rearrangements-$REFERENCE-$TARGET.csv
  #
  fi
#
#
# ==============================================================================
# ==============================================================================
