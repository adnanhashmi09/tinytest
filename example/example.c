// Change the following path to wherever you
// end up saving the tinytest.h file
#include "../lib/tinytest.h"

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
