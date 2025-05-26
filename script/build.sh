#!/bin/bash
# COMPILE LINUX AND WINDOWS BINARIES
SCRIPT_DIR="$(dirname "$(readlink -f "$0")")"
source $SCRIPT_DIR/var.sh x

# Delete bin dir
if [ -d "$OUTPUT_DIR" ]; then
  rm -r $OUTPUT_DIR;
fi

mkdir $OUTPUT_DIR

# Compile linux and windows binaries
$CC $CFILES -o $LINUX_OUTPUT $CFLAGS
$CC $CFILES -o $WINDOWS_OUTPUT $CFLAGS -target x86_64-windows

# Compile linux and windows debug binaries
$CC $CFILES -o $DEBUG_LINUX_OUTPUT $DEBUG_CFLAGS
$CC $CFILES -o $DEBUG_WINDOWS_OUTPUT $DEBUG_CFLAGS -target x86_64-windows

echo "COMPILING COMPLETE!"
