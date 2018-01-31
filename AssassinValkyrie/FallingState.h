// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Zhuang yuteng
// Student Number	: S10163964C

#ifndef _FALLING_STATE_H                // Prevent multiple definitions if this 
#define _FALLING_STATE_H                // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

namespace FALLING_STATE
{
	const int	WIDTH = 64;
	const int	HEIGHT = 96;
	const int TEXTURE_COLS = 11;
	const int   START_FRAME = 43;
	const int   END_FRAME = 43;
	const int FALLING_SPEED = 150;
}

#include "PlayerState.h"

class FallingState : public PlayerState
{

private:


public:

	FallingState() :PlayerState() {}
	~FallingState() {}

	virtual PlayerState* handleInput(Player &player, Input* input, Game *gamePtr, TextureManager *textureM, StageGenerator *floorList);

	void update(Player &player, float frameTime, bool playerInput)
	{
		if (playerInput) {
			VECTOR2 velocity = player.getVelocity();
			player.setY(player.getY() + (velocity.y) *frameTime);
		}
	}
};
#endif