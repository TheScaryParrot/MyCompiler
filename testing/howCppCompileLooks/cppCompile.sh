#!/bin/sh

g++ "$1.cpp" -S -o "$1.asm"
