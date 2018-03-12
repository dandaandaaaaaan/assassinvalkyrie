// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Zhuang yuteng
// Student Number	: S10163964C

#ifndef _ASSASSINATE_STATE_H                // Prevent multiple definitions if this 
#define _ASSASSINATE_STATE_H                // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

namespace ASSASSINATE_STATE
{
	const int	WIDTH =106;
	const int	HEIGHT = 97;
	const int TEXTURE_COLS = 2;
	const int   START_FRAME = 16;
	const int   END_FRAME = 17;

}

#include "PlayerState.h"

class AssassinateState : public PlayerState
{

private:


public:

	AssassinateState() :PlayerState() {}
	~AssassinateState() {}

	virtual PlayerState* handleInput(Player &player, Input* input, Game *gamePtr, TextureManager *textureM, StageGenerator *floorList, EnemyManager *enemyList, PLATFORM p, Audio *a);

	void update(Player &player, float frameTime)
	{

	}
};
#endif