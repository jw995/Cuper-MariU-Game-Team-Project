#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <limits>
#include <math.h>

#include "fssimplewindow.h"
#include "Mario.h"
#include "SteadyObjects.h"
#include "monster.h"



double computeDistance(double x0, double y0, double x1, double y1)
{
	return sqrt((x0-x1)*(x0-x1) + (y0-y1)*(y0-y1));
}


Mario::Mario()
{
	wid = 0;
	hei = 0;
	dat = nullptr;
}
Mario::Mario(const Mario &incoming)
{
	wid = 0;
	hei = 0;
	dat = nullptr;
	Set(incoming);
}
Mario &Mario::operator=(const Mario &incoming)
{
	Set(incoming);
	return *this;
}
const char *Mario::GetPointer(void) const
{
	if (nullptr != dat)
	{
		return dat;
	}
	else
	{
		return "";
	}
}
const int Mario::StrLen(void) const
{
	return strlen(GetPointer());
}
void Mario::Set(const Mario &incoming)
{
	if (nullptr != incoming.dat
		&& dat != incoming.dat
		&& GetWidth() != incoming.wid
		&& GetHeight() != incoming.hei)
	{
		CleanUp();

		const int n = strlen(incoming.dat);
		dat = new char[n + 1];
		strcpy(dat, incoming.dat);
		wid = incoming.wid;
		hei = incoming.hei;
	}
}
Mario::~Mario()
{
	CleanUp();
}
void Mario::CleanUp(void)
{
	wid = 0;
	hei = 0;
	if (nullptr != dat)
	{
		delete[] dat;
		dat = nullptr;
	}
}
const int Mario::GetWidth(void) const
{

	return wid;
}
const int Mario::GetHeight(void) const
{

	return hei;
}
void Mario::SetBitmap(int bmpWid, int bmpHei, char bmp[])
{
	wid = bmpWid;
	hei = bmpHei;
	const int n = strlen(bmp);
	dat = new char[n + 1];
	if (nullptr != dat)
	{
		strcpy(dat, bmp);
	}

}
void Mario::SetPixel(int x, int y, char c)
{
	dat[y*wid + x] = c;
}
const char Mario::GetPixel(int x, int y) const
{
	if (0 <= x && x<wid && 0 <= y && y<hei)
	{
		return dat[y*wid + x];
	}
	return 0;
}
void Mario::Print(void) const
{
	int x, y;
	for (y = 0; y<hei; y++)
	{
		for (x = 0; x<wid; x++)
		{
			printf("%c", GetPixel(x, y));
		}
		printf("\n");
	}
}
void Mario::Init(void)
{
	x = 120;
	y = 504; // need to adjust according to window size
	w = 48;
	h = 48;
	jumpheight = 0;
	isAlive = 1;
	spdX = 12;
	spdY = 16;
	facing = 0; // 0 <- face right   1 <- face left
	isJumping = 0; //0 <- not jumping   1 <- jumping
	isFalling = 0;
	isRunning = 0;
	isLanding = 1;	
	collState = 0;
	monState = 0;
	timer = 0;

	state = "normal";
	rightNormalStill =
	{
		// 0 <- white 1 <- red 2 <- brown 3 <- skin
		"0000011111000000"
		"0000111111111000"
		"0000222332300000"
		"0002323332333000"
		"0002322333233300"
		"0002233332222000"
		"0000033333330000"
		"0000221222000000"
		"0002222112200000"
		"0002221131130000"
		"0002222111110000"
		"0001223333330000"
		"0000111122220000"
		"0000222222220000"
		"0000222220000000"
		"0000000000000000"
	};

	rightNormalTransit =
	{
		// 0 <- white 1 <- red 2 <- brown 3 <- skin
		"0000011111000000"
		"0000111111111000"
		"0000222332300000"
		"0002323332333000"
		"0002322333233300"
		"0002233332222000"
		"0000033333330000"
		"0000221221220000"
		"0002221221222000"
		"0022221111222200"
		"0033213113123300"
		"0033311111133300"
		"0033111111113300"
		"0000111001110000"
		"0002220000222000"
		"0222220000222220"
	};

	rightNormalRun = 
	{
		"0000011111000000"
		"0000111111111000"
		"0000222332300000"
		"0002323332333000"
		"0002322333233300"
		"0002233332222000"
		"0000033333330000"
		"0022221122200000"
		"3322221112223333"
		"3333221311122333"
		"3330111111110220"
		"0001111111112220"
		"0011111111112220"
		"0221111001112220"
		"0022220000000000"
		"0000000000000000"
	};

	rightNormalJump =
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

	leftNormalStill =
	{
		// 0 <- white 1 <- red 2 <- brown 3 <- skin
		"0000001111100000"
		"0001111111110000"
		"0000032332220000"
		"0003332333232000"
		"0033323332232000"
		"0002222333322000"
		"0000333333300000"
		"0000002221220000"
		"0000022112222000"
		"0000311311222000"
		"0000111112222000"
		"0000333333221000"
		"0000222211110000"
		"0000222222220000"
		"0000000222220000"
		"0000000000000000"
	};

	leftNormalTransit =
	{
		// 0 <- white 1 <- red 2 <- brown 3 <- skin
		"0000001111100000"
		"0001111111110000"
		"0000032332220000"
		"0003332333232000"
		"0033323332232000"
		"0002222333322000"
		"0000333333300000"
		"0000221221220000"
		"0002221221222000"
		"0022221111222200"
		"0033213113123300"
		"0033311111133300"
		"0033111111113300"
		"0000111001110000"
		"0002220000222000"
		"0222220000222220"
	};

	leftNormalRun =
	{
		"0000001111100000"
		"0001111111110000"
		"0000032332220000"
		"0003332333232000"
		"0033323332232000"
		"0002222333322000"
		"0000333333300000"
		"0000022211222200"
		"3333222111222233"
		"3332211131223333"
		"0220111111110333"
		"0222111111111000"
		"0222111111111100"
		"0222111001111220"
		"0000000000222200"
		"0000000000000000"
	};

	leftNormalJump =
	{
		"3333001111100000"
		"3331111111110000"
		"2222032332220000"
		"2223332333232000"
		"2233323332232000"
		"0002222333322000"
		"0000333333300000"
		"0002122221222200"
		"2001222212222220"
		"2001111112222233"
		"2213131112100333"
		"2211111111102030"
		"0022211111111122"
		"0000011111112220"
		"0000000011110020"
		"0000000000000000"
	};

	NormalDead = 
	{
		"0000002222000000"
		"0002021111202000"
		"0223211111123220"
		"2333232332323332"
		"2331332332331332"
		"2311223333221131"
		"0221323333231220"
		"0002332222332000"
		"0002233223322000"
		"0022223333222200"
		"0211221111221120"
		"0211122112211120"
		"0211123223211120"
		"0211122222211120"
		"0021122222211200"
		"0002200000022000"
	};

	rightSuperTransit = 
	{
		"0000001111100000"
		"0000111111300000"
		"0001111113300000"
		"0001111111111100"
		"0002223323330000"
		"0023323322333300"
		"0023322333333330"
		"0223322333233330"
		"0223333322222200"
		"0222333332222200"
		"0002233333333000"
		"0000233333200000"// end of head, including neck
		"0000212222120000"
		"0000212222120000"
		"0000212222120000"
		"0000212222120000"
		"0000112222110000"
		"0000112222110000"
		"0000112222110000"
		"0000132222310000"
		"0000113333110000"
		"0000113333110000"
		"0000113331110000"
		"0000113311110000"
		"0011111111111100"
		"0111111001111110"
		"0111110000111110"
		"0111110000111110"
		"0022220000222200"
		"0022220000222200"
		"2222220000222222"
		"2222220000222222"
	};

	rightSuperStill =
	{
		// By the way, if you want to define a long string, you can write like this.
		"0000001111100000"
		"0000111111300000"
		"0001111113300000"
		"0001111111111100"
		"0002223323330000"
		"0023323322333300"
		"0023322333333330"
		"0223322333233330"
		"0223333322222200"
		"0222333332222200"
		"0002233333333000"
		"0000233333200000"
		"0000212222120000"
		"0002212222122000"
		"0022212222122200"
		"0222212222122220"
		"0222112222112220"
		"2222112222112222"
		"2222111111112222"
		"2222131111312222"
		"3333111111113333"
		"3333111111113333"
		"0333111111113330"
		"0331111111111330"
		"0011111111111100"
		"0111111001111110"
		"0111110000111110"
		"0111110000111110"
		"0022220000222200"
		"0022220000222200"
		"2222220000222222"
		"2222220000222222"
	};

	rightSuperRun =
	{
		// By the way, if you want to define a long string, you can write like this.
		"0000001111100000"
		"0000111111300000"
		"0001111113300000"
		"0001111111111100"
		"0002223323330000"
		"0023323322333300"
		"0023322333333330"
		"0223322333233330"
		"0223333322222200"
		"0222333332222200"
		"0002233333333000"
		"0000022233000000" // end of head, including neck
		"0000111122100030" //
		"0002222112210333" //
		"0022222211210333" //222122200"
		"0222222211221333" //122220"
		"0222222211221232" //112220"
		"0222222111221220"
		"2222221113123200" //
		"2222111111111000"
		"3333311111111000"
		"3333311111111002"
		"3333111111111022"
		"0333111111122222" //
		"0001211111122222"
		"0021121111122222"
		"2221112211122222"
		"2222111100022222"
		"2222210000000000"
		"0222000000000000"
		"0222000000000000"
		"0022200000000000"
	};

	rightSuperJump =
	{
		// By the way, if you want to define a long string, you can write like this.
		"0000000000003330"
		"0000000000033233"
		"0000011111133223"
		"0000111111133333"
		"0000111111122222"
		"0001111111122222"
		"0001111111111122"
		"0002223323332222"
		"0023323323333322"
		"0023322333333332"
		"0023322333233332"
		"0223333322222220" // end of head, including neck
		"0222233332222320" //
		"0002233333333220" //
		"0000111122122220" //222122200"
		"0222222112122200" //122220"
		"2222222212212200" //112220"
		"2222222211212000"
		"2233222211221000" //
		"2333322111123000"
		"3333321113111000" //
		"3333311111111002"
		"3233111111111022"
		"0331111111111222" //
		"0001111111112222"
		"0002111111112222"
		"2221221111112222"
		"2221112211112222" //
		"2221111100112222"
		"2221111100000000"
		"2221111000000000"
		"2200000000000000"
	};

	leftSuperTransit = 
	{
		"0000011111000000"
		"0000031111110000"
		"0000033111111000"
		"0011111111111000"
		"0000333233222000"
		"0033332233233200"
		"0333333332233200"
		"0333323332233220"
		"0022222233333220"
		"0022222333332220"
		"0003333333322000"
		"0000023333320000"
		"0000212222120000"
		"0002212222122000"
		"0022212222122200"
		"0222212222122220"
		"0222112222112220"
		"2222112222112222"
		"2222111111112222"
		"2222131111312222"
		"3333111111113333"
		"3333111111113333"
		"0333111111113330"
		"0331111111111330"
		"0011111111111100"
		"0111111001111110"
		"0111110000111110"
		"0111110000111110"
		"0022220000222200"
		"0022220000222200"
		"2222220000222222"
		"2222220000222222"
	};

	leftSuperStill =
	{
		// By the way, if you want to define a long string, you can write like this.
		"0000011111000000"
        "0000031111110000"
        "0000033111111000"
        "0011111111111000"
        "0000333233222000"
        "0033332233233200"
        "0333333332233200"
        "0333323332233220"
        "0022222233333220"
        "0022222333332220"
        "0003333333322000"
        "0000023333320000"
        "0000212222110000"
        "0000212222110000"
        "0000111222210000"
        "0000111222210000"
        "0000111222210000"
        "0000111222210000"
        "0000112222110000"
        "0000312222110000"
        "0000113333110000"
        "0000113333110000"
        "0000111333110000"
        "0000111133110000"
        "0000011111110000"
        "0000011111110000"
        "0000001111110000"
        "0000000111110000"
        "0000000022220000"
        "0000000022220000"
        "0000002222220000"
        "0000002222220000"
	};

	leftSuperRun =
	{
		// By the way, if you want to define a long string, you can write like this.
		"0000011111000000"
		"0000031111110000"
		"0000033111111000"
		"0011111111111000"
		"0000333233222000"
		"0033332233233200"
		"0333333332233200"
		"0333323332233220"
		"0022222233333220"
		"0022222333332220"
		"0003333333322000"
		"0000003322200000"
		"0300012211110000"
		"3330122112222000"
		"3330121122222200"
		"3331221122222220"
		"2321221122222220"
		"0221221112222220"
		"0023213111222222"
		"0001111111112222"
		"0001111111133333"
		"2001111111133333"
		"2201111111113333"
		"2222211111113330"
		"2222211111121000"
		"2222211111211200"
		"2222211122111222"
		"2222200011112222"
		"0000000000122222"
		"0000000000002220"
		"0000000000002220"
		"0000000000022200"
	};

	leftSuperJump =
	{
		// By the way, if you want to define a long string, you can write like this.
		"0333000000000000"
		"3323300000000000"
		"3223311111100000"
		"3333311111110000"
		"2222211111110000"
		"2222211111111000"
		"2211111111111000"
		"2222333233222000"
		"2233333233233200"
		"2333333332233200"
		"2333323332233200"
		"0222222233333220"
		"0232222333322220"
		"0223333333322000"
		"0222212211110000"
		"0022212112222220"
		"0022122122222222"
		"0002121122222222"
		"0001221122223322"
		"0003211112233332"
		"0001113111233333"
		"2001111111133333"
		"2201111111113323"
		"2221111111111330"
		"2222111111111000"
		"2222111111112000"
		"2222111111221222"
		"2222111122111222"
		"2222110011111222"
		"0000000011111222"
		"0000000001111222"
		"0000000000000022"
	};
}

