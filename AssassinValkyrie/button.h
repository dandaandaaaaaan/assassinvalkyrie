// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Png Yeow Li
// Student Number	: S10164245H

#ifndef _BUTTON_H
#define _BUTTON_H
#define WIN32_LEAN_AND_MEAN

#include "Image.h"
#include "constants.h"
#include "game.h"
#include "input.h"
#include "entity.h"
#include "cursor.h"

namespace buttonNS
{
	const int BUTTON_WIDTH = 248;
	const int BUTTON_HEIGHT = 70;
	const int START_BUTTON_FRAME = 0;
	const int START_HOVER_BUTTON_FRAME = 1;
	const int SETTINGS_BUTTON_FRAME = 2;
	const int SETTINGS_HOVER_BUTTON_FRAME = 3;
	const int EXIT_BUTTON_FRAME = 4;
	const int EXIT_HOVER_BUTTON_FRAME = 5;
	const int CREDITS_BUTTON_FRAME = 6;
	const int CREDITS_HOVER_BUTTON_FRAME = 7;
	const int RESUME_BUTTON_FRAME = 8;
	const int RESUME_HOVER_BUTTON_FRAME = 9;
	const int BUTTON_NCOLS = 2;

	const int SKILL_WIDTH = 50;
	const int SKILL_HEIGHT = 51;
	const int STEALTH_FRAME = 0;
	const int SPEED_FRAME = 1;
	const int RANGE_FRAME = 2;
	const int ARMOUR_FRAME = 3;
	const int STEALTH_GLOW = 4;
	const int SPEED_GLOW = 5;
	const int RANGE_GLOW = 6;
	const int ARMOUR_GLOW = 7;

}

namespace settingsNS
{
	const int WIDTH = 248;
	const int HEIGHT = 70;
	const int NCOLS = 2;

	const int RIGHT_FRAME = 10;
	const int RIGHT_HOVER = 11;
	const int LEFT_FRAME = 12;
	const int LEFT_HOVER = 13;
	const int UP_FRAME = 14;
	const int UP_HOVER = 15;
	const int DOWN_FRAME = 16;
	const int DOWN_HOVER = 17;
	const int MELEE_FRAME = 18;
	const int MELEE_HOVER = 19;
	const int RANGE_FRAME = 20;
	const int RANGE_HOVER = 21;
	const int DISTRACT_FRAME = 22;
	const int DISTRACT_HOVER = 23;
	const int ASSASSINATE_FRAME = 24;
	const int ASSASSINATE_HOVER = 25;
	const int BACK_FRAME = 26;
	const int BACK_HOVER = 27;
	const int DEFAULT_FRAME = 28;
	const int DEFAULT_HOVER = 29;
}

class Button : public Entity
{
private:
	bool mouseOn;
public:
	Button();
	virtual ~Button();

	bool initialize(Graphics *g, int width, int height, int ncols, TextureManager *textureM, Cursor *cursor);
	void update(int frame);
	void updateFrame();
	void draw();
	bool click(Entity &ent);

	bool collideButton(Entity &ent);

	void collisions(int startFrame, int endFrame);
	void collisions(Entity &ent, int startFrame, int endFrame, Audio *a);
	bool collideWithin();
	void releaseAll();
	void resetAll();

	Cursor mouse;
};

#endif
