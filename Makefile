BUILD_DIR = build
LIB_DIR = lib

LIB = $(BUILD_DIR)/libtinytest.so
OBJ = $(BUILD_DIR)/libtinytest.o
SRC = $(LIB_DIR)/tinytest.c

CC = gcc
CFLAGS = -fPIC -Wall -Wextra -I./lib/
LDFLAGS = -shared

all: directories $(LIB)

directories:
	mkdir -p $(BUILD_DIR)

$(OBJ) : $(SRC)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $<

clean:
	rm -rf $(BUILD_DIR)


.PHONY: all clean directories
