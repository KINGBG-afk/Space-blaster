#include "player.h"

#ifndef GAME_H // prevents a header being included twice
#define GAME_H

#define FPS 22

void start_game(void);
void run();
void run(void);
void clear_screen_array(void);
void clear_stats_array(void);
void draw_stats(int x, int y, char *s);
void draw_player(Player *player);
void draw_enemies();
void draw_bullets();
void render_game_screen(void);
void render_stats_screen(void);
void exit_game(void);

#endif