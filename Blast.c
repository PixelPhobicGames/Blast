// I hope you can somehow deciper this horrible code 
// Retro - GameJam March 4th - 12th 2021

// Liquid ( Ewan Cole )

#include <raylib.h>

#include <stdio.h>

#include <stdbool.h>

#include <stdlib.h>

#include "game.h"

int main(void) {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(640, 480, "BLAST");
    InitAudioDevice();
    SetTargetFPS(60);
    GameInit();
    Vector2 MousePosition = {
        0.0f,
        0.0f
    };

    while (!WindowShouldClose()) {
        UpdateMusic();
        BeginDrawing();
        if (game.ShadersEnabled) {
            BeginShaderMode(game.Scanlines);
        }
        DrawTexture(game.map_0_bg, game.map_x, game.map_y, WHITE);
        UpdateSpaceBackground();
        ClearBackground(BLACK);
        MousePosition = GetMousePosition();
        switch (game.level_id) {
            case 0:
                PlayMusicStream(game.titlemusic);
                DrawTexture(game.map_0, 0, 0, WHITE);
                DrawCircleV(MousePosition, 5, WHITE);
                DrawText("RetroGame Jam 2021", 400, 440, 20, WHITE);

                if (IsKeyPressed(KEY_SPACE)) {
                    StopMusicStream(game.titlemusic);
                    game.level_id = 3;
                }
                if (IsGamepadAvailable(GAMEPAD_PLAYER1)) {
                    if (IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_RIGHT_TRIGGER_2)) {
                        StopMusicStream(game.titlemusic);
                        game.level_id = 3;
                    }
                }
                if (GetCollision(MousePosition.x, MousePosition.y, 40, 120, 440, 460) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    game.level_id = 4;
                } else {
                    if (GetCollision(MousePosition.x, MousePosition.y, 40, 120, 440, 460)) {
                        DrawText("Settings", 40, 440, 20, WHITE);
                    } else {
                        DrawText("Settings", 40, 440, 16, WHITE);
                    }
                }

                if (IsKeyDown(KEY_Q)) {
                    game.debug = true;
                }

                if (game.animation_counter <= 50 && game.animation_counter >= 0) {
                    if (IsGamepadAvailable(GAMEPAD_PLAYER1)) {
                        DrawText("Press  R-T", 240, 220, 20, WHITE);
                    } else {
                        DrawText("Press Space", 240, 220, 20, WHITE);
                    }
                }
                
                break;

            case 1:
                PlayMusicStream(game.Invaders);
                DrawPlayer();
                UpdateProjectiles();
                DrawEnemys();
                break;
            case 2:
                if (game.animation_counter <= 50 && game.animation_counter >= 0) {
                    DrawText("Game   Over", 240, 220, 20, WHITE);
                }
                if (IsGamepadAvailable(GAMEPAD_PLAYER1)) {
                    DrawText("Press   R-T", 240, 260, 20, WHITE);
                    if (IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_RIGHT_TRIGGER_2)) {
                        GameInit();
                    }
                } else {
                    DrawText("Press Space", 240, 260, 20, WHITE);
                    if (IsKeyPressed(KEY_SPACE)) {
                        GameInit();
                    }
                }
                break;
            case 3:
                StopMusicStream(player.Shoot);
                StopMusicStream(enemytextures.boom);
                if (game.text_y <= 200) {
                    game.text_y += 1 * game.IntScaler;
                }

                DrawText(TextFormat("  Round %i", game.round), 200, game.text_y, 40, GREEN);
                if (IsGamepadAvailable(GAMEPAD_PLAYER1)) {
                    DrawText("Press  R-T", 240, 260, 20, WHITE);
                } else {
                    DrawText("Press Space", 240, 260, 20, WHITE);
                }
                if (IsKeyPressed(KEY_SPACE)) {
                    //GameInit();
                    game.text_y = 0;
                    game.level_id = 1;

                }
                if (IsGamepadAvailable(GAMEPAD_PLAYER1)) {
                    if (IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_RIGHT_TRIGGER_2)) {
                        game.text_y = 0;
                        game.level_id = 1;
                    }
                }
                break;

            case 4:
                EndShaderMode();
                DrawText(" Settings  ", 250, 50, 20, WHITE);
                DrawText(" FPS ", 100, 120, 18, WHITE);
                DrawText(" Shader ", 80, 175, 18, WHITE);
                DrawText("Help", 540, 50, 20, WHITE);
                DrawText("Back", 50, 50, 20, WHITE);

                if (game.fps == 60) {

                    DrawRectangle(155, 115, 40, 30, WHITE);
                    DrawRectangle(235, 115, 40, 30, WHITE);
                    DrawRectangle(195, 115, 40, 30, GRAY);

                }
                if (game.fps == 30) {
                    DrawRectangle(155, 115, 40, 30, GRAY);
                    DrawRectangle(235, 115, 40, 30, WHITE);
                    DrawRectangle(195, 115, 40, 30, WHITE);
                }
                if (game.fps == 15) {
                    DrawRectangle(155, 115, 40, 30, WHITE);
                    DrawRectangle(195, 115, 40, 30, WHITE);
                    DrawRectangle(235, 115, 40, 30, GRAY);
                }
                DrawText(" 30 ", 160, 120, 18, BLACK);
                DrawText(" 60 ", 200, 120, 18, BLACK);
                DrawText(" 15 ", 240, 120, 18, BLACK);

                if (GetCollision(MousePosition.x, MousePosition.y, 155, 195, 115, 145) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    game.fps = 30;
                    game.IntScaler = 2;
                    SetTargetFPS(30);
                }
                if (GetCollision(MousePosition.x, MousePosition.y, 195, 235, 115, 145) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    game.fps = 60;
                    game.IntScaler = 1;
                    SetTargetFPS(60);

                }

                if (GetCollision(MousePosition.x, MousePosition.y, 235, 275, 115, 145) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    game.fps = 15;
                    game.IntScaler = 3;
                    SetTargetFPS(15);

                }

                if (game.ShadersEnabled) {
                    DrawRectangle(155, 170, 40, 30, GRAY);;
                    DrawRectangle(195, 170, 40, 30, WHITE);
                } else {
                    DrawRectangle(155, 170, 40, 30, WHITE);
                    DrawRectangle(195, 170, 40, 30, GRAY);
                }
                DrawText(" ON ", 160, 175, 18, BLACK);
                DrawText(" OFF ", 195, 175, 18, BLACK);

                if (GetCollision(MousePosition.x, MousePosition.y, 155, 195, 175, 215) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    game.ShadersEnabled = true;
                }
                if (GetCollision(MousePosition.x, MousePosition.y, 195, 235, 175, 215) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    game.ShadersEnabled = false;
                }

                if (GetCollision(MousePosition.x, MousePosition.y, 535, 580, 40, 65) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    game.level_id = 5;
                }
                if (GetCollision(MousePosition.x, MousePosition.y, 45, 80, 40, 65) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    game.level_id = 0;
                }
                BeginShaderMode(game.Scanlines);
                break;
            case 5:
                EndShaderMode();
                DrawText("Back", 50, 50, 20, WHITE);
                if (GetCollision(MousePosition.x, MousePosition.y, 45, 80, 40, 65) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    game.level_id = 4;
                }
                DrawText("Controls Pc: Arrow Keys (Left / Right) , Space / Mouse (Shoot) ", 50, 125, 15, WHITE);
                DrawText("Controls Xbox - Controller: D-Pad (Left / Right) , Right Trigger (Shoot) ", 50, 200, 15, WHITE);
                DrawText("Creddits: Liquid ", 520, 450, 15, WHITE);
                BeginShaderMode(game.Scanlines);
                break;
        }
        UpdateAnimations();
        if (game.level_id == 1) {
            DrawText(TextFormat("Score %i", player.score), 515, 50, 20, RED);
            DrawText(TextFormat("Round %i", game.round), 50, 50, 20, GREEN);
        }
        if (IsKeyPressed(KEY_F)) {ToggleFullscreen();}
        EndShaderMode();
        EndDrawing();
    }
    CloseGame();
}