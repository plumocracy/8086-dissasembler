CC = clang++
FLAGS=
BUILD_DIR = build
STD = 23
SRC = src/main.cpp src/OpParser.cpp src/BitUtils.cpp src/Mov.cpp

# Assembly File to make with nasm
AFILE=asm-test-files/mr
ASM_DIR=asm

default: $(BUILD_DIR)
	$(CC) -g $(SRC) -o $(BUILD_DIR)/decoder --std=c++$(STD) $(FLAGS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

asm:
	mkdir -p $(ASM_DIR)
	nasm $(AFILE) -o $(ASM_DIR)/assembled

compile_commands:
	bear -- make

.PHONY: asm clean

clean:
	rm -rf $(BUILD_DIR) $(ASM_DIR)
