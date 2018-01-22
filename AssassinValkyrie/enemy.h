// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Chua Wei Jie Timothy
// Student Number	: S10165581F

#ifndef _ENEMY_SHIP_H 
#define _ENEMY_SHIP_H
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include "HealthComponet.h"
#include "MovementComponent.h"

namespace trooperNS
{
	const int	HEALTH = 20;
	const int	WIDTH = 91;
	const int	HEIGHT = 141;
	const double ROTATION = 0;
	const float SCALE = 1.0f;
	const int	X = GAME_WIDTH / 2 - WIDTH*SCALE;
	const int	Y = GAME_HEIGHT / 2 - HEIGHT*SCALE;
	const float SPEED = 100;
	const float MASS = 300.0f;
	const int   TEXTURE_COLS = 6;
	const int   START_FRAME = 0;
	const int   END_FRAME = 5;
	const float ANIMATION_DELAY = 1.0f;
}

class Enemy : public Entity
{
protected:
	HealthComponent	*health;
	MovementComponent *move;
	bool	dyingOn;
	Image	dying;
	Image	damaged;

public:
	// constructor
	Enemy();

	// inherited member functions
	bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
	void update(float frameTime);
	void ai(Entity &ship1, Entity &ship2);
	void draw();
};
#endif