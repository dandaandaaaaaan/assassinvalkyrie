// Module			: Gameplay Programming
// Assignment2		: Assassin Valkyrie
// Student Number	: Chua Wei Jie Timothy
// Student Number	: S10165581F

#include "rayCasting.h"
#include "Player.h"

Ray::Ray()
{
	color = graphicsNS::WHITE;
	direction = PI;
	rayMultiplier = 100000;
	distMultipler = 1.1;
}

Ray::~Ray()
{
	std::queue<CUSTOMVERTEX> empty;
	std::swap(vision, empty);
}
void Ray::init(Entity *ent, float angle, int dist, int height)
{
	enemy = ent;
	visibilityAngle = angle;
	viewDistance = dist;
	viewHeight = height;
}

bool isLeft(VECTOR2 a, VECTOR2 b, VECTOR2 c) {
	return ((b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x)) > 0;
}
bool isRight(VECTOR2 a, VECTOR2 b, VECTOR2 c) {
	return ((b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x)) < 0;
}

float normalizeAngle(float value)
{
	if (value < 0)
		value += 2 * PI;
	return value;
}
double Dot(const VECTOR2& a, const VECTOR2& b) { return (a.x*b.x) + (a.y*b.y); }
double PerpDot(const VECTOR2& a, const VECTOR2& b) { return (a.y*b.x) - (a.x*b.y); }

bool lineCollision(VECTOR2& A1, VECTOR2& A2, VECTOR2& B1, VECTOR2& B2, double* out = 0)
{
	VECTOR2 a(A2 - A1);
	VECTOR2 b(B2 - B1);

	double f = PerpDot(a, b);
	if (!f)      // lines are parallel
		return false;

	VECTOR2 c(B2 - A2);
	double aa = PerpDot(a, c);
	double bb = PerpDot(b, c);

	if (f < 0)
	{
		if (aa > 0)     return false;
		if (bb > 0)     return false;
		if (aa < f)     return false;
		if (bb < f)     return false;
	}
	else
	{
		if (aa < 0)     return false;
		if (bb < 0)     return false;
		if (aa > f)     return false;
		if (bb > f)     return false;
	}

	if (out)
		*out = 1.0 - (aa / f);
	return true;
}

VECTOR2 Ray::maxDist(VECTOR2 cast)
{
	VECTOR2 unit = cast - pos;
	if (D3DXVec2Length(&unit) > viewDistance)
	{
		unit = *D3DXVec2Normalize(&unit, &unit) * viewDistance + pos;
		return unit;
	}
	return cast;
}

VECTOR2 Ray::castRayVector(VECTOR2 target, const PLATFORM &walls) {
	double out = rayMultiplier;
	double check = 0;
	VECTOR2 intersect{ -(float)out,-(float)out };
	VECTOR2 prev{ -1,-1 };
	for (const auto &wall : walls) {
		if (wall->outOfBounds())
			continue;

		for (size_t i = 0; i < 4; ++i) {
			VECTOR2 t = *wall->getCorner(i);
			VECTOR2 unit = t - pos;
			if ((D3DXVec2Length(&unit) > viewDistance * distMultipler))
				continue;

			VECTOR2 B1 = { *wall->getCorner(i) };
			VECTOR2 B2 = { *wall->getCorner((i + 1) % 4) };
			if (lineCollision(target, pos, B1, B2, &check))
			{
				VECTOR2 t = ((B2 - B1) * check) + B1;
				if ((check < out && check != 0) || (D3DXVec2Length(&VECTOR2{ t.x - pos.x, t.y - pos.y }) < D3DXVec2Length(&VECTOR2{ intersect.x - pos.x, intersect.y - pos.y })))
				{
					out = check;
					prev = intersect;
					intersect = ((B2 - B1) * out) + B1;
				}
			}
			if (prev != VECTOR2{-1,-1} && D3DXVec2Length(&VECTOR2{ prev.x - pos.x, prev.y - pos.y }) < D3DXVec2Length(&VECTOR2{ intersect.x - pos.x, intersect.y - pos.y }))
				intersect = prev;
		}
	}
	if (intersect == VECTOR2{ -100000 ,-100000 })
		return maxDist(target);
	return maxDist(intersect);
}

