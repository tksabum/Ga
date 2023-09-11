#include <Windows.h>
#include <Windowsx.h>

#include <stdio.h> //sprintf ����� ���ؼ� ���

//#include <gdiplus.h>
//#pragma comment(lib, "gdiplus")
//using namespace Gdiplus;

#include "fmod_lowlevel/inc/fmod.h"

#include "GDIEngine.h"
#include "TimeControl.h"
#include "Scene.h"
#include "MainScene.h"
#include "GameScene.h"
#include "SettingScene.h"
#include "Input.h"
#include "SoundPlayer.h"

#include "IntroScene.h"
#include "LivingRoomScene.h"
#include "FirstInnerRoomScene.h"
#include "SecondInnerRoomScene.h"
#include "MirrorRoomScene.h"
#include "GameOverScene.h"
#include "EndingScene.h"

///
/// ���� 1.
/// ���� �⺻���� ������ Windows ���α׷� (�����ڵ� ����)
/// WinMain ����Ʈ
/// 2022.11.09 ��������� �����

// ���漱��
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int isDrawedFirstRender = 1;

/// <summary>
/// Win32API�� �̿��� ����ũ�� ���ø����̼�
/// ���α׷��� ��Ʈ�� ����Ʈ
/// </summary>
/// <param name="hInstance">�ν��Ͻ��� �ڵ�</param>
/// <param name="hPrevInstance">���� �ν��Ͻ��� �ڵ�(Win16�� ����)</param>
/// <param name="lpCmdLine">����� ����</param>
/// <param name="nCmdShow">����� ����</param>
/// <returns></returns>
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	// ���� �� �����츦 ���
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc; // ���ν���
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"COLORZZLEWIN32E";
	wcex.hIconSm = NULL;

	RegisterClassExW(&wcex);

	// �� �����츦 ����
	HWND hWnd = CreateWindowW(L"COLORZZLEWIN32E", L"[ʫ]", WS_OVERLAPPED | WS_SYSMENU,
		0, 0, 1600, 938, NULL, NULL, hInstance, NULL);

	// ������ �ڵ��� ���� �߿�
	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// ���ѷ��� (�ȿ� �޽��� ������ ���� ���� ���� ���Ե�)
	MSG msg;

	// �׷��Ƚ� ������ �ʱ�ȭ�Ѵ�.
	GDI_Initialize(hWnd);

	// SoundPlayer�� ����ϱ� ���� �غ�, �ݵ�� Scene_Ready ������ �ؾ��Ѵ�.
	SoundPlayer_Ready();

	// mainScene ����
	MainScene_Ready(hWnd);
	GameScene_Ready();
	SettingScene_Ready();
	MirrorRoomScene_Ready();
	FirstInnerRoomScene_Ready();
	SecondInnerRoomScene_Ready();
	LivingRoomScene_Ready();
	GameOverScene_Ready();
	IntroScene_Ready();
	EndingScene_Ready();

	// Scene�� �ʱ�ȭ �Ѵ�. �ݵ�� ��� ���� Ready�� ����� �� ����ؾ��Ѵ�.
    Scene_Ready();

	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;
			DispatchMessage(&msg);
		}
		else
		{
			// �޽��� ó�� ���� ���� ���� �� (�ð��� ���� ��)
			// ���� ���������� �Ѵ�.
			/// ���� ���� ��ü
			if (TimeControl_UpdateTime() == 1)
			{
				isDrawedFirstRender = 0;

				// Ű �Է� �ޱ�
				// �� ������ ���� ����� ��� Ű�� ������ ������Ʈ�Ѵ�. (Ű �Է��� ������ �޽����� ���� �����߱� ������ ������ ����)
				//input_update();

				// ���� �������� �ִ� scene�� update, render�� ȣ��
				Scene_Update(TimeControl_DeltaTime());
				Scene_Render();

				// �� �������� ���� ��, ���콺�� �Է� ���¸� �ʱ�ȭ�Ѵ�.
				Input_Init();
			}
		}
	}

	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	HDC hMemDC;
	HBITMAP hImage, hOldBitmap;
	int bx, by;
	BITMAP bit;

	switch (message)
	{
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		hMemDC = CreateCompatibleDC(hdc); // �޸� DC�� �����

		// ��Ʈ�� �Ӽ����� ������ �ҷ����� HBITMAP���� ����ȯ�ؼ� hImage�� �����Ѵ�
		// fuLoad �Ӽ�: ���ҽ� ��� ���ϸ�����, ȣȯ ��Ʈ���� �ƴ� DIB ���� ��Ʈ������ �ҷ��´�
		if (isDrawedFirstRender == 1)
		{
			hImage = (HBITMAP)LoadImage(NULL, TEXT("images/blackscreen.bmp"),
				IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		}
		else
		{
			hImage = (HBITMAP)LoadImage(NULL, TEXT("images/HelpMe.bmp"),
				IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		}

		// hImage�� ���õǱ� ���� �ڵ��� ������ �д�
		hOldBitmap = (HBITMAP)SelectObject(hMemDC, hImage);

		// ��Ʈ�� ������ �˾Ƴ���
		GetObject(hImage, sizeof(BITMAP), &bit);
		bx = bit.bmWidth;
		by = bit.bmHeight;

		// ȭ���� (0, 0) ��ġ�� ���� ũ��� ������ (0, 0) ��ġ���� �����Ͽ� �׸���
		BitBlt(hdc, 0, 0, bx, by, hMemDC, 0, 0, SRCCOPY);

		SelectObject(hMemDC, hOldBitmap); // hImage ������ �����ϱ� ���� hOldBitmap�� �����Ѵ�
		DeleteObject(hImage); // ���� ������ ��Ʈ���� �����Ѵ�

		DeleteDC(hMemDC); // �޸� DC�� �����Ѵ�
		EndPaint(hWnd, &ps);
		return 0;
	}
	break;


	case WM_LBUTTONUP:
	{
		POINT inputPoint;

		inputPoint.x = GET_X_LPARAM(lParam);
		inputPoint.y = GET_Y_LPARAM(lParam);

		Input_SetMouseLeftUp(inputPoint.x,inputPoint.y);
	}

	break;

	case WM_LBUTTONDOWN:
	{
		POINT inputPoint;

		inputPoint.x = GET_X_LPARAM(lParam);
		inputPoint.y = GET_Y_LPARAM(lParam);

		Input_SetMouseLeftDown(inputPoint.x, inputPoint.y);
	}

	break;

	case WM_RBUTTONUP:
	{
		POINT inputPoint;

		inputPoint.x = GET_X_LPARAM(lParam);
		inputPoint.y = GET_Y_LPARAM(lParam);

		Input_SetMouseRightUp(inputPoint.x, inputPoint.y);
	}

	break;

	case WM_RBUTTONDOWN:
	{
		POINT inputPoint;

		inputPoint.x = GET_X_LPARAM(lParam);
		inputPoint.y = GET_Y_LPARAM(lParam);

		Input_SetMouseRightDown(inputPoint.x, inputPoint.y);
	}

	break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}