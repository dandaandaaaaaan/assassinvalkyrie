// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Zhuang yuteng
// Student Number	: S10163964C

#include "Player.h"
#include "RunningState.h"
#include "StandingState.h"
#include "CrouchingState.h"
#include "MeleeAttackState.h"
#include "CrouchWalkingState.h"
#include "JumpingState.h"
#include "RangeAttackState.h"
#include "FallingState.h"
#include "ThrowingState.h"
#include "AssassinateState.h"
#include "keyBinding.h"
#include "ClimbReadyState.h"
#include "ClimbingState.h"


PlayerState* StandState::handleInput(Player& player, Input* input, Game *gamePtr, TextureManager *textureM, StageGenerator *stagegenerator,EnemyManager *enemyList, PLATFORM p, Audio *a)
{
	KeyBinding key;
	player.setCollideWithVision(false);
	VECTOR2 collisionVector;
	GUNNERLIST *gunnerCollection = enemyList->getGunners();
	TROOPERLIST *trooperCollection = enemyList->getTroopers();
	SERPANTLIST *serpantCollection = enemyList->getSerpants();
	LADDERS *ladderCollection = stagegenerator->getLadders();

	Player *playerpointer;
	playerpointer = &player;

	for (GUNNERLIST::iterator gunner = (gunnerCollection->begin()); gunner != gunnerCollection->end(); gunner++)
	{
		if ((*gunner)->getRay()->inSight(*playerpointer->getCenter(),p))
		{
			
			player.setCollideWithVision(true);
		
		}
	}
	for (TROOPERLIST::iterator trooper = (trooperCollection->begin()); trooper != trooperCollection->end(); trooper++)
	{
		if ((*trooper)->getRay()->inSight(*playerpointer->getCenter(), p))
		{

			player.setCollideWithVision(true);

		}
	}
	for (SERPANTLIST::iterator serpant = (serpantCollection->begin()); serpant != serpantCollection->end(); serpant++)
	{
		if ((*serpant)->getRay()->inSight(*playerpointer->getCenter(), p))
		{

			player.setCollideWithVision(true);

		}
	}

	for (LADDERS::iterator ladder = (ladderCollection->begin()); ladder != ladderCollection->end(); ladder++)
	{
		if (player.collidesWith(**ladder, collisionVector))
		{
			if (input->isKeyDown(CLIMBING_UP_KEY) || input->isKeyDown(CLIMBING_DOWN_KEY))
			{
				player.initialize(gamePtr,CLIMB_READY_STATE::WIDTH, CLIMB_READY_STATE::HEIGHT, CLIMB_READY_STATE::TEXTURE_COLS, textureM);
				player.setFrames(CLIMB_READY_STATE::START_FRAME, CLIMB_READY_STATE::END_FRAME);
				player.setCurrentFrame(CLIMB_READY_STATE::START_FRAME);
				return new ClimbReadyState();
			}
		}
	}

	if (!player.isCollidingWithVision())
	{
		if (input->isKeyDown(key.getAssassinateKey()))
		{
			player.initialize(gamePtr, ASSASSINATE_STATE::WIDTH, ASSASSINATE_STATE::HEIGHT, ASSASSINATE_STATE::TEXTURE_COLS, textureM);
			player.setFrames(ASSASSINATE_STATE::START_FRAME, ASSASSINATE_STATE::END_FRAME);
			player.setCurrentFrame(ASSASSINATE_STATE::START_FRAME);
			player.setFrameDelay(0.3);
			player.setLoop(false);
			player.IsAssassinating(true);
			return new AssassinateState();
		}
	}
	if (input->isKeyDown(key.getRightKey()))
	{
		player.initialize(gamePtr, RUNNING_STATE::WIDTH, RUNNING_STATE::HEIGHT, RUNNING_STATE::TEXTURE_COLS, textureM);
		player.setFrames(RUNNING_STATE::START_FRAME, RUNNING_STATE::END_FRAME);
		player.setCurrentFrame(RUNNING_STATE::START_FRAME);
		player.setFrameDelay(0.2);
		player.flipHorizontal(false);
		player.setLoop(true);
		player.setVelocity(VECTOR2(RUNNING_STATE::RUNNING_SPEED*player.calcMultipler(player.getSpeedLevel()), RUNNING_STATE::RUNNING_SPEED*player.calcMultipler(player.getSpeedLevel())));
		return new RunningState();
	}

	else if (input->isKeyDown(key.getLeftKey()))
	{
		player.initialize(gamePtr, RUNNING_STATE::WIDTH, RUNNING_STATE::HEIGHT, RUNNING_STATE::TEXTURE_COLS, textureM);
		player.flipHorizontal(true);
		player.setFrames(RUNNING_STATE::START_FRAME, RUNNING_STATE::END_FRAME);
		player.setCurrentFrame(RUNNING_STATE::START_FRAME);
		player.setFrameDelay(0.2);
		player.setLoop(true);
		player.setVelocity(VECTOR2(-RUNNING_STATE::RUNNING_SPEED*player.calcMultipler(player.getSpeedLevel()), RUNNING_STATE::RUNNING_SPEED*player.calcMultipler(player.getSpeedLevel())));
		return new RunningState();
	}

	else if (input->isKeyDown(key.getDownKey()))
	{
		player.initialize(gamePtr, CROUCHING_STATE::WIDTH, CROUCHING_STATE::HEIGHT, CROUCHING_STATE::TEXTURE_COLS, textureM);
		player.setFrames(CROUCHING_STATE::START_FRAME, CROUCHING_STATE::END_FRAME);
		player.setCurrentFrame(CROUCHING_STATE::START_FRAME);
		return new CrouchingState();
		
	}

	else if (input->isKeyDown(key.getMeleeKey()))
	{
		player.initialize(gamePtr, MELEE_ATTACK_STATE::WIDTH, MELEE_ATTACK_STATE::HEIGHT, MELEE_ATTACK_STATE::TEXTURE_COLS, textureM);
		player.setFrames(MELEE_ATTACK_STATE::START_FRAME, MELEE_ATTACK_STATE::END_FRAME);
		player.setCurrentFrame(MELEE_ATTACK_STATE::START_FRAME);
		player.setFrameDelay(0.1);
		player.setLoop(false);
		player.IsMeleeAttacking(true);
		a->playCue(PLAYERMELEE);
		return new MeleeAttackState();

	}

	else if (input->isKeyDown(key.getRangeKey()))
	{
		player.initialize(gamePtr, RANGE_ATTACK_STATE::WIDTH, RANGE_ATTACK_STATE::HEIGHT, RANGE_ATTACK_STATE::TEXTURE_COLS, textureM);
		player.setFrames(RANGE_ATTACK_STATE::START_FRAME, RANGE_ATTACK_STATE::END_FRAME);
		player.setCurrentFrame(RANGE_ATTACK_STATE::START_FRAME);
		player.setFrameDelay(0.1);
		player.setLoop(false);
		return new RangeAttackState();

	}

	else if (input->isKeyDown(key.getDistractKey()))
	{
		player.initialize(gamePtr, THROWING_STATE::WIDTH, THROWING_STATE::HEIGHT, THROWING_STATE::TEXTURE_COLS, textureM);
		player.setFrames(THROWING_STATE::START_FRAME, THROWING_STATE::END_FRAME);
		player.setCurrentFrame(THROWING_STATE::START_FRAME);
		player.setFrameDelay(0.3);
		player.setLoop(false);
		return new ThrowingState();

	}

	return NULL;
}

