// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Chua Wei Jie Timothy
// Student Number	: S10165581F

#include "enemyBulletManager.h"

EnemyBulletManager::EnemyBulletManager()
{
}

EnemyBulletManager::~EnemyBulletManager()
{
	for (bullet = bulletList.begin(); bullet != bulletList.end(); bullet++)
		SAFE_DELETE(*bullet);
	bulletList.clear();
	for (fireball = fireList.begin(); fireball != fireList.end(); fireball++)
		SAFE_DELETE(*bullet);
	fireList.clear();
}

void EnemyBulletManager::initialize(EnemyManager *enemyList)
{
	gunnerList = enemyList->getGunners();
	serpantList = enemyList->getSerpants();
}

bool EnemyBulletManager::initializeBullet(Game *gamePtr, TextureManager *textureM, Gunner *gunner)
{
	bool isInitialised = true;

	Bullet *it = new Bullet();
	isInitialised = it->initialize(gamePtr, bulletNS::WIDTH, bulletNS::HEIGHT, bulletNS::TEXTURE_COLS, textureM);
	it->setFrames(bulletNS::START_FRAME, bulletNS::END_FRAME);
	it->setCurrentFrame(bulletNS::START_FRAME);
	float direction = gunner->getMove()->getCurrentVelocity();
	if (direction > 0)
	{
		direction = 1;
		it->flipHorizontal(false);
	}
	else
	{
		direction = -1;
		it->flipHorizontal(true);
	}
	it->getMove()->setVelocity(direction * bulletNS::SPEED);
	it->setX(gunner->getCenterX() - bulletNS::WIDTH / 2);
	it->setY(gunner->getCenterY() - bulletNS::HEIGHT / 2 - gunnerNS::HEIGHT / 6);
	bulletList.emplace_back(it);

	if (!isInitialised)
		return !isInitialised;
	return isInitialised;
}

bool EnemyBulletManager::initializeFire(Game *gamePtr, TextureManager *textureM, Serpant *serpant, Entity *play)
{
	bool isInitialised = true;
	float dist = play->getCenterX() - serpant->getCenterX();

	Fireball *it = new Fireball(dist);
	isInitialised = it->initialize(gamePtr, fireNS::WIDTH, fireNS::HEIGHT, fireNS::TEXTURE_COLS, textureM);
	it->setFrames(fireNS::START_FRAME, fireNS::END_FRAME);
	it->setCurrentFrame(fireNS::START_FRAME);
	float direction = serpant->getMove()->getCurrentVelocity();
	if (direction > 0)
	{
		direction = 1;
		it->flipHorizontal(false);
	}
	else
	{
		direction = -1;
		it->flipHorizontal(true);
	}
	it->getMove()->setVelocity(direction * fireNS::SPEED);
	it->setX(serpant->getCenterX() - fireNS::WIDTH / 2);
	it->setY(serpant->getCenterY() - fireNS::HEIGHT / 2 - gunnerNS::HEIGHT / 6);
	fireList.emplace_back(it);

	if (!isInitialised)
		return !isInitialised;
	return isInitialised;
}

void EnemyBulletManager::update(float frameTime, Game *gamePtr, TextureManager *textureM, Entity *play, Audio *a)
{
	for (Gunner *g : *gunnerList)
		if (g->isAlive() && !g->outOfBounds())
		{
			ShootComponent *shot = g->getShoot();
			if (shot->getAnimation() && (GetTickCount() - shot->shootTimer > shot->maxTimeShoot))
			{
				shot->shootTimer = GetTickCount();
				initializeBullet(gamePtr, textureM, g);
				a->playCue(BULLET);
			}
		}

	for (Serpant *g : *serpantList)
		if (g->isAlive() && !g->outOfBounds())
		{
			FireComponent *shot = g->getShoot();
			if (shot->isFire() && (GetTickCount() - shot->fireTimer > shot->maxTimeFire))
			{
				shot->fireTimer = GetTickCount();
				initializeFire(gamePtr, textureM, g, play);
				a->playCue(FIREBALL);
			}
		}

	for (Bullet *t : bulletList)
		if (t->getActive())
			t->update(frameTime);

	for (Fireball *t : fireList)
		if (t->getActive())
			t->update(frameTime);
}

void EnemyBulletManager::collisions(Entity *play, PLATFORM p)
{
	VECTOR2 collisionVector;
	std::vector<Entity *> inRangeP;
	for (Entity *t : p)
		if (!t->outOfBounds())
			inRangeP.emplace_back(t);

	bullet = bulletList.begin();
	while (bullet != bulletList.end())
	{
		if ((*bullet)->getActive()) {
			if ((*bullet)->collidesWith(*play, collisionVector))
			{
				(*bullet)->setActive(false);
				play->setHealth(play->getHealth() - 4);
			}
			else
				for (Entity *t : inRangeP)
					if ((*bullet)->collidesWith(*t, collisionVector))
						(*bullet)->setActive(false);
			bullet++;
		}
		else
			bullet = bulletList.erase(bullet);
	}

	fireball = fireList.begin();
	while (fireball != fireList.end())
	{
		if ((*fireball)->getActive()) {
			if ((*fireball)->collidesWith(*play, collisionVector))
			{
				(*fireball)->setActive(false);
				play->setHealth(play->getHealth() - 6);
			}
			else
				for (Entity *t : inRangeP)
					if ((*fireball)->collidesWith(*t, collisionVector))
						(*fireball)->setActive(false);
			fireball++;
		}
		else
			fireball = fireList.erase(fireball);
	}
}

void EnemyBulletManager::render()
{
	for (Bullet *t : bulletList)
		if (t->getActive())
			t->draw();

	for (Fireball *t : fireList)
		if (t->getActive())
			t->draw();
}

void EnemyBulletManager::camera(float frameTime, int direction)
{
	for (Bullet *t : bulletList)
		t->getMove()->movementWithDirection(frameTime, direction);

	for (Fireball *t : fireList)
		t->getMove()->movementWithDirection(frameTime, direction);
}