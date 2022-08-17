// Provide a prototype of all functions that will be used for user interaction

typedef enum {
    YES = 'y',
    NO = 'n'
}user_binary_response_enum;

void show_grid(grid_struct grid);
void get_input_for_grid(player_struct player, grid_struct* grid); // take input iff the grid is not in win status
void is_player_interested_in_a_rematch();

void show_opponent_request(player_struct* opponent);
bool accept_opponent_request(player_struct player, player_struct opponent);