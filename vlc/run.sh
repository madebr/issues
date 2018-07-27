#!/bin/bash

set -e

CURDIR=$(dirname "$(readlink -f $0)")
BINDIR=$CURDIR/build

mkdir -p $BINDIR

cd "$BINDIR"

cmake "$CURDIR"

make

./window & ( sleep 10 && killall window )
