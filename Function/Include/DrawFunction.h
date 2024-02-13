#pragma once
#include "struct.h"
#include <Novice.h>


namespace DrawFunction {

	Vertex TransformeVertex(Vector2 Size);

	void ShortDrawQuad(Vertex vertex, Vector2 texSRC, Vector2 texSize, int texrture, unsigned int color);
}


