// Provide definitions for functions which will combine all the remaining modules into one

#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/semaphore.h>

#include "modules/grid/game_character.h"
#include "modules/grid/grid.h"
#include "modules/player/player.h"
#include "modules/ui/ui.h"

sem_t opponent_semaphore;

player_struct* player = NULL;
player_struct* opponent = NULL;
grid_struct* grid = NULL;

pthread_t broadcaster, listener, cooridnator;

static void coordinate_the_game () {

    show_opponent_request(opponent);
    bool opponent_accepted = accept_opponent_request(opponent);

    if (opponent_accepted) {
        // In case of opponent whose INVITE has been accepted, send the ACCEPT response
        // In case of opponent who has accepted this player's invite, mark the first location and send it to the opponent 
    } else {
        kill_player(opponent);
    }
}

static void* broadcast (void* data) {
    
    const unsigned int sleep_time = 1;

    while (1) {
        sem_wait(&opponent_semaphore);

        if (opponent == NULL)
            broadcast_player(*player);
        else
            sleep(sleep_time);

        sem_post(&opponent_semaphore);
    }

}

static void* listen (void* data) {

    const unsigned int sleep_time = 1;

    while (1) {
        sem_wait(&opponent_semaphore);

        if (opponent == NULL)
            opponent = look_for_opponents(*player);
        else
            sleep(sleep_time);
    
        sem_post(&opponent_semaphore);
    }

}

static void* coordinate (void* data) {

    const unsigned int sleep_time = 1;

    while (1) {
        sem_wait(&opponent_semaphore);

        if (opponent != NULL)
            
        else
            sleep(sleep_time);
    
        sem_post(&opponent_semaphore);
    }

}

static int initialise (char* name, game_character character) {

    player = create_player(name, character);
    grid = create_grid();

    if (player == NULL || grid == NULL)
        exit(ENOMEM); // Not enough memory

    // Map threads to corresponding functions
	if (pthread_create (&broadcaster, NULL, broadcast, NULL) != 0)
	{
		printf ("Failed to create broadcasting thread\n");
		return 1;
	}
	if (pthread_create (&listener, NULL, listen, NULL) != 0)
	{	
		printf ("Failed to create listener thread\n");
		return 1;
	}

    // Intialise the opponent related semaphore
    if (sem_init(&opponent_semaphore, 0, 1) != 0) {
        printf ("Failed to create a semaphore for locking the opponent data");
        return 1;
    }

    // Activate the threads
	if (pthread_join (broadcaster, NULL) != 0)
		return 1;
	if (pthread_join (listener, NULL) != 0)
		return 1;	
}

int genesis(char* name, game_character character) {

    initialise(char* name, game_character character);
    


}


int apocalypse(); // Apocalypse will never arrive on its own. It will be invoked by the will of the man (end user) 