void Ray::updateVision(const PLATFORM &walls)
{
	if (enemy->isFlipHorizontal())
		pos = { enemy->getCenterX() - enemy->getWidth()*0.2f, enemy->getCenterY() - viewHeight };
	else
		pos = { enemy->getCenterX() + enemy->getWidth()*0.2f, enemy->getCenterY() - viewHeight };

	float range1Angle = direction + visibilityAngle;
	float range2Angle = direction - visibilityAngle;

	range1 = VECTOR2{ cos(range1Angle), sin(range1Angle) } *rayMultiplier;
	range2 = VECTOR2{ cos(range2Angle), sin(range2Angle) } *rayMultiplier;

	std::vector<VECTOR2> points;
	for (const auto &wall : walls)
	{
		wall->computeRotatedBox();
		for (size_t i = 0; i < 4; ++i)
		{
			if (wall->outOfBounds())
				continue;

			VECTOR2 t = *wall->getCorner(i);
			VECTOR2 unit = t - pos;
			bool c1 = isRight(pos, range1, t);
			bool c2 = isLeft(pos, range2, t);
			if (!(c1 && c2) || (D3DXVec2Length(&unit) > viewDistance * distMultipler))
				continue;

			points.push_back(*wall->getCorner(i));
		}
	}

	std::vector<VECTOR2> visPoints;

	for (const auto& point : points) {
		float angle = atan2(point.y - pos.y, point.x - pos.x);

		VECTOR2 rayVector = VECTOR2{ cos(angle + 0.0001f), sin(angle + 0.0001f) } *rayMultiplier;
		visPoints.push_back(castRayVector(rayVector, walls));

		rayVector = VECTOR2{ cos(angle - 0.0001f), sin(angle - 0.0001f) } *rayMultiplier;
		visPoints.push_back(castRayVector(rayVector, walls));

		rayVector = VECTOR2{ cos(angle), sin(angle) } *rayMultiplier;
		visPoints.push_back(castRayVector(rayVector, walls));
	}

	visPoints.push_back(castRayVector(range1, walls));
	visPoints.push_back(castRayVector(range2, walls));

	//sort the points based on their angle
	std::sort(visPoints.begin(), visPoints.end(),
		[&](const VECTOR2 &p1, const VECTOR2 &p2) {
		return normalizeAngle(atan2(p2.y - pos.y, p2.x - pos.x)) > normalizeAngle(atan2(p1.y - pos.y, p1.x - pos.x));
	});

	// Iterator of visPoints 
	std::vector<VECTOR2>::iterator it_visPoints;

	// Vision is used for actual rendering
	it_visPoints = visPoints.begin();
	while (it_visPoints != visPoints.end())
	{
		vision.push({ pos.x, pos.y, 0.5f, 1.0f, color });
		vision.push({ it_visPoints->x, it_visPoints->y,0.5f,1.0f, color  & ALPHA });
		it_visPoints++;
		if (it_visPoints != visPoints.end())
			vision.push({ it_visPoints->x, it_visPoints->y,0.5f,1.0f, color  &  ALPHA });
		else
		{
			it_visPoints = visPoints.begin();
			vision.push({ it_visPoints->x, it_visPoints->y,0.5f,1.0f, color  & ALPHA });
			break;
		}
	}
}

void Ray::render(Graphics *g)
{
	if (vision.size() >= 3)
	{
		for (int i = 0; i < round(vision.size()/3); i++)
			g->initTriangle(&vision);
	}
}

bool Ray::inSight(Entity e, const PLATFORM &walls, Input *i)
{
	VECTOR2 center = VECTOR2{ roundf(e.getCenterX()),roundf(e.getCenterY()) };
	float range1Angle = direction + visibilityAngle;
	float range2Angle = direction - visibilityAngle;

	VECTOR2 range1 = VECTOR2{ cos(range1Angle), sin(range1Angle) } *rayMultiplier;
	VECTOR2 range2 = VECTOR2{ cos(range2Angle), sin(range2Angle) } *rayMultiplier;
	bool c1 = isRight(pos, range1, center);
	bool c2 = isLeft(pos, range2, center);

	if ((c1 && c2))
	{
		VECTOR2 collision1 = castRayVector(center, walls);
		VECTOR2 collision2 = castRayVector({center.x,center.y + (95 / 4) }, walls);
		VECTOR2 collision3 = castRayVector({ center.x,center.y - (95 / 4) }, walls);

		if (VECTOR2{ roundf(collision1.x),roundf(collision1.y) } == center)
			return true;
		else {
			if (i->isKeyDown(DEFAULT_DOWN_KEY))
				return false;
			else if (collision2 == VECTOR2{ center.x, center.y + (playerNS::HEIGHT / 4) })
				return true;
			else if (collision3 == VECTOR2{ center.x, center.y - (playerNS::HEIGHT / 4) })
				return true;
		}
	}
	return false;
}