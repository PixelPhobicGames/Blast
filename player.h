#define XBOX360_NAME_ID "Xbox 360 Controller"

typedef struct Player {
    /* data */
    int x;
    int y;
    int dir;
    int speed;
    int projectile_x;
    int projectile_y;
    int projectile_trigger;
    int score;
    char high_score;
    Texture2D player_1;
    Texture2D bullet_1;
    Texture2D bullet_2;
    Texture2D bullet_3;
    Music Shoot;
}
Player;

typedef struct Projectile {
    int x;
    int y;
    int trigger;
}
Projectile;

static Projectile projectile[10];

static Player player;


