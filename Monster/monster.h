#ifndef CMU_MARIO_MONSTERS
#define CMU_MARIO_MONSTERS

extern int global_x;


class Monsters{
public:
    int alive_state;
    int facing_state;
    int moving_state;
    int second_floor_state;
    int x;
    int y;
    double speed_x;
    double speed_y;

    void CheckCollisionBlockBrickTubeMonsters(int object_x);
    void Flip();
    void Move();
    int CheckGround();
    void CheckOnBlockHit(int object_x);
    
};

class MonMush: public Monsters {
public:
    int DieCount;
    
    MonMush();
    void Draw();
    void Die();
    void CheckCollisionMario(int mario_x, int mario_y, int hei, int mario_speed_y);

};

class Shell:public Monsters{
public:
    Shell();
    void Draw();
    void Die();
    void CheckCollisionMario(int mario_x, int mario_y, int wid, int mario_speed_x);

};

class Turtle: public Monsters {
public:
    Shell shell;
    
    Turtle();
    void Draw();
    void Die();
    void CheckCollisionMario(int mario_x, int mario_y, int hei, int mario_speed_y);

};



#endif
