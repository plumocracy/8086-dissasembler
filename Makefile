CC = clang++
FLAGS=
BUILD_DIR = build
STD = 17

default: $(BUILD_DIR)
	$(CC) src/decoder.cpp -o build/decoder --std=c++$(STD) $(FLAGS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -r $(BUILD_DIR)
