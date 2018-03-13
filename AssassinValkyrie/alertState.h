// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Chua Wei Jie Timothy
// Student Number	: S10165581F

#ifndef _ENEMY_ALERT_STATE_H 
#define _ENEMY_ALERT_STATE_H
#define WIN32_LEAN_AND_MEAN

#include "enemyState.h"

class AlertedState : public EnemyState
{
private:
	Entity lastSeen;

public:
	AlertedState();
	virtual EnemyState* handleInput(Enemy *enemy, Entity *target, PLATFORM p, Input *i);
	virtual void update(Enemy *enemy, Entity *target);
};//end of AlertedState class
#endif