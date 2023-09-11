#pragma once

#include <windows.h>
#include "GameObject.h"

// GDI�� ����� �׷��Ƚ� ������ �ʱ�ȭ �Ѵ�.
// �ʿ��� ���� hWnd
void GDI_Initialize(HWND hWnd);

// ��Ʈ���� �׸���.
void GDI_DrawBitmap(HDC hBitmapDC, int dstX, int dstY, int sizeX, int sizeY);

HDC LoadBitmapFromFile(LPCWSTR filePath);


// �׸��� �غ�, ������۸��� ���� memDC�� �����.
void GDIEngine_BeginPaint();

// �̹��������� ��� �׸��⸦ ������ ȭ�鿡 ����� �� memDC�� �����Ѵ�.
void GDIEngine_EndPaint();

void GDIEngine_Rectangle(int posX, int posY, int sizeX, int sizeY);

void GDIEngine_DrawLine(int leftupX, int leftupY, int rightdownX, int rightdownY);

void GDIEngine_PrintObject(GameObject gameobject);

void GDIEngine_PrintObjectText(GameObject gameobject);

void GDIEngine_PrintText(LPCWSTR str, RECT rt);

/*
* ���� ��� �Լ����� �ڱ� �׸��͸� �ϳ��� ȭ�鿡 �׸��� ��
* ���� ���۸��� ����ϱ� ���� memDC�� �����ϰ� ������ �׸��� �׸� ��
* ���������� �׷��� �׸��� ȭ�鿡 ����ؾ��Ѵ�.
*/