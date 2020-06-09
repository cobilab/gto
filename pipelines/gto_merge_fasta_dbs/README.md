# Script: gto_merge_fasta_dbs.sh

This pipeline merges two FASTA databases removing repeated entries (by ID). The execution of this pipeline requires: 1) a FASTA database; and 2) another FASTA database. This is then executed as follows:

```sh
gto_merge_fasta_dbs VDB.fa VDB_2.fa 
```

The following block of code represents the essential information for this script:

```sh
...
| grep "^>" \
| awk 'BEGIN{FS=" "}; {print $1}' \
| sort -f \
| uniq -i > IDS.txt;
...
while read id; 
  do
  echo "$id"
  gto_fasta_extract_read_by_pattern -p "$id" < tmp-mixed-dbs.fa \
  | awk '/^>/{if(N)exit;++N;} {print;}' >> mixed-db.fa
  done < IDS.txt;
...
```

## Tools
The GTO tools used and their role in this pipeline are the following:

- **gto_fasta_extract_read_by_pattern**: it extracts a FASTA reads by a pattern present in the header.
