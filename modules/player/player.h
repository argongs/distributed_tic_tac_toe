// Define the data structure associated with a player and provide a prototype of all the functions associated for its handling

typedef enum {
    SELF,
    OPPONENT_WITH_PLAYER_INVITE,// Opponent wants to ACCEPT the INVITE request of the player
    OPPONENT_WITH_OWN_INVITE // Opponent whose has sent its own INVITE request to the player
} player_type_enum;

typedef struct {
    char* name;
    game_character charachter;
    char* ipv4_addr;
    int port;
    int socket_fd;
    player_type_enum player_type;
} player_struct;

player_struct* create_player(char* name, game_character charachter);
player_struct* create_opponent(int socket_fd, struct sockaddr_in opponent_socket_address, char* request_message);
void kill_player(player_struct* player);

// Broadcasts a player's presence into the network in expectation of an opponent who will ACCEPT the request for a game.
int broadcast_player(player_struct player);

// Observe the network and prepare a list of the opponents.
player_struct* look_for_opponents(player_struct player);

// Accept the request for a match.
int accept_an_opponent(player_struct player, player_struct opponent);

// Getters
char* get_player_name(player_struct player);
game_character get_player_character(player_struct player);
char* get_player_ipv4_addr(player_struct player);
int get_player_port(player_struct player);
int get_player_socket_file_descriptor(player_struct player);

// Setters
void set_player_type(player_struct* player, player_type_enum player_type);