PlayerState* RunningState::handleInput(Player& player, Input* input, Game *gamePtr, TextureManager *textureM,  StageGenerator *stagegenerator, EnemyManager *enemyList, PLATFORM p, Audio *a)
{
	KeyBinding key;
	player.setOnGround(false);
	player.setCollideWithVision(false);
	VECTOR2 collisionVector;

	//FILLS *fillCollection = stagegenerator->getFills();
	FLOORS *floorCollection = stagegenerator->getFloors();
	GUNNERLIST *gunnerCollection = enemyList->getGunners();
	TROOPERLIST *trooperCollection = enemyList->getTroopers();
	SERPANTLIST *serpantCollection = enemyList->getSerpants();

	Player *playerpointer;
	playerpointer = &player;

	for (GUNNERLIST::iterator gunner = (gunnerCollection->begin()); gunner != gunnerCollection->end(); gunner++)
	{
		if ((*gunner)->getRay()->inSight(*playerpointer->getCenter(), p))
		{

			player.setCollideWithVision(true);

		}
	}
	for (TROOPERLIST::iterator trooper = (trooperCollection->begin()); trooper != trooperCollection->end(); trooper++)
	{
		if ((*trooper)->getRay()->inSight(*playerpointer->getCenter(), p))
		{

			player.setCollideWithVision(true);

		}
	}
	for (SERPANTLIST::iterator serpant = (serpantCollection->begin()); serpant != serpantCollection->end(); serpant++)
	{
		if ((*serpant)->getRay()->inSight(*playerpointer->getCenter(), p))
		{

			player.setCollideWithVision(true);

		}
	}

	
	for (FLOORS::iterator floor = (floorCollection->begin()); floor != floorCollection->end(); floor++)
	{
		if (player.collidesWith(**floor, collisionVector))
		{
			player.setOnGround(true);
		
		}
	}


	//VECTOR2 collisionVector;
	//FILLS *fillCollection = stagegenerator->getFills();
	//for (FILLS::iterator fill = (fillCollection->begin()); fill != fillCollection->end(); fill++)
	//{
	//	if (player.collidesWith(**fill, collisionVector))
	//	{
	//		if (!player.isFlipHorizontal())
	//		{
	//			player.setX((*fill)->getX() - RUNNING_STATE::WIDTH);
	//		}

	//		else
	//		{
	//			player.setX((*fill)->getX() + RUNNING_STATE::WIDTH);
	//		}
	//		
	//	}
	//} 
	if (!player.isCollidingWithVision())
	{
		if (input->isKeyDown(key.getAssassinateKey()))
		{
			player.initialize(gamePtr, ASSASSINATE_STATE::WIDTH, ASSASSINATE_STATE::HEIGHT, ASSASSINATE_STATE::TEXTURE_COLS, textureM);
			player.setFrames(ASSASSINATE_STATE::START_FRAME, ASSASSINATE_STATE::END_FRAME);
			player.setCurrentFrame(ASSASSINATE_STATE::START_FRAME);
			player.setFrameDelay(0.3);
			player.setLoop(false);
			player.IsAssassinating(true);
			return new AssassinateState();
		}
	}

	if(!player.isOnGround())
	{
		player.initialize(gamePtr, FALLING_STATE::WIDTH, FALLING_STATE::HEIGHT, FALLING_STATE::TEXTURE_COLS, textureM);
		player.setFrames(FALLING_STATE::START_FRAME, FALLING_STATE::END_FRAME);
		player.setCurrentFrame(FALLING_STATE::START_FRAME);
		return new FallingState();
	}

	if (!input->isKeyDown(key.getRightKey())&& !input->isKeyDown(key.getLeftKey()))
	{
		player.initialize(gamePtr, STANDING_STATE::WIDTH, STANDING_STATE::HEIGHT, STANDING_STATE::TEXTURE_COLS, textureM);
		player.setFrames(STANDING_STATE::START_FRAME, STANDING_STATE::END_FRAME);
		player.setCurrentFrame(STANDING_STATE::START_FRAME);
		return new StandState();
	}

	else if (input->isKeyDown(key.getJumpKey()) && input->isKeyDown(key.getRightKey()))
	{
		
				player.initialize(gamePtr, JUMPING_STATE::WIDTH, JUMPING_STATE::HEIGHT, JUMPING_STATE::TEXTURE_COLS, textureM);
				player.setFrames(JUMPING_STATE::START_FRAME, JUMPING_STATE::END_FRAME);
				player.setCurrentFrame(JUMPING_STATE::START_FRAME);
				player.setFrameDelay(0.2);
				player.flipHorizontal(false);
				player.setLoop(false);
				player.setJumpRight(true);
				return new JumpingState();

		
	}

	else if (input->isKeyDown(key.getJumpKey()) && input->isKeyDown(key.getLeftKey()))
	{
		player.initialize(gamePtr, JUMPING_STATE::WIDTH, JUMPING_STATE::HEIGHT, JUMPING_STATE::TEXTURE_COLS, textureM);
		player.setFrames(JUMPING_STATE::START_FRAME, JUMPING_STATE::END_FRAME);
		player.setCurrentFrame(JUMPING_STATE::START_FRAME);
		player.setFrameDelay(0.2);
		player.flipHorizontal(true);
		player.setLoop(false);
		player.setJumpLeft(true);
		return new JumpingState();
	}

	else if (input->isKeyDown(key.getMeleeKey()))
	{
		player.initialize(gamePtr, MELEE_ATTACK_STATE::WIDTH, MELEE_ATTACK_STATE::HEIGHT, MELEE_ATTACK_STATE::TEXTURE_COLS, textureM);
		player.setFrames(MELEE_ATTACK_STATE::START_FRAME, MELEE_ATTACK_STATE::END_FRAME);
		player.setCurrentFrame(MELEE_ATTACK_STATE::START_FRAME);
		player.setFrameDelay(0.1);
		player.setLoop(false);
		player.IsMeleeAttacking(true);
		a->playCue(PLAYERMELEE);
		return new MeleeAttackState();

	}



	return NULL;
}

