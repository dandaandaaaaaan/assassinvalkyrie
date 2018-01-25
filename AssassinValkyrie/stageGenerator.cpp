// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Daniel Lee Min Qiang
// Student Number	: S10162739H

#include "stageGenerator.h"
StageGenerator::StageGenerator() 
{
	stageLoad = new StageLoader();
	edge = true;
}

bool StageGenerator::initialize(Game *gamePtr, TextureManager *textureM, int *stageNo) 
{
	bool success = true;
	//stageLoad->clear();

	stageLoad->initialize();
	stageLoad->loadStage(stageNo);
	totalElements = stageLoad->elementSize();
	stageElement positionElement;
	for (int i = 0; i <= totalElements; i++)
	{
		if (!stageLoad->elementEmpty())
		{
			positionElement = stageLoad->getElement();
			if (positionElement.element == "FLOOR") {
				int count = (positionElement.xEnd - positionElement.xStart) / floorNS::WIDTH;
				if (count == 0)
					count = 1;
				for (int j = 0; j < count; j++) {
					floorCollection.emplace_back(new Floor());
					success = floorCollection.back()->initialize(gamePtr, floorNS::WIDTH, floorNS::HEIGHT, 2, textureM);
					floorCollection.back()->setCurrentFrame(0);
					floorCollection.back()->setX(positionElement.xStart + (floorNS::WIDTH * j));
					floorCollection.back()->setStartX(positionElement.xStart + (floorNS::WIDTH * j));
					floorCollection.back()->setY(GAME_HEIGHT - floorNS::HEIGHT - positionElement.y);
					floorCollection.back()->setStartY(GAME_HEIGHT - floorNS::HEIGHT - positionElement.y);
				}
				if (!success)
					return success;
			}
			if (positionElement.element == "FILL") {
				int count = (positionElement.xEnd - positionElement.xStart) / fillNS::WIDTH;
				if (count == 0)
					count = 1;
				for (int j = 0; j < count; j++) {
					fillCollection.emplace_back(new Fill());
					success = fillCollection.back()->initialize(gamePtr, fillNS::WIDTH, fillNS::HEIGHT, 2, textureM);
					fillCollection.back()->setCurrentFrame(1);
					fillCollection.back()->setX(positionElement.xStart + (fillNS::WIDTH * j));
					fillCollection.back()->setStartX(positionElement.xStart + (fillNS::WIDTH * j));
					fillCollection.back()->setY(GAME_HEIGHT - fillNS::HEIGHT - positionElement.y);
					fillCollection.back()->setStartY(GAME_HEIGHT - fillNS::HEIGHT - positionElement.y);
				}
				if (!success)
					return success;
			}
			if (positionElement.element == "HIDEOUT") {
				int count = (positionElement.xEnd - positionElement.xStart) / hideoutNS::WIDTH;
				if (count == 0)
					count = 1;
				for (int j = 0; j < count; j++) {
					hideoutCollection.emplace_back(new Hideout());
					success = hideoutCollection.back()->initialize(gamePtr, hideoutNS::WIDTH, hideoutNS::HEIGHT, 5, textureM);
					hideoutCollection.back()->setCurrentFrame(4);
					hideoutCollection.back()->setX(positionElement.xStart + (hideoutNS::WIDTH * j));
					hideoutCollection.back()->setY(GAME_HEIGHT - hideoutNS::HEIGHT - positionElement.y);
				}
				if (!success)
					return success;
			}
		}
		//return false;
	}
	
}



void StageGenerator::render()
{
	for (floor = floorCollection.begin(); floor != floorCollection.end(); floor++)
	{
		(*floor)->draw();
	}
	for (fill = fillCollection.begin(); fill != fillCollection.end(); fill++) {
		(*fill)->draw();
	}
	for (hideout = hideoutCollection.begin(); hideout != hideoutCollection.end(); hideout++) {
		(*hideout)->draw();
	}
}

void StageGenerator::update(float frametime, bool moveUp, int leftrightupdown, bool moveOn)
{
	/*
	for (hideout = hideoutCollection.begin(); hideout != hideoutCollection.end(); hideout++) {
		(*hideout)->update(frametime);
	}
	*/
	for (floor = floorCollection.begin(); floor != floorCollection.end(); floor++)
	{
		int x = (*floor)->getX();
		int y = (*floor)->getY();
		if (leftrightupdown == 1)
		{
			(*floor)->setX((*floor)->getStartX() - 160);
		}
		else if (leftrightupdown == 2)
		{
			(*floor)->setX((*floor)->getStartX());
		}
		else if (leftrightupdown == 3)
		{
			(*floor)->setY((*floor)->getStartY());
		}
		else if (leftrightupdown == 4)
		{
			(*floor)->setY((*floor)->getStartY() - 720);
		}
		if (moveOn)
			(*floor)->update(frametime, moveUp);
	}
	for (fill = fillCollection.begin(); fill != fillCollection.end(); fill++) {
		int x = (*fill)->getX();
		int y = (*fill)->getY();
		if (leftrightupdown == 1)
			(*fill)->setX((*fill)->getStartX() -160);
		else if (leftrightupdown == 2)
			((*fill)->setX((*fill)->getStartX()));
		else if (leftrightupdown == 3)
			(*fill)->setY((*fill)->getStartY());
		else if (leftrightupdown == 4)
			(*fill)->setY((*fill)->getStartY()-720);
		else if (moveOn)
			(*fill)->update(frametime, moveUp);
	}
}