#include <stdio.h>
#include "../idle_state_message.h"
#include "../../grid/game_character.h"
#include <stdbool.h>
#include <string.h>

bool test_create_invite_message ();
bool test_create_accept_message ();
bool test_parse_string_to_idle_state_message();

bool test_idle_state_message_to_string ();
bool test_compare_if_equal();
bool test_compare_if_unequal();


// TODO : Update the following tests
// bool test_idle_state_message_get_type();
// bool test_idle_state_message_get_name();
// bool test_idle_state_message_get_character();
// bool test_idle_state_message_get_data();

// bool test_idle_state_message_set_name();
// bool test_idle_state_message_set_character();
// bool test_idle_state_message_set_data();

int main () {

    const int total_test_cases = 6;
    
    int test_cases_passed = 
        test_create_invite_message() + 
        test_create_accept_message() + 
        test_parse_string_to_idle_state_message() + 
        test_idle_state_message_to_string() + 
        test_compare_if_equal() +
        test_compare_if_unequal();

    return total_test_cases - test_cases_passed;
}

// Test idle_state_create_invite_message() to see if it can create INVITE message from the given parameters
bool test_create_invite_message () {
    // assume
    char* name = "New";
    game_character character = CROSS;
    void* data = NULL;

    idle_state_message_struct expected = {INVITE, name, character, data};

    // act
    idle_state_message_struct actual = idle_state_create_invite_message(name, character, data);

    // assert
    bool test_passed = expected.type == actual.type && 
        expected.name == actual.name && 
        expected.character == actual.character && 
        expected.data == actual.data; 

    if (test_passed) 
        printf ("test_create_invite_message() passed\n");
    else
        printf ("test_create_invite_message() failed\n");

    return test_passed;
}

// Test idle_state_create_accept_message() to see if it can create ACCEPT message from the given parameters
bool test_create_accept_message () {
    // assume
    char* name = "New";
    game_character character = CROSS;
    void* data = NULL;

    idle_state_message_struct expected = {ACCEPT, name, character, data};

    // act
    idle_state_message_struct actual = idle_state_create_accept_message(name, character, data);

    // assert
    bool test_passed = expected.type == actual.type && expected.name == actual.name && expected.character == actual.character && expected.data == actual.data; 

    if (test_passed) 
        printf ("test_create_accept_message() passed\n");
    else
        printf ("test_create_accept_message() failed\n");

    return test_passed;
}

// Test parse_string_to_idle_state_message() to see if it can parse(de-serialize) given message into the Idle state message data structure 
bool test_parse_string_to_idle_state_message() {
    // assume
    char* string_to_parse = "INVITE,New,X,";

    char* name = "New";
    game_character character = CROSS;
    void* data = NULL;

    idle_state_message_struct expected = {INVITE, name, character, data};

    // act
    idle_state_message_struct actual = parse_string_to_idle_state_message(string_to_parse);

    // assert
    bool test_passed = expected.type == actual.type && expected.name == actual.name && expected.character == actual.character && expected.data == actual.data; 

    if (test_passed) 
        printf ("test_parse_string_to_idle_state_message() passed\n");
    else
        printf ("test_parse_string_to_idle_state_message() failed\n");

    return test_passed;
}

// Test idle_state_message_to_string() to see if it can convert given Idle state message data structure into a string that can be sent over the network (serialize) 
bool test_idle_state_message_to_string () {
    // assume
    char* name = "New";
    game_character character = CROSS;
    void* data = NULL;
    idle_state_message_struct invite_message = {INVITE, name, character, data};

    char* expected = "INVITE,New,X,";

    // act
    char* actual = idle_state_message_to_string (invite_message);

    // assert
    bool test_passed = strcmp(expected, actual) == 0;

    if (test_passed) 
        printf ("test_idle_state_message_to_string() passed\n");
    else
        printf ("test_idle_state_message_to_string() failed\n");

    return test_passed;
}

// Test compare_idle_state_messages() to see if it can compare 2 same messages and say that both are same
bool test_compare_if_equal () {
    // assume
    char* name = "New";
    game_character character = CROSS;
    void* data = NULL;

    idle_state_message_struct message1 = {INVITE, name, character, data};
    idle_state_message_struct message2 = {INVITE, name, character, data};

    bool expected = true;

    // act
    bool actual = compare_idle_state_messages(message1, message2);

    // assert
    bool test_passed = actual == expected; 

    if (test_passed) 
        printf ("test_idle_state_message_to_string() passed\n");
    else
        printf ("test_idle_state_message_to_string() failed\n");   

    return test_passed;
}

// Test compare_idle_state_messages() to see if it can compare 2 different messages and say that both are different
bool test_compare_if_unequal () {
    // assume
    char* name = "New";
    game_character character = CROSS;
    void* data = NULL;

    idle_state_message_struct message1 = {INVITE, name, character, data};
    idle_state_message_struct message2 = {ACCEPT, name, character, data};

    bool expected = true;
    // act
    bool actual = compare_idle_state_messages(message1, message2);

    // assert
    bool test_passed = actual != expected; 

    if (test_passed) 
        printf ("test_idle_state_message_to_string() passed\n");
    else
        printf ("test_idle_state_message_to_string() failed\n");

    return test_passed;
}

// bool test_idle_state_message_get_type() {
//     // assume

//     // act

//     // assert
// }
// bool test_idle_state_message_get_name() {
//     // assume

//     // act

//     // assert
// }
// bool test_idle_state_message_get_character() {
//     // assume

//     // act

//     // assert
// }
// bool test_idle_state_message_get_data() {
//     // assume

//     // act

//     // assert
// }

// bool test_idle_state_message_set_name() {
//     // assume

//     // act

//     // assert
// }
// bool test_idle_state_message_set_character() {
//     // assume

//     // act

//     // assert
// }
// bool test_idle_state_message_set_data() {
//     // assume

//     // act

//     // assert
// }