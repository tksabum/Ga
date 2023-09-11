#include "GDIEngine.h"
#pragma comment(lib, "msimg32.lib")		

// ��� ������ �� ���� ����

PAINTSTRUCT ps;
HDC hdc, MemDC;
HBITMAP BackBit, oldBackBit;
RECT bufferRT;
HWND hWnd;

HDC hMemDC;
HBITMAP hImage, hOldBitmap;
BITMAP bit;
int bx, by;

const int FONT_SIZE = 20;
const COLORREF FONT_COLOR = RGB(255, 255, 255);

// �׸��� �׸� ��� DC
HDC hScreenDC = NULL;

/// <summary>
/// GDI�� �̿��� 2D �׷��Ƚ� ������ �ʱ�ȭ�Ѵ�.
/// </summary>
/// <param name="hWnd">�׷��Ƚ� ������ ����� ����� �Ǵ� ������ �ڵ�</param>
void GDI_Initialize(HWND _hWnd)
{
	hScreenDC = GetDC(_hWnd);
	hWnd = _hWnd;
}

void GDI_DrawBitmap(HDC hBitmapDC, int dstX, int dstY, int sizeX, int sizeY)
{
	BitBlt(hScreenDC, dstX, dstY, sizeX, sizeY, hBitmapDC, 0, 0, SRCCOPY);
}

HDC LoadBitmapFromFile(LPCWSTR filePath)
{
	BITMAP bit;

	HDC hBitmapDC = CreateCompatibleDC(hScreenDC);
	HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, filePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	SelectObject(hBitmapDC, hBitmap);

	// ��Ʈ�� ������ ����
	DeleteObject(hBitmap);

	return hBitmapDC;
}

// �׸��� �غ�, ������۸��� ���� memDC�� �����.
void GDIEngine_BeginPaint()
{
	MemDC = GetDC(hWnd);
	GetClientRect(hWnd, &bufferRT);
	hdc = CreateCompatibleDC(MemDC);
	BackBit = CreateCompatibleBitmap(MemDC, bufferRT.right, bufferRT.bottom);
	oldBackBit = (HBITMAP)SelectObject(hdc, BackBit);
	PatBlt(hdc, 0, 0, bufferRT.right, bufferRT.bottom, WHITENESS);
}

// �̹��������� ��� �׸��⸦ ������ ȭ�鿡 ����� �� memDC�� �����Ѵ�.
void GDIEngine_EndPaint()
{
	GetClientRect(hWnd, &bufferRT);
	BitBlt(MemDC, 0, 0, bufferRT.right, bufferRT.bottom, hdc, 0, 0, SRCCOPY);
	SelectObject(hdc, oldBackBit);
	DeleteObject(BackBit);
	DeleteDC(hdc);
	ReleaseDC(hWnd, MemDC);
}

void GDIEngine_Rectangle(int posX, int posY, int sizeX, int sizeY)
{
	Rectangle(hdc, posX, posY, posX + sizeX, posY + sizeY);
}

/// <summary>
/// GDI�� �̿��ؼ�, �������� ������ �մ� ������ �ϳ� �׸���.
/// </summary>
void GDIEngine_DrawLine(int x1, int y1, int x2, int y2)
{
	// Ŀ���� Ư�� �������� �̵��Ѵ�.
	MoveToEx(hdc, x1, y1, NULL);

	// �װ��������� Ư�� �������� ���� �����.
	LineTo(hdc, x2, y2);
}

