#! /bin/bash
# BUILD AND RUN LINUX BINARY
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

source $SCRIPT_DIR/var.sh

if [ -f $LINUX_OUTPUT ]; then
  rm $LINUX_OUTPUT
fi

clang main.c forge.c functions.c -o $LINUX_OUTPUT --std=c23


if [ -f $LINUX_OUTPUT ]; then
  $LINUX_OUTPUT
else
  echo "COMPILATION FAILED"
fi
