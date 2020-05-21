# Script: gto_map_rearrangements_proteins.sh

This pipeline is a variation of the  gto_map_rearrangements.sh but designed for proteins. This loads the two FASTA files into the mapping pipeline and the output is two files, one with the mapping positions and the other is an SVG image depicting the mapped positions. The execution of this pipeline is done as follows:

```sh
gto_map_rearrangements_proteins.sh seq1.fa seq2.fa
```

The following block of code represents the essential information for this script:

```sh
...
gto_genomic_extract -i $I_POS_GUARD -e $E_POS_GUARD < SEQ2 > REGION.g
#
gto_amino_acid_compressor -v $PARAM -e -r REGION.g SEQ1
gto_upper_bound -u $UPPER_BOUND < SEQ1.iae > SEQ1-UB
gto_filter -d 0 -w $WINDOW_SIZE -c < SEQ1-UB > PROFILE-SEQ1-$I_POS-$E_POS
gto_segment -t $THRESHOLD < PROFILE-SEQ1-$I_POS-$E_POS > tmp-positions.csv
...
gto_comparative_map -o map.svg rearrangements-$1-$2.csv
...
```

## Tools
The GTO tools used and their role in this pipeline are the following:

- **gto_info**: it gives the basic properties of the file, namely size, cardinality, distribution percentage of
the symbols, among others.
- **gto_genomic_extract**: it extracts sequences from a sequence file, which the range is defined by the
user in the parameters.
- **gto_amino_acid_compressor**:  it is a lossless compressor to compress efficiently amino acid sequences, using a cooperation between multiple context and substitutional tolerant context models. 
- **gto_upper_bound**: it sets an upper bound in a file with a value per line.
- **gto_filter**: it filters numerical sequences using a low-pass filter.
- **gto_segment**: it segments a filtered sequence based on a threshold.
- **gto_comparative_map**:  it creates a visualization (SVG file) for comparative maps.

