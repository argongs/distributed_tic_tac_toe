#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

#include "modules/grid/game_character.h"
#include "modules/combine/combine.h"

int main(int argc, char **argv)
{
    if (signal(SIGINT, apocalypse) == SIG_ERR) {
        fputs("An error occurred while calling the apocalypse.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("Greetings %s! You have opted character %s.\n", argv[1], argv[2]);
    genesis(argv[1] == NULL ? "Default" : argv[1], argv[2][0] != CROSS && argv[2][0] != ZERO ? CROSS : argv[2][0] );
    return 0;
}