#include "player.h"

#define PLAYER_WIDTH 5
#define PLAYER_HEIGHT 2

const char *player_model[PLAYER_HEIGHT] = {
    "  mAm",
    " MAZAM"
};

void move_player_left(Player *player)
{
    player->x -= 1;
}

void move_player_right(Player *player)
{
    player->x += 1;
}

void damage_player(Player *player, int damage)
{
    player->health -= damage;
}
