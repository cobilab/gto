# Script: gto_relative_complexity_profile.sh

This pipeline computes relative complexity profiles. The execution of this pipeline requires two FASTA files, and this is then executed as follows:

```sh
gto_relative_complexity_profile seqA.fa SeqB.fa
```

The following block of code represents the essential information for this script:

```sh
...
gto_fasta_rand_extra_chars < $2 | gto_fasta_to_seq > SEQ;

LENGTH=`gto_info < SEQ | grep "Number of sym" | awk '{ print $5}'`;
echo "WINDOW SIZE: $WINDOW_SIZE";

gto_geco -v $LEVEL -e -r $1 SEQ

gto_upper_bound -u 2 < SEQ.iae   > SEQ_UB
gto_filter -d 0 -w $WINDOW_SIZE -c < SEQ_UB > FIL_UB.x
gto_segment -t 1 < FIL_UB.x > $1.positions
...  
```

## Tools
The GTO tools used and their role in this pipeline are the following:

- **gto_fasta_rand_extra_chars**:  it substitues in the DNA sequence the outside ACGT chars by random ACGT symbols.
- **gto_fasta_to_seq**: it converts a FASTA or Multi-FASTA file format to a seq.
- **gto_info**: it gives the basic properties of the file, namely size, cardinality, distribution percentage of
- **gto_geco**:  it is a lossless compressor to compress efficiently amino acid sequences, using a cooperation between multiple context and substitutional tolerant context models. 
- **gto_upper_bound**:
- **gto_filter**: it filters numerical sequences using a low-pass filter.
- **gto_segment**: it segments a filtered sequence based on a threshold.

