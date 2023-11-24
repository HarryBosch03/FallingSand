#include "Drawing.h"

bool initialized;

Vec2 quad[] =
{
	{ -0.5f, -0.5f },
	{  0.5f, -0.5f },
	{  0.5f,  0.5f },
	{ -0.5f,  0.5f },
};

void Initalize()
{
	if (initialized) return;
}

void Drawing::DrawQuad(Vec2 min, Vec2 max, float depth)
{
	Initalize();


}
