#pragma once

#include "./Function/Include/Matrix3Calc.h"
#include <ImGuiManager.h>

class Camera
{
private:
	Vector2 cameraWorldPos_;
	Vector2 size_;
	Vector2 scale_;
	float theta_;
	float degree_;
	float raito_;

	Matrix3x3 cameraWorldMatrix_;
	Matrix3x3 viewMatrix_;
	Matrix3x3 orthMatrix_;
	Matrix3x3 viewportMatrix_;
	Matrix3x3 wvpVpMatrix_;

	Matrix3x3 rotateMatrix_;

public:
	Camera();
	~Camera();

	void Initialize();
	void Update(char* keys);

	Matrix3x3 GetcameraWorldMatrix() { return cameraWorldMatrix_; }
	Matrix3x3 GetViewMatrix() { return viewMatrix_; }
	Matrix3x3 GetOrthMatrix() { return orthMatrix_; }
	Matrix3x3 GetViewportMatrix() { return viewportMatrix_; }

	float GetRaito() { return raito_; }




};

