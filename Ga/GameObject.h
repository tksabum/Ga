#pragma once
#include <windows.h>
#include "Vector2D.h"

#define LAYER_BACKGROUND 0
#define LAYER_BOTTOM 1
#define LAYER_MID 2
#define LAYER_TOP 3
#define LAYER_SIZE 4

#define TYPE_BASE 0x0000		// 출력하지 않음
#define TYPE_RECTANGLE 0x0001	// 사각형 출력
#define TYPE_TEXT 0x0002		// 텍스트 출력
#define TYPE_TRANSPARENT 0x0004	// 일반적인 이미지 출력
#define TYPE_ALPHABLEND 0x0008	// 투명한 이미지 출력

// 투명도설정을 위해 해야하는 초기화
// blendFunction.BlendOp = 0;
// blendFunction.BlendFlags = 0;
// blendFunction.AlphaFormat = 0;
//
// 투명도 설정
// blendFunction.SourceConstantAlpha = (투명도값); (0 ~ 255)

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
	int imageNumber;	// 몇 번째 이미지
	BLENDFUNCTION blendFunction;

	Vector2D imagePos;

	Vector2D scalePivot;
	float scale;

	LPCWSTR text;
	RECT _textBox;
	Vector2D textBoxPos;
	Vector2D textBoxSize;
	
	// 필요하면 사용
	//Vector2D pivot;
	//float rotation
} GameObject;