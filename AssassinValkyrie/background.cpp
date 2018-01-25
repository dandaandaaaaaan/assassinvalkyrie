// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Daniel Lee Min Qiang
// Student Number	: S10162739H

#include "background.h"

Background::Background() : Entity()
{
	spriteData.width = backgroundNS::WIDTH;           // size of Ship1
	spriteData.height = backgroundNS::HEIGHT;
	spriteData.rect.bottom = backgroundNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = backgroundNS::WIDTH;
	spriteData.y = -720;
	i = 0;
	centre = false;
	velocity.x = 100;
	velocity.y = 100;
	currentFrame = startFrame;
	edge = RECT{ (long)(-backgroundNS::WIDTH*backgroundNS::SCALE / 2), (long)(-backgroundNS::HEIGHT*backgroundNS::SCALE / 2), (long)(backgroundNS::WIDTH*backgroundNS::SCALE / 2), (long)(backgroundNS::HEIGHT*backgroundNS::SCALE / 2) };
	collisionType = entityNS::BOX;
}

bool Background::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM)
{
	//health = new HealthComponent();
	//move = new MovementComponent(&(spriteData.x), &(spriteData.y), trooperNS::SPEED, 0);
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void Background::update(float frameTime, Entity *player, StageGenerator *stageGen)
{
	/*
	player->setVelocity(VECTOR2(50, 50));
	bool lr = false;
	bool ud = false;
	if (input->isKeyDown(SHIP_LEFT_KEY))
	{
		spriteData.x += frameTime * velocity.x;         // move ship along X 
		lr = true;
	}
	if (input->isKeyDown(SHIP_RIGHT_KEY))
	{
		spriteData.x += frameTime * (-velocity.x);         // move ship along X 
		lr = true;
	}
	if (lr) {
		stageGen->update(frameTime, true, 0, true);
		lr = false;
	}

	if (input->isKeyDown(SHIP_UP_KEY))
	{
		spriteData.y += frameTime * velocity.y;         // move ship along X 
		ud = true;
	}

	if (input->isKeyDown(SHIP_DOWN_KEY))
	{
		spriteData.y += frameTime * (-velocity.y);         // move ship along X 
		ud = true;
	}
	if (ud) {
		stageGen->update(frameTime, false, 0, true);
	}
	if (spriteData.x > 0)
	{
		spriteData.x = 0;
		stageGen->update(frameTime, false, 2, false);
	}
	if (spriteData.x < -160)
	{
		spriteData.x = -160;
		stageGen->update(frameTime, false, 1, false);
	}
	if (spriteData.y < -720)
	{
		spriteData.y = -720;
		stageGen->update(frameTime, false, 3, false);
	}
	if (spriteData.y > 0)
	{
		spriteData.y = 0;
		stageGen->update(frameTime, false, 4, false);
	}
	*/
	
	float a = player->getX() - spriteData.x;
	float b = player->getY() - spriteData.y;
	bool leftSide = (a) > ((GAME_WIDTH / 2) );
	bool rightSide = (a) > (backgroundNS::WIDTH - (GAME_WIDTH / 2) );
	bool bottom = (b) < (GAME_HEIGHT + (GAME_HEIGHT/2));
	bool top = (b) > ( GAME_HEIGHT- (GAME_HEIGHT / 2));
	if (spriteData.y > 0) {
		velocity.y = 0;
		spriteData.y = 0;
		stageGen->update(frameTime, false, 4, false);
		player->setVelocity(VECTOR2(50, 50));
	}
	else if (spriteData.y < -720) {
		velocity.y = 0;
		spriteData.y = -720;
		stageGen->update(frameTime, false, 3, false);
		player->setVelocity(VECTOR2(50, 50));
	}
	if ((spriteData.x >= 0)) {
		velocity.x = 0;
		spriteData.x = 0;
		stageGen->update(frameTime, false, 2, false);
		player->setVelocity(VECTOR2(50, 50));
	}
	else if (spriteData.x <= -160) {
		velocity.x = 0;
		spriteData.x = -160;
		stageGen->update(frameTime, false, 1, false);
		player->setVelocity(VECTOR2(50, 50));

	}

	if (top && bottom && leftSide && rightSide){
		player->setVelocity(VECTOR2(0, 0));
		velocity.x = 100;
		velocity.y = 100;
		if (input->isKeyDown(SHIP_LEFT_KEY))
		{
			spriteData.x += frameTime * velocity.x;         // move ship along X 
		}
		if (input->isKeyDown(SHIP_RIGHT_KEY))
		{
			spriteData.x += frameTime * (-velocity.x);         // move ship along X 
		}
		stageGen->update(frameTime, true, 0, true);

		if (input->isKeyDown(SHIP_UP_KEY))
		{
			spriteData.y += frameTime * velocity.y;         // move ship along X 
		}

		if (input->isKeyDown(SHIP_DOWN_KEY))
		{
			spriteData.y += frameTime * (-velocity.y);         // move ship along X 
		}
		stageGen->update(frameTime, false, 0, true);

	}
	else if (top && bottom) {
		if (player->getVelocity() == VECTOR2(50, 0) || player->getVelocity() == VECTOR2(50, 50))
			player->setVelocity(VECTOR2(50, 0));
		else
			player->setVelocity(VECTOR2(0, 0));
		velocity.y = 100;
		if (input->isKeyDown(SHIP_UP_KEY))
		{
			spriteData.y += frameTime * velocity.y;         // move ship along X 
		}

		else if (input->isKeyDown(SHIP_DOWN_KEY))
		{
			spriteData.y += frameTime * (-velocity.y);         // move ship along X 
		}
		stageGen->update(frameTime, false, 0, true);
	}
	else if (leftSide && rightSide)
	{
		if (player->getVelocity() == VECTOR2(0, 50) || player->getVelocity() == VECTOR2(50, 50))
			player->setVelocity(VECTOR2(0, 50));
		else
			player->setVelocity(VECTOR2(0, 0));		

		velocity.x = 100;
		if (input->isKeyDown(SHIP_LEFT_KEY))
		{
			spriteData.x += frameTime * velocity.x;         // move ship along X 
		}

		else if (input->isKeyDown(SHIP_RIGHT_KEY))
		{
			spriteData.x += frameTime * (-velocity.x);         // move ship along X 
		}
		stageGen->update(frameTime, true, 0, true);

	}
	else {
		velocity.x = 0;
		velocity.y = 0;
		player->setVelocity(VECTOR2(50, 50));
	}

	//if (player->getX() == 639)
		//player->setX(640);

	Entity::update(frameTime);


	//move->update(frameTime);
}


void Background::draw()
{
	Image::draw();              // draw ship
}