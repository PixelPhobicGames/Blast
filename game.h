#include "enemy.h"

#include "delay.h"

typedef struct Game {
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
    int fps;
    time_t time;
    Shader Scanlines;
    Texture2D map_0;
    Texture2D map_1;
    Texture2D map_0_bg;
    Music titlemusic;
    Music victory;
    Music Invaders;
}
Game;

static Game game;

static void EnemyRestart() {
    for (int i; i < ENEMY_COUNT; i++) {
        enemy[i].x = i * 50;
        enemy[i].y = 50;
        enemy[i].isalive = true;
        enemy[i].speed = 1;
        enemy[i].projectile_trigger = false;
        enemy[i].projectile_x = 0;
        enemy[i].projectile_y = 0;
        enemycounter.count++;
    }
    powerupdrone.trigger = false;
    powerupdrone.x = 0;
    powerupdrone.y = -15;
    blastpowerupdrone.trigger = false;
    blastpowerupdrone.x = 0;
    blastpowerupdrone.y = -15;
    StopMusicStream(game.victory);

}

static void CloseGame() {
    UnloadTexture(player.player_1);
    UnloadTexture(player.bullet_1);
    UnloadTexture(player.bullet_2);
    UnloadTexture(player.bullet_3);
    UnloadTexture(game.map_0);
    UnloadTexture(game.map_0_bg);
    UnloadTexture(enemytextures.enemy_1);
    UnloadTexture(enemytextures.enemy_2);
    UnloadTexture(blastpowerupdrone.texture);
    UnloadTexture(powerupdrone.texture);
    UnloadMusicStream(powerupdrone.sound);
    UnloadMusicStream(game.titlemusic);
    UnloadMusicStream(game.Invaders);
    UnloadMusicStream(game.victory);
    UnloadMusicStream(enemytextures.boom);
    UnloadMusicStream(player.Shoot);
    UnloadShader(game.Scanlines);
    CloseAudioDevice();
    CloseWindow();
}

static void GameInit() {
    blastpowerupdrone.PowerUpLength = 0;
    powerupdrone.texture = LoadTexture("assets/alien/drone.png");
    blastpowerupdrone.texture = LoadTexture("assets/alien/bdrone.png");
    powerupdrone.sound = LoadMusicStream("assets/music/drone.mp3");
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
    enemytextures.PowerUpSound = LoadMusicStream("assets/sounds/PowerUP.mp3");
    game.Scanlines = LoadShader(0, TextFormat("assets/shaders/pixel.fs", 330));
    game.round = 1;
    player.x = 22;
    player.y = 406;
    player.score = 1;
    player.high_score = 0;
    player.speed = 5;
    game.level_id = 0;
    game.map_x = 0;
    game.map_y = 0;
    game.dir = 1;
    game.level = 1;
    game.IntScaler = 1;
    game.fps = 60;
    game.ShadersEnabled = true;
    enemycounter.count = 0;
    EnemyRestart();
    for (int i; i < ENEMY_COUNT; i++) {
        projectile[i].x = 0;
        projectile[i].y = 0;
        projectile[i].trigger = false;
    }

}

static void UpdateAnimations() {
    game.animation_counter += 3;
    if (game.animation_counter >= 100) {
        game.animation_counter = 0;
    }
}

static void UpdateSpaceBackground() {
    if (game.map_x <= -500) {
        game.map_x = 1;
    }
    game.map_x -= 1 * game.IntScaler;
}

static void UpdateMusic() {
    UpdateMusicStream(player.Shoot);
    UpdateMusicStream(game.titlemusic);
    UpdateMusicStream(enemytextures.boom);
    UpdateMusicStream(game.victory);
    UpdateMusicStream(game.Invaders);
    UpdateMusicStream(powerupdrone.sound);
    UpdateMusicStream(enemytextures.PowerUpSound);
}

