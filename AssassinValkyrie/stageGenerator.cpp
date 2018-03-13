// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Daniel Lee Min Qiang
// Student Number	: S10162739H

#include "stageGenerator.h"
StageGenerator::StageGenerator() 
{
	edge = true;
}

StageGenerator::~StageGenerator() 
{
	for (Floor *t : floorCollection)
		SAFE_DELETE(t);
	floorCollection.clear();

	for (Fill *t : fillCollection)
		SAFE_DELETE(t);
	fillCollection.clear();

	for (Fill *t : sideCollection)
		SAFE_DELETE(t);
	sideCollection.clear();

	for (Hideout *t : hideoutCollection)
		SAFE_DELETE(t);
	hideoutCollection.clear();

	for (Ladder *t : ladderCollection)
		SAFE_DELETE(t);
	ladderCollection.clear();

	for (PickupHP *t : hpCollection)
		SAFE_DELETE(t);
	hpCollection.clear();

	for (PickupArrow *t : pickupArrowCollection)
		SAFE_DELETE(t);
	pickupArrowCollection.clear();

	for (PickupStone *t : pickupStoneCollection)
		SAFE_DELETE(t);
	pickupStoneCollection.clear();
}

bool StageGenerator::initialize(Game *gamePtr, TextureManager *textureM, int *stageNo, EnemyManager *ent, TextureManager *pickupTextures)
{
	bool success = true;

	LevelLoader level;
	level.initializeStage(*stageNo);
	level.loadElements();
	totalElements = level.elementSize();
	horizontalElement2 horizontalElement2;
	for (int i = 0; i <= totalElements; i++)
	{
		if (!level.elementEmpty())
		{
			horizontalElement2 = level.getElement();
			if (horizontalElement2.element == "FLOOR")
			{
				floorCollection.emplace_back(new Floor());
				success = floorCollection.back()->initialize(gamePtr, floorNS::WIDTH, floorNS::HEIGHT, floorNS::TEXTURE_COLS, textureM);
				floorCollection.back()->setCurrentFrame(floorNS::START_FRAME);
				floorCollection.back()->setX(horizontalElement2.x);
				floorCollection.back()->setStartX(horizontalElement2.x);
				floorCollection.back()->setY(GAME_HEIGHT - horizontalElement2.y + block_height - floorNS::HEIGHT);
				floorCollection.back()->setStartY(GAME_HEIGHT - horizontalElement2.y + block_height - floorNS::HEIGHT);
				floorCollection.back()->setEdge(RECT{ (long)(-floorNS::WIDTH / 2), (long)(-floorNS::HEIGHT / 2), (long)(floorNS::WIDTH / 2), (long)(floorNS::HEIGHT / 2) });
				floorCollection.back()->setCollisionType(entityNS::ROTATED_BOX);
				if (!success)
					return success;
			}

			else if (horizontalElement2.element == "FILL")
			{
				fillCollection.emplace_back(new Fill());
				success = fillCollection.back()->initialize(gamePtr, fillNS::WIDTH, fillNS::HEIGHT, fillNS::TEXTURE_COLS, textureM);
				fillCollection.back()->setCurrentFrame(fillNS::START_FRAME);
				fillCollection.back()->setX(horizontalElement2.x);
				fillCollection.back()->setStartX(horizontalElement2.x);
				fillCollection.back()->setY(GAME_HEIGHT - horizontalElement2.y);
				fillCollection.back()->setStartY(GAME_HEIGHT - horizontalElement2.y);
				fillCollection.back()->setEdge(RECT{ (long)(-fillNS::WIDTH / 2), (long)(-fillNS::HEIGHT / 2), (long)(fillNS::WIDTH / 2), (long)(fillNS::HEIGHT / 2) });
				fillCollection.back()->setCollisionType(entityNS::ROTATED_BOX);
				if (!success)
					return success;
			}

			else if (horizontalElement2.element == "LEFT")
			{
				sideCollection.emplace_back(new LeftFill());
				success = sideCollection.back()->initialize(gamePtr, fillNS::WIDTH, fillNS::HEIGHT, fillNS::LEFT_TEXTURE_COLS, textureM);
				sideCollection.back()->setCurrentFrame(fillNS::LEFT_FRAME);
				sideCollection.back()->setX(horizontalElement2.x);
				sideCollection.back()->setStartX(horizontalElement2.x);
				sideCollection.back()->setY(GAME_HEIGHT - horizontalElement2.y);
				sideCollection.back()->setStartY(GAME_HEIGHT - horizontalElement2.y);
				sideCollection.back()->setEdge(RECT{ (long)(-fillNS::WIDTH / 2), (long)(-fillNS::HEIGHT / 2), (long)(fillNS::WIDTH / 2), (long)(fillNS::HEIGHT / 2) });
				sideCollection.back()->setCollisionType(entityNS::ROTATED_BOX);
				if (!success)
					return success;
			}

			else if (horizontalElement2.element == "RIGHT")
			{
				sideCollection.emplace_back(new RightFill());
				success = sideCollection.back()->initialize(gamePtr, fillNS::WIDTH, fillNS::HEIGHT, fillNS::RIGHT_TEXTURE_COLS, textureM);
				sideCollection.back()->setCurrentFrame(fillNS::RIGHT_FRAME);
				sideCollection.back()->setX(horizontalElement2.x);
				sideCollection.back()->setStartX(horizontalElement2.x);
				sideCollection.back()->setY(GAME_HEIGHT - horizontalElement2.y);
				sideCollection.back()->setStartY(GAME_HEIGHT - horizontalElement2.y);
				sideCollection.back()->setEdge(RECT{ (long)(-fillNS::WIDTH / 2), (long)(-fillNS::HEIGHT / 2), (long)(fillNS::WIDTH / 2), (long)(fillNS::HEIGHT / 2) });
				sideCollection.back()->setCollisionType(entityNS::ROTATED_BOX);
				if (!success)
					return success;
			}

			else if (horizontalElement2.element == "HIDEOUT")
			{
				hideoutCollection.emplace_back(new Hideout());
				success = hideoutCollection.back()->initialize(gamePtr, hideoutNS::WIDTH, hideoutNS::HEIGHT, hideoutNS::TEXTURE_COLS, textureM);
				hideoutCollection.back()->setCurrentFrame(hideoutNS::FRAME);
				hideoutCollection.back()->setX(horizontalElement2.x);
				hideoutCollection.back()->setStartX(horizontalElement2.x);
				hideoutCollection.back()->setY(GAME_HEIGHT - horizontalElement2.y + (fillNS::HEIGHT - floorNS::HEIGHT));
				hideoutCollection.back()->setStartY(GAME_HEIGHT - horizontalElement2.y + (fillNS::HEIGHT - floorNS::HEIGHT));
				hideoutCollection.back()->setEdge(RECT{ (long)(-hideoutNS::WIDTH / 2), (long)(-hideoutNS::HEIGHT / 2), (long)(hideoutNS::WIDTH / 2), (long)(hideoutNS::HEIGHT / 2) });
				hideoutCollection.back()->setCollisionType(entityNS::ROTATED_BOX);
				if (!success)
					return success;
			}

			else if (horizontalElement2.element == "TROOPER")
				trooperPos.emplace_back(VECTOR2{ (float)horizontalElement2.x + fillNS::WIDTH / 2, GAME_HEIGHT - (float)horizontalElement2.y + fillNS::HEIGHT });
			else if (horizontalElement2.element == "GUNNER")
				gunnerPos.emplace_back(VECTOR2{ (float)horizontalElement2.x + fillNS::WIDTH / 2, GAME_HEIGHT - (float)horizontalElement2.y + fillNS::HEIGHT });
			else if (horizontalElement2.element == "SERPANT")
				serpantPos.emplace_back(VECTOR2{ (float)horizontalElement2.x + fillNS::WIDTH / 2, GAME_HEIGHT - (float)horizontalElement2.y + fillNS::HEIGHT });

			else if (horizontalElement2.element == "LADDER")
			{
				ladderCollection.emplace_back(new Ladder());
				success = ladderCollection.back()->initialize(gamePtr, ladderNS::WIDTH, ladderNS::HEIGHT, 5, textureM);
				ladderCollection.back()->setCurrentFrame(4);
				ladderCollection.back()->setX(horizontalElement2.x);
				ladderCollection.back()->setStartX(horizontalElement2.x);
				ladderCollection.back()->setY(GAME_HEIGHT - horizontalElement2.y + (fillNS::HEIGHT - floorNS::HEIGHT));
				ladderCollection.back()->setStartY(GAME_HEIGHT - horizontalElement2.y + (fillNS::HEIGHT - floorNS::HEIGHT));
				ladderCollection.back()->setEdge(RECT{ (long)(-ladderNS::WIDTH / 2), (long)(-ladderNS::HEIGHT / 2), (long)(ladderNS::WIDTH / 2), (long)(ladderNS::HEIGHT / 2) });
				ladderCollection.back()->setCollisionType(entityNS::ROTATED_BOX);
			}

			else if (horizontalElement2.element == "PICKUPHP")
			{
				hpCollection.emplace_back(new PickupHP());
				success = hpCollection.back()->initialize(gamePtr, pickupHPNS::WIDTH, pickupHPNS::HEIGHT, pickupHPNS::TEXTURE_COLS, pickupTextures);
				hpCollection.back()->setCurrentFrame(pickupHPNS::START_FRAME);
				hpCollection.back()->setY(GAME_HEIGHT - horizontalElement2.y + (fillNS::HEIGHT - floorNS::HEIGHT));
				hpCollection.back()->setStartY(GAME_HEIGHT - horizontalElement2.y + (fillNS::HEIGHT - floorNS::HEIGHT));
				hpCollection.back()->setCollisionType(entityNS::ROTATED_BOX);
				hpCollection.back()->setX(horizontalElement2.x);
				hpCollection.back()->setStartX(horizontalElement2.x);
			}

			else if (horizontalElement2.element == "PICKUPARROW")
			{
				pickupArrowCollection.emplace_back(new PickupArrow());
				success = pickupArrowCollection.back()->initialize(gamePtr, pickupArrowNS::WIDTH, pickupArrowNS::HEIGHT, pickupArrowNS::TEXTURE_COLS, pickupTextures);
				pickupArrowCollection.back()->setCurrentFrame(pickupArrowNS::START_FRAME);
				pickupArrowCollection.back()->setY(GAME_HEIGHT - horizontalElement2.y + (fillNS::HEIGHT - floorNS::HEIGHT));
				pickupArrowCollection.back()->setStartY(GAME_HEIGHT - horizontalElement2.y + (fillNS::HEIGHT - floorNS::HEIGHT));
				pickupArrowCollection.back()->setCollisionType(entityNS::ROTATED_BOX);
				pickupArrowCollection.back()->setX(horizontalElement2.x);
				pickupArrowCollection.back()->setStartX(horizontalElement2.x);
			}

			else if (horizontalElement2.element == "PICKUPSTONE")
			{
				pickupStoneCollection.emplace_back(new PickupStone());
				success = pickupStoneCollection.back()->initialize(gamePtr, pickupStoneNS::WIDTH, pickupStoneNS::HEIGHT, pickupStoneNS::TEXTURE_COLS, pickupTextures);
				pickupStoneCollection.back()->setCurrentFrame(pickupStoneNS::START_FRAME);
				pickupStoneCollection.back()->setY(GAME_HEIGHT - horizontalElement2.y + (fillNS::HEIGHT - floorNS::HEIGHT));
				pickupStoneCollection.back()->setStartY(GAME_HEIGHT - horizontalElement2.y + (fillNS::HEIGHT - floorNS::HEIGHT));
				pickupStoneCollection.back()->setCollisionType(entityNS::ROTATED_BOX);
				pickupStoneCollection.back()->setX(horizontalElement2.x);
				pickupStoneCollection.back()->setStartX(horizontalElement2.x);
			}

			else if (horizontalElement2.element == "SPAWN")
				playerPos = { (float)horizontalElement2.x + fillNS::WIDTH / 2, GAME_HEIGHT - (float)horizontalElement2.y + fillNS::HEIGHT };
			else if (horizontalElement2.element == "T1")
			{
				helpList.emplace_back(new HelpText());
				helpList.back()->initialize(gamePtr->getGraphics(), VECTOR2{ (float)horizontalElement2.x + fillNS::WIDTH / 2, GAME_HEIGHT - (float)horizontalElement2.y + fillNS::HEIGHT }, 1);
				helpList.back()->setStartX(horizontalElement2.x);
				helpList.back()->setStartY(GAME_HEIGHT - horizontalElement2.y + (fillNS::HEIGHT - floorNS::HEIGHT));
			}
			else if (horizontalElement2.element == "T2")
			{
				helpList.emplace_back(new HelpText());
				helpList.back()->initialize(gamePtr->getGraphics(), VECTOR2{ (float)horizontalElement2.x + fillNS::WIDTH / 2, GAME_HEIGHT - (float)horizontalElement2.y + fillNS::HEIGHT }, 2);
				helpList.back()->setStartX(horizontalElement2.x);
				helpList.back()->setStartY(GAME_HEIGHT - horizontalElement2.y + (fillNS::HEIGHT - floorNS::HEIGHT));
			}
			else if (horizontalElement2.element == "T3")
			{
				helpList.emplace_back(new HelpText());
				helpList.back()->initialize(gamePtr->getGraphics(), VECTOR2{ (float)horizontalElement2.x + fillNS::WIDTH / 2, GAME_HEIGHT - (float)horizontalElement2.y + fillNS::HEIGHT }, 3);
				helpList.back()->setStartX(horizontalElement2.x);
				helpList.back()->setStartY(GAME_HEIGHT - horizontalElement2.y + (fillNS::HEIGHT - floorNS::HEIGHT));
			}
			else if (horizontalElement2.element == "T4")
			{
				helpList.emplace_back(new HelpText());
				helpList.back()->initialize(gamePtr->getGraphics(), VECTOR2{ (float)horizontalElement2.x + fillNS::WIDTH / 2, GAME_HEIGHT - (float)horizontalElement2.y + fillNS::HEIGHT }, 4);
				helpList.back()->setStartX(horizontalElement2.x);
				helpList.back()->setStartY(GAME_HEIGHT - horizontalElement2.y + (fillNS::HEIGHT - floorNS::HEIGHT));
			}
			else if (horizontalElement2.element == "T5")
			{
				helpList.emplace_back(new HelpText());
				helpList.back()->initialize(gamePtr->getGraphics(), VECTOR2{ (float)horizontalElement2.x + fillNS::WIDTH / 2, GAME_HEIGHT - (float)horizontalElement2.y + fillNS::HEIGHT }, 5);
				helpList.back()->setStartX(horizontalElement2.x);
				helpList.back()->setStartY(GAME_HEIGHT - horizontalElement2.y + (fillNS::HEIGHT - floorNS::HEIGHT));
			}
		}
	}
	ent->loadTrooper(trooperPos);
	ent->loadGunner(gunnerPos);
	ent->loadSerpant(serpantPos);
}

