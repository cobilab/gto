#!/bin/bash
gto_build_xs_viral_db.sh
gto_create_sars_dataset.sh
gto_fastq_metagenomics -v -F -l 1 reads1.fq:reads2.fq XSDB.fa
