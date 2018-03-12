// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Daniel Lee Min Qiang
// Student Number	: S10162739H

#ifndef _LADDER_H 
#define _LADDER_H
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include "MovementComponent.h"

namespace ladderNS
{
	const int	WIDTH = 64;
	const int	HEIGHT = 64;
	//const int	HEIGHT_MID = 26;
	//const int	HEIGHT_TOP = 20;
	//const int	HEIGHT_BTM = 28;
	const int	FRAME_MID = 0;
	const int	FRAME_TOP = 1;
	const int	FRAME_BTM = 2;
	const double ROTATION = 0;
	const float SCALE = 1.0f;
	const float SPEED = 100;
	const float MASS = 300.0f;
	const int   TEXTURE_COLS = 1;
	const int   START_FRAME = 0;
	const int   END_FRAME = 0;
}

class Ladder : public Entity
{
private:
	int startX;
	int startY;
	MovementComponent *move;
public:
	// constructor
	Ladder();

	// inherited member functions
	bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
	void update(float frameTime, int direction);
	void draw();

	void setStartX(int i);
	void setStartY(int i);
	int getStartX() { return startX; }
	int getStartY() { return startY; }

	MovementComponent *getMove() { return move; }
};
#endif