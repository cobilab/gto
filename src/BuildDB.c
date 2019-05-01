#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mem.h"
#include "argparse.h"

int buildViral(int threads)
{
  char buf[BUFSIZ];
  int systemRet = system("rm -f assembly_summary.txt;");
  systemRet = system("wget ftp://ftp.ncbi.nlm.nih.gov/genomes/genbank/viral/assembly_summary.txt");
  systemRet = system("awk -F '\t' '{if($12==\"Complete Genome\"||$12==\"Chromosome\")  print $20}' assembly_summary.txt > ASCG.txt");
  systemRet = system("mkdir -p GB_DB_VIRAL/");
  systemRet = system("rm -f GB_DB_VIRAL/*.fa.gz");
  snprintf(buf, sizeof(buf), "cat ASCG.txt | xargs -I{} -n1 -P%d wget -P GB_DB_VIRAL {}/*_genomic.fna.gz",threads);                                   
  systemRet = system(buf);
  systemRet = system("mkdir -p GB_DB_VIRAL_CDS/");
  systemRet = system("mkdir -p GB_DB_VIRAL_RNA/");
  systemRet = system("rm -f GB_DB_VIRAL_CDS/*.fa.gz");
  systemRet = system("rm -f GB_DB_VIRAL_RNA/*.fa.gz");
  systemRet = system("mv GB_DB_VIRAL/*_cds_from_genomic.fna.gz GB_DB_VIRAL_CDS/");
  systemRet = system("mv GB_DB_VIRAL/*_rna_from_genomic.fna.gz GB_DB_VIRAL_RNA/");
  systemRet = system("rm -f VDB.fa.gz;");
  systemRet = system("zcat GB_DB_VIRAL/*.fna.gz | gzip -9 > VDB.fa.gz");
  return systemRet;
}

int buildBacteria(int threads)
{
  char buf[BUFSIZ];
  int systemRet = system("rm -f assembly_summary.txt;");
  systemRet = system("wget ftp://ftp.ncbi.nlm.nih.gov/genomes/genbank/bacteria/assembly_summary.txt");
  systemRet = system("awk -F '\t' '{if($12==\"Complete Genome\"||$12==\"Chromosome\")  print $20}' assembly_summary.txt > ASCG.txt");
  systemRet = system("mkdir -p GB_DB_BACTERIA/");
  systemRet = system("rm -f GB_DB_BACTERIA/*.fa.gz");
  snprintf(buf, sizeof(buf), "cat ASCG.txt | xargs -I{} -n1 -P%d wget -P GB_DB_BACTERIA {}/*_genomic.fna.gz",threads);                                   
  systemRet = system(buf);
  systemRet = system("mkdir -p GB_DB_BACTERIA_CDS/");
  systemRet = system("mkdir -p GB_DB_BACTERIA_RNA/");
  systemRet = system("rm -f GB_DB_BACTERIA_CDS/*.fa.gz");
  systemRet = system("rm -f GB_DB_BACTERIA_RNA/*.fa.gz");
  systemRet = system("mv GB_DB_BACTERIA/*_cds_from_genomic.fna.gz GB_DB_BACTERIA_CDS/");
  systemRet = system("mv GB_DB_BACTERIA/*_rna_from_genomic.fna.gz GB_DB_BACTERIA_RNA/");
  systemRet = system("rm -f BDB.fa.gz;");
  systemRet = system("zcat GB_DB_BACTERIA/*.fna.gz | gzip -9 > BDB.fa.gz");
  return systemRet;
}

