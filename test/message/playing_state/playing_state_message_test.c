#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "modules/grid/game_character.h"
#include "modules/grid/grid.h"
#include "modules/message/playing_state/playing_state_message.h"
#include "modules/test/test.h"

bool test_create_grid_message();
bool test_create_win_message();
bool test_create_draw_message();
bool test_parse_string_to_playing_state_message();
bool test_playing_state_message_to_string();
bool test_compare_if_equal();
bool test_compare_if_unequal();

// TODO : Update the following tests
// bool test_playing_state_message_get_type();
// bool test_playing_state_message_get_grid();
// bool test_playing_state_message_get_data();
// bool test_playing_state_message_set_grid();
// bool test_playing_state_message_set_data();

int main()
{

    const int total_test_cases = 7;

    int test_cases_passed = test_create_grid_message() +
                            test_create_win_message() +
                            test_create_draw_message() +
                            test_parse_string_to_playing_state_message() +
                            test_playing_state_message_to_string() +
                            test_compare_if_equal() +
                            test_compare_if_unequal();

    return total_test_cases - test_cases_passed;
}

// Test playing_state_create_grid_message() to see if it can create GRID message from the given parameters
bool test_create_grid_message()
{
    // assume
    grid_struct grid = {
        "X0X0.....",
        1,
        ONGOING};
    void *data = NULL;

    playing_state_message_struct expected = {GRID, &grid, data};

    // act
    playing_state_message_struct* actual = create_grid_message(&grid, data);

    // assert
    bool test_passed = expected.type == actual->type &&
                       strcmp(expected.grid->contents, actual->grid->contents) == 0 &&
                       expected.grid->last_location == actual->grid->last_location &&
                       expected.data == actual->data;

    print_test_status(test_passed, "create_grid_message()");
    return test_passed;
}

// Test playing_state_create_win_message() to see if it can create WIN message from the given parameters
bool test_create_win_message()
{
    // assume
    grid_struct grid = {
        "X0X0X0X00",
        1,
        GAME_WIN};
    void *data = NULL;

    playing_state_message_struct expected = {WIN, &grid, data};

    // act
    playing_state_message_struct* actual = create_win_message(&grid, data);

    // assert
    bool test_passed = expected.type == actual->type &&
                       strcmp(expected.grid->contents, actual->grid->contents) == 0 &&
                       expected.grid->last_location == actual->grid->last_location &&
                       expected.data == actual->data;

    print_test_status(test_passed, "create_win_message()");
    return test_passed;
}

// Test playing_state_create_draw_message() to see if it can create DRAW message from the given parameters
bool test_create_draw_message()
{
    // assume
    grid_struct grid = {
        "X0X0X0X00",
        1,
        GAME_DRAW};
    void *data = NULL;

    playing_state_message_struct expected = {DRAW, &grid, data};

    // act
    playing_state_message_struct* actual = create_draw_message(&grid, data);

    // assert
    bool test_passed = expected.type == actual->type &&
                       strcmp(expected.grid->contents, actual->grid->contents) == 0 &&
                       expected.grid->last_location == actual->grid->last_location &&
                       expected.data == actual->data;

    print_test_status(test_passed, "create_draw_message()");
    return test_passed;
}

// Test parse_string_to_playing_state_message() to see if it can parse(de-serialize) given message into the playing state message data structure
bool test_parse_string_to_playing_state_message()
{
    // assume
    char *string_to_parse = "G,X0X0.....,1";

    grid_struct grid = {
        "X0X0.....",
        1,
        ONGOING};
    void *data = NULL;

    playing_state_message_struct expected = {GRID, &grid, data};

    // act
    playing_state_message_struct *actual = parse_string_to_playing_state_message(string_to_parse);

    // assert
    bool test_passed = expected.type == actual->type &&
                       strcmp(expected.grid->contents, actual->grid->contents) == 0 &&
                       expected.grid->last_location == actual->grid->last_location &&
                       expected.data == actual->data;

    print_test_status(test_passed, "parse_string_to_playing_state_message()");
    return test_passed;
}

// Test playing_state_message_to_string() to see if it can convert given playing state message data structure into a string that can be sent over the network (serialize)
bool test_playing_state_message_to_string()
{
    // assume
    grid_struct grid = {
        "X0X0.....",
        1,
        ONGOING};
    void *data = NULL;

    playing_state_message_struct grid_message = {GRID, &grid, data};

    char *expected = "G,X0X0.....,1";

    // act
    char *actual = playing_state_message_to_string(grid_message);

    // assert
    bool test_passed = strcmp(expected, actual) == 0;

    print_test_status(test_passed, "playing_state_message_to_string()");
    return test_passed;
}

// Test compare_playing_state_messages() to see if it can compare 2 same messages and say that both are same
bool test_compare_if_equal()
{
    // assume
    grid_struct grid = {
        "X0X0.....",
        1,
        ONGOING};
    void *data = NULL;

    playing_state_message_struct message1 = {GRID, &grid, data};
    playing_state_message_struct message2 = {GRID, &grid, data};

    bool expected = true;

    // act
    bool actual = compare_playing_state_message(message1, message2);

    // assert
    bool test_passed = actual == expected;

    print_test_status(test_passed, "compare_playing_state_message() (Equal Case)");
    return test_passed;
}

// Test compare_playing_state_messages() to see if it can compare 2 different messages and say that both are different
bool test_compare_if_unequal()
{
    // assume
    grid_struct grid1 = {
        "X0X0.....",
        1,
        ONGOING};
    grid_struct grid2 = {
        "X0X0X0X0X",
        9,
        GAME_WIN};
    void *data = NULL;

    playing_state_message_struct message1 = {GRID, &grid1, data};
    playing_state_message_struct message2 = {GRID, &grid2, data};

    bool expected = true;

    // act
    bool actual = compare_playing_state_message(message1, message2);

    // assert
    bool test_passed = actual != expected;

    print_test_status(test_passed, "compare_playing_state_message() (Unqual Case)");
    return test_passed;
}