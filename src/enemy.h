#ifndef ENEMY_H
#define ENEMY_H

#define ENEMY_WIDTH 4
#define ENEMY_HEIGHT 2
#define MAX_ENEMIES 30

typedef struct
{
    int x;
    int y;
    int health;
    int damage;
    int alive;
} Enemy;

extern const char *enemy_model[];
extern Enemy enemies[MAX_ENEMIES];

int spawn_enemy(int x, int y, int health, int damage);
void damage_enemy(Enemy *enemy, int damage);

#endif