static void UpdateProjectiles() {
    for (int i = 0; i < ENEMY_COUNT; i++) {
        if (IsGamepadAvailable(GAMEPAD_PLAYER1)) {
            if (IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_RIGHT_TRIGGER_2) && projectile[i].trigger == false) {
                projectile[i].trigger = true;
                projectile[i].x = player.x + 50;
                projectile[i].y = player.y - 9;
                PlayMusicStream(player.Shoot);
            }
        } else {
            if (IsKeyPressed(KEY_SPACE) && projectile[i].trigger == false) {
                projectile[i].trigger = true;
                projectile[i].x = player.x + 50;
                projectile[i].y = player.y - 9;
                PlayMusicStream(player.Shoot);
            }
            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && projectile[i].trigger == false) {
                projectile[i].trigger = true;
                projectile[i].x = player.x + 50;
                projectile[i].y = player.y - 9;
                PlayMusicStream(player.Shoot);
            }
        }
        if (projectile[i].trigger) {
            if (game.animation_counter <= 25) {
                DrawTexture(player.bullet_1, projectile[i].x, projectile[i].y, WHITE);
            }
            if (game.animation_counter <= 50) {
                DrawTexture(player.bullet_2, projectile[i].x, projectile[i].y, WHITE);
            }
            if (game.animation_counter <= 75) {
                DrawTexture(player.bullet_3, projectile[i].x, projectile[i].y, WHITE);
            }
            if (game.animation_counter <= 100) {
                DrawTexture(player.bullet_2, projectile[i].x, projectile[i].y, WHITE);
            }
            if (blastpowerupdrone.PowerUpLength == 0) {
                projectile[i].y -= 5 * game.IntScaler;
            } else {
                projectile[i].y -= 12 * game.IntScaler;
            }

            if (projectile[i].y <= -50) {
                if (blastpowerupdrone.PowerUpLength != 0) {
                    blastpowerupdrone.PowerUpLength -= 1;
                }
                projectile[i].trigger = false;
                StopMusicStream(player.Shoot);
                StopMusicStream(enemytextures.PowerUpSound);
                StopMusicStream(enemytextures.boom);
            }
        }
    }
}

