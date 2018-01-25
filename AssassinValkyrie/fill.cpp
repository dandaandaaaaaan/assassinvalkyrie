// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Daniel Lee Min Qiang
// Student Number	: S10162739H

#include "fill.h"

Fill::Fill() : Entity()
{
	spriteData.width = fillNS::WIDTH;           // size of Ship1
	spriteData.height = fillNS::HEIGHT;
	spriteData.rect.bottom = fillNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = fillNS::WIDTH;
	velocity.x = 100;
	velocity.y = 100;
	currentFrame = startFrame;
	//edge = RECT{ (long)(-fillNS::WIDTH*fillNS::SCALE / 2), (long)(-fillNS::HEIGHT*fillNS::SCALE / 2), (long)(fillNS::WIDTH*fillNS::SCALE / 2), (long)(fillNS::HEIGHT*fillNS::SCALE / 2) };
	//collisionType = entityNS::BOX;
}

bool Fill::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM)
{
	//health = new HealthComponent();
	//move = new MovementComponent(&(spriteData.x), &(spriteData.y), trooperNS::SPEED, 0);
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void Fill::update(float frameTime, bool moveOn)
{
	Entity::update(frameTime);
	if (input->isKeyDown(SHIP_LEFT_KEY) && moveOn)
	{
		spriteData.x += frameTime * velocity.x;         // move ship along X 
	}

	if (input->isKeyDown(SHIP_RIGHT_KEY) && moveOn)
	{
		spriteData.x += frameTime * (-velocity.x);         // move ship along X 
	}	
	if (input->isKeyDown(SHIP_UP_KEY) && !moveOn)
		spriteData.y += frameTime * velocity.y;
	if (input->isKeyDown(SHIP_DOWN_KEY) && !moveOn)
		spriteData.y += frameTime * (-velocity.y);
	//move->update(frameTime);
}


void Fill::draw()
{
	Image::draw();              // draw ship
}

void Fill::setStartX(int i)
{
	startX = i;
}

void Fill::setStartY(int i)
{
	startY = i;
}
