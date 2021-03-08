#include "player.h"
typedef struct Enemy
{
    /* data */
    int x;
    int y;
    int speed;
    int projectile_x;
    int projectile_y;
    int projectile_trigger;
    bool isalive;

}Enemy;

typedef struct EnemyTextures
{
    /* data */
    Texture2D enemy_1;
    Texture2D enemy_2;
    // Im gonna use this struct for music too 
    Music boom;

}EnemyTextures;

typedef struct EnemyCounter
{
    /* data */
    int count;

}EnemyCounter;

#define ENEMY_COUNT 20

static EnemyCounter enemycounter;
static EnemyTextures enemytextures;
static Enemy enemy[ENEMY_COUNT];

