#include <iostream>
#include <raylib.h>
#include <vector>
#include "classes/rcamera.h"
#include "classes/bala.hpp"

using namespace std;

int main() {
    const int windowWidth = 1000;
    const int windowHeight = 800;

    
    int x = 0;
    int y = 0;
    float speed = 0.1f;
    float camera_sens = 0.1f;
    bool troca = false;

    vector<Bala> balas;

    Camera camera = { 0 };
    camera.position = (Vector3){ 0.0f, 2.0f, 4.0f };
    camera.target = (Vector3){ 0.0f, 2.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Vector3 bala = { 0 };

    Color c = { 0 };

    InitWindow(windowWidth,windowHeight,"3D");
    DisableCursor();
    SetTargetFPS(70);

    double hue = 0;
    double addToHue = 1;

    while(WindowShouldClose() == false){
        hue = (hue>=360?0:hue);

        if(IsKeyDown(KEY_LEFT_SHIFT)){
            speed = 0.6f;
        }else if(IsKeyUp(KEY_LEFT_SHIFT)){
            speed = 0.3f;
        }

        if(IsKeyPressed(KEY_ONE)){
            troca = (troca?false:true);
        }else if(IsKeyPressed(KEY_TWO)){
            addToHue = 1;
        }else if(IsKeyPressed(KEY_THREE)){
            if(addToHue >= 1.2){
                addToHue += 0.1;
            }else{
                addToHue = 1.2;
            }
        }

        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
            hue+=addToHue;
            c = ColorFromHSV((int)hue,1,1);

            balas.push_back(Bala(camera,0.6f,c,troca));
            
        }
        
        UpdateCameraPro(&camera,
            (Vector3){ 
                IsKeyDown(KEY_W) * speed - IsKeyDown(KEY_S) * speed,
                IsKeyDown(KEY_D) * speed - IsKeyDown(KEY_A) * speed,
                IsKeyDown(KEY_SPACE) * speed - (IsKeyDown(KEY_RIGHT_SHIFT) || IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) * speed
             },
             (Vector3){
                GetMouseDelta().x * camera_sens,
                GetMouseDelta().y * camera_sens,
                0.0f
             },
             0.0f
        );

        if (!balas.empty()){
            for(int i=0;i<balas.size();i++){
                balas[i].Update();
            }
            for(int i=0;i<balas.size();i++){
                if(!balas[i].live)
                    balas.erase(balas.begin());
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);

            BeginMode3D(camera);

                DrawPlane((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector2){ 100.0f, 100.0f }, WHITE);
                DrawCube((Vector3){ 0.0f, 5.0f, -40.0f }, 10.0f, 1.0f, 32.0f, BLUE);
                
                DrawCube(bala, 0.1f, 0.1f, 0.1f, BLUE);

                if(!balas.empty()){
                    for(int i=0;i<balas.size();i++){
                        balas[i].Draw();
                    }
                }

            EndMode3D();
            DrawLineEx({windowWidth/2,(windowHeight/2)+20},{windowWidth/2,(windowHeight/2)-20},2.0f,WHITE);
            DrawLineEx({(windowWidth/2)-20,windowHeight/2},{(windowWidth/2)+20,windowHeight/2},2.0f,WHITE);
            DrawText(TextFormat("FPS:%i",GetFPS()),0,0,20,WHITE);
            DrawText(TextFormat("Tipo de cor:%s",((troca)?"Muda cor":"Apenas uma Cor")),0,30,20,WHITE);
            DrawText(TextFormat("Velocidade de aumento do HUE:%f",addToHue),0,60,20,WHITE);
            DrawText(TextFormat("Blocos:%i",balas.size()),0,90,20,WHITE);


        EndDrawing();
    }

    balas.clear();

    CloseWindow();

    return 0;
}