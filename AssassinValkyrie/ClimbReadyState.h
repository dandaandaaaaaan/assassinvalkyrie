// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Zhuang yuteng
// Student Number	: S10163964C

#ifndef _CLIMB_READY_STATE_H                // Prevent multiple definitions if this 
#define _CLIMB_READY_H                // file is included in more than one place
#define WIN32_LEAN_AND_MEAN



#include "PlayerState.h"


namespace CLIMB_READY_STATE
{
	//const int	WIDTH =76;
	//const int	HEIGHT = 97;
	const int	WIDTH = 79;
	const int	HEIGHT = 96;
	const int TEXTURE_COLS = 1;
	const int   START_FRAME = 9;
	const int   END_FRAME = 9;
}



class ClimbReadyState : public PlayerState
{

private:


public:

	ClimbReadyState() :PlayerState() {}
	~ClimbReadyState() {}

	virtual PlayerState* handleInput(Player &player, Input* input, Game *gamePtr, TextureManager *textureM, StageGenerator *floorList, EnemyManager *enemyList, PLATFORM p, Audio *a);


	void update(Player &player, float frameTime)
	{

	}
};
#endif