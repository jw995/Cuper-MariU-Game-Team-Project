/*
Class GameSetting - Integrate all classes into an entire game
@author Yueh-Han, Chuang

<Instruction>
This file is a common structure of a game.
Integration of a game is basically all taken care of.
All what you want to do is to fill the 4 functions below:
GameSetting::init()
GameSetting::timerFired()
GameSetting::keyPressed()
GameSetting::redrawAll()

You may also want to declare your own class in the game.
Please declare your class in the "Game Objects Area" in class GameSetting.
Replace the testing classes with your own class.
Doing so by including your class is recommended!
By the way, I commented out all the testing classes except for class Player.
However, you can look up them if you want to get further understanding of the structure.
You can also take them as default objects and background to test your own class.
**Caution**
Please do NOT declare variables other than your class in this file. e.g. int sth, bool sth...
THIS WILL SAVE OUR ASS FROM DEBUGGING!!!
In addition, it's the way for us to be a good object-oriented programmer!
If you feel you really want to declare some primitives, that's fine. Just do it.
But remember to discuss with me later!!!
Carpe Diem!
Have fun!
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fssimplewindow.h"
#include "yssimplesound.h"
#include "gamesetting.h"
#include "Ground.h"
#include "Mario.h"
#include "SteadyObjects.h"
#include "monster.h"


///////////////////////////////////////////////////////////////
// Fill the 4 functions Below!
////////////////////////////////////////////////////////////////

/* Initialize your object! */
void GameSetting::init(int newWindowWidth, int newWindowHeight, int newMapWidth, int newMapHeight)
{
	// Settings //
	windowWidth = newWindowWidth;
	windowHeight = newWindowHeight;
	mapWidth = newMapWidth;
	mapHeight = newMapHeight;

	// Your Code Here! //
	myBackground.Init();
	myTexture.Init();
	myMario.Init();
	myObjects.Init();
	myMonsters.initialize();
}

/* Anything relevant to the time! */
void GameSetting::timerFired(void)
{
	int block_hit_x;
	timeCounter += timerDelay / 1000.0;
	if (myMario.x <= cameraX)
		myMario.x = cameraX;

	myMario.jump();
	if (!strcmp(myMario.state, "normal"))
	{
		block_hit_x = myObjects.Contact(myMario.x, myMario.y - 48, 48, 48, myMario.state, myMario.isFalling);
		myObjects.MushroomMove(myMario.x,myMario.y-48,48,48,PassedTime);
		myObjects.MushroomMove(myMario.x,myMario.y-48,48,48,PassedTime);
		myMonsters.timeFired(cameraX, myObjects.tube, myObjects.brick[3].broken, block_hit_x, myMario.x, myMario.y-48, myMario.spdX, myMario.spdY, 48, 48 );
	}
	else
	{
		block_hit_x = myObjects.Contact(myMario.x, myMario.y - 96, 48, 96, myMario.state, myMario.isFalling);
		myObjects.MushroomMove(myMario.x,myMario.y-96,48,96,PassedTime);
		myObjects.MushroomMove(myMario.x,myMario.y-96,48,96,PassedTime);
		myMonsters.timeFired(cameraX, myObjects.tube, myObjects.brick[3].broken, block_hit_x, myMario.x, myMario.y-48, myMario.spdX, myMario.spdY, 48, 48 );
	}
	
	int idx1 = myMario.findCollisionIdx(myObjects.brick, 30, myObjects.qbrick, 12, myObjects.tube, 8, myObjects.stairbrick, 7);
	if(idx1 < 30)
	{
		myMario.checkLocalCollision_B(myObjects.brick[idx1]);
		//printf("find_B:%d, collstate: %d \n", idx1,myMario.collState);
	}
	else if (idx1 < 42)
	{
		myMario.checkLocalCollision_QB(myObjects.qbrick[idx1-30]);
		//printf("find_QB:%d, collstate: %d \n", idx1-30,myMario.collState);
	}
	else if (idx1 < 50)
	{
		myMario.checkLocalCollision_T(myObjects.tube[idx1-42]);
		//printf("find_T:%d, collstate: %d\n", idx1-42, myMario.collState);
	}
	else
	{
		myMario.checkLocalCollision_SB(myObjects.stairbrick[idx1-50]);
	}

	int idx2 = myMario.findMonsterIdx(myMonsters.mush, 16, myMonsters.turtle, 1);
	if (idx2 < 16)
		myMario.checkCollisionWithMonster(myMonsters.mush[idx2]);
	else
		myMario.checkCollisionWithTurtle(myMonsters.turtle[idx2-16]);
	myMario.growUp(myObjects.mushroom);
	
	
	setCamera();
	
}

/*
Put every function related to key-pressed events here.
keyEvent is the value of the key pressed by the user.
Record the keyEvent in keyState if you think you need to do so.
*/
void GameSetting::keyPressed(int keyEvent)
{
	if ((!myMario.checkGap() || myMario.y<504))
	{
		switch (keyEvent)
		{
			case FSKEY_NULL:
				myMario.isRunning = 0;
				break;
			case FSKEY_ESC:
				exit(0);
				break;
		}
		if (0 != FsGetKeyState(FSKEY_LEFT)) 
		{
			myMario.facing = 1;
			myMario.isRunning = 1;
			myMario.x -= myMario.spdX;
		}
		if (0 != FsGetKeyState(FSKEY_RIGHT)) 
		{
			myMario.facing = 0;
			myMario.isRunning = 1;
			myMario.x += myMario.spdX;
		}
		if (0 != FsGetKeyState(FSKEY_SPACE)) 
		{
			if ((!myMario.isJumping) && (!myMario.isFalling))
			{
				myMario.isJumping = 1;
				myMario.isFalling = 0;
				myMario.isLanding = 0;
			}
		}
	}
	else if(myMario.y > 576+myMario.h)
	{
		myMario.isAlive = 0;
	}
}

/* Put all of your draw functions here*/
void GameSetting::redrawAll(int cameraX)
{
	/* Your Code Here! */
	myBackground.Draw_background();
	myTexture.Draw_texture(cameraX);
	myTexture.Draw_soji(cameraX);
	myBackground.Draw_everything(cameraX);
	myObjects.Draw(cameraX);
	myMonsters.reDraw(cameraX);
	if (myMario.x <196*48)
		myMario.Draw(cameraX);
	Draw_edding(myMario.x, cameraX, myBackground, myTexture);

}

/* setCamera should only be modified by who designs class Player*/
void GameSetting::setCamera(void)
{ 
	if (myMario.x > 196*48 && cameraX < 198*48)
	{
		cameraX +=10;
	}
	else if ((myMario.x + windowWidth / 2) < mapWidth) 
	{
		if (((myMario.x - cameraX) > (windowWidth / 2)) && FsGetKeyState(FSKEY_RIGHT) != 0)
		{
			cameraX = myMario.x - windowWidth / 2;
		}
	}
}