int buildArchaea(int threads)
{
  char buf[BUFSIZ];
  int systemRet = system("rm -f assembly_summary.txt;");
  systemRet = system("wget ftp://ftp.ncbi.nlm.nih.gov/genomes/genbank/archaea/assembly_summary.txt");
  systemRet = system("awk -F '\t' '{if($12==\"Complete Genome\"||$12==\"Chromosome\")  print $20}' assembly_summary.txt > ASCG.txt");
  systemRet = system("mkdir -p GB_DB_ARCHAEA/");
  systemRet = system("rm -f GB_DB_ARCHAEA/*.fa.gz");
  snprintf(buf, sizeof(buf), "cat ASCG.txt | xargs -I{} -n1 -P%d wget -P GB_DB_ARCHAEA {}/*_genomic.fna.gz",threads);                                   
  systemRet = system(buf);
  systemRet = system("mkdir -p GB_DB_ARCHAEA_CDS/");
  systemRet = system("mkdir -p GB_DB_ARCHAEA_RNA/");
  systemRet = system("rm -f GB_DB_ARCHAEA_CDS/*.fa.gz");
  systemRet = system("rm -f GB_DB_ARCHAEA_RNA/*.fa.gz");
  systemRet = system("mv GB_DB_ARCHAEA/*_cds_from_genomic.fna.gz GB_DB_ARCHAEA_CDS/");
  systemRet = system("mv GB_DB_ARCHAEA/*_rna_from_genomic.fna.gz GB_DB_ARCHAEA_RNA/");
  systemRet = system("rm -f ADB.fa.gz;");
  systemRet = system("zcat GB_DB_ARCHAEA/*.fna.gz | gzip -9 > ADB.fa.gz");
  return systemRet;
}

int buildProtozoa(int threads)
{
  char buf[BUFSIZ];
  int systemRet = system("rm -f assembly_summary.txt;");
  systemRet = system("wget ftp://ftp.ncbi.nlm.nih.gov/genomes/genbank/protozoa/assembly_summary.txt");
  systemRet = system("awk -F '\t' '{if($12==\"Complete Genome\"||$12==\"Chromosome\")  print $20}' assembly_summary.txt > ASCG.txt");
  systemRet = system("mkdir -p GB_DB_PROTOZOA/");
  systemRet = system("rm -f GB_DB_PROTOZOA/*.fa.gz");
  snprintf(buf, sizeof(buf), "cat ASCG.txt | xargs -I{} -n1 -P%d wget -P GB_DB_PROTOZOA {}/*_genomic.fna.gz",threads);                                   
  systemRet = system(buf);
  systemRet = system("mkdir -p GB_DB_PROTOZOA_CDS/");
  systemRet = system("mkdir -p GB_DB_PROTOZOA_RNA/");
  systemRet = system("rm -f GB_DB_PROTOZOA_CDS/*.fa.gz");
  systemRet = system("rm -f GB_DB_PROTOZOA_RNA/*.fa.gz");
  systemRet = system("mv GB_DB_PROTOZOA/*_cds_from_genomic.fna.gz GB_DB_PROTOZOA_CDS/");
  systemRet = system("mv GB_DB_PROTOZOA/*_rna_from_genomic.fna.gz GB_DB_PROTOZOA_RNA/");
  systemRet = system("rm -f PDB.fa.gz;");
  systemRet = system("zcat GB_DB_PROTOZOA/*.fna.gz | gzip -9 > PDB.fa.gz");
  return systemRet;
}

int buildFungi(int threads)
{
  char buf[BUFSIZ];
  int systemRet = system("rm -f assembly_summary.txt;");
  systemRet = system("wget ftp://ftp.ncbi.nlm.nih.gov/genomes/genbank/fungi/assembly_summary.txt");
  systemRet = system("awk -F '\t' '{if($12==\"Complete Genome\"||$12==\"Chromosome\")  print $20}' assembly_summary.txt > ASCG.txt");
  systemRet = system("mkdir -p GB_DB_FUNGI/");
  systemRet = system("rm -f GB_DB_FUNGI/*.fa.gz");
  snprintf(buf, sizeof(buf), "cat ASCG.txt | xargs -I{} -n1 -P%d wget -P GB_DB_FUNGI {}/*_genomic.fna.gz",threads);                                   
  systemRet = system(buf);
  systemRet = system("mkdir -p GB_DB_FUNGI_CDS/");
  systemRet = system("mkdir -p GB_DB_FUNGI_RNA/");
  systemRet = system("rm -f GB_DB_FUNGI_CDS/*.fa.gz");
  systemRet = system("rm -f GB_DB_FUNGI_RNA/*.fa.gz");
  systemRet = system("mv GB_DB_FUNGI/*_cds_from_genomic.fna.gz GB_DB_FUNGI_CDS/");
  systemRet = system("mv GB_DB_FUNGI/*_rna_from_genomic.fna.gz GB_DB_FUNGI_RNA/");
  systemRet = system("rm -f FDB.fa.gz;");
  systemRet = system("zcat GB_DB_FUNGI/*.fna.gz | gzip -9 > FDB.fa.gz");
  return systemRet;
}

