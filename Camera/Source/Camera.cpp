#include "./Camera/Include/Camera.h"

Camera::Camera()
{
	Initialize();

}

void Camera::Initialize()
{
	cameraWorldPos_ = { 500,200 };
	size_ = { 1280,720 };
	scale_ = { 1.0f,1.0f };
	theta_ = 0;
	degree_ = 0;
	raito_ = 1.0f;
	/*cameraWorldMatrix_ = MakeAffineMatrix(scale_, theta_, cameraWorldPos_);
	viewMatrix_ = InverseMatrix(cameraWorldMatrix_);
	orthMatrix_ = MakeOrthographicMatrix(-size_.x / 2, size_.y / 2, size_.x / 2, -size_.y / 2);
	viewportMatrix_ = MakeViewportMatrix(0, 0, static_cast<float> (kWindowSizeX), static_cast<float>(kWindowSizeY));
	*/

}

void Camera::Update(char *keys)
{
	
	if (keys[DIK_RIGHT])
	{
		degree_ += 3;
	}
	if (keys[DIK_LEFT])
	{
		degree_ -= 3;

	}
	theta_ = (degree_ / 180.0f) * float(3.1415f);
	rotateMatrix_ = MakeRotateMatrix(theta_);
	cameraWorldMatrix_ = MaketranslateMatrix(cameraWorldPos_);
	
	//cameraWorldMatrix_ = MakeAffineMatrix({ scale_.x * raito_,scale_.y * raito_ }, theta_, cameraWorldPos_);
	viewMatrix_ = InverseMatrix(cameraWorldMatrix_);
	orthMatrix_ = MakeOrthographicMatrix(-size_.x / 2/(scale_.x * raito_), size_.y / 2 / (scale_.y * raito_),
		size_.x / 2 / (scale_.x * raito_), -size_.y / 2 / (scale_.y * raito_));
	viewportMatrix_ = MakeViewportMatrix(0, 0, static_cast<float> (kWindowSizeX), static_cast<float>(kWindowSizeY));
	
	viewMatrix_ = Multiply(viewMatrix_, rotateMatrix_);

#ifdef _DEBUG
	ImGui::Begin("test");
	ImGui::SliderFloat2("cameraPos", &cameraWorldPos_.x, -1000.0f, 1000.0f);

	ImGui::SliderFloat2("scale", &scale_.x, 0.1f, 3.0f);
	ImGui::SliderFloat("degree_", &degree_, 0, 360.0f);
	ImGui::SliderFloat("raito_", &raito_, 0, 2.0f);
	ImGui::End();
#endif // DEBUG

	
	
}
