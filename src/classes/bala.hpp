#include <raylib.h>
#include "raymath.h"
#include "rcamera.h"
#include <iostream>
using namespace std;

class Bala{
    public:
        Bala(Camera3D ps, float speed, Color c, bool troca);
        Camera3D cam;
        Vector3 ps = { 0 };
        Color c = YELLOW;
        bool live = true;
        double time = GetTime();
        double timee = 3;
        float speed = 0.0f;
        bool troca = false;

        void Update();
        void Draw();
    private:
};

Bala::Bala(Camera3D ps, float speed, Color c=YELLOW, bool troca = false){
    this->cam = ps;
    this->troca = troca;

    Vector3 f = GetCameraUp(&ps);
    f = Vector3Scale(f,-1.0f);

    this->ps = Vector3Add(ps.position,f);
    this->speed = speed;
    this->c = c;
}

void Bala::Update(){
    if(this->troca){
        Vector3 hsv = ColorToHSV(this->c);
        hsv.x+=(hsv.x<360)?1:-hsv.x;
        this->c = ColorFromHSV(hsv.x,hsv.y,hsv.z);
    }
    
    if(GetTime() - this->time<this->timee){
        Vector3 f = GetCameraForward(&this->cam);
        f = Vector3Scale(f,this->speed);

        this->ps = Vector3Add(this->ps,f);
    }
}

void Bala::Draw(){
    /*if(GetTime() - this->time>this->timee)
        live = false;*/
    DrawCube(ps, 0.5f, 0.5f, 0.5f, this->c);
}
