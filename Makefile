# Makefile for running test cases
CC = g++
CPPFLAGS = -Wall -g -pedantic -std=c++11 -fsanitize=address
TESTLIBS = -lgtest -lgtest_main -lpthread

TEST_DIR = tests
OBJ_DIR = build

# Target to test
ifeq ($(MAKECMDGOALS), test)
	ifndef TARGET
		$(error TARGET to test is not defined)
	endif
endif

# TEST_DEPS =

# Get the directory of the target
TARGET_DIR = $(dir $(TARGET))
TARGET_FILENAME = $(notdir $(TARGET))

# Convert to test file path
TEST_FILE = $(TEST_DIR)/$(TARGET_DIR)test_$(TARGET_FILENAME)pp
TEST_TARGET = $(patsubst %.c, test_%.exe, $(TARGET_FILENAME))

# TEST_DEPS_OBJ = $(patsubst %.c, $(OBJ_DIR)/test_%.o, $(TARGET_FILENAME))

# Object files
TARGET_OBJ = $(OBJ_DIR)/$(TARGET_FILENAME).o
TEST_OBJ = $(OBJ_DIR)/test_$(TARGET_FILENAME).o


test: $(TEST_TARGET)

$(TEST_TARGET): $(TARGET_OBJ) $(TEST_OBJ)
	$(CC) $(CPPFLAGS) -o $@ $^ $(TESTLIBS)
	./$@

# Create target and test object files
$(TARGET_OBJ): $(TARGET)
	$(CC) $(CPPFLAGS) -c -o $@ $<

$(TEST_OBJ): $(TEST_FILE)
	$(CC) $(CPPFLAGS) -c -o $@ $<


# Create object directory
$(TARGET_OBJ) $(TEST_OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean up
clean:
	rm -f test_*.exe $(OBJ_DIR)/*.o
	rm -rf $(OBJ_DIR)