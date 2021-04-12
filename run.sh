#!/bin/bash

CURR_DIR=$(pwd)
SCRIPT_DIR="$CURR_DIR/$(dirname "$0")"

#preprocess the data
python utils/blossom5_utils.py -i $CURR_DIR/data/com-dblp.ungraph.txt

# build Blossom V
cd $SCRIPT_DIR/blossom5
make
./blossom5 -e ../data/com-dblp.ungraph.txt.blossomv.preprocessed

