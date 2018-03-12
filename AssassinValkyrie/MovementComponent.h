// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Chua Wei Jie Timothy
// Student Number	: S10165581F

#ifndef _MOVE_COMPONENT_H
#define _MOVE_COMPONENT_H
#define WIN32_LEAN_AND_MEAN

#include "entity.h"

namespace MovementComponentNS {
	const int cameraVelocity = 125; //PLEASE MAKE THIS VARIBLE CHANGE CONSTANTLY TO THE DIFF PLAYER WALKING, JUMPING, UPSKILL RUN PERK
}

class MovementComponent
{
protected:
	Entity *object;
	VECTOR2 origin;
	int initialVelocity = 0;
	int currentVelocity;
	bool enable;
	VECTOR2 cameraVelocity;

public:
	MovementComponent(Entity* ent);

	void setVelocity(int speed);
	int getInitialVelocity() { return initialVelocity; }
	int getCurrentVelocity() { return currentVelocity; }
	virtual void update(float frameTime);
	void movementWithDirection(float frameTime, int direction);
	void setEnable(bool value) { enable = value; }
	void setCameraVelocity(VECTOR2 velocity);
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
	double t;
	double timeInterval;
	double angle;
	double distance;
	float  f;
	bool initialized;
	double speed;

public:
	ProjectileMovement(Entity *ent, float dist);
	void update(float frameTime);
};

#endif
