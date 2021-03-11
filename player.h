#define XBOX360_NAME_ID     "Xbox 360 Controller"

typedef struct Player
{
    /* data */
    int x;
    int y;
    int dir;
    int speed;
    int projectile_x;
    int projectile_y;
    int projectile_trigger;
    int score;
    Texture2D player_1;
    Texture2D bullet_1;
    Texture2D bullet_2;
    Texture2D bullet_3;
    Music Shoot;

}Player;

typedef struct Projectile{
    int x;
    int y;
    int trigger;
}Projectile;

static Projectile projectile[10];

static Player player;


static void DrawPlayer(){
    DrawTexture(player.player_1, player.x , player.y , WHITE);
    if (IsKeyDown(KEY_LEFT))
    {
        player.x -= player.speed;
    }
    if (IsKeyDown(KEY_RIGHT))
    {
        player.x += player.speed;
    }
    if (IsGamepadAvailable(GAMEPAD_PLAYER1)){
        if (IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_LEFT_FACE_LEFT)){
            player.x -= player.speed;
        }
        if (IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_LEFT_FACE_RIGHT)){
            player.x += player.speed;
        }
    }
    
    if(player.x >= 512){
        player.x -= player.speed;

    }
    if(player.x <= 0){
        player.x += player.speed;

    }
}
