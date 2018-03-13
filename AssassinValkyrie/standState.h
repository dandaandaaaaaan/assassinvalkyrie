// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Chua Wei Jie Timothy
// Student Number	: S10165581F

#ifndef _ENEMY_STAND_STATE_H 
#define _ENEMY_STAND_STATE_H
#define WIN32_LEAN_AND_MEAN

#include "enemyState.h"

class StandingState : public EnemyState
{
public:
	StandingState();
	virtual EnemyState* handleInput(Enemy *enemy, Entity *target, PLATFORM p, Input *i);
};//end of StandingState class
#endif