// Module			: Gameplay Programming
// Assignment1		: Assassin Valkyrie
// Student Number	: Png Yeow Li
// Student Number	: S10164245H

#include "dashboard.h"

Dashboard::Dashboard()
{
	healthRemaining = new TextDX();
	XP = new TextDX();
	stealthLevel = new TextDX();
	speedLevel = new TextDX();
	rangeLevel = new TextDX();
	armorLevel = new TextDX();
	inventoryCount = new TextDX();
	skillTooltip = new TextDX();

	mins = 0;
	secs = 0;
	
}

Dashboard::~Dashboard()
{
}

bool Dashboard::initialize(Graphics *g, Cursor *cursor, Player *playerM)
{
	mouse = cursor;

	if (!healthRemaining->initialize(g, 30, false, false, "Spectre 007"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing dashboard text"));

	if (!skillTexture.initialize(g, SKILL_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing skill icon texture"));

	if (!stealthIcon.initialize(g, buttonNS::SKILL_WIDTH, buttonNS::SKILL_HEIGHT, 0, &skillTexture, mouse))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializng stealth icon"));

	stealthIcon.setCurrentFrame(buttonNS::STEALTH_FRAME);
	stealthIcon.setX(((GAME_WIDTH / 2) - 150 - stealthIcon.getWidth())*stealthIcon.getScale());
	stealthIcon.setY((GAME_HEIGHT - 15 - stealthIcon.getHeight())*stealthIcon.getScale());

	if (!speedIcon.initialize(g, buttonNS::SKILL_WIDTH, buttonNS::SKILL_HEIGHT, 0, &skillTexture, mouse))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializng stealth icon"));

	speedIcon.setCurrentFrame(buttonNS::SPEED_FRAME);
	speedIcon.setX(((GAME_WIDTH / 2) - 50 - speedIcon.getWidth())*speedIcon.getScale());
	speedIcon.setY((GAME_HEIGHT - 15 - speedIcon.getHeight())*speedIcon.getScale());

	if (!rangeIcon.initialize(g, buttonNS::SKILL_WIDTH, buttonNS::SKILL_HEIGHT, 0, &skillTexture, mouse))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializng stealth icon"));

	rangeIcon.setCurrentFrame(buttonNS::RANGE_FRAME);
	rangeIcon.setX(((GAME_WIDTH / 2) + 50)*rangeIcon.getScale());
	rangeIcon.setY((GAME_HEIGHT - 15 - rangeIcon.getHeight())*rangeIcon.getScale());

	if (!armorIcon.initialize(g, buttonNS::SKILL_WIDTH, buttonNS::SKILL_HEIGHT, 0, &skillTexture, mouse))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializng stealth icon"));

	armorIcon.setCurrentFrame(buttonNS::ARMOUR_FRAME);
	armorIcon.setX(((GAME_WIDTH / 2) + 150)*armorIcon.getScale());
	armorIcon.setY((GAME_HEIGHT - 15 - armorIcon.getHeight())*armorIcon.getScale());

	if (!dashboardTexture.initialize(g,DASHBOARD_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing dashboard"));

	if (!dashboard.initialize(g, GAME_WIDTH, GAME_HEIGHT, 0, &dashboardTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing dashboard"));

	if (!tooltipTexture.initialize(g, TOOLTIP_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tooltip"));

	if (!tooltip.initialize(g, 201, 51, 0, &tooltipTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tooltip"));
	tooltip.setX(mouse->getX());
	tooltip.setY(mouse->getY() - tooltip.getHeight());
	tooltip.setCurrentFrame(0);


	if (!barTexture.initialize(g, BAR_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player bar"));
	
	//Health Bar
	if (!underHealth.initialize(g, &barTexture, playerM->getMaxHealth()))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player health"));
	underHealth.setX(10);
	underHealth.setY(10);

	//Health Bar
	if (!playerHealth.initialize(g, &barTexture, playerM->getHealth()))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player health"));
	playerHealth.setX(10);
	playerHealth.setY(10);

	playerMaxHealth = playerM->getMaxHealth();
	playerCurrentHealth = playerM->getHealth();

	// XP bar
	if (!underExp.initialize(g, &barTexture, playerM->getNextLevelXP()))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player health"));
	underExp.setX(10);
	underExp.setY(40);
	if (!playerExp.initialize(g, &barTexture, playerM->getNextLevelXP()))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player health"));
	playerExp.setX(10);
	playerExp.setY(40);

	playerCurrentXP = playerM->getTotalXP();
	playerMaxXP = playerM->getNextLevelXP();

	if (!XP->initialize(g, dashboardNS::SKILL_TEXT_HEIGHT, false, false, "Spectre 007"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing dashboard text"));

	// Stealth points
	if (!stealthLevel->initialize(g, dashboardNS::SKILL_TEXT_HEIGHT, false, false, "Spectre 007"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing dashboard text"));
	stealthPoints = playerM->getStealthLevel();

	// Speed points
	if (!speedLevel->initialize(g, dashboardNS::SKILL_TEXT_HEIGHT, false, false, "Spectre 007"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing dashboard text"));
	speedPoints = playerM->getSpeedLevel();

	// Range points
	if (!rangeLevel->initialize(g, dashboardNS::SKILL_TEXT_HEIGHT, false, false, "Spectre 007"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing dashboard text"));
	rangePoints = playerM->getRangeLevel();

	// Armor points
	if (!armorLevel->initialize(g, dashboardNS::SKILL_TEXT_HEIGHT, false, false, "Spectre 007"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing dashboard text"));
	armorPoints = playerM->getArmorLevel();

	if (!inventoryCount->initialize(g, dashboardNS::SKILL_TEXT_HEIGHT, false, false, "Spectre 007"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing dashboard text"));
	stoneCount = playerM->getTotalStone();
	arrowCount = playerM->getTotalArrow();

	if (!skillTooltip->initialize(g, dashboardNS::TOOLTIP_TEXT, false, false, "Spectre 007"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing dashboard text"));

}

void Dashboard::draw()
{
	dashboard.draw();
	underHealth.draw(graphicsNS::BLACK);
	playerHealth.draw(graphicsNS::RED);

	underExp.draw(graphicsNS::BLACK);
	playerExp.draw(graphicsNS::BLUE);

	stealthIcon.draw();
	speedIcon.draw();
	rangeIcon.draw();
	armorIcon.draw();

	const int textSize = 20;
	static char text[textSize];
	_snprintf(text, textSize, "%d/%d", (int)playerCurrentHealth, (int)playerMaxHealth);
	healthRemaining->setFontColor(graphicsNS::WHITE);
	healthRemaining->print(text, underHealth.getX(), underHealth.getY());
	
	static char exp[textSize];
	_snprintf(exp, textSize, "%d/%d", (int)playerCurrentXP, (int)playerMaxXP);
	XP->setFontColor(graphicsNS::WHITE);
	XP->print(exp, underExp.getX(), underExp.getY());
	
	static char stealth[textSize];
	_snprintf(stealth, textSize, "%d", (int)stealthPoints);
	stealthLevel->setFontColor(graphicsNS::WHITE);
	stealthLevel->print(stealth, (stealthIcon.getX() + stealthIcon.getWidth() + 20), (stealthIcon.getY() + 20));

	static char speed[textSize];
	_snprintf(speed, textSize, "%d", (int)speedPoints);
	speedLevel->setFontColor(graphicsNS::WHITE);
	speedLevel->print(speed, (speedIcon.getX() + speedIcon.getWidth() + 20), (speedIcon.getY() + 20));

	static char range[textSize];
	_snprintf(range, textSize, "%d", (int)rangePoints);
	rangeLevel->setFontColor(graphicsNS::WHITE);
	rangeLevel->print(range, (rangeIcon.getX() - 20), (rangeIcon.getY() + 20));

	static char armor[textSize];
	_snprintf(armor, textSize, "%d", (int)armorPoints);
	armorLevel->setFontColor(graphicsNS::WHITE);
	armorLevel->print(armor, (armorIcon.getX() - 20), (armorIcon.getY() + 20));

	static char invenCount[textSize];
	_snprintf(invenCount, textSize, "Arrow: %d \nStone: %d", (int)arrowCount, (int)stoneCount);
	inventoryCount->setFontColor(graphicsNS::WHITE);
	inventoryCount->print(invenCount, (underHealth.getX()), (underHealth.getY() + underHealth.getWidth() + 10));

	if (tooltipActive)
	{
		const int tooltipSize = 50;
		static char tooltipText[tooltipSize];

		tooltip.draw();
		if (tooltipType == 1)
		{
			_snprintf(tooltipText, tooltipSize, "Increase Player's Stealth");
			skillTooltip->setFontColor(graphicsNS::WHITE);
			skillTooltip->print(tooltipText, (tooltip.getX() + 23), (tooltip.getY() + 20));
		}
		if (tooltipType == 2)
		{
			_snprintf(tooltipText, tooltipSize, "Increase Player's Speed");
			skillTooltip->setFontColor(graphicsNS::WHITE);
			skillTooltip->print(tooltipText, (tooltip.getX() + 32), (tooltip.getY() + 20));
		}
		if (tooltipType == 3)
		{
			_snprintf(tooltipText, tooltipSize, "Increase Arrow Range");
			skillTooltip->setFontColor(graphicsNS::WHITE);
			skillTooltip->print(tooltipText, (tooltip.getX() + 34), (tooltip.getY() + 20));
		}
		if (tooltipType == 4)
		{
			_snprintf(tooltipText, tooltipSize, "Increase Player's Defence");
			skillTooltip->setFontColor(graphicsNS::WHITE);
			skillTooltip->print(tooltipText, (tooltip.getX() + 25), (tooltip.getY() + 20));
		}

	}

}

void Dashboard::update(float frameTime,Player *playerM, Input *input)
{
	playerCurrentHealth = playerM->getHealth();
	playerHealth.setHealthSize(playerM->getHealth());
	playerCurrentXP = playerM->getTotalXP();
	playerExp.setXPSize(playerM->getTotalXP(), playerM->getNextLevelXP());
	stealthPoints = playerM->getStealthLevel();
	speedPoints = playerM->getSpeedLevel();
	rangePoints = playerM->getRangeLevel();
	armorPoints = playerM->getArmorLevel();


	playerMaxXP = playerM->getNextLevelXP();

	tooltipActive = false;
	tooltipType = 0;
	

	VECTOR2 collisionVector;
	if (stealthIcon.collidesWith(*mouse, collisionVector))
	{
		tooltipActive = true;
		tooltipType = 1;		
	}

	if (speedIcon.collidesWith(*mouse, collisionVector))
	{
		tooltipActive = true;
		tooltipType = 2;		
	}

	if (rangeIcon.collidesWith(*mouse, collisionVector))
	{
		tooltipActive = true;
		tooltipType = 3;
	}

	if (armorIcon.collidesWith(*mouse, collisionVector))
	{
		tooltipActive = true;
		tooltipType = 4;
	}

	if (stealthIcon.collidesWith(*mouse, collisionVector) && playerM->getSkillPoints() >= 1 && input->getMouseLButton())
	{
		playerM->setStealthLevel();
		playerM->setStealthSet(true);
		playerM->useSkillPoints();
		stealthIcon.setCurrentFrame(buttonNS::STEALTH_FRAME);
	}

	if (speedIcon.collidesWith(*mouse, collisionVector) && playerM->getSkillPoints() >= 1 && input->getMouseLButton())
	{
		playerM->setSpeedLevel();
		playerM->useSkillPoints();
		speedIcon.setCurrentFrame(buttonNS::SPEED_FRAME);
	}

	if (rangeIcon.collidesWith(*mouse, collisionVector) && playerM->getSkillPoints() >= 1 && input->getMouseLButton())
	{
		playerM->setRangeLevel();
		playerM->useSkillPoints();
		rangeIcon.setCurrentFrame(buttonNS::RANGE_FRAME);
	}

	if (armorIcon.collidesWith(*mouse, collisionVector) && playerM->getSkillPoints() >= 1 && input->getMouseLButton())
	{
		playerM->setArmorLevel();
		playerM->useSkillPoints();
		armorIcon.setCurrentFrame(buttonNS::ARMOUR_FRAME);
	}

	if (playerM->getSkillPoints() >= 1)
	{
		if ((stealthIcon.getCurrentFrame() == buttonNS::STEALTH_FRAME) && (playerM->getStealthLevel() <= 3))
			stealthIcon.setCurrentFrame(buttonNS::STEALTH_GLOW);
		if ((speedIcon.getCurrentFrame() == buttonNS::SPEED_FRAME) && (playerM->getSpeedLevel() <= 3))
			speedIcon.setCurrentFrame(buttonNS::SPEED_GLOW);
		if ((rangeIcon.getCurrentFrame() == buttonNS::RANGE_FRAME) && (playerM->getRangeLevel() <= 3))
			rangeIcon.setCurrentFrame(buttonNS::RANGE_GLOW);
		if ((armorIcon.getCurrentFrame() == buttonNS::ARMOUR_FRAME) && (playerM->getArmorLevel() <= 3))
			armorIcon.setCurrentFrame(buttonNS::ARMOUR_GLOW);
	}
	else
	{
		if ((stealthIcon.getCurrentFrame() == buttonNS::STEALTH_GLOW))
			stealthIcon.setCurrentFrame(buttonNS::STEALTH_FRAME);
		if ((speedIcon.getCurrentFrame() == buttonNS::SPEED_GLOW))
			speedIcon.setCurrentFrame(buttonNS::SPEED_FRAME);
		if ((rangeIcon.getCurrentFrame() == buttonNS::RANGE_GLOW))
			rangeIcon.setCurrentFrame(buttonNS::RANGE_FRAME);
		if ((armorIcon.getCurrentFrame() == buttonNS::ARMOUR_GLOW))
			armorIcon.setCurrentFrame(buttonNS::ARMOUR_FRAME);
	}

}

void Dashboard::collisions()
{

}

void Dashboard::releaseAll()
{
	skillTexture.onLostDevice();
	barTexture.onLostDevice();
}

void Dashboard::resetAll() 
{
	skillTexture.onResetDevice();
	barTexture.onResetDevice();
}

