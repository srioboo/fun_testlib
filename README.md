# fun_testlib

A helper library to allow test the libraries and project written in C

> [!WARNING]
> This is a personal library for learning purposes, it is not fully complete and can contain serveral errors, bad practices and mistakes. If you use the code of this repo is on your own responsability

## Usage

### Compile and generate lib

1. download or clone the project
2. do `make all`
3. the library will be generated in the lib directory

### Use the libraries
1. add the include file funtestlib.h to the include directory of your project
2. add the libfuntest.a in the directory lib of your project
3. add the src-test directory to your project, and change/add your
4. add to the Makefile the following tasks:
  ```makefile
    # Test: generate test binary
    test: $(TEST_OBJS)
      $(CC) $(CFLAGS) -I$(INCLUDE) $(TEST_SRCS) -L$(LIB) -l:$(LIB_NAME) -o $(TEST_BIN)
      ./$(TEST_BIN)
  ```
The variables needed are:

```makefile
    # Library name
    LIB_NAME = libfuntest.a
    
    # Compiler and flags for compilation
    CC = cc
    CFLAGS = -Wall -Werror -Wextra

    # Directories
    INCLUDE = include
    LIB = lib

    ## Name of the test main executable
    TEST_BIN = test.out

    ## Library Test source and objects
    TEST_SRCS = $(wildcard src-tests/*.c)
    TEST_OBJS = $(TEST_SRCS:.c=.o)
``` 

## Troubleshooting

1. In the Makefile, in order to use properly the library already compiled and zipped, it is necesary be careful with the order in the compilation

```shell
test: $(OBJS_TESTS)
   $(CC) $(CFLAGS) -I$(TEST_INCLUDE) $(SRCS_TESTS) -L$(TEST_LIB) -l:libfuntest.a -o $(TEST_BIN)
  ./$(TEST_BIN)
```

libfuntest.a mas be go after the source code
