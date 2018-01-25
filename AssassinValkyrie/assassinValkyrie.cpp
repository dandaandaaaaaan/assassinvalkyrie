// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Chua Wei Jit Timothy
// Student Number	: S10165581F

#include "assassinValkyrie.h"

// Constructor
AssassinValkyrie::AssassinValkyrie()
{ 
	ShowCursor(false);
	trooper1 = new Enemy();
	mouse = new Cursor();
	background = new Background();
	stageGenerator = new StageGenerator();
	tempChar = new Hideout();
	currentStage = 1;
}

// Destructor
AssassinValkyrie::~AssassinValkyrie()
{
    releaseAll();
}

// Initializes the game
void AssassinValkyrie::initialize(Game &gamePtr, HWND *hwndM, HRESULT *hrM, LARGE_INTEGER *timeStartM, LARGE_INTEGER *timeEndM,
	LARGE_INTEGER *timerFreqM, float *frameTimeM)
{
	graphics = gamePtr.getGraphics();
	input = gamePtr.getInput();
	audio = gamePtr.getAudio();
	hwnd = *hwndM;
	hr = *hrM;
	timeStart = *timeStartM;
	timeEnd = *timeEndM;
	timerFreq = *timerFreqM;
	frameTime = *frameTimeM;

	// Mouse
	if (!mouseTextures.initialize(graphics, MOUSE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Enemy Textures"));

	if (!mouse->initialize(this, cursorNS::WIDTH, cursorNS::HEIGHT, cursorNS::TEXTURE_COLS, &mouseTextures))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy trooper"));
	
	// Enemy
	if (!enemyTextures.initialize(graphics, ENEMY_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Enemy Textures"));
	
	if (!trooper1->initialize(this, trooperNS::WIDTH, trooperNS::HEIGHT, trooperNS::TEXTURE_COLS, &enemyTextures))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy trooper"));

	//Background
	if (!backgroundTexture.initialize(graphics, BACKGROUND_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));

	if (!background->initialize(this, backgroundNS::WIDTH, backgroundNS::HEIGHT, backgroundNS::TEXTURE_COLS, &backgroundTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background"));

	if (!floorTexture.initialize(graphics, FLOOR_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initalizing floor texture"));

	if (!stageGenerator->initialize(this, &floorTexture, &currentStage))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing floor generation"));

	if (!tempChar->initialize(this, hideoutNS::WIDTH, hideoutNS::HEIGHT, 5, &floorTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing temp player placeholder"));
	tempChar->setCurrentFrame(4);
	tempChar->setY(576);
	return;
}

// Update all game items
void AssassinValkyrie::update()
{
	//background->update(frameTime, tempChar, stageGenerator);
	trooper1->update(frameTime);
	//stageGenerator->update(frameTime);
	background->update(frameTime, tempChar, stageGenerator);
	tempChar->update(frameTime);
	mouse->update();
}


// Artificial Intelligence
void AssassinValkyrie::ai()
{

}

// Handle collisions
void AssassinValkyrie::collisions()
{
    VECTOR2 collisionVector;
	mouse->collidesWith(*trooper1, collisionVector);
}

// Render game items
void AssassinValkyrie::render()
{
	background->draw();
	trooper1->draw();
	stageGenerator->render();
	tempChar->draw();
	mouse->draw();
}

// Release all reserved video memory so graphics device may be reset.
void AssassinValkyrie::releaseAll()
{
	SAFE_DELETE(mouse);
	SAFE_DELETE(trooper1);
	SAFE_DELETE(background);
	//SAFE_DELETE(stageGenerator);
	enemyTextures.onLostDevice();
	mouseTextures.onLostDevice();
	backgroundTexture.onLostDevice();
	floorTexture.onLostDevice();
    Game::releaseAll();
    return;
}

// Recreate all surfaces.
void AssassinValkyrie::resetAll()
{
	enemyTextures.onResetDevice();
	mouseTextures.onResetDevice();
	backgroundTexture.onResetDevice();
	floorTexture.onResetDevice();
    Game::resetAll();
    return;
}