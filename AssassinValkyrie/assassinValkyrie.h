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
#include "gunner.h"
#include "cursor.h"
#include "Player.h"
#include"weaponManager.h"
#include "stageGenerator.h"
#include "background.h"
#include "rayCasting.h"
#include "enemyBulletManager.h"
#include "enemyManager.h"
#include "stageGenerator.h"
#include "background.h"
#include "dashboard.h"
#include "textDX.h"
#include "keyBinding.h"
#include <vector>
#include <thread>

class AssassinValkyrie : public Game
{
private:
	TextureManager	mouseTextures;
	TextureManager	trooperTexture;
	TextureManager	gunnerTexture;
	TextureManager	serpantTexture;
	TextureManager	healthTexture;
	Cursor			*mouse;
	EnemyManager	emList;
	EnemyBulletManager	emBulletList;
	PLATFORM		visionPlatforms;
	PLATFORM		sidePlatforms;
	PLATFORM		floorPlatforms;

	TextureManager	playerTextures;
	Player *player;
	WeaponManager weaponManager;
	TextureManager backgroundTexture;

	int	currentStage;
	Background		*background;
	StageGenerator	*stageGenerator;
	TextureManager	floorTexture;
	Hideout			*tempChar;
	TextureManager	bulletTextures;

	TextureManager	pickupTextures;

	Dashboard *dashboard;
	TextDX *text;
	TextDX *displayTimer;
	KeyBinding *key;

public:
    AssassinValkyrie();
    virtual ~AssassinValkyrie();

	void initialize(Game &gamePtr, HWND *hwndM, HRESULT *hrM, LARGE_INTEGER *timeStartM, LARGE_INTEGER *timeEndM,
		LARGE_INTEGER *timerFreqM, float *frameTimeM, bool *paused, Cursor *cursor, KeyBinding *key);
    // Initialize the game
    void update();      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
    void render();      // "
    void releaseAll();
    void resetAll();

	void setPause(bool value) { paused = value; }
	bool getPause() { return paused; }

	int mins;
	int secs;
	int milliSec;

};

#endif
