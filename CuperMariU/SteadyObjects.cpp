#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <array>

#include "fssimplewindow.h"
#include "SteadyObjects.h"

void DrawRect(int x1,int y1,int x2,int y2,int fill)
{
    if(0 != fill) {
        glBegin(GL_QUADS);
    }
    else {
        glBegin(GL_LINE_LOOP);
    }

    glVertex2i(x1,y1);
    glVertex2i(x2,y1);
    glVertex2i(x2,y2);
    glVertex2i(x1,y2);

    glEnd();
}

// This function is not used currently
int CheckCollision(int tx,int ty,int tw,int th,
                    int x1,int y1, int w, int h)
{
    /* Check both corners and edges */

    /*
     * p1: x1, y1   p2: x2, y1
     * p3: x1, y2   p4: x2, y2
     */
	auto x2 = x1 + w;
	auto y2 = y1 + h;
	/* p1 */
	auto rx1 = x1 - tx;
	auto ry1 = y1 - ty;
	/* p2 */
	auto rx2 = x2 - tx;
	auto ry2 = y1 - ty;
	/* p3 */
	auto rx3 = x1 - tx;
	auto ry3 = y2 - ty;
	/* p4 */
	auto rx4 = x2 - tx;
	auto ry4 = y2 - ty;

    // must be right or down
	if (0 < rx1 && rx1 < tw && 0 < ry1 && ry1 < th) {
	    // compare p1 and target p4
	    rx1 = tx+tw - x1;
	    ry1 = ty+th - y1;
	    // down
	    if (rx1 >= ry1) {
	        return 3;
	    }
	    // right
        else {
            return 4;
        }
	}
	// left or down
    else if (0 < rx2 && rx2 < tw && 0 < ry2 && ry2 < th) {
        // compare p2 and target p3
        rx2 = x2 - tx;
        ry2 = ty+th - y1;
        // down
	    if (rx2 >= ry2) {
	        return 3;
	    }
	    // left
        else {
            return 2;
        }
	}
	// up or right
    else if (0 < rx3 && rx3 < tw && 0 < ry3 && ry3 < th) {
        // compare p3 and target p2
        rx3 = tx+tw - x1;
        ry3 = y2 - ty;
        // up
	    if (rx3 >= ry3) {
	        return 1;
	    }
	    // right
        else {
            return 4;
        }
	}
	// up or left
    else if (0 < rx4 && rx4 < tw && 0 < ry4 && ry4 < th) {
        // compare p4 and target p1
        rx4 = x2 - tx;
        ry4 = y2 - ty;
	    if (rx4 >= ry4) {
	        return 1;
	    }
        else {
            return 2;
        }
	}
	else {
		return 0;
	}
}

// Return 1 2 3 4 for contacts on different directions
int CheckContact(int tx, int ty, int tw, int th,
                 int x1, int y1, int w, int h)
{
    /*
     * 0: no contact
     * 1: up    (for target's point of view)
     * 2: left
     * 3: down
     * 4: right
     */

    /*
     * me
     * p1: x1, y1   p2: x2, y1
     * p3: x1, y2   p4: x2, y2
     *
     * target
     * p1: tx, ty     p2: tx+tw, ty
     * p3: tx, ty+th  p4: tx+tw, ty+th
     */

	auto x2 = x1 + w;
	auto y2 = y1 + h;
	/* p1 */
	auto rx1 = x1 - tx;
	auto ry1 = y1 - ty;
	/* p2 */
	auto rx2 = x2 - tx;
	auto ry2 = y1 - ty;
	/* p3 */
	auto rx3 = x1 - tx;
	auto ry3 = y2 - ty;
	/* p4 */
	auto rx4 = x2 - tx;
	auto ry4 = y2 - ty;

    // must be right or down
	if (0 <= rx1 && rx1 <= tw && 0 <= ry1 && ry1 <= th) {
	    // compare p1 and target p4
	    rx1 = tx+tw - x1;
	    ry1 = ty+th - y1;
	    // down
	    if (rx1 >= ry1) {
	        return 3;
	    }
	    // right
        else {
            return 4;
        }
	}
	// left or down
    else if (0 <= rx2 && rx2 <= tw && 0 <= ry2 && ry2 <= th) {
        // compare p2 and target p3
        rx2 = x2 - tx;
        ry2 = ty+th - y1;
        // down
	    if (rx2 >= ry2) {
	        return 3;
	    }
	    // left
        else {
            return 2;
        }
	}
	// up or right
    else if (0 <= rx3 && rx3 <= tw && 0 <= ry3 && ry3 <= th) {
        // compare p3 and target p2
        rx3 = tx+tw - x1;
        ry3 = y2 - ty;
        // up
	    if (rx3 >= ry3) {
	        return 1;
	    }
	    // right
        else {
            return 4;
        }
	}
	// up or left
    else if (0 <= rx4 && rx4 <= tw && 0 <= ry4 && ry4 <= th) {
        // compare p4 and target p1
        rx4 = x2 - tx;
        ry4 = y2 - ty;
	    if (rx4 >= ry4) {
	        return 1;
	    }
        else {
            return 2;
        }
	}
	else {
		return 0;
	}
}

