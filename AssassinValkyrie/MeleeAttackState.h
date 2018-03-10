// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Zhuang yuteng
// Student Number	: S10163964C

#ifndef _MELEE_ATTACK_STATE_H                // Prevent multiple definitions if this 
#define _MELEE_ATTACK_STATE_H                // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

namespace MELEE_ATTACK_STATE
{
<<<<<<< HEAD
	const int	WIDTH = 116;
	const int	HEIGHT = 97;
=======
	const int	WIDTH = 110;
	const int	HEIGHT = 95;
>>>>>>> 8b6459469d6f061b151308844cec0b5071efad82
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

	virtual PlayerState* handleInput(Player &player, Input* input, Game *gamePtr, TextureManager *textureM, StageGenerator *floorList, EnemyManager *enemyList, PLATFORM p, Audio *a);

	void update(Player &player, float frameTime)
	{

	}
};
#endif