# Compiler and flags for compilation
CC = cc
CFLAGS = -Wall -Werror -Wextra
MDIR = mkdir -p
RM = rm

## Test library directories
# uncoment TEST_LIB_ROOT value once in the app 
TEST_LIB_ROOT = # fun_testlib/
TEST_DIR_SRC = $(TEST_LIB_ROOT)src
TEST_BIN_DIR = $(TEST_LIB_ROOT)bin

## Name of the test main executable
TEST_BIN = fun_test_lib.o

## Library Test source
TEST_SRC = $(wildcard $(TEST_DIR_SRC)/*.c)

## Test source apps
TEST_DIR_APP = $(TEST_LIB_ROOT)src-tests
TEST_SRC_APP = $(wildcard $(TEST_DIR_APP)/*.c)
TESTED_LIBS = # ADD APPS LIBRARIES HERE

dirs:
	$(MDIR) $(TEST_BIN_DIR)

# Test: generate test binary and launch it
test: dirs
	$(CC) $(CFLAGS) -I$(TEST_LIB_ROOT)include -lbsd $(TEST_SRC) $(TEST_SRC_APP) $(TESTED_LIBS) -o $(TEST_BIN_DIR)/$(TEST_BIN)
	./$(TEST_BIN_DIR)/$(TEST_BIN)

# clean test directories
clean:
	$(RM) -fr $(TEST_BIN_DIR)

# detect memory leaks
sane:
	$(CC) $(CFLAGS) -I$(TEST_LIB_ROOT)include -lbsd $(TEST_SRC) $(TEST_SRC_APP) $(TESTED_LIBS) -o $(TEST_BIN_DIR)/$(TEST_BIN) -fsanitize=address -g
	./$(TEST_BIN_DIR)/$(TEST_BIN)

val:
	$(CC) $(CFLAGS) -I$(TEST_LIB_ROOT)include -lbsd $(TEST_SRC) $(TEST_SRC_APP) $(TESTED_LIBS) -o $(TEST_BIN_DIR)/$(TEST_BIN) -fsanitize=address -g
	valgrind --leak-check=full ./$(TEST_BIN_DIR)/$(TEST_BIN)


.PHONY: test clean dirs
