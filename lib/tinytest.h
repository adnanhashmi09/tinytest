#ifndef TINY_TEST_H
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TESTCASE_NAME_LENGTH 100

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define EPSILON 1e-6

struct TestCaseType {
  char name[MAX_TESTCASE_NAME_LENGTH];
  void (*testCaseFunction)(void);
  struct TestCaseType *next;
};
typedef struct TestCaseType TestCase;

extern int failed_flag;

static inline bool compare_int(int a, int b) { return a == b; }

static inline bool compare_float(float a, float b) {
  return fabs(a - b) < EPSILON;
}

static inline bool compare_double(double a, double b) {
  return fabs(a - b) < EPSILON;
}

static inline bool compare_string(const char *a, const char *b) {
  return strcmp(a, b) == 0;
}

static inline void print_int(int x) { printf("%d", x); }
static inline void print_float(float x) { printf("%f", x); }
static inline void print_double(double x) { printf("%lf", x); }
static inline void print_string(const char *x) { printf("%s", x); }

#define COMPARE(x, y)                                                          \
  _Generic((x),                                                                \
      int: compare_int,                                                        \
      float: compare_float,                                                    \
      double: compare_double,                                                  \
      char *: compare_string,                                                  \
      const char *: compare_string)((x), (y))

#define PRINT_VALUE(x)                                                         \
  _Generic((x),                                                                \
      int: print_int,                                                          \
      float: print_float,                                                      \
      double: print_double,                                                    \
      char *: print_string,                                                    \
      const char *: print_string)((x))

#define assert_equal(left, right, failure_message)                             \
  do {                                                                         \
    if (!COMPARE(left, right)) {                                               \
      printf(ANSI_COLOR_RED "  Assertion failed: %s\n" ANSI_COLOR_RESET,       \
             failure_message);                                                 \
      printf(ANSI_COLOR_RED "  Left = ");                                      \
      PRINT_VALUE(left);                                                       \
      printf("\n" ANSI_COLOR_RESET);                                           \
      printf(ANSI_COLOR_RED "  Right = ");                                     \
      PRINT_VALUE(right);                                                      \
      printf("\n" ANSI_COLOR_RESET);                                           \
      failed_flag = 1;                                                         \
    }                                                                          \
  } while (0)

void addTest(char *name, void (*test_function)(void));
void assert_condition(int condition, const char *failure_message);
void runTests();

#endif // !TINY_TEST_H
