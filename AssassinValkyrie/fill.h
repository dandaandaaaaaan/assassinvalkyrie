// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Daniel Lee Min Qiang
// Student Number	: S10162739H

#ifndef _FILL_H 
#define _FILL_H
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace fillNS
{
	const int	WIDTH = 64;
	const int	HEIGHT = 64;
	const double ROTATION = 0;
	const float SCALE = 1.0f;
	//const int	X = GAME_WIDTH / 2 - WIDTH*SCALE;
	//const int	Y = GAME_HEIGHT / 2 - HEIGHT*SCALE;
	const float SPEED = 100;
	const float MASS = 300.0f;
	const int   TEXTURE_COLS = 1;
	const int   START_FRAME = 0;
	const int   END_FRAME = 0;
}

class Fill : public Entity
{
private:
	int startX;
	int startY;
public:
	// constructor
	Fill();

	// inherited member functions
	bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
	void update(float frameTime, bool moveOn);
	void draw();

	void setStartX(int i);
	void setStartY(int i);
	int getStartX() { return startX; }
	int getStartY() { return startY; }
};
#endif