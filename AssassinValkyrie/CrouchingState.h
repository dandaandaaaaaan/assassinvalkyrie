// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Zhuang yuteng
// Student Number	: S10163964C

#ifndef _CROUCHING_STATE_H                // Prevent multiple definitions if this 
#define _CROUCHING_STATE_H                // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

namespace CROUCHING_STATE
{
	const int	WIDTH = 59.5;
	const int	HEIGHT = 95.99;
	const int TEXTURE_COLS = 7;
	const int   START_FRAME = 15;
	const int   END_FRAME = 15;
	
}

#include "PlayerState.h"

class CrouchingState : public PlayerState
{

private:


public:

	CrouchingState() :PlayerState() {}
	~CrouchingState() {}

	virtual PlayerState* handleInput(Player &player, Input* input, Game *gamePtr, TextureManager *textureM, StageGenerator *floorList, EnemyManager *enemyList, PLATFORM p, Audio *a);

	void update(Player &player, float frameTime)
	{
		
	}
};
#endif