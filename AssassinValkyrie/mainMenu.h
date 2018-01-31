// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Chua Wei Jie Timothy
// Student Number	: S10165581F

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

class MainMenu : public Game
{
private:
	AssassinValkyrie* assValk;	// main game to play
	bool gameStart;				// true to activate game

	// Textures & pictures
	TextureManager mmBackgroundTexture;
	TextureManager buttonsTexture;
	TextureManager mouseTextures;
	TextureManager pauseTexture;

	Image mmBackground;
	Button startButton;
	Button exitButton;
	Button creditsButton;
	Button settingsButton;
	Button pauseButton;
	Cursor *cursor;

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