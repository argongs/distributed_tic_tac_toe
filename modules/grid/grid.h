// Define the data structure for a grid and provide prototypes for its associated functions

#define GRID_SIZE 9

typedef unsigned short int location;

typedef enum {
    BLANK,
    ONGOING,
    WIN,
    DRAW
} grid_status_enum;

typedef struct {
    char[GRID_SIZE] contents;
    location last_location;
    grid_status_enum recent_status; 
} grid_struct;

grid_struct create_grid();
int mark_on_grid(grid_struct* grid, game_character character, location location);
grid_struct* flush_grid(grid_struct* grid);
//grid_struct* update_grid_status(grid_struct* grid);  // make it static and call it from mark_on_grid()
grid_status_enum last_move_outcome(grid_struct grid);

char* grid_to_string(grid_struct grid);
grid_struct parse_string_to_grid(char* grid_string);