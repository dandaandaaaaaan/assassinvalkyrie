

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

void HelpText::draw(int stage)
{
	const int bufferSize = 100;
	static char buffer[bufferSize];
	if (stage == 0)
	{
		if (type == 1)
			_snprintf(buffer, bufferSize, HelpTextNS::MOVE);
		else if (type == 2)
			_snprintf(buffer, bufferSize, HelpTextNS::LADDER);
		else if (type == 3)
			_snprintf(buffer, bufferSize, HelpTextNS::HIDE_ASS);
		else if (type == 4)
			_snprintf(buffer, bufferSize, HelpTextNS::TOSS);
		else if (type == 5)
			_snprintf(buffer, bufferSize, HelpTextNS::ATTACK);
	}
	else if (stage == 1)
	{
		if (type == 1)
			_snprintf(buffer, bufferSize, HelpTextNS2::MOVE);
		else if (type == 2)
			_snprintf(buffer, bufferSize, HelpTextNS2::LADDER);
		else if (type == 3)
			_snprintf(buffer, bufferSize, HelpTextNS2::HIDE_ASS);
		else if (type == 4)
			_snprintf(buffer, bufferSize, HelpTextNS2::TOSS);
	}
	text.setFontColor(graphicsNS::WHITE);
	text.print(buffer, getX(), getY());
}
