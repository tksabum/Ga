#pragma once

#include <windows.h>
#include "GameObject.h"

// GDI를 사용한 그래픽스 엔진을 초기화 한다.
// 필요한 것은 hWnd
void GDI_Initialize(HWND hWnd);

// 비트맵을 그린다.
void GDI_DrawBitmap(HDC hBitmapDC, int dstX, int dstY, int sizeX, int sizeY);

HDC LoadBitmapFromFile(LPCWSTR filePath);


// 그리기 준비, 더블버퍼링을 위해 memDC를 만든다.
void GDIEngine_BeginPaint();

// 이번프레임의 모든 그리기를 끝내고 화면에 출력한 후 memDC를 제거한다.
void GDIEngine_EndPaint();

void GDIEngine_Rectangle(int posX, int posY, int sizeX, int sizeY);

void GDIEngine_DrawLine(int leftupX, int leftupY, int rightdownX, int rightdownY);

void GDIEngine_PrintObject(GameObject gameobject);

void GDIEngine_PrintObjectText(GameObject gameobject);

void GDIEngine_PrintText(LPCWSTR str, RECT rt);

/*
* 현재 모든 함수들이 자기 그릴것만 하나씩 화면에 그리는 중
* 더블 버퍼링을 사용하기 위해 memDC를 생성하고 그위에 그림을 그린 후
* 최종적으로 그려진 그림을 화면에 출력해야한다.
*/