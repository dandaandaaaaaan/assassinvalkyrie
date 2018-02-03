#pragma once

#ifndef _KEYBINDING_H
#define _KEYBINDING_H
#define WIN32_LEAN_AND_MEAN

#include "constants.h"

class KeyBinding
{
private:
	UCHAR	RIGHT_KEY;
	UCHAR	LEFT_KEY;
	UCHAR	DOWN_KEY;
	UCHAR	UP_KEY;
	UCHAR	JUMP_KEY;
	UCHAR	MELEE_KEY;
	UCHAR	RANGE_KEY;
	UCHAR	DISTRACT_KEY;
	UCHAR	ASSASSINATE_KEY;

public:
	KeyBinding();

	void	defaultKey();

	void	setRightKey(UCHAR value)		{ RIGHT_KEY = value; }
	UCHAR	getRightKey()					{ return RIGHT_KEY; }

	void	setLeftKey(UCHAR value)			{ LEFT_KEY = value; }
	UCHAR	getLeftKey()					{ return LEFT_KEY; }

	void	setDownKey(UCHAR value)			{ DOWN_KEY = value; }
	UCHAR	getDownKey()					{ return DOWN_KEY; }

	void	setUpKey(UCHAR value)			{ UP_KEY = value; }
	UCHAR	getUpKey()						{ return UP_KEY; }

	void	setJumpKey(UCHAR value)			{ JUMP_KEY = value; }
	UCHAR	getJumpKey()					{ return JUMP_KEY; }

	void	setMeleeKey(UCHAR value)		{ MELEE_KEY = value; }
	UCHAR	getMeleeKey()					{ return MELEE_KEY; }

	void	setRangeKey(UCHAR value)		{ RANGE_KEY = value; }
	UCHAR	getRangeKey()					{ return RANGE_KEY; }

	void	setDistractKey(UCHAR value)		{ DISTRACT_KEY = value; }
	UCHAR	getDistractKey()				{ return DISTRACT_KEY; }

	void	setAssassinateKey(UCHAR value)	{ ASSASSINATE_KEY = value; }
	UCHAR	getAssassinateKey()				{ return ASSASSINATE_KEY; }
};

#endif