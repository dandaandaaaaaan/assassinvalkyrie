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
	TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void Enemy::handleInput(PLATFORM p)
{
	EnemyState* state = state_->handleInput(this, player,p);
	if (state != NULL)
	{
		SAFE_DELETE(state_);
		state_ = state;
	}
}

void Enemy::update(float frameTime, PLATFORM p)
{
	if (!health->getDieAnimation()) {
		handleInput(p);
		state_->update(this, player);

		move->update(frameTime);
		attack->update(frameTime);
		vision->setDirection(move->getCurrentVelocity());
		vision->updateVision(p);
	}
	health->update(frameTime, { spriteData.x + spriteData.width / 2, spriteData.y });

	Entity::update(frameTime);
}

void Enemy::ai()
{
}

void Enemy::draw()
{
	if (move->getCurrentVelocity() > 0)
		flipHorizontal(false);
	else
		flipHorizontal(true);
	
	COLOR_ARGB c = health->getDamageAnimation();
	if (!health->getDieAnimation()) {
		attack->draw(this,c);
	}
	Image::draw(c);
	health->draw(this);		//	image::draw inside health
}

void Enemy::drawRay(Graphics *g)
{
	vision->render(g);
}