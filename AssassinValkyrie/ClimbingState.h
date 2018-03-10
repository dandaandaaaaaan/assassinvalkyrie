// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Zhuang yuteng
// Student Number	: S10163964C

#ifndef _CLIMBING_STATE_H                // Prevent multiple definitions if this 
#define _CLIMBING_STATE_H                // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

namespace CLIMBING_STATE
{
	const int	WIDTH = 76;
	const int	HEIGHT = 97;
	const int TEXTURE_COLS = 3;
	const int   START_FRAME =27;
	const int   END_FRAME = 29;
	const int CLIMBING_SPEED = 150;
}

#include "PlayerState.h"

class ClimbingState : public PlayerState
{

private:


public:

	ClimbingState() :PlayerState() {}
	~ClimbingState() {}

	virtual PlayerState* handleInput(Player &player, Input* input, Game *gamePtr, TextureManager *textureM, StageGenerator *floorList, EnemyManager *enemyList, PLATFORM p, Audio *a);

	void update(Player &player, float frameTime)
	{
		VECTOR2 velocity = player.getVelocity();
		player.setY(player.getY() + (velocity.y) *frameTime);
	}
};
#endif