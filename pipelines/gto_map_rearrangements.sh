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
# |                $1: FILE WITH THE GENOME #1 IN FASTA FORMAT                 |
# |                $2: FILE WITH THE GENOME #2 IN FASTA FORMAT                 |
# |                                                                            |
# ==============================================================================
#
# ==============================================================================
# ================================ DEFINITIONS =================================
#
LEVEL="$2";
#
GET_GTO=0;
RUN_COMPARISON=1;
PARAM=" -rm 13:50:0:0:0.9/0:10:0.94 ";
PARAM_R=" -rm 13:50:2:0:0.9/0:10:0.94 ";
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
  gto_fasta_rand_extra_chars < $1 | gto_fasta_to_seq > SEQ1;
  gto_fasta_rand_extra_chars < $2 | gto_fasta_to_seq > SEQ2;
  #
  # GET WINDOW SIZE BY SEQUENCE SIZE FOR 1
  LENGTH1=`gto_info < SEQ1 | grep "Number of sym" | awk '{ print $5}'`;
  LENGTH2=`gto_info < SEQ2 | grep "Number of sym" | awk '{ print $5}'`;
  #
  echo "#SCF $LENGTH1 $LENGTH2" > rearrangements-$1-$2.csv;
  #
  WINDOW_SIZE=`echo "$LENGTH1 / 1000" | bc`;
  echo "WINDOW SIZE: $WINDOW_SIZE";
  #
  gto_geco -v $PARAM -e -r SEQ1 SEQ2
  gto_upper_bound -u 2 < SEQ2.iae > SEQ_2_UB
  gto_filter -d 0 -w $WINDOW_SIZE -c < SEQ_2_UB > PROFILE_N2
  gto_segment -t 1.2 < PROFILE_N2 > $2.positions
  #
  mapfile -t LINES < $2.positions
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
    gto_filter -d 0 -w $WINDOW_SIZE -c < SEQ1-UB > PROFILE-SEQ1-$I_POS-$E_POS
    gto_segment -t 1.2 < PROFILE-SEQ1-$I_POS-$E_POS > tmp-positions.csv
    #
    mapfile -t TMP < tmp-positions.csv
    #
    for y in "${TMP[@]}" #
      do
      #
      I_TMP=`echo $y | tr ':' '\t' | awk '{ print $1 }'`;
      E_TMP=`echo $y | tr ':' '\t' | awk '{ print $2 }'`;
      #
      printf "r\t%u\t%u\t%u\t%u\tt\t%u\t%u\t%u\t%u\n" "$I_POS" "$E_POS" "$I_POS" "$E_POS" "$I_TMP" "$E_TMP" "$I_TMP" "$E_TMP" >> rearrangements-$1-$2.csv
      #
      done
    #
    done
  #
  # REVERSE PROFILES
  #
  ./GeCo2 -v $PARAM_R -e -r SEQ1 SEQ2
  gto_upper_bound -u 2 < SEQ2.iae > SEQ_2_UB
  gto_filter -d 0 -w $WINDOW_SIZE -c < SEQ_2_UB > PROFILE_N2
  gto_segment -t 1.2 < PROFILE_N2 > $2.positions
  #
  mapfile -t LINES < $2.positions
  for line in "${LINES[@]}" # 
    do
    #
    I_POS=`echo $line | tr ':' '\t' | awk '{ print $1 }'`;
    E_POS=`echo $line | tr ':' '\t' | awk '{ print $2 }'`;
    #
    gto_genomic_extract -i $I_POS -e $E_POS < SEQ2 > REGION.g
    #
    ./GeCo2 -v $PARAM_R -e -r REGION.g SEQ1
    gto_upper_bound -u 2 < SEQ1.iae > SEQ1-UB
    gto_filter -d 0 -w $WINDOW_SIZE -c < SEQ1-UB > PROFILE-SEQ1-$I_POS-$E_POS
    gto_segment -t 1.2 < PROFILE-SEQ1-$I_POS-$E_POS > tmp-positions.csv
    #
    mapfile -t TMP < tmp-positions.csv
    #
    for y in "${TMP[@]}" #
      do
      #
      I_TMP=`echo $y | tr ':' '\t' | awk '{ print $1 }'`;
      E_TMP=`echo $y | tr ':' '\t' | awk '{ print $2 }'`;
      #
      printf "r\t%u\t%u\t%u\t%u\tt\t%u\t%u\t%u\t%u\n" "$I_POS" "$E_POS" "$I_POS" "$E_POS" "$E_TMP" "$I_TMP" "$E_TMP" "$I_TMP" >> rearrangements-$1-$2.csv
      #
      done
    #
    done
  #
  gto_comparative_map -o map.svg rearrangements-$1-$2.csv
  #
  fi
#
#
# ==============================================================================
# ==============================================================================
