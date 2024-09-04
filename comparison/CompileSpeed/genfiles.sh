#!/bin/bash

python3 generators/Cgenerator.py $1
python3 generators/THSgenerator.py $1
python3 generators/QHSgenerator.py $1