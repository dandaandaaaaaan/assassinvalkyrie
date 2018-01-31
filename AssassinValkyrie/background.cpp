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
	cameraVelocity = backgroundNS::CAMERA_VELOCITY;
	yes = false;
}

bool Background::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM)
{
	//health = new HealthComponent();
	//move = new MovementComponent(&(spriteData.x), &(spriteData.y), trooperNS::SPEED, 0);
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void Background::update(float frameTime, Player *player, StageGenerator *stageGen, EnemyManager *emList)
{
	cameraVelocity = backgroundNS::CAMERA_VELOCITY;

	VECTOR2 collisionVector;
	FILLS *fillCollection = stageGen->getFills();
	bool left =false;
	bool right = false;
	if (spriteData.x >= 0) {
		left = true;
		spriteData.x = 0;
		stageGen->update(frameTime, 0, 2, false);
	}
	if (spriteData.x <= -2560)
	{
		right = true;
		spriteData.x = -2560;
		stageGen->update(frameTime, 0, 1, false);
	}
	for (FILLS::iterator fill = (fillCollection->begin()); fill != fillCollection->end(); fill++)
	{
		if (player->collidesWith(**fill, collisionVector))
		{
			yes = true;
			break;
		}
	}
	if ((player->getX() < centreX) && !left) {
		velocity.x = cameraVelocity;
		if (input->isKeyDown(RUNNING_LEFT_KEY) && cameraVelocity != 0 ) {
			spriteData.x += frameTime * (velocity.x);         // move ship along X
			stageGen->update(frameTime, 1, 0, true);
			emList->camera(frameTime, 1);
		}
		if (input->isKeyDown(RUNNING_RIGHT_KEY) && cameraVelocity != 0) {
			if (!yes) {
				spriteData.x += frameTime * (-velocity.x);         // move ship along X
				stageGen->update(frameTime, 2, 0, true);
				emList->camera(frameTime, 2);
			}
		}
		if (!yes) {
			player->setPlayerInput(false);
			player->setX(centreX);
		}
		else
			player->setPlayerInput(true);
		yes = false;
	}
	for (FILLS::iterator fill = (fillCollection->begin()); fill != fillCollection->end(); fill++)
	{
		if (player->collidesWith(**fill, collisionVector))
		{
			yes = true;
			break;
		}
	}
	if ((player->getX() >= centreX) && !right) {
		velocity.x = cameraVelocity;
		if (input->isKeyDown(RUNNING_LEFT_KEY) && cameraVelocity != 0) {
			spriteData.x += frameTime * (velocity.x);         // move ship along X
			stageGen->update(frameTime, 1, 0, true);
			emList->camera(frameTime, 1);
		}
		if (input->isKeyDown(RUNNING_RIGHT_KEY) && cameraVelocity != 0) {
			if (!yes) {
				spriteData.x += frameTime * (-velocity.x);         // move ship along X
				stageGen->update(frameTime, 2, 0, true);
				emList->camera(frameTime, 2);
			}
		}
		if (!yes) {
			player->setPlayerInput(false);
			player->setX(centreX);
		}
		else
			player->setPlayerInput(true);
		yes = false;

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
	if ((player->getY() > centreY) && !down) {
		velocity.y = cameraVelocity;
		if (player->getVelocityY() > 0){
			spriteData.y += frameTime * (-velocity.y);         // move ship along X
			stageGen->update(frameTime, 4, 0, true);
			emList->camera(frameTime, 4);
			//if (player->getY() < centreY)
			//	player->setY(centre);
		}
		if (player->getVelocityY() < 0) {
			spriteData.y += frameTime * (velocity.y);         // move ship along X
			stageGen->update(frameTime, 3, 0, true);
			emList->camera(frameTime, 3);
			//if (player->getY() < centreY)
				//player->setY(centre);
		}

		player->setY(centreY);
	}
	if ((player->getY() < centreY) && !up) {
		velocity.y = cameraVelocity;
		if (player->getVelocityY() > 0) {
			spriteData.y += frameTime * (-velocity.y);         // move ship along X
			stageGen->update(frameTime, 4, 0, true);
			emList->camera(frameTime, 4);
			//if (player->getY() > centreY)
			//	player->setY(centre);
		}
		if (player->getVelocityY() < 0) {
			spriteData.y += frameTime * (velocity.y);         // move ship along X
			stageGen->update(frameTime, 3 , 0, true);
			emList->camera(frameTime, 3);
			//if (player->getY() > centreY)
				//player->setY(centre);
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
	FILLS *fillCollection = stageGen->getFills();
	for (FILLS::iterator fill = (fillCollection->begin()); fill != fillCollection->end(); fill++)
	{
		if (player->collidesWith(**fill, collisionVector))
		{
			cameraVelocity = 0;
			break;
		}
		else {
			cameraVelocity = backgroundNS::CAMERA_VELOCITY;
		}
	}
}