# Script: gto_map_rearrangements.sh

This pipeline applies smash technology for mapping the rearrangements in genomic sequences using an alignment-free methodology. This loads the two FASTA files into the mapping pipeline and the output is two files, one with the mapping positions and the other is an SVG image depicting the mapped positions. The execution of this pipeline is done as follows:

```sh
gto_map_rearrangements.sh seq1.fa seq2.fa
```

The following block of code represents the essential information for this script:

```sh
...
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
...
gto_comparative_map -o map.svg rearrangements-$1-$2.csv
...
```

## Tools
The GTO tools used and their role in this pipeline are the following:

- **gto_fasta_rand_extra_chars**: it substitues in the DNA sequence the outside ACGT chars by ran-
dom ACGT symbols.
- **gto_fasta_to_seq**: it converts a FASTA or Multi-FASTA file format to a seq.
- **gto_info**: it gives the basic properties of the file, namely size, cardinality, distribution percentage of
the symbols, among others.
- **gto_geco**: it compress and decompress genomic sequences for storage purposes.
- **gto_upper_bound**: it sets an upper bound in a file with a value per line.
- **gto_filter**: it filters numerical sequences using a low-pass filter.
- **gto_segment**: it segments a filtered sequence based on a threshold.
- **gto_genomic_extract**: it extracts sequences from a sequence file, which the range is defined by the
user in the parameters.
- **gto_comparative_map**:  it creates a visualization (SVG file) for comparative maps.

