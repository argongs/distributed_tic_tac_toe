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
int test_compare_grid_if_equal();
int test_compare_grid_if_unequal();
int test_destroy_grid();
int test_grid_to_string();
int test_parse_string_to_grid_with_blank_status();
int test_parse_string_to_grid_with_ongoing_status();
int test_parse_string_to_grid_with_win_status();
int test_parse_string_to_grid_with_draw_status();
int test_copy_grid();

// TODO : Update the following tests later on
// int test_get_grid_last_update_location();
// int test_get_no_of_entries_made_in_grid();
// int test_get_grid_recent_status();
// int test_set_grid_last_update_location();
// int test_set_grid_recent_status();

int main()
{
    const int total_test_cases = 12;

    int test_cases_passed = test_create_grid() +
        test_mark_on_grid_with_blank_to_ongoing() +
        test_mark_on_grid_with_ongoing_to_win() +
        test_mark_on_grid_with_ongoing_to_draw() +
        test_flush_grid() +
        test_compare_grid_if_equal() +
        test_compare_grid_if_unequal() +
        test_parse_string_to_grid_with_blank_status() +
        test_parse_string_to_grid_with_ongoing_status() +
        test_parse_string_to_grid_with_win_status() +
        test_parse_string_to_grid_with_draw_status() +
        test_copy_grid();

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

// Test flush_grid() to see if it can reverse a grid back to its blank state
int test_flush_grid() {
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

    grid_struct expected = {
        ".........",
        GRID_INFINITY,
        BLANK
    };

    // act
    grid_struct* actual = flush_grid(&input_grid);

    // assert
    bool test_passed = compare_grid(actual, &expected);
    print_test_status(test_passed, "flush_grid()");
    return test_passed;
}

// Test compare_grid() to see if it can identify 2 same grids
int test_compare_grid_if_equal() {
    // assume
    grid_struct grid1 = {
        "0X0X0X...",
        5,
        ONGOING
    };
    
    grid_struct grid2 = {
        "0X0X0X...",
        5,
        ONGOING
    };
    
    bool expected = true;

    // act
    bool actual = compare_grid(&grid1, &grid2);
    
    // assert
    bool test_passed = expected == actual;
    print_test_status(test_passed, "compare_grid() (Equal Case)");
    return test_passed;
}

// Test compare_grid() to see if it can identify 2 different grids
int test_compare_grid_if_unequal() {
    // assume
    grid_struct grid1 = {
        "0X0X0X...",
        5,
        ONGOING
    };
    
    grid_struct grid2 = {
        "0X0X0X...",
        4,
        ONGOING
    };
    
    bool expected = false;

    // act
    bool actual = compare_grid(&grid1, &grid2);
    
    // assert
    bool test_passed = expected == actual;
    print_test_status(test_passed, "compare_grid() (Unequal case)");
    return test_passed;
}

// Test grid_to_string() to see if it can serialise/stringify a given grid
int test_grid_to_string() {
    // assume
    grid_struct input_grid = {
        "0X0X0X...",
        5,
        ONGOING
    };
    
    char* expected = "0X0X0X...,5";

    // act
    char* actual = grid_to_string(input_grid);
    
    // assert
    bool test_passed = strcmp(expected, actual) == 0;
    print_test_status(test_passed, "grid_to_string()");
    return test_passed;
}

// Test parse_string_to_grid() function to see if it can convert a stringified grid
// representing an blank grid into an instance of grid structure and mark its status as blank
int test_parse_string_to_grid_with_blank_status() {
    // assume
    char* input = ".........,9";

    grid_struct expected = {
        ".........",
        GRID_INFINITY,
        BLANK
    };

    // act
    grid_struct* actual = parse_string_to_grid(input);

    // assert
    bool test_passed = compare_grid(actual, &expected);
    print_test_status(test_passed, "parse_string_to_grid() (Blank Status)");
    return test_passed;
}

// Test parse_string_to_grid() function to see if it can convert a stringified grid
// representing an ongoing game into an instance of grid structure and mark its status as ongoing
int test_parse_string_to_grid_with_ongoing_status() {
    // assume
    char* input = "0X0X0X...,5";

    grid_struct expected = {
        "0X0X0X...",
        5,
        ONGOING
    };

    // act
    grid_struct* actual = parse_string_to_grid(input);

    // assert
    bool test_passed = compare_grid(actual, &expected);
    print_test_status(test_passed, "parse_string_to_grid() (Ongoing Status)");
    return test_passed;
}

// Test parse_string_to_grid() function to see if it can convert a stringified grid
// representing an ongoing game into an instance of grid structure and mark its status as ongoing
int test_parse_string_to_grid_with_win_status() {
    // assume
    char* input = "0X0X0X0..,6";

    grid_struct expected = {
        "0X0X0X0..",
        6,
        GAME_WIN
    };

    // act
    grid_struct* actual = parse_string_to_grid(input);

    // assert
    bool test_passed = compare_grid(actual, &expected);
    print_test_status(test_passed, "parse_string_to_grid() (Win Status)");
    return test_passed;
}

// Test parse_string_to_grid() function to see if it can convert a stringified grid
// representing an ongoing game into an instance of grid structure and mark its status as ongoing
int test_parse_string_to_grid_with_draw_status() {
    // assume
    char* input = "0X0X0XX0X,8";

    grid_struct expected = {
        "0X0X0XX0X",
        8,
        GAME_DRAW
    };

    // act
    grid_struct* actual = parse_string_to_grid(input);

    // assert
    bool test_passed = compare_grid(actual, &expected);
    print_test_status(test_passed, "parse_string_to_grid() (Draw Status)");
    return test_passed;
}

// Test copy_grid() to see if it can copy the source grid contents into the destination grid
int test_copy_grid() {
    // assume
    grid_struct source = {
        "0X0X0X...",
        5,
        ONGOING
    };
    
    grid_struct destination = {
        "0X0X0X...",
        4,
        ONGOING
    };
    
    bool expected = true;

    // act
    copy_grid(source, &destination);

    // assert
    bool actual = compare_grid(&source, &destination);
    bool test_passed = expected == actual;
    print_test_status(test_passed, "copy_grid()");
    return test_passed;
}