PlayerState* CrouchingState::handleInput(Player& player, Input* input, Game *gamePtr, TextureManager *textureM, StageGenerator *stagegenerator, EnemyManager *enemyList, PLATFORM p, Audio *a)
{
	KeyBinding key;
	if (!input->isKeyDown(key.getDownKey()))
	{
		player.initialize(gamePtr, STANDING_STATE::WIDTH, STANDING_STATE::HEIGHT, STANDING_STATE::TEXTURE_COLS, textureM);
		player.setFrames(STANDING_STATE::START_FRAME, STANDING_STATE::END_FRAME);
		player.setCurrentFrame(STANDING_STATE::START_FRAME);
		return new StandState();
	}

	else if (input->isKeyDown(key.getRightKey()))
	{
		player.initialize(gamePtr, CROUCH_WALKING_STATE::WIDTH, CROUCH_WALKING_STATE::HEIGHT, CROUCH_WALKING_STATE::TEXTURE_COLS, textureM);
		player.setFrames(CROUCH_WALKING_STATE::START_FRAME, CROUCH_WALKING_STATE::END_FRAME);
		player.setCurrentFrame(CROUCH_WALKING_STATE::START_FRAME);
		player.setFrameDelay(0.2);
		player.flipHorizontal(false);
		player.setLoop(true);
		player.setVelocity(VECTOR2(CROUCH_WALKING_STATE::CROUCH_WALKING_SPEED*player.calcMultipler(player.getSpeedLevel()), CROUCH_WALKING_STATE::CROUCH_WALKING_SPEED*player.calcMultipler(player.getSpeedLevel())));
		return new CrouchWalkingState();
	}

	else if (input->isKeyDown(key.getLeftKey()))
	{
		player.initialize(gamePtr, CROUCH_WALKING_STATE::WIDTH, CROUCH_WALKING_STATE::HEIGHT, CROUCH_WALKING_STATE::TEXTURE_COLS, textureM);
		player.setFrames(CROUCH_WALKING_STATE::START_FRAME, CROUCH_WALKING_STATE::END_FRAME);
		player.setCurrentFrame(CROUCH_WALKING_STATE::START_FRAME);
		player.setFrameDelay(0.2);
		player.flipHorizontal(true);
		player.setLoop(true);
		player.setVelocity(VECTOR2(-CROUCH_WALKING_STATE::CROUCH_WALKING_SPEED*player.calcMultipler(player.getSpeedLevel()), -CROUCH_WALKING_STATE::CROUCH_WALKING_SPEED*player.calcMultipler(player.getSpeedLevel())));
		return new CrouchWalkingState();
	}


	return NULL;
}

