SHELL = /bin/sh
CC = gcc -I .
DEBUG_FLAG = -g
COMPILE_ONLY_FLAG = -c
OUTPUT_FLAG = -o

# Directories
binary_directory = bin

vpath % modules/message/idle_state:modules/message/playing_state:modules/grid:modules/network:modules/player:modules/test
vpath % test/message/idle_state:test/message/playing_state:test/grid
vpath %.o bin


# For message related modules
idle_state_message.o : idle_state_message.c idle_state_message.h game_character.h
	$(CC) $(COMPILE_ONLY_FLAG) $(DEBUG_FLAG) $< $(OUTPUT_FLAG) $(binary_directory)/$@

playing_state_message.o : playing_state_message.c playing_state_message.h game_character.h
	$(CC) $(COMPILE_ONLY_FLAG) $(DEBUG_FLAG) $< $(OUTPUT_FLAG) $(binary_directory)/$@

# For other modules
grid.o : grid.c grid.h game_character.h
	$(CC) $(COMPILE_ONLY_FLAG) $(DEBUG_FLAG) $< $(OUTPUT_FLAG) $(binary_directory)/$@

network.o : network.c network.h
	$(CC) $(COMPILE_ONLY_FLAG) $(DEBUG_FLAG) $< $(OUTPUT_FLAG) $(binary_directory)/$@

player.o : player.c idle_state_message.o playing_state_message.o grid.o network.o 
	$(CC) $(COMPILE_ONLY_FLAG) $(DEBUG_FLAG) $< $(OUTPUT_FLAG) $(binary_directory)/$@

# For testing
.PHONY = test
test: test.o idle_state_message_test playing_state_message_test grid_test
	$(binary_directory)/idle_state_message_test
	$(binary_directory)/playing_state_message_test
	$(binary_directory)/grid_test
	
test.o : test.c test.h
	$(CC) $(COMPILE_ONLY_FLAG) $(DEBUG_FLAG) $< $(OUTPUT_FLAG) $(binary_directory)/$@

idle_state_message_test : idle_state_message_test.c idle_state_message.o test.o
	$(CC) $(DEBUG_FLAG) $^ $(OUTPUT_FLAG) $(binary_directory)/$@

playing_state_message_test : playing_state_message_test.c playing_state_message.o test.o grid.o
	$(CC) $(DEBUG_FLAG) $^ $(OUTPUT_FLAG) $(binary_directory)/$@

grid_test : grid_test.c grid.o test.o
	$(CC) $(DEBUG_FLAG) $^ $(OUTPUT_FLAG) $(binary_directory)/$@