// Define the data structure associated with a player and provide a prototype of all the functions associated for its handling

typedef struct {
    char* name;
    game_character charachter;
    char* ipv4_addr;
    int port;
    int socket_fd;
} player_struct;

player_struct* create_player(char* name, game_character charachter);
void kill_player(player_struct* player);

// Broadcasts a player's presence into the network in expectation of an opponent who will ACCEPT the request for a game.
idle_state_message_struct* broadcast_player(player_struct* player);

// Observe the network and prepare a list of the opponents.
player_struct** look_for_opponents();

// Accept the request for a match.
int accept_an_opponent();

// Getters
char* get_player_name(player_struct player);
char* get_player_character(game_character charachter);