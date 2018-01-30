
#pragma once
#include <vector>
#include "arrow.h"
#include "stone.h"
#include "enemyManager.h"

using std::vector;

typedef std::vector<Arrow *> ARROWLIST;

class WeaponManager
{

private:
	std::vector<Arrow *> arrow_collection;
	std::vector<Stone *> stone_collection;
	DWORD Tick;
	DWORD Tick2;


public:
	WeaponManager();

	bool initializeArrow(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM, float X, float Y, Entity &player);
	bool initializeStone(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM, float X, float Y, Entity &player);
	void update(float frameTime, Input *input, Game *gamePtr, int width, int height, int arrowcols, int stonecols,
		TextureManager *textureM, float X, float Y, Entity &player);
	void collisions(EnemyManager *enemyList);
	void ai();
	void render();

};