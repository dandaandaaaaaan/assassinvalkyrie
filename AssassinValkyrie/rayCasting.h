// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Chua Wei Jie Timothy
// Student Number	: S10165581F

#ifndef _RAY_H
#define _RAY_H
#define WIN32_LEAN_AND_MEAN

#include <vector>
#include <queue>
#include <math.h>
#include "entity.h"
#include "constants.h"

typedef std::vector<Entity *> PLATFORM;
const COLOR_ARGB ALPHA = D3DCOLOR_ARGB(0, 255, 255, 255);

class Ray
{
private:
	Entity *enemy;
	double direction;
	float visibilityAngle;
	int viewDistance;
	int viewHeight;		// from center
	int rayMultiplier;
	double distMultipler;
	VECTOR2 pos;
	COLOR_ARGB color;
	VECTOR2 range1;
	VECTOR2 range2;
	std::queue<CUSTOMVERTEX> vision;

public:
	Ray();
	~Ray();

	void init(Entity *ent, float angle, int dist, int height);
	VECTOR2 Ray::maxDist(VECTOR2 cast);
	VECTOR2 castRayVector(VECTOR2 target, const PLATFORM &walls);
	void updateVision(const PLATFORM &walls);
	void render(Graphics *g);
	bool inSight(Entity entity, const PLATFORM &walls, Input *i);

	void setDirection(int d)
	{
		double old = direction;
		if (d > 0)
			direction = 0;
		else
			direction = PI;
		if (old != direction)
		{
			std::queue<CUSTOMVERTEX> empty;
			std::swap(vision, empty);
		}
	}
	void setColor(COLOR_ARGB c) { color = c; }

	//void setRayMultiplier(int i) { rayMultiplier = i; }
	//int getRayMultipler() { return rayMultiplier; }
};
#endif