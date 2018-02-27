// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Png Yeow Li
// Student Number	: S10164245H

#include "MainMenu.h"

MainMenu::MainMenu()
{
	cursor = new Cursor();
	gameStart = false;
	settings = false;
	key = new KeyBinding();
	insertKey = ' ';
	rightKey = new TextDX();
	leftKey = new TextDX();
	upKey = new TextDX();
	downKey = new TextDX();
	meleeKey = new TextDX();
	rangeKey = new TextDX();
	distractKey = new TextDX();
	assassinateKey = new TextDX();
	pausedText = new TextDX();
}

MainMenu::~MainMenu()
{
	ShowCursor(false);
	releaseAll();
}

void MainMenu::initialize(HWND hwnd)
{
	Game::initialize(hwnd);
	// Mouse
	if (!mouseTextures.initialize(graphics, MOUSE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Enemy Textures"));

	if (!cursor->initialize(this, cursorNS::WIDTH, cursorNS::HEIGHT, cursorNS::TEXTURE_COLS, &mouseTextures))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy trooper"));

	if (!mmBackgroundTexture.initialize(graphics, MMBACKGROUND_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Main Menu Background"));

	if (!mmBackground.initialize(graphics, 1280, 720, 1, &mmBackgroundTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Main Menu Background"));

	// Buttons Texture
	if (!buttonsTexture.initialize(graphics, BUTTON_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Buttons Texture"));

	// Start Button
	if (!startButton.initialize(graphics, buttonNS::BUTTON_WIDTH, buttonNS::BUTTON_HEIGHT, buttonNS::BUTTON_NCOLS, &buttonsTexture, cursor))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Start button"));
	startButton.setCurrentFrame(buttonNS::START_BUTTON_FRAME);
	startButton.setX(GAME_WIDTH/4 - ((startButton.getWidth()/2)*startButton.getScale()));
	startButton.setY(GAME_HEIGHT / 4);

	// Settings Button
	if (!settingsButton.initialize(graphics, buttonNS::BUTTON_WIDTH, buttonNS::BUTTON_HEIGHT, buttonNS::BUTTON_NCOLS, &buttonsTexture, cursor))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Settings button"));
	settingsButton.setCurrentFrame(buttonNS::SETTINGS_BUTTON_FRAME);
	settingsButton.setX(startButton.getX());
	settingsButton.setY(startButton.getY() + startButton.getHeight() + (5*startButton.getScale()));

	// Credits Button
	if (!creditsButton.initialize(graphics, buttonNS::BUTTON_WIDTH, buttonNS::BUTTON_HEIGHT, buttonNS::BUTTON_NCOLS, &buttonsTexture, cursor))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Credits button"));
	creditsButton.setCurrentFrame(buttonNS::CREDITS_BUTTON_FRAME);
	creditsButton.setX(settingsButton.getX());
	creditsButton.setY(settingsButton.getY() + settingsButton.getHeight() + (5 * settingsButton.getScale()));

	// Exit Button
	if (!exitButton.initialize(graphics, buttonNS::BUTTON_WIDTH, buttonNS::BUTTON_HEIGHT, buttonNS::BUTTON_NCOLS, &buttonsTexture, cursor))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Exit button"));
	exitButton.setCurrentFrame(buttonNS::EXIT_BUTTON_FRAME);
	exitButton.setX(creditsButton.getX());
	exitButton.setY(creditsButton.getY() + creditsButton.getHeight() + (5 * creditsButton.getScale()));

	// Pause Button
	if (!pauseTexture.initialize(graphics, PAUSE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Pause"));

	if (!pauseButton.initialize(graphics, dashboardNS::PAUSE_WIDTH, dashboardNS::PAUSE_HEIGHT, dashboardNS::PAUSE_NCOLS, &pauseTexture, cursor))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing pause"));
	pauseButton.setCurrentFrame(dashboardNS::PAUSE_FRAME);
	pauseButton.setX(GAME_WIDTH - pauseButton.getWidth());
	pauseButton.setY(0);

	// Settings: Right Button
	if (!rightButton.initialize(graphics, settingsNS::WIDTH, settingsNS::HEIGHT, settingsNS::NCOLS, &buttonsTexture, cursor))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing settings button"));
	rightButton.setCurrentFrame(settingsNS::RIGHT_FRAME);
	rightButton.setX(GAME_WIDTH / 8);
	rightButton.setY(2 * GAME_HEIGHT / 10);

	// Settings: Left Button
	if (!leftButton.initialize(graphics, settingsNS::WIDTH, settingsNS::HEIGHT, settingsNS::NCOLS, &buttonsTexture, cursor))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing settings button"));
	leftButton.setCurrentFrame(settingsNS::LEFT_FRAME);
	leftButton.setX(GAME_WIDTH / 8);
	leftButton.setY(3 * GAME_HEIGHT / 10);

	// Settings: Up Button
	if (!upButton.initialize(graphics, settingsNS::WIDTH, settingsNS::HEIGHT, settingsNS::NCOLS, &buttonsTexture, cursor))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing settings button"));
	upButton.setCurrentFrame(settingsNS::UP_FRAME);
	upButton.setX(GAME_WIDTH / 8);
	upButton.setY(4 * GAME_HEIGHT / 10);

	// Settings: Down Button
	if (!downButton.initialize(graphics, settingsNS::WIDTH, settingsNS::HEIGHT, settingsNS::NCOLS, &buttonsTexture, cursor))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing settings button"));
	downButton.setCurrentFrame(settingsNS::DOWN_FRAME);
	downButton.setX(GAME_WIDTH / 8);
	downButton.setY(5 * GAME_HEIGHT / 10);

	// Settings: Melee Button
	if (!meleeButton.initialize(graphics, settingsNS::WIDTH, settingsNS::HEIGHT, settingsNS::NCOLS, &buttonsTexture, cursor))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing settings button"));
	meleeButton.setCurrentFrame(settingsNS::MELEE_FRAME);
	meleeButton.setX(5 * GAME_WIDTH / 8);
	meleeButton.setY(2 * GAME_HEIGHT / 10);

	// Settings: Range Button
	if (!rangeButton.initialize(graphics, settingsNS::WIDTH, settingsNS::HEIGHT, settingsNS::NCOLS, &buttonsTexture, cursor))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing settings button"));
	rangeButton.setCurrentFrame(settingsNS::RANGE_FRAME);
	rangeButton.setX(5 * GAME_WIDTH / 8);
	rangeButton.setY(3 * GAME_HEIGHT / 10);

	// Settings: Distract Button
	if (!distractButton.initialize(graphics, settingsNS::WIDTH, settingsNS::HEIGHT, settingsNS::NCOLS, &buttonsTexture, cursor))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing settings button"));
	distractButton.setCurrentFrame(settingsNS::DISTRACT_FRAME);
	distractButton.setX(5 * GAME_WIDTH / 8);
	distractButton.setY(4 * GAME_HEIGHT / 10);

	// Settings: Assassinate Button
	if (!assassinateButton.initialize(graphics, settingsNS::WIDTH, settingsNS::HEIGHT, settingsNS::NCOLS, &buttonsTexture, cursor))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing settings button"));
	assassinateButton.setCurrentFrame(settingsNS::ASSASSINATE_FRAME);
	assassinateButton.setX(5 * GAME_WIDTH / 8);
	assassinateButton.setY(5 * GAME_HEIGHT / 10);

	// Settings: Back Button
	if (!backButton.initialize(graphics, settingsNS::WIDTH, settingsNS::HEIGHT, settingsNS::NCOLS, &buttonsTexture, cursor))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing settings button"));
	backButton.setCurrentFrame(settingsNS::BACK_FRAME);
	backButton.setX(2 * GAME_WIDTH / 4);
	backButton.setY(8 * GAME_HEIGHT / 10);

	// Settings: Default Button
	if (!defaultButton.initialize(graphics, settingsNS::WIDTH, settingsNS::HEIGHT, settingsNS::NCOLS, &buttonsTexture, cursor))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing settings button"));
	defaultButton.setCurrentFrame(settingsNS::DEFAULT_FRAME);
	defaultButton.setX(GAME_WIDTH / 4);
	defaultButton.setY(8 * GAME_HEIGHT / 10);

	// Settings: Display Current Key
	if (!rightKey->initialize(graphics, 30, false, false, "Spectre 007"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing text"));

	if (!leftKey->initialize(graphics, 30, false, false, "Spectre 007"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing text"));

	if (!upKey->initialize(graphics, 30, false, false, "Spectre 007"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing text"));

	if (!downKey->initialize(graphics, 30, false, false, "Spectre 007"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing text"));

	if (!meleeKey->initialize(graphics, 30, false, false, "Spectre 007"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing text"));

	if (!rangeKey->initialize(graphics, 30, false, false, "Spectre 007"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing text"));

	if (!distractKey->initialize(graphics, 30, false, false, "Spectre 007"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing text"));

	if (!assassinateKey->initialize(graphics, 30, false, false, "Spectre 007"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing text"));

	// Pause: Resume Button
	if (!resumeButton.initialize(graphics, buttonNS::BUTTON_WIDTH, buttonNS::BUTTON_HEIGHT, buttonNS::BUTTON_NCOLS, &buttonsTexture, cursor))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Resume button"));
	resumeButton.setCurrentFrame(buttonNS::RESUME_BUTTON_FRAME);
	resumeButton.setX(GAME_WIDTH / 4);
	resumeButton.setY(5*GAME_HEIGHT / 10);
	
	// Pause: Exit Button
	if (!pExitButton.initialize(graphics, buttonNS::BUTTON_WIDTH, buttonNS::BUTTON_HEIGHT, buttonNS::BUTTON_NCOLS, &buttonsTexture, cursor))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Resume button"));
	pExitButton.setCurrentFrame(buttonNS::EXIT_BUTTON_FRAME);
	pExitButton.setX(GAME_WIDTH / 4);
	pExitButton.setY(6*GAME_HEIGHT / 10);

	if (!pausedText->initialize(graphics, 50, false, false, "Spectre 007"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing text"));


	audio->playCue(RUSH);
	return;
}

void MainMenu::update()
{
	cursor->update();

	if (!gameStart && !settings)
	{
		// Start Button
		if(startButton.collideButton(*cursor) && input->getMouseLButton())
		{
			audio->playCue(BUTTON_ENTER);
			gameStart = true;
			audio->stopCue(RUSH);
			assValk = new AssassinValkyrie();
			assValk->initialize(*this, &hwnd, &hr, &timeStart, &timeEnd, &timerFreq, &frameTime, &paused, cursor, key);
			audio->playCue(STEALTH);
		}
		if (settingsButton.collideButton(*cursor) && input->getMouseLButton())
		{
			settings = true;
			enterKey = false;
		}

		// Exit Button
		if (input->isKeyDown(ESC_KEY) || (exitButton.collideButton(*cursor) && input->getMouseLButton()))
		{
			Game::exitGame();
		}
	}

	if (!gameStart && settings && !enterKey)
	{
		if (rightButton.collideButton(*cursor) && input->getMouseLButton())
		{
			enterKey = true;
			if (input->anyKeyPressed())
			{
				insertKey = input->getCharIn();
				key->setRightKey(insertKey);
				enterKey = false;
			}
		}
		if (leftButton.collideButton(*cursor) && input->getMouseLButton())
		{
			enterKey = true;
			if (input->anyKeyPressed())
			{
				insertKey = input->getCharIn();
				key->setLeftKey(insertKey);
				enterKey = false;
			}
		}
		if (upButton.collideButton(*cursor) && input->getMouseLButton())
		{
			enterKey = true;
			if (input->anyKeyPressed())
			{
				insertKey = input->getCharIn();
				key->setUpKey(insertKey);
				enterKey = false;
			}
		}
		if (downButton.collideButton(*cursor) && input->getMouseLButton())
		{
			enterKey = true;
			if (input->anyKeyPressed())
			{
				insertKey = input->getCharIn();
				key->setDownKey(insertKey);
				enterKey = false;
			}
		}
		if (meleeButton.collideButton(*cursor) && input->getMouseLButton())
		{
			enterKey = true;
			if (input->anyKeyPressed())
			{
				insertKey = input->getCharIn();
				key->setMeleeKey(insertKey);
				enterKey = false;
			}
		}
		if (rangeButton.collideButton(*cursor) && input->getMouseLButton())
		{
			enterKey = true;
			if (input->anyKeyPressed())
			{
				insertKey = input->getCharIn();
				key->setRangeKey(insertKey);
				enterKey = false;
			}
		}
		if (distractButton.collideButton(*cursor) && input->getMouseLButton())
		{
			enterKey = true;
			if (input->anyKeyPressed())
			{
				insertKey = input->getCharIn();
				key->setDistractKey(insertKey);
				enterKey = false;
			}
		}
		if (assassinateButton.collideButton(*cursor) && input->getMouseLButton())
		{
			enterKey = true;
			if (input->anyKeyPressed())
			{
				insertKey = input->getCharIn();
				key->setAssassinateKey(insertKey);
				enterKey = false;
			}
		}
		if (backButton.collideButton(*cursor) && input->getMouseLButton())
		{
			settings = false;
		}
		if (defaultButton.collideButton(*cursor) && input->getMouseLButton())
		{
			key->defaultKey();
		}
	}

	if (!gameStart && settings && enterKey)
	{
		if (input->isKeyDown(ESC_KEY))
			enterKey = false;
	}

	if (gameStart && !assValk->getPause())
	{
		if (pauseButton.collideButton(*cursor) && input->getMouseLButton())
		{
			audio->stopCue(STEALTH);
			assValk->setPause(true);
		}
		assValk->update();
	}

	if (gameStart && assValk->getPause())
	{
		if (resumeButton.collideButton(*cursor) && input->getMouseLButton())
		{
			audio->playCue(STEALTH);
			assValk->setPause(false);
		}
			if (pExitButton.collideButton(*cursor) && input->getMouseLButton())
		{
			audio->playCue(RUSH);
			assValk->resetAll();
			gameStart = false;
		}

	}
}

void MainMenu::ai()
{
	if (gameStart)
		assValk->ai();
}

void MainMenu::collisions()
{
	VECTOR2 collisionVector;
	if (!gameStart && !settings)
	{
		//if (!startButton.collideButton(*cursor))
		//	startButton.collisions(buttonNS::START_BUTTON_FRAME, buttonNS::START_HOVER_BUTTON_FRAME);
		//if (startButton.collideButton(*cursor))
		//	startButton.setCurrentFrame(buttonNS::START_BUTTON_FRAME);
		//if (startButton.collidesWith(*cursor,collisionVector))
		//	startButton.collisions(buttonNS::START_BUTTON_FRAME, buttonNS::START_HOVER_BUTTON_FRAME);
		//if (!startButton.collideButton(*cursor))
		//	startButton.setCurrentFrame(buttonNS::START_BUTTON_FRAME);
		//if (settingsButton.collideButton(*cursor))
		//	settingsButton.collisions(buttonNS::SETTINGS_BUTTON_FRAME, buttonNS::SETTINGS_HOVER_BUTTON_FRAME);
		//if (!settingsButton.collideButton(*cursor))
		//	settingsButton.setCurrentFrame(buttonNS::SETTINGS_BUTTON_FRAME);
		//if (creditsButton.collideButton(*cursor))
		//	creditsButton.collisions(buttonNS::CREDITS_BUTTON_FRAME, buttonNS::CREDITS_HOVER_BUTTON_FRAME);
		//if (!creditsButton.collideButton(*cursor))
		//	creditsButton.setCurrentFrame(buttonNS::CREDITS_BUTTON_FRAME);
		//if (exitButton.collideButton(*cursor))
		//	exitButton.collisions(buttonNS::EXIT_BUTTON_FRAME, buttonNS::EXIT_HOVER_BUTTON_FRAME);
		//if (!exitButton.collidesWith(*cursor, collisionVector))
		//	exitButton.setCurrentFrame(buttonNS::EXIT_BUTTON_FRAME);

		startButton.collisions(*cursor, buttonNS::START_BUTTON_FRAME, buttonNS::START_HOVER_BUTTON_FRAME, audio);
		settingsButton.collisions(*cursor, buttonNS::SETTINGS_BUTTON_FRAME, buttonNS::SETTINGS_HOVER_BUTTON_FRAME, audio);
		creditsButton.collisions(*cursor, buttonNS::CREDITS_BUTTON_FRAME, buttonNS::CREDITS_HOVER_BUTTON_FRAME, audio);
		exitButton.collisions(*cursor, buttonNS::EXIT_BUTTON_FRAME, buttonNS::EXIT_HOVER_BUTTON_FRAME, audio);
	}

	if (!gameStart && settings && !enterKey)
	{
		rightButton.collisions(*cursor, settingsNS::RIGHT_FRAME, settingsNS::RIGHT_HOVER, audio);
		leftButton.collisions(*cursor, settingsNS::LEFT_FRAME, settingsNS::LEFT_HOVER, audio);
		upButton.collisions(*cursor, settingsNS::UP_FRAME, settingsNS::UP_HOVER, audio);
		downButton.collisions(*cursor, settingsNS::DOWN_FRAME, settingsNS::DOWN_HOVER, audio);
		meleeButton.collisions(*cursor, settingsNS::MELEE_FRAME, settingsNS::MELEE_HOVER, audio);
		rangeButton.collisions(*cursor, settingsNS::RANGE_FRAME, settingsNS::RANGE_HOVER, audio);
		distractButton.collisions(*cursor, settingsNS::DISTRACT_FRAME, settingsNS::DISTRACT_HOVER, audio);
		assassinateButton.collisions(*cursor, settingsNS::ASSASSINATE_FRAME, settingsNS::ASSASSINATE_HOVER, audio);
		backButton.collisions(*cursor, settingsNS::BACK_FRAME, settingsNS::BACK_HOVER, audio);
		defaultButton.collisions(*cursor, settingsNS::DEFAULT_FRAME, settingsNS::DEFAULT_HOVER, audio);
	}

	if (gameStart && !assValk->getPause())
	{
		assValk->collisions();
		pauseButton.collisions(*cursor, dashboardNS::PAUSE_FRAME, dashboardNS::PAUSE_HOVER_FRAME, audio);
	}

	if (gameStart && assValk->getPause())
	{
		resumeButton.collisions(*cursor, buttonNS::RESUME_BUTTON_FRAME, buttonNS::RESUME_HOVER_BUTTON_FRAME, audio);
		pExitButton.collisions(*cursor, buttonNS::EXIT_BUTTON_FRAME, buttonNS::EXIT_HOVER_BUTTON_FRAME, audio);

	}
}

void MainMenu::render()
{
	graphics->spriteBegin();

	if (gameStart)
	{
		assValk->render();
		pauseButton.draw();
	}

	if (gameStart && assValk->getPause())
	{
		mmBackground.draw();
		resumeButton.draw();
		pExitButton.draw();

		const int bufferSize = 36;
		static char paused[bufferSize];
		_snprintf(paused, bufferSize, "Paused");
		pausedText->setFontColor(graphicsNS::WHITE);
		pausedText->print(paused, resumeButton.getY(), GAME_HEIGHT / 4);

	}

	if(!gameStart)
		mmBackground.draw();


	if (!gameStart && !settings)
	{
		startButton.draw();
		settingsButton.draw();
		creditsButton.draw();
		exitButton.draw();

		
	}

	if (!gameStart && settings)
	{
		rightButton.draw();
		leftButton.draw();
		upButton.draw();
		downButton.draw();
		meleeButton.draw();
		rangeButton.draw();
		distractButton.draw();
		assassinateButton.draw();
		defaultButton.draw();
		backButton.draw();

		// Current Key Text
		const int bufferSize = 1024;
		static char rightKeyText[bufferSize];
		static char leftKeyText[bufferSize];
		static char upKeyText[bufferSize];
		static char downKeyText[bufferSize];
		static char meleeKeyText[bufferSize];
		static char rangeKeyText[bufferSize];
		static char distractKeyText[bufferSize];
		static char assassinateKeyText[bufferSize];

		// Right key
		_snprintf(rightKeyText, bufferSize, "Default Key: %c", (char)key->getRightKey());
		rightKey->setFontColor(graphicsNS::WHITE);
		rightKey->print(rightKeyText, (rightButton.getX() + rightButton.getWidth()), rightButton.getY());

		// Left key
		_snprintf(leftKeyText, bufferSize, "Default Key: %c", (char)key->getLeftKey());
		leftKey->setFontColor(graphicsNS::WHITE);
		leftKey->print(leftKeyText, (leftButton.getX() + leftButton.getWidth()), leftButton.getY());

		// Up key
		_snprintf(upKeyText, bufferSize, "Default Key: %c", (char)key->getUpKey());
		upKey->setFontColor(graphicsNS::WHITE);
		upKey->print(upKeyText, (upButton.getX() + upButton.getWidth()), upButton.getY());

		// Down key
		_snprintf(downKeyText, bufferSize, "Default Key: %c", (char)key->getDownKey());
		downKey->setFontColor(graphicsNS::WHITE);
		downKey->print(downKeyText, (downButton.getX() + downButton.getWidth()), downButton.getY());

		// Melee key
		_snprintf(meleeKeyText, bufferSize, "Default Key: %c", (char)key->getMeleeKey());
		meleeKey->setFontColor(graphicsNS::WHITE);
		meleeKey->print(meleeKeyText, (meleeButton.getX() + meleeButton.getWidth()), meleeButton.getY());

		// Range key
		_snprintf(rangeKeyText, bufferSize, "Default Key: %c", (char)key->getRangeKey());
		rangeKey->setFontColor(graphicsNS::WHITE);
		rangeKey->print(rangeKeyText, (rangeButton.getX() + rangeButton.getWidth()), rangeButton.getY());

		// Distract key
		_snprintf(distractKeyText, bufferSize, "Default Key: %c", (char)key->getDistractKey());
		distractKey->setFontColor(graphicsNS::WHITE);
		distractKey->print(distractKeyText, (distractButton.getX() + distractButton.getWidth()), distractButton.getY());

		// Assassinate Key
		_snprintf(assassinateKeyText, bufferSize, "Default Key: %c", (char)key->getAssassinateKey());
		assassinateKey->setFontColor(graphicsNS::WHITE);
		assassinateKey->print(assassinateKeyText, (assassinateButton.getX() + assassinateButton.getWidth()), assassinateButton.getY());

	}

	cursor->draw();


	graphics->spriteEnd();
}

void MainMenu::releaseAll()
{
	if (gameStart)
		assValk->releaseAll();
	else
	{
		mmBackgroundTexture.onLostDevice();
		buttonsTexture.onLostDevice();
	}
	mouseTextures.onLostDevice();
	SAFE_DELETE(cursor);
	SAFE_DELETE(key);
	SAFE_DELETE(rightKey);
	SAFE_DELETE(leftKey);
	SAFE_DELETE(upKey);
	SAFE_DELETE(downKey);
	SAFE_DELETE(meleeKey);
	SAFE_DELETE(rangeKey);
	SAFE_DELETE(distractKey);
	SAFE_DELETE(assassinateKey);
	SAFE_DELETE(pausedText);

}

void MainMenu::resetAll()
{
	if (gameStart)
		assValk->resetAll();
	else
	{
		mmBackgroundTexture.onResetDevice();
		buttonsTexture.onResetDevice();
	}
	mouseTextures.onResetDevice();
}
