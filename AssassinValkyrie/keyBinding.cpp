#include "keyBinding.h"

KeyBinding::KeyBinding()
{
	defaultKey();
}

void KeyBinding::defaultKey()
{
	setRightKey(DEFAULT_RIGHT_KEY);
	setLeftKey(DEFAULT_LEFT_KEY);
	setDownKey(DEFAULT_DOWN_KEY);
	setUpKey(DEFAULT_UP_KEY);
	setJumpKey(DEFAULT_JUMPING_KEY);
	setMeleeKey(DEFAULT_MELEE_KEY);
	setRangeKey(DEFAULT_RANGE_KEY);
	setDistractKey(DEFAULT_DISTRACT_KEY);
	setAssassinateKey(DEFAULT_ASSASSINATE_KEY);
}