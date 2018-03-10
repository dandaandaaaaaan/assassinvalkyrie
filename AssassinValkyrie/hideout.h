// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Daniel Lee Min Qiang
// Student Number	: S10162739H

#ifndef _HIDEOUT_H 
#define _HIDEOUT_H
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include "MovementComponent.h"

namespace hideoutNS
{
	const int	WIDTH = 32;
	const int	HEIGHT = 64;
	const double ROTATION = 0;
	const float SCALE = 1.0f;
	const int	X = GAME_WIDTH / 2 - WIDTH*SCALE;
	const int	Y = GAME_HEIGHT / 2 - HEIGHT*SCALE;
	const float SPEED = 100;
	const float MASS = 300.0f;
	const int   TEXTURE_COLS = 12;
	const int   FRAME = 10;
	const int   HIDING_FRAME = 11;
}

class Hideout : public Entity
{
private:
	int startX;
	int startY;
	MovementComponent *move;
	int timer;

public:
	// constructor
	Hideout();

	// inherited member functions
	bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
	void update(float frameTime, int direction);
	void draw();

	void setStartX(int i);
	void setStartY(int i);
	int getStartX() { return startX; }
	int getStartY() { return startY; }
	int getTimer() { return timer; }
	void setTimer() {timer = GetTickCount(); }
};
#endif