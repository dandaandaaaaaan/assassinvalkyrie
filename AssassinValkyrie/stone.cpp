// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Zhuang yuteng
// Student Number	: S10163964C

#include "stone.h"

//=============================================================================
// default constructor
//=============================================================================
Stone::Stone() : Entity()
{
	spriteData.width = stoneNS::WIDTH;           // size of Ship1
	spriteData.height = stoneNS::HEIGHT;
	spriteData.rect.bottom = stoneNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = stoneNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	frameDelay = stoneNS::STONE_ANIMATION_DELAY;
	startFrame = stoneNS::STONE_START_FRAME;     // first frame of ship animation
	endFrame = stoneNS::STONE_END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	edge = RECT{ (long)(-stoneNS::WIDTH*stoneNS::SCALE / 2), (long)(-stoneNS::HEIGHT*stoneNS::SCALE / 2), (long)(stoneNS::WIDTH*stoneNS::SCALE / 2), (long)(stoneNS::HEIGHT*stoneNS::SCALE / 2) };
	collisionType = entityNS::BOX;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Stone::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ship
//=============================================================================
void Stone::draw()
{
	Image::draw();
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Stone::update(float frameTime)
{
	Entity::update(frameTime);

	velocityY += gravity*t*frameTime;

	if (throwingRight == true)
	{
		spriteData.x += velocityX*frameTime;
		spriteData.y += velocityY*frameTime;
		t += TimeInterval;
	}
	
	else
	{
		spriteData.x -= velocityX*frameTime;
		spriteData.y += velocityY*frameTime;
		t += TimeInterval;
	}
}










