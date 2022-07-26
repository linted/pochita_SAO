#!/bin/bash

WORKDIR=$(realpath $(dirname $0))
CPU_COUNT=$(lscpu | egrep "^CPU\(s\):" | tr -s ' ' | cut -d" " -f2)

USAGE="$0 [release | debug | clean]"

if [ -z $WORKDIR/../msp430-gcc ]; then
  echo $USAGE
  echo
  echo "Error: Expected msp430-gcc install dir to be located at " $(realpath $WORKDIR/../msp430-gcc)
  echo "Try making a symlink pointing to it?"
  echo "If you are feeling adventurous, update msp430_toolchain.cmake with the correct locations instead"
  exit 1
fi

BUILD_TYPE="Release"
if [ $# -eq 1 ]; then
    if [[ "release" == ${1,,} ]]; then
        BUILD_TYPE="Release"
    elif [[ "debug" == ${1,,} ]]; then
        BUILD_TYPE="Debug"
    elif [[ "clean" == ${1,,} ]]; then
        echo "Cleaning"
        rm -r $WORKDIR/build
        exit 0
    else
        echo $USAGE
        echo
        echo "Invalid release type: $0"
        exit 2
    fi
elif [ $# -gt 1 ]; then
    echo $USAGE
    echo
    exit 3
fi

mkdir -p $WORKDIR/build

pushd $WORKDIR/build
    cmake -DCMAKE_TOOLCHAIN_FILE=../msp430_toolchain.cmake -DCMAKE_BUILD_TYPE:STRING=$BUILD_TYPE ..
    cmake --build . -j$CPU_COUNT
    mspdebug tilib "prog ./pochita_firmware"
popd
