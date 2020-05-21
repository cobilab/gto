# Script: gto_create_viral_dataset.sh

This pipeline creates a viral dataset considering the following set of ids:  "AY386330.1", "JN561323.2", "X04370.1", "DQ279927.1", "X69198.1", "AB041963.1", "MG921180.1". This is executed as follows:
```sh
gto_create_viral_dataset.sh
```

## Tools
The GTO tools used and their role in this pipeline are the following:

- **gto_fasta_mutate**:  it creates a synthetic mutation of a FASTA file given specific rates of editions, deletions and additions.
- **gto_permute_by_blocks**:  it permutates by block sequence, FASTA and Multi-FASTA files.
- **gto_genomic_gen_random_dna**:  it generates a synthetic DNA.
- **gto_fastq_metagenomics**: it is an ultra-fast method to infer metagenomic composition of sequenced reads
relative to a database. 
