#include "./Function/Include/Matrix3Calc.h"

#include <assert.h>
#include <corecrt_math.h>
void MatrixScreenPrintf(int x, int y, Matrix3x3 matrix)
{
	for (int row = 0; row < 3; row++)
	{
		for (int colum = 0; colum < 3; colum++)
		{
			Novice::ScreenPrintf(x + colum * kColumWidth, y + row * kRowHeight,
				"%0.2f", matrix.m[row][colum]);
		}
	}
}
Matrix3x3 MakeAffineMatrix(Vector2 scale, float theta, Vector2 translate)
{

	Matrix3x3 result{};
	result.m[0][0] = scale.x * cosf(theta);
	result.m[0][1] = scale.x * sinf(theta);
	result.m[1][0] = scale.y * -sinf(theta);
	result.m[1][1] = scale.y * cosf(theta);
	result.m[2][0] = translate.x;
	result.m[2][1] = translate.y;
	result.m[2][2] = 1.0f;

	return Matrix3x3(result);
}
Matrix3x3 MaketranslateMatrix(Vector2 translate)
{

	Matrix3x3 A{};
	A.m[0][0] = 1.0f;
	A.m[1][1] = 1.0f;
	A.m[2][2] = 1.0f;
	A.m[2][0] = translate.x;
	A.m[2][1] = translate.y;
	return Matrix3x3(A);
}



Matrix3x3 Transpose(Matrix3x3 matrix)
{
	Matrix3x3 result{};
	
	for (int row = 0; row < 3; row++)
	{
		for (int cal = 0; cal < 3; cal++)
		{
			result.m[row][cal] = matrix.m[cal][row];
		}
	}
	return result;
}

Matrix3x3 MakeOrthographicMatrix(float left, float top, float right, float bottom)
{
	Matrix3x3 result{};
	result.m[0][0] = 2.0f / (right - left);
	result.m[1][1] = 2.0f / (top - bottom);
	result.m[2][0] = (left + right) / (left - right);
	result.m[2][1] = (top + bottom) / (bottom - top);
	result.m[2][2] = 1.0f;
	return result;
}

Matrix3x3 MakeViewportMatrix(float left, float top, float width, float height)
{
	Matrix3x3 result{};
	result.m[0][0] = width / 2;
	result.m[1][1] = -height / 2;
	result.m[2][0] = left + width / 2;
	result.m[2][1] = top + height / 2;
	result.m[2][2] = 1;
	return result;
}

void MakeVertexTransform(Vertex lorcal, Vertex &vertex, Matrix3x3 matrix)
{
	
	vertex.leftTop = Transform(lorcal.leftTop, matrix);
	vertex.rightTop = Transform(lorcal.rightTop, matrix);
	vertex.leftBottom = Transform(lorcal.leftBottom, matrix);
	vertex.rightBottom = Transform(lorcal.rightBottom, matrix);
	
}

Matrix3x3 InverseMatrix(Matrix3x3 matrix)
{

	Matrix3x3 result;
	result.m[0][0] = matrix.m[1][1] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][1];
	result.m[0][1] = -(matrix.m[0][1] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][1]);
	result.m[0][2] = matrix.m[0][1] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][1];

	result.m[1][0] = -(matrix.m[1][0] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][0]);
	result.m[1][1] = matrix.m[0][0] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][1];
	result.m[1][2] = -(matrix.m[0][0] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][0]);

	result.m[2][0] = matrix.m[1][0] * matrix.m[2][0] - matrix.m[1][1] * matrix.m[2][0];
	result.m[2][1] = -(matrix.m[0][0] * matrix.m[2][1] - matrix.m[0][1] * matrix.m[2][0]);
	result.m[2][2] = matrix.m[0][0] * matrix.m[1][1] - matrix.m[0][1] * matrix.m[1][0];


	float A = matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2] +
		matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][0] +
		matrix.m[0][2] * matrix.m[0][1] * matrix.m[2][1]
		- matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][1]
		- matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][2]
		- matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1];

	for (int row = 0; row < 3; row++)
	{
		for (int colume = 0; colume < 3; colume++)
		{
			result.m[row][colume] /= A;
		}
	}

	return result;
}