void StageGenerator::render(int stage)
{
	for (Floor *t : floorCollection)
		if (!t->outOfBounds())
			t->draw();

	for (Fill *t : fillCollection)
		if (!t->outOfBounds())
			t->draw();

	for (Fill *t : sideCollection)
		if (!t->outOfBounds())
			t->draw();

	for (Hideout *t : hideoutCollection)
		if (!t->outOfBounds())
			t->draw();

	for (Ladder *t : ladderCollection)
		if (!t->outOfBounds())
			t->draw();

	for (PickupHP *t : hpCollection)
		if (!t->outOfBounds())
			t->draw();

	for (PickupArrow *t : pickupArrowCollection)
		if (!t->outOfBounds())
			t->draw();

	for (PickupStone *t : pickupStoneCollection)
		if (!t->outOfBounds())
			t->draw();

	for (HelpText *t : helpList)
		if (!t->outOfBounds())
			t->draw(stage);
}

void StageGenerator::update(float frametime, int direction, int leftrightupdown, bool moveOn)
{
	for(Floor *floor : floorCollection){
		switch (leftrightupdown) {
		case 1:
			(floor)->setX((floor)->getStartX() - 2560);
			break;
		case 2:
			(floor)->setX((floor)->getStartX());
			break;
		case 3:
			(floor)->setY((floor)->getStartY() + 1264);
			break;
		case 4:
			(floor)->setY((floor)->getStartY());
			break;
		}
		if (moveOn)
			(floor)->update(frametime, direction);
	}
	for (Fill *fill : fillCollection) {
		switch (leftrightupdown) {
		case 1:
			(fill)->setX((fill)->getStartX() - 2560);
			break;
		case 2:
			(fill)->setX((fill)->getStartX());
			break;
		case 3:
			(fill)->setY((fill)->getStartY() + 1264);
			break;
		case 4:
			(fill)->setY((fill)->getStartY());
			break;
		}
		if (moveOn)
			(fill)->update(frametime, direction);
	}
	for (side = sideCollection.begin(); side != sideCollection.end(); side++) {
		switch (leftrightupdown) {
		case 1:
			(*side)->setX((*side)->getStartX() - 2560);
			break;
		case 2:
			(*side)->setX((*side)->getStartX());
			break;
		case 3:
			(*side)->setY((*side)->getStartY() + 1264);
			break;
		case 4:
			(*side)->setY((*side)->getStartY());
			break;
		}
		if (moveOn)
			(*side)->update(frametime, direction);
	}
	for (Hideout *hideout : hideoutCollection) {
		switch (leftrightupdown) {
		case 1:
			(hideout)->setX((hideout)->getStartX() - 2560);
			break;
		case 2:
			((hideout)->setX((hideout)->getStartX()));
			break;
		case 3:
			(hideout)->setY((hideout)->getStartY() + 1264);
			break;
		case 4:
			(hideout)->setY((hideout)->getStartY());
			break;
		}
		if (moveOn)
			(hideout)->update(frametime, direction);
	}
	
	for (Ladder *ladder : ladderCollection) {
		switch (leftrightupdown) {
		case 1:
			(ladder)->setX((ladder)->getStartX() - 2560);
			break;
		case 2:
			(ladder)->setX((ladder)->getStartX());
			break;
		case 3:
			(ladder)->setY((ladder)->getStartY() + 1264);
			break;
		case 4:
			(ladder)->setY((ladder)->getStartY());
			break;
		}
		if (moveOn)
			(ladder)->update(frametime, direction);
	}

	for (PickupHP *hp : hpCollection) {
		switch (leftrightupdown) {
		case 1:
			(hp)->setX((hp)->getStartX() - 2560);
			break;
		case 2:
			(hp)->setX((hp)->getStartX());
			break;
		case 3:
			(hp)->setY((hp)->getStartY() + 1264);
			break;
		case 4:
			(hp)->setY((hp)->getStartY());
			break;
		}
		if (moveOn)
			(hp)->update(frametime, direction);
	}

	for (PickupArrow *arrow : pickupArrowCollection) {
		switch (leftrightupdown) {
		case 1:
			(arrow)->setX((arrow)->getStartX() - 2560);
			break;
		case 2:
			(arrow)->setX((arrow)->getStartX());
			break;
		case 3:
			(arrow)->setY((arrow)->getStartY() + 1264);
			break;
		case 4:
			(arrow)->setY((arrow)->getStartY());
			break;
		}
		if (moveOn)
			(arrow)->update(frametime, direction);
	}

	for (PickupStone *stone : pickupStoneCollection) {
		switch (leftrightupdown) {
		case 1:
			(stone)->setX((stone)->getStartX() - 2560);
			break;
		case 2:
			(stone)->setX((stone)->getStartX());
			break;
		case 3:
			(stone)->setY((stone)->getStartY() + 1264);
			break;
		case 4:
			(stone)->setY((stone)->getStartY());
			break;
		}
		if (moveOn)
			(stone)->update(frametime, direction);
	}

	for (HelpText *t : helpList) {
		switch (leftrightupdown) {
		case 1:
			(t)->setX((t)->getStartX() - 2560);
			break;
		case 2:
			(t)->setX((t)->getStartX());
			break;
		case 3:
			(t)->setY((t)->getStartY() + 1264);
			break;
		case 4:
			(t)->setY((t)->getStartY());
			break;
		}
		if (moveOn)
			(t)->update(frametime, direction);
	}
}

