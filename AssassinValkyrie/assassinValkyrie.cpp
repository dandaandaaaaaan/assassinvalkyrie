// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Chua Wei Jie Timothy
// Student Number	: S10165581F

#include "assassinValkyrie.h"
#include "levelLoader.h"

// Constructor
AssassinValkyrie::AssassinValkyrie()
{
	ShowCursor(false);
	player = new Player();
	//mouse = new Cursor();
	dashboard = new Dashboard();
	background = new Background();
	stageGenerator = new StageGenerator();
	currentStage = 1;
	displayTimer = new TextDX();
	mins = 0;
	secs = 0;
	milliSec = 0;
	text = new TextDX();
}

// Destructor
AssassinValkyrie::~AssassinValkyrie()
{
    releaseAll();
}

// Initializes the game
void AssassinValkyrie::initialize(Game &gamePtr, HWND *hwndM, HRESULT *hrM, LARGE_INTEGER *timeStartM, LARGE_INTEGER *timeEndM,
	LARGE_INTEGER *timerFreqM, float *frameTimeM, bool *pausedM, Cursor *cursor)
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
	paused = *pausedM;
	mouse = cursor;

	mouse = new Cursor();

	// Mouse
	if (!mouseTextures.initialize(graphics, MOUSE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Enemy Textures"));

	if (!mouse->initialize(this, cursorNS::WIDTH, cursorNS::HEIGHT, cursorNS::TEXTURE_COLS, &mouseTextures))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy trooper"));

	/////////////////////////////////////////
	//				BG
	/////////////////////////////////////////
	//Background
	if (!backgroundTexture.initialize(graphics, BACKGROUND_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));

	if (!background->initialize(this, backgroundNS::WIDTH, backgroundNS::HEIGHT, backgroundNS::TEXTURE_COLS, &backgroundTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background"));

	if (!floorTexture.initialize(graphics, FLOOR_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initalizing floor texture"));

	if (!ladderTexture.initialize(graphics, LADDER_IMAGE))
		throw (GameError(gameErrorNS::FATAL_ERROR, "Error initializing ladder texture"));

	if (!stageGenerator->initialize(this, &floorTexture, &currentStage, &ladderTexture, &emList))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing stage generation"));
	/*
	if (!tempChar->initialize(this, hideoutNS::WIDTH, hideoutNS::HEIGHT, 5, &floorTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing temp player placeholder"));


	tempChar->setCurrentFrame(4);
	tempChar->setY(576);
	*/

	/////////////////////////////////////////
	//				Enemy
	/////////////////////////////////////////
	// Trooper
	if (!trooperTexture.initialize(graphics, ENEMY_TROOPER_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Enemy Textures"));

	// Player
	if (!playerTextures.initialize(graphics, PLAYER_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player Textures"));

	if (!player->initialize(this, playerNS::WIDTH, playerNS::HEIGHT, playerNS::TEXTURE_COLS, &playerTextures))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player"));
	// Gunner
	if (!gunnerTexture.initialize(graphics, ENEMY_GUNNER_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Enemy Textures"));

	// Serpant
	if (!serpantTexture.initialize(graphics, ENEMY_SERPANT_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Enemy Textures"));

	// Bullet
	if (!bulletTextures.initialize(graphics, BULLET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet texture"));

	// Health
	if (!healthTexture.initialize(graphics, HEALTH_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing health texture"));

	// Collection of enemies
	if (!emList.initialize(this, &trooperTexture, &gunnerTexture, &serpantTexture, &healthTexture, mouse))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemies texture"));

	emBulletList.initialize(&emList);

	//UI
	dashboard->initialize(graphics, mouse);

	if (!displayTimer->initialize(graphics, 30, false, false, "Spectre 007"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Dashboard Text"));

	if (!text->initialize(graphics, 30, false, false, "Spectre 007"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing text"));
	return;
}

// Update all game items
void AssassinValkyrie::update()
{
	milliSec++;
	if (milliSec >= FRAME_RATE)
	{
		secs++;
		milliSec = 0;
		if (secs >= 60)
		{
			mins++;
			secs = 0;
		}
	}
	pCollection = stageGenerator->getFillPlatforms();
	//stageGenerator->update(frameTime);
	background->update(frameTime, player, stageGenerator, &emList);
	player->update(frameTime, this, &playerTextures, stageGenerator);
	mouse->update();
	emBulletList.update(frameTime, this, &bulletTextures, player);
	weaponManager.update(frameTime, input, this, arrowNS::WIDTH, arrowNS::HEIGHT, arrowNS::ARROW_TEXTURE_COLS,stoneNS::STONE_TEXTURE_COLS, &playerTextures, player->getX() + 20, player->getY(),*player);
	emList.update(frameTime, pCollection);
}

// Artificial Intelligence
void AssassinValkyrie::ai()
{
	emList.ai();
}

// Handle collisions
void AssassinValkyrie::collisions()
{
    VECTOR2 collisionVector;
	weaponManager.collisions(&emList, player, stageGenerator->getFloorPlatforms());
	player->collisions(&emList, stageGenerator);
	//background->collisions(player, stageGenerator);
	emList.collisions(mouse, stageGenerator->getFloorPlatforms(), pCollection);
	emBulletList.collisions(mouse);
}

// Render game items
void AssassinValkyrie::render()
{
	
	background->draw();
	stageGenerator->render();
	mouse->draw();
    player->draw();
    weaponManager.render();
	player->draw();

	emList.render();
	emBulletList.render();

	graphics->spriteEnd();
	graphics->initRectangle();
	emList.renderRay(graphics);
	graphics->spriteBegin();

	dashboard->draw();

	const int bufferSize = 20;
	static char buffer[bufferSize];

	// Timer text
	_snprintf(buffer, bufferSize, "Time \n %d : %02d", (int)mins, (int)secs);
	displayTimer->setFontColor(graphicsNS::WHITE);
	displayTimer->print(buffer, (GAME_WIDTH / 2) - 30, 0);

	mouse->draw();
}

// Release all reserved video memory so graphics device may be reset.
void AssassinValkyrie::releaseAll()
{
	SAFE_DELETE(mouse);
	SAFE_DELETE(dashboard);
	SAFE_DELETE(text);
	SAFE_DELETE(displayTimer);
	SAFE_DELETE(background);
	emBulletList.~EnemyBulletManager();
	emList.~EnemyManager();
	mouseTextures.onLostDevice();
	trooperTexture.onLostDevice();
	gunnerTexture.onLostDevice();
	serpantTexture.onLostDevice();
	healthTexture.onLostDevice();
	bulletTextures.onLostDevice();
	playerTextures.onLostDevice();
	backgroundTexture.onLostDevice();
	floorTexture.onLostDevice();
    Game::releaseAll();
    return;
}

// Recreate all surfaces.
void AssassinValkyrie::resetAll()
{
	playerTextures.onResetDevice();
	mouseTextures.onResetDevice();
	trooperTexture.onResetDevice();
	gunnerTexture.onResetDevice();
	serpantTexture.onResetDevice();
	healthTexture.onResetDevice();
	bulletTextures.onResetDevice();
	backgroundTexture.onResetDevice();
	floorTexture.onResetDevice();
    Game::resetAll();
    return;
}
