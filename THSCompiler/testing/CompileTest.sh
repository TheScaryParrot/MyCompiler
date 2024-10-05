#!/bin/bash

time ../THScompiler testFile.ths -o testFile -k --link-files lib/print.o lib/mod.o lib/toChar.o
mv a.s testFile.s
rm a.o
