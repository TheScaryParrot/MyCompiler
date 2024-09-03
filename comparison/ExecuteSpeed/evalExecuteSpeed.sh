#!/bin/bash

echo "C:"
time ./ExecuteSpeedC > /dev/null

echo ""
echo ""

echo "THS:"
time ./ExecuteSpeedTHS > /dev/null
echo ""
echo ""

echo "QHS:"
time ./ExecuteSpeedQHS > /dev/null