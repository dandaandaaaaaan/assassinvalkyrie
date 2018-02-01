// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Zhuang yuteng
// Student Number	: S10163964C

#ifndef _PLAYER_H 
#define _PLAYER_H
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include "PlayerState.h"
#include "StandingState.h"
#include "enemyManager.h"
#include "stageGenerator.h"

namespace playerNS
{
	const int	HEALTH = 20;
	const int	WIDTH = 57.15;
	const int	HEIGHT = 96;
	const double ROTATION = 0;
	const float SCALE = 1.0f;
	const int	X = GAME_WIDTH / 4 ;
	//const int	Y = GAME_HEIGHT/2-100 ;
	const int	Y = 500;
	const float SPEED = 100;
	const float MASS = 300.0f;
	const int   TEXTURE_COLS = 1;
	const int   START_FRAME =0;
	const int   END_FRAME = 0;
	const float ANIMATION_DELAY = 0.5f;
	const int	START_LEVEL = 1;
	const int	TOTAL_LEVELS = 9;
}



class Player : public Entity
{
protected:
	bool jumpRight = false;
	bool jumpLeft = false;
	bool isMeleeAttacking = false;
	int totalXP;
	int totalLevels;
	int currentTotalLevel;
	int stealthLevel;
	int speedLevel;
	int rangeLevel;
	int armorLevel;
	PlayerState* state_;
	int skillPointAvailable;
public:
	// constructor
	Player();


	// inherited member functions
	bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
	void update(float frameTime, Game *gamePtr, TextureManager *textureM, StageGenerator *stagegenerator);
	void handleInput(Input* input, Game *gamePtr, TextureManager *textureM, StageGenerator *stagegenerator);
	void ai(Entity &ship1, Entity &ship2);
	void collisions(EnemyManager *enemyList);
	void draw();
	bool getJumpRight()
	{
		return jumpRight;
	}

	void setJumpRight(bool condition)
	{
		jumpRight = condition;
	}

	bool getJumpLeft()
	{
		return jumpLeft;
	}

	void setJumpLeft(bool condition)
	{
		jumpLeft = condition;
	}
	void IsMeleeAttacking(bool condition)
	{
		isMeleeAttacking = condition;
	}
	void setStealthLevel() { stealthLevel++; }
	int getStealthLevel() { return stealthLevel; }

	void setSpeedLevel() { speedLevel++; }
	int getSpeedLevel() { return speedLevel; }

	void setArmorLevel() { armorLevel++; }
	int getArmorLevel() { return armorLevel; }

	void setRangeLevel() { rangeLevel++; }
	int getRangeLevel() { return rangeLevel; }

	void setTotalXP(int i) { totalXP = i; }
	int getTotalXP() { return totalXP; }

	int getTotalLevels() { return totalLevels; }
	int getCurrentTotalLevel() { return currentTotalLevel; }

	int getSkillPoints() { return skillPointAvailable; }
	void useSkillPoints() { skillPointAvailable--; }
};
#endif