#include <stdio.h>
#include <stdlib.h>
#include "fssimplewindow.h"
#include "monster.h"
#include "SteadyObjects.h"

int global_x = 0;

int main(){
    FsOpenWindow(500,500,800,600,1);

    int terminate = 0;
    int count = 0;
    
    
    int x = global_x+300;
    int y = 200;
    
    int my = 100;
    int mx = global_x+520;
    double mx1 = global_x+300;
    int my1 = 220;
    
    MonMush mush[3];
    mush[0].x = global_x+x+200;
    mush[0].y = y+24;
    mush[1].x = global_x+x-180;
    mush[1].y = y-128;
    mush[2].x = global_x+x-132;
    mush[2].y = y-128;

    
    Turtle turtle[3];
    
    turtle[1].x = global_x+x+48;
    turtle[1].y = y;
    turtle[0].x = global_x+700;
    turtle[0].y = y;
    turtle[2].x = global_x+x+200;
    turtle[2].y = y;
    
    Bricks brick[4];
    
    
    while(terminate==0){
        FsPollDevice();
        int key= FsInkey();
        
        switch(key){
            case FSKEY_ESC:
                terminate=1;
                break;
            case FSKEY_LEFT:
                global_x -= 5;
                break;
            case FSKEY_RIGHT:
                global_x += 5;
                break;
            case FSKEY_UP:
                break;
            case FSKEY_DOWN:
                break;
            case FSKEY_SPACE:
                break;
        }
        

        glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
        
        
        /* verticle dropping box */
        glBegin(GL_QUADS);
        glColor3ub(0,0,0);
        glVertex2i(mx-global_x,my);
        glVertex2i(mx-global_x,my+20);
        glVertex2i(mx+50-global_x,my+20);
        glVertex2i(mx+50-global_x,my);
        my += 2;
        glEnd();
        
        
        /* horizontal moving box */
        glBegin(GL_QUADS);
        glColor3ub(0,0,0);
        glVertex2i(mx1-global_x,my1);
        glVertex2i(mx1-global_x,my1+20);
        glVertex2i(mx1+50-global_x,my1+20);
        glVertex2i(mx1+50-global_x,my1);
        if(mx1 <= 470){
        mx1 += 1;
        }
        glEnd();
        
        
        mush[0].Move();
        mush[0].Draw();
        mush[2].Move();
        turtle[2].shell.Move();
        

        mush[0].CheckCollisionBlockBrickTubeMonsters(turtle[1].x);
        mush[0].CheckCollisionBlockBrickTubeMonsters(turtle[0].x);
        mush[0].CheckCollisionBlockBrickTubeMonsters(mush[2].x);
        mush[2].CheckCollisionBlockBrickTubeMonsters(mush[0].x);

        /* */
        turtle[0].CheckCollisionBlockBrickTubeMonsters(mush[0].x);
        /* */
        mush[0].CheckCollisionMario(mx, my, 20, 5);
        
        if(count > 100){
            mush[1].CheckOnBlockHit(global_x+x-180);
        }
        
        turtle[2].CheckCollisionMario(mx, my, 20, 5);
        turtle[2].shell.CheckCollisionMario(mx1, my1, 50, 1);
        
        if(global_x > 20){
        turtle[1].Draw();
        }
        turtle[0].Draw();
        /* */
        turtle[0].Move();
        /* */
        turtle[2].Draw();
        turtle[2].shell.Draw();
        
        brick[0].x = 548-global_x;
        brick[0].y = 272;
        brick[1].x = 644-global_x;
        brick[1].y = 272;
        brick[2].x = 120-global_x;
        brick[2].y = 120;
        brick[3].x = 168-global_x;
        brick[3].y = 120;
        brick[0].Draw();
        brick[1].Draw();
        brick[2].Draw();
        brick[3].Draw();
        
        mush[1].Draw();
        mush[2].Draw();


        
        FsSwapBuffers();
        count ++;
        FsSleep(10);
    }
    
    return 0;
    
}