Mushrooms::Mushrooms()
{
    int i, L;
    char pattern[] = {
        "     kkkkkk     "
        "   kk..rrrrkk   "
        "  k....rrrr..k  "
        " k....rrrrrr..k "
        " krrrrr....rr.k "
        "kr..rr......rrrk"
        "k....r......rrrk"
        "k....r......rr.k"
        "k....rr....rr..k"
        "kr..rrrrrrrrr..k"
        "krrrkkkkkkkkrr.k"
        " kkk..k..k..kkk "
        "  k...k..k...k  "
        "  k..........k  "
        "   k........k   "
        "    kkkkkkkk    "
    };

    x = 0.0; y = 0.0;
    w = 48; h = 48;
    vx = 0.0;
    //////////////////////
    //////////////////////
    // Change vy
    vy = -700.0;
    //////////////////////
    //////////////////////
    alive = 0;
    generated = 0;
    wid = 16;
    hei = 16;
    L = wid * hei;
    dat = new char [L];
    for (i = 0; i < L; ++i) {
        dat[i] = pattern[i];
    }
}

Mushrooms::~Mushrooms()
{
    CleanUp();
}

void Mushrooms::CleanUp()
{
    if (nullptr != dat) {
        delete [] dat;
    }
    wid = 0; hei = 0; x = 0; y = 0;
    dat = nullptr;
}

void Mushrooms::Draw(int cameraX) const
{
    int pixelperbit = 3;
    glBegin(GL_QUADS);
    int i, j;

    for (i = 0; i < 16; ++i) {
        if (0 == alive) {
            break;
        }
        for (j = 0; j < 16; ++j) {
            switch (dat[i + hei*j]) {
                case 'r':
                    glColor3ub(200,0,5);
                    DrawRect(x+i*pixelperbit-cameraX, y+j*pixelperbit,
                             x+(i+1)*pixelperbit-cameraX, y+(j+1)*pixelperbit,
                             1);
                    break;
                case '.':
                    glColor3ub(255,255,255);
                    DrawRect(x+i*pixelperbit-cameraX, y+j*pixelperbit,
                             x+(i+1)*pixelperbit-cameraX, y+(j+1)*pixelperbit,
                             1);
                    break;
                case 'k':
                    glColor3ub(0,0,0);
                    DrawRect(x+i*pixelperbit-cameraX, y+j*pixelperbit,
                             x+(i+1)*pixelperbit-cameraX, y+(j+1)*pixelperbit,
                             1);
                    break;
                default:
                    break;
            }
        }
    }
    glEnd();
}

void Mushrooms::Move(Tubes tube[], int nTubes,
                     Bricks brick[], int nBricks,
                     QBricks qbrick[], int nQBricks,
                     double dt)
{
    double g;
    int i;

    if (alive) {
        g = -981.0;
        vy -= g*dt;

        //////////////////////////////////////////
        //////////////////////////////////////////
        // Modified several conditions and numbers
        if (y > 504 - h) {
            vy = 0;
            y = 504 - h;
        }
        if (0 <= vx && 150 >= vx && y < (576 - (5*48+72)) +1) {
            vx += 2;
        }
        else if (0 > vx && -150 <= vx) {
            vx -= 2;
        }
        //////////////////////////////////////////
        //////////////////////////////////////////

        for (i = 0; i < nTubes; ++i) {
            if (1 == Contact(&tube[i])) {
                if (vy > 0) {
                    y = tube[i].y - h;
                    vy = 0.0;
                    g = 0;
                }
                break;
            }
            else if (2 == Contact(&tube[i])
                    || 4 == Contact(&tube[i])) {
                vx = -vx;
                break;
            }
        }

        for (i = 0; i < nBricks; ++i) {
            if (brick[i].broken == 0
                && 1 == Contact(&brick[i])) {
                if (vy > 0) {
                    y = brick[i].y - h;
                    vy = 0.0;
                    g = 0;
                }
                break;
            }
            else if (brick[i].broken == 0
                     && (2 == Contact(&brick[i]) || 4 == Contact(&brick[i]))) {
                vx = -vx;
                break;
            }
        }

        for (i = 0; i < nQBricks; ++i) {
            if (1 == Contact(&qbrick[i])) {
                if (vy > 0) {
                    y = qbrick[i].y - h;
                    vy = 0.0;
                    g = 0;
                }
                break;
            }
            else if (2 == Contact(&qbrick[i])
                    || 4 == Contact(&qbrick[i])) {
                vx = -vx;
                break;
            }
        }

        // TRICK!!!
        x += vx*dt/2.0;
        y += vy*dt/2.0;
    }
}

int Mushrooms::Contact(Tubes * tube) const
{
    /* Contact with tube */
    return CheckContact(tube->x, tube->y, tube->w, tube->h,
                        x, y, w, h);
}

int Mushrooms::Contact(Bricks * brick) const
{
    /* Contact with tube */
    return CheckContact(brick->x, brick->y, brick->w, brick->h,
                        x, y, w, h);
}

void Mushrooms::MarioContact(int mx, int my, int mw, int mh)
{
    if (0 != CheckContact(mx, my, mw, mh,
                          x, y, w, h)) {
        alive = 0;
    }
    if (0 == generated && 0 == alive
        && 0 != CheckContact(mx, my, mw, mh, x, y, w, h)
        && (abs((int)mx - (int)x) < (mw/2))) {
        //&& my > ((y+h))
        alive = 1;
        generated = 1;
    }
}

