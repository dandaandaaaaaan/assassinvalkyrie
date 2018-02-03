// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Daniel Lee Min Qiang
// Student Number	: S10162739H

#ifndef _BACKGROUND_H 
#define _BACKGROUND_H
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include"stageGenerator.h"
#include "enemyManager.h"
#include "enemyBulletManager.h"
#include "Player.h"

namespace backgroundNS
{
	const int	WIDTH = 3840;
	const int	HEIGHT = 1984;
	const double ROTATION = 0;
	const float SCALE = 1.0f;
	const int	X = GAME_WIDTH / 2 - WIDTH*SCALE;
	const int	Y = GAME_HEIGHT - HEIGHT;
	const float SPEED = 100;
	const float MASS = 300.0f;
	const int   TEXTURE_COLS = 1;
	const int   START_FRAME = 0;
	const int   END_FRAME = 0;

}

class Background : public Entity
{
private:
	int i;
	bool centre;
	int centreX;
	int centreY;
	bool moveOn;
public:
	// constructor
	Background();

	// inherited member functions
	bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
	void update(float frameTime, Player *player, StageGenerator *stageGen, EnemyManager *emList, EnemyBulletManager *emBulletList, KeyBinding *key);
	void draw();
	void collisions(Player *player, StageGenerator *stageGen);
};
#endif