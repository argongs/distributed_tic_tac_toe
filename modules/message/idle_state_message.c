// Define the operations related to Idle state based messages : INVITE & ACCEPT

#include "idle_state_message.h"
#include "../grid/game_character.h"
#include "string.h"
#include "stdbool.h"

// Creates Idle State Message using the given values. This is meant to be used only by the functions of this file and no one else. Note that if the type of the 
static idle_state_message_struct create_idle_state_message (idle_state_message type, char* name, game_character character, void* data) {
    
    idle_state_message_struct idle_state_message = {
        INVITE,
        name,
        character,
        data
    };
    
    switch (type) {
        case INVITE: 
            break;

        case ACCEPT:
            idle_state_message_set_type(&idle_state_message, ACCEPT); 
            break;
        
        default:;
    }

    return idle_state_message;
}

// Creates INVITE Message using the given values.
idle_state_message_struct create_invite_message (char* name, game_character character, void* data) {
    return create_idle_state_message(INVITE, name, character, data);
}

// Creates ACCEPT Message using the given values.
idle_state_message_struct create_accept_message (char* name, game_character character, void* data) {
    return create_idle_state_message(ACCEPT, name, character, data);
}

// Creates Idle State Message by parsing the given message.
idle_state_message_struct parse_string_to_idle_state_message(char* message) {
    idle_state_message_struct idle_state_message;
    int no_of_variables_scanned = sscanf(message, "%c,%s,%c,%p", &idle_state_message.type, &idle_state_message.name, &idle_state_message.character, &idle_state_message.data);
    return idle_state_message;
}

// Converts Idle State Message to String. Remember to destroy the memory associated with the message post its usage.
char* idle_state_message_to_string (idle_state_message_struct message) {

    size_t idle_state_message_max_size = (IDLE_STATE_MESSAGE_MAX_LENGTH) * size_of(char);
    char* idle_state_message = malloc (idle_state_message_max_size);

    int bytes_read = snprintf(idle_state_message, idle_state_message_max_size, "%c,%s,%c,%p", message.type, message.name, message.character, message.data);

    return idle_state_message;
}

// Compares two Idle state messages. If both are same then it'll return 1 other wise 0.
int compare_idle_state_messages (idle_state_message_struct message1, idle_state_message_struct message2) {
    bool type_is_same = message1.type == message2.type;
    bool name_is_same = strcmp(message1.name, message2.name) == 0;
    bool character_is_same = message1.character == message2.character;
    bool data_is_same = message1.data == message2.data;

    return type_is_same & name_is_same & character_is_same & data_is_same;
}


// Getters
idle_state_message_get_type_enum idle_state_message_get_type(idle_state_message_struct message) {
    return message.type;
}


const char* idle_state_message_get_name(idle_state_message_struct message) {
    return message.name;
}

char idle_state_message_get_character(idle_state_message_struct message) {
    return message.character;
}

const void* idle_state_message_get_data(idle_state_message_struct message) {
    return message.data;
}

// Setters
static int idle_state_message_set_type(idle_state_message_struct* message, idle_state_message_type_enum type) {
    message->type = type;
    return 0;
} 


int idle_state_message_set_name(idle_state_message_struct* message, char* name) {
    message->name = name;
    return 0;
}

int idle_state_message_set_character(idle_state_message_struct* message, game_character character) {
    message->character = character;
    return 0;
}

int idle_state_message_set_data(idle_state_message_struct* message, void* data) {
    message->data = data;
    return 0;
}

