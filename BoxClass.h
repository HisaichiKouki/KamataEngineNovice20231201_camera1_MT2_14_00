#pragma once
#include "Vector2.h"
#include <Novice.h>
#include "./Function/Include/struct.h"
#include "./Function/Include/DrawFunction.h"
#include "./Camera/Include/Camera.h"
#include <math.h>
struct BoxStruct {
	Vector2 position;
	Vector2 size;
	Vector2 velocity;
	Vector2 acceleration;
	float mass;
	unsigned int color;
};

const Vector2 kGravity = { 0.0f,-9.8f };
class BoxClass
{

private:
	BoxStruct box;
	float magnitude;
	Vector2 direction;
	Vector2 frictionalForce;

	Matrix3x3 worldMatrix;
	Matrix3x3 wvpVpMatrix;

	int tex;
	Vertex vertex_;
	Vertex screenVertex_;
	Vector2 textureSRC_;
	Vector2 textureSize_;

	float miu;

	float length;

public:
	BoxClass();
	~BoxClass();
	void Init();
	void Update();
	void Draw(Camera *camera);
	void Debug();

	void SetVelocity(Vector2 setVel) { box.velocity = setVel; }

};

