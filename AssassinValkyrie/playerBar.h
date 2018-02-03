#pragma once

#ifndef _PLAYERBAR_H
#define _PLAYERBAR_H
#define WIN32_LEAN_AND_MEAN
#include "image.h"
#include "entity.h"
#include "constants.h"

namespace playerBarNS
{
	const int WIDTH = 200;
	const int HEIGHT = 50;
	const int NCOLS = 1;

}

class PlayerBar : public Image
{
private:
	int fullHealth;
	int totalExp;
	int currentExp;

public:
	bool initialize(Graphics *graphics, TextureManager *textureM, int total_health);
	void setHealthSize(int value);
	void setXPSize(int value);
};

#endif