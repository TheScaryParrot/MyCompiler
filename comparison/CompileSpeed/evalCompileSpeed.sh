#!/bin/bash

echo "C:"
time gcc -o CompileSpeedC.s -S CompileSpeed.c
#gcc CompileSpeedC.s -o CompileSpeedC
#rm CompileSpeedC.s

echo ""
echo ""

echo "THS:"
time ../../THSCompiler/THScompiler CompileSpeed.ths -c -o CompileSpeedTHS.s
#nasm -f elf64 CompileSpeedTHS.s -o CompileSpeedTHS.o
#rm CompileSpeedTHS.s
#ld CompileSpeedTHS.o ../thsLib/print.o -o CompileSpeedTHS
#rm CompileSpeedTHS.o
echo ""
echo ""

echo "QHS:"
#time 