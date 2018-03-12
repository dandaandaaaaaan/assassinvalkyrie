// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Zhuang yuteng
// Student Number	: S10163964C

#ifndef _THROWING_STATE_H                // Prevent multiple definitions if this 
#define _THROWING_STATE_H                // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

namespace THROWING_STATE
{
	const int	WIDTH = 84;
	const int	HEIGHT = 97;
	const int TEXTURE_COLS = 3;
	const int   START_FRAME = 21;
	const int   END_FRAME = 23;

}

#include "PlayerState.h"

class ThrowingState : public PlayerState
{

private:


public:

	ThrowingState() :PlayerState() {}
	~ThrowingState() {}

	virtual PlayerState* handleInput(Player &player, Input* input, Game *gamePtr, TextureManager *textureM, StageGenerator *floorList, EnemyManager *enemyList, PLATFORM p, Audio *a);

	void update(Player &player, float frameTime)
	{

	}
};
#endif