//Matrix3x3 MakeTranslateMatrix(Vector2 translate)
//{
//
//	Matrix3x3 A{};
//	A.m[0][0] = 1.0f;
//	A.m[1][1] = 1.0f;
//	A.m[2][2] = 1.0f;
//	A.m[2][0] = translate.x;
//	A.m[2][1] = translate.y;
//	return Matrix3x3(A);
//}

Vector2 Transform(Vector2 vector, Matrix3x3 matrix)
{
	Vector2 result;
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];
	float w = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];

	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	return result;
}

Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2)
{

	Matrix3x3 result{};
	result.m[0][0] = matrix1.m[0][0] * matrix2.m[0][0] + matrix1.m[0][1] * matrix2.m[1][0] + matrix1.m[0][2] * matrix2.m[2][0];
	result.m[0][1] = matrix1.m[0][0] * matrix2.m[0][1] + matrix1.m[0][1] * matrix2.m[1][1] + matrix1.m[0][2] * matrix2.m[2][1];
	result.m[0][2] = matrix1.m[0][0] * matrix2.m[0][2] + matrix1.m[0][1] * matrix2.m[1][2] + matrix1.m[0][2] * matrix2.m[2][2];
	result.m[1][0] = matrix1.m[1][0] * matrix2.m[0][0] + matrix1.m[1][1] * matrix2.m[1][0] + matrix1.m[1][2] * matrix2.m[2][0];
	result.m[1][1] = matrix1.m[1][0] * matrix2.m[0][1] + matrix1.m[1][1] * matrix2.m[1][1] + matrix1.m[1][2] * matrix2.m[2][1];
	result.m[1][2] = matrix1.m[1][0] * matrix2.m[0][2] + matrix1.m[1][1] * matrix2.m[1][2] + matrix1.m[1][2] * matrix2.m[2][2];
	result.m[2][0] = matrix1.m[2][0] * matrix2.m[0][0] + matrix1.m[2][1] * matrix2.m[1][0] + matrix1.m[2][2] * matrix2.m[2][0];
	result.m[2][1] = matrix1.m[2][0] * matrix2.m[0][1] + matrix1.m[2][1] * matrix2.m[1][1] + matrix1.m[2][2] * matrix2.m[2][1];
	result.m[2][2] = matrix1.m[2][0] * matrix2.m[0][2] + matrix1.m[2][1] * matrix2.m[1][2] + matrix1.m[2][2] * matrix2.m[2][2];


	return Matrix3x3(result);
}

Vector2 MultiplyVec2(Vector2 pos, Matrix3x3 matrix2)
{
	Vector2 result{};
	result.x = pos.x * matrix2.m[0][0] + pos.y * matrix2.m[1][0]+ matrix2.m[2][0];
	result.y = pos.x * matrix2.m[0][1] + pos.y * matrix2.m[1][1]+ matrix2.m[2][1];

	return result;
}

Matrix3x3 MakeRotateMatrix(float theta)
{
	Matrix3x3 rotate{};
	rotate.m[0][0] = cosf(theta);
	rotate.m[0][1] = sinf(theta);
	rotate.m[1][0] = -sinf(theta);
	rotate.m[1][1] = cosf(theta);
	rotate.m[2][2] = 1.0f;
	return Matrix3x3(rotate);
}

Matrix3x3 MakeScaleMatrix(Vector2 scale)
{
	Matrix3x3 result{};
	result.m[0][0] = scale.x;
	result.m[1][1] = scale.y;
	result.m[2][2] = 1;
	return Matrix3x3(result);
}
//Matrix3x3 MaketranslateMatrix(Vector2 translate)
//{
//
//	Matrix3x3 A{};
//	A.m[0][0] = 1.0f;
//	A.m[1][1] = 1.0f;
//	A.m[2][2] = 1.0f;
//	A.m[2][0] = translate.x;
//	A.m[2][1] = translate.y;
//	return Matrix3x3(A);
//}
//
//Vector2 Transform(Vector2 vector, Matrix3x3 matrix)
//{
//	Vector2 result;
//	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
//	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];
//	float w = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];
//
//	assert(w != 0.0f);
//	result.x /= w;
//	result.y /= w;
//	return result;
//}