PlayerState* AssassinateState::handleInput(Player& player, Input* input, Game *gamePtr, TextureManager *textureM, StageGenerator *stagegenerator, EnemyManager *enemyList, PLATFORM p, Audio *a)
{
	
	if (player.getAnimationComplete())
	{

		player.initialize(gamePtr, STANDING_STATE::WIDTH, STANDING_STATE::HEIGHT, STANDING_STATE::TEXTURE_COLS, textureM);
		player.setFrames(STANDING_STATE::START_FRAME, STANDING_STATE::END_FRAME);
		player.setCurrentFrame(STANDING_STATE::START_FRAME);
		player.setLoop(true);
		player.IsAssassinating(false);
	
		return new StandState();

	}
	return NULL;
}

PlayerState* MeleeAttackState::handleInput(Player& player, Input* input, Game *gamePtr, TextureManager *textureM, StageGenerator *stagegenerator, EnemyManager *enemyList, PLATFORM p, Audio *a)
{
	if (player.getAnimationComplete())
	{
		
			player.initialize(gamePtr, STANDING_STATE::WIDTH, STANDING_STATE::HEIGHT, STANDING_STATE::TEXTURE_COLS, textureM);
			player.setFrames(STANDING_STATE::START_FRAME, STANDING_STATE::END_FRAME);
			player.setCurrentFrame(STANDING_STATE::START_FRAME);
			player.IsMeleeAttacking(false);
			player.setLoop(true);
			player.IsMeleeAttacking(false);
			return new StandState();
		
	}
	return NULL;
}

