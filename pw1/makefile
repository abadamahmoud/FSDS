# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -Wcast-align -Wconversion -Wsign-conversion -Wnull-dereference -g3 -O0

# Source files
SRC = $(wildcard *.cpp)

# Object files
OBJ = $(SRC:.cpp=.o)

# Output file
OUT = ./build/Debug/outDebug

# Create the output directory
$(shell mkdir -p ./build/Debug)

# Target: Compile all files and link
$(OUT): $(OBJ)
	$(CXX) $(OBJ) -o $(OUT)

# Rule to compile .cpp to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the program
run: $(OUT)
	./$(OUT)

# Clean the project
clean:
	rm -f $(OBJ) $(OUT)

# Phony targets (no files named 'clean' or 'run' will be created)
.PHONY: clean run
