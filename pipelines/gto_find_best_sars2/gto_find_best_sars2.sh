#!/bin/bash
gto_create_sars_dataset.sh # PE reads with MT007544 SARS-CoV-2 
#
gto_download_sars2.sh # 93 SARS-CoV-2 genome sequences
#
gto_fastq_metagenomics -v -F -l 47 reads1.fq:reads2.fq SARS-CoV-2.fa
