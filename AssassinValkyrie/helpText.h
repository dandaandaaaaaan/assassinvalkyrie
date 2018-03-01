

#ifndef _HELPTEXT_H 
#define _HELPTEXT_H
#define WIN32_LEAN_AND_MEAN

#include "fill.h"
#include "constants.h"
#include "textDX.h"
#include <vector>

namespace HelpTextNS
{
	const auto MOVE = "Use A & D to move";
	const auto LADDER = "Press W to climb\nup ladder";
	const auto HIDE_ASS = "Press W to use hideout to avoid contact\n\nUse R to assassin an enemy";
	const auto TOSS = "Press H to toss a distraction\nto avoid direct contact";
	const auto ATTACK = "G for melee\n\nF for arrowshots";
}

class HelpText : public Fill
{
private:
	TextDX	text;
	int type;

public:
	// constructor
	HelpText();

	// inherited member functions
	bool initialize(Graphics *g, VECTOR2 pos, int t);
	void update(float frameTime, int direction);
	void draw();
};
#endif