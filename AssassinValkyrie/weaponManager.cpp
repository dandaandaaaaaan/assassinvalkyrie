// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Zhuang yuteng
// Student Number	: S10163964C

#include "weaponManager.h"
#include "distractedState.h"
#include "alertState.h"

WeaponManager::WeaponManager()
{
	Tick = GetTickCount();
	Tick2 = GetTickCount();
}

bool WeaponManager::initializeArrow(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM, float X, float Y, Entity &player, KeyBinding *key)
{
	bool is_initialised_arrow = true;
	Arrow *arrow = arrow_collection.back();
	
	is_initialised_arrow = (arrow)->initialize(gamePtr, width, height, ncols, textureM);	
	(arrow)->setFrames(arrowNS::ARROW_START_FRAME, arrowNS::ARROW_END_FRAME);
	(arrow)->setCurrentFrame(arrowNS::ARROW_START_FRAME);

	if (player.isFlipHorizontal())
	{
		(arrow)->flipHorizontal(true);
		(arrow)->setVelocity(VECTOR2(-arrowNS::SPEED, arrowNS::SPEED));
	}


	else
	{
		(arrow)->flipHorizontal(false);
		(arrow)->setVelocity(VECTOR2(arrowNS::SPEED, arrowNS::SPEED));
	}

	(arrow)->setX(X - arrowNS::WIDTH / 2);
	(arrow)->setY(Y-3);

	if (!is_initialised_arrow)
		return is_initialised_arrow;

	return is_initialised_arrow;
}

bool WeaponManager::initializeStone(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM, float X, float Y, Entity &player)
{
	
	bool is_initialised_stone = true;
	Stone *stone = stone_collection.back();
	
	is_initialised_stone = (stone)->initialize(gamePtr, width, height, ncols, textureM);
	
	(stone)->setFrames(stoneNS::STONE_START_FRAME, stoneNS::STONE_END_FRAME);
	(stone)->setCurrentFrame(stoneNS::STONE_START_FRAME);

	if (player.isFlipHorizontal())
	{
		(stone)->setThrowingRight(false);
	}
	else
	{
		(stone)->setThrowingRight(true);
	}

	(stone)->setX(X - stoneNS::WIDTH / 2);
	(stone)->setY(Y);

	if (!is_initialised_stone)
		return is_initialised_stone;

	return is_initialised_stone;
}


void WeaponManager::update(float frameTime, Input *input, Game *gamePtr, int width, int height, int arrowcols, int stonecols,
	TextureManager *textureM, Player &player, KeyBinding *key, Audio *a)
{
	int X = player.getCenterX();
	int Y = player.getY();

	if (input->isKeyDown(key->getRangeKey()))
	{
		if (GetTickCount() - Tick > 500 && player.getTotalArrow()>0)
		{
			Tick = GetTickCount();
			arrow_collection.push_back(new Arrow());
			player.setTotalArrow(player.getTotalArrow() - 1);
			a->playCue(PLAYERRANGE);
			initializeArrow(gamePtr, width, height, arrowcols, textureM, X, Y, player, key);
		}
	}

	else if (input->isKeyDown(key->getDistractKey()) )
	{
		if (GetTickCount() - Tick2 > 500 && player.getTotalStone()>0)
		{
			Tick2 = GetTickCount();
			stone_collection.push_back(new Stone());
			player.setTotalStone(player.getTotalStone() - 1);
			initializeStone(gamePtr, width, height,stonecols, textureM, X, Y, player);
		}
	}
	for (std::vector<Arrow *>::iterator arrow = arrow_collection.begin(); arrow < arrow_collection.end(); ++arrow)
	{
		(*arrow)->update(frameTime);
	}

	for (std::vector<Stone *>::iterator stone = stone_collection.begin(); stone < stone_collection.end(); ++stone)
	{
		(*stone)->update(frameTime);
	}
}

void WeaponManager::ai() {}

void WeaponManager::collisions(EnemyManager *enemyList, Player *player, PLATFORM floor)
{
	VECTOR2 collisionVector;
	GUNNERLIST *gunnerCollection = enemyList->getGunners();
	TROOPERLIST *trooperCollection = enemyList->getTroopers();
	SERPANTLIST *serpantCollection = enemyList->getSerpants();

	ARROWLIST::iterator it = arrow_collection.begin();
	while (it != arrow_collection.end())
	{
		for (GUNNERLIST::iterator gunner = (gunnerCollection->begin()); gunner != gunnerCollection->end(); gunner++)
		{
			if ((*gunner)->collidesWith(**it, collisionVector) && (*gunner)->isAlive() && !(*gunner)->outOfBounds() )
			{
				(*gunner)->getHealth()->damage(gunnerNS::HEALTH / 2);
				(*gunner)->handleInput(new AlertedState());
				(*it)->setVisible(false);
				(*it)->setActive(false);
				if (!(*gunner)->isAlive() && (player->getCurrentTotalLevel() < player->getTotalLevels()))
					player->setTotalXP(player->getTotalXP() + 10);
				break;
			}
		}
		for (TROOPERLIST::iterator trooper = (trooperCollection->begin()); trooper != trooperCollection->end(); trooper++)
		{
			if ((*trooper)->collidesWith(**it, collisionVector) && (*trooper)->isAlive() && !(*trooper)->outOfBounds())
			{
				(*trooper)->getHealth()->damage(trooperNS::HEALTH/2);
				(*trooper)->handleInput(new AlertedState());
				(*it)->setVisible(false);
				(*it)->setActive(false);
				if (!(*trooper)->isAlive() && (player->getCurrentTotalLevel() < player->getTotalLevels()))
					player->setTotalXP(player->getTotalXP() + 10);
				break;
			}
		}
		for (SERPANTLIST::iterator serpant = (serpantCollection->begin()); serpant != serpantCollection->end(); serpant++)
		{
			if ((*serpant)->collidesWith(**it, collisionVector) && (*serpant)->isAlive() && !(*serpant)->outOfBounds())
			{
				(*serpant)->getHealth()->damage(serpantNS::HEALTH / 3);
				(*serpant)->handleInput(new AlertedState());
				(*it)->setVisible(false);
				(*it)->setActive(false);
				if (!(*serpant)->isAlive() && (player->getCurrentTotalLevel() < player->getTotalLevels()))
					player->setTotalXP(player->getTotalXP() + 20);
				break;
			}
		}

		if (!(*it)->getActive())
			it = arrow_collection.erase(it);
		else
			it++;
	}

	STONELIST::iterator stone = stone_collection.begin();
	while (stone != stone_collection.end())
	{
		bool floorCollision = false;
		for (Entity *f : floor)
			if ((*stone)->collidesWith(*f, collisionVector))
			{
				floorCollision = true;
				break;
			}
		if (floorCollision)
		{
			for (Enemy *e : *enemyList->getWorlds())
			{
				VECTOR2 unit = *e->getCenter() - *(*stone)->getCenter();
				if (D3DXVec2Length(&unit) < stoneNS::RANGE)
					e->handleInput(new DistractedState(*(*stone)->getCenter()));
			}
			stone = stone_collection.erase(stone);
		}
		else if ((*stone)->outOfBounds())
			stone = stone_collection.erase(stone);
		else
			stone++;
	}
}

void WeaponManager::render()
{
	for (std::vector<Arrow *>::iterator it = arrow_collection.begin(); it < arrow_collection.end(); ++it)
	{
		(*it)->draw();
	}

	for (std::vector<Stone *>::iterator stone = stone_collection.begin(); stone <stone_collection.end(); ++stone)
	{
		(*stone)->draw();
	}
}