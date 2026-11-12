#ifndef ENEMY_H
#define ENEMY_H

#define ENEMY_WIDTH 4
#define ENEMY_HEIGHT 2
#define MAX_ENEMIES 30

typedef enum
{
    Steve,
    Robert,
    Gorge,

} EnemyType;

typedef struct
{
    int x;
    int y;
    int health;
    int damage;
    int alive;
    EnemyType type;
} Enemy;

extern const char *enemy_model[];
extern Enemy enemies[MAX_ENEMIES];

int spawn_enemy(int x, int y, int health, int damage, EnemyType type);
int damage_enemy(Enemy *enemy, int damage);

#endif