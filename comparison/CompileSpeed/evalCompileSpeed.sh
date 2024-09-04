#!/bin/bash

./genfiles.sh $1

echo "C:"
time gcc -o tmp/CompileSpeedC.s -S tmp/CompileSpeed.c
rm tmp/CompileSpeedC.s

echo ""
echo ""

echo "THS:"
time ../../THSCompiler/THScompiler tmp/CompileSpeed.ths -c -o tmp/CompileSpeedTHS.s
rm tmp/CompileSpeedTHS.s
echo ""
echo ""

echo "QHS:"
time ../../QHSCompiler/QHScompiler tmp/CompileSpeed.qhs -c -o tmp/CompileSpeedQHS.s
rm tmp/CompileSpeedQHS.s

echo ""
echo ""