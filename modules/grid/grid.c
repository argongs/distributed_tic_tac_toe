// Define functions associated with the grid data structure
#include "grid.h"
#include "game_character.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

// Creates a new grid ready for usage. Returns a pointer to that grid for easier access to it.
grid_struct* create_grid() {
    grid_struct* grid = malloc (size_of(gid_struct));

    if (grid == NULL)
        return NULL;

    flush_grid(grid);
    return grid;
}

// Marks a charachter (CROSS or ZERO) on the grid. 
int mark_on_grid(grid_struct* grid, game_character character, location location) {
    
    if (location < GRID_INFINITY) {
        grid->contents[location] = character;
        update_grid_status(grid);
    }
    else
        return 1;

    return 0;
}

// Clean the grid by reversing it back to the blank state.
grid_struct* flush_grid(grid_struct* grid) {

    for (location i = 0; i < GRID_SIZE; i++)
        mark_on_grid(grid, EMPTY, i);

    set_grid_last_update_location(grid, GRID_INFINITY);
    set_grid_recent_status(grid, BLANK);

    return grid;
}

// Analyse the grid to understand its current status
static grid_struct* update_grid_status(grid_struct* grid) {
    
    unsigned short int temp = 0;

    // Horizontal Bottom
    bool horizontal_bottom_match = false;
    temp = grid->contents[HORIZONTAL_BOTTOM_MIN];
    for (location horizontal_bottom_index = HORIZONTAL_BOTTOM_MIN + 1; horizontal_bottom_index <= HORIZONTAL_BOTTOM_MAX; horizontal_bottom_index++) 
        horizontal_bottom_match = (temp == grid->contents[horizontal_bottom_index]);

    // Horizontal Middle
    bool horizontal_mid_match = false;
    temp = grid->contents[HORIZONTAL_MID_MIN];
    for (location horizontal_mid_index = HORIZONTAL_MID_MIN + 1; horizontal_mid_index <= HORIZONTAL_MID_MAX; horizontal_mid_index++) 
        horizontal_mid_match = (temp == grid->contents[horizontal_mid_index]);

    // Horizontal Top
    bool horizontal_top_match = false;
    temp = grid->contents[HORIZONTAL_TOP_MIN];
    for (location horizontal_top_index = HORIZONTAL_TOP_MIN + 1; horizontal_top_index <= HORIZONTAL_TOP_MAX; horizontal_top_index++) 
        horizontal_top_match = (temp == grid->contents[horizontal_top_index]);

    // Vertical Left
    bool vertical_left_match = false;
    temp = grid->contents[VERTICAL_LEFT_MIN];
    for (location vertical_left_index = VERTICAL_LEFT_MIN + 3; vertical_left_index <= VERTICAL_LEFT_MAX; vertical_left_index += 3) 
        vertical_left_match = (temp == grid->contents[vertical_left_index]);

    // Vertical Middle
    bool vertical_mid_match = false;
    temp = grid->contents[VERTICAL_MID_MIN];
    for (location vertical_mid_index = VERTICAL_MID_MIN + 3; vertical_mid_index <= VERTICAL_MID_MAX; vertical_mid_index += 3) 
        vertical_mid_match = (temp == grid->contents[vertical_mid_index]);

    // Vertical Right
    bool vertical_right_match = false;
    temp = grid->contents[VERTICAL_RIGHT_MIN];
    for (location vertical_right_index = VERTICAL_RIGHT_MIN + 3; vertical_right_index <= VERTICAL_RIGHT_MAX; vertical_right_index += 3) 
        vertical_right_match = (temp == grid->contents[vertical_right_index]);

    // Diagonal Right
    bool diagonal_right_match = false;
    temp = grid->contents[DIAGONAL_RIGHT_MIN];
    for (location diagonal_right_index = DIAGONAL_RIGHT_MIN + 4; diagonal_right_index <= DIAGONAL_RIGHT_MAX; diagonal_right_index += 4) 
        diagonal_right_match = (temp == grid->contents[diagonal_right_index]);

    // Diagonal Left
    bool diagonal_left_match = false;
    temp = grid->contents[DIAGONAL_LEFT_MIN];
    for (location diagonal_left_index = DIAGONAL_LEFT_MIN + 2; diagonal_left_index <= DIAGONAL_LEFT_MAX; diagonal_left_index += 2) 
        diagonal_left_match = (temp == grid->contents[diagonal_left_index]);

    bool it_is_a_win = (horizontal_bottom_match || horizontal_mid_match || horizontal_top_match) ||
        (vertical_left_match || vertical_mid_match || vertical_right_match) ||
        (diagonal_left_match || diagonal_right_match);

    if (it_is_a_win)
        set_grid_recent_status(grid, WIN);
    else
        if (entries_made < GRID_SIZE)
            set_grid_recent_status(grid, INCOMPLETE);
        else
            set_grid_recent_status(grid, DRAW);

    return grid;
}

// grid_status_enum last_move_outcome(grid_struct grid);

// Compares 2 grid and tells whether they are same. Returns 1 if both match otherwise return 0.
int compare_grid(grid_struct grid1, grid_struct grid2) {

    bool contents_match = strcmp(grid1.contents, grid2.contents) == 0;
    bool attributes_match = false;

    if (contents_match)
        attributes_match = get_grid_last_update_location(grid1) == get_grid_last_update_location(grid2) &&
                    get_no_of_entries_made_in_grid(grid1) == get_no_of_entries_made_in_grid(grid2) &&
                    get_grid_recent_status(grid1) == get_grid_recent_status(grid2)

    return contents_match && attributes_match;
}

// Translate the grid contents along with the last move location into a String
char* grid_to_string(grid_struct grid) {
    char* stringified_grid = malloc (sizeof(char) * (GRID_SIZE + 2));
    int bytes_read = sprintf(stringified_grid, "%s,%u", grid.contents, grid.last_location); 
    return stringified_grid;
}

// Parse a string into a grid 
grid_struct* parse_string_to_grid(char* grid_string) {
    grid_struct* grid = create_grid();
    if (grid == NULL)
        return NULL;

    char[GRID_SIZE] grid_contents;
    location last_move;
    
    sscanf(grid_string, "%9s,%u", grid_contents, &last_move);
    
    strcpy(grid_string);
    set_grid_last_update_location(grid, last_move);
    update_grid_status(grid);

    return grid;
}

// Getters
location get_grid_last_update_location (grid_struct grid) {
    return grid.last_location;
}

unsigned short int get_no_of_entries_made_in_grid (grid_struct grid) {
    
    unsigned short int empty_entries = 0;

    for (int i = 0; i < GRID_SIZE; i++)
        if (grid.contents[i] == EMPTY)
            empty_entries++ ;

    return GRID_SIZE - empty_entries;
}

grid_status_enum get_grid_recent_status (grid_struct grid) {
    return grid.recent_status;
}

// Setters
location set_grid_last_update_location (grid_struct* grid, location last_location) {
    grid->last_location = last_location;
    return last_location;
}

grid_status_enum set_grid_recent_status (grid_struct* grid, grid_status_enum recent_status) {
    grid->recent_status = recent_status;
    return recent_status;
}