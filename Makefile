
VPATH = ./modules/message/idle_state:./modules/message/playing_state:./modules/grid:test/message/idle_state:./bin:./modules/test

SHELL = /bin/sh
CC = gcc -I .

# Directories
binary_directory = bin


# For message related modules
idle_state_message.o : idle_state_message.c idle_state_message.h game_character.h
	$(CC) -c -g $< -o $(binary_directory)/$@

playing_state_message.o : playing_state_message.c playing_state_message.h game_character.h
	$(CC) -c -g $< -o $(binary_directory)/$@

# For testing
.PHONY = test
test: test.o idle_state_message_test playing_state_message_test
	$(binary_directory)/idle_state_message_test
	$(binary_directory)/playing_state_message_test
	
test.o : test.c test.h
	$(CC) -c -g $< -o $(binary_directory)/$@

idle_state_message_test: idle_state_message_test.c idle_state_message.o test.o
	$(CC) -g $^ -o $(binary_directory)/$@

# playing_state_message_test: playing_state_message_test.c playing_state_message.o test.o
# 	$(CC) -g $^ -o $(binary_directory)/$@