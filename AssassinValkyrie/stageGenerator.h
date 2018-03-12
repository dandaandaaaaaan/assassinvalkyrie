// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Daniel Lee Min Qiang
// Student Number	: S10162739H
#ifndef _STAGEGENERATOR_H
#define _STAGEGENERATOR_H
#define WIN32_LEAN_AND_MEAN

#pragma once
#include "levelLoader.h"
#include "floor.h"
#include "fill.h"
#include "leftFill.h"
#include "rightFill.h"
#include "hideout.h"
#include "ladder.h"
#include "enemyManager.h"
#include "pickupHP.h"
#include "pickupArrow.h"
#include "pickupStone.h"
#include "helpText.h"
#include <queue>
#include <string>
#include <vector>

typedef std::vector<Floor *> FLOORS;
typedef std::vector<Fill *> FILLS;
typedef std::vector<Fill *> SIDES;
typedef std::vector<Hideout *> HIDEOUTS;
typedef std::vector<Ladder *> LADDERS;
typedef std::vector<PickupHP *> HPS;
typedef std::vector<PickupArrow *> PICKUPARROWS;
typedef std::vector<PickupStone *> PICKUPSTONES;
typedef std::vector<HelpText *> HELP;

class StageGenerator
{
private:
	int currentStage;
	FLOORS floorCollection;

	FILLS fillCollection;

	SIDES sideCollection;
	SIDES::iterator side;

	HIDEOUTS hideoutCollection;

	LADDERS ladderCollection;

	HPS hpCollection;

	PICKUPARROWS pickupArrowCollection;

	PICKUPSTONES pickupStoneCollection;

	POSITION	trooperPos;
	POSITION	gunnerPos;
	POSITION	serpantPos;
	VECTOR2		playerPos;
	HELP		helpList;

	int totalElements;
	bool edge;

public:
	StageGenerator();
	~StageGenerator();

	bool initialize(Game *gamePtr, TextureManager *textureM, int *stageNo, EnemyManager *ent, TextureManager *pickupTextures);
	void render(int stage);
	void update(float frametime, int direction, int leftrightupdown, bool moveOn);
	void updateSpeed(VECTOR2 velocity);

	PLATFORM getVisionPlatforms();
	PLATFORM getSidePlatforms();
	PLATFORM getFloorPlatforms();
	POSITION getTrooper() { return trooperPos; }
	FLOORS *getFloors() { return &floorCollection; }
	FILLS *getFills() { return &fillCollection; }
	FILLS *getSides() { return &sideCollection; }
	LADDERS *getLadders() { return &ladderCollection; }
	VECTOR2 getSpawn() { return playerPos; }

	HPS *getHP() { return &hpCollection; }
	PICKUPARROWS *getPickupArrows() { return &pickupArrowCollection; }
	PICKUPSTONES *getPickupStones() { return &pickupStoneCollection; }
	HIDEOUTS *getHideouts() { return &hideoutCollection; }
};
#endif
