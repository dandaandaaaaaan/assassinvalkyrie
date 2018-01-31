// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Zhuang yuteng
// Student Number	: S10163964C

#ifndef _MELEE_ATTACK_STATE_H                // Prevent multiple definitions if this 
#define _MELEE_ATTACK_STATE_H                // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

namespace MELEE_ATTACK_STATE
{
	const int	WIDTH = 111;
	const int	HEIGHT = 96;
	const int TEXTURE_COLS = 5;
	const int   START_FRAME = 20;
	const int   END_FRAME = 24;

}

#include "PlayerState.h"

class MeleeAttackState : public PlayerState
{

private:


public:

	MeleeAttackState() :PlayerState() {}
	~MeleeAttackState() {}

	virtual PlayerState* handleInput(Player &player, Input* input, Game *gamePtr, TextureManager *textureM, StageGenerator *floorList);

	void update(Player &player, float frameTime, bool playerInput)
	{

	}
};
#endif