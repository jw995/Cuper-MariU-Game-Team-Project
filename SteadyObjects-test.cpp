#include <stdio.h>
#include <stdlib.h>
#include "fssimplewindow.h"
#include "SteadyObjects.h"

int main()
{
    int winWid, winHei;
    int marioX, marioY, marioW, marioH;
    double dt;
    int cameraX;
    int terminate = 0;
    winWid = 768;
    winHei = 576;
    cameraX = 0;

    ///////////////////////////////////////////////////////////
    /////////// Code for creating and using Objects ///////////
    Objects objects;
    objects.Init();
    /////////// Code for creating and using Objects ///////////
    ///////////////////////////////////////////////////////////

	// test Mario
	marioX = 1*48;
	marioY = 10*48;
	marioW = 48;
	marioH = 48;

	FsOpenWindow(400,0,winWid,winHei,1);
    FsPassedTime();
	while(!terminate) {
		FsPollDevice();
		dt = (double)FsPassedTime()/1000.0;
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        marioX += 2;
        //marioY -= 2;
        if (0 != FsGetKeyState(FSKEY_RIGHT)) {
            cameraX += 50;
        }
        if (0 != FsGetKeyState(FSKEY_LEFT)) {
            cameraX -= 50;
        }
        if (0 != FsGetKeyState(FSKEY_ESC)) {
            terminate = 1;
        }
        DrawRect(marioX, marioY, marioX + marioW, marioY + marioH,1);


    ///////////////////////////////////////////////////////////
    /////////// Code for creating and using Objects ///////////
        objects.Contact(marioX, marioY, marioW, marioH);
        // It's a trick!!
        // Call twice to increase resolution
        objects.MushroomMove(marioX, marioY, marioW, marioH, dt);
        objects.MushroomMove(marioX, marioY, marioW, marioH, dt);

        objects.Draw(cameraX);
    /////////// Code for creating and using Objects ///////////
    ///////////////////////////////////////////////////////////

		FsSwapBuffers();
        FsSleep(10);
	}

	return 0;
}
