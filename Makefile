# Compiler and flags for compilation
CC = cc
CFLAGS = -Wall -Werror -Wextra
MDIR = mkdir -p
RM = rm

## Test directories
TEST_DIR = tests
TEST_DIR_SRC = $(TEST_DIR)/src
TEST_BIN_DIR = $(TEST_DIR)/bin
TESTED_LIB = libftprintf.a

## Name of the test main executable
TEST_BIN = main_test.o

## Library Test source
TEST_SRC = $(wildcard $(TEST_DIR_SRC)/*.c)

## Test source apps
TEST_DIR_APP = $(TEST_DIR)/tests-ft_printf
TEST_SRC_APP = $(wildcard $(TEST_DIR_APP)/*.c)

dirs:
	$(MDIR) $(TEST_BIN_DIR)

# Test: generate test binary and launch it
test: dirs
	$(CC) $(CFLAGS) -lbsd $(TEST_SRC) $(TEST_SRC_APP) $(TESTED_LIB) -o $(TEST_BIN_DIR)/$(TEST_BIN)
	./$(TEST_BIN_DIR)/$(TEST_BIN)

# clean test directories
clean:
	$(RM) -fr $(TEST_BIN_DIR)
	$(RM) $(TEST_DIR_SRC)/*.o

.PHONY: test clean dirs
