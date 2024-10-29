BUILD_DIR = build
LIB_DIR = lib

LINUX_AMD64_DIR = $(BUILD_DIR)/linux-amd64
LINUX_ARM64_DIR = $(BUILD_DIR)/linux-arm64
MAC_ARM64_DIR = $(BUILD_DIR)/mac-arm64
MAC_AMD64_DIR = $(BUILD_DIR)/mac-amd64

LINUX_LIB = libtinytest.so
MAC_LIB = libtinytest.dylib

LINUX_AMD64_LIB = $(LINUX_AMD64_DIR)/$(LINUX_LIB)
LINUX_ARM64_LIB = $(LINUX_ARM64_DIR)/$(LINUX_LIB)
MAC_ARM64_LIB = $(MAC_ARM64_DIR)/$(MAC_LIB)
MAC_AMD64_LIB = $(MAC_AMD64_DIR)/$(MAC_LIB)

SRC = $(LIB_DIR)/tinytest.c

CC = zig cc
CFLAGS = -fPIC -Wall -Wextra -I./lib/

LINUX_LDFLAGS = -shared
MAC_LDFLAGS = -shared -dynamiclib

LINUX_AMD64_TARGET = -target x86_64-linux
LINUX_ARM64_TARGET = -target aarch64-linux
MAC_ARM64_TARGET = -target aarch64-macos
MAC_AMD64_TARGET = -target x86_64-macos

all: directories $(LINUX_AMD64_LIB) $(LINUX_ARM64_LIB) $(MAC_ARM64_LIB) $(MAC_AMD64_LIB)

linux: directories $(LINUX_AMD64_LIB) $(LINUX_ARM64_LIB)

macos: directories $(MAC_ARM64_LIB) $(MAC_AMD64_LIB)

directories:
	mkdir -p $(LINUX_AMD64_DIR)
	mkdir -p $(LINUX_ARM64_DIR)
	mkdir -p $(MAC_ARM64_DIR)
	mkdir -p $(MAC_AMD64_DIR)

$(LINUX_AMD64_LIB): $(SRC)
	$(CC) $(LINUX_AMD64_TARGET) $(CFLAGS) $(LINUX_LDFLAGS) $< -o $@

$(LINUX_ARM64_LIB): $(SRC)
	$(CC) $(LINUX_ARM64_TARGET) $(CFLAGS) $(LINUX_LDFLAGS) $< -o $@

$(MAC_ARM64_LIB): $(SRC)
	ZIG_LIBC=libc.txt $(CC) $(MAC_ARM64_TARGET) $(CFLAGS) $(MAC_LDFLAGS) $< -o $@

$(MAC_AMD64_LIB): $(SRC)
	ZIG_LIBC=libc.txt $(CC) $(MAC_AMD64_TARGET) $(CFLAGS) $(MAC_LDFLAGS) $< -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all linux macos clean directories