void Mario::Draw(int cameraX)
{
	int interval = 1;
	int row, col;
	int hei = GetHeight();
	int	wid = GetWidth();
	int x0, y0;
	int xcellSize, ycellSize;
	int value;

	if (!strcmp(state,"normal"))
	{
		xcellSize = 3;
		ycellSize = 3;
		if (!isAlive)
		{
			SetBitmap(16,16,NormalDead);
		}
		else if (facing == 1)
		{
			if (isJumping || isFalling)
			{
				SetBitmap(16, 16, leftNormalJump);
			}
			else
			{
				if (isRunning == 0)
				{
					SetBitmap(16, 16, leftNormalStill);
				}
				else if (isRunning == 1)
				{
					if (timer < interval)
					{
						SetBitmap(16, 16, leftNormalStill);
						timer++;
					}
					else if (timer >= interval && timer < 2 * interval)
					{
						SetBitmap(16, 16, leftNormalTransit);
						timer++;
					}
					else if (timer >= 2 * interval && timer < 3 * interval)
					{
						SetBitmap(16, 16, leftNormalRun);
						timer++;
					}
					else if (timer >= 3 * interval)
					{
						timer = 0;
					}
				}
			}
		}
		else if (facing == 0)
		{
			if (isJumping || isFalling)
			{
				SetBitmap(16, 16, rightNormalJump);
			}
			else
			{
				if (isRunning == 0)
				{
					SetBitmap(16, 16, rightNormalStill);
				}
				else if (isRunning == 1)
				{
					if (timer < interval)
					{
						SetBitmap(16, 16, rightNormalStill);
						timer++;
					}
					else if (timer >= interval && timer < 2 * interval)
					{
						SetBitmap(16, 16, rightNormalTransit);
						timer++;
					}
					else if (timer >= 2 * interval && timer < 3 * interval)
					{
						SetBitmap(16, 16, rightNormalRun);
						timer++;
					}
					else if (timer >= 3 * interval)
					{
						timer = 0;
					}
				}
			}
		}
	}
	if (!strcmp(state,"super"))
	{
		xcellSize = 3;
		ycellSize = 3;
		if (!isAlive)
		{
			SetBitmap(16,16,NormalDead);
		}
		else if (facing == 1)
		{
			if (isJumping)
			{
				SetBitmap(16, 32, leftSuperJump);
			}
			else
			{
				if (isRunning == 0)
				{
					SetBitmap(16, 32, leftSuperStill);
				}
				else if (isRunning == 1)
				{
					if (timer < interval)
					{
						SetBitmap(16, 32, leftSuperStill);
						timer++;
					}
					else if (timer >= interval && timer < 2 * interval)
					{
						SetBitmap(16, 32, leftSuperTransit);
						timer++;
					}
					else if (timer >= 2 * interval && timer < 3 * interval)
					{
						SetBitmap(16, 32, leftSuperRun);
						timer++;
					}
					else if (timer >= 3 * interval)
					{
						timer = 0;
					}
				}
			}
		}
		else if (facing == 0)
		{
			if (isJumping)
			{
				SetBitmap(16, 32, rightSuperJump);
			}
			else
			{
				if (isRunning == 0)
				{
					SetBitmap(16, 32, rightSuperStill);
				}
				else if (isRunning == 1)
				{
					if (timer < interval)
					{
						SetBitmap(16, 32, rightSuperStill);
						timer++;
					}
					else if (timer >= interval && timer < 2 * interval)
					{
						SetBitmap(16, 32, rightSuperTransit);
						timer++;
					}
					else if (timer >= 2 * interval && timer < 3 * interval)
					{
						SetBitmap(16, 32, rightSuperRun);
						timer++;
					}
					else if (timer >= 3 * interval)
					{
						timer = 0;
					}
				}
			}
		}
	}

	int r = 0, g = 0, b = 0;
	for (row = 0; row < hei; row++)
	{
		for (col = 0; col < wid; col++)
		{
			value = GetPixel(col, row);
			if (value == '0')
			{
				// do nothing
			}
			else if (value == '1')
			{
				r = 255;
				g = 69;
				b = 0;
				glColor3ub(r, g, b);
				glBegin(GL_QUADS);
				x0 = x + col*xcellSize - cameraX;
				y0 = (y - hei*ycellSize) + row*ycellSize;
				glVertex2i(x0, y0);
				glVertex2i(x0 + xcellSize, y0);
				glVertex2i(x0 + xcellSize, y0 + ycellSize);
				glVertex2i(x0, y0 + ycellSize);
				glEnd();
			}
			else if (value == '2')
			{
				//r = 160;
				//g = 82;
				//b = 45;
				r = 215;
				g = 105;
				b = 30;
				glColor3ub(r, g, b);
				glBegin(GL_QUADS);
				x0 = x + col*xcellSize - cameraX;
				y0 = (y - hei*ycellSize) + row*ycellSize;
				glVertex2i(x0, y0);
				glVertex2i(x0 + xcellSize, y0);
				glVertex2i(x0 + xcellSize, y0 + ycellSize);
				glVertex2i(x0, y0 + ycellSize);
				glEnd();
			}
			else if (value == '3')
			{
				//r = 255;
				//g = 250;
				//b = 205;
				r = 255;
				g = 160;
				b = 122;
				glColor3ub(r, g, b);
				glBegin(GL_QUADS);
				x0 = x + col*xcellSize - cameraX;
				y0 = (y - hei*ycellSize) + row*ycellSize;
				glVertex2i(x0, y0);
				glVertex2i(x0 + xcellSize, y0);
				glVertex2i(x0 + xcellSize, y0 + ycellSize);
				glVertex2i(x0, y0 + ycellSize);
				glEnd();
			}
		}
	}
}

