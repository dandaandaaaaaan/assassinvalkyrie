// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Zhuang yuteng
// Student Number	: S10163964C

#ifndef _STONE_H                 // Prevent multiple definitions if this 
#define _STONE_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace stoneNS
{
	const float WIDTH = 84;                   // image width
	const float HEIGHT = 97;                  // image height
	const float SCALE = 0.2f;
	const float SPEED = 300;                // 200 pixels per second
	const int   STONE_TEXTURE_COLS = 2;           // texture has 8 columns
	const float   STONE_START_FRAME = 13;      // ship1 starts at frame 0
	const float   STONE_END_FRAME = 13;        // ship1 end at frame 0
	const float STONE_ANIMATION_DELAY = 0.2f;    // time between frames

	const int RANGE = 300;	// // Range of stone distraction affected
}

// inherits from Entity class
class Stone : public Entity
{

private:

	float velocityX = 250 * cos(45 * PI / 180);
	float velocityY = -(250 * sin(45 * PI / 180));
	float gravity = 9.81;
	float DestinationTime = (250 * 250 * sin(90 * PI / 180) / gravity) / velocityX;
	float TimeInterval = DestinationTime / 145;
	float t = 0;
	bool throwingRight = true;

public:
	// constructor
	Stone();

	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);
	void damage(WEAPON);
	void setThrowingRight(bool condition)
	{
		throwingRight = condition;
	}

};
#endif

