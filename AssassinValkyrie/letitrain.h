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


//=============================================================================
// This class is the core of the game
//=============================================================================
class Letitrain : public Game
{
private:
    // game items

public:
    // Constructor
    Letitrain();

    // Destructor
    virtual ~Letitrain();

	// Initialize the game
	void initialize(HWND hwnd);
    // Initialize the game
    void update();      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
    void render();      // "
    void releaseAll();
    void resetAll();
};

#endif
