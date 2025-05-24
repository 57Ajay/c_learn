# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude -MMD -MP
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
BIN_DIR = bin
BIN = $(BIN_DIR)/main

# File definitions
SRC = $(wildcard $(SRC_DIR)/*.c)
HDR = $(wildcard $(INC_DIR)/*.h)
OBJ = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))
DEP = $(OBJ:.o=.d)

# Default target
all: build

# Re-generate compile_commands.json if .c or .h files changed
.PHONY: ccjson
ccjson: $(SRC) $(HDR)
	@./gen-ccjson.sh

# Build binary
build: ccjson $(BIN)

$(BIN): $(OBJ)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $^

# Compile .c to .o and generate .d file
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Run binary
run: build
	./$(BIN)

# Clean generated files
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR) compile_commands.json

# Include dependencies
-include $(DEP)

