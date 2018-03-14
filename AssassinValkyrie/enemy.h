// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Chua Wei Jie Timothy
// Student Number	: S10165581F

#ifndef _ENEMY_H 
#define _ENEMY_H
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include "HealthComponent.h"
#include "MovementComponent.h"
#include "AttackComponent.h"
#include "rayCasting.h"
#include "enemyState.h"
#include "patrolState.h"

namespace trooperNS
{
	const int	HEALTH = 50;
	const int	WIDTH = 65;
	const int	HEIGHT = 100;
	const double ROTATION = 0;
	const float SCALE = 1.0f;
	const float	X = GAME_WIDTH / 2 - WIDTH*SCALE;
	const float	Y = GAME_HEIGHT / 2 - HEIGHT*SCALE;
	const float SPEED = 60;
	const float MASS = 300.0f;
	const int   TEXTURE_COLS = 10;
	const int   START_FRAME = 0;
	const int   END_FRAME = 9;
	const float ANIMATION_DELAY = 0.3f;

	const double VISION_ANGLE = PI / 6;
	const int	VISION_RANGE = 200;
	const float	VISION_HEIGHT = HEIGHT*SCALE / 3.5f;

	const int MELEE_RANGE = 100;
	const int MELEE_WIDTH = 92;
	const int MELEE_HEIGHT = 100;
	const int MELEE_TEXTURE_COLS = 5;
	const int MELEE_START_FRAME = 5;
	const int MELEE_END_FRAME = 9;

	const int DIE_WIDTH = 65*2;
	const int DIE_HEIGHT = 100;
	const int DIE_TEXTURE_COLS = 5;
	const int DIE_START_FRAME = 15;
	const int DIE_END_FRAME = 24;
	const float DIE_ANIMATION_DELAY = 0.15f;
}

namespace gunnerNS
{
	const int	HEALTH = 50;
	const int	WIDTH = 96;
	const int	HEIGHT = 96;
	const double ROTATION = 0;
	const float SCALE = 1.0f;
	const float	X = GAME_WIDTH / 2 - WIDTH*SCALE + 100;
	const float	Y = GAME_HEIGHT / 2 - HEIGHT*SCALE;
	const float SPEED = 40;
	const float MASS = 300.0f;
	const int   TEXTURE_COLS = 4;
	const int   START_FRAME = 8;
	const int   END_FRAME = 11;
	const float ANIMATION_DELAY = 0.25f;

	const double VISION_ANGLE = PI / 7;
	const int	VISION_RANGE = 200;
	const float	VISION_HEIGHT = HEIGHT*SCALE / 3.5f;

	const int SHOOT_RANGE = 200;
	const int SHOOT_WIDTH = 96;
	const int SHOOT_HEIGHT = 95;
	const int SHOOT_TEXTURE_COLS = 4;
	const int SHOOT_START_FRAME = 21;
	const int SHOOT_END_FRAME = 26;

	const int DIE_WIDTH = 96;
	const int DIE_HEIGHT = 96;
	const int DIE_TEXTURE_COLS = 4;
	const int DIE_START_FRAME = 32;
	const int DIE_END_FRAME = 39;
	const float DIE_ANIMATION_DELAY = 0.1f;
}

namespace serpantNS
{
	const int	HEALTH = 100;
	const int	WIDTH = 90;
	const int	HEIGHT = 99;
	const double ROTATION = 0;
	const float SCALE = 1.0f;
	const float	X = GAME_WIDTH / 2 - WIDTH*SCALE + 100;
	const float	Y = GAME_HEIGHT / 2 - HEIGHT*SCALE;
	const float SPEED = 40;
	const float MASS = 300.0f;
	const int   TEXTURE_COLS = 5;
	const int   START_FRAME = 0;
	const int   END_FRAME = 4;
	const float ANIMATION_DELAY = 0.25f;

	const double VISION_ANGLE = PI / 5;
	const int	VISION_RANGE = 200;
	const float	VISION_HEIGHT = HEIGHT*SCALE / 3.5f;

	const int FIRE_RANGE = 400;
	const int FIRE_WIDTH = 90;
	const int FIRE_HEIGHT = 99;
	const int FIRE_TEXTURE_COLS = 10;
	const int FIRE_START_FRAME = 31;
	const int FIRE_END_FRAME = 39;

	const int DIE_WIDTH = 90;
	const int DIE_HEIGHT = 99;
	const int DIE_TEXTURE_COLS = 9;
	const int DIE_START_FRAME = 9;
	const int DIE_END_FRAME = 17;
	const float DIE_ANIMATION_DELAY = 0.15f;
}

namespace healthBarNS
{
	const int   WIDTH = 65;
	const int   HEIGHT = 10;
	const float	SCALE = 1.0f;
	const int   TEXTURE_COLS = 1;
	const int   BAR_FRAME = 0;
}

namespace cautionNS
{
	const int   WIDTH = 15;
	const int   HEIGHT = 50;
	const float	SCALE = 1.0f;
	const int   TEXTURE_COLS = 1;
	const int   FRAME = 1;
}

class Enemy : public Entity
{
protected:
	HealthComponent		*health;
	PatrolMovement		*move;
	AttackComponent		*attack;
	EnemyState			*state_;
	// player to track
	Entity	*player;
	Ray		*vision;
	Image	attackAnimation;
	Image	dieAnimation;
	Image	cautionAnimation;
	int		range;
	int		attackFrame;

public:
	// constructor
	Enemy(Entity *play);
	~Enemy();
	bool	triggerAlert;

	// inherited member functions
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM, TextureManager *textureHealth);
	virtual void handleInput(EnemyState* newState, Input *i, PLATFORM *p = NULL);
	void update(float frameTime, PLATFORM p, Audio *a);
	virtual void ai(PLATFORM p, Input *i, float viewM);
	void draw();
	void drawRay(Graphics *g);

	void setOriginalPos(VECTOR2 pos)
	{
		spriteData.x = pos.x; spriteData.y = pos.y;
		move->setOrigin(pos);
	}
	Ray *getRay() { return vision; }
	AttackComponent *getAttack() { return attack; }
	PatrolMovement *getMove() { return move; }
	HealthComponent *getHealth() { return health; }

	int getRange() { return range; }
	Image *getAnimation() { return &attackAnimation; }
	int getAttackFrame() { return attackFrame; }
	bool isAlive() { return health->getAlive(); }
	int isDeathAnimation() { return health->getAnimationStatus(); }
	EnemyState *getState() {return state_; }
	void drawCaution(bool value);
};

#endif