# Project-owned Picolibc build using the pristine src/ submodule.
PROJECT_ROOT ?= $(abspath ..)
BUILD_DIR ?= $(PROJECT_ROOT)/build/picolibc
SOURCE_DIR = $(CURDIR)/src
TOOLCHAIN_FILE = $(CURDIR)/toolchain.cmake
CMAKE_CACHE = $(BUILD_DIR)/CMakeCache.txt
LIBC = $(BUILD_DIR)/libc.a

.PHONY: all build clean clean-all

all: build

build: $(LIBC)

$(CMAKE_CACHE): src/CMakeLists.txt toolchain.cmake Makefile
	cmake -S $(SOURCE_DIR) -B $(BUILD_DIR) \
		-DCMAKE_TOOLCHAIN_FILE=$(TOOLCHAIN_FILE) \
		-DCMAKE_BUILD_TYPE=MinSizeRel

$(LIBC): $(CMAKE_CACHE)
	cmake --build $(BUILD_DIR) --target c

clean:
	cmake --build $(BUILD_DIR) --target clean 2> /dev/null || true

clean-all: clean
	rm -rf $(BUILD_DIR)
