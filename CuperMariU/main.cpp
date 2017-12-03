/*
 * Game title: CuperMariU
 * A group project of course 24-780 @ 17 Fall semester in CMU
 * Group members: Ke Han / Han-Yu Lee / Jia-Yi Wang / Calvin Qiao / 
 *				  Yueh-Han Chuang / Yen-Hsiang Huang
 *
---------------------------------------------------------------------
 *
 * Everyone writes their header comments in their own header files,
 * But I am the assembler so this place is my only choice.
 *
 * Andrew ID: khan1
 * Contact: khan1@andrew.cmu.edu
 * Main work: Code linking / Bug testing / Debugging /
 *            Code transplanting and modifying /
 *            Algorithm designing / Communicating
 *
 * Hope you have fun in this game that costs my sleep for 2 weeks.
 * Infinite respect for group members that cooperated with me.
 *
---------------------------------------------------------------------
 *
 * Main() - Main program of CuperMariU game.
 * 			Load music and sounds.
 * 			Do ending operations.
 */
#include <stdlib.h>
#include <stdio.h>
#include "fssimplewindow.h"
#include "yssimplesound.h"
#include "gamesetting.h"
void run(int width, int height, int mapWidth, int mapHeight) {
	GameSetting CuperMariU;
	YsSoundPlayer player;
	bool if_ending_played = false;
	
	FsOpenWindow(16, 16, width, height, 1);

	player.MakeCurrent();
	player.Start();
	FsChangeToProgramDir();
	YsSoundPlayer::SoundData propeller, jumpNotice, gameover, stageclear;
	propeller.LoadWav("wavs/melody.wav");
	jumpNotice.LoadWav("wavs/smb_jump-small.wav");
	stageclear.LoadWav("wavs/smb_stage_clear.wav");
	gameover.LoadWav("wavs/smb_gameover.wav");

	CuperMariU.init(width, height, mapWidth, mapHeight);
	FsPollDevice();
	while (FsInkey() != FSKEY_ENTER)
	{
		FsPollDevice();
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		CuperMariU.myTexture.Draw_GameMenu();
		FsSwapBuffers();
		FsSleep(CuperMariU.timerDelay);
	}
	while (FsInkey() != FSKEY_ESC)
	{
		if (!if_ending_played)
			player.PlayBackground(propeller);
		FsPollDevice();
		CuperMariU.PassedTime = (double)FsPassedTime()/1000.0;
		auto key = FsInkey();
		if (key == FSKEY_SPACE && CuperMariU.myMario.isJumping == 0 && CuperMariU.myMario.isFalling == 0)
		{
			player.Stop(jumpNotice);
			player.PlayOneShot(jumpNotice);
		}
		CuperMariU.keyPressed(key); 
		CuperMariU.timerFired();

		if (CuperMariU.myMario.isAlive == 0)
		{
			player.Stop(propeller);
			player.PlayOneShot(gameover);
			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
			CuperMariU.redrawAll(CuperMariU.cameraX);
			FsSwapBuffers();
			FsSleep(1500);
			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
			CuperMariU.myTexture.Draw_Dead();
			FsSwapBuffers();
			FsSleep(2000);
			player.End();
			exit(0);
		}

		if (CuperMariU.myMario.x>=196*48 && !if_ending_played)
		{
			player.Stop(propeller);
			player.PlayOneShot(stageclear);
			if_ending_played = true;
		}
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		CuperMariU.redrawAll(CuperMariU.cameraX);
		FsSwapBuffers();
		FsSleep(CuperMariU.timerDelay);
	}
	player.End();
}

int main()
{

	run(768, 576, 10000, 1000);
	return 0;
}