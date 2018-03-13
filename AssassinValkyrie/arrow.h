// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Zhuang yuteng
// Student Number	: S10163964C

#ifndef _ARROW_H                 // Prevent multiple definitions if this 
#define _ARROW_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include "Player.h";

namespace arrowNS
{
	const float WIDTH = 79;                   // image width
	const float HEIGHT = 95;                  // image height
	const float SCALE = 0.15f;
	const float SPEED = 300;                // 200 pixels per second
	const int   ARROW_TEXTURE_COLS = 2;           // texture has 8 columns
	const float   ARROW_START_FRAME = 12;      // ship1 starts at frame 0
	const float   ARROW_END_FRAME = 12;        // ship1 end at frame 0
	const float ARROW_ANIMATION_DELAY = 0.2f;    // time between frames

}

// inherits from Entity class
class Arrow : public Entity
{
private:
	int startX;
public:
	// constructor
	Arrow();

	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime, Player p);
	void damage(WEAPON);

	int getStartX() { return startX; }
	void setStartX(int x) { startX = x; }
};
#endif

