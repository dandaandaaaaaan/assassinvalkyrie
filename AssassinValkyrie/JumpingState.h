// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Zhuang yuteng
// Student Number	: S10163964C

#ifndef _JUMPINGING_STATE_H                // Prevent multiple definitions if this 
#define _JUMPINGING_STATE_H                // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

namespace JUMPING_STATE
{
	const int	WIDTH = 65;
	const int	HEIGHT = 96;
	const int TEXTURE_COLS = 14;
	const int   START_FRAME = 42;
	const int   END_FRAME = 55;
	
}

#include "PlayerState.h"
#include "graphics.h"

class JumpingState : public PlayerState
{

private:
	
	float velocityX = 150*cos(45*PI/180);
	float velocityY = -(150*sin(45*PI/180));
	float gravity = 9.81;
	float DestinationTime = 500 / velocityX;
	float TimeInterval = DestinationTime / 50;
	float t = 0;
public:

	JumpingState() :PlayerState() {}
	~JumpingState() {}

	virtual PlayerState* handleInput(Entity &player, Input* input, Game *gamePtr, TextureManager *textureM);

	void update(Entity &player, float frameTime)
	{

			velocityY += gravity*t*frameTime;

			if (player.getJumpRight())
			{
				player.setX(player.getX() + velocityX*frameTime);
				player.setY(player.getY() + velocityY*frameTime);
				t += TimeInterval;

				if (player.getY() > 500)
				{
					velocityY = -(150 * sin(45 * PI / 180));;
					player.setY(500);
					t = 0;
					player.setJumpComplete(true);
					player.setJumpRight(false);
				}
			}

			else if (player.getJumpLeft())
			{
				player.setX(player.getX() - velocityX*frameTime);
				player.setY(player.getY() + velocityY*frameTime);
				t += TimeInterval;

				if (player.getY() > 500)
				{
					velocityY = -(150 * sin(45 * PI / 180));;
					player.setY(500);
					t = 0;
					player.setJumpComplete(true);
					player.setJumpLeft(false);
				}
			}

			
						
	}
};
#endif