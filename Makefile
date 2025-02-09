# Library name
LIB_NAME = libfuntest.a

# Compiler and flags for compilation
CC = @cc
CFLAGS = -Wall -Werror -Wextra
RM = @rm -f
AR = @ar rcs

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
	$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

# clean directories
clean:
	$(RM) $(SRC)/*.o

fclean: clean
	$(RM) $(LIB)/$(LIB_NAME)

# relink
re: fclean all

# build
build: all
	cp -r include src-tests
	cp -r lib src-tests

# TEST Section
test: build
	$(MAKE) -f src-tests/Makefile test

tclean:
	$(MAKE) -f src-tests/Makefile tclean

# Memory leaks detection
sane:
	$(MAKE) -f src-tests/Makefile sane

val: 
	$(MAKE) -f src-tests/Makefile val

.PHONY: all clean fclean re build test tclean sane val