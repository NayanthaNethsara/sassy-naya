CXX = g++
CXXFLAGS = -std=c++17 -I/opt/homebrew/include -Iinclude
LDFLAGS = -L/opt/homebrew/lib -lSDL2

SRC = src/main.cpp src/snake.cpp src/food.cpp
OUT = app

all:
	$(CXX) $(SRC) $(CXXFLAGS) $(LDFLAGS) -o $(OUT)

clean:
	rm -f $(OUT)
