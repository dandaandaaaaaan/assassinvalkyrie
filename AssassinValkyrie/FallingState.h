// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Zhuang yuteng
// Student Number	: S10163964C

#ifndef _FALLING_STATE_H                // Prevent multiple definitions if this 
#define _FALLING_STATE_H                // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

namespace FALLING_STATE
{
	//const int	WIDTH = 81;
	//const int	HEIGHT = 97;
	const int	WIDTH = 64;
	const int	HEIGHT = 94;
	const int TEXTURE_COLS = 10;
	const int   START_FRAME = 36;
	const int   END_FRAME = 36;
	
}

#include "PlayerState.h"

class FallingState : public PlayerState
{

private:

	float fallingVelocity =150;
	float gravity = 3;
public:

	FallingState() :PlayerState() {}
	~FallingState() {}

	virtual PlayerState* handleInput(Player &player, Input* input, Game *gamePtr, TextureManager *textureM, StageGenerator *floorList, EnemyManager *enemyList, PLATFORM p, Audio *a);

	void update(Player &player, float frameTime)
	{
		fallingVelocity += gravity;
		player.setY(player.getY() + fallingVelocity *frameTime);
		player.setVelocityY(fallingVelocity);
	}
};
#endif