PlayerState* RangeAttackState::handleInput(Player& player, Input* input, Game *gamePtr, TextureManager *textureM, StageGenerator *stagegenerator, EnemyManager *enemyList, PLATFORM p, Audio *a)
{
	if (player.getAnimationComplete())
	{

		player.initialize(gamePtr, STANDING_STATE::WIDTH, STANDING_STATE::HEIGHT, STANDING_STATE::TEXTURE_COLS, textureM);
		player.setFrames(STANDING_STATE::START_FRAME, STANDING_STATE::END_FRAME);
		player.setCurrentFrame(STANDING_STATE::START_FRAME);
		player.setLoop(true);
		return new StandState();

	}
	return NULL;
}

PlayerState* ThrowingState::handleInput(Player& player, Input* input, Game *gamePtr, TextureManager *textureM, StageGenerator *stagegenerator, EnemyManager *enemyList, PLATFORM p, Audio *a)
{
	if (player.getAnimationComplete())
	{

		player.initialize(gamePtr, STANDING_STATE::WIDTH, STANDING_STATE::HEIGHT, STANDING_STATE::TEXTURE_COLS, textureM);
		player.setFrames(STANDING_STATE::START_FRAME, STANDING_STATE::END_FRAME);
		player.setCurrentFrame(STANDING_STATE::START_FRAME);
		player.setLoop(true);
		return new StandState();

	}
	return NULL;
}

