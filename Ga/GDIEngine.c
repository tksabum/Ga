#include "GDIEngine.h"
#pragma comment(lib, "msimg32.lib")		

// 모듈 내에서 쓸 전역 변수

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

// 그림을 그릴 대상 DC
HDC hScreenDC = NULL;

/// <summary>
/// GDI를 이용한 2D 그래픽스 엔진을 초기화한다.
/// </summary>
/// <param name="hWnd">그래픽스 엔지을 사용할 대상이 되는 윈도우 핸들</param>
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

	// 비트맵 정보를 삭제
	DeleteObject(hBitmap);

	return hBitmapDC;
}

// 그리기 준비, 더블버퍼링을 위해 memDC를 만든다.
void GDIEngine_BeginPaint()
{
	MemDC = GetDC(hWnd);
	GetClientRect(hWnd, &bufferRT);
	hdc = CreateCompatibleDC(MemDC);
	BackBit = CreateCompatibleBitmap(MemDC, bufferRT.right, bufferRT.bottom);
	oldBackBit = (HBITMAP)SelectObject(hdc, BackBit);
	PatBlt(hdc, 0, 0, bufferRT.right, bufferRT.bottom, WHITENESS);
}

// 이번프레임의 모든 그리기를 끝내고 화면에 출력한 후 memDC를 제거한다.
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
/// GDI를 이용해서, 시작점과 끝점을 잇는 선분을 하나 그린다.
/// </summary>
void GDIEngine_DrawLine(int x1, int y1, int x2, int y2)
{
	// 커서를 특정 지점으로 이동한다.
	MoveToEx(hdc, x1, y1, NULL);

	// 그곳에서부터 특정 지점까지 선을 만든다.
	LineTo(hdc, x2, y2);
}

// 그냥 이미지 (배경 없는 단독 이미지) 출력용
void GDIEngine_PrintImage(LPCWSTR filePath, int posX, int posY)	// 잘라내기
{
	hMemDC = CreateCompatibleDC(hdc); // 메모리 DC를 만든다

	hImage = (HBITMAP)LoadImage(NULL, filePath,
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hImage);

	// 비트맵 정보를 알아낸다
	GetObject(hImage, sizeof(BITMAP), &bit);
	bx = bit.bmWidth;
	by = bit.bmHeight;

	BitBlt(hdc, posX, posY, bx, by, hMemDC, 0, 0, SRCCOPY);

	//// 이번에는 왼쪽을 보고 있고 한발을 내딛은 캐릭터(60, 200)를 그린다 
	//TransparentBlt(hdc, 650, 50, (bx / 4) * 1, (by / 4) * 1,
	//	hMemDC, 60, 200, bx / 4, by / 4, RGB(255, 0, 255));

	SelectObject(hMemDC, hOldBitmap); // hImage 선택을 해제하기 위해 hOldBitmap을 선택한다
	DeleteObject(hImage); // 선택 해제된 비트맵을 제거한다

	DeleteDC(hMemDC); // 메모리 DC를 제거한다
}

// 배경 투명 이미지(PNG) 출력용
void GDIEngine_PrintTransImage(LPCWSTR filePath, int posX, int posY)	// 투명
{
	hMemDC = CreateCompatibleDC(hdc); // 메모리 DC를 만든다

	hImage = (HBITMAP)LoadImage(NULL, filePath,
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hImage);

	// 비트맵 정보를 알아낸다
	GetObject(hImage, sizeof(BITMAP), &bit);
	bx = bit.bmWidth;
	by = bit.bmHeight;

	// RGB(255, 0, 255)(핑크색)을 투명하게 만들고 그린다 //msimg32.lib
	// 350, 50 시작점 X,Y 좌표
	TransparentBlt(hdc, posX, posY, bx, by, hMemDC, 0, 0, bx, by, RGB(255, 0, 255));

	//// 이번에는 왼쪽을 보고 있고 한발을 내딛은 캐릭터(60, 200)를 그린다 
	//TransparentBlt(hdc, 650, 50, (bx / 4) * 1, (by / 4) * 1,
	//	hMemDC, 60, 200, bx / 4, by / 4, RGB(255, 0, 255));

	SelectObject(hMemDC, hOldBitmap); // hImage 선택을 해제하기 위해 hOldBitmap을 선택한다
	DeleteObject(hImage); // 선택 해제된 비트맵을 제거한다

	DeleteDC(hMemDC); // 메모리 DC를 제거한다
}

