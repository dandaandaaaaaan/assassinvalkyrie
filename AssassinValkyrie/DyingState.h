// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Zhuang yuteng
// Student Number	: S10163964C

#ifndef _DYING_STATE_H                // Prevent multiple definitions if this 
#define _DYING_STATE_H                // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

namespace DYING_STATE
{
	const int	WIDTH = 97;
	const int	HEIGHT = 97;
	const int TEXTURE_COLS = 10;
	const int   START_FRAME = 100;
	const int   END_FRAME = 109;
	
}

#include "PlayerState.h"

class DyingState : public PlayerState
{

private:


public:

	DyingState() :PlayerState() {}
	~DyingState() {}

	virtual PlayerState* handleInput(Player &player, Input* input, Game *gamePtr, TextureManager *textureM, StageGenerator *floorList, EnemyManager *enemyList, PLATFORM p, Audio *a);

	void update(Player &player, float frameTime)
	{
	}
};
#endif