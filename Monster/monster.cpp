#include "monster.h"
#include "fssimplewindow.h"
#include <stdio.h>

MonMush::MonMush(){
    moving_state = 1;
    alive_state = 1;
    facing_state = 1;
    second_floor_state = 0;
    DieCount = 20;
    speed_x = 2;
    speed_y = 0;
}

Shell::Shell(){
    moving_state = 0;
    alive_state = 0;
    facing_state = 1;
    second_floor_state = 0;
    speed_x = 4;
    speed_y = 0;
    
}

Turtle::Turtle(){
    moving_state = 1;
    alive_state = 1;
    facing_state = 0;
    second_floor_state = 0;
    speed_x = -3;
    speed_y = 0;
    
}

void MonMush::Draw(){
    char pattern[]=
    {
        "......1111......"
        ".....111111....."
        "....11111111...."
        "...1111111111..."
        "..122111111221.."
        ".11132111123111."
        ".11132222223111."
        "1111323113231111"
        "1111333113331111"
        "1111111111111111"
        ".11113333331111."
        "....33333333...."
        "..223333333322.."
        ".22222333322222."
        ".22222233222222."
        "..222223322222.."
    };
    
    if(alive_state == 1){
        
        glBegin(GL_QUADS);
        
        for (int i=0; i<16; i++) {
            for (int j=0; j<16; j++) {
                
                if (pattern[j*16+i] == '1'){
                    glColor3ub(135, 60, 26);
                    glVertex2i(x+i*3-global_x, y+j*3);
                    glVertex2i(x+(i+1)*3-global_x, y+j*3);
                    glVertex2i(x+(i+1)*3-global_x, y+(j+1)*3);
                    glVertex2i(x+i*3-global_x, y+(j+1)*3);
                }
                if (pattern[j*16+i] == '2'){
                    glColor3ub(0, 0, 0);
                    glVertex2i(x+i*3-global_x, y+j*3);
                    glVertex2i(x+(i+1)*3-global_x, y+j*3);
                    glVertex2i(x+(i+1)*3-global_x, y+(j+1)*3);
                    glVertex2i(x+i*3-global_x, y+(j+1)*3);
                }
                if (pattern[j*16+i] == '3'){
                    glColor3ub(242, 205, 161);
                    glVertex2i(x+i*3-global_x, y+j*3);
                    glVertex2i(x+(i+1)*3-global_x, y+j*3);
                    glVertex2i(x+(i+1)*3-global_x, y+(j+1)*3);
                    glVertex2i(x+i*3-global_x, y+(j+1)*3);
                }
            }
        }
        glEnd();
    }
    else if (alive_state == 0 && DieCount > 1){
        DieCount -= 1;
        glBegin(GL_QUADS);
        
        for (int i=0; i<16; i++) {
            for (int j=0; j<16; j++) {
                
                if (pattern[j*16+i] == '1'){
                    glColor3ub(135, 60, 26);
                    glVertex2i(x+i*3-global_x, 16+y+(j*2));
                    glVertex2i(x+(i+1)*3-global_x, 16+y+(j*2));
                    glVertex2i(x+(i+1)*3-global_x, 16+y+(j+1)*2);
                    glVertex2i(x+i*3-global_x, 16+y+(j+1)*2);
                }
                if (pattern[j*16+i] == '2'){
                    glColor3ub(0, 0, 0);
                    glVertex2i(x+i*3-global_x, 16+y+(j*2));
                    glVertex2i(x+(i+1)*3-global_x, 16+y+(j*2));
                    glVertex2i(x+(i+1)*3-global_x, 16+y+(j+1)*2);
                    glVertex2i(x+i*3-global_x, 16+y+(j+1)*2);
                }
                if (pattern[j*16+i] == '3'){
                    glColor3ub(242, 205, 161);
                    glVertex2i(x+i*3-global_x, 16+y+(j*2));
                    glVertex2i(x+(i+1)*3-global_x, 16+y+(j*2));
                    glVertex2i(x+(i+1)*3-global_x, 16+y+(j+1)*2);
                    glVertex2i(x+i*3-global_x, 16+y+(j+1)*2);
                }
            }
        }
        glEnd();
    }
    else{
        x = -100;
        y = -100;
        speed_x = 0;
        speed_y = 0;
    }
}


