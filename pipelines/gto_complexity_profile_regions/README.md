# Script: gto_complexity_profile_regions.sh

This pipeline computes the bi-directional complexity profiles in any genomic sequences. These profiles can localise specific features in the sequences, namely low and high complexity sequences, inverted repeats regions, tandem duplications, among others. The construction of these profiles follows the pipeline described below, which is composed of several transformations (e.g. reversing, segmenting, inverting) as well as the use of specific low-pass filters after data compression applications. The execution of this pipeline requires: 1) a FASTA file; and 2) the level of compression. This is then executed as below:

```sh
gto_complexity_profile_regions.sh sequence.fa level
```

The following block of code represents the essential information for this script:

```sh
...
gto_fasta_rand_extra_chars < $1 | gto_fasta_to_seq > SEQ;
gto_reverse < SEQ > SEQ_R;
#
# GET WINDOW SIZE BY SEQUENCE SIZE
LENGTH=`gto_info < SEQ | grep "Number of sym" | awk '{ print $5}'`;
WINDOW_SIZE=`echo "$LENGTH / 1000" | bc`;
echo "WINDOW SIZE: $WINDOW_SIZE";
#
gto_geco -v -l $LEVEL -e SEQ
gto_geco -v -l $LEVEL -e SEQ_R
#
gto_upper_bound -u 2 < SEQ.iae   > SEQ_UB
gto_upper_bound -u 2 < SEQ_R.iae > SEQ_R_UB
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
gto_segment -t 1 < PROFILE_N > $1.positions
...
```

## Tools
The GTO tools used and their role in this pipeline are the following:

- **gto_fasta_rand_extra_chars**: it substitues in the DNA sequence the outside ACGT chars by ran-
dom ACGT symbols.
- **gto_fasta_to_seq**: it converts a FASTA or Multi-FASTA file format to a seq.
- **gto_reverse**: it reverses the ACGT bases order for each read in a sequence file.
- **gto_geco**: it compress and decompress genomic sequences for storage purposes.
- **gto_upper_bound**: it sets an upper bound in a file with a value per line.
- **gto_filter**: it filters numerical sequences using a low-pass filter.
- **gto_min**: it computes the minimum value in each row between two files.
- **gto_segment**: it segments a filtered sequence based on a threshold.


