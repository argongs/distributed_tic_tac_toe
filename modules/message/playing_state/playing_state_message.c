// Define the functions required to handle the Playing state data structure

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "modules/grid/game_character.h"
#include "modules/grid/grid.h"
#include "playing_state_message.h"

// Static functions

// Set type of the playing state message
static int playing_state_message_set_type(playing_state_message_struct* message, playing_state_message_type_enum type) {
    message->type = type;
    return 0;
}

// Create an instance of blank playing state message 
static playing_state_message_struct* create_blank_playing_state_message() {
    playing_state_message_struct* playing_state_message = (playing_state_message_struct*) malloc (sizeof(playing_state_message_struct));
    playing_state_message->grid = create_grid();
    playing_state_message->data = NULL;

    if (playing_state_message == NULL || grid == NULL)
        return NULL;

    return playing_state_message;
}

// Creates a playing state message instance
static playing_state_message_struct* create_playing_state_message (playing_state_message_type_enum type, grid_struct* grid, void* data) {
    
    playing_state_message_struct* playing_state_message = (playing_state_message_struct*) malloc (sizeof(playing_state_message_struct));
    
    playing_state_message_set_type(playing_state_message, GRID);
    playing_state_message_set_grid(playing_state_message, grid);
    playing_state_message_set_data(playing_state_message, data);
    
    switch (type) {
        case GRID:    
            break;
        
        case WIN:
            playing_state_message_set_type (playing_state_message, WIN);
            break;
        
        case DRAW:
            playing_state_message_set_type (playing_state_message, DRAW);
            break;
        
        default:;
    }

    return playing_state_message;
}

// Create a GRID message
playing_state_message_struct* create_grid_message (grid_struct* grid, void* data) {
    return create_playing_state_message (GRID, grid, data);
}

// Create a WIN message
playing_state_message_struct* create_win_message (grid_struct* grid, void* data) {
    return create_playing_state_message (WIN, grid, data);
}

// Create a DRAW message
playing_state_message_struct* create_draw_message (grid_struct* grid, void* data) {
    return create_playing_state_message (DRAW, grid, data);
}

// Parse/Deserialise a string message into a playing state message
playing_state_message_struct* parse_string_to_playing_state_message (char* message) {
    playing_state_message_struct* playing_state_message = create_blank_playing_state_message();
    
    if (playing_state_message == NULL)
        return NULL;
    
    int no_of_variables_scanned = sscanf(message, "%c,%[^,],%hd", (char*) &(playing_state_message->type), playing_state_message->grid->contents, (unsigned short int*) &(playing_state_message->grid->last_location));
    return playing_state_message;
}

// Destroy the memory associated with playing state message instance
void destroy_playing_state_message(playing_state_message_struct* message) {
    message->grid = NULL;
    free(message);
}

// Destroy the memory associated with playing state message instance as well as the grid associated with it
void destroy_playing_state_message_with_grid(playing_state_message_struct* message) {
    destroy_grid(message->grid);
    destroy_playing_state_message(message);
}


// Serialise/Stringify a playing state message instance
char* playing_state_message_to_string (playing_state_message_struct message) {
    size_t playing_state_message_max_size = (PLAYING_STATE_MESSAGE_MAX_LENGTH) * sizeof(char);
    char* playing_state_message = malloc (playing_state_message_max_size);

    int bytes_read = snprintf(playing_state_message, playing_state_message_max_size, "%c,%s,%d%*[^\n]", message.type, message.grid->contents, message.grid->last_location);

    return playing_state_message;
}

// Compare 2 playing state message instances
int compare_playing_state_message(playing_state_message_struct message1, playing_state_message_struct message2) {
    bool type_is_same = message1.type == message2.type;
    bool grid_is_same = compare_grid(message1.grid, message2.grid);
    bool data_is_same = message1.data == message2.data;

    return type_is_same & grid_is_same & data_is_same;
}

// Checks if a given message a playing state like message or not
bool is_it_playing_state_message (char* message) {
    switch (message[0]) {
        case GRID:;
        case WIN:;
        case DRAW:
            return true;
        default:
            return false;
    }
}

// Getters
playing_state_message_type_enum playing_state_message_get_type (playing_state_message_struct message) {
    return message.type;
}

grid_struct playing_state_message_get_grid (playing_state_message_struct message) {
    return *(message.grid);
}

void* playing_state_message_get_data (playing_state_message_struct message) {
    return message.data;
}

// Setters

int playing_state_message_set_grid(playing_state_message_struct* message, grid_struct* grid) {
    message->grid = grid;
    return 0;
}

int playing_state_message_set_data(playing_state_message_struct* message, void* data) {
    message->data = data;
    return 0;
}