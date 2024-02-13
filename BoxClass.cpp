#include "BoxClass.h"

BoxClass::BoxClass()
{
	tex = Novice::LoadTexture("white1x1.png");
	Init();
}

BoxClass::~BoxClass()
{
}

void BoxClass::Init()
{
	box = {};
	box.size = { 100,100 };
	box.position = { 50,50 };
	box.mass = 1;
	magnitude = 0;
	direction = {};
	frictionalForce = {};
	worldMatrix = {};
	wvpVpMatrix = {};

	box.color = WHITE;
	textureSRC_ = { 0,0 };
	textureSize_ = { 1,1 };
	vertex_ = DrawFunction::TransformeVertex(box.size);
	miu = 0.4f;
	length = 0;
}

void BoxClass::Update()
{

	length = sqrtf((-box.mass * kGravity.x) * (-box.mass * kGravity.x)
		+ (-box.mass * kGravity.y) * (-box.mass * kGravity.y));
	magnitude = miu * length;

	if (box.velocity.x > 0)
	{
		direction.x = -1.0f;
	}
	else if (box.velocity.x < 0)
	{
		direction.x = 1.0f;

	}
	else
	{
		direction.x = 0;
	}

	frictionalForce.x = magnitude * direction.x;
	frictionalForce.y = magnitude * direction.y;

	box.acceleration.x = frictionalForce.x / box.mass;
	box.acceleration.y = frictionalForce.y / box.mass;

	if (fabsf(box.acceleration.x/60.0f)>fabsf(box.velocity.x))
	{
		box.acceleration.x = box.velocity.x * 60.0f;
	}

	box.velocity.x += (box.acceleration.x / 60.0f);
	box.velocity.y += (box.acceleration.y / 60.0f);

	box.position.x += (box.velocity.x / 60.0f);
	box.position.y += (box.velocity.y / 60.0f);
}

void BoxClass::Draw(Camera* camera)
{

	worldMatrix = MaketranslateMatrix(box.position);
	wvpVpMatrix = Multiply(worldMatrix, camera->GetViewMatrix());
	wvpVpMatrix = Multiply(wvpVpMatrix, camera->GetOrthMatrix());
	wvpVpMatrix = Multiply(wvpVpMatrix, camera->GetViewportMatrix());

	MakeVertexTransform(vertex_, screenVertex_, wvpVpMatrix);

	DrawFunction::ShortDrawQuad(
		screenVertex_, textureSRC_, textureSize_, tex, box.color
	);
}

void BoxClass::Debug()
{
#ifdef _DEBUG
	Novice::ScreenPrintf(0, 0, "pos x=%0.1f y=%0.1f", box.position.x, box.position.y);
	Novice::ScreenPrintf(0, 20, "vel x=%0.1f y=%0.1f", box.velocity.x, box.velocity.y);
	Novice::ScreenPrintf(0, 40, "acc x=%0.1f y=%0.1f", box.acceleration.x, box.acceleration.y);
#endif // _DEBUG

}
