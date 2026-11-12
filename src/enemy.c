#include "enemy.h"

Enemy enemies[MAX_ENEMIES] = {0};

const char *enemy_model[] = {
    "dOOb",
    "^/\\^"};

int spawn_enemy(int x, int y, int health, int damage, EnemyType type)
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
            enemies[i].type = type;

            return i;
        }
    }

    return -1;
}

int damage_enemy(Enemy *enemy, int damage)
{
    if (!enemy->alive)
        return 0;

    enemy->health -= damage;

    if (enemy->health <= 0)
    {
        enemy->alive = 0;
        return 1;
    }
    return 0;
}