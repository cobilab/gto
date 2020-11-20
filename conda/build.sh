#! /bin/bash
#export C_INCLUDE_PATH=$C_INCLUDE_PATH:${PREFIX}/include
#export LIBRARY_PATH=$LIBRARY_PATH:${PREFIX}/lib

cd src/
make progs geco xs ac falcon chester 
cd ..

mkdir -p "$PREFIX/bin"
cp scripts/gto_build_dbs.sh $PREFIX/bin/

cp pipelines/gto_complexity_profile_regions/gto_complexity_profile_regions.sh $PREFIX/bin/
cp pipelines/gto_complexity_profiles/gto_complexity_profiles.sh $PREFIX/bin/
cp pipelines/gto_create_viral_dataset/gto_create_viral_dataset.sh $PREFIX/bin/
cp pipelines/gto_find_motif/gto_find_motif.sh $PREFIX/bin/
cp pipelines/gto_map_rearrangements/gto_map_rearrangements.sh $PREFIX/bin/
cp pipelines/gto_map_rearrangements_proteins/gto_map_rearrangements_proteins.sh $PREFIX/bin/
cp pipelines/gto_metagenomics/gto_metagenomics.sh $PREFIX/bin/
cp pipelines/gto_proteins_complexity_profile_regions/gto_proteins_complexity_profile_regions.sh $PREFIX/bin/
cp pipelines/gto_simulate_rearragements/gto_simulate_rearragements.sh $PREFIX/bin/
cp pipelines/gto_merge_fasta_dbs/gto_merge_fasta_dbs.sh $PREFIX/bin/
cp pipelines/gto_build_xs_viral_db/gto_build_xs_viral_db.sh $PREFIX/bin/
cp pipelines/gto_create_sars_dataset/gto_create_sars_dataset.sh $PREFIX/bin/
cp pipelines/gto_sars_simulation_detection/gto_sars_simulation_detection.sh $PREFIX/bin/
cp pipelines/gto_download_sars2/gto_download_sars2.sh $PREFIX/bin/
cp pipelines/gto_find_best_sars2/gto_find_best_sars2.sh $PREFIX/bin/
cp pipelines/gto_relative_complexity_profile/gto_relative_complexity_profile.sh $PREFIX/bin/


