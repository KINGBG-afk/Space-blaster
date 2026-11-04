#include <stdio.h>
#include "game.h"
#include "utils.h"
#include "input.h"
#include "timer.h"
#include <string.h>

// BUG: when resizing get_char detects a symbol: �
// decodes to: 239 191 189

#define FPS 30

int running = 0;

// this is what the player will see
char game_screen[MIN_ROWS][MIN_COLS + 1]; // +1 for the null char

// moves cursor to the top of the console ready to print the game state
// printf("\033[H");

void start_game(void)
{
    update_terminal_size();

    center_text("  _____                     ______ _           _            ", term_cols);
    center_text(" /  ___|                    | ___ \\ |         | |           ", term_cols);
    center_text(" \\ `--. _ __   __ _  ___ ___| |_/ / | __ _ ___| |_ ___ _ __ ", term_cols);
    center_text("  `--. \\ '_ \\ / _` |/ __/ _ \\ ___ \\ |/ _` / __| __/ _ \\ '__|", term_cols);
    center_text(" /\\__/ / |_) | (_| | (_|  __/ |_/ / | (_| \\__ \\ ||  __/ |   ", term_cols);
    center_text(" \\____/| .__/ \\__,_|\\___\\___\\____/|_|\\__,_|___/\\__\\___|_|   ", term_cols);
    center_text("       | |                                                  ", term_cols);
    center_text("       |_|                                                  ", term_cols);

    center_text("_____________|CONTROLS|_____________", term_cols);
    center_text("|       Press A to move left       |", term_cols);
    center_text("|      Press D to move right       |", term_cols);
    center_text("|  Press U to access upgrade menu  |", term_cols);
    center_text("|         Press P to pause         |", term_cols);
    center_text(" |__________________________________|\n", term_cols);
    center_text("Press E to play", term_cols);
    center_text("Press Q to exit\n", term_cols);
    center_text("WARNING!", term_cols);
    center_text("DO NOT USE Ctrl+C to exit the program!", term_cols);
    center_text("it may lead to unexpected behavior", term_cols);

    // maybe get_char() needs refactoring?
    char ch = get_char();
    do
    {
        ch = get_char();
        if (ch == 'q')
        {
            exit_game();
            return;
        }

    } while (ch != 'e');

    // entering main game loop
    Player player = {
        .x = 10,
        .y = MIN_ROWS - PLAYER_HEIGHT, // move to the bottom of the screen
        .health = 3,
        .damage = 1,
    };

    running = 1;

    input_init();
    clear_screen();
    while (running)
    {
        int key = input_poll();

        // handle keys
        if (key != -1)
        {

            switch (key)
            {
            case 'a':
                move_player_left(&player);
                break;

            case 'd':
                move_player_right(&player);
                break;
            case 'p':
                break;
            case 'u':
                break;
            case 'q':
                running = 0;
                break;
            }
        }

        // update game state

        // render
        clear_screen_array();
        draw_player(&player);
        render_screen();

        limit_fps(FPS);
    }

    exit_game();
}

void clear_screen_array(void)
{
    for (int y = 0; y < MIN_ROWS; y++)
    {
        // set MIN_COLS bytes of ' ' in one row
        memset(game_screen[y], '.', MIN_COLS);
        game_screen[y][MIN_COLS] = '\0'; // add null char
    }
}

// insert the player model into the array
void draw_player(Player *player)
{
    for (int y = 0; y < PLAYER_HEIGHT; y++)
    {
        for (int x = 0; x < PLAYER_WIDTH; x++)
        {
            char c = player_model[y][x];
            if (c != ' ')
            {
                game_screen[player->y + y][player->x + x] = c;
            }
        }
    }
}

void render_screen(void)
{
    printf("\033[H");

    for (int y = 0; y < MIN_ROWS; y++)
    {
        printf("%s\n", game_screen[y]);
    }

    fflush(stdout);
}

void exit_game(void)
{
    printf("Exiting game");

    // show the cursor again
    printf("\033[?25h");
    fflush(stdout);
}