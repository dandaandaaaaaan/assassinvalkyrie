// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Chua Wei Jie Timothy
// Student Number	: S10165581F

#include "enemy.h"

Enemy::Enemy() : Entity()
{
	spriteData.width = trooperNS::WIDTH;           // size of Ship1
	spriteData.height = trooperNS::HEIGHT;
	spriteData.x = trooperNS::X;                   // location on screen
	spriteData.y = trooperNS::Y;
	spriteData.rect.bottom = trooperNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = trooperNS::WIDTH;
	spriteData.angle = trooperNS::ROTATION;
	spriteData.scale = trooperNS::SCALE;

	frameDelay = trooperNS::ANIMATION_DELAY;
	startFrame = trooperNS::START_FRAME;     // first frame of ship animation
	endFrame = trooperNS::END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	edge = RECT{ (long)(-trooperNS::WIDTH*trooperNS::SCALE / 2), (long)(-trooperNS::HEIGHT*trooperNS::SCALE / 2), (long)(trooperNS::WIDTH*trooperNS::SCALE / 2), (long)(trooperNS::HEIGHT*trooperNS::SCALE / 2) };
	collisionType = entityNS::BOX;
}

bool Enemy::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM)
{
	health = new HealthComponent();
	//move = new MovementComponent(&(spriteData.x), &(spriteData.y), trooperNS::SPEED, 0);
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void Enemy::update(float frameTime)
{
	Entity::update(frameTime);

	//move->update(frameTime);
}

// To find closest ship vector position
void Enemy::ai(Entity &ship1, Entity &ship2)
{
}

void Enemy::draw()
{
	Image::draw();              // draw ship
}