/*
Mario class
by Calvin Qiao, Ke Han
This class provides attributes and methods of Mario

Main attributes
1. Mario state "normal", "super"
2. Position, speed, facing
3. Collision state, Interaction state with mosters
4. Jumping state, falling state, landing state, jumping height, jumping timer

Main methods
1. Process key inputs in order to let users move Mario
2. Draw Mario according to Mario's current state
3. Check collisions with bricks, tubes, monsters, etc and respond correspondingly
*/

#ifndef MARIO_H_IS_INCLUDED
#define MARIO_H_IS_INCLUDED
#include "SteadyObjects.h"
#include "monster.h"


class Target
{
public:
	int x, y, state;
	int w, h, vel;
	int colorR, colorG, colorB;
};

class Mario
{
protected:
	int wid, hei;
	char *dat;

public:
	int x, y, w, h, spdX, spdY, steps, timer;
	int radius, facing, isJumping, isFalling, isRunning, isLanding, isAlive;
	int jumpheight,collState,monState;
	char *state;
	char *leftNormalStill, *leftNormalTransit, *leftNormalRun, *leftNormalJump;
	char *rightNormalStill, *rightNormalTransit, *rightNormalRun, *rightNormalJump;
	char *leftSuperStill, *leftSuperTransit, *leftSuperRun, *leftSuperJump;
	char *rightSuperStill, *rightSuperTransit, *rightSuperRun, *rightSuperJump;
	char *NormalDead;

	Mario();
	~Mario();
	void CleanUp(void);
	Mario(const Mario &incoming);
	Mario &operator = (const Mario &incoming);
	void Set(const Mario &incoming);
	const char *GetPointer(void) const;
	const int StrLen(void) const;

	const int GetWidth(void) const;
	const int GetHeight(void) const;
	void SetBitmap(int bmpWid, int bmpHei, char bmp[]);
	void SetPixel(int x, int y, char c);

	void Print(void) const;
	void Draw(int cameraX);
	const char GetPixel(int x, int y) const;

	void Init(void);

	void jump(void);
	int findCollisionIdx(Bricks B_targets[], int B_num, QBricks QB_targets[], int QB_num, Tubes T_targets[], int T_num, StairBricks SB_targets[], int SB_num);
	void checkLocalCollision_B(Bricks &target);
	void checkLocalCollision_QB(QBricks &target);
	int findTubeIdx(Tubes T_targets[], int T_num);
	void checkLocalCollision_T(Tubes &target);
	void checkLocalCollision_SB(StairBricks &target);
	int findMonsterIdx(MonMush M_Mons[], int mush_num, Turtle T_Mons[], int tur_num);
	void checkCollisionWithMonster(MonMush M_Mons);
	void checkCollisionWithTurtle(Turtle T_Mons);
	int checkGap(void);
	void growUp(Mushrooms &target);
};


#endif