void StageGenerator::updateSpeed(VECTOR2 velocity) {
	for (Floor *t : floorCollection)
		t->getMove()->setCameraVelocity(velocity);
	for (Fill *t : fillCollection)
		t->getMove()->setCameraVelocity(velocity);

	for (Fill *t : sideCollection)
		t->getMove()->setCameraVelocity(velocity);

	for (Hideout *t : hideoutCollection)
		t->getMove()->setCameraVelocity(velocity);

	for (Ladder *t : ladderCollection)
		t->getMove()->setCameraVelocity(velocity);

	for (PickupHP *t : hpCollection)
		t->getMove()->setCameraVelocity(velocity);

	for (PickupArrow *t : pickupArrowCollection)
		t->getMove()->setCameraVelocity(velocity);

	for (PickupStone *t : pickupStoneCollection)
		t->getMove()->setCameraVelocity(velocity);

	for (HelpText *t : helpList)
		t->getMove()->setCameraVelocity(velocity);
}


PLATFORM StageGenerator::getVisionPlatforms()
{
	PLATFORM p;
	for (Entity *t : floorCollection)
		p.emplace_back(t);
	for (Entity *t : sideCollection)
		p.emplace_back(t);
	return p;
}

PLATFORM StageGenerator::getSidePlatforms()
{
	PLATFORM p;
	for (Entity *t : sideCollection)
		p.emplace_back(t);
	return p;
}

PLATFORM StageGenerator::getFloorPlatforms()
{
	PLATFORM p;
	for (Entity *t : floorCollection)
		p.emplace_back(t);
	return p;
}