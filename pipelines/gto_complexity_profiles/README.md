# Script: gto_complexity_profiles.sh

This pipeline computes complexity and relative complexity profiles in any genomic sequences. The pipeline gto_complexity_profile_regions is an improved version of this pipeline. However, the execution of this pipeline requires: 1) a file with the genomes ids (GID); 2) a reference data set; and 3) a FASTQ file. This is then executed as follows:

```sh
gto_complexity_profiles.sh ids.txt VDB.fa reads.fq 
```

The following block of code represents the essential information for this script:

```sh
...
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
...
```

## Tools
The GTO tools used and their role in this pipeline are the following:

- **gto_fasta_extract_read_by_pattern**:  it extracts reads from a Multi-FASTA file format given a
pattern in the header.
- **gto_fasta_rand_extra_chars**: it substitues in the DNA sequence the outside ACGT chars by ran-
dom ACGT symbols.
- **gto_reverse**: it reverses the ACGT bases order for each read in a sequence file.
- **gto_geco**: it compress and decompress genomic sequences for storage purposes.
- **gto_upper_bound**: it sets an upper bound in a file with a value per line.
- **gto_filter**: it filters numerical sequences using a low-pass filter.
- **gto_min**: it computes the minimum value in each row between two files.
- **gto_fasta_to_seq**: it converts a FASTA or Multi-FASTA file format to a seq.


