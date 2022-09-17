// Provide definitions for functions which will combine all the remaining modules into one

#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "modules/grid/game_character.h"
#include "modules/grid/grid.h"
#include "modules/player/player.h"
#include "modules/ui/ui.h"

sem_t opponent_semaphore;

player_struct *player = NULL;
player_struct *opponent = NULL;
grid_struct *grid = NULL;

pthread_t broadcaster, sniffer, coordinator;

static int send_grid()
{
    show_grid(*grid);

    grid_status_enum game_status_before = get_grid_recent_status(*grid);
    grid_status_enum game_status_after = get_input_for_grid(*player, grid);

    if (game_status_after == GAME_WIN || game_status_after == GAME_DRAW)
    {
        if (game_status_before == game_status_after)
        {
            // Opponent has won/drawn
            if (is_player_interested_in_a_rematch())
            {
                flush_grid(grid);
                show_grid(*grid);
                get_input_for_grid(*player, grid);
            }
            else
                return -1;
        }
        else
        {
            // Player has won/drawn
            switch (game_status_after)
            {
            case GAME_WIN:
                printf("You've won!\n");
                break;
            case GAME_DRAW:
                printf("You've reached a draw!\n");
                break;
            default:
                break;
            }
            printf("Awaiting your opponent's interest in a rematch.");
        }
    }

    return send_grid_to_opponent(grid, *player, *opponent);
}

static void send_first_response()
{

    switch (opponent->player_type)
    {
    case OPPONENT_WITH_PLAYER_INVITE:
        send_grid();
        break;
    case OPPONENT_WITH_OWN_INVITE:
        accept_an_opponent(*player, *opponent);
        break;
    default:;
    }
}

static void coordinate_the_game()
{

    if (opponent != NULL)
    {
        show_opponent_request(*opponent);
        bool opponent_accepted = accept_opponent_request(*opponent);

        if (opponent_accepted)
        {
            send_first_response();

            while (true)
            {
                int recieve_status = recieve_grid_from_opponent(grid, *player, *opponent);

                if (recieve_status == -1)
                {
                    printf("Failed to recieve a response from %s\n", opponent->name);
                    break;
                }

                int send_status = send_grid();

                if (send_status == -1)
                {
                    printf("Failed to send message to %s\n", opponent->name);
                    break;
                }
            }
        }

        flush_grid(grid);
        kill_player(&opponent);
    }
}

static void *broadcast(void *data)
{

    const unsigned int sleep_time = 3;

    while (1)
    {
        sem_wait(&opponent_semaphore);

        if (opponent == NULL)
        {
            printf("Broadcasting your presence into the network ...\n");
            broadcast_player(*player);
        }

        sem_post(&opponent_semaphore);
        sleep(sleep_time);
    }
}

static void *sniff(void *data)
{

    const unsigned int sleep_time = 2;

    while (1)
    {
        sem_wait(&opponent_semaphore);

        if (opponent == NULL)
        {
            printf("Seeking out opponents for you ...\n");
            opponent = look_for_opponents(*player);
        }

        sem_post(&opponent_semaphore);
        sleep(sleep_time);
    }
}

static void *coordinate(void *data)
{

    const unsigned int sleep_time = 1;

    while (1)
    {
        sem_wait(&opponent_semaphore);

        if (opponent != NULL)
        {
            coordinate_the_game();
        }

        sem_post(&opponent_semaphore);
        // sleep(sleep_time);
    }

    return NULL;
}

static int initialise(char *name, game_character character)
{

    srand(time(NULL));

    player = create_player(name, character);
    grid = create_grid();

    if (player == NULL || grid == NULL)
        exit(ENOMEM); // Not enough memory

    // Intialise the opponent related semaphore
    if (sem_init(&opponent_semaphore, 0, 1) != 0)
    {
        printf("Failed to create a semaphore for locking the opponent data");
        return 1;
    }

    // Map threads to corresponding functions
    if (pthread_create(&broadcaster, NULL, broadcast, NULL) != 0)
    {
        printf("Failed to create broadcasting thread\n");
        return 1;
    }
    if (pthread_create(&sniffer, NULL, sniff, NULL) != 0)
    {
        printf("Failed to create listener thread\n");
        return 1;
    }
    if (pthread_create(&coordinator, NULL, coordinate, NULL) != 0)
    {
        printf("Failed to create coordinator thread\n");
        return 1;
    }

    // Activate the threads
    if (pthread_join(broadcaster, NULL) != 0)
        return 1;
    if (pthread_join(sniffer, NULL) != 0)
        return 1;
    if (pthread_join(coordinator, NULL) != 0)
        return 1;
}

int genesis(char *name, game_character character)
{
    printf("\nLet there be light!\n");
    initialise(name, character);
}

void apocalypse()
{
    printf("\nApocalypse, Come!\n");

    kill_player(&player);
    kill_player(&opponent);
    destroy_grid(grid);
    exit(1);
} // Apocalypse will never arrive on its own. It will be invoked by the will of the man (end user)