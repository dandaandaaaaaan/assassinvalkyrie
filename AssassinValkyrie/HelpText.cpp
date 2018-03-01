

#include "helpText.h"

HelpText::HelpText() : Fill()
{
}

bool HelpText::initialize(Graphics *g, VECTOR2 pos, int t)
{
	setX(pos.x);
	setY(pos.y);
	type = t;
	move = new MovementComponent(this);
	if (!text.initialize(g, 25, false, false, "Spectre 007"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing help text"));
}

void HelpText::update(float frameTime, int direction)
{
	Fill::update(frameTime, direction);
}

void HelpText::draw()
{
	const int bufferSize = 100;
	static char buffer[bufferSize];
	if (type == 1)
		_snprintf(buffer, bufferSize, HelpTextNS::MOVE);
	if (type == 2)
		_snprintf(buffer, bufferSize, HelpTextNS::LADDER);
	if (type == 3)
		_snprintf(buffer, bufferSize, HelpTextNS::HIDE_ASS);
	if (type == 4)
		_snprintf(buffer, bufferSize, HelpTextNS::TOSS);
	if (type == 5)
		_snprintf(buffer, bufferSize, HelpTextNS::ATTACK);
	text.setFontColor(graphicsNS::WHITE);
	text.print(buffer, getX(), getY());
}
