// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Zhuang yuteng
// Student Number	: S10163964C

#ifndef _STANDING_STATE_H                // Prevent multiple definitions if this 
#define _STANDING_STATE_H                // file is included in more than one place
#define WIN32_LEAN_AND_MEAN



#include "PlayerState.h"


namespace STANDING_STATE
{
	const int	WIDTH = 57.15;
	const int	HEIGHT = 96;
	const int TEXTURE_COLS = 1;
	const int   START_FRAME = 0;
	const int   END_FRAME = 0;
}



class StandState : public PlayerState
{

private:


public:

	StandState() :PlayerState() {}
	~StandState() {}

	virtual PlayerState* handleInput(Player &player, Input* input, Game *gamePtr, TextureManager *textureM, StageGenerator *floorList);
	

	void update(Player &player,float frameTime, bool playerInput)
	{

	}
};
#endif