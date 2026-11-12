#include "player.h"
#include "utils.h"

#define PLAYER_WIDTH 5
#define PLAYER_HEIGHT 2

const char *player_model[PLAYER_HEIGHT] = {
    " /^\\ ",
    "/W|W\\"};

void move_player_left(Player *player)
{
    if (player->x > 1)
        player->x--;
}

void move_player_right(Player *player)
{
    // its -1 for the border and the same is the move_player_left
    if (player->x < MIN_COLS - PLAYER_WIDTH - 1)
        player->x++;
}

void damage_player(Player *player, int damage)
{
    player->health -= damage;
}
