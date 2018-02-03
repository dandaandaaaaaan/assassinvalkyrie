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
	spriteData.y = backgroundNS::Y;
	i = 0;
	centre = false;
	velocity.x = 0;
	currentFrame = startFrame;
	edge = RECT{ (long)(-backgroundNS::WIDTH*backgroundNS::SCALE / 2), (long)(-backgroundNS::HEIGHT*backgroundNS::SCALE / 2), (long)(backgroundNS::WIDTH*backgroundNS::SCALE / 2), (long)(backgroundNS::HEIGHT*backgroundNS::SCALE / 2) };
	collisionType = entityNS::BOX;
	centreX = 640;
	centreY = 360;
	moveOn = true;
}

bool Background::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM)
{
	//health = new HealthComponent();
	//move = new MovementComponent(&(spriteData.x), &(spriteData.y), trooperNS::SPEED, 0);
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void Background::update(float frameTime, Player *player, StageGenerator *stageGen, EnemyManager *emList, EnemyBulletManager *emBulletList, KeyBinding *key)
{

	bool left =false;
	bool right = false;
	//bool onSide = false;
	if (spriteData.x >= 0) {
		left = true;
		//onSide = true;
		spriteData.x = 0;
		stageGen->update(frameTime, 0, 2, false);
	}
	if (spriteData.x <= -2560)
	{
		right = true;
		//onSide = true;
		spriteData.x = -2560;
		stageGen->update(frameTime, 0, 1, false);
	}
	if ((player->getX() < centreX) && !left) {
		if (input->isKeyDown(key->getLeftKey()) && moveOn) {
			velocity.x = 100;
			spriteData.x += frameTime * (velocity.x);         // move ship along X
			stageGen->update(frameTime, 1, 0, true);
			emList->camera(frameTime, 1);
			emBulletList->camera(frameTime, 1);
		}
		if (input->isKeyDown(key->getRangeKey()) && moveOn) {
			velocity.x = 100;
			spriteData.x += frameTime * (-velocity.x);         // move ship along X
			stageGen->update(frameTime, 2, 0, true);
			emList->camera(frameTime, 2);
			emBulletList->camera(frameTime, 2);
		}
		player->setX(centreX);
	}

	if ((player->getX() >= centreX) && !right) {
		if (input->isKeyDown(key->getLeftKey()) && moveOn) {
			velocity.x = 100;
			spriteData.x += frameTime * (velocity.x);         // move ship along X
			stageGen->update(frameTime, 1, 0, true);
			emList->camera(frameTime, 1);
			emBulletList->camera(frameTime, 2);
		}
		if (input->isKeyDown(key->getRightKey()) && moveOn) {
			velocity.x = 100;
			spriteData.x += frameTime * (-velocity.x);         // move ship along X
			stageGen->update(frameTime, 2, 0, true);
			emList->camera(frameTime, 2);
			emBulletList->camera(frameTime, 2);
		}
		player->setX(centreX);
	}

	bool up = false;
	bool down = false;
	if (spriteData.y >= 0) {
		up = true;
		spriteData.y = 0;
		stageGen->update(frameTime, 0, 3, false);
	}
	if (spriteData.y <= -1264) {
		down = true;
		spriteData.y = -1264;
		stageGen->update(frameTime, 0, 4, false);
	}
	bool topLock = false;
	if (up && (right || left))
		topLock = true;
	if ((player->getY() < centreY) && !up && !topLock ) {
		if (player->getVelocityY() >= 0 ){
			velocity.y = 100;
			spriteData.y += frameTime * (-velocity.y);         // move ship along X
			stageGen->update(frameTime, 4, 0, true);
			emList->camera(frameTime, 4);
			emBulletList->camera(frameTime, 4);

		}
		if (player->getVelocityY() < 0 ) {
			velocity.y = 100;
			spriteData.y += frameTime * (velocity.y);         // move ship along X
			stageGen->update(frameTime, 3, 0, true);
			emList->camera(frameTime, 3);
			emBulletList->camera(frameTime, 3);

		}
		player->setY(centreY);
	}
	if ((player->getY() > centreY) && !down && !topLock ) {
		if (player->getVelocityY() > 0) {
			velocity.y = 100;
			spriteData.y += frameTime * (-velocity.y);         // move ship along X
			stageGen->update(frameTime, 4, 0, true);
			emList->camera(frameTime, 4);
			emBulletList->camera(frameTime, 4);

		}
		if (player->getVelocityY() < 0 ) {
			velocity.y = 100;
			spriteData.y += frameTime * (velocity.y);         // move ship along X
			stageGen->update(frameTime, 3 , 0, true);
			emList->camera(frameTime, 3);
			emBulletList->camera(frameTime, 3);

		}
		player->setY(centreY);
	}

	/*	
	bool leftSide = (player->getX() - spriteData.x) > (GAME_WIDTH / 2);
	bool rightSide = (player->getX() - spriteData.x) < (backgroundNS::WIDTH - (GAME_WIDTH / 2));
	bool bottom = (player->getY() - spriteData.y) < (GAME_HEIGHT + (GAME_HEIGHT/2));
	bool top = (player->getY() - spriteData.y ) > ( GAME_HEIGHT- (GAME_HEIGHT / 2));
	
	
	if (top && bottom) 
	{
		if (player->getVelocity() == VECTOR2(100, 0) || player->getVelocity() == VECTOR2(100, 100))
			player->setVelocity(VECTOR2(100, 0));
		else
			player->setVelocity(VECTOR2(0, 0));
		velocity.y = 100;

		if (input->isKeyDown(SHIP_UP_KEY))
		{
			spriteData.y += frameTime * velocity.y;         // move ship along X 
			stageGen->update(frameTime, false, 3, true);
		}

		else if (input->isKeyDown(SHIP_DOWN_KEY))
		{
			spriteData.y += frameTime * (-velocity.y);         // move ship along X 
			stageGen->update(frameTime, false, 4, true);
		}
	}
	
	if (leftSide && rightSide)
	{
		if (player->getVelocity() == VECTOR2(0, 100) || player->getVelocity() == VECTOR2(100, 100))
			player->setVelocity(VECTOR2(0, 100));
		else
			player->setVelocity(VECTOR2(0, 0));		
		velocity.x = 100;
		if (input->isKeyDown(SHIP_LEFT_KEY))
		{
			spriteData.x += frameTime * velocity.x;         // move ship along X 
			stageGen->update(frameTime, true, 0, true);
		}

		else if (input->isKeyDown(SHIP_RIGHT_KEY))
		{
			spriteData.x += frameTime * (-velocity.x);         // move ship along X 
			stageGen->update(frameTime, true, 0, true);
		}
	}
	else {
		if (leftSide)
		{
			stageGen->update(frameTime, false, 1, false);
			if (spriteData.x > 0)
				spriteData.x = 0;
		}
		else if (rightSide)
		{
			stageGen->update(frameTime, false, 2, false);
			if (spriteData.x < -160)
				spriteData.x = -160;
		}
		
		else if (top)
		{
			stageGen->update(frameTime, false, 3, false);
			if (spriteData.y < -720)
				spriteData.y = -720;
		}
		else if (bottom) 
		{
			stageGen->update(frameTime, false, 4, false);
			if (spriteData.y > 0)
				spriteData.y= 0;
		}
		
		velocity.x = 0;
		velocity.y = 0;
		if (spriteData.y > 0)
			spriteData.y = 0;
		player->setVelocity(VECTOR2(100, 100));
	}
	*/
	Entity::update(frameTime);


	//move->update(frameTime);
}


void Background::draw()
{
	Image::draw();              // draw ship
}

void Background::collisions(Player *player, StageGenerator *stageGen)
{
	VECTOR2 collisionVector;
	FILLS *fillCollection = stageGen->getSides();

	for (FILLS::iterator fill = (fillCollection->begin()); fill != fillCollection->end(); fill++)
	{
		if (player->collidesWith(**fill, collisionVector))
		{
			if (!player->isFlipHorizontal())
			{
				player->setX((*fill)->getX() - 80);
			}

			else
			{
				player->setX((*fill)->getX() + 80);
			}
			moveOn = false;
			break;
		}
		else
			moveOn = true;
	}
}