static void DrawEnemys() {
    for (int i = 0; i < ENEMY_COUNT; i++) {
        if (enemy[i].isalive) {
            DrawTexture(enemytextures.enemy_1, enemy[i].x, enemy[i].y, WHITE);
            if (projectile[i].x >= enemy[i].x && projectile[i].x <= enemy[i].x + 50 && projectile[i].y <= enemy[i].y + 50 && projectile[i].y >= enemy[i].y) {
                player.score++;
                enemycounter.count--;
                DrawTexture(enemytextures.enemy_2, enemy[i].x, enemy[i].y, WHITE);
                PlayMusicStream(enemytextures.boom);
                enemy[i].isalive = false;

            }
            if (game.animation_counter >= 25) {
                enemy[i].x += enemy[i].speed + game.level * game.IntScaler;
            }
            if (enemy[i].x >= 450) {
                enemy[i].x -= 400;
                enemy[i].y += 50;
            }
            if (enemy[i].y >= 380) {
                game.level_id = 2;
            }
            if (enemycounter.count == 0) {
                enemy[i].speed++;
                PlayMusicStream(game.victory);
                game.round++;
                EnemyRestart();
                game.level_id = 3;
            }
            if (player.score <= 0) {
                game.level_id = 2;
            }
            if (GenerateRandomNumber(25) == 15) {
                if (enemy[i].projectile_trigger == false) {
                    enemy[i].projectile_trigger = true;
                    enemy[i].projectile_x = enemy[i].x + 20;
                    enemy[i].projectile_y = enemy[i].y - 9;
                }
            }
            if (enemy[i].projectile_trigger == true) {
                DrawRectangle(enemy[i].projectile_x, enemy[i].projectile_y, 5, 5, WHITE);
                enemy[i].projectile_y += 2 * enemy[i].speed * game.IntScaler;
                if (enemy[i].projectile_y >= 500) {
                    enemy[i].projectile_trigger = false;
                }
                if (enemy[i].projectile_x >= player.x && enemy[i].projectile_x <= player.x + 50 && enemy[i].projectile_y <= player.y + 50 && enemy[i].projectile_y >= player.y) {
                    if (game.round <= 10) {
                        player.score -= 1 * game.round;
                    }
                    player.score -= 1;
                    enemy[i].projectile_trigger = false;
                }
            }
            if (powerupdrone.trigger) {
                if (projectile[i].x >= powerupdrone.x && projectile[i].x <= powerupdrone.x + 50 && projectile[i].y <= powerupdrone.y + 50 && projectile[i].y >= powerupdrone.y) {
                    player.score += 50;
                    PlayMusicStream(enemytextures.PowerUpSound);
                    StopMusicStream(powerupdrone.sound);
                    powerupdrone.trigger = false;
                }
            }
            if (blastpowerupdrone.trigger) {
                if (projectile[i].x >= blastpowerupdrone.x && projectile[i].x <= blastpowerupdrone.x + 50 && projectile[i].y <= blastpowerupdrone.y + 50 && projectile[i].y >= blastpowerupdrone.y) {
                    PlayMusicStream(enemytextures.PowerUpSound);
                    player.score += 20;
                    blastpowerupdrone.PowerUpLength = 100;
                    StopMusicStream(powerupdrone.sound);
                    StopMusicStream(enemytextures.PowerUpSound);
                    blastpowerupdrone.trigger = false;
                }
            }
        }
    }
    if (GenerateRandomNumber(25) == 14 && powerupdrone.trigger == false) {
        powerupdrone.trigger = true;
        powerupdrone.x = 500;
        powerupdrone.y = 50;

    }
    if (powerupdrone.trigger) {
        PlayMusicStream(powerupdrone.sound);
        DrawTexture(powerupdrone.texture, powerupdrone.x, powerupdrone.y, WHITE);
        powerupdrone.x -= 2 * game.IntScaler;
        if (powerupdrone.x <= 0) {
            powerupdrone.x = 0;
            powerupdrone.y = 0;
            StopMusicStream(powerupdrone.sound);
            powerupdrone.trigger = false;
        }
    }

    if (GenerateRandomNumber(50) == 49 && blastpowerupdrone.trigger == false) {
        blastpowerupdrone.trigger = true;
        blastpowerupdrone.x = 500;
        blastpowerupdrone.y = 50;
    }

    if (blastpowerupdrone.trigger) {
        PlayMusicStream(powerupdrone.sound);
        DrawTexture(blastpowerupdrone.texture, blastpowerupdrone.x, blastpowerupdrone.y, WHITE);
        blastpowerupdrone.x -= 2 * game.IntScaler;
        if (blastpowerupdrone.x <= 0) {
            blastpowerupdrone.x = 0;
            blastpowerupdrone.y = 0;
            StopMusicStream(powerupdrone.sound);
            blastpowerupdrone.trigger = false;
        }
    }
}

static void DrawPlayer() {
    DrawTexture(player.player_1, player.x, player.y, WHITE);
    if (IsKeyDown(KEY_LEFT)) {
        player.x -= player.speed * game.IntScaler;
    }
    if (IsKeyDown(KEY_RIGHT)) {
        player.x += player.speed * game.IntScaler;
    }
    if (IsGamepadAvailable(GAMEPAD_PLAYER1)) {
        if (IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_LEFT_FACE_LEFT)) {
            player.x -= player.speed * game.IntScaler;
        }
        if (IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_LEFT_FACE_RIGHT)) {
            player.x += player.speed * game.IntScaler;
        }
    }

    if (player.x >= 512) {
        player.x -= player.speed * game.IntScaler;

    }
    if (player.x <= 0) {
        player.x += player.speed * game.IntScaler;

    }
}

int GenerateRandomNumber(int val) {
    srand((unsigned) time( & game.time));
    return rand() % val;
}

int GetCollision(int x, int y, int Smallx, int Bigx, int Smally, int Bigy) {
    if (x >= Smallx && x <= Bigx && y <= Bigy && y >= Smally) {
        return true;
    } else {
        return false;
    }
}