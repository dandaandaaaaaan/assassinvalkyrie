// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Chua Wei Jie Timothy
// Student Number	: S10165581F

#ifndef _ENEMY_STATE_H 
#define _ENEMY_STATE_H
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "rayCasting.h"

class Enemy;

class EnemyState
{
protected:
	int maxTime;
	int timer;

public:
	EnemyState() { timer = GetTickCount(); }
	virtual ~EnemyState() {}
	virtual EnemyState* handleInput(Enemy *enemy, Entity *target, PLATFORM p, Input *i) { return new EnemyState(); }
	virtual void update(Enemy *enemy, Entity *target);
};//end of EnemyState class
#endif