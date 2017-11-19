#include <stdio.h>
#include <stdlib.h>
#include "fssimplewindow.h"
#include "SteadyObjects.h"

int main()
{
    int winWid, winHei;
    int pixelperbit;
    const int nCoins = 5;
    const int nBricks = 16+5;
    const int nTubes = 2;
    int i;
    int mx, my, mw, mh;
    double dt;
    winWid = 768;
    winHei = 576;

	Coins coin[nCoins];
	Bricks brick[nBricks];
    Tubes tube[nTubes];
	Mushrooms mushroom;

	// test Mario
	mx = 1*48;
	my = 10*48;
	mw = 48;
	mh = 48;

	i = 0;
	for (auto &c : coin) {
	    c.x = (i+3)*48;
	    c.y = 1*48;
	    i++;
	}

	i = 0;
    for (i = 0; i < 16; ++i) {
        auto &b = brick[i];
        b.x = i * 48;
        b.y = 11*48;
        b.y_original = b.y;
        b.y_peak = b.y - b.h/2;
    }
    for (i = 16; i < nBricks; ++i) {
        auto &b = brick[i];
        b.x = (i-15) * 48;
        b.y = 3*48;
        b.y_original = b.y;
        b.y_peak = b.y - b.h/2;
    }

    i = 0;
    for (auto &t : tube) {
        t.x = i * 48;
        t.y = 6*48;
        t.layers = 5;
        t.UpdateHeight();
        i += 8;
    }

	mushroom.x = 7*48.0;
	mushroom.y = 1*48.0;

	FsOpenWindow(400,0,winWid,winHei,1);
    FsPassedTime();
	while(FSKEY_NULL==FsInkey()) {
		FsPollDevice();
		dt = (double)FsPassedTime()/1000.0;
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);


        /* test Mario */
        mx += 2;
        //my -= 2;


        DrawRect(mx, my, mx + mw,my + mh,1);
        /* End test mario */
        for (auto &c:coin) {
            c.MarioContact(mx, my, mw, mh);
        }
        for (auto &b:brick) {
            b.MarioContact(mx, my, mw, mh);
        }
        mushroom.MarioContact(mx, my, mw, mh);

        // TRICK!! to increase resolution
        mushroom.Move(tube, nTubes, brick, nBricks, dt);
        mushroom.Move(tube, nTubes, brick, nBricks, dt);

        for (auto &c:coin) {
            c.Draw();
        }
        for (auto &b:brick) {
            b.Draw();
        }
        for (auto &t:tube) {
            t.Draw();
        }
        mushroom.Draw();

		FsSwapBuffers();

        FsSleep(10);
	}

	return 0;
}
