# Compiler settings
CC = gcc
CFLAGS = -Iinclude -Wall # Include the header file directory

# Build target executable
TARGET = dispatcher

# Source and object directories
SRCDIR = src
OBJDIR = obj
INCDIR = include

# Find all .c files in the src directory
SOURCES = $(wildcard $(SRCDIR)/*.c)
# Replace the path and extension to compile into the obj directory
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))

# Default target
all: $(TARGET)

# Link object files into the executable
$(TARGET): $(OBJECTS)
	$(CC) $^ -o $@

# Compile source files into object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up the build
clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: all clean