void Turtle::Draw() {
    if(alive_state ==1){
        char pattern[]=
        {
            "...11..........."
            "..1221.........."
            "..1221.........."
            ".122211........."
            ".1122131........"
            ".11221331......."
            ".11223331......."
            ".12223331......."
            "131233331......."
            "1333333131111..."
            "13311331144441.."
            "131.13121414141."
            "11..13121441441."
            "...1331214141441"
            ".113312141444141"
            ".133312114444411"
            "..11312141444141"
            "...1312144141441"
            "....112144414441"
            ".....1221414141."
            ".....11222222221"
            "....13111111111."
            "...133331.133331"
            "...111111.111111"
            
        };
        
        if(facing_state == 0){
            glBegin(GL_QUADS);
            for (int i=0; i<16; i++) {
                for (int j=0; j<24; j++) {
                    
                    if (pattern[j*16+i] == '1'){
                        glColor3ub(0, 0, 0);
                        glVertex2i(x+i*3-global_x, y+j*3);
                        glVertex2i(x+(i+1)*3-global_x, y+j*3);
                        glVertex2i(x+(i+1)*3-global_x, y+(j+1)*3);
                        glVertex2i(x+i*3-global_x, y+(j+1)*3);
                    }
                    if (pattern[j*16+i] == '2'){
                        glColor3ub(255, 255, 255);
                        glVertex2i(x+i*3-global_x, y+j*3);
                        glVertex2i(x+(i+1)*3-global_x, y+j*3);
                        glVertex2i(x+(i+1)*3-global_x, y+(j+1)*3);
                        glVertex2i(x+i*3-global_x, y+(j+1)*3);
                    }
                    if (pattern[j*16+i] == '3'){
                        glColor3ub(251, 231, 95);
                        glVertex2i(x+i*3-global_x, y+j*3);
                        glVertex2i(x+(i+1)*3-global_x, y+j*3);
                        glVertex2i(x+(i+1)*3-global_x, y+(j+1)*3);
                        glVertex2i(x+i*3-global_x, y+(j+1)*3);
                    }
                    if (pattern[j*16+i] == '4'){
                        glColor3ub(141, 204, 112);
                        glVertex2i(x+i*3-global_x, y+j*3);
                        glVertex2i(x+(i+1)*3-global_x, y+j*3);
                        glVertex2i(x+(i+1)*3-global_x, y+(j+1)*3);
                        glVertex2i(x+i*3-global_x, y+(j+1)*3);
                    }
                }
            }
            glEnd();
        }
        else{
            glBegin(GL_QUADS);
            for (int i=0; i<16; i++) {
                for (int j=0; j<24; j++) {
                    
                    if (pattern[j*16+i] == '1'){
                        glColor3ub(0, 0, 0);
                        glVertex2i(-(x+i*3)+2*(x+24)-global_x, y+j*3);
                        glVertex2i(-(x+(i+1)*3)+2*(x+24)-global_x, y+j*3);
                        glVertex2i(-(x+(i+1)*3)+2*(x+24)-global_x, y+(j+1)*3);
                        glVertex2i(-(x+i*3)+2*(x+24)-global_x, y+(j+1)*3);
                    }
                    if (pattern[j*16+i] == '2'){
                        glColor3ub(255, 255, 255);
                        glVertex2i(-(x+i*3)+2*(x+24)-global_x, y+j*3);
                        glVertex2i(-(x+(i+1)*3)+2*(x+24)-global_x, y+j*3);
                        glVertex2i(-(x+(i+1)*3)+2*(x+24)-global_x, y+(j+1)*3);
                        glVertex2i(-(x+i*3)+2*(x+24)-global_x, y+(j+1)*3);
                    }
                    if (pattern[j*16+i] == '3'){
                        glColor3ub(251, 231, 95);
                        glVertex2i(-(x+i*3)+2*(x+24)-global_x, y+j*3);
                        glVertex2i(-(x+(i+1)*3)+2*(x+24)-global_x, y+j*3);
                        glVertex2i(-(x+(i+1)*3)+2*(x+24)-global_x, y+(j+1)*3);
                        glVertex2i(-(x+i*3)+2*(x+24)-global_x, y+(j+1)*3);
                    }
                    if (pattern[j*16+i] == '4'){
                        glColor3ub(141, 204, 112);
                        glVertex2i(-(x+i*3)+2*(x+24)-global_x, y+j*3);
                        glVertex2i(-(x+(i+1)*3)+2*(x+24)-global_x, y+j*3);
                        glVertex2i(-(x+(i+1)*3)+2*(x+24)-global_x, y+(j+1)*3);
                        glVertex2i(-(x+i*3)+2*(x+24)-global_x, y+(j+1)*3);
                    }
                }
            }
            glEnd();
        }
    }
}

