# Script: gto_simulate_rearragements.sh

This pipeline simulates genome rearrangements, that can be used to test other pipelines.

```sh
gto_simulate_rearragements.sh
```

The following block of code represents the essential information for this script:

```sh
gto_genomic_gen_random_dna -s 0   -n 1000 > A.g
gto_genomic_gen_random_dna -s 7   -n 1000 > B.g
gto_genomic_gen_random_dna -s 11  -n 1000 > C.g
gto_genomic_gen_random_dna -s 63  -n 1000 > D.g
gto_genomic_gen_random_dna -s 102 -n 1000 > E.g
#
cat A.g B.g C.g D.g E.g | gto_fasta_from_seq -n A > A.fa
#
gto_genomic_reverse < B.g | gto_genomic_complement > R_B.g
gto_genomic_reverse < D.g | gto_genomic_complement > R_D.g
#
cat A.g R_B.g C.g R_D.g E.g > ALL.g
#
gto_permute_by_blocks -b 500 -s 0 < ALL.g | gto_fasta_from_seq -n B > B.fa
```

## Tools
The GTO tools used and their role in this pipeline are the following:

- **gto_genomic_gen_random_dna**: it generates a synthetic DNA.
- **gto_fasta_from_seq**: it converts a genomic sequence to pseudo FASTA file format.
- **gto_genomic_reverse**: it reverses the ACGT bases order for each read in a sequence file.
- **gto_genomic_complement**: it replaces the ACGT bases with their complements in a DNA sequence.
- **gto_permute_by_blocks**: it permutates by block sequence, FASTA and Multi-FASTA files.