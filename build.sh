#!/bin/bash

WORKDIR=$(realpath $(dirname $0))

mkdir -p $WORKDIR/build

pushd $WORKDIR/build
    # cmake -DCMAKE_TOOLCHAIN_FILE=../msp430_toolchain.cmake -DCMAKE_BUILD_TYPE:STRING=Release ..
    cmake -DCMAKE_TOOLCHAIN_FILE=../msp430_toolchain.cmake -DCMAKE_BUILD_TYPE:STRING=Debug ..
    cmake --build . -j10
    mspdebug tilib "prog ./test"
popd