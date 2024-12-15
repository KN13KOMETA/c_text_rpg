#! /bin/bash
# DECLARE ENVIROMENT VARIABLES
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

PROGRAM_NAME=c_text_rpg

# Setup dirs
OUTPUT_DIR=$(dirname -- "$SCRIPT_DIR")/bin
LINUX_OUTPUT=$OUTPUT_DIR/$PROGRAM_NAME
WINDOWS_OUTPUT=$OUTPUT_DIR/$PROGRAM_NAME.exe
