#! /bin/bash
# DECLARE ENVIROMENT VARIABLES
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

PROJECT_NAME=c_text_rpg

CC="$(dirname -- "$SCRIPT_DIR")/zig-linux-x86_64-0.14.0-dev.2487+af89bb05d/zig cc"
CFLAGS="--std=c99 -Wall -Wextra -Wpedantic"
CFILES="main.c forge.c functions.c"

# Setup dirs
OUTPUT_DIR=$(dirname -- "$SCRIPT_DIR")/bin
LINUX_OUTPUT="$OUTPUT_DIR/$PROJECT_NAME"
WINDOWS_OUTPUT="$OUTPUT_DIR/$PROJECT_NAME.exe"
