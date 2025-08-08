# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -I/opt/homebrew/include

# Linker flags
LDFLAGS = -L/opt/homebrew/lib -lSDL2

# Source files
SRC = main.cpp

# Output executable
OUT = app

# Default target
all:
	$(CXX) $(SRC) $(CXXFLAGS) $(LDFLAGS) -o $(OUT)

# Clean build artifacts
clean:
	rm -f $(OUT)
