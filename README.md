# fun_testlib

A C testing framework for validating C libraries and projects with colored output, structured logging, and assertion utilities.

> [!WARNING]
> This is a personal learning project from 42 School. It is not production-ready and may contain errors or incomplete features. Use at your own risk.

## Features

- **Colored output** – Color-coded test results (OK/KO) with customizable ANSI colors
- **Structured logging** – Test groups, headers, and method start/end markers
- **Multiple assertion types** – Integer comparisons, variadic function assertions
- **Memory debugging** – Integration with AddressSanitizer and Valgrind
- **Flexible test organization** – Easy to write, organize, and run test suites

## Quick Start

### 1. Build the Library

```bash
git clone <repo>
cd fun_testlib
make all
```

This generates `lib/libfuntest.a` from sources in `src/`.

### 2. Use in Your Project

#### Option A: Copy Files (Recommended for Small Projects)

```bash
# Copy library and headers to your project
cp lib/libfuntest.a /path/to/your/project/lib/
cp include/funtestlib.h /path/to/your/project/include/
cp -r src-tests /path/to/your/project/
```

#### Option B: Reference from fun_testlib

Build fun_testlib, then link directly from its `lib/` directory in your project's Makefile.

### 3. Create a Test File

Create `src-tests/test_my_lib.c`:

```c
#include "test.h"

int test_my_lib(int active)
{
    char *method = fun_method_name("test_my_lib");
    int result = 0;
    
    if (active != 0)
    {
        fun_start(method);
        fun_test_header(1);
        
        // Test your function
        int expected = 42;
        int actual = my_function();
        fun_assert_int(expected, actual);
        
        fun_color_show();
        fun_end(method);
    }
    method = fun_free_str(method);
    return (result);
}
```

### 4. Register Test in test.h

```c
#ifndef TEST_H
# define TEST_H

# include "funtestlib.h"

int test_my_lib(int active);

#endif
```

### 5. Call from main_test.c

```c
#include "test.h"

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    
    fun_group_start("MY LIBRARY TESTS");
    test_my_lib(1);
    
    return (0);
}
```

### 6. Build Tests

Update your project's `Makefile`:

```makefile
# TEST Section
test: all
	$(MAKE) -f src-tests/Makefile test

tclean:
	$(MAKE) -f src-tests/Makefile tclean

# Memory leak detection with AddressSanitizer
sane:
	$(MAKE) -f src-tests/Makefile sane

# Memory leak detection with Valgrind
val:
	$(MAKE) -f src-tests/Makefile val

.PHONY: test tclean sane val
```

Then update `src-tests/Makefile` to include your libraries:

```makefile
LIB_TESTED = -L/path/to/your/lib -l:your_lib.a

# ... rest of Makefile
```

Run tests with:

```bash
make test    # Run tests
make sane    # Run with AddressSanitizer (detects memory errors)
make val     # Run with Valgrind (detailed leak detection)
make tclean  # Clean test artifacts
```

## API Overview

### Test Structure Functions

| Function | Purpose |
|----------|---------|
| `fun_group_start(const char *msg)` | Print test group header with blue background |
| `fun_start(const char *msg)` | Print test start marker |
| `fun_end(const char *msg)` | Print test end marker |
| `fun_test_header(int num)` | Print numbered test header |
| `fun_test_header_label(int num, char *str)` | Print numbered test header with label |

### Assertion Functions

| Function | Purpose |
|----------|---------|
| `fun_assert_int(int orig, int new)` | Compare two integers, print OK/KO |
| `fun_assert_int_fun(f_orig, f_new, str, ...)` | Compare output of two functions with variadic args |

### Utility Functions

| Function | Purpose |
|----------|---------|
| `fun_method_name(char *text)` | Allocate memory for method name string |
| `fun_free_str(char *text)` | Free and null-terminate string |
| `fun_show_data(char **message)` | Print formatted data |
| `fun_show_orig_new(f1, f2, msg)` | Compare output of two functions |

### Color Functions

| Function | Return Value |
|----------|--------------|
| `fun_color_red()` | Red ANSI color code |
| `fun_color_green()` | Green ANSI color code |
| `fun_color_white()` | White ANSI color code |
| `fun_color_show()` | Print legend of all colors |

