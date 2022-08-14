#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "modules/grid/game_character.h"
#include "modules/grid/grid.h"
#include "modules/test/test.h"

int test_create_grid();
int test_mark_on_grid();
int test_flush_grid();
int test_compare_grid();
int test_destroy_grid();
int test_grid_to_string();
int test_parse_string_to_grid();

// TODO : Update the following tests later on
// int test_get_grid_last_update_location();
// int test_get_no_of_entries_made_in_grid();
// int test_get_grid_recent_status();
// int test_set_grid_last_update_location();
// int test_set_grid_recent_status();

int main()
{
    const int total_test_cases = 7;

    int test_cases_passed = test_create_grid() +
        test_mark_on_grid() +
        test_flush_grid() +
        test_compare_grid() +
        test_destroy_grid() +
        test_grid_to_string() +
        test_parse_string_to_grid();

    return total_test_cases - test_cases_passed;
}

// Test if create_grid() can create an instance of grid
int test_create_grid() {
    // assume

    // act
    grid_struct* grid = create_grid();

    // assert
    bool test_passed = grid != NULL && grid->contents != NULL;

    print_test_status(test_passed, "create_grid()");
    return test_passed;
}

int test_mark_on_grid() {
    // assume
    grid_struct input_grid = {
        "0X.......",
        2,
        ONGOING
    };



    // act

    // assert
}

int test_flush_grid() {
    // assume

    // act

    // assert
}

int test_compare_grid() {
    // assume

    // act

    // assert
}

int test_destroy_grid() {
    // assume

    // act

    // assert
}

int test_grid_to_string() {
    // assume

    // act

    // assert
}

int test_parse_string_to_grid() {
    // assume

    // act

    // assert
}