Tubes::Tubes()
{
    int i, L;
    char pattern[] = {
        "kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk"
        "kggggggggggggggggggggggggggggggk"
        "kGGGGGgggggGGGGGGGGGGGGGGGGGGGGk"
        "kgggGGgggggGggGGGGGGGGGGGgGgGggk"
        "kgggGGgggggGggGGGGGGGGGGGGgGgggk"
        "kgggGGgggggGggGGGGGGGGGGGgGgGggk"
        "kgggGGgggggGggGGGGGGGGGGGGgGgggk"
        "kgggGGgggggGggGGGGGGGGGGGgGgGggk"
        "kgggGGgggggGggGGGGGGGGGGGGgGgggk"
        "kgggGGgggggGggGGGGGGGGGGGgGgGggk"
        "kgggGGgggggGggGGGGGGGGGGGGgGgggk"
        "kgggGGgggggGggGGGGGGGGGGGgGgGggk"
        "kgggGGgggggGggGGGGGGGGGGGGgGgggk"
        "kgggGGgggggGggGGGGGGGGGGGgGgGggk"
        "kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk"
        "  kkkkkkkkkkkkkkkkkkkkkkkkkkkk  "
        "  kgggGGggggGggGGGGGGGGGgGgggk  "
        "  kgggGGggggGggGGGGGGGGGGgGggk  "
        "  kgggGGggggGggGGGGGGGGGgGgggk  "
        "  kgggGGggggGggGGGGGGGGGGgGggk  "
        "  kgggGGggggGggGGGGGGGGGgGgggk  "
        "  kgggGGggggGggGGGGGGGGGGgGggk  "
        "  kgggGGggggGggGGGGGGGGGgGgggk  "
        "  kgggGGggggGggGGGGGGGGGGgGggk  "
        "  kgggGGggggGggGGGGGGGGGgGgggk  "
        "  kgggGGggggGggGGGGGGGGGGgGggk  "
        "  kgggGGggggGggGGGGGGGGGgGgggk  "
        "  kgggGGggggGggGGGGGGGGGGgGggk  "
        "  kgggGGggggGggGGGGGGGGGgGgggk  "
        "  kgggGGggggGggGGGGGGGGGGgGggk  "
        "  kgggGGggggGggGGGGGGGGGgGgggk  "
        "  kgggGGggggGggGGGGGGGGGGgGggk  "
    };

    x = 0; y = 0;
    w = 2*48;
    h = 0;
    layers = 0;
    wid = 32;
    hei = 32;
    L = wid * hei;
    dat = new char [L];
    for (i = 0; i < L; ++i) {
        dat[i] = pattern[i];
    }
}

Tubes::~Tubes()
{
    CleanUp();
}

void Tubes::CleanUp()
{
    if (nullptr != dat) {
        delete [] dat;
        wid = 0; hei = 0; x = 0; y = 0;
        dat = nullptr;
    }
}

void Tubes::Draw(int cameraX) const
{
    int i;
    int bsize = 48;
    DrawUpper(cameraX);
    for (i = 0; i < layers-1; ++i) {
        DrawLower(x, y + i*bsize, cameraX);
    }
}

void Tubes::DrawUpper(int cameraX) const
{
    glBegin(GL_QUADS);
    int i, j;

    for (i = 0; i < 32; ++i) { /* horizontal */
        for (j = 0; j < 16; ++j) { /* vertical */
            switch (dat[i + hei*j]) {
                case 'g':
                    glColor3ub(112,202,15);
                    DrawRect(x+i*pixelperbit-cameraX, y+j*pixelperbit,
                             x+(i+1)*pixelperbit-cameraX, y+(j+1)*pixelperbit,
                             1);
                    break;
                case 'G':
                    glColor3ub(22,154,4);
                    DrawRect(x+i*pixelperbit-cameraX, y+j*pixelperbit,
                             x+(i+1)*pixelperbit-cameraX, y+(j+1)*pixelperbit,
                             1);
                    break;
                case 'k':
                    glColor3ub(0,0,0);
                    DrawRect(x+i*pixelperbit-cameraX, y+j*pixelperbit,
                             x+(i+1)*pixelperbit-cameraX, y+(j+1)*pixelperbit,
                             1);
                    break;
                default:
                    break;
            }
        }
    }
    glEnd();
}

void Tubes::DrawLower(int x0, int y0, int cameraX) const
{
    glBegin(GL_QUADS);
    int i, j;

    for (i = 0; i < 32; ++i) { /* horizontal */
        for (j = 16; j < 32; ++j) { /* vertical */
            switch (dat[i + hei*j]) {
                case 'g':
                    glColor3ub(112,202,15);
                    DrawRect(x0+i*pixelperbit-cameraX, y0+j*pixelperbit,
                             x0+(i+1)*pixelperbit-cameraX, y0+(j+1)*pixelperbit,
                             1);
                    break;
                case 'G':
                    glColor3ub(22,154,4);
                    DrawRect(x0+i*pixelperbit-cameraX, y0+j*pixelperbit,
                             x0+(i+1)*pixelperbit-cameraX, y0+(j+1)*pixelperbit,
                             1);
                    break;
                case 'k':
                    glColor3ub(0,0,0);
                    DrawRect(x0+i*pixelperbit-cameraX, y0+j*pixelperbit,
                             x0+(i+1)*pixelperbit-cameraX, y0+(j+1)*pixelperbit,
                             1);
                    break;
                default:
                    break;
            }
        }
    }
    glEnd();
}

