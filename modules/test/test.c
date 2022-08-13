// Defines all the functions that can be used for aiding the testing of other functions

#include <stdbool.h>
#include <stdio.h>

#include "test.h"

void print_test_status(bool test_passed, char* function_name) {
    test_passed ?
        printf ("%s passed\n", function_name):  
        printf ("%s failed\n", function_name);
}