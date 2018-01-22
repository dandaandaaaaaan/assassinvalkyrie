// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Chua Wei Jie Timothy
// Student Number	: S10165581F

#ifndef _MOVE_COMPONENT_H
#define _MOVE_COMPONENT_H
#define WIN32_LEAN_AND_MEAN

class MovementComponent
{
private:
	int velocityX;
	int velocityY;
	float *posX;
	float *posY;

public:
	//MovementComponent(float *x, float *y, int speedX, int speedY);
	//void update(float frameTime);
};

//MovementComponent::MovementComponent(float *x, float *y, int speedX, int speedY)
//{
//	velocityX = speedX;
//	velocityY = speedY;
//	posX = x;
//	posY = y;
//}

//void MovementComponent::update(float frameTime)
//{
//	*posX = *posX + velocityX * frameTime;
//	*posY = *posY + velocityY * frameTime;
//}

#endif
