// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Zhuang yuteng
// Student Number	: S10163964C

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
	ARROWLIST arrow_collection;
	STONELIST stone_collection;
	DWORD Tick;
	DWORD Tick2;


public:
	WeaponManager();

	bool initializeArrow(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM, float X, float Y, Entity &player, KeyBinding *key);
	bool initializeStone(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM, float X, float Y, Entity &player);
	void update(float frameTime, Input *input, Game *gamePtr, int width, int height, int arrowcols, int stonecols,
		TextureManager *textureM, Player &player, KeyBinding *key, Audio *a);
	void collisions(EnemyManager *enemyList, Player *player, PLATFORM floor, Input *i);
	void ai();
	void render();

	void setCameraVelocity(VECTOR2 velocity);
	void camera(float frametime, int direction);
};