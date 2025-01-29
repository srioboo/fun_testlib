# Library name
LIB_NAME = libfuntest.a

# Compiler and flags for compilation
CC = cc
CFLAGS = -Wall -Werror -Wextra
MDIR = mkdir -p
RM = rm -f
AR = ar rcs

# Directories
INCLUDE = include
LIB = lib
SRC = src

## Library source and objects
SRCS = $(wildcard $(SRC)/*.c)
OBJS = $(SRCS:.c=.o)

# Tasks
all: $(LIB_NAME)

# create objects and packaging
$(LIB_NAME): $(OBJS)
	$(AR) $(LIB)/$(LIB_NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -Iinclude -c $< -o $@

# clean directories
clean:
	$(RM) $(SRC)/*.o

fclean: clean
	$(RM) $(LIB)/$(LIB_NAME)

# relink
re: fclean all

# TEST Section
## Name of the test main executable
TEST_BIN = test.out

## Library Test source and objects
TEST_SRCS = $(wildcard src-tests/*.c)
TEST_OBJS = $(TEST_SRCS:.c=.o)

# Test: generate test binary
test: $(TEST_OBJS)
	$(CC) $(CFLAGS) -I$(INCLUDE) $(TEST_SRCS) -L$(LIB) -l:$(LIB_NAME) -o $(TEST_BIN)
	./$(TEST_BIN)

# clean test directories
tclean:
	$(RM) $(TEST_OBJS) $(TEST_BIN)

# Memory leaks detection
sane: all
	$(CC) $(CFLAGS) -I$(INCLUDE) $(TEST_SRCS) -L$(LIB) -l:$(LIB_NAME) -o $(TEST_BIN) -fsanitize=address -g
	./$(TEST_BIN)

val: all
	$(CC) $(CFLAGS) -I$(INCLUDE) $(TEST_SRCS) -L$(LIB) -l:$(LIB_NAME) -o $(TEST_BIN)
	valgrind --leak-check=full ./$(TEST_BIN)

.PHONY: all clean fclean re sane val