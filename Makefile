SHELL = /bin/sh
CC = gcc -I .
DEBUG_FLAG = -g
COMPILE_ONLY_FLAG = -c
OUTPUT_FLAG = -o
THREAD_LIBRARY = -lpthread

# Directories
binary_directory = bin

vpath % modules/message/idle_state:modules/message/playing_state:modules/grid:modules/network:modules/player:modules/ui:modules/combine:modules/test
vpath %.o $(binary_directory)
vpath % test/message/idle_state:test/message/playing_state:test/grid

main : main.c $(binary_directory)/idle_state_message.o $(binary_directory)/playing_state_message.o $(binary_directory)/grid.o $(binary_directory)/network.o $(binary_directory)/player.o $(binary_directory)/ui.o $(binary_directory)/combine.o  
	$(CC) $(DEBUG_FLAG) $^ $(THREAD_LIBRARY) $(OUTPUT_FLAG) $(binary_directory)/$@

.PHONY = all
all : $(binary_directory)/combine.o $(binary_directory)/idle_state_message.o $(binary_directory)/playing_state_message.o $(binary_directory)/grid.o $(binary_directory)/network.o $(binary_directory)/player.o $(binary_directory)/ui.o

# For message related modules
$(binary_directory)/idle_state_message.o : idle_state_message.c idle_state_message.h game_character.h
	$(CC) $(COMPILE_ONLY_FLAG) $(DEBUG_FLAG) $< $(OUTPUT_FLAG) $@

$(binary_directory)/playing_state_message.o : playing_state_message.c playing_state_message.h game_character.h
	$(CC) $(COMPILE_ONLY_FLAG) $(DEBUG_FLAG) $< $(OUTPUT_FLAG) $@

# For other modules
$(binary_directory)/grid.o : grid.c grid.h game_character.h
	$(CC) $(COMPILE_ONLY_FLAG) $(DEBUG_FLAG) $< $(OUTPUT_FLAG) $@

$(binary_directory)/network.o : network.c network.h
	$(CC) $(COMPILE_ONLY_FLAG) $(DEBUG_FLAG) $< $(OUTPUT_FLAG) $@

$(binary_directory)/player.o : player.c $(binary_directory)/idle_state_message.o $(binary_directory)/playing_state_message.o $(binary_directory)/grid.o $(binary_directory)/network.o 
	$(CC) $(COMPILE_ONLY_FLAG) $(DEBUG_FLAG) $< $(OUTPUT_FLAG) $@

$(binary_directory)/ui.o : ui.c $(binary_directory)/player.o
	$(CC) $(COMPILE_ONLY_FLAG) $(DEBUG_FLAG) $< $(OUTPUT_FLAG) $@

$(binary_directory)/combine.o : combine.c $(binary_directory)/ui.o $(binary_directory)/player.o $(binary_directory)/grid.o $(binary_directory)/playing_state_message.o $(binary_directory)/idle_state_message.o
	$(CC) $(COMPILE_ONLY_FLAG) $(DEBUG_FLAG) $< $(OUTPUT_FLAG) $@

# For testing
.PHONY = test
test: test.o grid_test idle_state_message_test playing_state_message_test
	$(binary_directory)/idle_state_message_test
	$(binary_directory)/playing_state_message_test
	$(binary_directory)/grid_test
	
$(binary_directory)/test.o : test.c test.h
	$(CC) $(COMPILE_ONLY_FLAG) $(DEBUG_FLAG) $< $(OUTPUT_FLAG) $@

idle_state_message_test : idle_state_message_test.c test.o $(binary_directory)/idle_state_message.o
	$(CC) $(DEBUG_FLAG) $^ $(OUTPUT_FLAG) $(binary_directory)/$@

playing_state_message_test : playing_state_message_test.c test.o $(binary_directory)/grid.o $(binary_directory)/playing_state_message.o
	$(CC) $(DEBUG_FLAG) $^ $(OUTPUT_FLAG) $(binary_directory)/$@

grid_test : grid_test.c $(binary_directory)/test.o $(binary_directory)/grid.o
	$(CC) $(DEBUG_FLAG) $^ $(OUTPUT_FLAG) $(binary_directory)/$@

.PHONY = clean
clean : 
	rm ./$(binary_directory)/* -v