PlayerState* CrouchWalkingState::handleInput(Player& player, Input* input, Game *gamePtr, TextureManager *textureM, StageGenerator *stagegenerator, EnemyManager *enemyList, PLATFORM p, Audio *a)
{
	KeyBinding key;
	//VECTOR2 collisionVector;
	//FILLS *fillCollection = stagegenerator->getFills();

	//for (FILLS::iterator fill = (fillCollection->begin()); fill != fillCollection->end(); fill++)
	//{
	//	if (player.collidesWith(**fill, collisionVector))
	//	{
	//		if (!player.isFlipHorizontal())
	//		{
	//			player.setX((*fill)->getX() - CROUCH_WALKING_STATE::WIDTH-30);
	//		}

	//		else
	//		{
	//			player.setX((*fill)->getX() + CROUCH_WALKING_STATE::WIDTH+30);
	//		}
	//		

	//	}
	//}

	if (!input->isKeyDown(key.getRightKey()) && !input->isKeyDown(key.getLeftKey()) || !input->isKeyDown(key.getDownKey()))
	{

		player.initialize(gamePtr, STANDING_STATE::WIDTH, STANDING_STATE::HEIGHT, STANDING_STATE::TEXTURE_COLS, textureM);
		player.setFrames(STANDING_STATE::START_FRAME, STANDING_STATE::END_FRAME);
		player.setCurrentFrame(STANDING_STATE::START_FRAME);
		return new StandState();

	}
	return NULL;
}

PlayerState* JumpingState::handleInput(Player& player, Input* input, Game *gamePtr, TextureManager *textureM, StageGenerator *stagegenerator, EnemyManager *enemyList, PLATFORM p, Audio *a)
{
	
	
	VECTOR2 collisionVector;
	FLOORS *floorCollection = stagegenerator->getFloors();
	FILLS *fillCollection = stagegenerator->getSides();

	for (FLOORS::iterator floor = (floorCollection->begin()); floor != floorCollection->end(); floor++)
	{
		if (player.collidesWith(**floor, collisionVector))
		{
			if (player.getJumpRight())
			{
				player.setJumpRight(false);
				player.initialize(gamePtr, STANDING_STATE::WIDTH, STANDING_STATE::HEIGHT, STANDING_STATE::TEXTURE_COLS, textureM);
				
				player.setFrames(STANDING_STATE::START_FRAME, STANDING_STATE::END_FRAME);
				player.setCurrentFrame(STANDING_STATE::START_FRAME);
				player.setLoop(true);
				return new StandState();
			}

			else if (player.getJumpLeft())
			{
				player.setJumpLeft(false);
				player.initialize(gamePtr, STANDING_STATE::WIDTH, STANDING_STATE::HEIGHT, STANDING_STATE::TEXTURE_COLS, textureM);
				
				player.setFrames(STANDING_STATE::START_FRAME, STANDING_STATE::END_FRAME);
				player.setCurrentFrame(STANDING_STATE::START_FRAME);
				player.setLoop(true);
				return new StandState();
			}
		}
	}

	//for (FILLS::iterator fill = (fillCollection->begin()); fill != fillCollection->end(); fill++)
	//{
		//if (player.collidesWith(**fill, collisionVector))
		//{
			//if (!player.isFlipHorizontal())
			//{
				//player.setX((*fill)->getX() - FALLING_STATE::WIDTH-10);
			//}

			//else
			//{
				//player.setX((*fill)->getX() + FALLING_STATE::WIDTH+10);
			//}
			
			//player.initialize(gamePtr, FALLING_STATE::WIDTH, FALLING_STATE::HEIGHT, FALLING_STATE::TEXTURE_COLS, textureM);
			//player.setFrames(FALLING_STATE::START_FRAME, FALLING_STATE::END_FRAME);
			//player.setCurrentFrame(FALLING_STATE::START_FRAME);
			//player.setVelocity(VECTOR2(FALLING_STATE::FALLING_SPEED*player.calcMultipler(player.getSpeedLevel()), FALLING_STATE::FALLING_SPEED*player.calcMultipler(player.getSpeedLevel())));
			//return new FallingState();

		//}
	//}

	return NULL;
}

PlayerState* FallingState::handleInput(Player& player, Input* input, Game *gamePtr, TextureManager *textureM, StageGenerator *stagegenerator, EnemyManager *enemyList, PLATFORM p, Audio *a)
{
	VECTOR2 collisionVector;
	FLOORS *floorCollection = stagegenerator->getFloors();

	for (FLOORS::iterator floor = (floorCollection->begin()); floor != floorCollection->end(); floor++)
	{
		if (player.collidesWith(**floor, collisionVector))
		{
			
			player.initialize(gamePtr, STANDING_STATE::WIDTH, STANDING_STATE::HEIGHT, STANDING_STATE::TEXTURE_COLS, textureM);
			player.setFrames(STANDING_STATE::START_FRAME, STANDING_STATE::END_FRAME);
			player.setCurrentFrame(STANDING_STATE::START_FRAME);
			return new StandState();

		}
	}

	return NULL;
}