void Tubes::UpdateHeight()
{
    h = layers * 48;
}

BrokenBricks::BrokenBricks()
{
    int i, L;
    char pattern[] = {
        "       bbb      "
        "      bkbkb     "
        "     bbbkbbb    "
        "    bbbkbbbk    "
        "    bbkbbbkb    "
        "    bkbkbkb     "
        "     bbbkb      "
        "      bkb       "
        "                "
        "                "
        "                "
        "                "
        "                "
        "                "
        "                "
        "                "
    };

    originalX = 0;
    x = 0, y = 0;
    vx = 100, vy = -500;
    diffy = 0;
    fly = 0;
    wid = 16;
    hei = 16;
    L = wid * hei;
    dat = new char [L];
    for (i = 0; i < L; ++i) {
        dat[i] = pattern[i];
    }
}

BrokenBricks::~BrokenBricks()
{
    CleanUp();
}

void BrokenBricks::CleanUp()
{
    if (nullptr != dat) {
        delete [] dat;
        wid = 0; hei = 0;
        x = 0; y = 0;
        vx = 0, vy = 0;
        dat = nullptr;
    }
}

void BrokenBricks::Draw(int cameraX) const
{
    int i, j;
    int dx;
    glBegin(GL_QUADS);

    if (fly == 1) {
        dx = x - originalX;
        for (i = 0; i < 16; ++i) {
            for (j = 0; j < 16; ++j) {
                switch (dat[i + hei*j]) {
                    case 'b':
                        glColor3ub(213,60,15);
                        DrawRect(x+i*pixelperbit-cameraX,
                                y+j*pixelperbit,
                                x+(i+1)*pixelperbit-cameraX,
                                y+(j+1)*pixelperbit,
                                1);
                        // vertical mirrow
                        DrawRect(x-2*dx+i*pixelperbit-cameraX,
                                y+j*pixelperbit,
                                x-2*dx+(i+1)*pixelperbit-cameraX,
                                y+(j+1)*pixelperbit,
                                1);
                        // horizontal mirrow
                        DrawRect(x+i*pixelperbit-cameraX,
                                y+diffy+j*pixelperbit,
                                x+(i+1)*pixelperbit-cameraX,
                                y+diffy+(j+1)*pixelperbit,
                                1);
                        // vertical and horizontal mirrow
                        DrawRect(x-2*dx+i*pixelperbit-cameraX,
                                y+diffy+j*pixelperbit,
                                x-2*dx+(i+1)*pixelperbit-cameraX,
                                y+diffy+(j+1)*pixelperbit,
                                1);
                        break;
                    case 'k':
                        glColor3ub(0,0,0);
                        DrawRect(x+i*pixelperbit-cameraX,
                                y+j*pixelperbit,
                                x+(i+1)*pixelperbit-cameraX,
                                y+(j+1)*pixelperbit,
                                1);
                        // vertical mirrow
                        DrawRect(x-2*dx+i*pixelperbit-cameraX,
                                y+j*pixelperbit,
                                x-2*dx+(i+1)*pixelperbit-cameraX,
                                y+(j+1)*pixelperbit,
                                1);
                        // horizontal mirrow
                        DrawRect(x+i*pixelperbit-cameraX,
                                y+diffy+j*pixelperbit,
                                x+(i+1)*pixelperbit-cameraX,
                                y+diffy+(j+1)*pixelperbit,
                                1);
                        // vertical and horizontal mirrow
                        DrawRect(x-2*dx+i*pixelperbit-cameraX,
                                y+diffy+j*pixelperbit,
                                x-2*dx+(i+1)*pixelperbit-cameraX,
                                y+diffy+(j+1)*pixelperbit,
                                1);
                        break;
                    default:
                        break;
                }
            }
        }
    }
    glEnd();
}

void BrokenBricks::Move(double dt)
{
    double g;

    if (fly) {
        g = -981;
        vy -= g*dt;
        diffy += 5;
        if (0 <= vx && 200 >= vx) {
            vx += 2;
        }
        else if (0 >= vx && -200 <= vx) {
            vx -= 2;
        }
        x += vx*dt;
        y += vy*dt;
    }
    if (y > 576) {
        fly = 0;
        diffy = 0;
        vx = 100;
        vy = -500;
    }
}

