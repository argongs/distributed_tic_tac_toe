// Define data structure for Playing state based messages : GRID, WIN & DRAW and prototypes of the functions that can be used to handle them

#define PLAYING_STATE_MESSAGE_MAX_LENGTH 64

typedef enum {
    GRID = 'G',
    WIN = 'W',
    DRAW = 'D'
} playing_state_message_type_enum;

typedef struct {
    playing_state_message_type_enum type;
    grid_struct* grid;
    void* data;
} playing_state_message_struct;

playing_state_message_struct* create_grid_message (grid_struct* grid, void* data);
playing_state_message_struct* create_win_message (grid_struct* grid, void* data);
playing_state_message_struct* create_draw_message (grid_struct* grid, void* data);
playing_state_message_struct* parse_string_to_playing_state_message (char* message);
void destroy_playing_state_message(playing_state_message_struct* message);

char* playing_state_message_to_string (playing_state_message_struct message);
int compare_playing_state_message(playing_state_message_struct message1, playing_state_message_struct message2);

// Getters
playing_state_message_type_enum playing_state_message_get_type (playing_state_message_struct message);
grid_struct playing_state_message_get_grid (playing_state_message_struct message);
void* playing_state_message_get_data (playing_state_message_struct message);

// Setters
int playing_state_message_set_grid(playing_state_message_struct* message, grid_struct* grid);
int playing_state_message_set_data(playing_state_message_struct* message, void* data);