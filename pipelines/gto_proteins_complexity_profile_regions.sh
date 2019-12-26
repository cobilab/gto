#!/bin/bash
#
# ==============================================================================
# |                                                                            |
# |             THIS PROGRAM COMPUTES COMPLEXITY PROFILES WITH GTO             |
# |             ==================================================             |
# |                                                                            |
# |              ./gto_proteins_complexity_profile_regions seq.fa              |
# |                                                                            |
# |                     FILE NEEDED TO THE COMPUTATION:                        |
# |                                                                            |
# |                   $1: FILE WITH THE PROTEOME IN FASTA                      |
# |                                                                            |
# ==============================================================================
#
# ==============================================================================
# ================================ DEFINITIONS =================================
#
LEVEL=" -e -tm 6:100:0.95/1:20:0.96 -tm 8:200:0.98/4:50:0.95 ";
#
GET_GTO=0;
RUN_COMPARISON=1;
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
  grep -v ">" $1 | tr -d "\n" > SEQ;
  gto_reverse < SEQ > SEQ_R;
  #
  # GET WINDOW SIZE BY SEQUENCE SIZE
  LENGTH=`gto_info < SEQ | grep "Number of sym" | awk '{ print $5}'`;
  CARDINALITY=`gto_info < SEQ | grep "Alphabet size" | awk '{ print $4}'`;
  WINDOW_SIZE=`echo "$LENGTH /500" | bc`;
  LOG_CARD=`echo "l($CARDINALITY)/l(2)" | bc -l`;
  echo "LOG_CARD: $LOG_CARD";
  echo "CARD: $CARDINALITY";
  LOG_CARD_DIV_2=`echo "$LOG_CARD/2.0" | bc -l`;
  LOG_CARD_NORM=`echo "scale=0;$LOG_CARD/1" | bc`;
  echo "WINDOW SIZE: $WINDOW_SIZE";
  #
  gto_amino_acid_compressor -v $LEVEL -e SEQ
  gto_amino_acid_compressor -v $LEVEL -e SEQ_R
  #
  cp SEQ.iae SEQ_UB
  cp SEQ_R.iae SEQ_R_UB
  #
  gto_filter -d 0 -w $WINDOW_SIZE -c < SEQ_UB   > FIL_UB.x
  gto_filter -d 0 -w $WINDOW_SIZE -c < SEQ_R_UB > FIL_UB_R.x
  #
  tac FIL_UB_R.x > FIL_UB_N.x
  awk '{print $1;}' FIL_UB.x   > IDXES
  awk '{print $2;}' FIL_UB.x   > A_D
  awk '{print $2;}' FIL_UB_N.x > A_R
  #
  gto_min -f A_D -s A_R > A_min
  #
  paste -d '\t' IDXES A_min > PROFILE_N
  #
  gto_segment -t $LOG_CARD_DIV_2 < PROFILE_N > $1.positions
  #
  gnuplot << EOF
    reset
    set terminal pdfcairo enhanced color font 'Verdana,12'
    set output "profile-aa-$1.pdf"
    set style line 101 lc rgb '#000000' lt 1 lw 4
    set border 3 front ls 101
    set tics nomirror out scale 0.75
    set format '%g'
    set size ratio 0.1
    unset key
    set yrange [0:] 
    set xrange [:]
    set xtics auto
    set ytics 0.5
    set grid 
    set ylabel "Bps"
    set xlabel "Length"
    set border linewidth 1.5
    set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 5 ps 0.4 # --- blue
    set style line 2 lc rgb '#0060ad' lt 1 lw 4 pt 6 ps 0.4 # --- green
    plot "PROFILE_N" using 1:2 with lines ls 1
EOF
  fi
#
#
# ==============================================================================
# ==============================================================================
