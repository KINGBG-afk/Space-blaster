
#ifndef PLAYER_H
#define PLAYER_H

#define PLAYER_WIDTH 5
#define PLAYER_HEIGHT 2

typedef struct
{
    int x;
    int y;
    int health;
    int damage;
    int fire_rate;

} Player;

extern const char *player_model[PLAYER_HEIGHT];

void move_player_left(Player *player);
void move_player_right(Player *player);
void damage_player(Player *player, int damage);

#endif
