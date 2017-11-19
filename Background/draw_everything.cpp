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
#include "yspng.h"
#include "fssimplewindow.h"
#include <math.h>
#include <ctype.h>

const double PI = 3.1415927;

void set_texture(GLuint &texId, YsRawPngDecoder png)
{
	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D
	(GL_TEXTURE_2D,
		0,
		GL_RGBA,
		png.wid,
		png.hei,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		png.rgba);
}

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

inline void Draw_quad(int a, int b)
{
	glBegin(GL_QUADS);

	glVertex2i(a, b);
	glVertex2i(a + 3, b);
	glVertex2i(a + 3, b + 3);
	glVertex2i(a, b + 3);

	glEnd();
}

////////////////////////////////////////////
class bkgd
{
public:
	void Draw_bgd(void);
};

void bkgd::Draw_bgd(void)
{
	glColor3ub(2, 103, 218);
	glBegin(GL_QUADS);

	glVertex2i(0, 0);
	glVertex2i(48 * 206, 0);
	glVertex2i(48 * 206, 576);
	glVertex2i(0, 576);

	glEnd();
}

class CharBitmap
{
protected:
	int wid, hei;
	char *dat;
public:
	CharBitmap();
	~CharBitmap();
	void CleanUp(void);

	CharBitmap(const CharBitmap &incoming);
	CharBitmap &operator=(const CharBitmap &incoming);

	int GetWidth(void) const;
	int GetHeight(void) const;
	void SetBitmap(int bmpWid, int bmpHei, char bmp[]);
	void SetPixel(int x, int y, char c) const;
	char GetPixel(int x, int y) const;

	// Draw functions
	void Draw_ground(int bias1, int bias2);
	void Draw_cloud(int bias1, int bias2);
	void Draw_grass(int bias1, int bias2);
	void Draw_mountain(int bias1, int bias2);
};

CharBitmap::CharBitmap()
{
	wid = 0;
	hei = 0;
	dat = nullptr;
}
CharBitmap::~CharBitmap()
{
	CleanUp();
}
void CharBitmap::CleanUp(void)
{
	if (nullptr != dat)
	{
		delete[] dat;
		dat = nullptr;
	}
}
int CharBitmap::GetWidth(void) const
{
	return wid;
}
int CharBitmap::GetHeight(void) const
{
	return hei;
}
CharBitmap::CharBitmap(const CharBitmap &incoming)
{
	dat = nullptr;
	SetBitmap(GetWidth(), GetHeight(), incoming.dat);
}
CharBitmap &CharBitmap::operator=(const CharBitmap &incoming)
{
	SetBitmap(GetWidth(), GetHeight(), incoming.dat);
	return *this;
}
void CharBitmap::SetBitmap(int bmpWid, int bmpHei, char bmp[])
{
	if (bmp != dat)
	{
		CleanUp();
		wid = bmpWid;
		hei = bmpHei;
		int length = bmpWid*bmpHei;
		dat = new char[length];
		for (int i = 0; i<length; i++)
		{
			dat[i] = bmp[i];
		}
	}
}
void CharBitmap::SetPixel(int x, int y, char c) const
{
	if (0 <= x && x < wid && 0 <= y && y < hei)
	{
		dat[y*wid + x] = c;
	}
}


void CharBitmap::Draw_ground(int bias1, int bias2)
{
	int x, y;
	for (y = 0; y < hei; y++)
	{
		for (x = 0; x < wid; x++)
		{	
			int a = 3 * x + bias1;
			int b = 3 * y + bias2;
			if ('1' == GetPixel(x, y))
			{
				glColor3ub(0, 0, 0);
				Draw_quad(a, b);
			}
			else if ('2' == GetPixel(x, y))
			{
				glColor3ub(255, 255, 218);
				Draw_quad(a, b);
			}
			else
			{
				glColor3ub(196, 110, 24);
				Draw_quad(a, b);
			}
		}
	}
}