Bricks::Bricks()
{
    int i, L;
    char pattern[] = {
        "yyyyyyyyyyyyyyyy"
        "bbbbbbbkbbbbbbbk"
        "bbbbbbbkbbbbbbbk"
        "kkkkkkkkkkkkkkkk"
        "bbbkbbbbbbbkbbbb"
        "bbbkbbbbbbbkbbbb"
        "bbbkbbbbbbbkbbbb"
        "kkkkkkkkkkkkkkkk"
        "bbbbbbbkbbbbbbbk"
        "bbbbbbbkbbbbbbbk"
        "bbbbbbbkbbbbbbbk"
        "kkkkkkkkkkkkkkkk"
        "bbbkbbbbbbbkbbbb"
        "bbbkbbbbbbbkbbbb"
        "bbbkbbbbbbbkbbbb"
        "kkkkkkkkkkkkkkkk"
    };

    w = 48; h = 48;
    shift = 0;
    reachpeak = 0;
    broken = 0;
    wid = 16;
    hei = 16;
    L = wid * hei;
    dat = new char [L];
    for (i = 0; i < L; ++i) {
        dat[i] = pattern[i];
    }
}

Bricks::~Bricks()
{
    CleanUp();
}

void Bricks::CleanUp(void)
{
    if (nullptr != dat) {
        delete [] dat;
        wid = 0; hei = 0;
        x = 0; y = 0;
        dat = nullptr;
    }
}

void Bricks::Draw(int cameraX) const
{
    int i, j;
    glBegin(GL_QUADS);

    if (broken == 0) {
        for (i = 0; i < 16; ++i) {
            for (j = 0; j < 16; ++j) {
                switch (dat[i + hei*j]) {
                    case 'y':
                        glColor3ub(251,221,194);
                        DrawRect(x+i*pixelperbit-cameraX, y+j*pixelperbit,
                                 x+(i+1)*pixelperbit-cameraX, y+(j+1)*pixelperbit,
                                 1);
                        break;
                    case 'b':
                        glColor3ub(213,60,15);
                        DrawRect(x+i*pixelperbit-cameraX, y+j*pixelperbit,
                                 x+(i+1)*pixelperbit-cameraX, y+(j+1)*pixelperbit,
                                 1);
                        break;
                    case 'k':
                        glColor3ub(0,0,0);
                        DrawRect(x+i*pixelperbit-cameraX, y+j*pixelperbit,
                                 x+(i+1)*pixelperbit-cameraX, y+(j+1)*pixelperbit,
                                 1);
                        break;
                    default:
                        break;
                }
            }
        }
    }
    glEnd();
}

int Bricks::MarioContact(int mx, int my, int mw, int mh,
                         std::string ms, int m_isFalling,
                         Coins coin[], BrokenBricks brokenbrick[])
{
    int block_hit_x = -1;
    if (1 == CheckContact(mx, my, mw, mh,
                          x, y, w, h)
        && (abs(mx - x) < (mw/2))
        //////////////////////
        //////////////////////
        && m_isFalling == 0) {
        //////////////////////
        //////////////////////




        // Brick should shift up and send x, y position to Monster class
        // Monster_on_bricks_hit(x, y);
        shift = 1;

        /////////////////////////////////////////
        /////////////////////////////////////////
        if (HaveNCoins <= 0 && HaveNCoins > -2) {
            --HaveNCoins;
        }
        /////////////////////////////////////////
        /////////////////////////////////////////

        /////////////////////////////////////////
        /////////////////////////////////////////
        if (broken == 0 && !ms.compare("super") && HaveNCoins == -2) {
        /////////////////////////////////////////
        /////////////////////////////////////////
            broken = 1;
            if (brokenbrick->fly == 0) {
                brokenbrick->fly = 1;
                brokenbrick->x = x;
                brokenbrick->originalX = x;
                brokenbrick->y = y;
            }
        }

        if (0 < HaveNCoins && 0 == coin[0].exist) {
            coin[0].CoinFly(x, y);
            --HaveNCoins;
        }

        block_hit_x = x;

    }

    if (1 == shift) {
        ShiftUp();
    }

    return block_hit_x;
}

void Bricks::ShiftUp(void)
{
    ///////////////////
    ///////////////////
    int shiftspeed = 6;
    ///////////////////
    ///////////////////

    if (y > y_peak && 0 == reachpeak) {
        y -= shiftspeed;
    }
    else {
        y += shiftspeed;
    }

    if (y == y_original) {
        shift = 0;
        reachpeak = 0;
    }

    if (y <= y_peak) {
        reachpeak = 1;
    }
}

StairBricks::StairBricks()
{
    int i, L;
    char pattern[] = {
        "byyyyyyyyyyyyyyk"
        "ybyyyyyyyyyyyykk"
        "yybyyyyyyyyyykkk"
        "yyybyyyyyyyykkkk"
        "yyyybbbbbbbbkkkk"
        "yyyybbbbbbbbkkkk"
        "yyyybbbbbbbbkkkk"
        "yyyybbbbbbbbkkkk"
        "yyyybbbbbbbbkkkk"
        "yyyybbbbbbbbkkkk"
        "yyyybbbbbbbbkkkk"
        "yyyybbbbbbbbkkkk"
        "yyykkkkkkkkkbkkk"
        "yykkkkkkkkkkkbkk"
        "ykkkkkkkkkkkkkbk"
        "kkkkkkkkkkkkkkkb"
    };

    w = 48; h = 48;
    wid = 16;
    hei = 16;
    L = wid * hei;
    dat = new char [L];
    for (i = 0; i < L; ++i) {
        dat[i] = pattern[i];
    }
}

