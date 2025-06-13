TOOL_DIR := $(CURDIR)/tool
ZIG_CACHE_DIR := $(CURDIR)/.zig-cache
ZIG := export ZIG_GLOBAL_CACHE_DIR=$(ZIG_CACHE_DIR) && $(realpath $(TOOL_DIR)/$(shell (ls $(TOOL_DIR) | grep --color=never zig))/zig)

TODO_EXCLUDE := --exclude todolist.sh
TODO_EXCLUDE := $(TODO_EXCLUDE) --exclude Makefile
TODO_EXCLUDE := $(TODO_EXCLUDE) --exclude-dir .git
TODO_EXCLUDE := $(TODO_EXCLUDE) --exclude-dir .zig-cache
TODO_EXCLUDE := $(TODO_EXCLUDE) --exclude-dir bin
TODO_EXCLUDE := $(TODO_EXCLUDE) --exclude-dir tool

PROJECT_VERSION := v2.3.0-beta
PROJECT_NAME := c_text_rpg
COMMIT_SHORT_HASH := $(shell git rev-parse --short HEAD)
FULL_PROJECT_NAME := $(PROJECT_NAME)_$(PROJECT_VERSION)
DEBUG_FULL_PROJECT_NAME := $(FULL_PROJECT_NAME)_debug

CC := ZIG_GLOBAL_CACHE_DIR=$(CURDIR)/.zig-cache && $(ZIG) cc
CFLAGS := -std=c99
CFLAGS := $(CFLAGS) -Wall -Wextra -Wpedantic
CFLAGS := $(CFLAGS) -D PROJECT_NAME=\"$(PROJECT_NAME)\"
CFLAGS := $(CFLAGS) -D PROJECT_VERSION=\"$(PROJECT_VERSION)\"
CFLAGS := $(CFLAGS) -D COMMIT_SHORT_HASH=\"$(COMMIT_SHORT_HASH)\"
DEBUG_CFLAGS := $(CFLAGS) -D DEBUG
CSOURCE_FOLDER := $(realpath $(CURDIR)/src)
CFILES := $(shell find "$(CSOURCE_FOLDER)" -name "*.c" | tr '\n' ' ')

OUTPUT_DIR := $(CURDIR)/bin

LINUX_OUTPUT := $(OUTPUT_DIR)/$(FULL_PROJECT_NAME)
WINDOWS_OUTPUT := $(OUTPUT_DIR)/$(FULL_PROJECT_NAME).exe
DEBUG_LINUX_OUTPUT := $(OUTPUT_DIR)/$(DEBUG_FULL_PROJECT_NAME)
DEBUG_WINDOWS_OUTPUT := $(OUTPUT_DIR)/$(DEBUG_FULL_PROJECT_NAME).exe

.PHONY: help all run-linux test clean todo

help: ## Display this help screen
	@grep -E '^[a-z.A-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

all: ## Builds all targets
all: $(LINUX_OUTPUT) $(WINDOWS_OUTPUT)
all: $(DEBUG_LINUX_OUTPUT) $(DEBUG_WINDOWS_OUTPUT)

run-linux: $(LINUX_OUTPUT) ## Runs linux executable
	$<

release-linux: $(LINUX_OUTPUT) ## Builds linux executable

$(LINUX_OUTPUT): $(OUTPUT_DIR) $(CFILES)
	$(CC) $(CFILES) -o $(LINUX_OUTPUT) $(CFLAGS)

release-windows: $(WINDOWS_OUTPUT) ## Builds windows executable

$(WINDOWS_OUTPUT): $(OUTPUT_DIR) $(CFILES)
	$(CC) $(CFILES) -o $(WINDOWS_OUTPUT) $(CFLAGS) -target x86_64-windows

debug-linux: $(LINUX_OUTPUT) ## Builds debug linux executable

$(DEBUG_LINUX_OUTPUT): $(OUTPUT_DIR) $(CFILES)
	$(CC) $(CFILES) -o $(DEBUG_LINUX_OUTPUT) $(DEBUG_CFLAGS)

debug-windows: $(WINDOWS_OUTPUT) ## Builds debug windows executable

$(DEBUG_WINDOWS_OUTPUT): $(OUTPUT_DIR) $(CFILES)
	$(CC) $(CFILES) -o $(DEBUG_WINDOWS_OUTPUT) $(DEBUG_CFLAGS) -target x86_64-windows

$(OUTPUT_DIR):
	@mkdir $(OUTPUT_DIR)

clean: ## Removes build files
	@rm "$(OUTPUT_DIR)" "$(ZIG_CACHE_DIR)" -rf
	@echo Clean complete

todo: ## Grep all todo
	cd $(CURDIR) && grep -e TODO -Hnr . $(TODO_EXCLUDE)
