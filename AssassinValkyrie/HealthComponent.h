// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Chua Wei Jie Timothy
// Student Number	: S10165581F

#ifndef _HEALTH_COMPONENT_H
#define _HEALTH_COMPONENT_H
#define WIN32_LEAN_AND_MEAN

#include "healthBar.h"

class HealthComponent
{
private:
	int curr_health;
	bool isAlive;
	Bar healthbar;
	bool animationOn = false;
	COLOR_ARGB damageColor = NULL;
	int damageTimer;
	Image *animation;
	int isAnimating;
	bool dieSound;

public:
	HealthComponent(Image *image);
	bool initialize(Graphics *graphics, TextureManager *textureM, int max);
	void update(float frameTime, VECTOR2 pos, Audio *a);
	void draw(Entity *ent);
	void damage(int hitPoint);

	bool getAlive() { return isAlive; }
	bool getDieAnimation() { return animationOn; }
	COLOR_ARGB getDamageAnimation() { return damageColor; }
	int getAnimationStatus() { return isAnimating; }
};

#endif
