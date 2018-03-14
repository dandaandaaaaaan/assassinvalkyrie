//  Module:             Gameplay Programming
//  Assignment1:        LET IT RAIN
//  Student Name:       Timothy Chua
//  Student Number:     10165581F

#ifndef _ENEMY_MANAGER_H
#define _ENEMY_MANAGER_H
#define WIN32_LEAN_AND_MEAN

#include "trooper.h"
#include "gunner.h"
#include "serpant.h"
#include <vector>

typedef std::vector<Enemy*> WORLDENEMYLIST;
typedef std::vector<Trooper*> TROOPERLIST;
typedef std::vector<Gunner*> GUNNERLIST;
typedef std::vector<Serpant*> SERPANTLIST;

typedef std::vector<VECTOR2> POSITION;

class EnemyManager
{
private:
	WORLDENEMYLIST worldCollection;
	TROOPERLIST trooperCollection;
	GUNNERLIST gunnerCollection;
	SERPANTLIST serpantCollection;

	WORLDENEMYLIST::iterator world;
	TROOPERLIST::iterator trooper;
	GUNNERLIST::iterator gunner;
	SERPANTLIST::iterator serpant;

	POSITION	trooperPos;
	POSITION	gunnerPos;
	POSITION	serpantPos;
	int			alertRange;
	bool alertSound;

public:
	EnemyManager();
	~EnemyManager();

	bool initialize(Game *gamePtr, TextureManager *textureTrooper, TextureManager *textureGunner, TextureManager *textureSerpant, TextureManager *textureHealth, Entity *play);
	void update(float frameTime, PLATFORM p, Audio *a);
	void ai(Entity *player, PLATFORM p, Input *i, float viewM);
	void collisions(Entity *play, PLATFORM floor, PLATFORM fill, Audio *a);
	void render();
	void renderRay(Graphics *g);
	void unCollide(Enemy *t, PLATFORM floor, PLATFORM fill);

	TROOPERLIST *getTroopers() { return &trooperCollection; }
	GUNNERLIST *getGunners() { return &gunnerCollection; }
	SERPANTLIST *getSerpants() { return &serpantCollection; }
	WORLDENEMYLIST *getWorlds() { return &worldCollection; }

	void loadTrooper(POSITION p) { trooperPos = p; }
	void loadGunner(POSITION p) { gunnerPos = p; }
	void loadSerpant(POSITION p) { serpantPos = p; }

	void camera(float frameTime, int direction);
	void setCameraVelocity(VECTOR2 velocity);
};
#endif