void Shell::Draw() {
    if(alive_state==1){
        char pattern[]=
        {
            ".....111111....."
            "....11444411...."
            "...1441111441..."
            "..144144441441.."
            "..141444444141.."
            ".14144444444141."
            ".11414444441411."
            "1144414444144411"
            "1444441111444441"
            "1114414444144111"
            "2211144444411122"
            "1222144444412221"
            ".11221111112211."
            "...1222222221..."
            "....11222211...."
            "......1111......"
            
        };
        glBegin(GL_QUADS);
        for (int i=0; i<16; i++) {
            for (int j=0; j<16; j++) {
                
                if (pattern[j*16+i] == '1'){
                    glColor3ub(0, 0, 0);
                    glVertex2i(x+i*3-global_x, y+j*3);
                    glVertex2i(x+(i+1)*3-global_x, y+j*3);
                    glVertex2i(x+(i+1)*3-global_x, y+(j+1)*3);
                    glVertex2i(x+i*3-global_x, y+(j+1)*3);
                }
                if (pattern[j*16+i] == '2'){
                    glColor3ub(255, 255, 255);
                    glVertex2i(x+i*3-global_x, y+j*3);
                    glVertex2i(x+(i+1)*3-global_x, y+j*3);
                    glVertex2i(x+(i+1)*3-global_x, y+(j+1)*3);
                    glVertex2i(x+i*3-global_x, y+(j+1)*3);
                }
                
                if (pattern[j*16+i] == '4'){
                    glColor3ub(141, 204, 112);
                    glVertex2i(x+i*3-global_x, y+j*3);
                    glVertex2i(x+(i+1)*3-global_x, y+j*3);
                    glVertex2i(x+(i+1)*3-global_x, y+(j+1)*3);
                    glVertex2i(x+i*3-global_x, y+(j+1)*3);
                }
            }
        }
        glEnd();
    }
    
}

void Monsters::Move() {
    if(moving_state == 1){
        if(y>600){
            alive_state = 0;
            x = -200;
            y = -200;
            speed_x = 0;
            speed_y = 0;
        }
        
        if(y < 120){ // change this to real block height
            if(speed_y != 0){
                second_floor_state = 1;
            }
        }
        
        if(second_floor_state == 1){
            if(y>=224){ // change this to real floor height
                y = 224;
                speed_y = 0;
                if(speed_x > 0){
                    speed_x = 2;
                }
                else{
                    speed_x = -2;
                }
                second_floor_state = 0;
            }
        }
        
        if(CheckGround()==0){
            speed_y = 5;

            if(speed_x >0){
                speed_x = 0.2;
            }
            else{
                speed_x = -0.2;
            }
        }
        x += speed_x;
        y += speed_y;
        
    }
}


void Monsters::Flip(){
    if(facing_state ==1){
        facing_state = 0;
        speed_x *= -1;
    }
    else{
        facing_state = 1;
        speed_x *= -1;
    }
}

void Monsters::CheckCollisionBlockBrickTubeMonsters(int object_x){
    if((x+48)>=object_x && (x+48) <= (object_x+48) && facing_state == 1) {
        Flip();
    }
    if((x<= (object_x+48) && x >= object_x && facing_state == 0)) {
        Flip();
    }
}

int Monsters::CheckGround(){
    
    /* I need all the brick boundaries */
    if(y==72){ // change this to real block height later
        if((x+48-global_x) == (168+2*48 - global_x)){ // gap is happening at 2 units to the right of last block
            return 0;
        }
        else{
            return 1;
        }
    }
    
    /* I need all the gaps positions */
    if(y==224){  // change this to real ground height later
        if((x+48-global_x) == (644 - global_x)){
            return 0;
        }
        else{
            return 1;
        }
    }
    return 1;
}


void MonMush::CheckCollisionMario(int mario_x, int mario_y, int hei, int mario_speed_y){
    if((mario_x+48) >= x && (mario_x+48) <= (x+48) && (mario_y + hei) >= y && (mario_y + hei) <= (y + 48) && mario_speed_y >= 0){
        Die();
    }
    else if(mario_x <= (x+48) && mario_x >= x && (mario_y + hei) >= y && (mario_y + hei) <= (y + 48) && mario_speed_y >= 0){
        Die();
    }
    else{
    }
}

void Turtle::CheckCollisionMario(int mario_x, int mario_y, int hei, int mario_speed_y){
    if((mario_x+48) >= x && (mario_x+48) <= (x+48) && (mario_y + hei) >= y && (mario_y + hei) <= (y + 72) && mario_speed_y >= 0){
        Die();
    }
    else if(mario_x <= (x+48) && mario_x >= x && (mario_y + hei) >= y && (mario_y + hei) <= (y + 72) && mario_speed_y >= 0){
        Die();
    }
    else{
    }
}

void Shell::CheckCollisionMario(int mario_x, int mario_y, int wid, int mario_speed_x){
    if((mario_x+48) >= x && (mario_x+48) <= (x+48) && mario_speed_x > 0) {
        moving_state = 1;
    }
    if((mario_x <= (x+48) && mario_x >= x && mario_speed_x < 0)) {
        moving_state = 1;
    }
}

void Monsters::CheckOnBlockHit(int object_x){
    if((x+48) >= object_x && (x+48) <= (object_x+48)){
        alive_state = 0;
    }
}


void MonMush::Die(){
    alive_state = 0;
    speed_x = 0;
}

void Turtle::Die(){
    alive_state = 0;
    shell.x = x;
    shell.y = y+24;
    shell.alive_state = 1;
    x = -100;
    y = -100;
    speed_x = 0;
    speed_y = 0;
}

void Shell::Die(){
    alive_state = 0;
    x = -100;
    y = -100;
    speed_x = 0;
    speed_y = 0;
}

