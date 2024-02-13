#include "./Function/Include/DrawFunction.h"

Vertex DrawFunction::TransformeVertex(Vector2 size)
{
	Vertex result{};
	result.leftTop = { -size.x / 2,size.y / 2 };
	result.rightTop = { size.x / 2,size.y / 2 };
	result.leftBottom = { -size.x / 2,-size.y / 2 };
	result.rightBottom = { size.x / 2,-size.y / 2 };
	return result;
}

void DrawFunction::ShortDrawQuad(Vertex vertex, Vector2 texSRC, Vector2 texSize, int texrture, unsigned int color)
{
	Novice::DrawQuad(
		static_cast<int>(vertex.leftTop.x),
		static_cast<int>(vertex.leftTop.y),
		static_cast<int>(vertex.rightTop.x),
		static_cast<int>(vertex.rightTop.y),
		static_cast<int>(vertex.leftBottom.x),
		static_cast<int>(vertex.leftBottom.y),
		static_cast<int>(vertex.rightBottom.x),
		static_cast<int>(vertex.rightBottom.y),
		static_cast<int>(texSRC.x),
		static_cast<int>(texSRC.y),
		static_cast<int>(texSize.x),
		static_cast<int>(texSize.y),
		texrture,
		color
	);
}
