#!/bin/bash

echo "C:"
echo "skipping C"
#time ./ExecuteSpeedC > /dev/null

echo ""
echo ""

echo "THS:"
time ./ExecuteSpeedTHS > /dev/null
echo ""
echo ""

echo "QHS:"
time ./ExecuteSpeedQHS > /dev/null
