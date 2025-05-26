#!/bin/bash
# SET UPS PATH
# SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
SCRIPT_DIR="$(dirname "$(readlink -f "$0")")"
source $SCRIPT_DIR/var.sh x

SCRIPT_BIN_DIR="$SCRIPT_DIR/bin"

# Clearing and creating bin dir for scripts
if [ -d $SCRIPT_BIN_DIR ]; then
  rm $SCRIPT_BIN_DIR -r
fi

mkdir $SCRIPT_BIN_DIR

# Create a symlinks for scripts
ln -s "$SCRIPT_DIR/build.sh" "$SCRIPT_BIN_DIR/build"
ln -s "$SCRIPT_DIR/buildtest.sh" "$SCRIPT_BIN_DIR/buildtest"

PATH=$PATH:$SCRIPT_BIN_DIR

echo "\$PATH SETTED UP"
echo "COMMANDS ARE build, buildtest"
