#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "modules/grid/game_character.h"
#include "modules/grid/grid.h"
#include "modules/test/test.h"

int test_create_grid();
int test_mark_on_grid_with_blank_to_ongoing();
int test_mark_on_grid_with_ongoing_to_win();
int test_mark_on_grid_with_ongoing_to_draw();
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
        test_mark_on_grid_with_blank_to_ongoing() +
        test_mark_on_grid_with_ongoing_to_win() +
        test_mark_on_grid_with_ongoing_to_draw();
        // test_flush_grid() +
        // test_compare_grid() +
        // test_destroy_grid() +
        // test_grid_to_string() +
        // test_parse_string_to_grid();

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

// Test if the mark_on_grid() can mark a charachter and change state of the grid from blank to ongoing
int test_mark_on_grid_with_blank_to_ongoing() {
    // assume
    grid_struct input_grid = {
        malloc (GRID_SIZE*sizeof(char)),
        GRID_INFINITY,
        BLANK
    };
    strcpy(input_grid.contents, ".........");

    unsigned short int new_location = 0;
    game_character character = ZERO;

    grid_struct expected = {
        malloc (GRID_SIZE*sizeof(char)),
        0,
        ONGOING
    };
    strcpy(expected.contents, "0........");

    // act
    mark_on_grid(&input_grid, character, new_location);
    
    // assert
    bool test_passed = compare_grid(&input_grid, &expected);
    print_test_status(test_passed, "mark_on_grid() (BLANK -> ONGOING)");
    return test_passed;
}

// Test if the mark_on_grid() can mark a charachter and change state of the grid from ongoing to win
int test_mark_on_grid_with_ongoing_to_win() {
    // assume
    /**
     * . . .
     * X 0 X
     * 0 X 0
     */
    grid_struct input_grid = {
        malloc (GRID_SIZE*sizeof(char)),
        5,
        ONGOING
    };
    strcpy(input_grid.contents, "0X0X0X...");

    unsigned short int new_location = 6;
    game_character character = ZERO;

    /**
     * 0 . .
     * X 0 X
     * 0 X 0
     */
    grid_struct expected = {
        malloc (GRID_SIZE*sizeof(char)),
        6,
        GAME_WIN
    };
    strcpy(expected.contents, "0X0X0X0..");

    // act
    mark_on_grid(&input_grid, character, new_location);
    
    // assert
    bool test_passed = compare_grid(&input_grid, &expected);
    print_test_status(test_passed, "mark_on_grid() (ONGOING -> WIN)");
    return test_passed;
}

// Test if the mark_on_grid() can mark a charachter and change state of the grid from ongoing to win
int test_mark_on_grid_with_ongoing_to_draw() {
    // assume
    /**
     * X 0 .
     * 0 X X
     * 0 X 0
     */
    grid_struct input_grid = {
        malloc (GRID_SIZE*sizeof(char)),
        7,
        ONGOING
    };
    strcpy(input_grid.contents, "0X00XXX0.");

    unsigned short int new_location = 8;
    game_character character = CROSS;

    /**
     * X 0 X
     * 0 X X
     * 0 X 0
     */
    grid_struct expected = {
        malloc (GRID_SIZE*sizeof(char)),
        8,
        GAME_DRAW
    };
    strcpy(expected.contents, "0X00XXX0X");

    // act
    mark_on_grid(&input_grid, character, new_location);
    
    // assert
    bool test_passed = compare_grid(&input_grid, &expected);
    print_test_status(test_passed, "mark_on_grid() (ONGOING -> DRAW)");
    return test_passed;
}

// int test_flush_grid() {
//     // assume

//     // act

//     // assert
// }

// int test_compare_grid() {
//     // assume

//     // act

//     // assert
// }

// int test_destroy_grid() {
//     // assume

//     // act

//     // assert
// }

// int test_grid_to_string() {
//     // assume

//     // act

//     // assert
// }

// int test_parse_string_to_grid() {
//     // assume

//     // act

//     // assert
// }

