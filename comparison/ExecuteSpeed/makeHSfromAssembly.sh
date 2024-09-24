#!/bin/bash

nasm -felf64 ExecuteSpeedTHS.s
ld ExecuteSpeedTHS.o ../thsLib/print.o -o ExecuteSpeedTHS
rm ExecuteSpeedTHS.o

nasm -felf64 ExecuteSpeedQHS.s
ld ExecuteSpeedQHS.o -o ExecuteSpeedQHS
rm ExecuteSpeedQHS.o