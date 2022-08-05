
CC = gcc -O

path_to_message_module=.\modules\message

message: idle_state_message

idle_state_message: $(path_to_message_module)\idle_state_message.c $(path_to_message_module)\idle_state_message.h
	$(CC) $(path_to_message_module)\idle_state_message.c

message_test: $(path_to_message_module)\test\idle_state_message_test.c $(path_to_message_module)\idle_state_message.h