void Mario::jump(void)
{
	if (collState == 0)
	{
		jumpheight = 0;
	}
	if (isJumping)
	{
		if (jumpheight < 192)
		{
			y -= spdY;
			jumpheight += spdY;
			isJumping = 1;
			isFalling = 0;
			isLanding = 0;

		}
		else
		{
			isFalling = 1;
			isJumping = 0;
			isLanding = 0;
		}
	}
	else if (isFalling)
	{
		if ((!isLanding) && ((y < 504) || (checkGap() == 1)))
		{
			y += spdY;
			isJumping = 0;
			isLanding = 0;
			isFalling = 1;
		}
		else
		{
			isJumping = 0;
			isFalling = 0;
			isLanding = 1;
			jumpheight = 0;
		}
	}
	else if (isLanding)
	{
		if (checkGap() == 1)
		{
			isJumping = 0;
			isLanding = 0;
			isFalling = 1;
		}
	}
}

int Mario::findCollisionIdx(Bricks B_targets[], int B_num, 
	QBricks QB_targets[], int QB_num, 
	Tubes T_targets[], int T_num, 
	StairBricks SB_targets[], int SB_num)
{
	int xcellSize, ycellSize;
	if (!strcmp(state,"super"))
	{
		xcellSize = 3;
		ycellSize = 3;
	}
	else
	{
		xcellSize = 3;
		ycellSize = 3;
	}
	int mWid = GetWidth()*xcellSize;
	int mHei = GetHeight()*ycellSize;
	int closetIdx = -1, closetDis = -1;
	double centerMarioX, centerMarioY, centerTargetX, centerTargetY;

	for (int i = 0; i < B_num + QB_num + T_num + SB_num; i ++)
	{
		centerMarioX = x + mWid/2;
		centerMarioY = y - mHei/2;
		if (i < B_num)
		{
			if (B_targets[i].broken == 1)
				continue;
			centerTargetX = B_targets[i].x + 48 / 2.0;
			centerTargetY = B_targets[i].y + 48 / 2.0;
		}
		else if (i < B_num + QB_num)
		{
			centerTargetX = QB_targets[i-B_num].x + 48 / 2.0;
			centerTargetY = QB_targets[i-B_num].y + 48 / 2.0;
		}
		else if (i < B_num + QB_num + T_num)
		{
			centerTargetX = T_targets[i-B_num-QB_num].x + T_targets[i-B_num-QB_num].w / 2.0;
			centerTargetY = T_targets[i-B_num-QB_num].y + T_targets[i-B_num-QB_num].h / 2.0;
		}
		else
		{
			centerTargetX = SB_targets[i-B_num-QB_num-T_num].x;
			centerTargetY = 0;
		}
		double dis = computeDistance(centerMarioX, centerMarioY, centerTargetX, centerTargetY);
		if ((dis <= closetDis) || (closetDis == -1))
		{
			closetDis = dis;
			closetIdx = i;
		}
	}
	return closetIdx;
}

