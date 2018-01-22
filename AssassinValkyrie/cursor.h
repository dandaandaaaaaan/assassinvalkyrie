// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Chua Wei Jie Timothy
// Student Number	: S10165581F

#ifndef _CURSOR_COMPONENT_H
#define _CURSOR_COMPONENT_H
#define WIN32_LEAN_AND_MEAN

#include "entity.h"

namespace cursorNS
{
	const int	WIDTH = 22;
	const int	HEIGHT = 32;
	const double ROTATION = 0;
	const float SCALE = 1.0f;
	const int	X = GAME_WIDTH / 2 - WIDTH*SCALE;
	const int	Y = GAME_HEIGHT / 2 - HEIGHT*SCALE;
	const int   TEXTURE_COLS = 1;
	const int   START_FRAME = 0;
	const int   END_FRAME = 0;
	const float ANIMATION_DELAY = 0.0f;
}

class Cursor : public Entity
{
public:
	// constructor
	Cursor();
	void update();
};
#endif
