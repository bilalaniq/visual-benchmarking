# Define compiler and flags
CXX = g++
CXXFLAGS = -Wall -g

# Define target executable name
TARGET = main

# Define object files
OBJ = main.o

# Default target (when you just type 'make')
all: $(TARGET)

# Rule to link object files into the executable
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

# Rule to compile each .cpp file into a .o object file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up object files and the target executable
clean:
	del /f $(OBJ) $(TARGET)
