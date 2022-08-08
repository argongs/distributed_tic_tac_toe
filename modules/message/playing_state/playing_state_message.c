// Define the functions required to handle the Playing state data structure

#include "playing_state_message.h"
#include "../grid/grid.h"

playing_state_message_struct create_playing_state_message (playing_state_message_type type, grid_struct grid, void* data) {
    
    playing_state_message_struct playing_state_message = {
        GRID,
        grid,
        data
    }

    switch (type) {
        case GRID:    
            break;
        
        case WIN:
            playing_state_message_set_type (&playing_state_message, WIN);
            break;
        
        case DRAW:
            playing_state_message_set_type (&playing_state_message, DRAW);
            break;
        
        default:;
    }

    return playing_state_message;
}

playing_state_message_struct create_grid_message (grid_struct grid, void* data) {
    return create_playing_state_message (GRID, grid, data);
}

playing_state_message_struct create_win_message (grid_struct grid, void* data) {
    return create_playing_state_message (WIN, grid, data);
}

playing_state_message_struct create_draw_message (grid_struct grid, void* data) {
    return create_playing_state_message (DRAW, grid, data);
}

playing_state_message_struct parse_string_to_playing_state_message (char* message) {
    playing_state_message_struct playing_state_message;
    int no_of_variables_scanned = sscanf(message, "%c,%s,%d,%p", &playing_state_message.type, &playing_state_message.grid.contents, &playing_state_message.grid.last_location, &playing_state_message.data);
    return playing_state_message;
}

char* playing_state_message_to_string (playing_state_message_struct message) {
    size_t playing_state_message_max_size = (PLAYING_STATE_MESSAGE_MAX_LENGTH) * sizeof(char);
    char* playing_state_message = malloc (playing_state_message_max_size);

    int bytes_read = snprintf(playing_state_message, playing_state_message_max_size, "%c,%s,%d,%p", message.type, message.grid.contents, message.grid.last_location, message.data);

    return playing_state_message;
}

int compare_playing_state_message(playing_state_message_struct message1, playing_state_message_struct message2) {
    bool type_is_same = message1.type == message2.type;
    bool grid_is_same = compare_grid(message1.grid, message2.grid) == 0;
    bool data_is_same = message1.data == message2.data;

    return type_is_same & grid_is_same & data_is_same;
}

// Getters
playing_state_message_type_enum playing_state_message_get_type (playing_state_message_struct message) {
    return message.type;
}

grid_struct playing_state_message_get_grid (playing_state_message_struct message) {
    return message.grid;
}

void* playing_state_message_get_data (playing_state_message_struct message) {
    return message.data;
}

// Setters

static int playing_state_message_set_type(playing_state_message_struct* message, playing_state_message_type_enum type) {
    message->type = type;
    return 0;
}

int playing_state_message_set_grid(playing_state_message_struct* message, grid_struct grid) {
    message->grid = grid;
    return 0;
}

int playing_state_message_set_data(playing_state_message_struct* message, void* data) {
    message->data = data;
    return 0;
}