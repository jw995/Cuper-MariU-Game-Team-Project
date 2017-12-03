#include <stdio.h>
#include <string.h>

#include "monster.h"
#include "SteadyObjects.h"
#include "fssimplewindow.h"
// make sure you unblock the following line
#include "Mario.h"

MonMush::MonMush(){
    moving_state = 1;
    alive_state = 1;
    facing_state = 0;
    second_floor_state = 0;
    third_floor_state = 0;
    DieCount = 4;
    speed_x = -4;
    speed_y = 0;
    timer = 0;
    dieflip_state = 0;
}

Shell::Shell(){
    moving_state = 0;
    alive_state = 0;
    facing_state = 1;
    second_floor_state = 0;
    third_floor_state = 0;
    speed_x = 0;
    speed_y = 0;
    timer = 0;
    
}

Turtle::Turtle(){
    moving_state = 1;
    alive_state = 1;
    facing_state = 0;
    second_floor_state = 0;
    third_floor_state = 0;
    speed_x = -3;
    speed_y = 0;
    timer =0;
    
}

void Monsters::SetBitmap(char bmp[]){
    const int n = strlen(bmp);
    pattern = new char[n + 1];
    if (nullptr != pattern){
        strcpy(pattern, bmp);
    }
}

void MonMush::Draw(int CameraX){
    //int interval = 1;
    global_x = CameraX;
    
    char pattern1[]=
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
        "....3333333322.."
        "...223333322222."
        "...222333222222."
        "....2223.22222.."
    };
    
    char pattern2[]=
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
        "..2233333333...."
        ".222223333322..."
        ".222222333222..."
        "..22222..222...."
    };
    
    if(alive_state ==1){
        if(timer%20 <= 9){
            SetBitmap(pattern1);
            timer ++;
        }
        else{
            SetBitmap(pattern2);
            timer ++;
        }
    }
    
    
    
    if(alive_state == 1 || (dieflip_state == 1 && DieCount > 1)){
        if(dieflip_state == 1){
            DieCount -= 1;
            if(y >= 480){
                x = -200;
                y = -200;
            }
        }
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
    else if (alive_state == 0 && DieCount > 1 && dieflip_state != 1){
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


void Turtle::Draw(int CameraX) {
    global_x = CameraX;
    char pattern1[]=
    {
        "...2............"
        "..222..........."
        "..2223.........."
        ".312233........."
        ".312233........."
        ".312233........."
        ".312233........."
        ".322233........."
        "3332333........."
        "3133333........."
        "3333331111111..."
        "333.3124144411.."
        "33..31244141441."
        "33.312444414221."
        ".3.312444141421."
        "...312141444141."
        "..3122414444411."
        "...124141444141."
        "...121444141441."
        "...124444414441."
        "...1224441414221"
        "...312221442221."
        "..3331122222133."
        ".33333.111113333"
        
    };
    char pattern2[]=
    {
        "....2..........."
        "...222.........."
        "..3222.........."
        "..31223........."
        ".331223........."
        ".331223........."
        ".332223........."
        "3133233........."
        "3333333........."
        "333..31111111..."
        "33...124144411.."
        "....3124414141.."
        "...312444414221."
        ".33312444141421."
        "..3312141444141."
        "...122414444411."
        "...124141444141."
        "...121444141441."
        "...124444414441."
        "...1224441414221"
        "....12221442211."
        "....31122222133."
        ".....3331111333."
        "......333..333.."
        
    };
    
    if(timer%20 <= 9){
        SetBitmap(pattern1);
        timer ++;
    }
    else{
        SetBitmap(pattern2);
        timer ++;
    }
    
    if(alive_state ==1){
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

void Shell::Draw(int CameraX) {
    global_x = CameraX;
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

void Monsters::Move(int CameraX, int brick_3_break) {
    if(moving_state == 1){
        if(y>600){
            alive_state = 0;
            x = -200;
            y = -200;
            speed_x = 0;
            speed_y = 0;
        }
        
        if(y < 100){
            if(speed_y != 0){
                third_floor_state = 1;
            }
        }
        
        if(third_floor_state == 1){
            if(y >= 264){
                y = 264;
                speed_y = 0;
                if(speed_x > 0){
                    speed_x = 4;
                }
                else{
                    speed_x = -4;
                }
                third_floor_state = 0;
                second_floor_state = 1;
            }
        }
        
        if(second_floor_state == 1){
            if(dieflip_state != 1){
                if(y>=456){ // change this to real floor height
                    y = 456;
                    speed_y = 0;
                    if(speed_x > 0){
                        speed_x = 4;
                    }
                    else{
                        speed_x = -4;
                    }
                    second_floor_state = 0;
                }
            }
        }
        
        if(CheckGround(CameraX, brick_3_break)==0){
            speed_y = 10;
            
            if(speed_x >0){
                speed_x = 4;
            }
            else{
                speed_x = -4;
            }
        }
        x += speed_x;
        y += speed_y;
        
    }
}


void Monsters::Flip(){
    if(facing_state ==1){
        facing_state = 0;
        speed_x = -4;
    }
    else{
        facing_state = 1;
        speed_x = 4;
        
    }
}

void Monsters::CheckCollisionBlockBrickTubeMonsters(int object_x, int obj_wid){
    if((x+48)>=object_x && (x+48) <= (object_x+obj_wid) && facing_state == 1) {
        Flip();
    }
    
    if(x<= (object_x+obj_wid) && x >= object_x && facing_state ==0){
        Flip();
    }
}

void MonMush::CheckHitByShell(int shell_x){
    if((x+48)>=shell_x && (x+48) <= (shell_x+48) && facing_state == 1) {
        DieFlip();
    }
    
    if(x<= (shell_x+48) && x >= shell_x && facing_state ==0){
        DieFlip();
    }
}

int Monsters::CheckGround(int cameraX, int brick_3_break){
    
    global_x = cameraX;
    /* third floor */
    if(y == 72){
        if((x-global_x) <= (3840 - global_x)){
            return 0;
        }
        else{
            return 1;
        }
    }
    
    /* second floor */
    if(brick_3_break == 0){
        if(y == 264){
            if((x-global_x) <= (3696 - global_x)){
                return 0;
            }
            else{
                return 1;
            }
        }
    }
    else{
        if(y == 264){
            if((x-global_x) <= (3744 - global_x)){
                return 0;
            }
            else{
                return 1;
            }
        }
    }
    
    /* ground level */
    if(y==456){  // change this to real ground height later
        if(((x-global_x) >= (69*48 -global_x)) && ((x-global_x)<=(70*48 -global_x))) {
            return 0;
        }
        if(((x-global_x) >= (87*48 -global_x)) && ((x-global_x)<=(88*48 -global_x))){ // the 84th block is a gap
            return 0;
        }
        if(((x-global_x) >= (153*48 -global_x)) && ((x-global_x)<=(154*48 -global_x))){ // the 151th block is a gap
            return 0;
        }
        else{
            return 1;
        }
    }
    
    return 1;
}


void MonMush::CheckCollisionMario(int mario_x, int mario_y, int hei, int mario_speed_y){
    if((mario_x+48) > x && (mario_x+48) < (x+48) && (mario_y + hei) >= y && (mario_y + hei) < (y + 48) && mario_speed_y >= 0){
        Die();
    }
    else if(mario_x <= (x+48) && mario_x >= x && (mario_y + hei) >= y && (mario_y + hei) < (y + 48) && mario_speed_y >= 0){
        Die();
    }
    else{
    }
}

void Turtle::CheckCollisionMario(int mario_x, int mario_y, int hei, int mario_speed_y){
    if((mario_x+48) > x && (mario_x+48) < (x+48) && (mario_y + hei) >= y && (mario_y + hei) < (y + 72) && mario_speed_y >= 0){
        Die();
    }
    else if(mario_x <= (x+48) && mario_x >= x && (mario_y + hei) >= y && (mario_y + hei) < (y + 72) && mario_speed_y >= 0){
        Die();
    }
    else{
    }
}

void Shell::CheckCollisionMario(int mario_x, int mario_y, int wid, int hei){
    if( (mario_y+hei) >= y && (mario_y+hei) <= (y+48) && (mario_x+48) >= x && (mario_x+48) <= (x+48)){
        moving_state = 1;
        speed_x = 16;
    }
    if(((mario_y+hei) >= y && (mario_y+hei) <= (y+48) && mario_x <= (x+48) && mario_x >= x )) {
        moving_state = 1;
        speed_x = -16;
    }
}

int Monsters::CheckOnBlockHit(int object_x){
    if(y == 264){
        if((x+48) >= object_x && (x+48) <= (object_x+48)){
            return 1;
        }
    }
    return 0;
}


void MonMush::Die(){
    alive_state = 0;
    speed_x = 0;
}

void MonMush::DieFlip(){
    alive_state = 0;
    dieflip_state = 1;
    DieCount = 20;
    char pattern3[]=
    {
        "..222223322222.."
        ".22222233222222."
        ".22222333322222."
        "..223333333322.."
        "....33333333...."
        ".11113333331111."
        "1111111111111111"
        "1111333113331111"
        "1111323113231111"
        ".11132222223111."
        ".11132111123111."
        "..122111111221.."
        "...1111111111..."
        "....11111111...."
        ".....111111....."
        "......1111......"
    };
    SetBitmap(pattern3);
    speed_y = 10;
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

void MonsterAll::initialize(){
    mush[0].x = 960;
    mush[0].y = 456;
    mush[1].x = 2112;
    mush[1].y = 456;
    mush[2].x = 2400;
    mush[2].y = 456;
    mush[3].x = 2496;
    mush[3].y = 456;
    
    mush[4].x = 3936;
    mush[4].y = 72;
    mush[5].x = 4032;
    mush[5].y = 72;
    
    mush[6].x = 4800;
    mush[6].y = 456;
    mush[7].x = 4896;
    mush[7].y = 456;
    
    mush[8].x = 5760;
    mush[8].y = 456;
    mush[9].x = 5856;
    mush[9].y = 456;
    
    mush[10].x = 5952;
    mush[10].y = 456;
    mush[11].x = 6048;
    mush[11].y = 456;
    
    mush[12].x = 6240;
    mush[12].y = 456;
    mush[13].x = 6336;
    mush[13].y = 456;
    
    mush[14].x = 7968;
    mush[14].y = 456;
    mush[15].x = 8064;
    mush[15].y = 456;
    
    
    turtle[0].x = 5184;
    turtle[0].y = 432;
}

void MonsterAll::reDraw(int CameraX){
    mush[0].Draw(CameraX);
    mush[1].Draw(CameraX);
    mush[2].Draw(CameraX);
    mush[3].Draw(CameraX);
    mush[4].Draw(CameraX);
    mush[5].Draw(CameraX);
    mush[6].Draw(CameraX);
    mush[7].Draw(CameraX);
    mush[8].Draw(CameraX);
    mush[9].Draw(CameraX);
    mush[10].Draw(CameraX);
    mush[11].Draw(CameraX);
    mush[12].Draw(CameraX);
    mush[13].Draw(CameraX);
    mush[14].Draw(CameraX);
    mush[15].Draw(CameraX);
    
    turtle[0].Draw(CameraX);
    turtle[0].shell.Draw(CameraX);
    
}

void CheckCollisionMonster(int monNum, MonMush mush[], Shell shell){
    int i;
    for(i=0;i<16;i++){
        if(i==monNum){
        }
        else{
            mush[monNum].CheckCollisionBlockBrickTubeMonsters(mush[i].x,48);
        }
    }
}

void CheckCollisionTube(MonMush &mush, Tubes tube[]){
    int i;
    int Tubenum=8;
    for(i=0; i< Tubenum; i++){
        mush.CheckCollisionBlockBrickTubeMonsters(tube[i].x,96);
    }
}

void MonsterAll::timeFired(int CameraX,Tubes tube[], int brick_3_break, int block_hit_x, int mx, int my, int mspeedx, int mspeedy, int mwid, int mhei){
    /* mario should be passed in here, and the following should be changed */
    
    global_x = CameraX;
    
    int mario_x = mx;
    int mario_y = my;
    int mario_hei = mwid;
    int mario_wid = mhei;
    int mario_speed_y = mspeedy;
  //  int mario_speed_x = mspeedx;
    /* */
    
    if(global_x > 960-800){
        mush[0].Move(CameraX, brick_3_break);
        CheckCollisionMonster(0, mush, turtle[0].shell);
        CheckCollisionTube(mush[0], tube);
        mush[0].CheckCollisionMario(mario_x, mario_y, mario_hei, mario_speed_y);
        mush[0].CheckHitByShell(turtle[0].shell.x);
    }
    if(global_x > 2112-800){
        mush[1].Move(CameraX, brick_3_break);
        CheckCollisionMonster(1, mush, turtle[0].shell);
        CheckCollisionTube(mush[1], tube);
        mush[1].CheckCollisionMario(mario_x, mario_y, mario_hei, mario_speed_y);
        mush[1].CheckHitByShell(turtle[0].shell.x);
    }
    if(global_x > 2400-800){
        mush[2].Move(CameraX, brick_3_break);
        CheckCollisionMonster(2, mush, turtle[0].shell);
        CheckCollisionTube(mush[2], tube);
        mush[2].CheckCollisionMario(mario_x, mario_y, mario_hei, mario_speed_y);
        mush[2].CheckHitByShell(turtle[0].shell.x);
    }
    if(global_x > 2496-800){
        mush[3].Move(CameraX, brick_3_break);
        CheckCollisionMonster(3, mush, turtle[0].shell);
        CheckCollisionTube(mush[3], tube);
        mush[3].CheckCollisionMario(mario_x, mario_y, mario_hei, mario_speed_y);
        mush[3].CheckHitByShell(turtle[0].shell.x);
    }
    if(global_x > 3936-800){
        mush[4].Move(CameraX, brick_3_break);
        CheckCollisionMonster(4, mush, turtle[0].shell);
        CheckCollisionTube(mush[4], tube);
        mush[4].CheckCollisionMario(mario_x, mario_y, mario_hei, mario_speed_y);
        if(mush[4].CheckOnBlockHit(block_hit_x) == 1) {
            mush[4].DieFlip();
        }
        mush[4].CheckHitByShell(turtle[0].shell.x);
    }
    if(global_x > 4032-800){
        mush[5].Move(CameraX, brick_3_break);
        CheckCollisionMonster(5, mush, turtle[0].shell);
        CheckCollisionTube(mush[5], tube);
        mush[5].CheckCollisionMario(mario_x, mario_y, mario_hei, mario_speed_y);
        if(mush[5].CheckOnBlockHit(block_hit_x) == 1) {
            mush[5].DieFlip();
        }
        mush[5].CheckHitByShell(turtle[0].shell.x);
    }
    if(global_x > 4800-800){
        mush[6].Move(CameraX, brick_3_break);
        CheckCollisionMonster(6, mush, turtle[0].shell);
        CheckCollisionTube(mush[6], tube);
        mush[6].CheckCollisionMario(mario_x, mario_y, mario_hei, mario_speed_y);
        mush[6].CheckHitByShell(turtle[0].shell.x);
    }
    if(global_x > 4896-800){
        mush[7].Move(CameraX, brick_3_break);
        CheckCollisionMonster(7, mush, turtle[0].shell);
        CheckCollisionTube(mush[7], tube);
        mush[7].CheckCollisionMario(mario_x, mario_y, mario_hei, mario_speed_y);
        mush[7].CheckHitByShell(turtle[0].shell.x);
    }
    if(global_x > 5760-800){
        mush[8].Move(CameraX, brick_3_break);
        CheckCollisionMonster(8, mush, turtle[0].shell);
        CheckCollisionTube(mush[8], tube);
        mush[8].CheckCollisionMario(mario_x, mario_y, mario_hei, mario_speed_y);
        mush[8].CheckHitByShell(turtle[0].shell.x);
    }
    if(global_x > 5856-800){
        mush[9].Move(CameraX, brick_3_break);
        CheckCollisionMonster(9, mush, turtle[0].shell);
        CheckCollisionTube(mush[9], tube);
        mush[9].CheckCollisionMario(mario_x, mario_y, mario_hei, mario_speed_y);
        mush[9].CheckHitByShell(turtle[0].shell.x);
    }
    if(global_x > 5952-800){
        mush[10].Move(CameraX, brick_3_break);
        CheckCollisionMonster(10, mush, turtle[0].shell);
        CheckCollisionTube(mush[10], tube);
        mush[10].CheckCollisionMario(mario_x, mario_y, mario_hei, mario_speed_y);
        mush[10].CheckHitByShell(turtle[0].shell.x);
    }
    if(global_x > 6048-800){
        mush[11].Move(CameraX, brick_3_break);
        CheckCollisionMonster(11, mush, turtle[0].shell);
        CheckCollisionTube(mush[11], tube);
        mush[11].CheckCollisionMario(mario_x, mario_y, mario_hei, mario_speed_y);
        mush[11].CheckHitByShell(turtle[0].shell.x);
    }
    if(global_x > 6240-800){
        mush[12].Move(CameraX, brick_3_break);
        CheckCollisionMonster(12, mush, turtle[0].shell);
        CheckCollisionTube(mush[12], tube);
        mush[12].CheckCollisionMario(mario_x, mario_y, mario_hei, mario_speed_y);
        mush[12].CheckHitByShell(turtle[0].shell.x);
    }
    if(global_x > 6336-800){
        mush[13].Move(CameraX, brick_3_break);
        CheckCollisionMonster(13, mush, turtle[0].shell);
        CheckCollisionTube(mush[13], tube);
        mush[13].CheckCollisionMario(mario_x, mario_y, mario_hei, mario_speed_y);
        mush[13].CheckHitByShell(turtle[0].shell.x);
    }
    if(global_x > 7968-800){
        mush[14].Move(CameraX, brick_3_break);
        CheckCollisionMonster(14, mush, turtle[0].shell);
        CheckCollisionTube(mush[14], tube);
        mush[14].CheckCollisionMario(mario_x, mario_y, mario_hei, mario_speed_y);
        mush[14].CheckHitByShell(turtle[0].shell.x);
    }
    if(global_x > 8064-800){
        mush[15].Move(CameraX, brick_3_break);
        CheckCollisionMonster(15, mush, turtle[0].shell);
        CheckCollisionTube(mush[15], tube);
        mush[15].CheckCollisionMario(mario_x, mario_y, mario_hei, mario_speed_y);
        mush[15].CheckHitByShell(turtle[0].shell.x);
    }
    
    if(global_x > 5184-800){
        turtle[0].Move(CameraX, brick_3_break);
        for(int i = 0; i<16; i++){
            turtle[0].CheckCollisionBlockBrickTubeMonsters(mush[i].x,48);
        }
        turtle[0].shell.Move(CameraX, brick_3_break);
        turtle[0].CheckCollisionMario(mario_x, mario_y, mario_hei, mario_speed_y);
        if(turtle[0].shell.alive_state == 1){
            turtle[0].shell.timer += 1;
        }
        if(turtle[0].shell.timer >= 5){
            turtle[0].shell.CheckCollisionMario(mario_x, mario_y, mario_wid, mario_hei);
        }
    }
    
}

