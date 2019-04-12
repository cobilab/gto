#!/bin/bash
wget http://sweet.ua.pt/pratas/datasets/AminoAcidsCorpus.zip
unzip AminoAcidsCorpus.zip
cp AminoAcidsCorpus/HI .
../../bin/gto_ac -v -l 2 HI
../../bin/gto_ad -v HI.co 
cmp HI HI.de -l > compareOriginalWithDecompressed.diff