// �׳� �̹��� (��� ���� �ܵ� �̹���) ��¿�
void GDIEngine_PrintImage(LPCWSTR filePath, int posX, int posY)	// �߶󳻱�
{
	hMemDC = CreateCompatibleDC(hdc); // �޸� DC�� �����

	hImage = (HBITMAP)LoadImage(NULL, filePath,
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hImage);

	// ��Ʈ�� ������ �˾Ƴ���
	GetObject(hImage, sizeof(BITMAP), &bit);
	bx = bit.bmWidth;
	by = bit.bmHeight;

	BitBlt(hdc, posX, posY, bx, by, hMemDC, 0, 0, SRCCOPY);

	//// �̹����� ������ ���� �ְ� �ѹ��� ������ ĳ����(60, 200)�� �׸��� 
	//TransparentBlt(hdc, 650, 50, (bx / 4) * 1, (by / 4) * 1,
	//	hMemDC, 60, 200, bx / 4, by / 4, RGB(255, 0, 255));

	SelectObject(hMemDC, hOldBitmap); // hImage ������ �����ϱ� ���� hOldBitmap�� �����Ѵ�
	DeleteObject(hImage); // ���� ������ ��Ʈ���� �����Ѵ�

	DeleteDC(hMemDC); // �޸� DC�� �����Ѵ�
}

// ��� ���� �̹���(PNG) ��¿�
void GDIEngine_PrintTransImage(LPCWSTR filePath, int posX, int posY)	// ����
{
	hMemDC = CreateCompatibleDC(hdc); // �޸� DC�� �����

	hImage = (HBITMAP)LoadImage(NULL, filePath,
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hImage);

	// ��Ʈ�� ������ �˾Ƴ���
	GetObject(hImage, sizeof(BITMAP), &bit);
	bx = bit.bmWidth;
	by = bit.bmHeight;

	// RGB(255, 0, 255)(��ũ��)�� �����ϰ� ����� �׸��� //msimg32.lib
	// 350, 50 ������ X,Y ��ǥ
	TransparentBlt(hdc, posX, posY, bx, by, hMemDC, 0, 0, bx, by, RGB(255, 0, 255));

	//// �̹����� ������ ���� �ְ� �ѹ��� ������ ĳ����(60, 200)�� �׸��� 
	//TransparentBlt(hdc, 650, 50, (bx / 4) * 1, (by / 4) * 1,
	//	hMemDC, 60, 200, bx / 4, by / 4, RGB(255, 0, 255));

	SelectObject(hMemDC, hOldBitmap); // hImage ������ �����ϱ� ���� hOldBitmap�� �����Ѵ�
	DeleteObject(hImage); // ���� ������ ��Ʈ���� �����Ѵ�

	DeleteDC(hMemDC); // �޸� DC�� �����Ѵ�
}

// �ִϸ��̼ǿ� 
// ���ӵǴ� �̹��� Ŀ���ؼ� �̾������� ��
// ���� �Լ��� ���� ���̶� �� ��ü�� �Ű� �Ƚᵵ��
void GDIEngine_PrintCutImage(LPCWSTR filePath, int posX, int posY, int cutX, int cutY, int imgX, int imgY, Vector2D scalePivot, float scale)	// �߶󳻱�
{
	hMemDC = CreateCompatibleDC(hdc); // �޸� DC�� �����

	hImage = (HBITMAP)LoadImage(NULL, filePath,
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hImage);

	// ��Ʈ�� ������ �˾Ƴ���
	GetObject(hImage, sizeof(BITMAP), &bit);
	bx = bit.bmWidth;
	by = bit.bmHeight;

	int imageSizeX = (bx / cutX);
	int imageSizeY = (by / cutY);

	// �̹����� ������ ���� �ְ� �ѹ��� ������ ĳ����(60, 200)�� �׸��� 
	TransparentBlt(hdc, posX + (1 - scale) * scalePivot.x, posY + (1 - scale) * scalePivot.y, imageSizeX * scale, imageSizeY * scale,	//cutX �����Ұ��� bx/cutX �ϵ�� �ʺ�
		hMemDC, imgX, imgY, bx / cutX, by / cutY, RGB(255, 0, 255));

	SelectObject(hMemDC, hOldBitmap); // hImage ������ �����ϱ� ���� hOldBitmap�� �����Ѵ�
	DeleteObject(hImage); // ���� ������ ��Ʈ���� �����Ѵ�

	DeleteDC(hMemDC); // �޸� DC�� �����Ѵ�
}