StairBricks::~StairBricks()
{
    CleanUp();
}

void StairBricks::CleanUp(void)
{
    if (nullptr != dat) {
        delete [] dat;
        wid = 0; hei = 0;
        x = 0; y = 0;
        dat = nullptr;
    }
}

void StairBricks::Draw(int cameraX) const
{
    int i, j, k=0;
    glBegin(GL_QUADS);
    while(k<((576-y-72)/48)){
    for (i = 0; i < 16; ++i) {
        for (j = 0; j < 16; ++j) {
            switch (dat[i + hei*j]) {
                case 'y':
                    glColor3ub(251,221,194);
                    DrawRect(x+i*pixelperbit-cameraX, y+48*k+j*pixelperbit,
                            x+(i+1)*pixelperbit-cameraX, y+48*k+(j+1)*pixelperbit,
                            1);
                    break;
                case 'b':
                    glColor3ub(213,60,15);
                    DrawRect(x+i*pixelperbit-cameraX, y+48*k+j*pixelperbit,
                            x+(i+1)*pixelperbit-cameraX, y+48*k+(j+1)*pixelperbit,
                            1);
                    break;
                case 'k':
                    glColor3ub(0,0,0);
                    DrawRect(x+i*pixelperbit-cameraX, y+48*k+j*pixelperbit,
                            x+(i+1)*pixelperbit-cameraX, y+48*k+(j+1)*pixelperbit,
                            1);
                    break;
                default:
                    break;
            }
        }
    }
    ++k;
    }
    glEnd();
}

QBricks::QBricks()
{
    int i, L;
    char pattern[] = {
        "kooooooooooooook"
        "oyyyyyyyyyyyyyyk"
        "oykyyyyyyyyyykyk"
        "oyyyyoooooyyyyyk"
        "oyyyookkkooyyyyk"
        "oyyyookyyookyyyk"
        "oyyyookyyookyyyk"
        "oyyyykkyoookyyyk"
        "oyyyyyyookkkyyyk"
        "oyyyyyyookyyyyyk"
        "oyyyyyyykkyyyyyk"
        "oyyyyyyooyyyyyyk"
        "oyyyyyyookyyyyyk"
        "oykyyyyykkyyykyk"
        "oyyyyyyyyyyyyyyk"
        "kkkkkkkkkkkkkkkk"
    };

    w = 48; h = 48;
    shift = 0;
    reachpeak = 0;
    fixed = 0;
    patternchanged = 0;
    wid = 16;
    hei = 16;
    L = wid * hei;
    dat = new char [L];
    for (i = 0; i < L; ++i) {
        dat[i] = pattern[i];
    }
}

QBricks::~QBricks()
{
    CleanUp();
}

void QBricks::CleanUp(void)
{
    if (nullptr != dat) {
        delete [] dat;
        wid = 0; hei = 0;
        x = 0; y = 0;
        dat = nullptr;
    }
}

void QBricks::Draw(int cameraX) const
{
    int i, j;
    glBegin(GL_QUADS);

    if (0 == patternchanged) {
        for (i = 0; i < 16; ++i) {
            for (j = 0; j < 16; ++j) {
                switch (dat[i + hei*j]) {
                    case 'y':
                        glColor3ub(253,147,49);
                        DrawRect(x+i*pixelperbit-cameraX, y+j*pixelperbit,
                                x+(i+1)*pixelperbit-cameraX, y+(j+1)*pixelperbit,
                                1);
                        break;
                    case 'o':
                        glColor3ub(218,71,19);
                        DrawRect(x+i*pixelperbit-cameraX, y+j*pixelperbit,
                                x+(i+1)*pixelperbit-cameraX, y+(j+1)*pixelperbit,
                                1);
                        break;
                    case 'k':
                        glColor3ub(0,0,0);
                        DrawRect(x+i*pixelperbit-cameraX, y+j*pixelperbit,
                                x+(i+1)*pixelperbit-cameraX, y+(j+1)*pixelperbit,
                                1);
                        break;
                    default:
                        break;
                }
            }
        }
    }
    else {
        for (i = 0; i < 16; ++i) {
            for (j = 0; j < 16; ++j) {
                switch (dat[i + hei*j]) {
                    case 'b':
                        glColor3ub(218,71,19);
                        DrawRect(x+i*pixelperbit-cameraX, y+j*pixelperbit,
                                x+(i+1)*pixelperbit-cameraX, y+(j+1)*pixelperbit,
                                1);
                        break;
                    case 'k':
                        glColor3ub(0,0,0);
                        DrawRect(x+i*pixelperbit-cameraX, y+j*pixelperbit,
                                x+(i+1)*pixelperbit-cameraX, y+(j+1)*pixelperbit,
                                1);
                        break;
                    default:
                        break;
                }
            }
        }
    }
    glEnd();
}

