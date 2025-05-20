# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -g -I recursion

# Name of execution file
TARGET = main

# List of source files
SRC = main.cpp recursion/recursion.cpp

# Default command
all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# Clean command
clean:
	rm -f $(TARGET)

# Compile and run command
run: all
	./$(TARGET)
