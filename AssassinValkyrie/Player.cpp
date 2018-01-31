// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Zhuang yuteng
// Student Number	: S10163964C

#include "Player.h"

Player::Player() : Entity()
{
	state_ = new StandState();
	spriteData.width = playerNS::WIDTH;           // size of Ship1
	spriteData.height = playerNS::HEIGHT;
	spriteData.x = playerNS::X;                   // location on screen
	spriteData.y = playerNS::Y;
	spriteData.rect.bottom = playerNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = playerNS::WIDTH;
	spriteData.angle = playerNS::ROTATION;
	spriteData.scale = playerNS::SCALE;

	frameDelay = playerNS::ANIMATION_DELAY;
	startFrame = playerNS::START_FRAME;     // first frame of ship animation
	endFrame = playerNS::END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	edge = RECT{ (long)(-playerNS::WIDTH*playerNS::SCALE / 2), (long)(-playerNS::HEIGHT*playerNS::SCALE / 2), (long)(playerNS::WIDTH*playerNS::SCALE / 2), (long)(playerNS::HEIGHT*playerNS::SCALE / 2) };
	collisionType = entityNS::BOX;
	totalXP = 0;
	totalLevels = playerNS::TOTAL_LEVELS;
	stealthLevel = playerNS::START_LEVEL;
	speedLevel = playerNS::START_LEVEL;
	rangeLevel = playerNS::START_LEVEL;
	armorLevel = playerNS::START_LEVEL;
	currentTotalLevel = 4;
	skillPointAvailable = 0;
	playerInput = true;
}

bool Player::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM)
{
	
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}
int returnXPToNextLevel(int i) {
	return ((i - 3) * 50);
}
void Player::update(float frameTime, Game *gamePtr, TextureManager *textureM, StageGenerator *stagegenerator)
{
	if (totalXP >= returnXPToNextLevel(currentTotalLevel)) {
		currentTotalLevel++;
		skillPointAvailable++;
		totalXP = 0;
	}
	handleInput(input,gamePtr,textureM,stagegenerator);
	state_->update(*this, frameTime, playerInput);


	
	Entity::update(frameTime);

	//move->update(frameTime);
}

void Player::handleInput(Input* input, Game *gamePtr, TextureManager *textureM, StageGenerator *stagegenerator)
{
    PlayerState* state = state_->handleInput(*this, input,gamePtr,textureM,stagegenerator);
	if (state != NULL)
	{
		delete state_;
		state_ = state;
	}
}

void Player::collisions(EnemyManager *enemyList, StageGenerator *stageGenerator)
{
	VECTOR2 collisionVector;
	GUNNERLIST *gunnerCollection = enemyList->getGunners();
	TROOPERLIST *trooperCollection = enemyList->getTroopers();
	SERPANTLIST *serpantCollection = enemyList->getSerpants();
	//FILLS *fillCollection = stageGenerator->getFills();
	
	for (GUNNERLIST::iterator gunner = (gunnerCollection->begin()); gunner != gunnerCollection->end(); gunner++)
	{
		if (collidesWith(**gunner,collisionVector))
		{
			
			if (isMeleeAttacking == true)
			{
				(*gunner)->getHealth()->damage(gunnerNS::HEALTH);
				isMeleeAttacking = false;
				if (!(*gunner)->getHealth()->getAlive() && (currentTotalLevel < totalLevels))
					totalXP += 50;
				break;
			}
		}
	}
	for (TROOPERLIST::iterator trooper = (trooperCollection->begin()); trooper != trooperCollection->end(); trooper++)
	{
		if (collidesWith(**trooper, collisionVector))
		{
			if (isMeleeAttacking == true)
			{
				(*trooper)->getHealth()->damage(trooperNS::HEALTH);
				isMeleeAttacking = false;
				if (!(*trooper)->getHealth()->getAlive() && (currentTotalLevel < totalLevels))
					totalXP += 50;
				break;
			}
		}
	}
	for (SERPANTLIST::iterator serpant = (serpantCollection->begin()); serpant != serpantCollection->end(); serpant++)
	{
		if (collidesWith(**serpant, collisionVector))
		{
			if (isMeleeAttacking == true)
			{
				(*serpant)->getHealth()->damage(serpantNS::HEALTH/2);
				isMeleeAttacking = false;
				if (!(*serpant)->getHealth()->getAlive() && (currentTotalLevel < totalLevels))
					totalXP += 100;
				break;
			}
		}
	}
	//for (FILLS::iterator fill = (fillCollection->begin()); fill != fillCollection->end(); fill++)
	//{
	//	if (collidesWith(**fill, collisionVector))
	//	{
	//		background->setVelocity(VECTOR2(0, 0));
	//	}
	//}
}

// To find closest ship vector position
void Player::ai(Entity &ship1, Entity &ship2)
{
}

void Player::draw()
{
	
	Image::draw();              // draw ship
}
