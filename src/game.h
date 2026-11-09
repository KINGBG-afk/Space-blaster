#include "player.h"

#ifndef GAME_H // prevents a header being included twice
#define GAME_H

#define FPS 22

void start_game(void);
void clear_screen_array(void);
void draw_player(Player *player);
void draw_bullets();
void render_screen(void);
void exit_game(void);

#endif