/*
@author Yueh-Han, Chuang              Contact me: yuehhanc@andrew.cmu.edu

Class GameSetting is a piece of base code for making games and animations.
The class practices the Model-View-Control structure and isolates four functions, 
init(), keyPressed(), timerFired(), redrawAll(), from the main loop.
Moreover, it has variables specifically preset for our project.
Though GameSetting may not be perfect, it was already tested beforehand.
Basically, any code written according to the struture of GameSetting will 
always work even if we need to update GameSetting in the future. Actually, 
we did add functions to play music in the end. And it turned out that pieces
of code built on it still works as I promised.
*/

#include "Ground.h"
#include "Mario.h"
#include "SteadyObjects.h"
#include "monster.h"
#include "yssimplesound.h"



class GameSetting {
public:
	//Default game features and their values
	int mapWidth = 10000, mapHeight = 1000;
	int windowWidth = 768, windowHeight = 576;
	int timerDelay = 10;
	int cameraX = 0, cameraY = 0;
	int keyState;
	double timeCounter = 0;

	//Global variables in the game(eg.score, coins)
	double PassedTime;

	//Game objects
	CharBitmap myBackground;
	Texture myTexture;
	Mario myMario;
	Objects myObjects;
	MonsterAll myMonsters;

	void init(int newWindowWidth, int newWindowHeight, int newMapWidth, int newMapHeight);
	void timerFired(void);
	void keyPressed(int keyEvent);
	void redrawAll(int cameraX);
	void setCamera(void);
};