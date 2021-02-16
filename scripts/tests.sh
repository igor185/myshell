#!/bin/bash

PROGRAM=./build/myshell
HELP_FOLDER=./scripts/help


#### check running simple program and mpwd
if [ "$($PROGRAM $HELP_FOLDER/pwd.msh)" != "$(pwd)" ]
then
  echo "Incorrect mpwd"
  exit 1
fi
####


#### check mycat
echo "123 321 \n 123 123" > temp.txt

if [ "$($PROGRAM $HELP_FOLDER/cat.msh)" != "$(cat temp.txt)" ]
then
  echo "Incorrect cat"
  rm temp.txt
  exit 1
fi
rm temp.txt
####

#### checks

MYSHELL="$($PROGRAM $HELP_FOLDER/tests.msh)"
BASH="$(bash $HELP_FOLDER/tests.sh)"
echo $MYSHELL
if [ "$MYSHELL" != "$BASH" ]
then
  echo $MYSHELL > ms.txt
  echo $BASH > bh.txt
  diff ms.txt bh.txt > errors.txt
  echo "Incorrect tests"
  exit 1
fi
####

echo "Pass tests"
