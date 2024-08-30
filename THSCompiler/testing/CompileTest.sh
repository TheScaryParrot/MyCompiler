#!/bin/bash

time ../THScompiler testFile.ths -o testFile.o -s -k
ld lib/print.o lib/mod.o lib/toChar.o testFile.o -o testFile
mv a.s testFile.s
rm testFile.o
