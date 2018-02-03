#include "playerBar.h"

bool PlayerBar::initialize(Graphics *graphics, TextureManager *textureM, int total_health)
{
	fullHealth = total_health;
	return Image::initialize(graphics, playerBarNS::WIDTH, playerBarNS::HEIGHT, playerBarNS::NCOLS, textureM);
}

void PlayerBar::setHealthSize(int health)
{
	if (health < 0)
		health = 0;
	else if (health > fullHealth)
		health = fullHealth;
	spriteData.rect.right = spriteData.rect.left + (LONG)(spriteData.width * health / fullHealth);
}

void PlayerBar::setXPSize(int XP)
{
	if (XP < 0)
		XP = 0;
	else if (XP > fullHealth)
		XP = fullHealth;
	spriteData.rect.right = spriteData.rect.left + (LONG)(spriteData.width * XP / fullHealth);
}

