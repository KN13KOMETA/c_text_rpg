#! /bin/bash
# DECLARE ENVIROMENT VARIABLES
SCRIPT_DIR="$(dirname "$(readlink -f "$0")")"

TOOL_DIR="$(readlink -f "$SCRIPT_DIR/../tool")"
ZIG_PATH="$(readlink -f "$TOOL_DIR/$(ls "$TOOL_DIR" | grep --color=never zig)")"

PATH=$PATH:$ZIG_PATH

PROJECT_VERSION="v2.1.0-alpha"
PROJECT_NAME="c_text_rpg"
FULL_PROJECT_NAME="${PROJECT_NAME}_$PROJECT_VERSION"

CC="zig cc"
CFLAGS="-std=c99 -Wall -Wextra -Wpedantic"
CSOURCE_FOLDER="$(dirname "$SCRIPT_DIR")/src"
CFILES="$(find "$CSOURCE_FOLDER" -name "*.c" | tr '\n' ' ')"

# Setup dirs
OUTPUT_DIR=$(dirname -- "$SCRIPT_DIR")/bin
LINUX_OUTPUT="$OUTPUT_DIR/$FULL_PROJECT_NAME"
WINDOWS_OUTPUT="$OUTPUT_DIR/$FULL_PROJECT_NAME.exe"
