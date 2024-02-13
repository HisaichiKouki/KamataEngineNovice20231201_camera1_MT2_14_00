#pragma once
#include <Vector2.h>

static int kWindowSizeX = 1280;
static int kWindowSizeY = 720;
struct  intVector2
{
	int x;
	int y;
};

struct Vertex
{
	Vector2 leftTop;
	Vector2 rightTop;
	Vector2 leftBottom;
	Vector2 rightBottom;
};

struct Matrix3x3
{
	float m[3][3];
};
