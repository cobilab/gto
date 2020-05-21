# Script: gto_metagenomics.sh

This pipeline automatically identifies metagenomic viral (or any other) content in FASTQ reads. This includes the filtering and trimming of the reads, mapping, and sensitive identification of the most representative genomes, under a ranking of abundance. The execution of this pipeline requires: 1) two FASTA file; and 2) a dataset for comparison, which is built using the pipeline gto_create_viral_dataset. This is then executed as follows:

```sh
gto_metagenomics.sh reads1.fq reads2.fq VDB.fa
```

The following block of code represents the essential information for this script:

```sh
...
gto_fastq_minimum_local_quality_score_forward -k 5 -w 25 -m 33 < $2 \
| gto_fastq_exclude_n -m 5 \
| gto_fastq_minimum_read_size -s 30 > filt-$2
#
gto_fastq_metagenomics -F -t 200 -v -n 8 filt-$1:filt-$2 $3
...
```

## Tools
The GTO tools used and their role in this pipeline are the following:

- **gto_fastq_minimum_local_quality_score_forward**:  it filters the reads considering the quality score
average of a defined window size of bases.
- **gto_fastq_exclude_n**:  it discards the FASTQ reads with the minimum number of "N" symbols.
- **gto_fastq_minimum_read_size**:  it filters the FASTQ reads with the length smaller than the value
defined.
- **gto_fastq_metagenomics**: it is an ultra-fast method to infer metagenomic composition of sequenced reads
relative to a database. 