void GDIEngine_PrintAlphaImage(LPCWSTR filePath, int posX, int posY, int cutX, int cutY, int imgX, int imgY, BLENDFUNCTION bf, Vector2D scalePivot, float scale)
{
	hMemDC = CreateCompatibleDC(hdc); // �޸� DC�� �����

	hImage = (HBITMAP)LoadImage(NULL, filePath,
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hImage);

	// ��Ʈ�� ������ �˾Ƴ���
	GetObject(hImage, sizeof(BITMAP), &bit);
	bx = bit.bmWidth;
	by = bit.bmHeight;

	int imageSizeX = (bx / cutX);
	int imageSizeY = (by / cutY);

	AlphaBlend(hdc, posX + (1 - scale) * scalePivot.x, posY + (1 - scale) * scalePivot.y, imageSizeX * scale, imageSizeY * scale,
		hMemDC, imgX, imgY, bx / cutX, by / cutY, bf);

	SelectObject(hMemDC, hOldBitmap); // hImage ������ �����ϱ� ���� hOldBitmap�� �����Ѵ�
	DeleteObject(hImage); // ���� ������ ��Ʈ���� �����Ѵ�

	DeleteDC(hMemDC); // �޸� DC�� �����Ѵ�
}

// ������ ���� PRINTCUTIMAGE�Լ��� ���ӿ�����Ʈ �ִϸ��̼� ��¿�
void GDIEngine_PrintObject(GameObject gameobject)
{
	if (gameobject.printType & TYPE_RECTANGLE)
	{
		GDIEngine_Rectangle(gameobject.position.x, gameobject.position.y, gameobject.size.x, gameobject.size.y);
	}

	if ((gameobject.printType & TYPE_TRANSPARENT) > 0)
	{
		GDIEngine_PrintCutImage(gameobject.imagePath,
			gameobject.imagePos.x, gameobject.imagePos.y, gameobject.Xdivision, gameobject.Ydivision,
			gameobject.size.x * gameobject.imageNumber, 0, gameobject.scalePivot, gameobject.scale);
	}

	if ((gameobject.printType & TYPE_ALPHABLEND) > 0)
	{
		GDIEngine_PrintAlphaImage(gameobject.imagePath,
			gameobject.imagePos.x, gameobject.imagePos.y, gameobject.Xdivision, gameobject.Ydivision,
			gameobject.size.x * gameobject.imageNumber, 0, gameobject.blendFunction, gameobject.scalePivot, gameobject.scale);
	}

	if ((gameobject.printType & TYPE_TEXT) > 0)
	{
		GDIEngine_PrintObjectText(gameobject);
	}
}

// ���ӿ�����Ʈ �ؽ�Ʈ ����Լ��� ���� ���� �Լ� 
// ��� �Ű� �Ƚᵵ��
void GDIEngine_PrintText(LPCWSTR str, RECT rt)
{
	HFONT hFont = CreateFont(FONT_SIZE, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("�ü�"));
	HFONT oldFont = (HFONT)SelectObject(hdc, hFont);

	SetTextColor(hdc, FONT_COLOR);
	SetBkMode(hdc, TRANSPARENT);
	DrawText(hdc, str, -1, &rt, DT_CENTER | DT_WORDBREAK| DT_VCENTER);

	SelectObject(hdc, oldFont);
	DeleteObject(hFont);
}

// ���ӿ�����Ʈ �ؽ�Ʈ ����Լ�
void GDIEngine_PrintObjectText(GameObject gameobject)
{
	gameobject._textBox.left = gameobject.textBoxPos.x + gameobject.position.x;
	gameobject._textBox.right = gameobject.textBoxPos.x + gameobject.position.x + gameobject.textBoxSize.x;
	gameobject._textBox.bottom = gameobject.textBoxPos.y + gameobject.position.y + gameobject.textBoxSize.y;
	gameobject._textBox.top = gameobject.textBoxPos.y + gameobject.position.y;

	GDIEngine_PrintText(gameobject.text, gameobject._textBox);
}