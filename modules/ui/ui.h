// Provide a prototype of all functions that will be used for user interaction

void show_grid(grid_struct grid);
void get_input_for_grid(player_struct player, grid_struct* grid); // take input iff the grid is not in win status
void ask_for_rematch(player_struct player, player_struct opponent);

void show_opponent_request(player_struct* opponent);
bool accept_opponent_request(player_struct player, player_struct opponent);

bool validate_command_line_input(char* name, game_character character);
bool validate_grid_input(grid_struct grid);
