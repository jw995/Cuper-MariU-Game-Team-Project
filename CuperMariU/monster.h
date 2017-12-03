/*===============================================

File Name: monsters.h
Copyright (c) 2017 Han-Yu Lee  All rights reserved.
    
    DESCRIPTION:
    A class that handles all the monsters action for Cuper MariU.

    MONSTERS TYPE:
    There are two kinds of monsters.
    1. mushroom monsters - MonMush
    2. turtle monsters - Turtle
        turtle monsters would degenerate into a shell after being hit
        thus - Shell is defined to support this

    IMPLEMENTATION:
    A base class "Monsters" defined states and functions that all monsters share.
    Then 3 subclass inherit from it, which is "MonMush". "Turtle" and "Shell"


==================================================*/
#ifndef CMU_MARIO_MONSTERS
#define CMU_MARIO_MONSTERS

#include "SteadyObjects.h"

static int global_x;

class Monsters{
public:
    int alive_state;
    int facing_state;
    int moving_state;
    int second_floor_state;
    int third_floor_state;
    int x;
    int y;
    double speed_x;
    double speed_y;
    int timer;
    char *pattern;
    int dieflip_state;
    
    void CheckCollisionBlockBrickTubeMonsters(int object_x, int obj_wid);
    void Flip();
    void Move(int CameraX, int brick_3_break);
    int CheckGround(int CameraX, int brick_3_break);
    int CheckOnBlockHit(int object_x);
    void SetBitmap(char bmp[]);
    
};

class MonMush: public Monsters {
public:
    int DieCount;
    int dieflip_state;
    
    MonMush();
    void Draw(int CameraX);
    void Die();
    void DieFlip();
    void CheckCollisionMario(int mario_x, int mario_y, int hei, int mario_speed_y);
    void CheckHitByShell(int shell_x);
    
};

class Shell:public Monsters{
public:
    Shell();
    void Draw(int CameraX);
    void Die();
    void CheckCollisionMario(int mario_x, int mario_y, int wid, int hei);
    
};

class Turtle: public Monsters {
public:
    Shell shell;
    
    Turtle();
    void Draw(int CameraX);
    void Die();
    void CheckCollisionMario(int mario_x, int mario_y, int hei, int mario_speed_y);
    
};

class MonsterAll{
public:
    MonMush mush[16];
    Turtle turtle[1];
    
    void initialize();
    void timeFired(int CameraX,Tubes tube[], int brick_3_break, int block_hit_x, int mx, int my, int mspeedx, int mspeedy, int mwid, int mhei);
    void reDraw(int CameraX);
};


#endif

