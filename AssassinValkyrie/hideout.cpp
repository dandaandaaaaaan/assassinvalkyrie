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
	velocity.x = 100;
	velocity.y = 100;
	currentFrame = startFrame;
	edge = RECT{ (long)(-hideoutNS::WIDTH*hideoutNS::SCALE / 2), (long)(-hideoutNS::HEIGHT*hideoutNS::SCALE / 2), (long)(hideoutNS::WIDTH*hideoutNS::SCALE / 2), (long)(hideoutNS::HEIGHT*hideoutNS::SCALE / 2) };
	collisionType = entityNS::BOX;
	timer = GetTickCount();
}

bool Hideout::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM)
{
	move = new MovementComponent(this);
	//health = new HealthComponent();
	//move = new MovementComponent(&(spriteData.x), &(spriteData.y), trooperNS::SPEED, 0);
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void Hideout::update(float frameTime, int direction)
{
	Entity::update(frameTime);

	move->movementWithDirection(frameTime, direction);
}


void Hideout::draw()
{
	Image::draw();              // draw ship
}

void Hideout::setStartX(int i)
{
	startX = i;
}

void Hideout::setStartY(int i)
{
	startY = i;
}