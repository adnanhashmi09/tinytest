CC = gcc

BUILD_DIR = build
TARGET = $(BUILD_DIR)/example
OBJ = $(BUILD_DIR)/example.o
SRC = ./example.c
LDFLAGS = -ltinytest -L../build/mac-arm64/

all: directories $(TARGET)
	DYLD_LIBRARY_PATH=../build/mac-arm64/ $(TARGET)

directories:
	mkdir -p $(BUILD_DIR)

$(OBJ): $(SRC)
	$(CC) -c $< -o $@

$(TARGET): $(OBJ)
	$(CC) -o $@ $< $(LDFLAGS)

clean:
	rm -rf ./build/

.PHONY: all clean directories
