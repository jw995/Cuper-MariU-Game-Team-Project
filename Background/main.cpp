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
	// set timer
	time_t t = time(NULL);
	srand(time(NULL));

	int gap[7] = { 69,70,86,87,88,153,154 };

	int cloud_x[20], cloud_y[20];
	for (int i = 0; i < 20; i++)
	{
		cloud_x[i] = rand() % 9889;
		cloud_y[i] = rand() % 180;
	}
	////////////////////////////////////////////
	CharBitmap bmp;
	bkgd background;

	
	// texture parameters
	const int num = 11;
	GLuint texId[num];
	YsRawPngDecoder png[num];
	png[0].Decode("hunt.png");
	png[1].Decode("wean.png");
	png[2].Decode("museum.png");
	png[3].Decode("walk.png");
	png[4].Decode("cloud_m.png");
	png[5].Decode("cloud_l.png");
	png[6].Decode("grass_m.png");
	png[7].Decode("grass_s.png");
	png[8].Decode("wean_on.png");
	png[9].Decode("hunt_off.png");
	png[10].Decode("fence.png");

	
	////////////////////////////////////////////////

	FsOpenWindow(16, 16, 768, 576, 1);

	// set 2D texture
	set_texture(texId[0], png[0]);
	set_texture(texId[1], png[1]);
	set_texture(texId[2], png[2]);
	set_texture(texId[3], png[3]);
	set_texture(texId[4], png[4]);
	set_texture(texId[5], png[5]);
	set_texture(texId[6], png[6]);
	set_texture(texId[7], png[7]);
	set_texture(texId[8], png[8]);
	set_texture(texId[9], png[9]);
	set_texture(texId[10], png[10]);


	while (FsInkey() != FSKEY_ESC)
	{
		FsPollDevice();

		int wid, hei;
		FsGetWindowSize(wid, hei);

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
		background.Draw_bgd();

		////////////////////////////////////////////////
		// texture map setting begins here 
		glViewport(0, 0, wid, hei);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, (float)wid - 1, (float)hei - 1, 0, -1, 1);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glColor4d(1.0, 1.0, 1.0, 1.0);

		glEnable(GL_TEXTURE_2D);

		// 2D drawing goes here////////////////////////////////////
		// draw m_cloud
		draw_sth(1000 - camera_x, 150, texId[4], 192, 96);
		draw_sth(3000 - camera_x, 150, texId[4], 192, 96);
		draw_sth(5000 - camera_x, 100, texId[4], 192, 96);
		draw_sth(7000 - camera_x, 150, texId[4], 192, 96);
		// draw l_cloud
		draw_sth(2000 - camera_x, 50, texId[5], 288, 96);
		draw_sth(4000 - camera_x, 20, texId[5], 288, 96);
		draw_sth(6000 - camera_x, 50, texId[5], 288, 96);
		draw_sth(8000 - camera_x, 50, texId[5], 288, 96);
		// draw hunt
		if (camera_x > 28 * 48)
		{
			draw_sth(35 * 48 - camera_x, 312, texId[0], 256 * 1.5, 128 * 1.5);
		}
		else
		{
			draw_sth(35 * 48 - camera_x, 312, texId[9], 256 * 1.5, 128 * 1.5);
		}

		// draw wean
		if (camera_x > 165 * 48)
		{
			draw_sth(170 * 48 - camera_x, 312, texId[8], 256 * 1.5, 128 * 1.5);
		}
		else
		{
			draw_sth(170 * 48 - camera_x, 312, texId[1], 256 * 1.5, 128 * 1.5);
		}
		
		// draw dinosaur
		draw_sth(61*48-camera_x, 288, texId[2], 240*1.5, 144*1.5);
		// draw walking to sky
		draw_sth(198*48-camera_x, 216, texId[3], 144*1.5, 192*1.5);
		// draw fence
		draw_sth(100*48 - camera_x, 360, texId[10], 480*1.5, 96*1.5);

		glDisable(GL_TEXTURE_2D);


		// Bitmap drawing goes here/////////////////////////////////
		// draw ground 
		for (int bias_x = 0; bias_x < 48*206; bias_x = bias_x + 48)
		{
			if (bias_x != 48 * gap[0] && 
				bias_x != 48 * gap[1] &&
				bias_x != 48 * gap[2] &&
				bias_x != 48 * gap[3] && 
				bias_x != 48 * gap[4] &&
				bias_x != 48 * gap[5] &&
				bias_x != 48 * gap[6] )
			{
				bmp.Draw_ground(bias_x-camera_x, 504);
				bmp.Draw_ground(bias_x-camera_x, 552);
			}
		}

		// draw cloud
		bmp.Draw_cloud(300-camera_x, 30);
		for (int i = 0; i < 20; i++)
		{
			bmp.Draw_cloud(cloud_x[i] - camera_x, cloud_y[i]);
		}

		// draw grass 
		bmp.Draw_grass(100 - camera_x,456);

		// draw mountain
		bmp.Draw_mountain(500 - camera_x, 456);


		FsSwapBuffers();

		FsSleep(10);
	}

	return 0;
}