int Mario::findMonsterIdx(MonMush M_Mons[], int mush_num, Turtle T_Mons[], int tur_num)
{
	int xcellSize, ycellSize;
	if (!strcmp(state,"super"))
	{
		xcellSize = 3;
		ycellSize = 3;
	}
	else
	{
		xcellSize = 3;
		ycellSize = 3;
	}
	int mWid = GetWidth()*xcellSize;
	int mHei = GetHeight()*ycellSize;
	int closetIdx = -1, closetDis = -1;
	double centerMarioX, centerMarioY, centerTargetX, centerTargetY;
	for (int i = 0; i < mush_num + tur_num; i ++)
	{
		centerMarioX = x + mWid/2;
		centerMarioY = y - mHei/2;
		if (i < mush_num)
		{
			centerTargetX = M_Mons[i].x + 48 / 2.0;
			centerTargetY = M_Mons[i].y + 48 / 2.0;
		}
		else
		{
			centerTargetX = T_Mons[i-mush_num].shell.x + 48 / 2.0;
			centerTargetY = T_Mons[i-mush_num].shell.y + 48 / 2.0;
		}
		double dis = computeDistance(centerMarioX, centerMarioY, centerTargetX, centerTargetY);
		if ((dis < closetDis) || (closetDis == -1))
		{
			closetDis = dis;
			closetIdx = i;
		}
	}
	return closetIdx;
}

