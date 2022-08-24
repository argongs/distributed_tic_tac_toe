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
    printf ("\n");
    int temp = 0;
    for (int i = 0; i < GRID_ROWS; i++) {
        for (int j = 0; j < GRID_ROWS; j++) {
            printf ("%d\t", temp++);
        }
        printf("\n\n");
    }

    printf("\n");
}

// Accept the user's input
static void get_input_for_ongoing_game(player_struct player, grid_struct* grid) {
    printf ("Where do you wish to make the mark?\n");
    unsigned int no_of_entries = get_no_of_entries_made_in_grid(*grid);
    bool both_players_have_not_yet_made_first_move = no_of_entries < 2; 
    
    if(both_players_have_not_yet_made_first_move) {
        printf ("Mark can be made on one of the %d locations. The intended location should be empty. The location mapping of the grid is as follows:\n", GRID_SIZE);
        show_grid_indexing();
    }

    int last_location = GRID_INFINITY;

    while (true) {
        scanf("%d", &last_location);
        if (last_location < HORIZONTAL_TOP_MIN || last_location > HORIZONTAL_BOTTOM_MAX)
            printf ("Incorrect location. Please provide an input in between %d and %d.\n", HORIZONTAL_TOP_MIN, HORIZONTAL_BOTTOM_MAX);
        else
            break;
    }

    mark_on_grid(grid, player.character, last_location);
}

// Take input in the form of yes or no (y/n) 
static bool yes_or_no_input() {
    char input = ' ';
    scanf("%c", &input);
    return tolower(input) == YES ? true : false;
}

// Display the game grid
void show_grid(grid_struct grid) {
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
}

// Take the user's input for marking on the grid
grid_status_enum get_input_for_grid(player_struct player, grid_struct* grid) {

    switch (grid->recent_status) {
        case BLANK:;
        case ONGOING:
            get_input_for_ongoing_game(player, grid);
            return ONGOING;
        case GAME_WIN:
            printf ("Your opponent has won this round!\n");
            return GAME_WIN;
        case GAME_DRAW:
            printf ("It's a tie!\n");
            return GAME_DRAW;
        default: 
            return BLANK;
    }

}

// Take user's input to understand whether or not he/she is interested in a rematch
bool is_player_interested_in_a_rematch() {
    printf ("Do you wish to go for a rematch? (y/n)\t");
    return yes_or_no_input();
}

// Show the type of request recieved by the opponent (ACCEPT/INVITE)
void show_opponent_request(player_struct opponent) {
    
    switch (opponent.player_type) {
        case OPPONENT_WITH_PLAYER_INVITE:
            printf ("%s has accepted your request.\n", opponent.name);
            break;
        case OPPONENT_WITH_OWN_INVITE:
            printf ("%s has sent an invitation to you.\n", opponent.name);
            break;
        default:;
    }

}

// Accept the opponent for playing the game
bool accept_opponent_request(player_struct opponent) {
    printf ("Are you interested in playing against %s? (y/n)\t", opponent.name);
    return yes_or_no_input();
}