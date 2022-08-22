// Define functions associated with the grid data structure

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "game_character.h"
#include "grid.h"

// Analyse the grid to understand its current status
static grid_struct* update_grid_status(grid_struct* grid) {
    
    unsigned short int temp = 0;

    // Horizontal Bottom
    bool horizontal_bottom_match = true;
    temp = grid->contents[HORIZONTAL_BOTTOM_MIN];
    for (location horizontal_bottom_index = HORIZONTAL_BOTTOM_MIN + 1; horizontal_bottom_index <= HORIZONTAL_BOTTOM_MAX; horizontal_bottom_index++) 
        horizontal_bottom_match = horizontal_bottom_match && (temp != EMPTY) && (temp == grid->contents[horizontal_bottom_index]);

    // Horizontal Middle
    bool horizontal_mid_match = true;
    temp = grid->contents[HORIZONTAL_MID_MIN];
    for (location horizontal_mid_index = HORIZONTAL_MID_MIN + 1; horizontal_mid_index <= HORIZONTAL_MID_MAX; horizontal_mid_index++) 
        horizontal_mid_match = horizontal_mid_match && (temp != EMPTY) && (temp == grid->contents[horizontal_mid_index]);

    // Horizontal Top
    bool horizontal_top_match = true;
    temp = grid->contents[HORIZONTAL_TOP_MIN];
    for (location horizontal_top_index = HORIZONTAL_TOP_MIN + 1; horizontal_top_index <= HORIZONTAL_TOP_MAX; horizontal_top_index++) 
        horizontal_top_match = horizontal_top_match && (temp != EMPTY) && (temp == grid->contents[horizontal_top_index]);

    // Vertical Left
    bool vertical_left_match = true;
    temp = grid->contents[VERTICAL_LEFT_MIN];
    for (location vertical_left_index = VERTICAL_LEFT_MIN + 3; vertical_left_index <= VERTICAL_LEFT_MAX; vertical_left_index += 3) 
        vertical_left_match = vertical_left_match && (temp != EMPTY) && (temp == grid->contents[vertical_left_index]);

    // Vertical Middle
    bool vertical_mid_match = true;
    temp = grid->contents[VERTICAL_MID_MIN];
    for (location vertical_mid_index = VERTICAL_MID_MIN + 3; vertical_mid_index <= VERTICAL_MID_MAX; vertical_mid_index += 3) 
        vertical_mid_match = vertical_mid_match && (temp != EMPTY) && (temp == grid->contents[vertical_mid_index]);

    // Vertical Right
    bool vertical_right_match = true;
    temp = grid->contents[VERTICAL_RIGHT_MIN];
    for (location vertical_right_index = VERTICAL_RIGHT_MIN + 3; vertical_right_index <= VERTICAL_RIGHT_MAX; vertical_right_index += 3) 
        vertical_right_match = vertical_right_match && (temp != EMPTY) && (temp == grid->contents[vertical_right_index]);

    // Diagonal Right
    bool diagonal_right_match = true;
    temp = grid->contents[DIAGONAL_RIGHT_MIN];
    for (location diagonal_right_index = DIAGONAL_RIGHT_MIN + 4; diagonal_right_index <= DIAGONAL_RIGHT_MAX; diagonal_right_index += 4) 
        diagonal_right_match = diagonal_right_match && (temp != EMPTY) && (temp == grid->contents[diagonal_right_index]);

    // Diagonal Left
    bool diagonal_left_match = true;
    temp = grid->contents[DIAGONAL_LEFT_MIN];
    for (location diagonal_left_index = DIAGONAL_LEFT_MIN + 2; diagonal_left_index <= DIAGONAL_LEFT_MAX; diagonal_left_index += 2) 
        diagonal_left_match = diagonal_left_match && (temp != EMPTY) && (temp == grid->contents[diagonal_left_index]);

    bool it_is_a_win = (horizontal_bottom_match || horizontal_mid_match || horizontal_top_match) ||
        (vertical_left_match || vertical_mid_match || vertical_right_match) ||
        (diagonal_left_match || diagonal_right_match);

    unsigned short int entries_made = get_no_of_entries_made_in_grid(*grid);
    
    if (it_is_a_win)
        set_grid_recent_status(grid, GAME_WIN);
    else
        if (entries_made < GRID_SIZE)
            set_grid_recent_status(grid, ONGOING);
        else
            set_grid_recent_status(grid, GAME_DRAW);

    return grid;
}

// Creates a new grid ready for usage. Returns a pointer to that grid for easier access to it.
grid_struct* create_grid() {
    grid_struct* grid = malloc (sizeof(grid_struct));
    grid->contents = malloc (GRID_SIZE * sizeof(char));

    if (grid == NULL)
        return NULL;

    flush_grid(grid);
    return grid;
}

// Marks a charachter (CROSS or ZERO) on the grid. Returns 1 if the location is invalid.
int mark_on_grid(grid_struct* grid, game_character character, location location) {
    
    if (location < GRID_INFINITY && grid->contents[location] == EMPTY) {
        grid->contents[location] = character;
        set_grid_last_update_location (grid, location);
        update_grid_status(grid);
    }
    else
        return 1;

    return 0;
}

// Clean the grid by reversing it back to the blank state.
grid_struct* flush_grid(grid_struct* grid) {

    for (location i = 0; i < GRID_SIZE; i++)
        grid->contents[i] = EMPTY;

    set_grid_last_update_location(grid, GRID_INFINITY);
    set_grid_recent_status(grid, BLANK);

    return grid;
}

// grid_status_enum last_move_outcome(grid_struct grid);

// Compares 2 grid and tells whether they are same. Returns 1 if both match otherwise return 0.
int compare_grid(grid_struct* grid1, grid_struct* grid2) {

    bool same_memory_location = grid1 == grid2;

    if (same_memory_location)
        return 1;

    bool contents_match = strcmp(grid1->contents, grid2->contents) == 0;
    bool attributes_match = false;

    if (contents_match)
        attributes_match = get_grid_last_update_location(*grid1) == get_grid_last_update_location(*grid2) &&
                    get_no_of_entries_made_in_grid(*grid1) == get_no_of_entries_made_in_grid(*grid2) &&
                    get_grid_recent_status(*grid1) == get_grid_recent_status(*grid2);

    return contents_match && attributes_match;
}

// Send the grid to oblivion
void destroy_grid(grid_struct* grid) {
    free(grid);
}

// Translate the grid contents along with the last move location into a String
char* grid_to_string(grid_struct grid) {
    char* stringified_grid = malloc (sizeof(char) * (GRID_SIZE + 2));
    int bytes_read = sprintf(stringified_grid, "%s,%u", grid.contents, grid.last_location); 
    return stringified_grid;
}

// Parse a string into a grid 
grid_struct* parse_string_to_grid(char* grid_string) {
    grid_struct* grid = malloc (sizeof(grid_struct));

    if (grid == NULL)
        return NULL;

    sscanf(grid_string, "%m[^,],%hu", &(grid->contents), &(grid->last_location));
    
    if (grid->last_location == GRID_INFINITY)
        grid->recent_status = BLANK;
    else
        update_grid_status(grid);

    return grid;
}

void copy_grid(grid_struct source, grid_struct* destination) {
    strncpy(destination->contents, source.contents, GRID_SIZE * sizeof(char));
    destination->last_location = source.last_location;
    destination->recent_status = source.recent_status;
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