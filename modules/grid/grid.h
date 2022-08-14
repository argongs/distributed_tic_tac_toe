// Define the data structure for a grid and provide prototypes for its associated functions

/**
    Indexing of the Grid:

      6 | 7 | 8
    ----+---+----
      3 | 4 | 5
    ----+---+----
      0 | 1 | 2
**/


#define GRID_SIZE 9
#define GRID_INFINITY 9

typedef unsigned short int location;

typedef enum {
    HORIZONTAL_BOTTOM_MAX = 2,
    HORIZONTAL_MID_MAX = 5,
    HORIZONTAL_TOP_MAX = 8,

    VERTICAL_LEFT_MAX = 6,
    VERTICAL_MID_MAX = 7,
    VERTICAL_RIGHT_MAX = 8,
    
    DIAGONAL_LEFT_MAX = 6,
    DIAGONAL_RIGHT_MAX = 8
} grid_maxima_enum;

typedef enum {
    HORIZONTAL_BOTTOM_MIN = 0,
    HORIZONTAL_MID_MIN = 3,
    HORIZONTAL_TOP_MIN = 6,

    VERTICAL_LEFT_MIN = 0,
    VERTICAL_MID_MIN = 1,
    VERTICAL_RIGHT_MIN = 2,
    
    DIAGONAL_LEFT_MIN = 2,
    DIAGONAL_RIGHT_MIN = 0
} grid_minima_enum;

typedef enum {
    BLANK,
    ONGOING,
    GAME_WIN,
    GAME_DRAW
} grid_status_enum;

typedef struct {
    char* contents;
    location last_location;
    grid_status_enum recent_status; 
} grid_struct;

grid_struct* create_grid();
int mark_on_grid(grid_struct* grid, game_character character, location location);
grid_struct* flush_grid(grid_struct* grid);
//grid_struct* update_grid_status(grid_struct* grid);  // make it static and call it from mark_on_grid()
//grid_status_enum last_move_outcome(grid_struct grid);
int compare_grid(grid_struct* grid1, grid_struct* grid2);
void destroy_grid(grid_struct* grid);

char* grid_to_string(grid_struct grid);
grid_struct* parse_string_to_grid(char* grid_string);


// Getters
location get_grid_last_update_location (grid_struct grid);
unsigned short int get_no_of_entries_made_in_grid (grid_struct grid);
grid_status_enum get_grid_recent_status (grid_struct grid);

// Setters
location set_grid_last_update_location (grid_struct* grid, location new_location);
grid_status_enum set_grid_recent_status (grid_struct* grid, grid_status_enum new_status);
