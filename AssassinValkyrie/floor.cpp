// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Daniel Lee Min Qiang
// Student Number	: S10162739H

#include "floor.h"

Floor::Floor() : Entity()
{
	spriteData.width = floorNS::WIDTH;           // size of Ship1
	spriteData.height = floorNS::HEIGHT;
	spriteData.rect.bottom = floorNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = floorNS::WIDTH;
	velocity.x = 100;
	velocity.y = 25;
	currentFrame = startFrame;
	edge = RECT{ (long)(-floorNS::WIDTH*floorNS::SCALE / 2), (long)(-floorNS::HEIGHT*floorNS::SCALE / 2), (long)(floorNS::WIDTH*floorNS::SCALE / 2), (long)(floorNS::HEIGHT*floorNS::SCALE / 2) };
	collisionType = entityNS::BOX;
	startX = 0;
	startY = 0;
}

bool Floor ::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM)
{
	//health = new HealthComponent();
	//move = new MovementComponent(&(spriteData.x), &(spriteData.y), trooperNS::SPEED, 0);
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void Floor::update(float frameTime, bool moveOn)
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


void Floor::draw()
{
	Image::draw();              // draw ship
}

void Floor::setStartX(int i) 
{
	startX = i;
}

void Floor::setStartY(int i)
{
	startY = i;
}
