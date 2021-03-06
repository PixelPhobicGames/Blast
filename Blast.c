// I hope you can somehow deciper this horrible code 
// Retro - GameJam March 4th - 12th 2021


// Liquid ( Ewan Cole )

#include <raylib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "game.h"

int main(void){
    InitWindow(640,480,"BLAST");
    InitAudioDevice();
    SetTargetFPS(60);
    GameInit();
    while (!WindowShouldClose())
    {
        UpdateMusic();   
        BeginDrawing();
        BeginShaderMode(game.Scanlines);
        DrawTexture(game.map_0_bg,game.map_x,game.map_y,WHITE);
        UpdateSpaceBackground();
        ClearBackground(BLACK);
            switch (game.level_id)
            {
                case 0:
                    PlayMusicStream(game.titlemusic);
                    DrawTexture(game.map_0,0,0,WHITE);
                    if (IsKeyPressed(KEY_SPACE)){
                        StopMusicStream(game.titlemusic);
                        game.level_id = 3;
                    }
                
                    if (IsKeyDown(KEY_Q)){
                        game.debug = true;
                    }
                    DrawText("RetroGame Jam 2021", 400,440,20,WHITE);
                    if(game.animation_counter <= 50 && game.animation_counter >= 0){
                        DrawText("Press Space", 240,220,20,WHITE);
                    }
                    break;
            
                case 1:
                    DrawPlayer();
                    DrawEnemys();
                    UpdateProjectiles();
                    
                    break;
                case 2:
                    if(game.animation_counter <= 50 && game.animation_counter >= 0){
                        DrawText("Game   Over", 240,220,20,WHITE);
                    }
                    DrawText("Press Space", 235,260,20,WHITE);
                    if (IsKeyPressed(KEY_SPACE)){
                        GameInit();
                    }
                    break;
                case 3:
                    StopMusicStream(player.Shoot);
                    StopMusicStream(enemytextures.boom);
                    if(game.text_y <= 200){
                        game.text_y ++;
                    }

                    DrawText(TextFormat("  Round %i" , game.round), 195,game.text_y,40,GREEN);
                    DrawText("Press Space", 235,260,20,WHITE);
                    if (IsKeyPressed(KEY_SPACE)){
                        //GameInit();
                        game.text_y = 0;
                        game.level_id = 1;

                    }
                    break;


            }
        if (game.debug){
            DrawFPS(50,50);
            DrawText("Blast: Debug is Enabled",50,75,20,GREEN);
        }
        UpdateAnimations();
        EndShaderMode();
        if(game.level_id == 1){
            DrawText(TextFormat("Score %i" , player.score), 515,50,20,RED);
            DrawText(TextFormat("Round %i" , game.round), 50,50,20,GREEN);
        }
        if (IsKeyPressed(KEY_F)){
            ToggleFullscreen();
        }
        EndDrawing();
    }
    CloseGame();
}
