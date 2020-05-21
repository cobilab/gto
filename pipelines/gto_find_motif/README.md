# Script: gto_find_motif.sh

This pipeline finds and localizes a motif sequence in a FASTA file. The execution of this pipeline requires: 1) the motif; and 2) a FASTA file. This is then executed as below:

```sh
gto_find_motif.sh <motif> sequence.fa 
```

The following block of code represents the essential information for this script:

```sh
...
gto_fasta_rand_extra_chars < $2 | gto_fasta_to_seq > sequence.seq;
#
gto_geco -v -e $PARAM -r motif.seq sequence.seq;
#
gto_real_to_binary_with_threshold -t 1.5 < sequence.seq.iae | tr -d -c "01" > sequence.bin
gto_fasta_variation_filter -v -w $WINDOW -u 5 -t 0.5 sequence.bin
gto_fasta_variation_visual -e $ENLARGE sequence.bin.seg
...
```

## Tools
The GTO tools used and their role in this pipeline are the following:

- **gto_fasta_rand_extra_chars**: it substitues in the DNA sequence the outside ACGT chars by ran-
dom ACGT symbols.
- **gto_fasta_to_seq**: it converts a FASTA or Multi-FASTA file format to a seq.
- **gto_geco**: it compress and decompress genomic sequences for storage purposes.
- **gto_real_to_binary_with_threshold**: it converts a sequence of real numbers into a binary sequence,
given a threshold. 
- **gto_fasta_variation_filter**:  it filters and segments the regions of singularity from a binary file.
- **gto_fasta_variation_visual**: it depites the regions of singularity using the output from gto_fastq_variation_
into an SVG image.