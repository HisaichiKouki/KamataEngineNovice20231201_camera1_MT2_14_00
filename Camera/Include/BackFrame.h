#pragma once
#include "Camera.h"
#include "./Function/Include/struct.h"
#include "./Function/Include/DrawFunction.h"
#include <Novice.h>

const int row = 32;
const int culumn = 32;

class BackFrame
{
private:
	Vector2 pos_[row][culumn];
	Vector2 size_;
	Vertex vertex_;
	Vertex screenVertex_;
	Matrix3x3 worldMatrix_;
	Matrix3x3 wvpVpMatrix_;

	unsigned int color_;
	Vector2 textureSRC_;
	Vector2 textureSize_;
	int texture_;

public:


	BackFrame();

	void Init();
	void Update();
	void Draw(Camera *camera_);
};