int buildPlant(int threads)
{
  char buf[BUFSIZ];
  int systemRet = system("rm -f assembly_summary.txt;");
  systemRet = system("wget ftp://ftp.ncbi.nlm.nih.gov/genomes/genbank/fungi/assembly_summary.txt");
  systemRet = system("awk -F '\t' '{if($12==\"Complete Genome\"||$12==\"Chromosome\")  print $20}' assembly_summary.txt > ASCG.txt");
  systemRet = system("mkdir -p GB_DB_PLANT/");
  systemRet = system("rm -f GB_DB_PLANT/*.fa.gz");
  snprintf(buf, sizeof(buf), "cat ASCG.txt | xargs -I{} -n1 -P%d wget -P GB_DB_PLANT {}/*_genomic.fna.gz",threads);                                   
  systemRet = system(buf);
  systemRet = system("mkdir -p GB_DB_PLANT_CDS/");
  systemRet = system("mkdir -p GB_DB_PLANT_RNA/");
  systemRet = system("rm -f GB_DB_PLANT_CDS/*.fa.gz");
  systemRet = system("rm -f GB_DB_PLANT_RNA/*.fa.gz");
  systemRet = system("mv GB_DB_PLANT/*_cds_from_genomic.fna.gz GB_DB_PLANT_CDS/");
  systemRet = system("mv GB_DB_PLANT/*_rna_from_genomic.fna.gz GB_DB_PLANT_RNA/");
  systemRet = system("rm -f TDB.fa.gz;");
  systemRet = system("zcat GB_DB_PLANT/*.fna.gz | gzip -9 > TDB.fa.gz");
  return systemRet;
}

int buildInvertebrate(int threads)
{
  char buf[BUFSIZ];
  int systemRet = system("rm -f assembly_summary.txt;");
  systemRet = system("wget ftp://ftp.ncbi.nlm.nih.gov/genomes/genbank/invertebrate/assembly_summary.txt");
  systemRet = system("awk -F '\t' '{if($12==\"Complete Genome\"||$12==\"Chromosome\")  print $20}' assembly_summary.txt > ASCG.txt");
  systemRet = system("mkdir -p GB_DB_INVER/");
  systemRet = system("rm -f GB_DB_INVER/*.fa.gz");
  snprintf(buf, sizeof(buf), "cat ASCG.txt | xargs -I{} -n1 -P%d wget -P GB_DB_INVER {}/*_genomic.fna.gz",threads);                                   
  systemRet = system(buf);
  systemRet = system("mkdir -p GB_DB_INVER_CDS/");
  systemRet = system("mkdir -p GB_DB_INVER_RNA/");
  systemRet = system("rm -f GB_DB_INVER_CDS/*.fa.gz");
  systemRet = system("rm -f GB_DB_INVER_RNA/*.fa.gz");
  systemRet = system("mv GB_DB_INVER/*_cds_from_genomic.fna.gz GB_DB_INVER_CDS/");
  systemRet = system("mv GB_DB_INVER/*_rna_from_genomic.fna.gz GB_DB_INVER_RNA/");
  systemRet = system("rm -f IDB.fa.gz;");
  systemRet = system("zcat GB_DB_INVER/*.fna.gz | gzip -9 > IDB.fa.gz");
  return systemRet;
}

