# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -g -I fraction_helper -I student_helper

# Name of execution file
TARGET = main

# List of source files
SRC = main.cpp fraction_helper/fraction_utils.cpp student_helper/student_utils.cpp

# Default command
all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# Clean command
clean:
	rm -f $(TARGET)

# Compile and run command
run: all
	./$(TARGET)