cp bin/gto $PREFIX/bin/
cp bin/gto_amino_acid_compressor $PREFIX/bin/
cp bin/gto_amino_acid_decompressor $PREFIX/bin/
cp bin/gto_amino_acid_from_fasta $PREFIX/bin/
cp bin/gto_amino_acid_from_fastq $PREFIX/bin/
cp bin/gto_amino_acid_from_seq $PREFIX/bin/
cp bin/gto_amino_acid_to_group $PREFIX/bin/
cp bin/gto_amino_acid_to_pseudo_dna $PREFIX/bin/
cp bin/gto_brute_force_string $PREFIX/bin/
cp bin/gto_char_to_line $PREFIX/bin/
cp bin/gto_comparative_map $PREFIX/bin/
cp bin/gto_fasta_complement $PREFIX/bin/
cp bin/gto_fasta_extract $PREFIX/bin/
cp bin/gto_fasta_extract_by_read $PREFIX/bin/
cp bin/gto_fasta_extract_pattern_coords $PREFIX/bin/
cp bin/gto_fasta_extract_read_by_pattern $PREFIX/bin/
cp bin/gto_fasta_find_n_pos $PREFIX/bin/
cp bin/gto_fasta_from_seq $PREFIX/bin/
cp bin/gto_fasta_get_unique $PREFIX/bin/
cp bin/gto_fasta_info $PREFIX/bin/
cp bin/gto_fasta_mutate $PREFIX/bin/
cp bin/gto_fasta_rand_extra_chars $PREFIX/bin/
cp bin/gto_fasta_rename_human_headers $PREFIX/bin/
cp bin/gto_fasta_reverse $PREFIX/bin/
cp bin/gto_fasta_split_reads $PREFIX/bin/
cp bin/gto_fasta_to_seq $PREFIX/bin/
cp bin/gto_fasta_variation_filter $PREFIX/bin/
cp bin/gto_fasta_variation_map $PREFIX/bin/
cp bin/gto_fasta_variation_visual $PREFIX/bin/
cp bin/gto_fastq_complement $PREFIX/bin/
cp bin/gto_fastq_cut $PREFIX/bin/
cp bin/gto_fastq_exclude_n $PREFIX/bin/
cp bin/gto_fastq_extract_quality_scores $PREFIX/bin/
cp bin/gto_fastq_from_seq $PREFIX/bin/
cp bin/gto_fastq_info $PREFIX/bin/
cp bin/gto_fastq_maximum_read_size $PREFIX/bin/
cp bin/gto_fastq_metagenomics $PREFIX/bin/
cp bin/gto_fastq_minimum_local_quality_score_forward $PREFIX/bin/
cp bin/gto_fastq_minimum_local_quality_score_reverse $PREFIX/bin/
cp bin/gto_fastq_minimum_quality_score $PREFIX/bin/
cp bin/gto_fastq_minimum_read_size $PREFIX/bin/
cp bin/gto_fastq_mutate $PREFIX/bin/
cp bin/gto_fastq_pack $PREFIX/bin/
cp bin/gto_fastq_quality_score_info $PREFIX/bin/
cp bin/gto_fastq_quality_score_max $PREFIX/bin/
cp bin/gto_fastq_quality_score_min $PREFIX/bin/
cp bin/gto_fastq_rand_extra_chars $PREFIX/bin/
cp bin/gto_fastq_reverse $PREFIX/bin/
cp bin/gto_fastq_split $PREFIX/bin/
cp bin/gto_fastq_to_fasta $PREFIX/bin/
cp bin/gto_fastq_to_mfasta $PREFIX/bin/
cp bin/gto_fastq_unpack $PREFIX/bin/
cp bin/gto_fastq_variation_filter $PREFIX/bin/
cp bin/gto_fastq_variation_map $PREFIX/bin/
cp bin/gto_fastq_variation_visual $PREFIX/bin/
cp bin/gto_fastq_xs $PREFIX/bin/
cp bin/gto_filter $PREFIX/bin/
cp bin/gto_geco $PREFIX/bin/
cp bin/gto_gede $PREFIX/bin/
cp bin/gto_genomic_complement $PREFIX/bin/
cp bin/gto_genomic_compressor $PREFIX/bin/
cp bin/gto_genomic_count_bases $PREFIX/bin/
cp bin/gto_genomic_decompressor $PREFIX/bin/
cp bin/gto_genomic_dna_mutate $PREFIX/bin/
cp bin/gto_genomic_extract $PREFIX/bin/
cp bin/gto_genomic_gen_random_dna $PREFIX/bin/
cp bin/gto_genomic_period $PREFIX/bin/
cp bin/gto_genomic_rand_seq_extra_chars $PREFIX/bin/
cp bin/gto_genomic_reverse $PREFIX/bin/
cp bin/gto_genomic_variation_filter $PREFIX/bin/
cp bin/gto_genomic_variation_map $PREFIX/bin/
cp bin/gto_genomic_variation_visual $PREFIX/bin/
cp bin/gto_info $PREFIX/bin/
cp bin/gto_lower_bound $PREFIX/bin/
cp bin/gto_max $PREFIX/bin/
cp bin/gto_min $PREFIX/bin/
cp bin/gto_new_line_on_new_x $PREFIX/bin/
cp bin/gto_permute_by_blocks $PREFIX/bin/
cp bin/gto_real_to_binary_with_threshold $PREFIX/bin/
cp bin/gto_reverse $PREFIX/bin/
cp bin/gto_segment $PREFIX/bin/
cp bin/gto_sum $PREFIX/bin/
cp bin/gto_upper_bound $PREFIX/bin/
cp bin/gto_word_search $PREFIX/bin/
cp bin/gto_fasta_split_streams $PREFIX/bin/
cp bin/gto_fasta_merge_streams $PREFIX/bin/
