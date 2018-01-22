// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Chua Wei Jie Timothy
// Student Number	: S10165581F

#ifndef _ATTACK_COMPONENT_H
#define _ATTACK_COMPONENT_H
#define WIN32_LEAN_AND_MEAN

class AttackComponent
{
private:
	int hitPoint;
public:
	void update();
};

class ShootComponent : AttackComponent
{

};
class MeleeComponent : AttackComponent
{

};

#endif