int buildVertebrateMammalian(int threads)
{
  char buf[BUFSIZ];
  int systemRet = system("rm -f assembly_summary.txt;");
  systemRet = system("wget ftp://ftp.ncbi.nlm.nih.gov/genomes/genbank/vertebrate_mammalian/assembly_summary.txt");
  systemRet = system("awk -F '\t' '{if($12==\"Complete Genome\"||$12==\"Chromosome\")  print $20}' assembly_summary.txt > ASCG.txt");
  systemRet = system("mkdir -p GB_DB_VER_MAM/");
  systemRet = system("rm -f GB_DB_VER_MAM/*.fa.gz");
  snprintf(buf, sizeof(buf), "cat ASCG.txt | xargs -I{} -n1 -P%d wget -P GB_DB_VER_MAM {}/*_genomic.fna.gz",threads);                                   
  systemRet = system(buf);
  systemRet = system("mkdir -p GB_DB_VER_MAM_CDS/");
  systemRet = system("mkdir -p GB_DB_VER_MAM_RNA/");
  systemRet = system("rm -f GB_DB_VER_MAM_CDS/*.fa.gz");
  systemRet = system("rm -f GB_DB_VER_MAM_RNA/*.fa.gz");
  systemRet = system("mv GB_DB_VER_MAM/*_cds_from_genomic.fna.gz GB_DB_VER_MAM_CDS/");
  systemRet = system("mv GB_DB_VER_MAM/*_rna_from_genomic.fna.gz GB_DB_VER_MAM_RNA/");
  systemRet = system("rm -f VMDB.fa.gz;");
  systemRet = system("zcat GB_DB_VER_MAM/*.fna.gz | gzip -9 > VMDB.fa.gz");
  return systemRet;
}

int buildVertebrateOther(int threads)
{
  char buf[BUFSIZ];  
  int systemRet = system("rm -f assembly_summary.txt;");
  systemRet = system("wget ftp://ftp.ncbi.nlm.nih.gov/genomes/genbank/vertebrate_other/assembly_summary.txt");
  systemRet = system("awk -F '\t' '{if($12==\"Complete Genome\"||$12==\"Chromosome\") print $20}' assembly_summary.txt > ASCG.txt");
  systemRet = system("mkdir -p GB_DB_VER_OTH/");
  systemRet = system("rm -f GB_DB_VER_OTH/*.fa.gz");
  snprintf(buf, sizeof(buf), "cat ASCG.txt | xargs -I{} -n1 -P%d wget -P GB_DB_VER_OTH {}/*_genomic.fna.gz",threads);                                   
  systemRet = system(buf);
  systemRet = system("mkdir -p GB_DB_VER_OTH_CDS/");
  systemRet = system("mkdir -p GB_DB_VER_OTH_RNA/");
  systemRet = system("rm -f GB_DB_VER_OTH_CDS/*.fa.gz");
  systemRet = system("rm -f GB_DB_VER_OTH_RNA/*.fa.gz");
  systemRet = system("mv GB_DB_VER_OTH/*_cds_from_genomic.fna.gz GB_DB_VER_OTH_CDS/");
  systemRet = system("mv GB_DB_VER_OTH/*_rna_from_genomic.fna.gz GB_DB_VER_OTH_RNA/");
  systemRet = system("rm -f VODB.fa.gz;");
  systemRet = system("zcat GB_DB_VER_OTH/*.fna.gz | gzip -9 > VODB.fa.gz");
  return systemRet;
}

int buildMito()
{
  int systemRet = system("rm -f mitochondrion.1.1.genomic.fna.gz mitochondrion.2.1.genomic.fna.gz;");
  systemRet = system("wget ftp://ftp.ncbi.nlm.nih.gov/refseq/release/mitochondrion/mitochondrion.1.1.genomic.fna.gz");
  systemRet = system("wget ftp://ftp.ncbi.nlm.nih.gov/refseq/release/mitochondrion/mitochondrion.2.1.genomic.fna.gz");
  systemRet = system("zcat mitochondrion.1.1.genomic.fna.gz mitochondrion.2.1.genomic.fna.gz | gzip -9 > MTDB.fa.gz");
  return systemRet;
}