void Mario::checkLocalCollision_B(Bricks &target)
{
	int xcellSize, ycellSize;
	if (!strcmp(state,"super"))
	{
		xcellSize = 3;
		ycellSize = 3;
	}
	else
	{
		xcellSize = 3;
		ycellSize = 3;
	}
	int mWid = GetWidth()*xcellSize;
	int mHei = GetHeight()*ycellSize;
	int xTLeft, xTRight, yTUp, yTDown;
	xTLeft = target.x;
	xTRight = target.x + 48;
	yTUp = target.y;
	yTDown = target.y + 48;



	if (x <= xTLeft && xTLeft < x + mWid)
	{
		if ((y <= yTDown && y > yTUp) || (!strcmp(state,"super") && yTDown<=y && yTUp>=y-mHei))
		{
			if (((collState == 2) || (collState == 5)))
			{
				isJumping = 0;
				isFalling = 0;
				isLanding = 1;
				y = yTUp;
				jumpheight = 0;
			}
			else
			{
				x = xTLeft - mWid;
				collState = 1;
			}
			
		}
		else if (y <= yTUp)
		{
			collState = 2;
		}
		else if (y > yTDown)
		{
			if (y - mHei < yTDown)
			{
				isJumping = 0;
				isFalling = 1;
			}
			collState = 3;
		}
	}
	else if (x < xTRight && x + mWid > xTRight)
	{
		if ((y <= yTDown && y > yTUp) || (!strcmp(state,"super") && yTDown<=y && yTUp>=y-mHei))
		{
			if (((collState == 2) || (collState == 5)))
			{
				isJumping = 0;
				isFalling = 0;
				isLanding = 1;
				y = yTUp;
				jumpheight = 0;
			}
			else
			{
				x = xTRight;
				collState = 4;
			}
			
		}
		else if (y <= yTUp)
		{
			collState = 5;
		}
		else if (y > yTDown)
		{
			if (y - mHei < yTDown)
			{
				isJumping = 0;
				isFalling = 1;
			}
			collState = 6;
		}
	}
	else
	{
		collState = 7;
		if (y != 504)
		{
			isLanding = 0;
			isFalling = 1;
		}
	}
}

