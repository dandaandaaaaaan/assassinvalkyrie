// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Chua Wei Jie Timothy
// Student Number	: S10165581F

#include "MainMenu.h"

MainMenu::MainMenu()
{
	assValk = new AssassinValkyrie();
	gameStart = false;
}

MainMenu::~MainMenu()
{
	ShowCursor(FALSE);
	releaseAll();
}

void MainMenu::initialize(HWND hwnd)
{
	Game::initialize(hwnd);

	if (!mmBackgroundTexture.initialize(graphics, MMBACKGROUND_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Main Menu Background"));

	if (!mmBackground.initialize(graphics, 1280, 720, 1, &mmBackgroundTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Main Menu Background"));

	return;
}

void MainMenu::update()
{
	if (input->isKeyDown(ENTER_KEY))
	{
		gameStart = true;
		assValk->initialize(*this, &hwnd, &hr, &timeStart, &timeEnd, &timerFreq, &frameTime);
	}
	if (gameStart)
		assValk->update();
}

void MainMenu::ai()
{
	if (gameStart)
		assValk->ai();
}

void MainMenu::collisions()
{
	if (gameStart)
		assValk->collisions();
}

void MainMenu::render()
{
	graphics->spriteBegin();

	if (gameStart)
		assValk->render();
	else
		mmBackground.draw();

	graphics->spriteEnd();
}

void MainMenu::releaseAll()
{
	if (gameStart)
		assValk->releaseAll();
	else
		mmBackgroundTexture.onLostDevice();
}

void MainMenu::resetAll()
{
	if (gameStart)
		assValk->resetAll();
	else
		mmBackgroundTexture.onResetDevice();
}