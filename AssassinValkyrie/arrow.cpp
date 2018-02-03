// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Zhuang yuteng
// Student Number	: S10163964C

#include "arrow.h"

//=============================================================================
// default constructor
//=============================================================================
Arrow::Arrow() : Entity()
{
	spriteData.width = arrowNS::WIDTH;           // size of Ship1
	spriteData.height = arrowNS::HEIGHT;
	spriteData.rect.bottom = arrowNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = arrowNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	frameDelay = arrowNS::ARROW_ANIMATION_DELAY;
	startFrame = arrowNS::ARROW_START_FRAME;     // first frame of ship animation
	endFrame = arrowNS::ARROW_END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	edge = RECT{ (long)(-arrowNS::WIDTH*arrowNS::SCALE / 2), (long)(-arrowNS::HEIGHT*arrowNS::SCALE / 2), (long)(arrowNS::WIDTH*arrowNS::SCALE / 2), (long)(arrowNS::HEIGHT*arrowNS::SCALE / 2) };

	collisionType = entityNS::BOX;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Arrow::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{

	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ship
//=============================================================================
void Arrow::draw()
{
	Image::draw();

}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Arrow::update(float frameTime)
{
	Entity::update(frameTime);

	spriteData.x += frameTime * velocity.x;         // move ship along y

}










