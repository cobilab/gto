#include "msg-cmap.h"
#include <stdio.h>
#include <stdlib.h>

void PrintMenuGVisual(void){
  fprintf(stderr,
  "Usage: ./gto_comparative_map [options] [[--] args]                        \n"
  "   or: ./gto_comparative_map [options]                                    \n"  
  "                                                                          \n"
  "It creates a visualization for comparative maps.                          \n"
  "                                                                          \n"
  "    -h, --help            Show this help message and exit                 \n"
  "                                                                          \n"
  "Basic options                                                             \n"
  "    <FILE>                Contigs filename with positions (.pos)          \n"
  "                                                                          \n"
  "Optional                                                                  \n"
  "                                                                          \n"
  "    -h                    Give this help                                  \n"
  "    -V                    Display version number                          \n"
  "    -v                    Verbose mode (more information)                 \n"
  "    -l <link>             Link type between maps [0;4]                    \n"
  "    -w <width>            Chromosome width                                \n"
  "    -s <space>            Space between chromosomes                       \n"
  "    -m <mult>             Color id multiplication factor                  \n"
  "    -b <begin>            Color id beggining                              \n"
  "    -c <minimum>          Minimum block size to consider                  \n"
  "    -i                    Do NOT show inversion maps                      \n"
  "    -r                    Do NOT show regular maps                        \n"
  "    -o <FILE>             Output image filename with map                  \n"
  "                                                                          \n"
  "Example: ./gto_comparative_map -o map.svg map.config                      \n"
  "                                                                          \n");
  }
