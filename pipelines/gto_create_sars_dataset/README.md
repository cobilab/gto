# Script: gto_create_sars_dataset.sh

This pipeline creates a viral dataset considering the following set of ids:  "AY386330.1", "JN561323.2", "X04370.1", "MT007544", "AB041963.1", "MG921180.1", "NC_012920.1". This is executed as follows:

```sh
gto_create_sars_dataset.sh
```

## Tools
The GTO tools used and their role in this pipeline are the following:

- **gto_fasta_mutate**:  it creates a synthetic mutation of a FASTA file given specific rates of editions, deletions and additions.
- **gto_permute_by_blocks**:  it permutates by block sequence, FASTA and Multi-FASTA files.
- **gto_genomic_gen_random_dna**:  it generates a synthetic DNA.
