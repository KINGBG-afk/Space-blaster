#include <string.h>
#include <stdio.h>
#include "game.h"
#include "utils.h"
#include "input.h"
#include "timer.h"
#include "bullet.h"
#include "enemy.h"
#include "upgrades.h"

// BUG: after you kill an enemy he is still there

// apperently if its called 'pause'
// the program gives a segmentation fault
int paused = 0;
int running = 0;
int score = 0;

// this is what the player will see
// MIN_ROWS + 1 is for the border - same for MIN_COLS but we also add a null character
char game_screen[MIN_ROWS + 1][MIN_COLS + 2];

void start_game(void)
{
    // NOTE this is only needed for the starting screen of the game
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
    center_text("|       Press A to move left        |", term_cols);
    center_text("|      Press D to move right        |", term_cols);
    center_text("|         Press SPACE to shoot      |", term_cols);
    center_text("|     Press U for upgrade menu      |", term_cols);
    center_text("|         Press P to pause          |", term_cols);
    center_text(" |___________________________________|\n", term_cols);
    center_text("Press E to play", term_cols);
    center_text("Press Q to exit\n", term_cols);
    center_text("WARNING!", term_cols);
    center_text("DO NOT USE Ctrl+C to exit the program!", term_cols);
    center_text("it may lead to unexpected behavior", term_cols);

    // NOTE add this when game is done
    /*
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

    */
    run();
}

void run()
{
    running = 1;
    double fire_interval = FIRE_INTERVAL;
    double fire_timer = fire_interval;

    Player player = {
        .x = 10,
        .y = MIN_ROWS - PLAYER_HEIGHT - 1, // move to the bottom of the screen
        .health = 3,
        .damage = 1,
    };

    // bullets update 30 times a second so we need to limit it
    int control_bullet_update = 0;

    for (int i = 0; i < 5; i++)
    {
        spawn_enemy((10 * i) + 1, 10, 5, 5, Steve);
    }

    input_init();
    clear_screen();
    while (running)
    {
        update_terminal_size();
        // pause the game untill it becomes the needed size
        if (!terminal_size_ok())
        {
            clear_screen();
            printf("Game needs to be at least %u columns and %u rows big\n", MIN_COLS, MIN_ROWS);
            printf("Make the window bigger!\n");

            // lets not waste extra resorces with that
            limit_fps(1);
            continue;
        }

        if (paused == 1)
        {
            clear_screen();
            printf("Game paused");
            continue;
        }
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
                paused = paused ? 0 : 1;
                break;
            case 'u':
                upgrade_fire_rate(&fire_interval);
                break;
            case 'q':
                running = 0;
                break;
            }
        }

        // used for debug pourpeses only when rendering
        // clear_screen();

        // render
        clear_screen_array();
        draw_player(&player);
        draw_enemies();
        draw_bullets();
        render_screen();
        printf("%d", score);

        // update game elements
        // bullets
        if (control_bullet_update)
        {
            update_bullets(&player, &score);
            control_bullet_update = 0;
        }
        else
            control_bullet_update = 1;

        // player
        fire_timer += 1.0 / FPS;
        if (fire_timer >= fire_interval)
        {
            spawn_bullet(PLAYER, player.x + 2, player.y - 1, 1);
            fire_timer -= fire_interval;
        }

        limit_fps(FPS);
    }

    exit_game();
}

void clear_screen_array(void)
{
    for (int y = 0; y < MIN_ROWS; y++)
    {
        memset(game_screen[y], '.', MIN_COLS);

        for (int x = 0; x < MIN_COLS; x++)
        {
            // Top and bottom borders
            if (y == MIN_ROWS - 1 || y == 0)
                game_screen[y][x] = '|';

            // Left and right borders
            if (x == MIN_COLS - 1 || x == 0)
                game_screen[y][x] = '|';
        }

        game_screen[y][MIN_COLS] = '\0';
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

// enemies_array just so they dont overlap
void draw_enemies(void)
{
    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        if (!enemies[i].alive)
            continue;

        for (int y = 0; y < ENEMY_HEIGHT; y++)
        {
            for (int x = 0; x < ENEMY_WIDTH; x++)
            {
                int screen_x = enemies[i].x + x;
                int screen_y = enemies[i].y + y;

                if (screen_x >= 0 && screen_x < MIN_COLS &&
                    screen_y >= 0 && screen_y < MIN_ROWS)
                {
                    game_screen[screen_y][screen_x] = enemy_model[y][x];
                }
            }
        }
    }
}

void draw_bullets()
{
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (!bullets[i].alive)
            continue;

        // check if position is valid
        if (bullets[i].x < 0 || bullets[i].x >= MIN_COLS ||
            bullets[i].y < 0 || bullets[i].y >= MIN_ROWS)
            continue;

        game_screen[bullets[i].y][bullets[i].x] = bullet_model;
    }
}

void render_screen(void)
{
    // moves cursor to the top of the console ready to print the game state
    printf("\033[H");

    for (int y = 0; y < MIN_ROWS; y++)
    {
        center_text(game_screen[y], term_cols);
    }
    fflush(stdout);
}

void exit_game(void)
{
    clear_screen();
    printf("Exiting game...\n");
    printf("Thanks for playing my game!\n");

    // show the cursor again
    printf("\033[?25h");

    input_shutdown();
    fflush(stdout);
}