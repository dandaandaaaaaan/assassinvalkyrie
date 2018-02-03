#include "dashboard.h"

Dashboard::Dashboard()
{
	healthRemaining = new TextDX();
	stealthLevel = new TextDX();
	speedLevel = new TextDX();
	rangeLevel = new TextDX();
	armorLevel = new TextDX();

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

}

void Dashboard::draw()
{
	dashboard.draw();
	underHealth.draw(graphicsNS::BLACK);
	playerHealth.draw(graphicsNS::RED);

	stealthIcon.draw();
	speedIcon.draw();
	rangeIcon.draw();
	armorIcon.draw();

	const int textSize = 20;
	static char text[textSize];
	_snprintf(text, textSize, "%d/%d", (int)playerCurrentHealth, (int)playerMaxHealth);
	healthRemaining->setFontColor(graphicsNS::WHITE);
	healthRemaining->print(text, underHealth.getX(), underHealth.getY());

	
	static char stealth[textSize];
	_snprintf(stealth, textSize, "%d", (int)stealthPoints);
	stealthLevel->setFontColor(graphicsNS::WHITE);
	stealthLevel->print(stealth, (stealthIcon.getX() + stealthIcon.getWidth() + 20), (stealthIcon.getY() + 20));

	static char speed[textSize];
	_snprintf(speed, textSize, "%d", (int)stealthPoints);
	speedLevel->setFontColor(graphicsNS::WHITE);
	speedLevel->print(speed, (speedIcon.getX() + speedIcon.getWidth() + 20), (speedIcon.getY() + 20));

	static char range[textSize];
	_snprintf(range, textSize, "%d", (int)stealthPoints);
	rangeLevel->setFontColor(graphicsNS::WHITE);
	rangeLevel->print(range, (rangeIcon.getX() - 20), (rangeIcon.getY() + 20));

	static char armor[textSize];
	_snprintf(armor, textSize, "%d", (int)stealthPoints);
	armorLevel->setFontColor(graphicsNS::WHITE);
	armorLevel->print(armor, (armorIcon.getX() - 20), (armorIcon.getY() + 20));


}

void Dashboard::update(float frameTime,Player *playerM, Input *input)
{
	playerCurrentHealth = playerM->getHealth();
	playerHealth.setHealthSize(playerM->getHealth());
	stealthPoints = playerM->getStealthLevel();
	speedPoints = playerM->getSpeedLevel();
	rangePoints = playerM->getRangeLevel();
	armorPoints = playerM->getArmorLevel();

	VECTOR2 collisionVector;
	if (stealthIcon.collidesWith(*mouse, collisionVector) && playerM->getSkillPoints() >= 1 && input->getMouseLButton())
	{
		playerM->setStealthLevel();
		playerM->useSkillPoints();
	}

	if (speedIcon.collidesWith(*mouse, collisionVector) && playerM->getSkillPoints() >= 1 && input->getMouseLButton())
	{
		playerM->setSpeedLevel();
		playerM->useSkillPoints();
	}

	if (rangeIcon.collidesWith(*mouse, collisionVector) && playerM->getSkillPoints() >= 1 && input->getMouseLButton())
	{
		playerM->setRangeLevel();
		playerM->useSkillPoints();
	}

	if (armorIcon.collidesWith(*mouse, collisionVector) && playerM->getSkillPoints() >= 1 && input->getMouseLButton())
	{
		playerM->setArmorLevel();
		playerM->useSkillPoints();
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

