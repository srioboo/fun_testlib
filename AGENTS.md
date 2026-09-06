# AGENTS.md - AI Coding Agent Guide for fun_testlib

## Project Overview
**fun_testlib** is a C testing library designed to help test other C libraries. It provides colored output, structured test logging, and assertion functions. This is a learning/educational project following 42 School conventions.

## Key Architecture Patterns

### Build System: Two-Layer Makefile Architecture
- **Root Makefile** (`/Makefile`): Compiles the test library itself into `lib/libfuntest.a`
  - Uses `$(wildcard $(SRC)/*.c)` pattern to auto-discover sources
  - Produces static archive: `lib/libfuntest.a`
  - Targets: `all`, `clean`, `fclean`, `re`, `build`, `test`, `tclean`, `sane`, `val`

- **Test Makefile** (`src-tests/Makefile`): Compiles and runs user tests against the library
  - Links against the pre-built archive: `-l:libfuntest.a`
  - **Critical ordering requirement**: Library MUST come after source files in linker command (see README Troubleshooting)
  - Includes memory checking: `-fsanitize=address` (sane) and valgrind (val)

### Test Framework Pattern
Tests follow a consistent structure (see `src-tests/test_ft_dummy.c`):
1. Call `fun_method_name()` to allocate method name string
2. Call `fun_start()` to print test start marker
3. Call `fun_test_header()` or `fun_test_header_label()` for test numbering
4. Execute assertions (e.g., `fun_assert_int()`)
5. Call `fun_color_show()` to display color legend
6. Call `fun_end()` to print test end marker
7. Free the method name with `fun_free_str()`

### Assertion Types Available
- `fun_assert_int(orig, new)`: Compares two integers, prints [OK]/[KO] in color
- `fun_assert_int_fun(f_orig, f_new, str, ...)`: Variadic function comparison with string + int args

### Logging & Output
- All output uses ANSI color codes (defined in `funtestlib.h`)
- Structured printing with functions: `fun_group_start()`, `fun_start()`, `fun_end()`
- Color helpers: `fun_color_red()`, `fun_color_green()`, `fun_color_white()`
- Color constants for backgrounds: `COLOR_BLUE_BKG`, `COLOR_YELLOW`, etc.

## File Organization

```
fun_testlib/
├── src/                   # Library source (5 files: base, asserts, colors, show, utils)
├── include/funtestlib.h   # Main public API header
├── lib/                   # Output directory for libfuntest.a
├── src-tests/             # User test files (main_test.c, test.h, test_*.c)
└── Makefile               # Root build configuration
```

## Essential Workflows

### Compile Library
```bash
make all          # Builds lib/libfuntest.a from src/*.c
make re           # Full rebuild (fclean + all)
make clean        # Removes .o files only
make fclean       # Removes .o files AND libfuntest.a
```

### Run Tests
```bash
make test         # Builds library → copies includes/libs to src-tests → runs tests
make tclean       # Cleans test artifacts
make sane         # Run with address sanitizer (-fsanitize=address)
make val          # Run with valgrind leak detection
```

### Test Development Cycle
1. Edit `src-tests/test_*.c` to add/modify tests
2. Declare test function in `src-tests/test.h`
3. Call test function from `src-tests/main_test.c`
4. Run `make test` (automatically rebuilds library and copies dependencies)

## Code Conventions & Patterns

### File Header Format
All source files use a specific header format (see examples):
```c
/* ************************************************************************** */
/*                                                                            */
/*   filename.c                                           :+:      :+:    :+:   */
/*                                                                            */
/* ************************************************************************** */
```

### Function Naming
- Library functions: `fun_*` prefix (e.g., `fun_assert_int`, `fun_color_red`)
- Test functions: `test_*` prefix (e.g., `test_ft_dummy`)
- Color functions: Return `char*` to color codes, use printf directly

### Memory Management Pattern
Strings allocated by `fun_method_name()` MUST be freed with `fun_free_str()` after use.

### Variadic Function Assertion
`fun_assert_int_fun()` uses `va_list` to forward variadic args. Always pass string + one int arg.

## Integration Points

### Adding New Tests to a Project
1. Copy `libfuntest.a` to your project's lib directory
2. Copy header file to your includes
3. Create `src-tests/Makefile` following the template (link with `-l:libfuntest.a`)
4. Create test files and declare them in `test.h`, call from `main_test.c`

### Linking External Libraries to Test
In `src-tests/Makefile`, set `LIB_TESTED` variable:
```makefile
LIB_TESTED = -L/path/to/lib -l:your_lib.a
```

## Important Constraints

- **Compiler flags are strict**: `-Wall -Werror -Wextra` (no warnings allowed)
- **Library linking order matters**: Sources before `-l:libfuntest.a` in compiler command
- **Test output is colored**: No way to disable; assume ANSI color support in environment
- **Memory safety**: Project includes sanitizer and valgrind support; use `make sane` or `make val` for checking

## Extension Points

### Adding New Assertion Types
1. Create function in `src/ft_test_asserts.c`
2. Add declaration to `include/funtestlib.h`
3. Use consistent naming: `fun_assert_*` prefix
4. Follow color output pattern (green for OK, red for KO)

### Adding New Output Helpers
Place in `src/ft_test_show.c` or `src/ft_test_base.c` depending on whether it's display-related.

## Code Styling

- Don't allow more than 5 functions in each file
