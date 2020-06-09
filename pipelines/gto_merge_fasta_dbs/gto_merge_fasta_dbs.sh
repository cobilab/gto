#!/bin/bash
#
# This pipeline merges two FASTA databases removing repeated entries (by ID)
#
# EXAMPLE: ./gto_merge_fasta_dbs VDB.fa VDB_2.fa
#
# INPUT $1 -> FASTA DB #1
# INPUT $2 -> FASTA DB #2
#
# OUTPUT   -> mixed-da.fa
#
# Merge DB:
cat $1 $2 > tmp-mixed-dbs.fa;
#
# Get IDS form DB:
cat tmp-mixed-dbs.fa \
| grep "^>" \
| awk 'BEGIN{FS=" "}; {print $1}' \
| sort -f \
| uniq -i > IDS.txt;
#
# Extract from mixed DB:
rm -f mixed-db.fa;
while read id; 
  do
  echo "$id"
  gto_fasta_extract_read_by_pattern -p "$id" < tmp-mixed-dbs.fa \
  | awk '/^>/{if(N)exit;++N;} {print;}' >> mixed-db.fa
  done < IDS.txt;
#

