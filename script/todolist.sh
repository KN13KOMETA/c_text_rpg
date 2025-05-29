#!/bin/bash
# Prints every TODO
SCRIPT_DIR="$(dirname "$(readlink -f "$0")")"
source $SCRIPT_DIR/var.sh x

# EXCLUDE="$EXCLUDE --exclude "
# EXCLUDE="$EXCLUDE --exclude-dir "

EXCLUDE="--exclude todolist.sh"
EXCLUDE="$EXCLUDE --exclude-dir .git"
EXCLUDE="$EXCLUDE --exclude-dir .zig-cache"
EXCLUDE="$EXCLUDE --exclude-dir bin"
EXCLUDE="$EXCLUDE --exclude-dir tool"

cd $ROOT_DIR
grep -e TODO -Hnr . ${EXCLUDE}
