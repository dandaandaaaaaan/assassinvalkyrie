// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Chua Wei Jie Timothy
// Student Number	: S10165581F

#pragma once
#include "bullet.h"
#include "fireBall.h"
#include "enemyManager.h"
#include <vector>

typedef std::vector<Bullet*> BULLETLIST;
typedef std::vector<Fireball*> FIRELIST;

class EnemyBulletManager
{
private:
	GUNNERLIST	*gunnerList;
	SERPANTLIST	*serpantList;
	BULLETLIST	bulletList;
	FIRELIST	fireList;

	GUNNERLIST::iterator	gunner;
	SERPANTLIST::iterator	serpant;
	BULLETLIST::iterator	bullet;
	FIRELIST::iterator		fireball;

public:
	EnemyBulletManager();
	~EnemyBulletManager();

	void initialize(EnemyManager *enemyList);
	bool initializeBullet(Game *gamePtr, TextureManager *textureM, Gunner *gunner);
	bool initializeFire(Game *gamePtr, TextureManager *textureM, Serpant *serpant, Entity *play);
	void update(float frameTime, Game *gamePtr, TextureManager *textureM, Entity *play, Audio *a);
	void collisions(Entity *play, PLATFORM p);
	void render();
	void camera(float frameTime, int direction);
};