**ANSI Color Constants** (use directly in printf):
```c
COLOR_RED, COLOR_GREEN, COLOR_YELLOW, COLOR_BLUE, COLOR_MAGENTA, COLOR_CYAN
COLOR_RED_BKG, COLOR_GREEN_BKG, COLOR_YELLOW_BKG, // backgrounds
COLOR_RESET  // reset formatting
```

## Project Structure

```
fun_testlib/
├── src/                        # Library source files
│   ├── ft_test_base.c         # Group/test start/end functions
│   ├── ft_test_asserts.c      # Assertion implementations
│   ├── ft_test_colors.c       # Color handling
│   ├── ft_test_show.c         # Data display functions
│   └── ft_test_utils.c        # Memory utilities
├── include/
│   └── funtestlib.h           # Main public header
├── lib/                        # Output directory (libfuntest.a)
├── src-tests/                 # Example test suite
│   ├── Makefile               # Test build configuration
│   ├── test.h                 # Test declarations
│   ├── main_test.c            # Test entry point
│   └── test_ft_dummy.c        # Example test
├── Makefile                   # Library build configuration
└── README.md
```

## Compilation Details

### Building the Library

```bash
make all      # Compile src/*.c → lib/libfuntest.a
make clean    # Remove .o object files
make fclean   # Remove .o files and library
make re       # Full rebuild (fclean + all)
```

**Compiler flags**: `-Wall -Werror -Wextra` (strict, no warnings allowed)

### Building Tests

Tests use a two-stage Makefile system:

1. **Root Makefile** (`Makefile`): Builds library
2. **Test Makefile** (`src-tests/Makefile`): Compiles and runs tests against the library

The test Makefile compiles test sources and links against the precompiled `libfuntest.a`.

## Common Patterns

### Testing a Function

```c
void test_string_functions(int active)
{
    char *method = fun_method_name("test_string_functions");
    
    if (active)
    {
        fun_group_start("STRING UTILITIES");
        fun_start(method);
        
        fun_test_header_label(1, "strlen test");
        fun_assert_int(5, my_strlen("hello"));
        
        fun_test_header_label(2, "strcmp test");
        fun_assert_int(0, my_strcmp("abc", "abc"));
        
        fun_color_show();
        fun_end(method);
    }
    
    method = fun_free_str(method);
}
```

### Testing with Variadic Functions

```c
fun_assert_int_fun(original_printf, my_printf, "format: %s", "test_value");
```

## Troubleshooting

### Issue: Linking Errors / Undefined Reference

**Problem**: Library not found or symbols not defined.

**Solution**: Ensure library comes AFTER source files in linker command:

```makefile
# ✅ CORRECT
$(CC) $(CFLAGS) -I$(INCLUDE) $(SRCS) -L$(LIB) -l:libfuntest.a -o $(BIN)

# ❌ WRONG
$(CC) $(CFLAGS) -I$(INCLUDE) -L$(LIB) -l:libfuntest.a $(SRCS) -o $(BIN)
```

### Issue: Compilation Errors (Wall/Werror)

**Problem**: `-Werror` flag treats warnings as errors.

**Solution**: Fix all compiler warnings. Common issues:
- Unused variables: Use `(void)var;` to suppress
- Implicit declarations: Include proper headers
- Missing prototypes: Declare functions before use

### Issue: Memory Leaks Detected

**Problem**: AddressSanitizer or Valgrind reports memory errors.

**Solution**:
- Always pair `fun_method_name()` with `fun_free_str()`
- Check for malloc/free imbalances in your test code
- Run with `make sane` for better error messages

### Issue: Colored Output Not Appearing

**Problem**: Output appears plain without colors.

**Solution**: Ensure your terminal supports ANSI color codes. Some options:
- Run directly in terminal (not captured/piped output)
- Force colors with: `TERM=xterm-256color make test`

## Learning Goals

This project demonstrates:
- Static library creation with Make
- ANSI color codes for terminal output
- Variadic function handling
- Memory safety (using sanitizers and Valgrind)
- Test framework design
- Makefile advanced features (wildcard, pattern rules)
