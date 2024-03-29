#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

int main(int argc, char *argv[])
{
  fprintf(stderr, 
  "                                                                          \n"
  "                                                                          \n"
  "      ████████ ████████ ████████                                          \n"
  "      ██          ██    ██    ██                                          \n"
  "      ██  ████    ██    ██    ██                                          \n"
  "      ██    ██    ██    ██    ██                                          \n"
  "      ████████    ██    ████████                                          \n"
  "                                                                          \n"
  "NAME                                                                      \n"
  "      GTO v1.6.2,                                                         \n"
  "      The Genomics-Proteomics Toolkit.                                    \n"
  "                                                                          \n"
  "AUTHORS                                                                   \n"
  "      João R. Almeida     joao.rafael.almeida@ua.pt                       \n"
  "      Armando Pinho       ap@ua.pt                                        \n"
  "      José L. Oliveira    jlo@ua.pt                                       \n"
  "      Olga Fajarda        olga.oliveira@ua.pt                             \n"
  "      Diogo Pratas        pratas@ua.pt                                    \n"
  "                                                                          \n"
  "SYNOPSIS                                                                  \n"
  "      gto_[PROGRAM]                                                       \n"
  "                                                                          \n"
  "SAMPLE                                                                    \n"
  "      Run Info:  gto_info < sequence.txt                                  \n"
  "                                                                          \n"
  "DESCRIPTION                                                               \n"
  "      A complete set of efficient tools for genomics & proteomics.        \n"
  "      The gto works as the \"LEGOs\", since it allows multiple            \n"
  "      combinations through the usage of multiple programs with            \n"
  "      pipes. The gto includes multiple functions, such as view,           \n"
  "      convert, compress, simulate, analyze, invert, modify, and           \n"
  "      many others. GTO is under MIT license.                              \n"
  "                                                                          \n"
  "PROGRAMS                                                                  \n"
  "      [gto_info]                                                          \n"
  "          It gives the basic properties of the file, namely               \n"
  "          size, cardinality, distribution percentage of the               \n"
  "          symbols, among others.                                          \n"
  "                                                                          \n"
  "Amino Acid Sequence Tools                                                 \n"
  "      [gto_amino_acid_compressor]                                         \n"
  "          It is a new lossless compressor to compress efficiently         \n"
  "          amino acid sequences (proteins).                                \n"
  "                                                                          \n"
  "      [gto_amino_acid_decompressor]                                       \n"
  "          It decompresses the result of gto_amino_acid_compressor.        \n"
  "                                                                          \n"
  "      [gto_amino_acid_from_fasta]                                         \n"
  "          It converts FASTA or Multi-FASTA file format to an amino acid   \n"
  "          sequence (translation).                                         \n"
  "                                                                          \n"
  "      [gto_amino_acid_from_fastq]                                         \n"
  "          It converts FASTQ file format to an amino acid sequence         \n"
  "          (translation).                                                  \n"
  "                                                                          \n"
  "      [gto_amino_acid_from_seq]                                           \n"
  "          It converts DNA sequence to an amino acid sequence              \n"
  "          (translation).                                                  \n"
  "                                                                          \n"
  "      [gto_amino_acid_to_group]                                           \n"
  "          It converts an amino acid sequence to a group sequence.         \n"
  "                                                                          \n"
  "      [gto_amino_acid_to_pseudo_dna]                                      \n"
  "          It converts an amino acid (protein) sequence to a               \n"
  "          pseudo DNA sequence.                                            \n"
  "                                                                          \n"
  "FASTQ Tools                                                               \n"
  "      [gto_fastq_clust_reads]                                             \n"
  "          It agroups reads and creates an index file.                     \n"
  "                                                                          \n"
  "      [gto_fastq_complement]                                              \n"
  "          It replaces the ACGT bases with their complements in a          \n"
  "          FASTQ file format.                                              \n"
  "                                                                          \n"
  "      [gto_fastq_cut]                                                     \n"
  "          It cuts read sequences in a FASTQ file.                         \n"
  "                                                                          \n"
  "      [gto_fastq_exclude_n]                                               \n"
  "          It discards the FASTQ reads with the minimum number of          \n" 
  "          \"N\" symbols.                                                  \n"
  "                                                                          \n"
  "      [gto_fastq_extract_quality_scores]                                  \n"
  "          It extracts all the quality-scores from FASTQ reads.            \n"
  "                                                                          \n"
  "      [gto_fastq_from_seq]                                                \n"
  "          It converts a genomic sequence to pseudo FASTQ file             \n"
  "          format.                                                         \n"
  "                                                                          \n"
  "      [gto_fastq_info]                                                    \n" 
  "          It analyses the basic information of FASTQ file format.         \n"
  "                                                                          \n"
  "      [gto_fastq_maximum_read_size]                                       \n"
  "          It filters the FASTQ reads with the length higher than          \n"
  "          the value defined.                                              \n"
  "                                                                          \n"
  "      [gto_fastq_metagenomics]                                            \n"
  "          It infers metagenomic sample composition of sequenced reads.    \n"
  "                                                                          \n"
  "      [gto_fastq_minimum_local_quality_score_forward]                     \n"
  "          It ilters the reads considering the quality score               \n"
  "          average of a defined window size of bases.                      \n"
  "                                                                          \n"
  "      [gto_fastq_minimum_local_quality_score_reverse]                     \n"
  "          It filters the reverse reads, considering the average           \n"
  "          window size score defined by the bases.                         \n"
  "                                                                          \n"
  "      [gto_fastq_minimum_quality_score]                                   \n"
  "          It discards reads with average quality-score below of           \n"
  "          the defined.                                                    \n"
  "                                                                          \n"
  "      [gto_fastq_minimum_read_size]                                       \n"
  "          It filters the FASTQ reads with the length smaller than         \n"
  "          the value defined.                                              \n"
  "                                                                          \n"
  "      [gto_fastq_mutate]                                                  \n" 
  "          It creates a synthetic mutation of a FASTQ file given           \n"
  "          specific rates of mutations, deletions and additions.           \n"
  "                                                                          \n"
  "      [gto_fastq_pack]                                                    \n"
  "          It packages each FASTQ read in a single line.                   \n"
  "                                                                          \n"
  "      [gto_fastq_quality_score_info]                                      \n"
  "          Iit analyses the quality-scores of a FASTQ file.                \n"
  "                                                                          \n"
  "      [gto_fastq_quality_score_max]                                       \n"
  "          It analyses the maximal quality-scores of a FASTQ file.         \n"
  "                                                                          \n"
  "      [gto_fastq_quality_score_min]                                       \n"
  "          It analyses the minimal quality-scores of a FASTQ file.         \n"
  "                                                                          \n"
  "      [gto_fastq_rand_extra_chars]                                        \n"
  "          It substitues in the FASTQ files, the DNA sequence the          \n"
  "          outside ACGT chars by random ACGT symbols.                      \n"
  "                                                                          \n"
  "      [gto_fastq_reverse]                                                 \n"
  "          It reverses the ACGT bases order for each read in a FASTQ       \n"
  "          file.                                                           \n"
  "                                                                          \n"
  "      [gto_fastq_split]                                                   \n"
  "          It splits Paired End files according to the direction           \n"
  "          of the strand ('/1' or '/2').                                   \n"
  "                                                                          \n"
  "      [gto_fastq_to_fasta]                                                \n"
  "          It converts a FASTQ file into a FASTA file format.              \n"
  "                                                                          \n"
  "      [gto_fastq_to_mfasta]                                               \n"
  "          It converts a FASTQ file format to a pseudo Multi-FASTA         \n"
  "          file.                                                           \n"
  "                                                                          \n"
  "      [gto_fastq_unpack]                                                  \n"
  "          It unpacks the FASTQ reads packaged using the                   \n"
  "          gto_fastq_pack tool.                                            \n"
  "                                                                          \n"
  "      [gto_fastq_variation_filter]                                        \n"
  "          It uses the Chester-filter to filter maps.                      \n"
  "                                                                          \n"
  "      [gto_fastq_variation_map]                                           \n"
  "          It uses the Chester-map to map relative singularity regions.    \n"
  "                                                                          \n"
  "      [gto_fastq_variation_visual]                                        \n"
  "          It uses the Chester-visual to visualize relative singularity    \n"
  "          regions.                                                        \n"
  "                                                                          \n"
  "      [gto_fastq_xs]                                                      \n"
  "          It is a skilled FASTQ read simulation tool, flexible,           \n" 
  "          portable and tunable in terms of sequence complexity.           \n"
  "                                                                          \n"
  "FASTA Tools                                                               \n"
  "      [gto_fasta_complement]                                              \n"
  "          It replaces the ACGT bases with their complements in a          \n"
  "          FASTA file format.                                              \n"
  "                                                                          \n"
  "      [gto_fasta_extract]                                                 \n"
  "          It extracts sequences from a FASTA file, which the              \n"
  "          range is defined by the user in the parameters.                 \n"
  "                                                                          \n"
  "      [gto_fasta_extract_by_read]                                         \n"
  "          It extracts sequences from each read in a Multi-FASTA           \n"
  "          file (splited by \\n), which the range is defined by the        \n"
  "          user in the parameters.                                         \n"
  "                                                                          \n"
  "      [gto_fasta_extract_pattern_coords]                                  \n"
  "          It extracts the header and coordinates from a Multi-FASTA       \n"
  "          file format given a pattern/motif in the sequence.              \n"
  "                                                                          \n"
  "      [gto_fasta_extract_read_by_pattern]                                 \n"
  "          It extracts reads from a Multi-FASTA file format given a        \n" 
  "          pattern in the header.                                          \n"
  "                                                                          \n"
  "      [gto_fasta_find_n_pos]                                              \n"
  "          It reports the \"N\" regions in a sequence or FASTA (seq)       \n" 
  "          file.                                                           \n"
  "                                                                          \n"
  "      [gto_fasta_from_seq]                                                \n"
  "          It converts a genomic sequence to pseudo FASTA file             \n" 
  "          format.                                                         \n"
  "                                                                          \n"
  "      [gto_fasta_get_unique]                                              \n"
  "          It changes the headers of FASTA or Multi-FASTA file to          \n" 
  "          simple chrX by order, where X is the number.                    \n"
  "                                                                          \n"
  "      [gto_fasta_info]                                                    \n"
  "          It shows the readed information of a FASTA or Multi-FASTA       \n"
  "          file format.                                                    \n"
  "                                                                          \n"
  "      [gto_fasta_mutate]                                                  \n"
  "          It reates a synthetic mutation of a fasta file given            \n"
  "          specific rates of editions, deletions and additions.            \n"
  "                                                                          \n"
  "      [gto_fasta_rand_extra_chars]                                        \n"
  "          It substitues in the DNA sequence the outside ACGT chars        \n" 
  "          by random ACGT symbols.                                         \n"
  "                                                                          \n"
  "      [gto_fasta_rename_human_headers]                                    \n"
  "          It changes the headers of FASTA or Multi-FASTA file to          \n" 
  "          simple chrX by order, where X is the number.                    \n"
  "                                                                          \n"
  "      [gto_fasta_reverse]                                                 \n"
  "          It reverses the ACGT bases order for each read in a FASTA       \n"
  "          or Multi-FASTA file.                                            \n"
  "                                                                          \n"
  "      [gto_fasta_split_reads]                                             \n"
  "          It splits a Multi-FASTA file to multiple FASTA files.           \n"
  "                                                                          \n"
  "      [gto_fasta_to_seq]                                                  \n"
  "          It converts a FASTA or Multi-FASTA file format to a seq.        \n"
  "                                                                          \n"
  "      [gto_fasta_variation_filter]                                        \n"
  "          It uses the Chester-filter to filter maps.                      \n"
  "                                                                          \n"
  "      [gto_fasta_variation_map]                                           \n"
  "          It uses the Chester-map to map relative singularity regions.    \n"
  "                                                                          \n"
  "      [gto_fasta_variation_visual]                                        \n"
  "          It uses the Chester-visual to visualize relative singularity    \n"
  "          regions.                                                        \n"
  "                                                                          \n"
  "      [gto_fasta_split_streams]                                           \n"
  "          It splits and writes a FASTA file into three channels of        \n"
  "          information: headers, extra and DNA.                            \n"
  "                                                                          \n"
  "      [gto_fasta_merge_streams]                                           \n"
  "          It merges the three channels of information (headers, extra     \n"
  "          and DNA) and writes it into a FASTA file.                       \n"
  "                                                                          \n"
  "Genomic Sequence Tools                                                    \n"
  "      [gto_genomic_count_bases]                                           \n"
  "          It counts the number of bases in sequence, FASTA or             \n"
  "          FASTQ files.                                                    \n"
  "                                                                          \n"
  "      [gto_genomic_dna_mutate]                                            \n" 
  "          It creates a synthetic mutation of a sequence file              \n"
  "          given specific rates of mutations, deletions and                \n" 
  "          additions.                                                      \n"
  "                                                                          \n"
  "      [gto_genomic_extract]                                               \n"
  "          It extracts sequences from a sequence file, which the           \n"
  "          range is defined by the user in the parameters.                 \n"
  "                                                                          \n"
  "      [gto_genomic_gen_random_dna]                                        \n"
  "          It generates a synthetic DNA.                                   \n"
  "                                                                          \n"
  "      [gto_genomic_rand_seq_extra_chars]                                  \n"
  "          It substitues in the DNA sequence the outside ACGT              \n" 
  "          chars by random ACGT symbols.                                   \n"
  "                                                                          \n"
  "      [gto_genomic_period]                                                \n"
  "          It calculates the best order depth of a sequence, using         \n"
  "          FCMs.                                                           \n"
  "                                                                          \n"
  "General Purpose Tools                                                     \n"
  "      [gto_brute_force_string]                                            \n"
  "          It generates all combinations, line by line, for an             \n"
  "          inputted alphabet and specific size.                            \n"
  "                                                                          \n"
  "      [gto_char_to_line]                                                  \n"
  "          It splits a sequence into lines, creating an output             \n"
  "          sequence which has a char for each line.                        \n"
  "                                                                          \n"
  "      [gto_comparative_map]                                               \n"
  "          It creates a visualization for comparative maps.                \n"
  "                                                                          \n"
  "      [gto_filter]                                                        \n"
  "          It filters numerical sequences using a low-pass filter.         \n"
  "                                                                          \n"
  "      [gto_info]                                                          \n"
  "          It gives the basic properties of the file.                      \n"
  "                                                                          \n"
  "      [gto_lower_bound]                                                   \n"
  "          It sets an lower bound in a file with a value per               \n"
  "          line.                                                           \n"
  "                                                                          \n"
  "      [gto_max]                                                           \n"
  "          It computes the maximum value in each row between two           \n"
  "          files.                                                          \n"
  "                                                                          \n"
  "      [gto_min]                                                           \n"
  "          It computes the minimum value in each row between two           \n"
  "          files.                                                          \n"
  "                                                                          \n"
  "      [gto_new_line_on_new_x]                                             \n"
  "          It splits different rows with a new empty row.                  \n"
  "                                                                          \n"
  "      [gto_permute_by_blocks]                                             \n"
  "          It permutates by block sequence, FASTA and Multi-FASTA          \n"
  "          files.                                                          \n"
  "                                                                          \n"
  "      [gto_real_to_binary_with_threshold]                                 \n"
  "          It converts a sequence of real numbers into a binary            \n"
  "          sequence, given a threshold.                                    \n"
  "                                                                          \n"
  "      [gto_reverse]                                                       \n"
  "          It reverses the order of a sequence.                            \n"
  "                                                                          \n"
  "      [gto_segment]                                                       \n"
  "          It segments a filtered sequence.                                \n"
  "                                                                          \n"
  "      [gto_sum]                                                           \n"
  "          It adds decimal values in file, line by line, splitted          \n"
  "          by spaces or tabs.                                              \n"
  "                                                                          \n"
  "      [gto_upper_bound]                                                   \n"
  "          It sets an upper bound in a file with a value per               \n"
  "          line.                                                           \n"
  "                                                                          \n"
  "      [gto_word_search]                                                   \n"
  "          It search for a word in a file.                                 \n"
  "                                                                          \n"
  "PIPELINES  								     \n"
  "      [gto_build_xs_viral_db.sh]                                          \n"
  "          It builds a viral and human mitogenome dataset considering      \n"
  "          many ids.                                                       \n"
  "                                                                          \n"
  "      [gto_complexity_profile_regions.sh]                                 \n"
  "          It computes the bi-directional complexity profiles in any       \n" 
  "          genomic sequences.                                              \n"
  "                                                                          \n" 
  "      [gto_complexity_profiles.sh]                                        \n"
  "          It computes complexity and relative complexity profiles in      \n"
  "          any genomic sequences.                                          \n"
  "                                                                          \n"  
  "      [gto_create_sars_dataset.sh]                                        \n"
  "          It creates a viral dataset considering the following set of     \n"
  "          ids: 'AY386330.1', 'JN561323.2', 'X04370.1', 'MT007544',        \n" 
  "          'AB041963.1', 'MG921180.1', 'NC_012920.1'.                      \n" 
  "                                                                          \n"
  "      [gto_create_viral_dataset.sh]                                       \n"
  "          It creates a viral dataset considering the following set of     \n"
  "          ids: 'AY386330.1, 'JN561323.2', 'X04370.1', 'DQ279927.1',       \n"
  "          'X69198.1', 'AB041963.1', 'MG921180.1'.                         \n"
  "                                                                          \n" 
  "      [gto_download_sars2.sh]                                       	     \n"
  "          It downloads 93 SARS-CoV-2 genome sequences.              	     \n"
  "                                                                          \n" 
  "      [gto_find_best_sars2.sh]                                            \n"
  "          It finds the best SARS-CoV-2 reads.                             \n"
  "                                                                          \n" 
  "      [gto_find_motif.sh]                                                 \n"
  "          It finds and localizes a motif sequence in a FASTA file.        \n"
  "                                                                          \n" 
  "      [gto_map_rearrangements.sh]                                         \n"
  "          It applies smash technology for mapping the rearrangements      \n"
  "          in genomic sequences using an alignment-free methodology.       \n"
  "                                                                          \n" 
  "      [gto_map_rearrangements_proteins.sh]                                \n"
  "          It is a variation of the gto_map_rearrangements.sh but          \n"
  "          designed for proteins.                                          \n"
  "                                                                          \n" 
  "      [gto_merge_fasta_dbs.sh]                                            \n"
  "          It merges two FASTA databases removing repeated entries.        \n"
  "                                                                          \n" 
  "      [gto_metagenomics.sh]                                               \n"
  "          It automatically identifies metagenomic viral (or any other)    \n"
  "          content in FASTQ reads.                                         \n"
  "                                                                          \n" 
  "      [gto_proteins_complexity_profile_regions.sh]                        \n"
  "          It computes the bi-directional complexity profiles in any       \n"
  "          proteominc sequences.                                           \n"
  "                                                                          \n" 
  "      [gto_sars_simulation_detection.sh]                                  \n"
  "          It builds a small FASTA database (viral references + human      \n"
  "          mitogenome), creates a FASTQ dataset containning SARS and       \n"
  "          the human mitogenome (among others), and maps the existence     \n"
  "          of the virus and human.                                         \n"
  "                                                                          \n" 
  "      [gto_simulate_rearragements.sh]                                     \n"
  "          It simulates genome rearrangements, that can be used to test    \n"
  "          other pipelines.                                                \n"
  "                                                                          \n" 
  "      [gto_relative_complexity_profile.sh]                                \n"
  "          It computes relative complexity profiles.                       \n"
  "                                                                          \n"
  "                                                                          \n"
  "COPYRIGHT                                                                 \n"
  "      Copyright (C) 2014-2024, IEETA/DETI, University of Aveiro.          \n"
  "      This is a Free software, under MIT. You may redistribute            \n"
  "      copies of it under the terms of the MIT license. See more           \n"
  "      at <https://opensource.org/licenses/MIT>.                           \n"
  "                                                                          \n"
  "REFERENCE                                                                 \n"
  "      If you use GTO, please cite:                                        \n"
  "      GTO: A toolkit to unify pipelines in genomic and proteomic research.\n"
  "      J. R. Almeida, A. J. Pinho, J. L. Oliveira, O. Fajarda, D. Pratas,  \n"
  "      SoftwareX, Volume 12, 2020, 100535,                                 \n"
  "      doi: https://doi.org/10.1016/j.softx.2020.100535                    \n"
  "                                                                          \n");
  return EXIT_SUCCESS;
}
