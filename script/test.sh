#! /bin/bash
# BUILD AND RUN LINUX BINARY
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

source $SCRIPT_DIR/var.sh


if [ ! -d "$OUTPUT_DIR" ]; then
  mkdir $OUTPUT_DIR
fi


if [ -f $LINUX_OUTPUT ]; then
  rm $LINUX_OUTPUT
fi

$CC $CFILES -o $LINUX_OUTPUT $CFLAGS

if [ -f $LINUX_OUTPUT ]; then
  $LINUX_OUTPUT
else
  echo "COMPILATION FAILED"
fi
