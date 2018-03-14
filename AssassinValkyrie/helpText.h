

#ifndef _HELPTEXT_H 
#define _HELPTEXT_H
#define WIN32_LEAN_AND_MEAN

#include "fill.h"
#include "constants.h"
#include "textDX.h"
#include <vector>

namespace HelpTextNS
{
	const auto MOVE = "Use 'A' & 'D' to move\nAnd 'SPACE' to jump";
	const auto LADDER = "Hold 'W' to climb\nup ladder";
	const auto HIDE_ASS = "Press 'W' to use hideout to avoid contact\n\n'G' for melee\n\n'F' for arrowshots";
	const auto TOSS = "Press 'H' to toss a distraction\nto avoid direct contact";
	const auto ATTACK = "Use 'R' to assassin an enemy";
}
namespace HelpTextNS2
{
	const auto MOVE = "Skill One : ";
	const auto LADDER = "Skill Two : ";
	const auto HIDE_ASS = "Skill Three : ";
	const auto TOSS = "Skill Four : ";
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
	void draw(int stage);
};
#endif