void CharBitmap::Draw_cloud(int bias1, int bias2)
{
	int x, y;
	for (y = 0; y < hei; y++)
	{
		for (x = 0; x < wid; x++)
		{
			int a = 3 * x + bias1;
			int b = 3 * y + bias2;
			if ('1' == GetPixel(x, y))
			{
				glColor3ub(0, 0, 0);
				Draw_quad(a, b);
			}
			else if ('2' == GetPixel(x, y))
			{
				;
			}
			else if ('0' == GetPixel(x, y))
			{
				glColor3ub(45, 175, 77);
				Draw_quad(a, b);
			}
			else
			{
				glColor3ub(255, 255, 255);
				Draw_quad(a, b);
			}
		}
	}
}

void CharBitmap::Draw_grass(int bias1, int bias2)
{
	int x, y;
	for (y = 0; y < hei; y++)
	{
		for (x = 0; x < wid; x++)
		{
			int a = 3 * x + bias1;
			int b = 3 * y + bias2;
			if ('1' == GetPixel(x, y))
			{
				glColor3ub(0, 0, 0);
				Draw_quad(a, b);
			}
			else if ('2' == GetPixel(x, y))
			{
				glColor3ub(2, 103, 218);
				Draw_quad(a, b);
			}
			else if ('0' == GetPixel(x, y))
			{
				glColor3ub(45, 175, 77);
				Draw_quad(a, b);
			}
			else
			{
				glColor3ub(113, 217, 3);
				Draw_quad(a, b);
			}
		}
	}
}

void CharBitmap::Draw_mountain(int bias1, int bias2)
{
	int x, y;
	for (y = 0; y < hei; y++)
	{
		for (x = 0; x < wid; x++)
		{
			int a = 3 * x + bias1;
			int b = 3 * y + bias2;
			if ('1' == GetPixel(x, y))
			{
				glColor3ub(0, 0, 0);
				Draw_quad(a, b);
			}
			else if ('2' == GetPixel(x, y))
			{
				;
			}
			else if ('0' == GetPixel(x, y))
			{
				glColor3ub(45, 175, 77);
				Draw_quad(a, b);
			}
			else
			{
				glColor3ub(45, 175, 77);
				Draw_quad(a, b);
			}
		}
	}
}


char CharBitmap::GetPixel(int x, int y) const
{
	if (0 <= x && x<wid && 0 <= y && y<hei)
	{
		return dat[y*wid + x];
	}
	return 0;
}

