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
	if (player->outOfBounds() || !player->getVisible())
		return;
	bool left =false;
	bool right = false;
	VECTOR2 cameraVelocity = player->getVelocity();
	cameraVelocity.x = cameraVelocity.x / 2;
	//cameraVelocity.y = cameraVelocity.y / 2;
	if (cameraVelocity.x < 0)
		cameraVelocity.x = -cameraVelocity.x;
	if (cameraVelocity.y < 0)
		cameraVelocity.y = -cameraVelocity.y;
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
			velocity.x = cameraVelocity.x;
			spriteData.x += frameTime * (velocity.x);         // move ship along X
			stageGen->updateSpeed(cameraVelocity);
			stageGen->update(frameTime, 1, 0, true);
			emList->setCameraVelocity(cameraVelocity);
			emList->camera(frameTime, 1);
			emBulletList->setCameraVelocity(cameraVelocity);
			emBulletList->camera(frameTime, 1);
		}
		if (input->isKeyDown(key->getRightKey()) && moveOn) {
			velocity.x = cameraVelocity.x;;
			spriteData.x += frameTime * (-velocity.x);         // move ship along X
			stageGen->updateSpeed(cameraVelocity);
			stageGen->update(frameTime, 2, 0, true);
			emList->setCameraVelocity(cameraVelocity);
			emList->camera(frameTime, 2);
			emBulletList->setCameraVelocity(cameraVelocity);
			emBulletList->camera(frameTime, 2);
		}
		player->setX(centreX);
	}

	if ((player->getX() > centreX) && !right) {
		if (input->isKeyDown(key->getLeftKey()) && moveOn) {
			velocity.x = cameraVelocity.x;
			spriteData.x += frameTime * (velocity.x);         // move ship along X
			stageGen->updateSpeed(cameraVelocity);
			stageGen->update(frameTime, 1, 0, true);
			emList->setCameraVelocity(cameraVelocity);
			emList->camera(frameTime, 1);
			emBulletList->setCameraVelocity(cameraVelocity);
			emBulletList->camera(frameTime, 1);
		}
		if (input->isKeyDown(key->getRightKey()) && moveOn) {
			velocity.x = cameraVelocity.x;
			spriteData.x += frameTime * (-velocity.x);         // move ship along X
			stageGen->updateSpeed(cameraVelocity);
			stageGen->update(frameTime, 2, 0, true);
			emList->setCameraVelocity(cameraVelocity);
			emList->camera(frameTime, 2);
			emBulletList->setCameraVelocity(cameraVelocity);
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
			velocity.y = cameraVelocity.y;
			spriteData.y += frameTime * (-velocity.y);         // move ship along X
			stageGen->updateSpeed(cameraVelocity);
			stageGen->update(frameTime, 4, 0, true);
			emList->setCameraVelocity(cameraVelocity);
			emList->camera(frameTime, 4);
			emBulletList->setCameraVelocity(cameraVelocity);
			emBulletList->camera(frameTime, 4);

		}
		if (player->getVelocityY() < 0 ) {
			velocity.y = cameraVelocity.y;
			spriteData.y += frameTime * (velocity.y);         // move ship along X
			stageGen->updateSpeed(cameraVelocity);
			stageGen->update(frameTime, 3, 0, true);
			emList->setCameraVelocity(cameraVelocity);
			emList->camera(frameTime, 3);
			emBulletList->setCameraVelocity(cameraVelocity);
			emBulletList->camera(frameTime, 3);

		}
		player->setY(centreY);
	}
	if ((player->getY() > centreY) && !down && !topLock ) {
		if (player->getVelocityY() > 0) {
			velocity.y = cameraVelocity.y;
			spriteData.y += frameTime * (-velocity.y);         // move ship along X
			stageGen->updateSpeed(cameraVelocity);
			stageGen->update(frameTime, 4, 0, true);
			emList->setCameraVelocity(cameraVelocity);
			emList->camera(frameTime, 4);
			emBulletList->setCameraVelocity(cameraVelocity);
			emBulletList->camera(frameTime, 4);

		}
		if (player->getVelocityY() < 0 ) {
			velocity.y = cameraVelocity.y;
			spriteData.y += frameTime * (velocity.y);         // move ship along X
			stageGen->updateSpeed(cameraVelocity);
			stageGen->update(frameTime, 3 , 0, true);
			emList->setCameraVelocity(cameraVelocity);
			emList->camera(frameTime, 3);
			emBulletList->setCameraVelocity(cameraVelocity);
			emBulletList->camera(frameTime, 3);

		}
		player->setY(centreY);
	}

	Entity::update(frameTime);
}


void Background::draw()
{
	Image::draw();              // draw ship
}

void Background::collisions(Player *player, StageGenerator *stageGen)
{
}