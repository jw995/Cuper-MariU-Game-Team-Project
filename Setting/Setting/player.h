#ifndef PLAYER_H_IS_INCLUDED
#define PLAYER_H_IS_INCLUDED

class Player {
public:
	int x = 0, y = 500, defaultY = 500;
                     double jumpTimer = 0, timerDefault = 1.0;
	void jump(void);
	void draw(int cameraX) const;
};

#endif