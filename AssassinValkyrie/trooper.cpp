// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Chua Wei trooper Timothy
// Student Number	: S10165581F

#include "trooper.h"

Trooper::Trooper(Entity *play) : Enemy(play)
{
	spriteData.width = trooperNS::WIDTH;           // size of Ship1
	spriteData.height = trooperNS::HEIGHT;
	spriteData.x = trooperNS::X;                   // location on screen
	spriteData.y = trooperNS::Y;
	spriteData.rect.bottom = trooperNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = trooperNS::WIDTH;
	spriteData.angle = trooperNS::ROTATION;
	spriteData.scale = trooperNS::SCALE;
	velocity = VECTOR2(trooperNS::SPEED, 0);
	frameDelay = trooperNS::ANIMATION_DELAY;
	startFrame = trooperNS::START_FRAME;     // first frame of ship animation
	endFrame = trooperNS::END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	edge = RECT{ (long)(-trooperNS::WIDTH*trooperNS::SCALE / 2), (long)(-trooperNS::HEIGHT*trooperNS::SCALE / 2), (long)(trooperNS::WIDTH*trooperNS::SCALE / 2), (long)(trooperNS::HEIGHT*trooperNS::SCALE / 2) };
}

bool Trooper::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	attackAnimation.initialize(gamePtr->getGraphics(), trooperNS::MELEE_WIDTH, trooperNS::MELEE_HEIGHT, trooperNS::MELEE_TEXTURE_COLS, textureM);
	attackAnimation.setFrames(trooperNS::MELEE_START_FRAME, trooperNS::MELEE_END_FRAME);
	attackAnimation.setCurrentFrame(trooperNS::MELEE_START_FRAME);
	attackAnimation.setFrameDelay(trooperNS::ANIMATION_DELAY);
	attackAnimation.setLoop(false);

	move->setVelocity(trooperNS::SPEED);
	attack = new MeleeComponent(&attackAnimation);
	vision->init(&center.x, &center.y, trooperNS::VISION_ANGLE, trooperNS::VISION_RANGE, trooperNS::VISION_HEIGHT);

	return(Enemy::initialize(gamePtr, width, height, ncols, textureM));
}

void Trooper::ai()
{
	VECTOR2 pos1 = *getCenter() - *player->getCenter();

	if (D3DXVec2Length(&pos1) < trooperNS::MELEE_RANGE && !attack->getAnimation() && !sameSign(velocity.x, pos1.x))
	{
		attack->setAnimation(true);
		attackAnimation.setCurrentFrame(trooperNS::MELEE_START_FRAME);
	}
}