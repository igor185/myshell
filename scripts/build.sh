#!/bin/bash

RUN=false
EXTERNAL_DIR="src/external"
EXTERNAL_DIR_BACK="../.."
BUILD_DIR="build"

help(){
  echo "Script to build and run myshell"
  echo
  echo "[-h|--help] show this message"
  echo "[-r|--run] run after success build"
  exit 0
}

read_args() {
  while [ -n "$1" ]; do
    case "$1" in
    -h | --help)
      help
      ;;
    -r | --run)
      RUN=true
      ;;
    esac
    shift
  done
}

build_external(){
  mkdir "./$BUILD_DIR/external"

  cd "./$EXTERNAL_DIR" || exit 1

  ls "./" | while read i; do
    cd ./"$i" && cmake ./ -G "Unix Makefiles" -Bbuild
    cmake --build build
    cp ./build/"$i" "$EXTERNAL_DIR_BACK/../build/external/$i"
    echo "-- Moved to ../build/external/$i"
    cd ../
  done
  cd "$EXTERNAL_DIR_BACK" || exit 1
}

read_args "$@"

if [ ! -d "./build" ]
then
  cmake ./ -G "Unix Makefiles" -Bbuild
fi
cmake --build build

if [ $? == 0 ]
then
  build_external
else
  exit 1
fi

echo "Build success"

if [ $? == 0 ] && [ $RUN == true ]
then
  ./build/myshell
fi
