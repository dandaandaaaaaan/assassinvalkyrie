// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Zhuang yuteng
// Student Number	: S10163964C

#ifndef _CROUCH_WALKING_STATE_H                // Prevent multiple definitions if this 
#define _CROUCH_WALKING_STATE_H                // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

namespace CROUCH_WALKING_STATE
{
	const int	WIDTH = 59.5;
	const int	HEIGHT = 95.99;
	const int TEXTURE_COLS = 7;
	const int   START_FRAME = 16;
	const int   END_FRAME = 20;
	const int CROUCH_WALKING_SPEED = 100;

}

#include "PlayerState.h"

class CrouchWalkingState : public PlayerState
{

private:


public:

	CrouchWalkingState() :PlayerState() {}
	~CrouchWalkingState() {}

	virtual PlayerState* handleInput(Player &player, Input* input, Game *gamePtr, TextureManager *textureM ,StageGenerator *floorList);

	void update(Player &player, float frameTime, bool playerInput)
	{
		if (playerInput) {
			VECTOR2 velocity = player.getVelocity();
			player.setX(player.getX() + (velocity.x) *frameTime);
		}
	}
};
#endif