void Mario::checkLocalCollision_QB(QBricks &target)
{
	int xcellSize, ycellSize;
	if (!strcmp(state,"super"))
	{
		xcellSize = 3;
		ycellSize = 3;
	}
	else
	{
		xcellSize = 3;
		ycellSize = 3;
	}
	int mWid = GetWidth()*xcellSize;
	int mHei = GetHeight()*ycellSize;
	int xTLeft, xTRight, yTUp, yTDown;
	xTLeft = target.x;
	xTRight = target.x + 48;
	yTUp = target.y;
	yTDown = target.y + 48;
	if (x <= xTLeft && xTLeft < x + mWid)
	{
		if ((y <= yTDown && y > yTUp) || (!strcmp(state,"super") && yTDown<=y && yTUp>=y-mHei))
		{
			if (((collState == 2) || (collState == 5)))
			{
				isJumping = 0;
				isFalling = 0;
				isLanding = 1;
				y = yTUp;
				jumpheight = 0;
			}
			else
			{
				x = xTLeft - mWid;
				collState = 1;
			}
			
		}
		else if ((y <= yTUp) )
		{
			collState = 2;
		}
		else if (y > yTDown)
		{
			if (y - mHei < yTDown)
			{
				isJumping = 0;
				isFalling = 1;
			}
			collState = 3;
		}
	}
	else if (x < xTRight && x + mWid > xTRight)
	{
		if ((y <= yTDown && y > yTUp) || (!strcmp(state,"super") && yTDown<=y && yTUp>=y-mHei))
		{
			if (((collState == 2) || (collState == 5)))
			{
				isJumping = 0;
				isFalling = 0;
				isLanding = 1;
				y = yTUp;
				jumpheight = 0;
			}
			else
			{
				x = xTRight;
				collState = 4;
			}
			
		}
		else if (y <= yTUp)
		{
			collState = 5;
		}
		else if (y > yTDown)
		{
			if (y - mHei < yTDown)
			{
				isJumping = 0;
				isFalling = 1;
			}
			collState = 6;
		}
	}
	else
	{
		collState = 7;
		if (y != 504)
		{
			isLanding = 0;
			isFalling = 1;
		}
	}
}

