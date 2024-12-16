#! /bin/bash
# COMPILE LINUX AND WINDOWS BINARIES
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

source $SCRIPT_DIR/var.sh

# Delete bin dir
if [ -d "$OUTPUT_DIR" ]; then
  rm -r $OUTPUT_DIR;
fi

mkdir $OUTPUT_DIR

# Compile linux and windows binaries
$CC $CFILES -o $LINUX_OUTPUT $CFLAGS
$CC $CFILES -o $WINDOWS_OUTPUT $CFLAGS -target x86_64-windows

echo "COMPILING COMPLETE!"
