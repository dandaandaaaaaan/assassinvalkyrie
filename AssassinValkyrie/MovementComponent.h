// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Chua Wei Jie Timothy
// Student Number	: S10165581F

#ifndef _MOVE_COMPONENT_H
#define _MOVE_COMPONENT_H
#define WIN32_LEAN_AND_MEAN

#include "entity.h"

namespace MovementComponentNS {
	const int cameraVelocity = 150;
}
class MovementComponent
{
protected:
	Entity *object;
	VECTOR2 origin;
	int initialVelocity = 0;
	int currentVelocity;

public:
	MovementComponent(Entity* ent);

	void setVelocity(int speed);
	int getInitialVelocity() { return initialVelocity; }
	int getCurrentVelocity() { return currentVelocity; }
	virtual void update(float frameTime);
	void movementWithDirection(float frameTime, int direction);
};

class PatrolMovement : public MovementComponent
{
private:
	bool onFloor;
	bool onFill;

public:
	PatrolMovement(Entity* ent);
	void setOrigin(VECTOR2 pos) { origin = pos; }

	bool returnOrigin();
	void update(float frameTime);
	void setFloor(bool value) { onFloor = value; }
	void setFill(bool value) { onFill = value; }
};

class ProjectileMovement : public MovementComponent
{
private:
	VECTOR2 velocity;
	int t;
	float timeInterval;
	Entity *player;

public:
	ProjectileMovement(Entity* ent, Entity *play);
	void update(float frameTime);
};

#endif
