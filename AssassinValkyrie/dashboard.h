#ifndef _DASHBOARD_H
#define _DASHBOARD_H
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include "textDX.h"
#include "constants.h"
#include "graphics.h"
#include "button.h"
#include "Player.h"
#include "playerBar.h"

namespace dashboardNS
{
	const COLOR_ARGB fontColor = D3DCOLOR_ARGB(255, 141, 214, 233);
	const int PAUSE_WIDTH = 100;
	const int PAUSE_HEIGHT = 50;
	const int PAUSE_NCOLS = 0;
	const int PAUSE_FRAME = 0;
	const int PAUSE_HOVER_FRAME = 1;
	const int SKILL_TEXT_HEIGHT = 30;
}

class Dashboard
{
private:
	TextureManager skillTexture;
	TextureManager dashboardTexture;
	TextureManager barTexture;
	Button stealthIcon;
	Button speedIcon;
	Button rangeIcon;
	Button armorIcon;
	Cursor *mouse;
	Image dashboard;
	PlayerBar playerHealth;
	PlayerBar underHealth;
	PlayerBar playerExp;
	PlayerBar underExp;
	TextDX *healthRemaining;
	TextDX *XP;
	TextDX *stealthLevel;
	TextDX *speedLevel;
	TextDX *rangeLevel;
	TextDX *armorLevel;

	int playerMaxHealth;
	int playerCurrentHealth;
	int playerMaxXP;
	int playerCurrentXP;
	int stealthPoints;
	int speedPoints;
	int rangePoints;
	int armorPoints;


public:
	Dashboard();
	virtual ~Dashboard();
	bool initialize(Graphics *g, Cursor *cursor, Player *playerM);
	void draw();
	void update(float frameTime, Player *playerM, Input *input);
	void collisions();
	void releaseAll();
	void resetAll();

	int mins;
	int secs;
};

#endif