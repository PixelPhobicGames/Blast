#include "enemy.h"
#include "delay.h"

typedef struct Game
{
    /* data */
    bool debug;
    bool ShadersEnabled;
    int level_id;
    int level;
    int map_x;
    int map_y;
    int dir;
    int round;
    int animation_counter;
    int text_y;
    int IntScaler;
    time_t time;
    Shader Scanlines;
    Texture2D map_0; 
    Texture2D map_1; 
    Texture2D map_0_bg;
    Music titlemusic; 
    Music victory; 
    Music Invaders;

}Game;
static Game game;

static void EnemyRestart(){
    for (int i; i < ENEMY_COUNT; i ++){
        enemy[i].x = i * 50 ;
        enemy[i].y = 50;
        enemy[i].isalive = true;
        enemy[i].speed = 1;
        enemy[i].projectile_trigger = false;
        enemy[i].projectile_x = 0;
        enemy[i].projectile_y = 0;
        enemycounter.count ++;
    }
    StopMusicStream(game.victory);

}

static void CloseGame(){

    UnloadTexture(player.player_1);
    UnloadTexture(player.bullet_1);
    UnloadTexture(player.bullet_2);
    UnloadTexture(player.bullet_3);
    UnloadTexture(game.map_0);
    UnloadTexture(game.map_0_bg);
    UnloadTexture(enemytextures.enemy_1);
    UnloadTexture(enemytextures.enemy_2);
    UnloadMusicStream(player.Shoot);
    UnloadShader(game.Scanlines);
    CloseWindow();
    CloseAudioDevice();
    
}

static void GameInit(){
    enemytextures.enemy_1 = LoadTexture("assets/alien/enemy_1.png");
    enemytextures.enemy_2 = LoadTexture("assets/alien/death/frame_7.png");
    enemytextures.boom = LoadMusicStream("assets/sounds/boom.mp3");
    player.Shoot = LoadMusicStream("assets/sounds/shoot.mp3");
    player.player_1 = LoadTexture("assets/player/player_1.png");
    player.bullet_2 = LoadTexture("assets/bullets/rocket_2.png");
    player.bullet_3 = LoadTexture("assets/bullets/rocket_3.png");
    player.bullet_1 = LoadTexture("assets/bullets/rocket_1.png");
    game.map_0 = LoadTexture("assets/maps/map_0.png");
    game.map_0_bg = LoadTexture("assets/maps/map_0_background.png");
    game.titlemusic = LoadMusicStream("assets/music/Phobos.mp3");
    game.Invaders = LoadMusicStream("assets/music/Invaders.mp3");
    game.victory = LoadMusicStream("assets/sounds/win.mp3");
    game.Scanlines = LoadShader(0, TextFormat("assets/shaders/pixel.fs", 330));
    game.round = 1;
    player.x = 22;
    player.y = 406;
    player.score = 1;
    player.speed = 5;
    game.level_id = 0;
    game.map_x = 0;
    game.map_y = 0;
    game.dir = 1;
    game.level = 1;
    game.IntScaler = 1;
    enemycounter.count = 0;
    EnemyRestart();
    for (int i; i < ENEMY_COUNT; i ++){
        projectile[i].x = 0;
        projectile[i].y = 0;
        projectile[i].trigger = false;
    }

}


static void UpdateAnimations(){
    game.animation_counter += 3;
    if (game.animation_counter >= 100){
        game.animation_counter = 0;
    }
}

static void UpdateSpaceBackground(){
    if (game.map_x == -500){
        game.map_x = 1; 
    }
    game.map_x --;
}

static void UpdateMusic(){
    UpdateMusicStream(player.Shoot);
    UpdateMusicStream(game.titlemusic);
    UpdateMusicStream(enemytextures.boom);
    UpdateMusicStream(game.victory);
    UpdateMusicStream(game.Invaders);
}
static void UpdateProjectiles()
{
    for (int i = 0; i < ENEMY_COUNT; i++)
    {
        if (IsKeyPressed(KEY_SPACE) && projectile[i].trigger == false)
        {
            projectile[i].trigger = true;
            projectile[i].x = player.x + 50;
            projectile[i].y = player.y - 9;
            PlayMusicStream(player.Shoot);
        }
        if(projectile[i].trigger){
            if (game.animation_counter <= 25){
                DrawTexture(player.bullet_1, projectile[i].x , projectile[i].y, WHITE);
            }
            if (game.animation_counter <= 50){
                DrawTexture(player.bullet_2, projectile[i].x , projectile[i].y, WHITE);
            }
            if (game.animation_counter <= 75){
                DrawTexture(player.bullet_3, projectile[i].x , projectile[i].y, WHITE);
            }
            if (game.animation_counter <= 100){
                DrawTexture(player.bullet_2, projectile[i].x , projectile[i].y, WHITE);
            }
            projectile[i].y -= 4;
            if (projectile[i].y <= -50){
                projectile[i].trigger = false;
                StopMusicStream(player.Shoot);
                StopMusicStream(enemytextures.boom);
            }
        }
    }
}


static void DrawEnemys(){
    for (int i = 0; i < ENEMY_COUNT; i++)
    {
        if (enemy[i].isalive){
            DrawTexture(enemytextures.enemy_1, enemy[i].x , enemy[i].y , WHITE);
            if (projectile[i].x >= enemy[i].x && projectile[i].x <= enemy[i].x + 50 && projectile[i].y <= enemy[i].y + 50 && projectile[i].y >= enemy[i].y){
                player.score ++;
                enemycounter.count --;
                DrawTexture(enemytextures.enemy_2, enemy[i].x , enemy[i].y , WHITE);
                PlayMusicStream(enemytextures.boom);
                enemy[i].isalive = false;

            }
            if (game.animation_counter >= 25){
                enemy[i].x += enemy[i].speed + game.level; 
            }
            if (enemy[i].x >= 450){
                enemy[i].x -= 400;
                enemy[i].y += 50 ;   
            }
            if (player.x - enemy[i].x <= 128 && player.x - enemy[i].x >= 0 && player.y - enemy[i].y >= -50 &&player.y - enemy[i].y <= 0) {
                game.level_id = 2;
            }
            if (enemycounter.count == 0){
                enemy[i].speed ++;
                PlayMusicStream(game.victory);
                game.round ++;
                EnemyRestart();
                game.level_id = 3;
            }
            if(player.score <= 0){
                game.level_id = 2;
            }
            if(GenerateRandomNumber(25) == 15){
                if (enemy[i].projectile_trigger == false){
                    enemy[i].projectile_trigger = true;
                    enemy[i].projectile_x =  enemy[i].x + 20;
                    enemy[i].projectile_y =  enemy[i].y - 9;
                }
            }
            if (enemy[i].projectile_trigger == true ){
                DrawRectangle(enemy[i].projectile_x,enemy[i].projectile_y,5,5,WHITE);
                enemy[i].projectile_y += 2*enemy[i].speed;
                if ( enemy[i].projectile_y >= 500){
                    enemy[i].projectile_trigger = false;
                }
                if (enemy[i].projectile_x >= player.x && enemy[i].projectile_x <= player.x + 50 && enemy[i].projectile_y <= player.y + 50 && enemy[i].projectile_y >= player.y){
                    if (game.round <= 10 ){
                        player.score -= 1*game.round;
                    }
                    if (game.round){

                    }

                    player.score -= 1;
                    enemy[i].projectile_trigger = false;
                }
            }
        }
        
    }
}


int GenerateRandomNumber(int val){
    srand((unsigned) time(&game.time));

    return rand() % val;
}