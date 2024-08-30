#!/bin/bash

time ../QHScompiler testFile.qhs -o testFile -k
mv a.s testFile.s
rm a.o
