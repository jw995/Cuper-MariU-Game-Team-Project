// Player.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fssimplewindow.h"
#include "player.h"


void Player::jump(void) {
	if (jumpTimer > 0) {
		if (jumpTimer <= 0) {
			y = defaultY;
		}
		if (jumpTimer > 0.5 * timerDefault) {
			y = defaultY - 50 * (1 - jumpTimer);
		}
		else {
			y = defaultY - 50 * jumpTimer;
		}
	}
}

void Player::draw(int cameraX) const {
	glColor3ub(255, 0, 0);
	glBegin(GL_QUADS);
	glVertex2i(x-10 - cameraX,y);
	glVertex2i(x+10 - cameraX,y);
	glVertex2i(x+10 - cameraX,y-20);
	glVertex2i(x-10 - cameraX,y-20);
	glEnd();
}
