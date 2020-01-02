#!/bin/bash
#
# ==============================================================================
# |                                                                            |
# |             THIS PROGRAM MAPS & VISUALIZES REARRANGEMETS W GTO             |
# |             ==================================================             |
# |                                                                            |
# |            ./gto_map_rearrangements_proteins.sh seq1.fa seq2.fa            |
# |                                                                            |
# |                     FILE NEEDED TO THE COMPUTATION:                        |
# |                                                                            |
# |                $1: FILE WITH THE PROTEIN #1 IN FASTA FORMAT                |
# |                $2: FILE WITH THE PROTEIN #2 IN FASTA FORMAT                |
# |                                                                            |
# ==============================================================================
#
# ==============================================================================
# ================================ DEFINITIONS =================================
#
GET_GTO=0;
RUN_COMPARISON=1;
PARAM=" -t 1 -rm 11:200:0.9/6:50:0.95 -rm 6:100:0.9/3:10:0.9 ";
THRESHOLD="3.5";
UPPER_BOUND="5";
GUARD="20";
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
  #
  grep -v ">" $1 | tr -d "\n" > SEQ1;
  grep -v ">" $2 | tr -d "\n" > SEQ2;
  #
  # GET WINDOW SIZE BY SEQUENCE SIZE FOR 1
  LENGTH1=`gto_info < SEQ1 | grep "Number of sym" | awk '{ print $5}'`;
  LENGTH2=`gto_info < SEQ2 | grep "Number of sym" | awk '{ print $5}'`;
  #
  echo "#SCF $LENGTH1 $LENGTH2" > rearrangements-$1-$2.csv;
  #
  if [[ "$LENGTH1" -gt "2000" ]];
    then
    WINDOW_SIZE=`echo "$LENGTH1 / 1000" | bc`;
    else
    WINDOW_SIZE=5;
  fi
  #
  echo "WINDOW SIZE: $WINDOW_SIZE";
  #
  gto_amino_acid_compressor -v $PARAM -e -r SEQ1 SEQ2
  gto_upper_bound -u $UPPER_BOUND < SEQ2.iae > SEQ_2_UB
  gto_filter -d 0 -w $WINDOW_SIZE -c < SEQ_2_UB > PROFILE_N2
  gto_segment -t $THRESHOLD < PROFILE_N2 > $2.positions
  #
  mapfile -t LINES < $2.positions
  for line in "${LINES[@]}" # 
    do
    #
    I_POS=`echo $line | tr ':' '\t' | awk '{ print $1 }'`;
    E_POS=`echo $line | tr ':' '\t' | awk '{ print $2 }'`;
    #
    if [[ "$I_POS" -gt "$GUARD" ]];
      then
      I_POS_GUARD=`echo "$I_POS-$GUARD" | bc`;
      else
      I_POS_GUARD="1";
      fi
    #
    MAX_EPOS=`echo "$LENGTH2-$GUARD" | bc`;
    LM1=`echo "$LENGTH2-1" | bc`;
    if [[ "$E_POS" -gt "$MAX_EPOS" ]];
      then
      E_POS_GUARD=`echo "$LM1"`;
      else
      E_POS_GUARD=`echo "$E_POS+$GUARD" | bc`;
      fi
    #
    gto_genomic_extract -i $I_POS_GUARD -e $E_POS_GUARD < SEQ2 > REGION.g
    #
    gto_amino_acid_compressor -v $PARAM -e -r REGION.g SEQ1
    gto_upper_bound -u $UPPER_BOUND < SEQ1.iae > SEQ1-UB
    gto_filter -d 0 -w $WINDOW_SIZE -c < SEQ1-UB > PROFILE-SEQ1-$I_POS-$E_POS
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
      printf "r\t%u\t%u\t%u\t%u\tt\t%u\t%u\t%u\t%u\n" "$I_POS" "$E_POS" "$I_POS" "$E_POS" "$I_TMP" "$E_TMP" "$I_TMP" "$E_TMP" >> rearrangements-$1-$2.csv
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
~                                                                                  
