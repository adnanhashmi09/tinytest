# tinytest - A Simple and Tiny C Testing Library

`tinytest` is a simple and lightweight unit testing library for C projects. It provides a minimal set of macros and functions to write, run, and report tests in a concise and easy-to-use manner.

## Features

- **Simplicity**: Minimal API with just a few macros and functions to get started.
- **Flexibility**: Write tests using plain C code without any external dependencies.
- **Portability**: Works on multiple platforms (Linux, macOS) and architectures (x86, ARM).
- **Ease of Integration**: Seamlessly integrate into your existing C projects.

## Installation

Download the required files from the releases:
- `tinytest.h` - Header file
- `libtinytest.so` - Shared library (Linux)
- `libtinytest.dylib` - Dynamic library (macOS)

## API Reference

### Main Functions
```c
assert_equal(left, right, failure_message);
// Compares two values of the same type (int, float, double, or string)
// Prints detailed error message if values don't match

assert_condition(condition, failure_message);
// Tests if a boolean condition is true

addTest(test_name, function_running_the_test_case);
// Add the Test case to be run

runTests();
// Run all the Test cases

```

### Compilation
```bash
# Linux
gcc -Wall -Wextra test_file.c -L/path/to/lib -ltinytest -o test_program

# macOS
gcc -Wall -Wextra test_file.c -L/path/to/lib -ltinytest -o test_program
```

Make sure the library is in your library path or use `LD_LIBRARY_PATH` (Linux) or `DYLD_LIBRARY_PATH` (macOS).

### Usage Example
```c
#include "tinytest.h"

void test_addition() {
    int result = 2 + 2;
    assert_equal(result, 5, "2 + 2 should equal 4");
    assert_condition(result > 0, "Result should be positive");
}

void test_string_comparison() {
    const char *str = "hello";
    assert_equal(str, "hello", "String should match 'hello'");
}

int main() {
    addTest("Addition Test", test_addition);
    addTest("String Test", test_string_comparison);
    runTests();
    return 0;
}
```
### Output
```bash
  Assertion failed: 2 + 2 should equal 4
  Left = 4
  Right = 5
 ✘ [Test Case] Addition Test: Failed
  ✓ [Test Case] String Test: Passed

============TEST REPORT============
Tests passed = 1, Tests failed = 1
```

## Type Support
The library supports comparison of these types:

`int` \
`float` (with epsilon comparison) \
`double` (with epsilon comparison) \
`char*` and `const char*` (string comparison)
