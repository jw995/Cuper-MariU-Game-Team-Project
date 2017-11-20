#include <stdio.h>
#include "yspng.h"
#include "fssimplewindow.h"
#include <math.h>
#include <ctype.h>
#include "Ground.h"

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

