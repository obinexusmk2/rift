# RIFT Is a Flexible Translator
# Cross-platform Makefile (Windows MinGW / Linux / macOS)
# Wraps CMake for a familiar make interface.

# --- Platform detection ---
ifeq ($(OS),Windows_NT)
    PLATFORM   := windows
    EXE        := .exe
    SHARED_EXT := .dll
    STATIC_EXT := .a
    RM         := del /Q /F
    RMDIR      := rmdir /S /Q
    MKDIR      := mkdir
    DEVNULL    := NUL
    # Prefer gcc over system Clang on MinGW (Clang has lld-link issues)
    CMAKE_C_FLAGS  := -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++
    CMAKE_GENERATOR := -G "MinGW Makefiles"
else
    UNAME := $(shell uname -s)
    ifeq ($(UNAME),Darwin)
        PLATFORM   := macos
        SHARED_EXT := .dylib
    else
        PLATFORM   := linux
        SHARED_EXT := .so
    endif
    EXE        :=
    STATIC_EXT := .a
    RM         := rm -f
    RMDIR      := rm -rf
    MKDIR      := mkdir -p
    DEVNULL    := /dev/null
    CMAKE_C_FLAGS  :=
    CMAKE_GENERATOR :=
endif

# --- Paths ---
BUILD_DIR  := build
BIN_DIR    := $(BUILD_DIR)/bin
LIB_DIR    := $(BUILD_DIR)/lib

RIFT_EXE   := $(BUILD_DIR)/rift$(EXE)
RIFT_STATIC:= $(BUILD_DIR)/librift$(STATIC_EXT)
RIFT_SHARED:= $(BUILD_DIR)/librift$(SHARED_EXT)

# --- Build type (default: Release) ---
BUILD_TYPE ?= Release

# --- Targets ---

.PHONY: all configure build clean test install help \
        debug release run doctor version

all: build

## Configure the CMake build directory
configure:
	cmake -S . -B $(BUILD_DIR) \
	    $(CMAKE_GENERATOR) \
	    $(CMAKE_C_FLAGS) \
	    -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) \
	    -DRIFT_BUILD_TESTS=ON \
	    -DRIFT_BUILD_SHARED=ON

## Build all targets (rift executable + static + shared library)
build: configure
	cmake --build $(BUILD_DIR)

## Build with Debug symbols
debug: BUILD_TYPE = Debug
debug: build

## Build optimized Release
release: BUILD_TYPE = Release
release: build

## Run the test suite
test: build
	cd $(BUILD_DIR) && ctest --output-on-failure

## Run rift doctor (diagnostics)
doctor: build
	$(RIFT_EXE) doctor

## Show rift version
version: build
	$(RIFT_EXE) --version

## Install to PREFIX (default: /usr/local on Unix, C:/rift on Windows)
ifeq ($(PLATFORM),windows)
PREFIX ?= C:/rift
else
PREFIX ?= /usr/local
endif

install: build
	cmake --install $(BUILD_DIR) --prefix $(PREFIX)

## Remove build artifacts
clean:
ifeq ($(PLATFORM),windows)
	-$(RMDIR) $(BUILD_DIR) 2>$(DEVNULL)
else
	$(RMDIR) $(BUILD_DIR)
endif

## Show this help
help:
	@echo "RIFT Is a Flexible Translator v5.0.0"
	@echo ""
	@echo "Usage: make [target] [BUILD_TYPE=Debug|Release]"
	@echo ""
	@echo "Targets:"
	@echo "  all        Build everything (default)"
	@echo "  build      Configure + build"
	@echo "  debug      Build with debug symbols"
	@echo "  release    Build optimized release"
	@echo "  test       Run test suite"
	@echo "  doctor     Run rift doctor diagnostics"
	@echo "  version    Show rift version"
	@echo "  install    Install to PREFIX=$(PREFIX)"
	@echo "  clean      Remove build directory"
	@echo "  help       Show this message"
	@echo ""
	@echo "Platform: $(PLATFORM)"
	@echo "Outputs:  $(RIFT_EXE)  $(RIFT_STATIC)  $(RIFT_SHARED)"
