#pragma once
#include "struct.h"
#include <Novice.h>

static const int kRowHeight = 20;
static const int kColumWidth = 54;

void MatrixScreenPrintf(int x, int y, Matrix3x3 matrix);

//Matrix3x3 MakeTranslateMatrix(Vector2 translate);
Matrix3x3 MakeAffineMatrix(Vector2 scale, float theta, Vector2 translate);


Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2);
Vector2 MultiplyVec2(Vector2 pos, Matrix3x3 matrix2);

Matrix3x3 MakeRotateMatrix(float theta);

Matrix3x3 MakeScaleMatrix(Vector2 scale);


//Matrix3x3 MaketranslateMatrix(Vector2 translate);

Vector2 Transform(Vector2 vector, Matrix3x3 matrix);

Matrix3x3 InverseMatrix(Matrix3x3 matrix);

Matrix3x3 MaketranslateMatrix(Vector2 translate);

Vector2 Transform(Vector2 vector, Matrix3x3 matrix);

Matrix3x3 Transpose(Matrix3x3 matrix);

Matrix3x3 MakeOrthographicMatrix(float left, float top, float right, float bottom);

Matrix3x3 MakeViewportMatrix(float left, float top, float width, float height);

void MakeVertexTransform(Vertex lorcal,Vertex &vertex, Matrix3x3 matrix);

