#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error_codes.h"
#include "tinytest.h"

TestCase *testcases = NULL;
TestCase *currentTest = NULL;
int passed, failed = 0;

int failed_flag = 0;

void addTest(char *name, void (*test_function)(void)) {
  TestCase *test = (TestCase *)malloc(sizeof(TestCase));
  if (test == NULL) {
    exit(MEMORY_ALLOCATION_FOR_TESTS_FAILED);
  }
  strncpy(test->name, name, MAX_TESTCASE_NAME_LENGTH - 1);
  test->name[MAX_TESTCASE_NAME_LENGTH - 1] = '\0';
  test->testCaseFunction = test_function;
  if (testcases == NULL) {
    testcases = test;
    currentTest = test;
  } else {
    currentTest->next = test;
    currentTest = currentTest->next;
  }
  currentTest->next = NULL;
}

void assert_condition(int condition, const char *failure_message) {
  if (condition > 1 || condition < 0) {
    printf(ANSI_COLOR_RED
           "The condition expression should resolve to either 0 or 1. Got "
           "value %d \n" ANSI_COLOR_RESET,
           condition);
    exit(ASSERT_CONDITION_RESOLVES_TO_NON_BOOLEAN);
  }
  if (!condition) {
    printf(ANSI_COLOR_RED "  Assertion failed: %s\n" ANSI_COLOR_RESET,
           failure_message);
    failed_flag = 1;
  }
}

void runTests() {
  TestCase *test = testcases;
  while (test != NULL) {
    failed_flag = 0;
    test->testCaseFunction();
    if (failed_flag > 0) {
      printf(ANSI_COLOR_RED " ✘ [Test Case] %s: Failed\n" ANSI_COLOR_RESET,
             test->name);
      failed++;
    } else {
      printf(ANSI_COLOR_GREEN "  ✓ [Test Case] %s: Passed\n" ANSI_COLOR_RESET,
             test->name);
      passed++;
    }

    test = test->next;
  }

  printf("\n============TEST REPORT============\n");
  printf("Tests passed = %d, Tests failed = %d\n", passed, failed);

  if (failed > 0) {
    exit(TESTS_FAILED_ERROR_CODE);
  }
}
