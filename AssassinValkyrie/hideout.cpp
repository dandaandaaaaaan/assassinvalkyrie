// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Daniel Lee Min Qiang
// Student Number	: S10162739H

#include "hideout.h"

Hideout::Hideout() : Entity()
{
	spriteData.width = hideoutNS::WIDTH;           // size of Ship1a
	spriteData.height = hideoutNS::HEIGHT;
	spriteData.rect.bottom = hideoutNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = hideoutNS::WIDTH;
	velocity.x = 200;
	currentFrame = startFrame;
	edge = RECT{ (long)(-hideoutNS::WIDTH*hideoutNS::SCALE / 2), (long)(-hideoutNS::HEIGHT*hideoutNS::SCALE / 2), (long)(hideoutNS::WIDTH*hideoutNS::SCALE / 2), (long)(hideoutNS::HEIGHT*hideoutNS::SCALE / 2) };
	collisionType = entityNS::BOX;
}

bool Hideout::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM)
{
	//health = new HealthComponent();
	//move = new MovementComponent(&(spriteData.x), &(spriteData.y), trooperNS::SPEED, 0);
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void Hideout::update(float frameTime)
{
	Entity::update(frameTime);

	if (input->isKeyDown(SHIP_LEFT_KEY))
	{
		spriteData.x += frameTime * (-velocity.x);         // move ship along X 
	}
	if (input->isKeyDown(SHIP_RIGHT_KEY))
	{
		spriteData.x += frameTime * velocity.x;         // move ship along X 
	}
	if (input->isKeyDown(SHIP_DOWN_KEY))
		spriteData.y += frameTime * velocity.y;
	if (input->isKeyDown(SHIP_UP_KEY))
		spriteData.y += frameTime * (-velocity.y);
	//move->update(frameTime);
}


void Hideout::draw()
{
	Image::draw();              // draw ship
}