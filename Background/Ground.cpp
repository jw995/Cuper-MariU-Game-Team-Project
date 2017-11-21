#include <stdio.h>
#include <stdlib.h>
#include "yspng.h"
#include "fssimplewindow.h"
#include <math.h>
#include <ctype.h>
#include "Ground.h"
#include <time.h>


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

//////////////////////////////////////

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
	SetBitmap(16, 16, pattern_ground);
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
	SetBitmap(32, 32, pattern_cloud);
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
	SetBitmap(64, 16, pattern_grass);
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
	SetBitmap(48, 16, pattern_mountain);
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


///////////////////////////////////////////////////////////
void grd::Initialize(void)
{


	int gap[7] = { 69,70,86,87,88,153,154 };

	int cloud_x[20], cloud_y[20];
	for (int i = 0; i < 20; i++)
	{
		cloud_x[i] = rand() % 9889;
		cloud_y[i] = rand() % 180;
	}
}

