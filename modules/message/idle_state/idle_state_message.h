// Define data structure for Idle state based messages : INVITE & ACCEPT

#define IDLE_STATE_MESSAGE_MAX_LENGTH 64
#define NAME_FIELD_MAX_LENGTH 10

typedef enum {
    INVITE = 'I',
    ACCEPT = 'A'
} idle_state_message_type_enum;

typedef struct {
    idle_state_message_type_enum type;
    char* name;
    game_character character;
    void* data;
} idle_state_message_struct;

idle_state_message_struct* create_invite_message (char* name, game_character character, void* data);
idle_state_message_struct* create_accept_message (char* name, game_character character, void* data);
void destroy_idle_state_message(idle_state_message_struct* message);
idle_state_message_struct* parse_string_to_idle_state_message(char* message);

char* idle_state_message_to_string (idle_state_message_struct message);
int compare_idle_state_messages (idle_state_message_struct message1, idle_state_message_struct message2);

// Getters
idle_state_message_type_enum idle_state_message_get_type(idle_state_message_struct message);
const char* idle_state_message_get_name(idle_state_message_struct message);
char idle_state_message_get_character(idle_state_message_struct message);
const void* idle_state_message_get_data(idle_state_message_struct message);

// Setters
int idle_state_message_set_name(idle_state_message_struct* message, char* name);
int idle_state_message_set_character(idle_state_message_struct* message, game_character character);
int idle_state_message_set_data(idle_state_message_struct* message, void* data);