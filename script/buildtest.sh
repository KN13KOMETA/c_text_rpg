#! /bin/bash
# BUILD AND RUN LINUX BINARY
SCRIPT_DIR="$(dirname "$(readlink -f "$0")")"
source $SCRIPT_DIR/var.sh

if [ ! -d "$OUTPUT_DIR" ]; then
  mkdir $OUTPUT_DIR
fi


if [ -f $FLEX_LINUX_OUTPUT ]; then
  rm $FLEX_LINUX_OUTPUT
fi

$CC $CFILES -o $FLEX_LINUX_OUTPUT $FLEX_CFLAGS

if [ -f $FLEX_LINUX_OUTPUT ]; then
  $FLEX_LINUX_OUTPUT
else
  echo "COMPILATION FAILED"
fi
