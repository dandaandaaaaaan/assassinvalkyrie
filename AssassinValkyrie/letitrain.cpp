// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Draw animated spaceships with collision and shield
// Chapter 6 spacewar.cpp v1.0
// This class is the core of the game

#include "letitrain.h"


//=============================================================================
// Constructor
//=============================================================================
Letitrain::Letitrain()
{ 
}

//=============================================================================
// Destructor
//=============================================================================
Letitrain::~Letitrain()
{
    releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void Letitrain::initialize(HWND hwnd)
{
	Game::initialize(hwnd);

    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Letitrain::update()
{
	
}


//=============================================================================
// Artificial Intelligence
//=============================================================================
void Letitrain::ai()
{

}

//=============================================================================
// Handle collisions
//=============================================================================
void Letitrain::collisions()
{
    VECTOR2 collisionVector;
	
}

//=============================================================================
// Render game items
//=============================================================================
void Letitrain::render()
{
    graphics->spriteBegin();                // begin drawing sprites

	
    graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Letitrain::releaseAll()
{

    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Letitrain::resetAll()
{

    Game::resetAll();
    return;
}