int buildPlast()
{
  int systemRet = system("rm -f plastid.1.1.genomic.fna.gz plastid.2.1.genomic.fna.gz");
  systemRet = system("wget ftp://ftp.ncbi.nlm.nih.gov/refseq/release/plastid/plastid.1.1.genomic.fna.gz");
  systemRet = system("wget ftp://ftp.ncbi.nlm.nih.gov/refseq/release/plastid/plastid.2.1.genomic.fna.gz");
  systemRet = system("zcat plastid.1.1.genomic.fna.gz plastid.2.1.genomic.fna.gz | gzip -9 > PLDB.fa.gz");
  return systemRet;
}

int buildAll()
{
  return system("zcat VDB.fa.gz BDB.fa.gz ADB.fa.gz PDB.fa.gz FDB.fa.gz TDB.fa.gz IDB.fa.gz VMDB.fa.gz VODB.fa.gz MTDB.fa.gz PLDB.fa.gz | gzip -9 > ALLDB.fa.gz");
}


int main(int argc, char *argv[])
{
  int threads=8;
  uint32_t viral=0;
  uint32_t bacteria=0;
  uint32_t archaea=0;
  uint32_t protozoa=0;
  uint32_t fungi=0;
  uint32_t plant=0;
  uint32_t inver=0;
  uint32_t vermam=0;
  uint32_t veroth=0;
  uint32_t mito=0;
  uint32_t plast=0;
  uint32_t all=0;

  char *programName = argv[0];
  struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_STRING('t', "threads", &threads, "Number of threads to use (Default: 8)"),
        OPT_BOOLEAN('v', "viral", &viral,   "Downloads and builds the viral database"),
        OPT_BOOLEAN('b', "bacteria", &bacteria,   "Downloads and builds the bacteria database"),
        OPT_BOOLEAN('e', "archaea", &archaea,   "Downloads and builds the archaea database"),
        OPT_BOOLEAN('p', "protozoa", &protozoa,   "Downloads and builds the protozoa database"),
        OPT_BOOLEAN('f', "fungi", &fungi,   "Downloads and builds the fungi database"),
        OPT_BOOLEAN('n', "plant", &plant,   "Downloads and builds the plant database"),
        OPT_BOOLEAN('i', "inver", &inver,   "Downloads and builds the invertebrate database"),
        OPT_BOOLEAN('m', "vermam", &vermam,   "Downloads and builds the vertebrate mammalian database"),
        OPT_BOOLEAN('o', "veroth", &veroth,   "Downloads and builds the vertebrate other database"),
        OPT_BOOLEAN('c', "mito", &mito,   "Downloads and builds the mitochondrion database"),
        OPT_BOOLEAN('s', "plast", &plast,   "Downloads and builds the plastid database"),
        OPT_BOOLEAN('a', "all", &all,   "Downloads and builds all the databases"),
        OPT_END(),
  };
  struct argparse argparse;

  char usage[250] = "\nExample: "; 
  strcat(usage, programName);
  strcat(usage, " -a \n");

  argparse_init(&argparse, options, NULL, programName, 0);
  argparse_describe(&argparse, "\nIt downloads and compresses the complete genomic sequences form the NCBI database that are labelled as 'Complete genome' or 'Chromosome'", usage);
  argc = argparse_parse(&argparse, argc, argv);

  if(argc != 0)
    argparse_help_cb(&argparse, options);

  if(viral==0)
    buildViral(threads);
  if(bacteria==0)
    buildBacteria(threads);
  if(archaea==0)
    buildArchaea(threads);
  if(protozoa==0)
    buildProtozoa(threads);
  if(fungi==0)
    buildFungi(threads);
  if(plant==0)
    buildPlant(threads);
  if(inver==0)
    buildInvertebrate(threads);
  if(vermam==0)
    buildVertebrateMammalian(threads);
  if(veroth==0)
    buildVertebrateOther(threads);
  if(mito==0)
    buildMito();
  if(plast==0)
    buildPlast();
  if(all==0)
    buildAll();

  return EXIT_SUCCESS;
}