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
#include <stdlib.h>//
#include <math.h>
#include "fssimplewindow.h"
//////////////////////////////////
// Include Your Class Here!//
//////////////////////////////////
//#include "player.h"



/////////////////////////////////////

/* Testing Classes*/


class Player {
public:
int x = 0, y = 500, defaultY = 500;
double jumpTimer = 0, timerDefault = 1.0;
void jump(void);
void draw(int cameraX) const;
};

void Player::jump(void) {
if (jumpTimer > 0) {
if (jumpTimer <= 0) {
y = defaultY;
}
if (jumpTimer > 0.5 * timerDefault) {
y = defaultY - 50 * (1 - jumpTimer);
}
else {
y = defaultY - 50 * jumpTimer;
}
}
}
void Player::draw(int cameraX) const {
glColor3ub(255, 0, 0);
glBegin(GL_QUADS);
glVertex2i(x-10 - cameraX,y);
glVertex2i(x+10 - cameraX,y);
glVertex2i(x+10 - cameraX,y-20);
glVertex2i(x-10 - cameraX,y-20);
glEnd();
}


class Monster{
public:
	int x = 600, y = 500;
	void draw(int cameraX) const;
};

void Monster::draw(int cameraX) const {
	glColor3ub(255, 255, 0);
	glBegin(GL_QUADS);
	glVertex2i(x - 10 - cameraX, y);
	glVertex2i(x + 10 - cameraX, y);
	glVertex2i(x + 10 - cameraX, y - 30);
	glVertex2i(x - 10 - cameraX, y - 30);
	glEnd();
}

class Background{
public:
	int numTree = 5;
	int treeX[5], treeY[5];
	void init(void);
	void draw(int cameraX) const;
};

void Background::draw(int cameraX) const {
	glColor3ub(0, 255, 0);
	for (int i = 0; i < numTree; i++) {
		glBegin(GL_QUADS);
		glVertex2i(treeX[i] - 20 - cameraX, treeY[i]);
		glVertex2i(treeX[i] + 20 - cameraX, treeY[i]);
		glVertex2i(treeX[i] + 20 - cameraX, treeY[i] - 50);
		glVertex2i(treeX[i] - 20 - cameraX, treeY[i] - 50);
		glEnd();
	}
	glColor3ub(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2i(0, 500);
	glVertex2i(800, 500);
	glEnd();
	
}
void Background::init(void) {
	for (int i = 0; i < 5; i++) {
		treeX[i] = i * 500;
		treeY[i] = 500;
	}
}


class GameSetting {
public:
	//Default game features and their values
	int mapWidth = 1600, mapHeight = 1000;
	int windowWidth = 768, windowHeight = 576;
	int timerDelay = 100;
	int cameraX = 0, cameraY = 0;
	int keyState;
	double timeCounter = 0;
	//Global variables in the game(eg.score, coins)
	int numCoin = 0;
	int numPlayerLives = 3;

	//////////////////////////////////////////
	// ** Game Objects Area **
	///////////////////////////////////////////////////////////////////////////////////////
	Player myPlayer;
	Player myPlayer2;
	Monster myMonsters;
	Background myBackground;






















	
	/*End of Game Object Area*/

	void init(void);
	void init(int newWindowWidth, int newWindowHeight, int newMapWidth, int newMapHeight);
	void timerFired(void);
	void keyPressed(int keyEvent);
	void redrawAll(int cameraX) const;
	void setCamera(void);
};
///////////////////////////////////////////////////////////////
// Fill the 4 functions Below!
////////////////////////////////////////////////////////////////

/* Initialize your object! */
void GameSetting::init(int newWindowWidth, int newWindowHeight, int newMapWidth, int newMapHeight)
{
	/* Settings */
	windowWidth = newWindowWidth;
	windowHeight = newWindowHeight;
	mapWidth = newMapWidth;
	mapHeight = newMapHeight;

	/* Your Code Here! */
	myBackground.init();
}

/* Anything relevant to the time! */
void GameSetting::timerFired(void)
{
	timeCounter += timerDelay / 1000.0;
	setCamera();

	/* Your Code Here! */
	if (myPlayer.jumpTimer > 0) {
		myPlayer.jumpTimer -= timerDelay / 1000.0;
		myPlayer.jump();
	}
	
}

/*
Put every function related to key-pressed events here.
keyEvent is the value of the key pressed by the user.
Record the keyEvent in keyState if you think you need to do so.
*/
void GameSetting::keyPressed(int keyEvent)
{
	/* Your Code Here! */
	// default player controls
	switch (keyEvent)
	{
	case FSKEY_SPACE:
		if (myPlayer.jumpTimer <= 0) {
			myPlayer.jumpTimer = myPlayer.timerDefault;
		}
		break;
	}
	if (0 != FsGetKeyState(FSKEY_LEFT)) {
		myPlayer.x -= 10;
		keyState = FSKEY_LEFT;
	}
	if (0 != FsGetKeyState(FSKEY_RIGHT)) {
		myPlayer.x += 10;
		keyState = FSKEY_RIGHT;
	}
}

/* Put all of your draw functions here*/
void GameSetting::redrawAll(int cameraX) const
{
	/* Your Code Here! */
	myBackground.draw(cameraX);
	myMonsters.draw(cameraX);
	myPlayer.draw(cameraX);
	
	
}

/* setCamera should only be modified by who designs class Player*/
void GameSetting::setCamera(void)
{
	if ((myPlayer.x + windowWidth / 2) < mapWidth) {
		if ((myPlayer.x - cameraX) > windowWidth / 2 && keyState == FSKEY_RIGHT) {
			cameraX = myPlayer.x - windowWidth / 2;
		}
	}
}

/*****Ignore the code below*****/
////////////////////////////////////////////////////////////////////////////////////

//overload init() with no args
void GameSetting::init(void)
{
}

void run(void) {
	GameSetting myGame;	
	myGame.init();
	FsOpenWindow(16, 16, 768, 576, 1);
	while (FsInkey() != FSKEY_ESC)
	{
		FsPollDevice();
		int key = FsInkey();
		myGame.keyPressed(key);
		myGame.timerFired();
		
		//drawing
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		myGame.redrawAll(myGame.cameraX);
		FsSwapBuffers();
		FsSleep(myGame.timerDelay);
	}
}

//overload no args run()
void run(int width, int height, int mapWidth, int mapHeight) {
	GameSetting myGame;
	myGame.init(width, height, mapWidth, mapHeight);
	FsOpenWindow(16, 16, width, height, 1);
	while (FsInkey() != FSKEY_ESC)
	{
		FsPollDevice();
		int key = FsInkey();
		myGame.keyPressed(key);
		myGame.timerFired();

		//drawing
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		myGame.redrawAll(myGame.cameraX);
		FsSwapBuffers();
		FsSleep(myGame.timerDelay);
	}
}

int main()
{
	run(768, 576, 1600, 1000);
	return 0;
}
