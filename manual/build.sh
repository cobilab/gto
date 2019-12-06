#!/bin/bash
pdflatex manual.tex
bibtex manual
pdflatex manual.tex
pdflatex manual.tex
okular manual.pdf
