# Script: gto_sars_simulation_detection

This pipeline builds a small FASTA database (viral references + human mitogenome), creates a FASTQ dataset containning SARS and the human mitogenome (among others), and maps the existence of the virus and human. This is executed as follows:

```sh
gto_sars_simulation_detection.sh
```

## Tools
The GTO tools used and their role in this pipeline are the following:

- **gto_build_xs_viral_db.sh**:  it builds a tiny FASTA database.
- **gto_create_sars_dataset.sh**: it creates a sars (sars-cov-2) dataset with other viruses and a human mitogenome.
- **gto_fastq_metagenomics**:  it maps the metagenomic composition.
