#include "button.h"

Button::Button() : Entity()
{
	spriteData.width = buttonNS::BUTTON_WIDTH;
	spriteData.height = buttonNS::BUTTON_HEIGHT;
	spriteData.rect.bottom = buttonNS::BUTTON_HEIGHT;
	spriteData.rect.right = buttonNS::BUTTON_WIDTH;
	spriteData.x = getX();
	spriteData.y = getY();
	spriteData.rect.bottom = buttonNS::BUTTON_HEIGHT;
	spriteData.rect.right = buttonNS::BUTTON_WIDTH;

	edge = RECT{ (long)(-buttonNS::BUTTON_WIDTH / 2), (long)(-buttonNS::BUTTON_HEIGHT / 2), (long)(buttonNS::BUTTON_WIDTH / 2), (long)(buttonNS::BUTTON_HEIGHT / 2) };
	collisionType = entityNS::BOX;

	mouseOn = false;
}

Button::~Button()
{
	releaseAll();
}

bool Button::initialize(Graphics *g, int width, int height, int ncols, TextureManager *textureM, Cursor *cursor)
{
	mouse = *cursor;
	return(Image::initialize(g, width, height, ncols, textureM));
}

void Button::update(int frame)
{
	setCurrentFrame(frame);
}

void Button::updateFrame()
{
	setCurrentFrame(1);
}

void Button::draw()
{
	Image::draw();
}

bool Button::click(Entity &ent)
{
	if (collideButton(ent) && input->getMouseLButton())
		return 1;
}

void Button::collisions(int startFrame, int endFrame)
{
	update(endFrame);
}

void Button::collisions(Entity &ent, int startFrame, int endFrame, Audio *a)
{
	if (collideButton(ent))
	{
		update(endFrame);
	}
	else
	{
		update(startFrame);
	}
}

bool Button::collideButton(Entity &ent)
{
	if ((getCenterX() + edge.right*getScale() < ent.getCenterX() + ent.getEdge().left*ent.getScale()) ||
		(getCenterX() + edge.left*getScale() > ent.getCenterX() + ent.getEdge().right*ent.getScale()) ||
		(getCenterY() + edge.bottom*getScale() < ent.getCenterY() + ent.getEdge().top*ent.getScale()) ||
		(getCenterY() + edge.top*getScale() > ent.getCenterY() + ent.getEdge().bottom*ent.getScale()))
	{
		return false;
	}
	return true;
}


bool Button::collideWithin()
{
	RECT rect;
	rect.left	= spriteData.x;
	rect.right	= spriteData.x + spriteData.width;
	rect.top	= spriteData.y;
	rect.bottom = spriteData.y + spriteData.height;


	if (!mouse.outsideRect(rect))

	{
		return 1;
	}
	return 0;
}

void Button::releaseAll()
{
}

void Button::resetAll()
{
}
