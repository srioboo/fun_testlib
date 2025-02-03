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

1. add the include file funtestlib.h to the include directory of your project and add the header of the libraries to test
2. add the libfuntest.a in the directory lib of your project
3. add the src-test directory to your project, and change/add your test
4. add to the Makefile of the project the following tasks:

  ```makefile
  # TEST Section
  test: all
    $(MAKE) -f src-tests/Makefile test

  tclean:
    $(MAKE) -f src-tests/Makefile tclean

  # Memory leaks detection
  sane:
    $(MAKE) -f src-tests/Makefile sane

  val: 
    $(MAKE) -f src-tests/Makefile val 
  ```

add to the test Makefile the library to tests

## Troubleshooting

1. In the Makefile, in order to use properly the library already compiled and zipped, it is necesary be careful with the order in the compilation

```shell
test: $(OBJS_TESTS)
   $(CC) $(CFLAGS) -I$(TEST_INCLUDE) $(SRCS_TESTS) -L$(TEST_LIB) -l:libfuntest.a -o $(TEST_BIN)
  ./$(TEST_BIN)
```

libfuntest.a mas be go after the source code
