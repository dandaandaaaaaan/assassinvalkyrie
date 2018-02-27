// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Zhuang yuteng
// Student Number	: S10163964C

#ifndef _RUNNING_STATE_H                // Prevent multiple definitions if this 
#define _RUNNING_STATE_H                // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

namespace RUNNING_STATE
{
	const int	WIDTH = 79.73;
	const int	HEIGHT = 96;
	const int TEXTURE_COLS = 4;
	const int   START_FRAME = 4;
	const int   END_FRAME = 7;
	const int RUNNING_SPEED=250;
}

#include "PlayerState.h"

class RunningState : public PlayerState
{

private:

	
public:

	RunningState() :PlayerState() {}
	~RunningState() {}

	virtual PlayerState* handleInput(Player &player, Input* input, Game *gamePtr, TextureManager *textureM, StageGenerator *floorList, EnemyManager *enemyList, PLATFORM p, Audio *a);
	
	void update(Player &player, float frameTime)
	{
		VECTOR2 velocity = player.getVelocity();
		player.setX(player.getX() + (velocity.x) *frameTime);
	}
};
#endif