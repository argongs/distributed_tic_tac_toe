
#VPATH = modules/message/idle_state_message:test/message/idle_state_message
#vpath %.c ./modules/message/idle_state_message:./test/message/idle_state_message
#vpath %.h ./modules/idle_state_message

CC = gcc
binary_directory = ./bin
message_module_directory = ./modules/message

# For message related modules

idle_state_message.o: idle_state_message.c idle_state_message.h
	$(CC) -c -g $< -o $(binary_directory)/$@ 

idle_state_message_test: idle_state_message_test.c idle_state_message.o
	$(CC) -g $^ -o $@