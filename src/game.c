#include <stdio.h>
#include "game.h"
#include "utils.h"
#include <string.h>

int running = 1;

// this is what the player will see
int game_screen[MIN_ROWS][MIN_COLS];

// moves cursor to the top of the console ready to print the game state
// printf("\033[H");

void start_game(void)
{

    char *a_control = "|        Press A to move left         |";
    update_terminal_size();  

center_text("  _____                     ______ _           _            ", term_cols);
center_text(" /  ___|                    | ___ \\ |         | |           ", term_cols);
center_text(" \\ `--. _ __   __ _  ___ ___| |_/ / | __ _ ___| |_ ___ _ __ ", term_cols);
center_text("  `--. \\ '_ \\ / _` |/ __/ _ \\ ___ \\ |/ _` / __| __/ _ \\ '__|", term_cols);
center_text(" /\\__/ / |_) | (_| | (_|  __/ |_/ / | (_| \\__ \\ ||  __/ |   ", term_cols);
center_text(" \\____/| .__/ \\__,_|\\___\\___\\____/|_|\\__,_|___/\\__\\___|_|   ", term_cols);
center_text("       | |                                                  ", term_cols);
center_text("       |_|                                                  ", term_cols);

    center_text("    ┌-------------CONTROLS-------------┐", term_cols);
    center_text("|       Press A to move left       |", term_cols);
    center_text("|      Press D to move right       |", term_cols);
    center_text("|  Press U to access upgrade menu  |", term_cols);
    center_text("|         Press P to pause         |", term_cols);
    center_text("     └----------------------------------┘\n", term_cols);
    center_text("Press enter to continue", term_cols);

    exit_game();
}

void exit_game()
{
    // show the cursor again
    printf("\033[?25h");
}