// 애니메이션용 
// 연속되는 이미지 커팅해서 이어지도록 함
// 밑의 함수를 위한 아이라 얘 자체는 신경 안써도됨
void GDIEngine_PrintCutImage(LPCWSTR filePath, int posX, int posY, int cutX, int cutY, int imgX, int imgY, Vector2D scalePivot, float scale)	// 잘라내기
{
	hMemDC = CreateCompatibleDC(hdc); // 메모리 DC를 만든다

	hImage = (HBITMAP)LoadImage(NULL, filePath,
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hImage);

	// 비트맵 정보를 알아낸다
	GetObject(hImage, sizeof(BITMAP), &bit);
	bx = bit.bmWidth;
	by = bit.bmHeight;

	int imageSizeX = (bx / cutX);
	int imageSizeY = (by / cutY);

	// 이번에는 왼쪽을 보고 있고 한발을 내딛은 캐릭터(60, 200)를 그린다 
	TransparentBlt(hdc, posX + (1 - scale) * scalePivot.x, posY + (1 - scale) * scalePivot.y, imageSizeX * scale, imageSizeY * scale,	//cutX 몇등분할건지 bx/cutX 일등분 너비
		hMemDC, imgX, imgY, bx / cutX, by / cutY, RGB(255, 0, 255));

	SelectObject(hMemDC, hOldBitmap); // hImage 선택을 해제하기 위해 hOldBitmap을 선택한다
	DeleteObject(hImage); // 선택 해제된 비트맵을 제거한다

	DeleteDC(hMemDC); // 메모리 DC를 제거한다
}

void GDIEngine_PrintAlphaImage(LPCWSTR filePath, int posX, int posY, int cutX, int cutY, int imgX, int imgY, BLENDFUNCTION bf, Vector2D scalePivot, float scale)
{
	hMemDC = CreateCompatibleDC(hdc); // 메모리 DC를 만든다

	hImage = (HBITMAP)LoadImage(NULL, filePath,
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hImage);

	// 비트맵 정보를 알아낸다
	GetObject(hImage, sizeof(BITMAP), &bit);
	bx = bit.bmWidth;
	by = bit.bmHeight;

	int imageSizeX = (bx / cutX);
	int imageSizeY = (by / cutY);

	AlphaBlend(hdc, posX + (1 - scale) * scalePivot.x, posY + (1 - scale) * scalePivot.y, imageSizeX * scale, imageSizeY * scale,
		hMemDC, imgX, imgY, bx / cutX, by / cutY, bf);

	SelectObject(hMemDC, hOldBitmap); // hImage 선택을 해제하기 위해 hOldBitmap을 선택한다
	DeleteObject(hImage); // 선택 해제된 비트맵을 제거한다

	DeleteDC(hMemDC); // 메모리 DC를 제거한다
}

// 위에서 만든 PRINTCUTIMAGE함수로 게임오브젝트 애니메이션 출력용
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

// 게임오브젝트 텍스트 출력함수를 위해 만든 함수 
// 얘는 신경 안써도됨
void GDIEngine_PrintText(LPCWSTR str, RECT rt)
{
	HFONT hFont = CreateFont(FONT_SIZE, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("궁서"));
	HFONT oldFont = (HFONT)SelectObject(hdc, hFont);

	SetTextColor(hdc, FONT_COLOR);
	SetBkMode(hdc, TRANSPARENT);
	DrawText(hdc, str, -1, &rt, DT_CENTER | DT_WORDBREAK| DT_VCENTER);

	SelectObject(hdc, oldFont);
	DeleteObject(hFont);
}

// 게임오브젝트 텍스트 출력함수
void GDIEngine_PrintObjectText(GameObject gameobject)
{
	gameobject._textBox.left = gameobject.textBoxPos.x + gameobject.position.x;
	gameobject._textBox.right = gameobject.textBoxPos.x + gameobject.position.x + gameobject.textBoxSize.x;
	gameobject._textBox.bottom = gameobject.textBoxPos.y + gameobject.position.y + gameobject.textBoxSize.y;
	gameobject._textBox.top = gameobject.textBoxPos.y + gameobject.position.y;

	GDIEngine_PrintText(gameobject.text, gameobject._textBox);
}