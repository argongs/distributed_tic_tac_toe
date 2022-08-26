// Define the functions for handling player data structure

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "modules/grid/game_character.h"
#include "modules/grid/grid.h"
#include "modules/message/idle_state/idle_state_message.h"
#include "modules/message/playing_state/playing_state_message.h"
#include "modules/network/network.h"
#include "player.h"


// Create an INVITE for a given player
static char* create_invite_message_for_player (player_struct player) {
    
    idle_state_message_struct* invite_message_data = create_invite_message (
        get_player_name(player), 
        get_player_character(player), 
        NULL
    );
    
    char* invite_message = idle_state_message_to_string(*invite_message_data);
    destroy_idle_state_message(invite_message_data);

    return invite_message;

}

// Create an ACCEPT message for a given player
static char* create_accept_message_for_player (player_struct player) {
    
    idle_state_message_struct* accept_message_data = create_accept_message (
        get_player_name(player), 
        get_player_character(player), 
        NULL
    );
    
    return idle_state_message_to_string(*accept_message_data);
}

// Generate a random port number in between 1025 and 3025
static int generate_random_port () {
    return START_PORT + random() % MAX_NODE_COUNT;
}

// Create a new player using the name and character of preference
player_struct* create_player(char* name, game_character character) {
    player_struct* player = malloc (sizeof(player_struct));

    if (player != NULL) {
        player->name = name;
        player->character = character;

        int socket_fd = create_udp_socket();
        int port = generate_random_port();
        player->ipv4_addr = LOCALHOST;
        player->port = port;
        player->socket_fd = socket_fd;
        set_player_type(player, SELF);

        while (perform_binding(socket_fd, LOCALHOST, port) != 0);
    }

    return player;
}

// Create a new opponent using the given details
player_struct* create_opponent(int socket_fd, struct sockaddr_in opponent_socket_address, char* request_message) {
    player_struct* opponent = malloc (sizeof(player_struct));

    if (opponent != NULL) {
        opponent->ipv4_addr = inet_ntoa(opponent_socket_address.sin_addr);
        opponent->port = ntohs(opponent_socket_address.sin_port);
        opponent->socket_fd = socket_fd;

        // inet_ntop(AF_INET, &(opponent_socket_address.sin_addr), opponent->ipv4_addr, INET_ADDRSTRLEN);

        idle_state_message_struct* idle_state_message = parse_string_to_idle_state_message(request_message);
        
        opponent->name = idle_state_message_get_name(*idle_state_message);
        opponent->character = idle_state_message_get_character(*idle_state_message);

        switch(idle_state_message_get_type(*idle_state_message)) {
            case INVITE:
                set_player_type(opponent, OPPONENT_WITH_OWN_INVITE);
                break;
            case ACCEPT:
                set_player_type(opponent, OPPONENT_WITH_PLAYER_INVITE);
                break;
            default:;
        }
    }

    return opponent;
}

// Kill the player
void kill_player(player_struct** player) {
    free(*player);
    *player = NULL;
}

// Broadcasts a player's presence into the network in expectation of an opponent who will ACCEPT the request for a game.
int broadcast_player(player_struct player) {
    // Message to send
    char* invite_message = create_invite_message_for_player(player);
    size_t message_length = strlen(invite_message);
    int socket_fd = get_player_socket_file_descriptor(player);

    // Destination data
    struct sockaddr_in dest_socket_addr;
	char* dest_ipv4_addr = LOCALHOST;
    unsigned short int max_port = START_PORT + MAX_NODE_COUNT;
    
    // Iteratively broadcast INVITE message to all the possible players
    for (int destination_port = START_PORT; destination_port < max_port; destination_port++) {
        if (destination_port != player.port) {
            parse_address (dest_ipv4_addr, destination_port, &dest_socket_addr);
            printf("Sending message : %s\n", invite_message);
            sendto (socket_fd, invite_message, message_length, 0, (struct sockaddr*) &dest_socket_addr, sizeof (dest_socket_addr));
        }
    }

    free(invite_message);

    return 0;
}

