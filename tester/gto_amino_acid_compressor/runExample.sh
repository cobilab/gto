#!/bin/bash
wget http://sweet.ua.pt/pratas/datasets/AminoAcidsCorpus.zip
unzip AminoAcidsCorpus.zip
cp AminoAcidsCorpus/HI .
../../bin/gto_amino_acid_compressor -v -l 2 HI
../../bin/gto_amino_acid_decompressor -v HI.co 
cmp HI HI.de -l > compareOriginalWithDecompressed.diff