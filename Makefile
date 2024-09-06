# Variables
CC = gcc            # The C compiler to use
CFLAGS = -Wall -g   # Compiler flags for warnings and debugging
LDFLAGS =           # Linker flags (no external libraries required)

# Target executable
TARGET = dbc2dbf

# Source files and object files
SRCS = dbc2dbf.c blast.c    # Source files
OBJS = $(SRCS:.c=.o)        # Object files

# Default target: builds the executable
all: $(TARGET)

# Build the target
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Compile C source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Run the test (You can adapt this to your actual test inputs/outputs)
test: $(TARGET)
	./$(TARGET) ABOAC1909.dbc ABOAC1909.dbf  # Replace with actual input and output file names

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets (to prevent conflicts with file names)
.PHONY: all clean test