void Mario::checkLocalCollision_T(Tubes &target)
{
	int xcellSize, ycellSize;
	if (!strcmp(state,"super"))
	{
		xcellSize = 3;
		ycellSize = 3;
	}
	else
	{
		xcellSize = 3;
		ycellSize = 3;
	}
	int mWid = GetWidth()*xcellSize;
	int xTLeft, xTRight, yTUp, yTDown;
	xTLeft = target.x;
	xTRight = target.x + target.w;
	yTUp = target.y;
	yTDown = target.y + target.h;

	if (x <= xTLeft && xTLeft < x + mWid)
	{
		if (y <= yTDown && y > yTUp)
		{
			if (((collState == 2) || (collState == 5)))
			{
				isJumping = 0;
				isFalling = 0;
				isLanding = 1;
				y = yTUp;
				jumpheight = 0;
			}
			else
			{
				x = xTLeft - mWid;
				collState = 1;
			}
			
		}
		else if ((y <= yTUp) )
		{
			collState = 2;
		}
	}
	else if (x < xTRight && x + mWid >= xTRight)
	{
		if (y <= yTDown && y > yTUp)
		{
			if (((collState == 2) || (collState == 5)))
			{
				isJumping = 0;
				isFalling = 0;
				isLanding = 1;
				y = yTUp;
				jumpheight = 0;
			}
			else
			{
				x = xTRight;
				collState = 4;
			}
			
		}
		else if (y <= yTUp)
		{
			collState = 5;
		}
	}
	else if (x > xTLeft && x + mWid < xTRight)
	{
		if (y <= yTDown && y > yTUp)
		{
			if (((collState == 2) || (collState == 5)) || (collState == 8))
			{
				isJumping = 0;
				isFalling = 0;
				isLanding = 1;
				y = yTUp;
				jumpheight = 0;
			}
			else
			{
				x = xTRight;
				collState = 4;
			}
			
		}
		else if (y <= yTUp)
		{
			collState = 8;
		}
	}
	else
	{
		collState = 7;
		if (y != 504)
		{
			isLanding = 0;
			isFalling = 1;
		}
	}
}

void Mario::checkLocalCollision_SB(StairBricks &target)
{
	int xcellSize, ycellSize;
	if (!strcmp(state,"super"))
	{
		xcellSize = 3;
		ycellSize = 3;
	}
	else
	{
		xcellSize = 3;
		ycellSize = 3;
	}
	int mWid = GetWidth()*xcellSize;
	int xTLeft, xTRight, yTUp, yTDown;
	xTLeft = target.x;
	xTRight = target.x + target.w;
	yTUp = target.y;
	yTDown = 504;
	if (x <= xTLeft && xTLeft < x + mWid)
	{
		if (y <= yTDown && y > yTUp)
		{
			if (((collState == 2) || (collState == 5)))
			{
				isJumping = 0;
				isFalling = 0;
				isLanding = 1;
				y = yTUp;
				jumpheight = 0;
				collState = 7;
			}
			else
			{
				x = xTLeft - mWid;
				collState = 1;
			}
			
		}
		else if ((y < yTUp) )
		{
			collState = 2;
			if (!isFalling && !isJumping)
			{
				isFalling = 1;
				isJumping = 0;
				isLanding = 0;
			}
		}
	}
	else if (x < xTRight && x + mWid >= xTRight)
	{
		if (y <= yTDown && y > yTUp)
		{
			if (((collState == 2) || (collState == 5)))
			{
				isJumping = 0;
				isFalling = 0;
				isLanding = 1;
				y = yTUp;
				jumpheight = 0;
				collState = 7;
			}
			else
			{
				x = xTRight;
				collState = 4;
			}
			
		}
		else if (y < yTUp)
		{
			collState = 5;
			if (!isFalling && !isJumping)
			{
				isFalling = 1;
				isJumping = 0;
				isLanding = 0;
			}
		}
	}
	else
	{
		collState = 7;
		if (y != 504)
		{
			isLanding = 0;
			isFalling = 1;
		}
	}
}

