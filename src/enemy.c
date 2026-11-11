#include "enemy.h"

Enemy enemies[MAX_ENEMIES] = {0};

const char *enemy_model[] = {
    "dOOb",
    "^/\\^"};

int spawn_enemy(int x, int y, int health, int damage)
{
    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        if (!enemies[i].alive)
        {
            enemies[i].x = x;
            enemies[i].y = y;
            enemies[i].health = health;
            enemies[i].damage = damage;
            enemies[i].alive = 1;

            return i;
        }
    }

    return -1;
}

void damage_enemy(Enemy *enemy, int damage)
{
    if (!enemy->alive)
        return;

    enemy->health -= damage;

    if (enemy->health <= 0)
    {
        enemy->alive = 0;
    }
}