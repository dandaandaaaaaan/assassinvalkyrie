// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Zhuang yuteng
// Student Number	: S10163964C

#ifndef _JUMPINGING_STATE_H                // Prevent multiple definitions if this 
#define _JUMPINGING_STATE_H                // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

namespace JUMPING_STATE
{
	//const int	WIDTH = 81;
	//const int	HEIGHT = 96;
	const int	WIDTH = 65;
	const int	HEIGHT = 95;
	const int TEXTURE_COLS = 10;
	const int   START_FRAME = 30;
	const int   END_FRAME = 39;
}

#include "PlayerState.h"
#include "graphics.h"

class JumpingState : public PlayerState
{

private:

	float velocityX = 250 * cos(45 * PI / 180);
	float velocityY = -(250 * sin(45 * PI / 180));
	float gravity = 9.81;
	float DestinationTime =(250*250*sin(90*PI/180)/gravity) / velocityX;
	float TimeInterval = DestinationTime /145;
	float t = 0;
public:

	JumpingState() :PlayerState() {}
	~JumpingState() {}

	virtual PlayerState* handleInput(Player &player, Input* input, Game *gamePtr, TextureManager *textureM, StageGenerator *floorList, EnemyManager *enemyList, PLATFORM p, Audio *a);

	void update(Player &player, float frameTime)
	{
		velocityY += gravity*t*frameTime;
		player.setVelocityY(velocityY);
		if (player.getJumpRight())
		{
			if (!player.getCollideWall())
				player.setX(player.getX() + velocityX*frameTime);
			else
				velocityX = 0;
			player.setY(player.getY() + velocityY*frameTime);
			t += TimeInterval;
		}

		else if (player.getJumpLeft())
		{
			if (!player.getCollideWall())
				player.setX(player.getX() - velocityX*frameTime);
			else
				velocityX = 0;
			player.setY(player.getY() + velocityY*frameTime);
			t += TimeInterval;
		}
	}
};
#endif