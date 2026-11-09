#include "bullet.h"
#include "utils.h"

const char bullet_model = '|';
Bullet bullets[MAX_BULLETS];
void update_bullets(void)
{
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (!bullets[i].alive)
        {
            continue;
        }

        if (bullets[i].owner == PLAYER)
        {
            bullets[i].y--;
        }
        // fired from enemy
        else
            bullets[i].y++;

        // check if outside the screen
        if (bullets[i].y < 0 || bullets[i].y > MIN_ROWS)
        {
            bullets[i].alive = 0;
            continue;
        }

        // TODO add collision detection
    }
}

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