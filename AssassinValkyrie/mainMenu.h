// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Png Yeow Li
// Student Number	: S10164245H

#ifndef _MAINMENU_H
#define _MAINMENU_H
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "image.h"
#include "textureManager.h"
#include "assassinValkyrie.h"
#include "button.h"
#include "cursor.h"
#include "dashboard.h"
#include "rayCasting.h"
#include "keyBinding.h"

class MainMenu : public Game
{
private:
	AssassinValkyrie* assValk;	// main game to play
	bool gameStart;				// true to activate game
	bool settings;				// check if in settings screen
	bool enterKey;
	bool isEnterKey;
	bool leaderboard;
	bool credits;

	// Textures & pictures
	TextureManager backgroundTexture;
	TextureManager mmBackgroundTexture;
	TextureManager buttonsTexture;
	TextureManager mouseTextures;
	TextureManager pauseTexture;
	TextureManager creditsTexture;

	// Main Menu items
	Image background;
	Image mmBackground;
	Image creditsImage;
	Button startButton;
	Button exitButton;
	Button creditsButton;
	Button settingsButton;
	Button leaderboardButton;
	Button mainMenuButton;
	Button pauseButton;
	Cursor *cursor;
	TextDX *leaderboardText;
	TextDX *gameOverText;

	// Settings items
	KeyBinding *key;
	Button rightButton;
	Button leftButton;
	Button upButton;
	Button downButton;
	Button meleeButton;
	Button rangeButton;
	Button distractButton;
	Button assassinateButton;
	Button backButton;
	Button defaultButton;
	char   insertKey;

	// Setting Text
	TextDX *rightKey;
	TextDX *leftKey;
	TextDX *upKey;
	TextDX *downKey;
	TextDX *meleeKey;
	TextDX *rangeKey;
	TextDX *distractKey;
	TextDX *assassinateKey;

	// Leaderboard Items
		
	// Pause Items
	Button pExitButton;
	Button resumeButton;
	TextDX *pausedText;


public:
	MainMenu();
	virtual ~MainMenu();

	void initialize(HWND hwnd);
	void update();
	void ai();
	void collisions();
	void render();
	void releaseAll();
	void resetAll();
};


#endif
