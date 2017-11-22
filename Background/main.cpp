/* 
 * Author   : Jiayi Wang
 * Andrew id: jiayiw2
 *
 * Content:
 * This .cpp file basically draws ground and background of the game.
 * 
 * How to operate:
 * Press RIGHT to roll the screen to right side.
 * Press LEFT to roll the screen to left side.
 * Press ESC to exit.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include "yspng.h"
#include "fssimplewindow.h"
#include "Ground.h"

const double PI = 3.1415927;

int main(void)
{    
	// set camera
	int camera_x = 0;

	// initialization
	CharBitmap bmp;
	bmp.init();
	
	Texture TX;
	TX.init();
	

	FsOpenWindow(16, 16, 768, 576, 1);
	TX.set();

	while (FsInkey() != FSKEY_ESC)
	{
		FsPollDevice();

		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		// move camera
		if (0 != FsGetKeyState(FSKEY_RIGHT))
		{
			camera_x += 10;
		}

		if (0 != FsGetKeyState(FSKEY_LEFT))
		{
			camera_x -= 10;
		}
		if (0 != FsGetKeyState(FSKEY_SPACE))
		{
			camera_x += 100;
		}

		/////////////////////// draw everything ////////////////////
	        // draw background
		bmp.Draw_bgd();

		// texture mapping goes here 
		TX.Draw_texture(camera_x);

		// Bitmap drawing goes here
		bmp.Draw_everything(camera_x);
		

		FsSwapBuffers();

		FsSleep(10);
	}

	return 0;
}
