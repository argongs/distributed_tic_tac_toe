// Define all the functions needed to represent the UI for the end user

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "modules/grid/game_character.h"
#include "modules/grid/grid.h"
#include "modules/player/player.h"
#include "ui.h"

// Static functions

// Display the grid locations
static void show_grid_indexing() {
    fprintf(stderr, "show_grid_indexing() start\n");
    
    printf ("\n");
    int temp = 0;
    for (int i = 0; i < GRID_ROWS; i++) {
        for (int j = 0; j < GRID_ROWS; j++) {
            printf ("%d\t", temp++);
        }
        printf("\n\n");
    }

    printf("\n");
    fprintf(stderr, "show_grid_indexing() end\n");
}

// Accept the user's input
static void get_input_for_ongoing_game(player_struct player, grid_struct* grid) {
    fprintf(stderr, "get_input_for_ongoing_game() start\n");
    
    printf ("Where do you wish to make the mark?\n");
    unsigned int no_of_entries = get_no_of_entries_made_in_grid(*grid);
    bool both_players_have_not_yet_made_first_move = no_of_entries < 2; 
    
    if(both_players_have_not_yet_made_first_move) {
        printf ("Mark can be made on one of the %d locations. The intended location should be empty. The location mapping of the grid is as follows:\n", GRID_SIZE);
        show_grid_indexing();
    }

    unsigned short int last_location = GRID_INFINITY;
    unsigned short int is_input_location_occupied = 1;

    while (true) {
        scanf("%hd", &last_location);
        if (last_location < HORIZONTAL_TOP_MIN || last_location > HORIZONTAL_BOTTOM_MAX)
            printf ("Incorrect location. Please provide an input in between %d and %d.\n", HORIZONTAL_TOP_MIN, HORIZONTAL_BOTTOM_MAX);
        else {
            is_input_location_occupied = mark_on_grid(grid, player.character, last_location);
            if (is_input_location_occupied)
                printf ("Given location is already occupied\n");
            else
                break;
        }
    }
    
    fprintf(stderr, "get_input_for_ongoing_game() end\n");
}

// Take input in the form of yes or no (y/n) 
static bool yes_or_no_input() {
    fprintf(stderr, "yes_or_no_input() start\n");
    
    char input;
    scanf(" %c", &input);
    
    fprintf(stderr, "yes_or_no_input() end\n");

    return tolower(input) == YES ? true : false;
}

// Display the game grid
void show_grid(grid_struct grid) {
    fprintf(stderr, "show_grid() start\n");

    printf ("Grid\n");
    fflush(stdout);
    int temp = 0;
    for (int i = 0; i < GRID_ROWS; i++) {
        for (int j = 0; j < GRID_ROWS; j++) {
            printf ("%c\t", grid.contents[temp++]);
        }
        printf("\n\n");
    }

    printf("\n");

    fprintf(stderr, "show_grid() end\n");
}

// Take the user's input for marking on the grid
grid_status_enum get_input_for_grid(player_struct player, grid_struct* grid) {
    fprintf(stderr, "get_input_for_grid() start\n");

    grid_status_enum recent_grid_status = get_grid_recent_status(*grid);
    grid_status_enum updated_grid_status = BLANK;
    
    switch (recent_grid_status) {
        case BLANK: fprintf(stderr, "Grid is currently blank\n");
        case ONGOING:
            fprintf(stderr, "Grid has a game ongoing on it\n");
            get_input_for_ongoing_game(player, grid);
            updated_grid_status = get_grid_recent_status(*grid);
            break;
        case GAME_WIN:
            fprintf(stderr, "Game completed, opponent won\n");
            printf ("Your opponent has won this round!\n");
            updated_grid_status = recent_grid_status;
            break;
        case GAME_DRAW:
            fprintf(stderr, "Game completed, it's a draw\n");
            printf ("It's a tie!\n");
            updated_grid_status = recent_grid_status;
            break;
        default: fprintf(stderr, "Grid is in unknown status\n");;
    }

    fprintf(stderr, "get_input_for_grid() end\n");

    return updated_grid_status;
}

// Take user's input to understand whether or not he/she is interested in a rematch
bool is_player_interested_in_a_rematch() {
    fprintf(stderr, "is_player_interested_in_a_rematch() start\n");
    
    printf ("Do you wish to go for a rematch? (y/n)\t");

    fprintf(stderr, "is_player_interested_in_a_rematch() end\n");

    return yes_or_no_input();
}

// Show the type of request recieved by the opponent (ACCEPT/INVITE)
void show_opponent_request(player_struct opponent) {
    fprintf(stderr, "show_opponent_request() start\n");
    
    switch (opponent.player_type) {
        case OPPONENT_WITH_PLAYER_INVITE:
            printf ("%s has accepted your request.\n", opponent.name);
            break;
        case OPPONENT_WITH_OWN_INVITE:
            printf ("%s has sent an invitation to you.\n", opponent.name);
            break;
        default:;
    }

    fprintf(stderr, "show_opponent_request() end\n");
}

// Accept the opponent for playing the game
bool accept_opponent_request(player_struct opponent) {
    fprintf(stderr, "accept_opponent_request() start\n");

    printf ("Are you interested in playing against %s? (y/n)\t", opponent.name);
    
    fprintf(stderr, "accept_opponent_request() end\n");

    return yes_or_no_input();
}