// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 spacewar.h v1.0

#ifndef _LETITRAIN_H             // Prevent multiple definitions if this 
#define _LETITRAIN_H             // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#pragma once
#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "enemy.h"
#include "cursor.h"
#include "dashboard.h"
#include "textDX.h"

//Testing
//=============================================================================
// This class is the core of the game
//=============================================================================
class AssassinValkyrie : public Game
{
private:
    // game items
	TextureManager enemyTextures;
	TextureManager mouseTextures;
	Cursor *mouse;
	Enemy *trooper1;
	Dashboard *dashboard;
	TextDX *text;
	TextDX *timer;


public:
    // Constructor
    AssassinValkyrie();

    // Destructor
    virtual ~AssassinValkyrie();

	// Initialize the game
	void initialize(Game &gamePtr, HWND *hwndM, HRESULT *hrM, LARGE_INTEGER *timeStartM, LARGE_INTEGER *timeEndM,
		LARGE_INTEGER *timerFreqM, float *frameTimeM, bool *paused, Cursor *cursor);
    // Initialize the game
    void update();      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
    void render();      // "
    void releaseAll();
    void resetAll();

	void setPause(bool value) { paused = value; }
	bool getPaused() { return paused; }

	int mins;
	int secs;
	int milliSec;
};

#endif
