#!/bin/bash
# DECLARE ENVIROMENT VARIABLES
SCRIPT_DIR="$(dirname "$(readlink -f "$0")")"

ROOT_DIR="$(readlink -f "$SCRIPT_DIR/..")"

TOOL_DIR="$(readlink -f "$SCRIPT_DIR/../tool")"
ZIG_PATH="$(readlink -f "$TOOL_DIR/$(ls "$TOOL_DIR" | grep --color=never zig)")"

PATH=$PATH:$ZIG_PATH

PROJECT_VERSION="v2.3.0-beta"
PROJECT_NAME="c_text_rpg"
COMMIT_SHORT_HASH="$(git rev-parse --short HEAD)"
FULL_PROJECT_NAME="${PROJECT_NAME}_$PROJECT_VERSION"
DEBUG_FULL_PROJECT_NAME="${FULL_PROJECT_NAME}_debug"

CC="zig cc"
CFLAGS="-std=c99"
CFLAGS="${CFLAGS} -Wall -Wextra -Wpedantic"
CFLAGS="${CFLAGS} -D PROJECT_NAME=\"${PROJECT_NAME}\""
CFLAGS="${CFLAGS} -D PROJECT_VERSION=\"${PROJECT_VERSION}\""
CFLAGS="${CFLAGS} -D COMMIT_SHORT_HASH=\"${COMMIT_SHORT_HASH}\""
DEBUG_CFLAGS="$CFLAGS -D DEBUG"
CSOURCE_FOLDER="$(dirname "$SCRIPT_DIR")/src"
CFILES="$(find "$CSOURCE_FOLDER" -name "*.c" | tr '\n' ' ')"

OUTPUT_DIR=$(dirname -- "$SCRIPT_DIR")/bin

LINUX_OUTPUT="$OUTPUT_DIR/$FULL_PROJECT_NAME"
WINDOWS_OUTPUT="$OUTPUT_DIR/$FULL_PROJECT_NAME.exe"
DEBUG_LINUX_OUTPUT="$OUTPUT_DIR/$DEBUG_FULL_PROJECT_NAME"
DEBUG_WINDOWS_OUTPUT="$OUTPUT_DIR/$DEBUG_FULL_PROJECT_NAME.exe"



if [[ "$1" == "${1#[Xx]}" ]]; then
  while true; do
    read -p "Build in debug mode (y/n): " yn
    case $yn in
      [Yy]* )
        echo "Debug mode is used";
        FLEX_CFLAGS=$DEBUG_CFLAGS
        FLEX_LINUX_OUTPUT=$DEBUG_LINUX_OUTPUT
        FLEX_WINDOWS_OUTPUT=$DEBUG_WINDOWS_OUTPUT
        break;;
      * )
        echo "Debug mode is not used";
        FLEX_CFLAGS=$CFLAGS
        FLEX_LINUX_OUTPUT=$LINUX_OUTPUT
        FLEX_WINDOWS_OUTPUT=$WINDOWS_OUTPUT
        break;;
    esac
  done
fi
