// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Chua Wei Jie Timothy
// Student Number	: S10165581F

#ifndef _HEALTH_COMPONENT_H
#define _HEALTH_COMPONENT_H
#define WIN32_LEAN_AND_MEAN

class HealthComponent
{
private:
	int max_health;
	int curr_health;
	bool isAlive;
public:
	void update(int hitPoint);
};

#endif