int QBricks::MarioContact(int mx, int my, int mw, int mh,
                          int m_isFalling, Coins coin[])
{
    int block_hit_x = -1;
    if (1 == CheckContact(mx, my, mw, mh,
                          x,  y, w, h)
        && (abs(mx - x) < (mw/2))
        && m_isFalling == 0) {
        // Brick should shift up and send x, y position to Monster class
        //Monster_on_bricks_hit(x, y);
        shift = 1;
        ChangePattern();
        patternchanged = 1;

        /////////////////////////////////////////
        /////////////////////////////////////////
        if (HaveNCoins <= 0 && HaveNCoins > -2) {
            --HaveNCoins;
        }
        /////////////////////////////////////////
        /////////////////////////////////////////

        if (0 < HaveNCoins && 0 == coin[0].exist) {
            coin[0].CoinFly(x, y);
            --HaveNCoins;
        }

        block_hit_x = x;
    }

    if (1 == shift && 0 == fixed) {
        ShiftUp();
    }


    return block_hit_x;
}

void QBricks::ShiftUp(void)
{
    int shiftspeed = 2;

    if (y > y_peak && 0 == reachpeak) {
        y -= shiftspeed;
    }
    else {
        y += shiftspeed;
    }

    if (y == y_original) {
        shift = 0;
        reachpeak = 0;
        fixed = 1;
    }

    if (y <= y_peak) {
        reachpeak = 1;
    }

}

void QBricks::ChangePattern(void)
{
    int i, L;
    char pattern[] = {
        " kkkkkkkkkkkkkk "
        "kbbbbbbbbbbbbbbk"
        "kbkbbbbbbbbbbkbk"
        "kbbbbbbbbbbbbbbk"
        "kbbbbbbbbbbbbbbk"
        "kbbbbbbbbbbbbbbk"
        "kbbbbbbbbbbbbbbk"
        "kbbbbbbbbbbbbbbk"
        "kbbbbbbbbbbbbbbk"
        "kbbbbbbbbbbbbbbk"
        "kbbbbbbbbbbbbbbk"
        "kbbbbbbbbbbbbbbk"
        "kbbbbbbbbbbbbbbk"
        "kbkbbbbbbbbbbkbk"
        "kbbbbbbbbbbbbbbk"
        " kkkkkkkkkkkkkk "
    };

    w = 48; h = 48;
    wid = 16;
    hei = 16;
    L = wid * hei;
    dat = new char [L];
    for (i = 0; i < L; ++i) {
        dat[i] = pattern[i];
    }
}

Coins::Coins()
{
    int i, L;
    char pattern[] = {
        "     kkkkkk     "
        "   kkk...kkkk   "
        "  kk..yyyyykk   "
        "  k.yy...kyykk  "
        " kk.yy.yykyykk  "
        " k.yyy.yykyyykk "
        " k.yyy.yykyyykk "
        " k.yyy.yykyyykk "
        " k.yyy.yykyyykk "
        " k.yyy.yykyyykk "
        " k.yyy.yykyyykk "
        " kk.yy.yykyykk  "
        "  k.yykkkkyykk  "
        "  kk.yyyyyykk   "
        "   kkkyyykkkk   "
        "     kkkkkk     "
    };

    x = 0; y = 0;
    w = 48; h = 48;
    exist = 0;
    wid = 16;
    hei = 16;
    L = wid * hei;
    dat = new char [L];
    for (i = 0; i < L; ++i) {
        dat[i] = pattern[i];
    }
}

Coins::~Coins()
{
    CleanUp();
}

void Coins::CleanUp(void)
{
    if (nullptr != dat) {
        delete [] dat;
        wid = 0; hei = 0; x = 0; y = 0;
        dat = nullptr;
    }
}

void Coins::Draw(int cameraX)
{
    if (exist) {
        int i, j;
        glBegin(GL_QUADS);
        ShiftUp();

        for (i = 0; i < 16; ++i) {
            for (j = 0; j < 16; ++j) {
                switch (dat[i + hei*j]) {
                    case 'k':
                        glColor3ub(0,0,0);
                        DrawRect(x+i*pixelperbit-cameraX, y+j*pixelperbit,
                                x+(i+1)*pixelperbit-cameraX, y+(j+1)*pixelperbit,
                                1);
                        break;
                    case 'y':
                        glColor3ub(242,220,15);
                        DrawRect(x+i*pixelperbit-cameraX, y+j*pixelperbit,
                                x+(i+1)*pixelperbit-cameraX, y+(j+1)*pixelperbit,
                                1);
                        break;
                    case '.':
                        glColor3ub(255,255,255);
                        DrawRect(x+i*pixelperbit-cameraX, y+j*pixelperbit,
                                x+(i+1)*pixelperbit-cameraX, y+(j+1)*pixelperbit,
                                1);
                        break;
                    default:
                        break;
                }
            }
        }
        glEnd();
    }
}

void Coins::CoinFly(int flyx, int flyy)
{
    if (0 == exist) {
        exist = 1;
        x = flyx;
        y = flyy;
        y_peak = flyy - 3*48;
    }
}

void Coins::ShiftUp(void)
{
    int shiftspeed = 8;

    if (y > y_peak) {
        y -= shiftspeed;
    }
    else {
        exist = 0;
    }
}

//void Coins::MarioContact(int mx, int my, int mw, int mh)
//{
    //if (0 != CheckContact(mx, my, mw, mh,
                          //x,  y, 48, 48)) {
        //exist = 0;
    //}
//}

