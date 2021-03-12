#include "player.h"

typedef struct Enemy {
    int x;
    int y;
    int speed;
    int projectile_x;
    int projectile_y;
    int projectile_trigger;
    bool isalive;

}
Enemy;

typedef struct EnemyTextures {
    Texture2D enemy_1;
    Texture2D enemy_2;
    // Im gonna use this struct for music too 
    Music boom;
    Music PowerUpSound;

}
EnemyTextures;

typedef struct EnemyCounter {
    int count;

}
EnemyCounter;

typedef struct PowerupDrone {
    int x;
    int y;
    Texture2D texture;
    int trigger;
    int PowerUpLength;
    Music sound;
}
PowerupDrone;

#define ENEMY_COUNT 20

static EnemyCounter enemycounter;
static EnemyTextures enemytextures;
static PowerupDrone powerupdrone;
static PowerupDrone blastpowerupdrone;
static Enemy enemy[ENEMY_COUNT];