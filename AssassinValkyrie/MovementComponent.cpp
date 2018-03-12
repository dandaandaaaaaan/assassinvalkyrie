// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Chua Wei Jie Timothy
// Student Number	: S10165581F
#include "MovementComponent.h"
#include "fireBall.h"

MovementComponent::MovementComponent(Entity* ent)
{
	object = ent;
	enable = true;
	cameraVelocity = VECTOR2(MovementComponentNS::cameraVelocity, MovementComponentNS::cameraVelocity);
};
void MovementComponent::setVelocity(int speed) {
	if (initialVelocity == 0)
		initialVelocity = speed;
	currentVelocity = speed;
};

void MovementComponent::update(float frameTime)
{
	if (enable)
		object->setX(object->getX() + currentVelocity *frameTime);
};
void MovementComponent::movementWithDirection(float frameTime, int direction)
{
	if (direction == 1)
	{
		object->setX(object->getX() + cameraVelocity.x *frameTime);
	}
	else if (direction == 2)
	{
		object->setX(object->getX() + (-cameraVelocity.x) * frameTime);
	}
	else if (direction == 3)
	{
		object->setY(object->getY() + cameraVelocity.y * frameTime);
	}
	else if (direction == 4)
	{
		object->setY(object->getY() + (-cameraVelocity.y) * frameTime);
	}
}

void MovementComponent::setCameraVelocity(VECTOR2 velocity) {
	cameraVelocity = velocity;
}

PatrolMovement::PatrolMovement(Entity* ent) : MovementComponent(ent) {}
bool PatrolMovement::returnOrigin()
{
	if (object->getCenter()->x > origin.x + 1)
		currentVelocity = -initialVelocity;
	else if (object->getCenter()->x < origin.x - 1)
		currentVelocity = initialVelocity;
	else
		return true;
	return false;
}
void PatrolMovement::update(float frameTime)
{
	MovementComponent::update(frameTime);
	if (!onFloor)
		object->setY(object->getY() + GRAVITY / 2);
}

ProjectileMovement::ProjectileMovement(Entity *ent, float dist) : MovementComponent(ent)
{
	distance = dist;
	speed = 2*fireNS::SPEED;
	if (distance < 0) distance = -distance;

	angle = (asin((distance * GRAVITY * 6) / pow(speed, 2)) / 2);
	timeInterval = distance / (speed * cos(angle));
	initialized = false;
	t = 0;
	f = 0;
}
void ProjectileMovement::update(float frameTime)
{
	if (!initialized)
	{
		if (currentVelocity < 0)
			speed = -speed;
		
		velocity = { (float)(speed * cos(angle)), -(float)(speed * sin(angle)) };
		if (velocity.y > 0) velocity.y = -velocity.y;
		timeInterval = timeInterval / distance;
		initialized = true;
	}
	else
	{
		velocity.y += GRAVITY*6*f*frameTime;
		object->setX(object->getX() + velocity.x *frameTime);
		object->setY(object->getY() + velocity.y *frameTime);
		t++;
		f = timeInterval * t;
		double rotate = atan2(velocity.y, velocity.x);
		object->setRadians(rotate);
		if (currentVelocity < 0)
			object->setRadians(rotate + PI);
	}
}
