#! /bin/bash
# COMPILE LINUX AND WINDOWS BINARIES
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

source $SCRIPT_DIR/var.sh

# Delete bin dir
if [ -d "$OUTPUT_DIR" ]; then
  rm -r $OUTPUT_DIR;
fi

mkdir $OUTPUT_DIR

clang main.c forge.c functions.c -o $LINUX_OUTPUT --std=c23
x86_64-w64-mingw32-gcc main.c forge.c functions.c -o $WINDOWS_OUTPUT --std=c2x

echo "COMPILING COMPLETE!"