void Objects::Init(void)
{
    int i;
    int brickx[] = { 21, 23, 25, 78, 80,
                     81, 82, 83, 84, 85, 86, 87, 88,
                     92, 93, 94, 95,101,102,119,
                    122,123,124,129,132,
                    130,131,168,169,171};
    int bricky[] = {  4,  4,  4,  4,  4,
                      8,  8,  8,  8,  8,  8,  8,  8,
                      8,  8,  8,  4,  4,  4,  4,
                      8,  8,  8,  8,  8,
                      4,  4,  4,  4,  4};
    /*int stairbrickx[] = {191,192,192,193,193,193,194,194,194,194,
                         195,195,195,195,195,196,196,196,196,196,196,
                         197,197,197,197,197,197};*/
    int stairbrickx[] = {191,192,193,194,195,196,197};
    /*int stairbricky[] = {  1,  1,  2,  1,  2,  3,  1,  2,  3,  4,
                           1,  2,  3,  4,  5,  1,  2,  3,  4,  5,  6,
                           1,  2,  3,  4,  5,  6};*/
    int stairbricky[] = {1,2,3,4,5,6,6};
    int tubex[] = { 28, 38, 46, 57,135,151,163,179};
    int tubel[] = {  2,  3,  4,  4,  3,  3,  2,  2};  // layers
    int qbrickx[] = { 22, 24, 23, 79, 95,
                     107,110,113,110,130,
                     131,170};
    int qbricky[] = {  4,  4,  8,  4,  8,
                       4,  4,  4,  8,  8,
                       8,  4};

    mushroom.x = 22*48;
    mushroom.y = 576 - (4*48+72);

    // init bricks
    i = 0;
    for (auto &b : brick) {
        b.x = brickx[i]*48;
        b.y = 576 - (bricky[i]*48+72);
        b.y_original = b.y;
        b.y_peak = b.y - b.h/2;
        //////////////////////////////
        //////////////////////////////
        b.HaveNCoins = 0;
        //////////////////////////////
        //////////////////////////////
        ++i;
    }
    //brick[1].HaveNCoins = 2;
    //brick[2].HaveNCoins = 3;
    //brick[3].HaveNCoins = 5;

    i = 0;
    for (auto &s : stairbrick) {
        s.x = stairbrickx[i]*48;
        s.y = 576 - (stairbricky[i]*48+72);
        ++i;
    }
    // init coins
    // don't need them now
	//i = 0;
	//for (auto &c : coin) {
		//c.x = (i+3)*48;
		//c.y = 1*48;
		//i++;
	//}

    // init tubes
    i = 0;
    for (auto &t : tube) {
        t.layers = tubel[i];
        t.x = tubex[i]*48;
        t.y = 576 - (t.layers*48+72);
        t.UpdateHeight();
        ++i;
    }

    i = 0;
    for (auto &q : qbrick) {
        q.x = qbrickx[i]*48;
        q.y = 576 - (qbricky[i]*48+72);
        q.y_original = q.y;
        q.y_peak = q.y - q.h/2;
        q.HaveNCoins = 1;
        ++i;
    }
    qbrick[0].HaveNCoins = 0;


    // Test code, just ignore them
    //int brickx[] = {1,1,1,1,1,
                    //1,1,1,1,1,1,1,1,
                    //1,1,1,1,1,1,1,
                    //1,1,1,1,1,
                    //1,1,1,1};

    //for (i = 0; i < 16; ++i) {
        //auto &b = brick[i];
        //b.x = i * 48;
        //b.y = 11*48;
        //b.y_original = b.y;
        //b.y_peak = b.y - b.h/2;
    //}
}

///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
int Objects::Contact(int mx, int my, int mw, int mh,
                     std::string ms, int m_isFalling)
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
{
    std::array<int, 42> block_hit_xS;
    int i = 0;
    int block_hit_x = 0;

    ///////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////
    for (auto &b : brick) {
        block_hit_xS[i] = b.MarioContact(mx, my, mw, mh,
                                         ms, m_isFalling,
                                         coin, &brokenbrick);
        ++i;
    }
    ///////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////
    for (auto &q : qbrick) {
        block_hit_xS[i] = q.MarioContact(mx, my, mw, mh,
                                         m_isFalling, coin);
        ++i;
    }
    ///////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////

    block_hit_x = *std::max_element(block_hit_xS.begin(), block_hit_xS.end());

    //for (auto &c:coin) {
        //c.MarioContact(mx, my, mw, mh);
    //}

    return block_hit_x;
}

void Objects::MushroomMove(int marioX, int marioY, int marioW, int marioH, double dt)
{
    mushroom.MarioContact(marioX, marioY, marioW, marioH);
    mushroom.Move(tube, nTubes, brick, nBricks, qbrick, nQBricks, dt);
    brokenbrick.Move(dt);
}

void Objects::Draw(int cameraX)
{
    coin[0].Draw(cameraX);

    mushroom.Draw(cameraX);

    for (auto &b : brick) {
        b.Draw(cameraX);
    }

    for (auto &s : stairbrick) {
        s.Draw(cameraX);
    }

    for (auto &t:tube) {
        t.Draw(cameraX);
    }

    for (auto &q : qbrick) {
        q.Draw(cameraX);
    }

    brokenbrick.Draw(cameraX);

}

