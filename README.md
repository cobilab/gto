[![Build Status](https://travis-ci.org/cobilab/gto.svg?branch=master)](https://travis-ci.org/cobilab/gto)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/53c822299f6841fbb7680d065be5b796)](https://www.codacy.com/app/pratas/GTO?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=pratas/GTO&amp;utm_campaign=Badge_Grade)
[![License: MIT](https://img.shields.io/github/license/mashape/apistatus.svg)](LICENSE)

<p align="center"><img src="imgs/logo.png"
alt="GTO" height="74" border="0" /></p>

<p align="center"><b>The genomics toolkit</b></p>

## INSTALL

### 1.1 Automatic installation with [Conda](https://conda.io/miniconda) ###

```
conda install -c cobilab gto --yes
```

### 1.2 Manual installation ###

```bash
git clone https://github.com/bioinformatics-ua/gto.git
cd gto/src/
make
```
Note, an already compiled version of GTO is available for 64 bit Linux OS in
the `bin/` directory.

## GTO Programs

The GTO provides pipe support for easy integration with the majority of the tools. These include programs to shuffle, transform, simulate, compress, vizualize, among others. The GTO includes the following tools, divided by genomic data format type.

### 1. FASTQ tools

```bash
1.1 gto_fastq_to_fasta
1.2 gto_fastq_to_mfasta
1.3 gto_fastq_exclude_n
1.4 gto_fastq_extract_quality_scores
1.5 gto_fastq_info
1.6 gto_fastq_maximum_read_size
1.7 gto_fastq_minimum_quality_score
1.8 gto_fastq_minimum_read_size
1.9 gto_fastq_rand_extra_chars
1.10 gto_fastq_from_seq
1.11 gto_fastq_mutate
1.12 gto_fastq_split
1.13 gto_fastq_pack
1.14 gto_fastq_unpack
1.15 gto_fastq_quality_score_info
1.16 gto_fastq_quality_score_max
1.17 gto_fastq_quality_score_min
1.18 gto_fastq_cut
1.19 gto_fastq_minimum_local_quality_score_forward
1.20 gto_fastq_minimum_local_quality_score_reverse
1.21 gto_xs
1.22 gto_fastq_clust_reads
1.23 gto_fastq_complement
1.24 gto_fastq_reverse
1.25 gto_fastq_variation_map
1.26 gto_fastq_variation_filter
1.27 gto_fastq_variation_visual
1.28 gto_fastq_metagenomics
```

### 2. FASTA tools

```bash
2.1 gto_fasta_to_seq
2.2 gto_fasta_from_seq
2.3 gto_fasta_extract
2.4 gto_fasta_extract_by_read
2.5 gto_fasta_info
2.6 gto_fasta_mutate
2.7 gto_fasta_rand_extra_chars
2.8 gto_fasta_extract_read_by_pattern
2.9 gto_fasta_find_n_pos
2.10 gto_fasta_split_reads
2.11 gto_fasta_rename_human_headers
2.12 gto_fasta_extract_pattern_coords
2.13 gto_fasta_complement
2.14 gto_fasta_reverse
2.15 gto_fasta_variation_map
2.16 gto_fasta_variation_filter
2.17 gto_fasta_variation_visual
```

### 3. Genomic sequence tools

```bash
3.1 gto_genomic_gen_random_dna
3.2 gto_genomic_rand_seq_extra_chars
3.3 gto_genomic_dna_mutate
3.4 gto_genomic_extract
3.5 gto_genomic_period
3.6 gto_genomic_count_bases
3.7 gto_genomic_compressor (also under the alias gto_geco)
3.8 gto_genomic_decompressor (also under the alias gto_gede)
3.9 gto_genomic_complement
3.10 gto_genomic_reverse (also under the alias gto_reverse)
3.11 gto_genomic_variation_map
3.12 gto_genomic_variation_filter
3.13 gto_genomic_variation_visual
```

### 4. Amino acid sequence tools

```bash
4.1 gto_amino_acid_to_group
4.2 gto_amino_acid_to_pseudo_dna
4.3 gto_amino_acid_compressor
4.4 gto_amino_acid_decompressor
```


### 5. General purpose tools

```bash
5.1 gto_char_to_line
5.2 gto_new_line_on_new_x
5.3 gto_upper_bound
5.4 gto_lower_bound
5.5 gto_brute_force_string
5.6 gto_real_to_binary_with_threshold
5.7 gto_sum
5.8 gto_filter
5.9 gto_word_search
5.10 gto_permute_by_blocks
5.11 gto_info
5.12 gto_segment
5.13 gto_comparative_map
5.14 gto_max
5.15 gto_min
``` 

### 6. Scripts
```bash
6.1 gto_build_dbs.sh
```

## CITE
Please cite the followings, if you use GTO:
J. R. Almeida, D. Pratas. GTO: the genomics toolkit, 2018.

## ISSUES
Please let us know if there is any
[issues](https://github.com/bioinformatics-ua/gto/issues).

## LICENSE
GTO is under MIT license. For more information, click
[here](https://opensource.org/licenses/MIT).
