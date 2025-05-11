# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -g -I utils -I 1d_array -I 2d_array

# Name of execution file
TARGET = main

# List of source files
SRC = main.cpp utils/format_utils.cpp 1d_array/array_1d_utils.cpp 2d_array/array_2d_utils.cpp

# Default command
all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# Clean command
clean:
	rm -f $(TARGET)

# Compile and run command
run: all
	./$(TARGET)
