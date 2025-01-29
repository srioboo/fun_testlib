# fun_testlib

A helper library to allow test the libraries and project written in C

> [!WARNING]
> This is a personal library for learning purposes, it is not fully complete and can contain serveral errors, bad practices and mistakes. If you use the code of this repo is on your own responsability

## Usage

1. add to the root of your project with the name fun_testlib
2. edit the the files on the src-test to allow testing, add methos to the header file an change test_ft_dummy.c or add new files as needed
3. Change de Makefile to allow be call form the project Makefile
    - uncomment TEST_LIB_ROOT
    - add the needed libraries in TESTTED_LIBS
    - modify TEST_DIR_APP if needed
4. Change the include/testlib.h to add your app library to test

## Troubleshooting

1. In the Makefile, in order to use properly the library already compiled and zipped, it is necesary be careful with the order in the compilation

```shell
test: $(OBJS_TESTS)
   $(CC) $(CFLAGS) -I$(TEST_INCLUDE) $(SRCS_TESTS) -L$(TEST_LIB) -l:libfuntest.a -o $(TEST_BIN)
  ./$(TEST_BIN)
```

libfuntest.a mas be go after the source code
