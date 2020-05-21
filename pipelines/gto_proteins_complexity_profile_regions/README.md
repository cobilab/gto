# Script: gto_proteins_complexity_profile_regions.sh

This pipeline computes the bi-directional complexity profiles in any proteominc sequences. These profiles can localise specific features in the sequences, namely low and high complexity sequences, inverted repeats regions, tandem duplications, among others. The construction of these profiles follows the pipeline described below, which is composed of several transformations (e.g. reversing, segmenting, inverting) as well as the use of specific low-pass filters after data compression applications. The execution of this pipeline requires a FASTA file, and this is then executed as below:

```sh
gto_proteins_complexity_profile_regions seq.fa
```

The following block of code represents the essential information for this script:

```sh
...
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
...
```

## Tools
The GTO tools used and their role in this pipeline are the following:

- **gto_reverse**: it reverses the ACGT bases order for each read in a sequence file.
- **gto_amino_acid_compressor**:  it is a lossless compressor to compress efficiently amino acid sequences, using a cooperation between multiple context and substitutional tolerant context models. 
- **gto_filter**: it filters numerical sequences using a low-pass filter.
- **gto_min**: it computes the minimum value in each row between two files.
- **gto_segment**: it segments a filtered sequence based on a threshold.