// Observe the network and prepare a list of the opponents.
player_struct* look_for_opponents(player_struct player) {

    // Wait for responses to arrive
    char opponent_request[IDLE_STATE_MESSAGE_MAX_LENGTH];
    size_t request_max_size = sizeof (char) * IDLE_STATE_MESSAGE_MAX_LENGTH;
    static struct sockaddr_in opponent_socket_addr;
	socklen_t opponent_sockaddr_len;
    unsigned short int socket_fd = get_player_socket_file_descriptor(player);

    int recieve_status = recvfrom (socket_fd, opponent_request, request_max_size, 0, (struct sockaddr*) &opponent_socket_addr, &opponent_sockaddr_len);

    if (recieve_status == -1)
        return NULL;

    player_struct* opponent = create_opponent (socket_fd, opponent_socket_addr, opponent_request);

    return opponent;
}

// Accept the request for a match.
int accept_an_opponent(player_struct player, player_struct opponent) {
    
    // Prepare the ACCEPT message
    char* accept_message = create_accept_message_for_player(player);
    int message_length = strlen(accept_message);
    int socket_fd = get_player_socket_file_descriptor(player);

    // Prepare the destination details
    struct sockaddr_in dest_socket_addr;
	char* dest_ipv4_addr = get_player_ipv4_addr(opponent);
    int dest_port = get_player_port(opponent);
    parse_address (dest_ipv4_addr, dest_port, &dest_socket_addr);

    // Send the ACCEPT message    
    sendto (socket_fd, accept_message, message_length, 0, (struct sockaddr*) &dest_socket_addr, sizeof (dest_socket_addr));

    free(accept_message);
}

// Send the grid to the opponent
int send_grid_to_opponent(grid_struct* grid, player_struct player, player_struct opponent) {

    // Prepare the GRID message
    playing_state_message_struct* grid_message = create_grid_message(grid, NULL);
    char* message = playing_state_message_to_string(*grid_message);
    int message_length = strlen(message);
    int socket_fd = get_player_socket_file_descriptor(player);
    
    // Prepare the destination details
    struct sockaddr_in dest_socket_addr;
	char* dest_ipv4_addr = get_player_ipv4_addr(opponent);
    int dest_port = get_player_port(opponent);
    parse_address (dest_ipv4_addr, dest_port, &dest_socket_addr);

    // Send the GRID message    
    sendto (socket_fd, message, message_length, 0, (struct sockaddr*) &dest_socket_addr, sizeof (dest_socket_addr));

    //free(message);
    destroy_playing_state_message_with_grid(grid_message);
}

// Recieve the grid from the intended opponent
int recieve_grid_from_opponent(grid_struct* current_grid, player_struct player, player_struct opponent) {
    
    // Wait for responses to arrive
    char opponent_response[PLAYING_STATE_MESSAGE_MAX_LENGTH];
    size_t data_recvd = 0;
	size_t request_max_size = sizeof (char) * PLAYING_STATE_MESSAGE_MAX_LENGTH;
    static struct sockaddr_in opponent_socket_addr;
	
    socklen_t opponent_sockaddr_len;
    unsigned short int socket_fd = get_player_socket_file_descriptor(player);

    int recieve_status = 0;
    
    do {
        recieve_status = recvfrom (socket_fd, opponent_response, request_max_size, 0, (struct sockaddr*) &opponent_socket_addr, &opponent_sockaddr_len);

        if (recieve_status == -1)
            return -1;

    } while (!is_it_playing_state_message(opponent_response));
    
    playing_state_message_struct* message = parse_string_to_playing_state_message (opponent_response);
    
    
    copy_grid(*(message->grid), current_grid);
    destroy_playing_state_message_with_grid(message);
    
    return 0;
}


// Getters
char* get_player_name(player_struct player) {
    return player.name;
}

game_character get_player_character(player_struct player) {
    return player.character;
}

char* get_player_ipv4_addr(player_struct player) {
    return player.ipv4_addr;
}

int get_player_port(player_struct player) {
    return player.port;
}

int get_player_socket_file_descriptor(player_struct player) {
    return player.socket_fd;
}

// Setters
void set_player_type(player_struct* player, player_type_enum player_type) {
    player->player_type = player_type;
}