void Mario::checkCollisionWithMonster(MonMush M_Mons)
{
	int xcellSize, ycellSize;
	if (!strcmp(state,"super"))
	{
		xcellSize = 3;
		ycellSize = 3;
	}
	else
	{
		xcellSize = 3;
		ycellSize = 3;
	}
	int mWid = GetWidth()*xcellSize;
	int mHei = GetHeight()*ycellSize;
	int xTLeft, xTRight, yTUp, yTDown;

	xTLeft = M_Mons.x;
	xTRight = M_Mons.x + 48;
	yTUp = M_Mons.y;
	yTDown = M_Mons.y + 48;

		if (x <= xTLeft && xTLeft < x + mWid)
		{
			if ((y <= yTDown && y > yTUp))
			{
				if (((monState == 2) || (monState == 5)) && M_Mons.dieflip_state == 0)
				{
					isJumping = 1;
					isFalling = 0;
					isLanding = 0;
					y = yTUp;
					jumpheight = 144;
					monState = 7;
				}
				else
				{
					if (M_Mons.dieflip_state == 0)
					{
						isAlive = 0;
						monState = 1;
					}
				}
				
			}
			else if (y < yTUp)
			{
				monState = 2;
			}
			else if (y > yTDown)
			{
				// y> yTDown
				monState = 3;
			}
		}
		else if (x < xTRight && x + mWid > xTRight)
		{
			if ((y <= yTDown && y > yTUp))
			{
				if (((monState == 2) || (monState == 5)) && M_Mons.dieflip_state == 0)
				{
					isJumping = 1;
					isFalling = 0;
					isLanding = 0;
					y = yTUp;
					jumpheight = 144;
					monState = 7;
				}
				else
				{
					if (M_Mons.dieflip_state == 0)
					{
						isAlive = 0;
						monState = 4;
					}
				}
				
			}
			else if (y < yTUp)
			{
				monState = 5;
			}
			else if (y > yTDown)
			{
				monState = 6;
			}
		}
		else
			monState = 7;
	
	
}

void Mario::checkCollisionWithTurtle(Turtle T_Mons)
{
	int xcellSize, ycellSize;
	if (!strcmp(state,"super"))
	{
		xcellSize = 3;
		ycellSize = 3;
	}
	else
	{
		xcellSize = 3;
		ycellSize = 3;
	}
	int mWid = GetWidth()*xcellSize;
	int mHei = GetHeight()*ycellSize;
	int xTLeft, xTRight, yTUp, yTDown;

	xTLeft = T_Mons.shell.x;
	xTRight = T_Mons.shell.x + 48;
	yTUp = T_Mons.shell.y;
	yTDown = T_Mons.shell.y + 48;

	if (x <= xTLeft && xTLeft < x + mWid)
	{
		if ((y <= yTDown && y > yTUp))
		{
			if (((monState == 2) || (monState == 5)))
			{
				isJumping = 1;
				isFalling = 0;
				isLanding = 0;
				y = yTUp;
				jumpheight = 144;
				//monState = 7;
			}
			else
			{
				isAlive = 0;
				monState = 1;
			}				
		}
		else if (y <= yTUp)
		{
			monState = 2;
		}
		else if (y > yTDown)
		{
			// y> yTDown
			monState = 3;
		}
	}
	else if (x < xTRight && x + mWid > xTRight)
	{
		if ((y <= yTDown && y > yTUp))
		{
			if (((monState == 2) || (monState == 5)))
			{
				isJumping = 1;
				isFalling = 0;
				isLanding = 0;
				y = yTUp;
				jumpheight = 144;
				//monState = 7;
			}
			else
			{
				isAlive = 0;
				monState = 4;
			}			
		}
		else if (y <= yTUp)
		{
			monState = 5;
		}
		else if (y > yTDown)
		{
			monState = 6;
		}
	}
}

void Mario::growUp(Mushrooms &target)
{
	if (x<=target.x && x+w >=target.x && y>=target.y && y<=target.y+48 && target.generated)
	{
		state = "super";
		h = 96;
		return;
	}
	if (x<=target.x && x+w >=target.x && y-h>=target.y && y-h<=target.y+48 && target.generated)
	{
		state = "super";
		h = 96;
		return;
	}
	if (x<=target.x+48 && x+w >=target.x+48 && y>=target.y && y<=target.y+48 && target.generated)
	{
		state = "super";
		h = 96;
		return;
	}
	if (x<=target.x+48 && x+w >=target.x+48 && y-h>=target.y && y-h<=target.y+48 && target.generated)
	{
		state = "super";
		h = 96;
		return;
	}
}

int Mario::checkGap()
{
	if (x>69*48 && x<=70*48)
		return 1;
	if (x>86*48 && x<=88*48)
		return 1;
	if (x>153*48 && x<=154*48)
		return 1;
	return 0;
}