int main(void)
{    
	// set camera
	int camera_x = 0;
	
	// initialization
	////////////////////////////////////////////

	char pattern_ground[] =
	{
		"2........12....1"
		"2........12....1"
		"2........121...1"
		"2........1.11111"
		"2........12....1"
		"2........12....1"
		"2........12....1"
		"2........12....1"
		"2.......12.....1"
		"11......12.....1"
		"2211....12.....1"
		"2.2211112......1"
		"2...22212......1"
		"2......12......1"
		"211111111111111."
		".222222222222221"
	};

	char pattern_cloud[] =
	{
		"22222222222222222222222222222222"
		"22222222222222222222222222222222"
		"22222222222222222222222222222222"
		"22222222222222222222222222222222"
		"22222222222222222222222222222222"
		"22222222222222222222222222222222"
		"22222222222222222222222222222222"
		"22222222222211112222222222222222"
		"222222222211....1222222222222222"
		"2222222221.......122222222222222"
		"2222222221....2..122212222222222"
		"222222221......2..121.1222222222"
		"22222111...22......1..1212222222"
		"22221.....2............1.1222222"
		"2221....22...............1212222"
		"221.......................1.1222"
		"221..........................122"
		"21..........................1222"
		"21.........................12222"
		"2211...2....2........2......1222"
		"222211..2..2.22.....2....22..122"
		"2222221..22....22222.22222...122"
		"222221.......1...22....2...11222"
		"222222111...1211....11...1122222"
		"22222222211122221111221112222222"
		"22222222222222222222222222222222"
		"22222222222222222222222222222222"
		"22222222222222222222222222222222"
		"22222222222222222222222222222222"
		"22222222222222222222222222222222"
		"22222222222222222222222222222222"
		"22222222222222222222222222222222"
	};

	char pattern_grass[] =
	{
		"2222222222222222222222222222222222222222222222211112222222222222"
		"22222222222222111112222222222221111122222222221....1222222222222"
		"22222222222221.....122222222221.....12212222111....1112222222222"
		"22222222222221......12122222111.....111.1221..........1222222222"
		"2222222222211.......11.12221.............121.....0.....122222222"
		"22222222221......0.....12221....0..00....11...0...00....12222222"
		"2222222221........00....1211..00.....00......00.....0...12222222"
		"2222222221....0.....0...11..................0...........12212222"
		"2222222221....0..........................................11.1222"
		"222222111....0...........................................1..1112"
		"222221.........................................................1"
		"22221..........................................................1"
		"2111...........................................................1"
		"1.............................................................12"
		"1.............................................................12"
		"21.............................................................1"
	};

	char pattern_mountain[] =
	{
		"222222222222222222222111111222222222222222222222"
		"222222222222222221111......111122222222222222222"
		"22222222222222111..............11122222222222222"
		"22222222222221................1...12222222222222"
		"2222222222221................111...1222222222222"
		"222222222221.................111....122222222222"
		"22222222221...............11.111.....12222222222"
		"2222222221................11..1.......1222222222"
		"222222221.................11...........122222222"
		"22222221................................12222222"
		"2222221..................................1222222"
		"222221....................................122222"
		"22221......................................12222"
		"2221........................................1222"
		"221..........................................122"
		"21............................................12"
	};

	CharBitmap bmp;
	bkgd background;
	int gap[7] = { 69,70,86,87,88,153,154 };
	
	// texture parameters
	const int num = 4;
	GLuint texId[num];
	YsRawPngDecoder png[num];
	png[0].Decode("hunt.png");
	png[1].Decode("wean.png");
	png[2].Decode("museum.png");
	png[3].Decode("walk.png");

	
	////////////////////////////////////////////////

	FsOpenWindow(16, 16, 768, 576, 1);

	// set 2D texture
	set_texture(texId[0], png[0]);
	set_texture(texId[1], png[1]);
	set_texture(texId[2], png[2]);
	set_texture(texId[3], png[3]);


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


		/////////////////////// draw everything ////////////////////
	    // draw blue sky
		background.Draw_bgd();

		////////////////////////////////////////////////
		// texture mapping begins here 
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
		// draw hunt 
		draw_sth(650-camera_x, 312, texId[0], 256*1.5, 128*1.5);
		// draw wean
		draw_sth(2500-camera_x, 312, texId[1], 256*1.5, 128*1.5);
		// draw dinosaur
		draw_sth(1700-camera_x, 288, texId[2], 240*1.5, 144*1.5);
		// draw walking to sky
		draw_sth(48*80-camera_x, 216, texId[3], 144*1.5, 192*1.5);

		glDisable(GL_TEXTURE_2D);


		// Bitmap drawing goes here/////////////////////////////////
		// draw ground 
		bmp.SetBitmap(16, 16, pattern_ground);
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
		bmp.SetBitmap(32, 32, pattern_cloud);
		bmp.Draw_cloud(300-camera_x, 30);
		bmp.Draw_cloud(600 - camera_x, 100);
		bmp.Draw_cloud(1000 - camera_x, 50);

		// draw grass 
		bmp.SetBitmap(64, 16, pattern_grass);
		bmp.Draw_grass(100 - camera_x,456);

		// draw mountain
		bmp.SetBitmap(48, 16, pattern_mountain);
		bmp.Draw_mountain(500 - camera_x, 456);

		/////////////////////////////////////////////////////////////
	


	    /////////////////////////////////////////////////////////////
		FsSwapBuffers();

		FsSleep(10);
	}

	return 0;
}