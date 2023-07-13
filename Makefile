CC = clang
CFLAGS = -Wall
LDFLAGS = -lSDL2 -lSDL2_ttf -lSDL2_image
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
RES_DIR = res

# Find all .c files recursively in the source directory and its subdirectories
SRCS := $(shell find $(SRC_DIR) -name '*.c')

# Generate object file names from source file names
OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Set the name of the final executable
TARGET = $(BIN_DIR)/explore

# Default target
all: $(TARGET)

# Compile .c files into .o files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files to create the final executable
$(TARGET): $(OBJS)
	@mkdir -p $(@D)
	$(CC) $(OBJS) $(LDFLAGS) -o $(TARGET)
	cp -r $(RES_DIR) $(BIN_DIR)/

# Clean build artifacts
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

run :
	./bin/explore

br : all run

# Phony targets (not associated with files)
.PHONY: all clean
