// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Chua Wei Jie Timothy
// Student Number	: S10165581F

#include "enemy.h"
#include "enemyState.h"
#include "alertState.h"
#include "standState.h"
#include "patrolState.h"
#include "returnState.h"

void EnemyState::update(Enemy *enemy, Entity *target)
{
	enemy->getMove()->setVelocity(enemy->getMove()->getCurrentVelocity());
}

PatrollingState::PatrollingState() : EnemyState()
{
	maxTime = 8000;
}

EnemyState* PatrollingState::handleInput(Enemy *enemy, Entity *target, PLATFORM p)
{
	if (enemy->getRay()->inSight(*target->getCenter(),p))
	{
		enemy->getRay()->setColor(graphicsNS::YELLOW);
		return new AlertedState();
	}
	return NULL;
}

void PatrollingState::update(Enemy *enemy, Entity *target)
{
	if (GetTickCount() - timer > maxTime)
	{
		enemy->getMove()->setVelocity(-enemy->getMove()->getCurrentVelocity());
		timer = GetTickCount();
	}
}

AlertedState::AlertedState() : EnemyState()
{
	maxTime = 5000;
}

EnemyState* AlertedState::handleInput(Enemy *enemy, Entity *target, PLATFORM p)
{
	if (GetTickCount() - timer > maxTime)
		if (!(enemy->getRay()->inSight(*target->getCenter(), p)))
			return new StandingState();
		else
			timer = GetTickCount();
	return NULL;
}

bool sameSign(int x, int y)
{
	return (x >= 0) ^ (y < 0);
}

void AlertedState::update(Enemy *enemy, Entity *target)
{
	VECTOR2 direction = VECTOR2(target->getX() - enemy->getX(), target->getY() - enemy->getY());
	direction = *D3DXVec2Normalize(&direction, &direction);
	enemy->getMove()->setVelocity(direction.x * enemy->getMove()->getInitialVelocity());
	VECTOR2 pos1 = *enemy->getCenter() - *target->getCenter();

	if (D3DXVec2Length(&pos1) < enemy->getRange() && !enemy->getAttack()->getAnimation())
	{
		enemy->getAttack()->setAnimation(true);
		enemy->getAnimation()->setCurrentFrame(enemy->getAttackFrame());
	}
}

StandingState::StandingState() : EnemyState()
{
	maxTime = 3000;
}

EnemyState* StandingState::handleInput(Enemy *enemy, Entity *target, PLATFORM p)
{
	enemy->getMove()->setVelocity(0);
	if (GetTickCount() - timer > maxTime)
	{
		enemy->getRay()->setColor(graphicsNS::WHITE);
		enemy->getMove()->setVelocity(enemy->getMove()->getInitialVelocity());
		return new ReturningState();
	}
	return NULL;
}

ReturningState::ReturningState()
{
	timer = 0;
	maxTime = 1000;
}

EnemyState* ReturningState::handleInput(Enemy *enemy, Entity *target, PLATFORM p)
{
	if (enemy->getMove()->returnOrigin())
	{
		enemy->getMove()->setVelocity(enemy->getMove()->getInitialVelocity());
		return new PatrollingState();
	}
	for (Entity *e : p)
		if (enemy->collidesWith(*e, VECTOR2{}))
		{
			enemy->getMove()->setVelocity(-enemy->getMove()->getCurrentVelocity());
			enemy->setOriginalPos({ enemy->getX(), enemy->getY() });
			return new PatrollingState();
		}

	return NULL;
}