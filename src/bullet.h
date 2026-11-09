#ifndef BULLET_H
#define BULLET_H

// max amount of fired bullets on the screen
#define MAX_BULLETS 150

// this enum is added just for readability
typedef enum
{
    PLAYER,
    ENEMY
} BulletOwner;

typedef struct
{
    int x;
    int y;
    int damage;
    int alive; // 0 for not alive and 1 for alive
    BulletOwner owner;
} Bullet;

extern Bullet bullets[MAX_BULLETS];
extern const char bullet_model;

void update_bullets(void);
int spawn_bullet(BulletOwner owner, int x, int y, int damage);

#endif