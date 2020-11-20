#!/bin/bash
#
# ==============================================================================
# | |
# |       THIS PROGRAM COMPUTES RELATIVE COMPLEXITY PROFILES WITH GTO          |
# | =========================================================== |
# | |
# |           ./gto_relative_complexity_profile.sh seqA.fa SeqB.fa             |
# | |
# |                     FILE NEEDED TO THE COMPUTATION:                        |
# | |
# |                $1: FILE WITH THE REFERENCE SEQUENCE IN FASTA               |
# |                $2: FILE WITH THE TARGET    SEQUENCE IN FASTA               |
# | |
# ==============================================================================
#
# ==============================================================================
# ================================ DEFINITIONS =================================
#
#LEVEL=" -rm 5:10:0:0:0.85/0:0:0 -rm 11:20:0:0:0.9/4:10:0.9 ";
LEVEL=" $3 ";
WINDOW_SIZE=3;
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
  gto_fasta_rand_extra_chars < $2 | gto_fasta_to_seq > SEQ;
  #
  # GET WINDOW SIZE BY SEQUENCE SIZE
  LENGTH=`gto_info < SEQ | grep "Number of sym" | awk '{ print $5}'`;
  echo "WINDOW SIZE: $WINDOW_SIZE";
  #
  gto_geco -v $LEVEL -e -r $1 SEQ
  #
  gto_upper_bound -u 2 < SEQ.iae   > SEQ_UB
  gto_filter -d 0 -w $WINDOW_SIZE -c < SEQ_UB > FIL_UB.x
  gto_segment -t 1 < FIL_UB.x > $1.positions
  #
  gnuplot << EOF
    reset
    set terminal pdfcairo enhanced color font 'Verdana,12'
    set output "profile-$1.pdf"
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
    plot "FIL_UB.x" using 1:2 with lines ls 1
EOF
  fi
#
#
# ==============================================================================
# ==============================================================================

