#!/bin/bash

if [ ! -f "$1".ths ]; then
    echo "$1.ths does not exist and cannot be compiled."
    exit 1
fi


../THScompiler "$1".ths -o "$1".o -s
ld lib/print.o lib/mod.o lib/toChar.o "$1".o -o "$1"

rm "$1".o
