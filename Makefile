GCC_VERSION := $(shell g++ --version)
IS_MINGW64 := $(findstring W64, $(GCC_VERSION))

cpuinfo:
ifneq ($(OS),Windows_NT)
	@echo "Building *nix executable"
	g++ main.cpp -Wformat=0 -o cpuinfo
else ifeq ($(IS_MINGW64),W64)
	@echo "Building Windows executable (MinGW64 mode)"
	g++ -static -static-libgcc -static-libstdc++ main.cpp -o cpuinfo64.exe
else
	@echo "Building Windows executable (MinGW 32-bit mode)"
	g++ -static-libgcc -static-libstdc++ main.cpp -o cpuinfo.exe
endif
