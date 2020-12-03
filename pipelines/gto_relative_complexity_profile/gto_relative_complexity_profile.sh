#!/bin/bash
#
TAG="X";
RUN="0";
LEVEL=" -rm 5:10:1:0:0.85/0:0:0 -rm 11:20:1:0:0.9/4:10:0.9 "; 
THREADS="8";
WINDOW="5";
REFERENCE="";
TARGET="";
#
################################################################################
#
SHOW_MENU () {
  echo " -------------------------------------------------------  ";
  echo "                                                          ";
  echo " gto_relative_complexity_profile.sh >> creates relative   ";
  echo "                                    complexity profiles   ";
  echo "                                                          ";
  echo " Program options ---------------------------------------  ";
  echo "                                                          ";
  echo " -h, --help                     Show this,                ";
  echo " -c, --install                  Installation (w/ conda),  ";
  echo "                                                          ";
  echo " -n <STR>, --name <STR>         TAG name for uniqueness,  ";
  echo " -d <INT>, --threads <INT>      Number of threads,        ";
  echo " -w <INT>, --window <INT>       Low-pass filter size,     ";
  echo " -l <STR>, --level <STR>        Compression parameters.   ";
  echo "                                                          ";
  echo " Input options -----------------------------------------  ";
  echo "                                                          ";
  echo " -r <FILE>, --reference <FILE>  FASTA Reference filename, ";
  echo " -t <FILE>, --target <FILE>     FASTA target filename.    ";
  echo "                                                          ";
  echo " Example -----------------------------------------------  ";
  echo "                                                          ";
  echo " gto_relative_complexity_profile.sh --threads 8 \\        ";
  echo " --name x --reference ref.fa --target tar.fa \\           ";
  echo " --window 5 --level \" -rm 11:20:0:0:0.9/4:10:0.9 \"      ";
  echo "                                                          ";
  echo " -------------------------------------------------------  ";
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
    echo -e "\e[42mTIP\e[49m: Try: gto_relative_complexity_profile.sh --install" >&2;
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
    -t|--target)
      TARGET="$2";
      shift 2;
    ;;
    -w|--window)
      WINDOW="$2";
      shift 2;
    ;;
    -l|--level)
      LEVEL="$2";
      shift 2;
    ;;
    -*) # unknown option with small
    echo "Invalid arg ($1)!";
    echo "For help, try: gto_relative_complexity_profile.sh -h"
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
  conda install -c cobilab gto --yes
  exit;
  fi
#
################################################################################
#
if [[ "$RUN" -eq "1" ]];
  then
  #
  PROGRAM_EXISTS "gto";
  #
  CHECK_INPUT "$REFERENCE";
  CHECK_INPUT "$TARGET";
  #
  rm -f SEQ-$TAG SEQ-$TAG.iae SEQ-$TAG.ub $REFERENCE-$TARGET-$TAG.pos $REFERENCE-$TARGET-$TAG.x ;
  #
  echo "Using window size: $WINDOW";
  echo "Randomizing chars outside {A,C,G,T}";
  gto_fasta_rand_extra_chars < $TARGET | gto_fasta_to_seq > SEQ-$TAG;
  echo "Running compression ... ";
  gto_geco -v $LEVEL -e -r $REFERENCE SEQ-$TAG;
  echo "Processing output ... ";
  gto_upper_bound -u 2 < SEQ-$TAG.iae > SEQ-$TAG.ub
  gto_filter -d 0 -w $WINDOW -c < SEQ-$TAG.ub > $REFERENCE-$TARGET-$TAG.x
  gto_segment -t 1 < $REFERENCE-$TARGET-$TAG.x > $REFERENCE-$TARGET-$TAG.pos
  #
  echo "Generating plot with Gnuplot ... ";
  gnuplot << EOF
    reset
    set terminal pdfcairo enhanced color font 'Verdana,12'
    set output "$REFERENCE-$TARGET-$TAG.pdf"
    set style line 101 lc rgb '#000000' lt 1 lw 4
    set border 3 front ls 101
    set tics nomirror out scale 0.75
    set format '%g'
    set size ratio 0.1
    unset key
    set yrange [0:2] 
    set xrange [:]
    set xtics auto
    set ytics 0.5
    set grid 
    set ylabel "Bps"
    set xlabel "Length"
    set border linewidth 1.5
    set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 5 ps 0.4 # --- blue
    set style line 2 lc rgb '#0060ad' lt 1 lw 4 pt 6 ps 0.4 # --- green
    plot "$REFERENCE-$TARGET-$TAG.x" using 1:2 with lines ls 1
EOF
  #
  rm -f SEQ-$TAG SEQ-$TAG.iae SEQ-$TAG.ub ;
  #
  echo "PDF plot           : $REFERENCE-$TARGET-$TAG.pdf";
  echo "Segmented regions  : $REFERENCE-$TARGET-$TAG.pos";
  echo "Information values : $REFERENCE-$TARGET-$TAG.x";
  #
  fi
#
#
# ==============================================================================
# ==============================================================================
