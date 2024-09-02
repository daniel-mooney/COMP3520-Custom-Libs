CC = gcc
CFLAGS = -Wall -g -pedantic -std=c11 -fsanitize=address
TARGET = queue_test

# Collect source and object files
SRC_DIR = data_structures
OBJ_DIR = build
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))


all: $(TARGET)

$(TARGET): $(OBJ) $(TARGET).c
	$(CC) $(CFLAGS) -o $@.exe $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Pipe `|` means order-only prerequisite i.e. only check if $(OBJ_DIR) exists, not timestamp
$(OBJ): | $(OBJ_DIR)		

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

clean:
	rm -f $(TARGET).exe
	rm -rf $(OBJ_DIR)