PlayerState* ClimbReadyState::handleInput(Player& player, Input* input, Game *gamePtr, TextureManager *textureM, StageGenerator *stagegenerator, EnemyManager *enemyList, PLATFORM p, Audio *a)
{
	if (input->isKeyDown(CLIMBING_UP_KEY))
	{
		player.initialize(gamePtr, CLIMBING_STATE::WIDTH, CLIMBING_STATE::HEIGHT, CLIMBING_STATE::TEXTURE_COLS, textureM);
		player.setFrames(CLIMBING_STATE::START_FRAME, CLIMBING_STATE::END_FRAME);
		player.setCurrentFrame(CLIMBING_STATE::START_FRAME);
		player.setFrameDelay(0.2);
		player.setLoop(true);
		player.setVelocity(VECTOR2(CLIMBING_STATE::CLIMBING_SPEED*player.calcMultipler(player.getSpeedLevel()), -CLIMBING_STATE::CLIMBING_SPEED*player.calcMultipler(player.getSpeedLevel())));
		return new ClimbingState();
	}

	if (input->isKeyDown(CLIMBING_DOWN_KEY))
	{
		player.initialize(gamePtr, CLIMBING_STATE::WIDTH, CLIMBING_STATE::HEIGHT, CLIMBING_STATE::TEXTURE_COLS, textureM);
		player.setFrames(CLIMBING_STATE::START_FRAME, CLIMBING_STATE::END_FRAME);
		player.setCurrentFrame(CLIMBING_STATE::START_FRAME);
		player.setFrameDelay(0.2);
		player.setLoop(true);
		player.setVelocity(VECTOR2(CLIMBING_STATE::CLIMBING_SPEED*player.calcMultipler(player.getSpeedLevel()), CLIMBING_STATE::CLIMBING_SPEED*player.calcMultipler(player.getSpeedLevel())));
		return new ClimbingState();
	}
	return NULL;
}

PlayerState* ClimbingState::handleInput(Player& player, Input* input, Game *gamePtr, TextureManager *textureM, StageGenerator *stagegenerator, EnemyManager *enemyList, PLATFORM p, Audio *a)
{
	player.setCollideWithLadder(false);
	LADDERS *ladderCollection = stagegenerator->getLadders();
	VECTOR2 collisionVector;

	for (LADDERS::iterator ladder = (ladderCollection->begin()); ladder != ladderCollection->end(); ladder++)
	{
		if (player.collidesWith(**ladder, collisionVector))
		{
			player.setCollideWithLadder(true);
		}
	}

	if (!player.isCollidingWithLadder())
	{
		player.initialize(gamePtr, STANDING_STATE::WIDTH, STANDING_STATE::HEIGHT, STANDING_STATE::TEXTURE_COLS, textureM);
		player.setFrames(STANDING_STATE::START_FRAME, STANDING_STATE::END_FRAME);
		player.setCurrentFrame(STANDING_STATE::START_FRAME);
		return new StandState();
	}
	if (!input->isKeyDown(CLIMBING_UP_KEY) && !input->isKeyDown(CLIMBING_DOWN_KEY))
	{
		player.initialize(gamePtr, CLIMB_READY_STATE::WIDTH, CLIMB_READY_STATE::HEIGHT, CLIMB_READY_STATE::TEXTURE_COLS, textureM);
		player.setFrames(CLIMB_READY_STATE::START_FRAME, CLIMB_READY_STATE::END_FRAME);
		player.setCurrentFrame(CLIMB_READY_STATE::START_FRAME);
		return new ClimbReadyState();
	}
	
	return NULL;
}