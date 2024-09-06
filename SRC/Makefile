# Variables
CC = gcc            # The C compiler to use
CFLAGS = -Wall -g   # Compiler flags for warnings and debugging
LDFLAGS =           # Linker flags

# Check if we're cross-compiling for Windows (mingw)
ifeq ($(findstring mingw,$(TARGET)),mingw)
    LDFLAGS += -no-undefined
endif

# Target executable
TARGET = dbc2dbf

# Source files and object files
SRCS = dbc2dbf.c blast.c    # Source files
OBJS = $(SRCS:.c=.o)        # Object files

# Default target: builds the executable
all: $(TARGET)

# Build the target
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compile C source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Run the test using ABOAC1909.dbc and ABOAC1909.dbf in the current directory
test: $(TARGET)
	@if [ -f "ABOAC1909.dbc" ]; then \
		./$(TARGET) "ABOAC1909.dbc" "ABOAC1909.dbf"; \
		echo "Test completed. Output written to ABOAC1909.dbf."; \
	else \
		echo "Error: ABOAC1909.dbc not found."; \
	fi

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets (to prevent conflicts with file names)
.PHONY: all clean test
