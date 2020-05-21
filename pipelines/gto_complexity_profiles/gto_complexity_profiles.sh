#!/bin/bash
#
# ==============================================================================
# |                                                                            |
# |     THIS PROGRAM COMPUTES COMPLEXITY AND RELATIVE COMPLEXITY PROFILES      |
# |     =================================================================      |
# |                                                                            |
# |           ./gto_complexity_profiles.sh ids.txt VDB.fa reads.fq             |
# |                                                                            |
# |                FILES NEEDED TO THE WHOLE COMPUTATION:                      |
# |                                                                            |
# |                $1  >  FILE WITH THE GENOMES ID (GID)                       |
# |                $2  >  REFERENCE DATABASE WITH THE GENOMES                  |
# |                       WHEN BUILD_DATABASE=1 IT WILL BE CREATED             |
# |                $3  >  READS FROM METAGENOMICS [RELATIVE MODE]              |
# |                                                                            |
# ==============================================================================
#
# ==============================================================================
# ================================ DEFINITIONS =================================
#
GET_GTO=1;
FILTER_READS=1;
RUN_COMPARISON=1;
RUN_RELATIVE=1; # reads.fq ARE NEEDED FOR THIS COMPUTATION
#
# ==============================================================================
# ================================== GET GTO ===================================
if [[ "$GET_GTO" -eq "1" ]];
  then
  conda install -c cobilab gto --yes
  fi
#
# ==============================================================================
# ============================= EXTRACT FASTA READS ============================
if [[ "$FILTER_READS" -eq "1" ]];
  then
  IFS=$'\r\n' GLOBIGNORE='*' command eval  'IDS_ARRAY=($(cat $1))'
  for ids_gen in ${IDS_ARRAY[@]};
    do
    gto_fasta_extract_read_by_pattern -p "$ids_gen" < $2 > S$ids_gen.fa
    done
  fi
#
# ==============================================================================
# =============================== RUN COMPARISON ===============================
if [[ "$RUN_COMPARISON" -eq "1" ]];
  then
  for ids_gen in ${IDS_ARRAY[@]};
    do
    seqx="S$ids_gen.fa";
    #
    gto_fasta_rand_extra_chars < $seqx | gto_fasta_to_seq > SEQ;
    gto_reverse < SEQ > SEQ_R;
    #
    # GET WINDOW SIZE BY SEQUENCE SIZE
    LENGTH=`gto_info < SEQ | grep "Number of sym" | awk '{ print $5}'`;
    WINDOW_SIZE=`echo "$LENGTH / 285" | bc`;
    echo "WINDOW SIZE: $WINDOW_SIZE";
    #
    gto_geco -v -tm 16:200:1:20:0.95/5:10:0.95 -e SEQ
    gto_geco -v -tm 16:200:1:20:0.95/5:10:0.95 -e SEQ_R
    #
    gto_upper_bound -u 2 < SEQ.iae   > SEQ_UB
    gto_upper_bound -u 2 < SEQ_R.iae > SEQ_R_UB
    #
    gto_filter -d 2 -w $WINDOW_SIZE -c < SEQ_UB   > FIL_UB.x
    gto_filter -d 2 -w $WINDOW_SIZE -c < SEQ_R_UB > FIL_UB_R.x
    #
    tac FIL_UB_R.x > FIL_UB_N.x
    awk '{print $1;}' FIL_UB.x   > IDXES
    awk '{print $2;}' FIL_UB.x   > A_D
    awk '{print $2;}' FIL_UB_R.x > A_R
    #
    gto_min -f A_D -s A_R > A_min
    #
    paste -d '\t' IDXES A_min > PROFILE_N
    #
    gnuplot << EOF
      reset
      set terminal pdfcairo enhanced color font 'Verdana,12'
      set output "profile_self-$ids_gen.pdf"
      set style line 101 lc rgb '#000000' lt 1 lw 4
      set border 3 front ls 101
      set tics nomirror out scale 0.75
      set format '%g'
      set size ratio 0.1
      unset key
      set yrange [:2] 
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
    if [[ "$RUN_RELATIVE" -eq "1" ]];  # HERE reads.fq WILL BE NEEDED!
      then
      #
      gto_fasta_rand_extra_chars < $seqx | gto_fasta_to_seq > SEQ;
      gto_reverse < SEQ > SEQ_R;
      #
      gto_geco -v -rm 16:200:1:20:0.95/5:10:0.95 -e -r $3 SEQ
      gto_geco -v -rm 16:200:1:20:0.95/5:10:0.95 -e -r $3 SEQ_R
      #
      gto_upper_bound -u 2 < SEQ.iae   > SEQ_UB
      gto_upper_bound -u 2 < SEQ_R.iae > SEQ_R_UB
      #
      gto_filter -d 2 -w $WINDOW_SIZE -c < SEQ_UB   > FIL_UB.x
      gto_filter -d 2 -w $WINDOW_SIZE -c < SEQ_R_UB > FIL_UB_R.x
      #
      tac FIL_UB_R.x > FIL_UB_N.x
      awk '{print $1;}' FIL_UB.x   > IDXES
      awk '{print $2;}' FIL_UB.x   > A_D
      awk '{print $2;}' FIL_UB_R.x > A_R
      #
      gto_min -f A_D -s A_R > A_min
      #
      paste -d '\t' IDXES A_min > PROFILE_N_REL
      #
      gnuplot << EOF
        reset
        set terminal pdfcairo enhanced color font 'Verdana,12'
        set output "profile_relative-$ids_gen.pdf"
        set style line 101 lc rgb '#000000' lt 1 lw 4
        set border 3 front ls 101
        set tics nomirror out scale 0.75
        set format '%g'
        set size ratio 0.1
        unset key
        set yrange [:2]
        set xrange [:]
        set xtics auto
        set ytics 0.5
        set grid
        set ylabel "Bps"
        set xlabel "Length"
        set border linewidth 1.5
        set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 5 ps 0.4 # --- blue
        set style line 2 lc rgb '#228B22' lt 1 lw 2 pt 5 ps 0.4 # --- green
        plot "PROFILE_N_REL" using 1:2 with lines ls 2
EOF
      # JOINT PLOT
      paste -d '\t' PROFILE_N A_min > PROFILES_N_AND_N_REL
      #
      gnuplot << EOF
        reset
        set terminal pdfcairo enhanced color font 'Verdana,12'
        set output "profiles_self_and_relative-$ids_gen.pdf"
        set style line 101 lc rgb '#000000' lt 1 lw 4
        set border 3 front ls 101
        set tics nomirror out scale 0.75
        set format '%g'
        set size ratio 0.1
        unset key
        set yrange [:2]
        set xrange [:]
        set xtics auto
        set ytics 0.5
        set grid
        set ylabel "Bps"
        set xlabel "Length"
        set border linewidth 1.5
        set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 5 ps 0.4 # --- blue
        set style line 2 lc rgb '#228B22' lt 1 lw 2 pt 5 ps 0.4 # --- green
        plot "PROFILES_N_AND_N_REL" using 1:2 with lines ls 1, "PROFILES_N_AND_N_REL" using 1:3 with lines ls 2 
EOF
      fi
    done
    #
  fi
#
# ==============================================================================
# ==============================================================================

