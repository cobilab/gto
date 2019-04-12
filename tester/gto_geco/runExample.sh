#!/bin/bash
wget http://sweet.ua.pt/pratas/datasets/DNACorpus.zip
unzip DNACorpus.zip
cp DNACorpus/BuEb .
../../bin/gto_geco -v -l 2 BuEb
../../bin/gto_gede -v BuEb.co 
cmp BuEb BuEb.de -l > compareOriginalWithDecompressed.diff