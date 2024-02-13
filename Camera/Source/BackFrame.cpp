#include "./Camera/Include/BackFrame.h"
BackFrame::BackFrame()
{
	Init();
}

void BackFrame::Init()
{
	size_ = { 128,128 };

	vertex_ = DrawFunction::TransformeVertex(size_);
	/*vertex_.leftTop = { -size_.x / 2,size_.y / 2 };
	vertex_.rightTop = { size_.x / 2,size_.y / 2 };
	vertex_.leftBottom = { -size_.x / 2,-size_.y / 2 };
	vertex_.rightBottom = { size_.x / 2,-size_.y / 2 };*/

	for (int y = 0; y < row; y++)
	{
		for (int x = 0; x < culumn; x++)
		{
			pos_[y][x] = { size_.x / 2 + x * size_.x,size_.x / 2 + y * size_.y };
			pos_[y][x].x -= size_.x * ((float)culumn / 2);
			pos_[y][x].y -= size_.y * ((float)row / 2);

		}
	}
	worldMatrix_ = {};
	wvpVpMatrix_ = {};

	color_ = 0xffffffff;
	textureSRC_ = { 0,0 };
	textureSize_ = { 128,128 };
	texture_ = Novice::LoadTexture("./Camera/Include/Resources/frame.png");
}

void BackFrame::Update()
{

}

void BackFrame::Draw(Camera* camera_)
{
	for (int y = 0; y < row; y++)
	{
		for (int x = 0; x < culumn; x++)
		{
			worldMatrix_ = MaketranslateMatrix(pos_[y][x]);

			//worldMatrix_ = MaketranslateMatrix(worldPos_);

			wvpVpMatrix_ = Multiply(worldMatrix_, camera_->GetViewMatrix());
			wvpVpMatrix_ = Multiply(wvpVpMatrix_, camera_->GetOrthMatrix());
			wvpVpMatrix_ = Multiply(wvpVpMatrix_, camera_->GetViewportMatrix());

			MakeVertexTransform(vertex_, screenVertex_, wvpVpMatrix_);

			DrawFunction::ShortDrawQuad(
				screenVertex_, textureSRC_, textureSize_, texture_, color_
			);
			/*Novice::DrawQuad(
				static_cast<int>(screenVertex_.leftTop.x),
				static_cast<int>(screenVertex_.leftTop.y),
				static_cast<int>(screenVertex_.rightTop.x),
				static_cast<int>(screenVertex_.rightTop.y),
				static_cast<int>(screenVertex_.leftBottom.x),
				static_cast<int>(screenVertex_.leftBottom.y),
				static_cast<int>(screenVertex_.rightBottom.x),
				static_cast<int>(screenVertex_.rightBottom.y),
				static_cast<int>(textureSRC_.x),
				static_cast<int>(textureSRC_.y),
				static_cast<int>(textureSize_.x),
				static_cast<int>(textureSize_.y),
				texture_,
				color_
			);*/
		}
	}

	worldMatrix_ = MaketranslateMatrix({ 0,0 });

	//worldMatrix_ = MaketranslateMatrix(worldPos_);

	wvpVpMatrix_ = Multiply(worldMatrix_, camera_->GetViewMatrix());
	wvpVpMatrix_ = Multiply(wvpVpMatrix_, camera_->GetOrthMatrix());
	wvpVpMatrix_ = Multiply(wvpVpMatrix_, camera_->GetViewportMatrix());
	Novice::DrawEllipse(
		static_cast<int>(Transform({ 0,0 }, wvpVpMatrix_).x),
		static_cast<int>(Transform({ 0,0 }, wvpVpMatrix_).y),

		static_cast<int>(10* camera_->GetRaito()), static_cast<int>(10* camera_->GetRaito())
		,0, RED, kFillModeSolid

	);
}
