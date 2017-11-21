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

inline void draw_sth(int x, int y, GLuint texId, int wid, int hei)
{
	glBindTexture(GL_TEXTURE_2D, texId);
	glBegin(GL_QUADS);

	glTexCoord2d(0.0, 0.0);
	glVertex2i(x, y);

	glTexCoord2d(1.0, 0.0);
	glVertex2i(x + wid, y);

	glTexCoord2d(1.0, 1.0);
	glVertex2i(x + wid, y + hei);

	glTexCoord2d(0.0, 1.0);
	glVertex2i(x, y + hei);

	glEnd();
}

int main(void)
{    
	// set camera
	int camera_x = 0;

	// initialization

	////////////////////////////////////////////
	CharBitmap bmp;
	bmp.init();
	
	// texture parameters
	Texture TX;
	TX.init();
	
	////////////////////////////////////////////////

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
	    // draw blue sky
		bmp.Draw_bgd();

		////////////////////////////////////////////////
		// texture map setting begins here 
		TX.Draw_texture(camera_x);

		// Bitmap drawing goes here//////
		bmp.Draw_everything(camera_x);
		

		FsSwapBuffers();

		FsSleep(10);
	}

	return 0;
}