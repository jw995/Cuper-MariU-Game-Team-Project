#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include "Ground.h"
#include "yspng.h"
#include "fssimplewindow.h"

inline void  CharBitmap::Draw_quad(int a, int b)
{
	glBegin(GL_QUADS);

	glVertex2i(a, b);
	glVertex2i(a + 3, b);
	glVertex2i(a + 3, b + 3);
	glVertex2i(a, b + 3);

	glEnd();
}

inline void  CharBitmap::Draw_quad1(double a, double b)
{
	glBegin(GL_QUADS);

	glVertex2d(a, b);
	glVertex2d(a + 1.5, b);
	glVertex2d(a + 1.5, b + 1.5);
	glVertex2d(a, b + 1.5);

	glEnd();
}

////////////////////////////////////////////



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

char CharBitmap::GetPixel(int x, int y) const
{
	if (0 <= x && x<wid && 0 <= y && y<hei)
	{
		return dat[y*wid + x];
	}
	return 0;
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

void CharBitmap::Draw_people1(int bias1, int bias2)
{
	char pattern_p1[] =
	{
		"............1......"
		".............1....."
		"..............1111."
		".............111111"
		".....1.......121111"
		"...1111......131111"
		"..1111111111112211."
		"...11111..144111..."
		"...11111114441....."
		"....1111444411....."
		"1111155114111......"
		"5555555511..1......"
		".111115511..1......"
		"....1551...1......."
		"...1551...1........"
		"...151............."
		"...551............."
		"....1.............."
		"....1.............."
	};
	SetBitmap(19, 19, pattern_p1);
	int x, y;
	for (y = 0; y < hei; y++)
	{
		for (x = 0; x < wid; x++)
		{
			double a = 1.5*x + bias1;
			double b = 1.5*y + bias2;
			if ('1' == GetPixel(x, y))
			{
				glColor3ub(100, 12, 14);
				Draw_quad1(a, b);
			}
			else if ('2' == GetPixel(x, y))
			{
				glColor3ub(234, 206, 207);
				Draw_quad1(a, b);
			}
			else if ('3' == GetPixel(x, y))
			{
				glColor3ub(0, 0, 0);
				Draw_quad1(a, b);
			}
			else if ('4' == GetPixel(x, y))
			{
				glColor3ub(77, 33, 66);
				Draw_quad1(a, b);
			}
			else if ('5' == GetPixel(x, y))
			{
				glColor3ub(153, 131, 67);
				Draw_quad1(a, b);
			}
			else
			{
				;
			}
		}
	}
}

void CharBitmap::Draw_people2(int bias1, int bias2)
{
	char pattern_p2[] =
	{
		".................11111.."
		"...............1122111.."
		"...............1232111.."
		".........11....1221111.."
		"...........11..12211111."
		".............1121111111."
		"...........11441..1.1111"
		".......111144411.....111"
		".....11514444411.....111"
		"...1155514444411...1111."
		".1155555514441.1..1111.."
		"15555555514441.1.111...."
		".155555555111.1........."
		"..1555555551..1........."
		"..215555551..1.........."
		"....1555551............."
		"....155551.............."
		".....15551.............."
		"....22151..............."
		"....2..11..............."
		"........1..............."
	};
	SetBitmap(24, 20, pattern_p2);
	int x, y;
	for (y = 0; y < hei; y++)
	{
		for (x = 0; x < wid; x++)
		{
			double a = 1.5*x + bias1;
			double b = 1.5*y + bias2;
			if ('1' == GetPixel(x, y))
			{
				glColor3ub(153, 131, 67);
				Draw_quad1(a, b);
			}
			else if ('2' == GetPixel(x, y))
			{
				glColor3ub(234, 206, 207);
				Draw_quad1(a, b);
			}
			else if ('3' == GetPixel(x, y))
			{
				glColor3ub(0, 0, 0);
				Draw_quad1(a, b);
			}
			else if ('4' == GetPixel(x, y))
			{
				glColor3ub(236, 94, 202);
				Draw_quad1(a, b);
			}
			else if ('5' == GetPixel(x, y))
			{
				glColor3ub(253, 209, 77);
				Draw_quad1(a, b);
			}
			else
			{
				;
			}
		}
	}
}

void CharBitmap::Draw_people3(int bias1, int bias2)
{
	char pattern_p3[] =
	{
		"......................1111."
		".............1......112111."
		".............1......1332111"
		".............1.....12222111"
		".............1.....12221111"
		"..............1144441111111"
		".....555......444414.11111."
		"..5555555555.4444144..11..."
		"55555555555555444144..1...."
		"5555...555555541144........"
		"55........55111444........."
		"..........555554..........."
		".........555555............"
		"......55555555............."
		".....55555555.............."
		"....5555555................"
		"...55555..................."
		"....55....................."
	};
	SetBitmap(27, 18, pattern_p3);
	int x, y;
	for (y = 0; y < hei; y++)
	{
		for (x = 0; x < wid; x++)
		{
			double a = 1.5*x + bias1;
			double b = 1.5*y + bias2;
			if ('1' == GetPixel(x, y))
			{
				glColor3ub(98, 44, 12);
				Draw_quad1(a, b);
			}
			else if ('2' == GetPixel(x, y))
			{
				glColor3ub(153, 99, 67);
				Draw_quad1(a, b);
			}
			else if ('3' == GetPixel(x, y))
			{
				glColor3ub(0, 0, 0);
				Draw_quad1(a, b);
			}
			else if ('4' == GetPixel(x, y))
			{
				glColor3ub(2, 218, 216);
				Draw_quad1(a, b);
			}
			else if ('5' == GetPixel(x, y))
			{
				glColor3ub(186, 254, 254);
				Draw_quad1(a, b);
			}
			else
			{
				;
			}
		}
	}
}

void CharBitmap::Draw_people4(int bias1, int bias2)
{
	char pattern_p4[] =
	{
		"..........................11..."
		"..........................1111."
		"........................221111."
		"..............11.......22211111"
		"..............11......223321111"
		"...............11.....222222111"
		"...............11......2222211."
		"................11111..2221111."
		"..................1111112221..."
		"...............11111111........"
		".............31111111111......."
		"............344111111.11......."
		"....3333333333441111.11........"
		"..33444444444444111..11........"
		"334444444444444441..11........."
		".44433333333344433.111........."
		".333......344333...11.........."
		".........34443................."
		"........34443.................."
		".......34443..................."
		"......34443...................."
		".....34443....................."
		".....4443......................"
		"......43......................."
		"......3........................"
	};
	SetBitmap(31, 25, pattern_p4);
	int x, y;
	for (y = 0; y < hei; y++)
	{
		for (x = 0; x < wid; x++)
		{
			double a = 1.5*x + bias1;
			double b = 1.5*y + bias2;
			if ('1' == GetPixel(x, y))
			{
				glColor3ub(255, 255, 255);
				Draw_quad1(a, b);
			}
			else if ('2' == GetPixel(x, y))
			{
				glColor3ub(247,234,193);
				Draw_quad1(a, b);
			}
			else if ('3' == GetPixel(x, y))
			{
				glColor3ub(0, 0, 0);
				Draw_quad1(a, b);
			}
			else if ('4' == GetPixel(x, y))
			{
				glColor3ub(221,206,132);
				Draw_quad1(a, b);
			}
			else
			{
				;
			}
		}
	}
}

void CharBitmap::Draw_people5(int bias1, int bias2)
{
	char pattern_p5[] =
	{
		"................1..........."
		"..............11......1222.."
		"..............1......112222."
		"..............11....11322222"
		"...............11...11322222"
		"................114411122222"
		"...............44444413322.."
		"..............44444443332..."
		".......33333344444144...2..."
		".......3555555444414....2..."
		"...1111355555544441........."
		"1111111355555554441........."
		"111....335533554..1........."
		"........3333554...1........."
		".........35553...11........."
		"........13533....1.........."
		".......11333.....1.........."
		".......11..................."
		".......11..................."
		"........11.................."
		"........11.................."
		".........11................."
		".........11................."
		"..........11................"
		".........11................."
	};
	SetBitmap(28, 25, pattern_p5);
	int x, y;
	for (y = 0; y < hei; y++)
	{
		for (x = 0; x < wid; x++)
		{
			double a = 1.5*x + bias1;
			double b = 1.5*y + bias2;
			if ('1' == GetPixel(x, y))
			{
				glColor3ub(218, 185, 168);
				Draw_quad1(a, b);
			}
			else if ('2' == GetPixel(x, y))
			{
				glColor3ub(218,2,5);
				Draw_quad1(a, b);
			}
			else if ('3' == GetPixel(x, y))
			{
				glColor3ub(0, 0, 0);
				Draw_quad1(a, b);
			}
			else if ('4' == GetPixel(x, y))
			{
				glColor3ub(232,253,77);
				Draw_quad1(a, b);
			}
			else if ('5' == GetPixel(x, y))
			{
				glColor3ub(236,94,96);
				Draw_quad1(a, b);
			}
			else
			{
				;
			}
		}
	}
}


void CharBitmap::Draw_Mario(int bias1, int bias2)
{
	char pattern_mario[] =
	{
		"......11111..."
		"...111111111.."
		".....3233222.."
		"...3332333232."
		"..33323332232."
		"...2222333322."
		"....3333333..."
		".....2112222.."
		"....222222222."
		".332222222221."
		".333222221111."
		"..33222111111."
		".....111111111"
		".....131311111"
		".22.1111111111"
		".222221111111."
		"..2222221111.."
		"....2222......"
	};
	SetBitmap(14, 20, pattern_mario);
	int x, y;
	for (y = 0; y < hei; y++)
	{
		for (x = 0; x < wid; x++)
		{
			int a = 3*x + bias1;
			int b = 3*y + bias2;
			if ('1' == GetPixel(x, y))
			{
				glColor3ub(255, 69, 0);
				Draw_quad(a, b);
			}
			else if ('2' == GetPixel(x, y))
			{
				glColor3ub(215,105,30);
				Draw_quad(a, b);
			}
			else if ('3' == GetPixel(x, y))
			{
				glColor3ub(255,160,122);
				Draw_quad(a, b);
			}
			else
			{
				;
			}
		}
	}
}


void CharBitmap::Mario_jump(int bias1, int bias2)
{
	char pattern_mario[] =
	{
		"0000011111003333"
		"0000111111111333"
		"0000222332302222"
		"0002323332333222"
		"0002322333233322"
		"0002233332222000"
		"0000033333330000"
		"0022221222212000"
		"0222222122221002"
		"3322222111111002"
		"3330012111313122"
		"0302011111111122"
		"0022211111111122"
		"0222111111100000"
		"0200111100000000"
		"0000000000000000"
	};
	SetBitmap(16, 16, pattern_mario);
	int x, y;
	for (y = 0; y < hei; y++)
	{
		for (x = 0; x < wid; x++)
		{
			int a = 3 * x + bias1;
			int b = 3 * y + bias2;
			if ('1' == GetPixel(x, y))
			{
				glColor3ub(255, 69, 0);
				Draw_quad(a, b);
			}
			else if ('2' == GetPixel(x, y))
			{
				glColor3ub(215, 105, 30);
				Draw_quad(a, b);
			}
			else if ('3' == GetPixel(x, y))
			{
				glColor3ub(255, 160, 122);
				Draw_quad(a, b);
			}
			else
			{
				;
			}
		}
	}
}

void CharBitmap::Draw_background(void)
{
	glColor3ub(2, 103, 218);
	glBegin(GL_QUADS);

	glVertex2i(0, 0);
	glVertex2i(48 * 206, 0);
	glVertex2i(48 * 206, 576);
	glVertex2i(0, 576);

	glEnd();
}

void CharBitmap::Init(void)
{
	const double pi = 3.14159265;
	double theta = 30;
	double theta1 = 60;

	state = 0;
	flag1 = 0;
	flag2 = 0;
	flag3 = 0;
	dt = 0.025;
	vx1 = 400 * cos(theta / 180 * pi);
	vy1 = -400 * sin(theta / 180 * pi);
	vx2 = 400 * cos(theta / 180 * pi);
	vy2 = -400 * sin(theta / 180 * pi);
	vx3 = 400 * cos(theta / 180 * pi);
	vy3 = -400 * sin(theta / 180 * pi);
	vx4 = 400 * cos(theta / 180 * pi);
	vy4 = -400 * sin(theta / 180 * pi);
	vx5 = 400 * cos(theta / 180 * pi);
	vy5 = -400 * sin(theta / 180 * pi);
	vmy = -100 * cos(theta1 / 180 * pi);
	vmx = 400 * sin(theta1 / 180 * pi);

	xx1 = 0, yy1 = 0;
	xx2 = 0, yy2 = 0;
	xx3 = 0, yy3 = 0;
	xx4 = 0, yy4 = 0;
	xx5 = 0, yy5 = 0;
	mx = 0, my = 0;
	mmx = 0, mmy = 0;
	
	time_t t = time(NULL);
	srand(time(NULL));

	for (int i = 0; i < 20; i++)
	{
		cloud_x[i] = rand() % 9889;
		cloud_y[i] = rand() % 180;
	}
}

void CharBitmap::Draw_everything(int camera_x)
{
	// draw ground 
	for (int bias_x = 0; bias_x < 48 * 215; bias_x = bias_x + 48)
	{
		if (bias_x != 48 * gap[0] &&
			bias_x != 48 * gap[1] &&
			bias_x != 48 * gap[2] &&
			bias_x != 48 * gap[3] &&
			bias_x != 48 * gap[4] &&
			bias_x != 48 * gap[5] &&
			bias_x != 48 * gap[6])
		{
			Draw_ground(bias_x - camera_x, 504);
			Draw_ground(bias_x - camera_x, 552);
		}
	}

	// draw cloud
	Draw_cloud(300 - camera_x, 30);
	for (int i = 0; i < 20; i++)
	{
		Draw_cloud(cloud_x[i] - camera_x, cloud_y[i]);
	}

	// draw grass_l
	Draw_grass(100 - camera_x, 456);
	Draw_grass(25 * 48 - camera_x, 456);

	// draw mountain
	Draw_mountain(500 - camera_x, 456);
	Draw_mountain(80 * 48 - camera_x, 456);
	Draw_mountain(125 * 48 - camera_x, 456);
	Draw_mountain(160 * 48 - camera_x, 456);
	Draw_mountain(202 * 48 - camera_x, 456);
}

void CharBitmap::Move1(void)
{
	xx1 += vx1*dt;
	yy1 += vy1*dt;
	vy1 += 800*dt;
}

void CharBitmap::Move2(void)
{
	xx2 += vx2*dt;
	yy2 += vy2*dt;
	vy2 += 800*dt;
}

void CharBitmap::Move3(void)
{
	xx3 += vx3*dt;
	yy3 += vy3*dt;
	vy3 += 800*dt;
}


void CharBitmap::Move4(void)
{
	xx4 += vx4*dt;
	yy4 += vy4*dt;
	vy4 += 800*dt;
}

void CharBitmap::Move5(void)
{
	xx5 += vx5*dt;
	yy5 += vy5*dt;
	vy5 += 800*dt;
}


void CharBitmap::Move_mario(void)
{
	mx += 3;
	my += 6;
}

void CharBitmap::Bounce_mario(void)
{
	mx += 3;
	my -= 7;
}

void CharBitmap::Jump_mario(void)
{
	double ddt = 0.015;
	mmx += vmx*ddt;
	mmy += vmy*ddt;
	vmy += 1000 * ddt;
}

void CharBitmap::Draw_transit(int camera_x, int player_x)
{
	// here should change when player_x is not camera_x
	// change to (player_x >= 48*196) then the player won't appear all of a sudden
	if (player_x > 48 * 196 && flag3 == 0)
	{
		Jump_mario();
		// draw mario jump to walk to sky
		// change last block of the stair to 196*48 instead of 190*48!!
		// and the height is 6 blocks instead of 8!!!
		Mario_jump(196 * 48 + mmx -camera_x, 168 +mmy);
	}
	if (196 * 48 + mmx > 9538)
	{
		flag3 = 1;
	}
}


// draw 5 people and mario
void CharBitmap::Draw_move(int camera_x, int player_x)
{
	// draw slide down
	if (player_x < 48 * 190 && state==0)
	{
		Draw_people1(9555 - camera_x, 235);
		Draw_people2(9576 - camera_x, 270);
		Draw_people3(9603 - camera_x, 317);
		Draw_people4(9632 - camera_x, 363);
		Draw_people5(9660 - camera_x, 417);
	}
	else
	{
		state = 1;
	}
	if (state == 1)
	{
		Draw_people1(9555 + xx1 - camera_x, 235 + yy1);
		Draw_people2(9576 + xx2 - camera_x, 270 + yy2);
		Draw_people3(9603 + xx3 - camera_x, 317 + yy3);
		Draw_people4(9632 + xx4 - camera_x, 363 + yy4);
		Draw_people5(9660 + xx5 - camera_x, 417 + yy5);
	}

	if (9538 + mx < 9875 && flag3 == 1)
	{
		Draw_Mario(9538 + mx - camera_x, 220 + my);
	}
	if (9538 + mx > 9875)
	{
		Draw_Mario(9875 - camera_x, 410);
	}
	
}

///////////////////////////////////////////////////////////
void Texture::draw_sth(int x, int y, GLuint texId, int wid, int hei)
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

void Texture::set_texture(GLuint &texId, YsRawPngDecoder png)
{
	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D
	(GL_TEXTURE_2D,0,GL_RGBA,png.wid,png.hei,
		0,GL_RGBA,GL_UNSIGNED_BYTE,png.rgba);
}

void Texture::Init(void)
{
	png[0].Decode("pngs/hunt.png");
	png[1].Decode("pngs/wean.png");
	png[2].Decode("pngs/museum.png");
	png[3].Decode("pngs/walk.png");
	png[4].Decode("pngs/cloud_m.png");
	png[5].Decode("pngs/cloud_l.png");
	png[6].Decode("pngs/grass_m.png");
	png[7].Decode("pngs/grass_s.png");
	png[8].Decode("pngs/wean_on.png");
	png[9].Decode("pngs/hunt_off.png");
	png[10].Decode("pngs/fence.png");
	png[11].Decode("pngs/shoot.png");
	png[12].Decode("pngs/soji1.png");
	png[13].Decode("pngs/soji2.png");
	png[14].Decode("pngs/startmenu.png");
	png[15].Decode("pngs/die.png");

	for (int i = 0; i < 16; ++i)
		set_texture(texId[i], png[i]);
}

void Texture::Draw_texture(int camera_x)
{
	int wid, hei;
	FsGetWindowSize(wid, hei);
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
	if (camera_x > 130 * 48)
	{
		draw_sth(139 * 48 - camera_x, 312, texId[0], 256 * 1.5, 128 * 1.5);
	}
	else
	{
		draw_sth(139 * 48 - camera_x, 312, texId[9], 256 * 1.5, 128 * 1.5);
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
	draw_sth(61 * 48 - camera_x, 288, texId[2], 240 * 1.5, 144 * 1.5);
	// draw walking to sky
	draw_sth(198 * 48 - camera_x, 216, texId[11], 144 * 1.5, 192 * 1.5);
	// draw fence
	draw_sth(100 * 48 - camera_x, 360, texId[10], 480 * 1.5, 96 * 1.5);
	// draw grass_s
	draw_sth(20 * 48 - camera_x, 456, texId[7], 96, 48);
	draw_sth(42 * 48 - camera_x, 456, texId[7], 96, 48);
	draw_sth(58 * 48 - camera_x, 456, texId[7], 96, 48);
	draw_sth(98 * 48 - camera_x, 456, texId[7], 96, 48);
	draw_sth(34 * 48 - camera_x, 456, texId[7], 96, 48);
	draw_sth(166 * 48 - camera_x, 456, texId[7], 96, 48);
	// draw grass_m
	draw_sth(191 * 48 - camera_x, 456, texId[6], 144, 48);
	draw_sth(72 * 48 - camera_x, 456, texId[6], 144, 48);
	draw_sth(115 * 48 - camera_x, 456, texId[6], 144, 48);

	glDisable(GL_TEXTURE_2D);
}

void Texture::Draw_GameMenu(void)
{
	int wid, hei;
	FsGetWindowSize(wid, hei);
	glViewport(0, 0, wid, hei);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, (float)wid - 1, (float)hei - 1, 0, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glColor4d(1.0, 1.0, 1.0, 1.0);

	glEnable(GL_TEXTURE_2D);

	draw_sth(0, 0, texId[14], 768, 576);
	glDisable(GL_TEXTURE_2D);
}

void Texture::Draw_Dead(void)
{
	int wid, hei;
	FsGetWindowSize(wid, hei);
	glViewport(0, 0, wid, hei);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, (float)wid - 1, (float)hei - 1, 0, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glColor4d(1.0, 1.0, 1.0, 1.0);

	glEnable(GL_TEXTURE_2D);

	draw_sth(0, 0, texId[15], 768, 576);
	glDisable(GL_TEXTURE_2D);
}

void Texture::Draw_soji(int camera_x)
{
	int wid, hei;
	FsGetWindowSize(wid, hei);
	glViewport(0, 0, wid, hei);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, (float)wid - 1, (float)hei - 1, 0, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glColor4d(1.0, 1.0, 1.0, 1.0);

	glEnable(GL_TEXTURE_2D);

	// draw soji
	if (9538 + temp < 9875)
	{
		draw_sth(206 * 48 - camera_x, 264, texId[12], 25 * 4, 60 * 4);
	}
	else
	{
		draw_sth(206 * 48 - camera_x, 264, texId[13], 25 * 4, 60 * 4);
	}
	glDisable(GL_TEXTURE_2D);
}

void Draw_edding(int &player_x, int &camera_x, CharBitmap &bmp, Texture &TX)
{
	// camera auto move on
	if (player_x > 196 * 48)
	{
		camera_x += 6;
	}

	// jump mario
	bmp.Draw_transit(camera_x, player_x);

	// slide mario
	if (bmp.flag3 == 1)
	{
		bmp.Move1();
		bmp.Move_mario();

		if (bmp.my + 220 > 270)
		{
			bmp.Move2();
		}
		if (bmp.my + 220 > 317)
		{
			bmp.Move3();
		}
		if (bmp.my + 220 > 363)
		{
			bmp.Move4();
		}
		if (bmp.my + 220 > 417)
		{
			bmp.flag2 = 1;
		}
		if (bmp.flag2 == 1)
		{
			bmp.Move5();
		}

		if (bmp.my > 225)
		{
			bmp.flag1 = 1;
		}
		if (bmp.flag1 == 1)
		{
			bmp.Bounce_mario();
		}
	}
	bmp.Draw_move(camera_x, player_x);
	TX.temp = bmp.mx;
	
	// camera auto move off
	if (player_x > 198 * 48)
	{
		camera_x -= 3;
	}
}

