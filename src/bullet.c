#include "bullet.h"
#include "utils.h"
#include "player.h"
#include <stdlib.h>

#include "enemy.h"

const char bullet_model = '|';
Bullet bullets[MAX_BULLETS];
void update_bullets(Player *player, int *score)
{
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        Bullet *bullet = &bullets[i];

        if (!bullet->alive)
            continue;

        bullet->y += bullet->owner == PLAYER ? -1 : 1;

        // check if outside the screen
        if (bullet->y < 0 || bullet->y > MIN_ROWS)
        {
            bullet->alive = 0;
            continue;
        }

        for (int j = 0; j < MAX_ENEMIES; j++)
        {
            if (!enemies[j].alive)
                continue;
            // check if bullet hit something
            if ((bullet->x >= enemies[j].x && bullet->x <= enemies[j].x + ENEMY_WIDTH) &&
                (bullet->y >= enemies[j].y && bullet->y <= enemies[j].y + ENEMY_HEIGHT))
            {
                // hits enemy
                *score += damage_enemy(&enemies[j], bullet->damage) * 10; // returns 1 if enemy is killed
                bullet->alive = 0;
                break;
            }
            else if ((bullet->x >= player->x && bullet->x <= player->x + PLAYER_WIDTH) &&
                     (bullet->y >= player->y && bullet->y <= player->y + PLAYER_HEIGHT))
            {
                // hits player
                player->health--;
                bullet->alive = 0;
            }
        }
    }
}

// NOTE i mean as of now i dont need that index returned but lets keep it like this
int spawn_bullet(BulletOwner owner, int x, int y, int damage)
{
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (!bullets[i].alive)
        {
            bullets[i].alive = 1;
            bullets[i].x = x;
            bullets[i].y = y;
            bullets[i].damage = damage;
            bullets[i].owner = owner;

            return i;
        }
    }
    return -1;
}