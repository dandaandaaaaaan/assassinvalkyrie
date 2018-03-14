// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Chua Wei Jie Timothy
// Student Number	: S10165581F

#include "enemy.h"

Enemy::Enemy(Entity *play) : Entity()
{
	collisionType = entityNS::BOX;
	health = new HealthComponent(&dieAnimation);
	move = new PatrolMovement(this);
	state_ = new PatrollingState();
	player = play;
	vision = new Ray();
	triggerAlert = false;
}

Enemy::~Enemy()
{
	SAFE_DELETE(health);
	SAFE_DELETE(move);
	SAFE_DELETE(state_);
	SAFE_DELETE(attack);
	SAFE_DELETE(vision);
}

bool Enemy::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM, TextureManager *textureHealth)
{
	cautionAnimation.initialize(gamePtr->getGraphics(), cautionNS::WIDTH, cautionNS::HEIGHT, cautionNS::TEXTURE_COLS, textureHealth);
	cautionAnimation.setCurrentFrame(cautionNS::FRAME);
	cautionAnimation.setVisible(false);
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void Enemy::handleInput(EnemyState* newState, Input *i, PLATFORM *p)
{	
	EnemyState* state;
	if (newState == NULL)
		state = state_->handleInput(this, player, *p, i);
	else
		state = newState;

	if (state != NULL)
	{
		SAFE_DELETE(state_);
		state_ = state;
	}
}

void Enemy::update(float frameTime, PLATFORM p, Audio *a)
{
	if (!health->getDieAnimation()) {
		state_->update(this, player);

		move->update(frameTime);
		attack->update(frameTime);
		vision->setDirection(move->getCurrentVelocity());
		vision->updateVision(p);
	}
	health->update(frameTime, { spriteData.x + spriteData.width / 2, spriteData.y }, a);
	cautionAnimation.setX(spriteData.x + spriteData.width / 2 - cautionNS::WIDTH / 2);
	cautionAnimation.setY(spriteData.y - cautionNS::HEIGHT * 2);
	Entity::update(frameTime);
}

void Enemy::ai(PLATFORM p, Input *i, float viewM)
{
	handleInput(NULL, i, &p);
	float factor = 1;
	if (viewM > 1)
	{
		viewM = viewM - 0.5;
		factor = 10 - viewM;
		factor /= 10;
	}
	vision->setViewMultiplier(factor);
}

void Enemy::draw()
{
	if (move->getCurrentVelocity() > 0)
		flipHorizontal(false);
	else
		flipHorizontal(true);
	
	COLOR_ARGB c = health->getDamageAnimation();
	if (!health->getDieAnimation())
		attack->draw(this,c);

	Image::draw(c);
	health->draw(this);
	cautionAnimation.draw();
}

void Enemy::drawRay(Graphics *g)
{
	vision->render(g);
}

void Enemy::drawCaution(bool value)
{
	cautionAnimation.setVisible(value);
}