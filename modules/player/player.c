// Define the functions for handling player data structure

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "player.h"
#include "../message/idle_state_message/idle_state_message.h"
#include "../network/network.h"
#include "../grid/game_charachter.h"

// Create a new player using the name and character of preference
player_struct*  create_player(char* name, game_character charachter) {
    player_struct* player = malloc (sizeof(player_struct));

    if (player != NULL) {
        player->name = name;
        player->charachter = charachter;

        int socket_fd = create_udp_socket();
        int port = generate_random_port();
        player->ipv4_addr = LOCALHOST;
        player->port = port;
        player->socket_fd = socket_fd;

        while (perform_binding(socket_fd, LOCALHOST, source_port) != 0);
    }

    return player;
}

// Kill the player
void kill_player(player_struct* player) {
    free(player);
}

// Generate a random port number in between 1025 and 3025
static int generate_random_port () {
    return START_PORT + random() % MAX_NODE_COUNT;
}

// Broadcasts a player's presence into the network in expectation of an opponent who will ACCEPT the request for a game.
idle_state_message_struct* broadcast_player(player_struct* player) {

    // Source Data
    idle_state_message_struct invite_message_data = create_invite_message (
        get_player_name(player), 
        get_player_character(player), 
        NULL
    );
    char* invite_message = idle_state_message_to_string(invite_message_data);
    unsigned int message_length = strlen(invite_message);

    // Destination data
    int dest_port = node_data.base_port;
	int node_name = 0;
	struct sockaddr_in dest_socket_addr;
	char* dest_ipv4_addr = LOCALHOST;
    
    for (int destination_port = START_PORT; destination_port < source_port; destination_port++)
        // Send data to each node in the network in the node iteratively
		sendto (socket_fd, invite_message, message_length, 0, (struct sockaddr*) &dest_socket_addr, sizeof (dest_socket_addr));


}

// Observe the network and prepare a list of the opponents.
player_struct** look_for_opponents();

// Accept the request for a match.
int accept_an_opponent();

// Getters
char* get_player_name(player_struct player) {
    return player.name;
}

char* get_player_character(player_struct player) {
    return player.charachter
}