#pragma once
#include <windows.h>
#include "Vector2D.h"

#define LAYER_BACKGROUND 0
#define LAYER_BOTTOM 1
#define LAYER_MID 2
#define LAYER_TOP 3
#define LAYER_SIZE 4

#define TYPE_BASE 0x0000		// ������� ����
#define TYPE_RECTANGLE 0x0001	// �簢�� ���
#define TYPE_TEXT 0x0002		// �ؽ�Ʈ ���
#define TYPE_TRANSPARENT 0x0004	// �Ϲ����� �̹��� ���
#define TYPE_ALPHABLEND 0x0008	// ������ �̹��� ���

// ���������� ���� �ؾ��ϴ� �ʱ�ȭ
// blendFunction.BlendOp = 0;
// blendFunction.BlendFlags = 0;
// blendFunction.AlphaFormat = 0;
//
// ���� ����
// blendFunction.SourceConstantAlpha = (������); (0 ~ 255)

typedef struct _GameObject
{
	Vector2D position;
	Vector2D size;

	int isVisible;
	int layer;

	unsigned int printType;
	LPCWSTR imagePath;
	int Xdivision;
	int Ydivision;
	int imageNumber;	// �� ��° �̹���
	BLENDFUNCTION blendFunction;

	Vector2D imagePos;

	Vector2D scalePivot;
	float scale;

	LPCWSTR text;
	RECT _textBox;
	Vector2D textBoxPos;
	Vector2D textBoxSize;
	
	// �ʿ��ϸ� ���
	//Vector2D pivot;
	//float rotation
} GameObject;