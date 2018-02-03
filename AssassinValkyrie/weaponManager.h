
#pragma once
#include <vector>
#include "arrow.h"
#include "stone.h"
#include "enemyManager.h"
#include "Player.h"

using std::vector;

typedef std::vector<Arrow *> ARROWLIST;
typedef std::vector<Stone *> STONELIST;

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
		TextureManager *textureM, float X, float Y, Entity &player, KeyBinding *key);
	bool initializeStone(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM, float X, float Y, Entity &player);
	void update(float frameTime, Input *input, Game *gamePtr, int width, int height, int arrowcols, int stonecols,
		TextureManager *textureM, Player &player, KeyBinding *key);
	void collisions(EnemyManager *enemyList, Player *player, PLATFORM floor);
	void ai();
	void render();

};