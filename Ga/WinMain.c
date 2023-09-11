#include <Windows.h>
#include <Windowsx.h>

#include <stdio.h> //sprintf 사용을 위해서 사용

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
/// 예제 1.
/// 가장 기본적인 형태의 Windows 프로그램 (유니코드 버전)
/// WinMain 디폴트
/// 2022.11.09 게임인재원 김범준

// 전방선언
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int isDrawedFirstRender = 1;

/// <summary>
/// Win32API를 이용한 데스크톱 어플리케이션
/// 프로그램의 엔트리 포인트
/// </summary>
/// <param name="hInstance">인스턴스의 핸들</param>
/// <param name="hPrevInstance">이전 인스턴스의 핸들(Win16의 잔재)</param>
/// <param name="lpCmdLine">실행시 인자</param>
/// <param name="nCmdShow">실행시 인자</param>
/// <returns></returns>
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	// 내가 쓸 윈도우를 등록
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc; // 프로시저
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

	// 그 윈도우를 생성
	HWND hWnd = CreateWindowW(L"COLORZZLEWIN32E", L"[家]", WS_OVERLAPPED | WS_SYSMENU,
		0, 0, 1600, 938, NULL, NULL, hInstance, NULL);

	// 윈도우 핸들이 가장 중요
	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// 무한루프 (안에 메시지 루프와 게임 루프 등이 포함됨)
	MSG msg;

	// 그래픽스 엔진을 초기화한다.
	GDI_Initialize(hWnd);

	// SoundPlayer를 사용하기 위한 준비, 반드시 Scene_Ready 이전에 해야한다.
	SoundPlayer_Ready();

	// mainScene 실행
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

	// Scene을 초기화 한다. 반드시 모든 씬의 Ready를 사용한 후 사용해야한다.
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
			// 메시지 처리 등을 하지 않을 때 (시간이 남을 때)
			// 뭔가 적극적으로 한다.
			/// 게임 루프 본체
			if (TimeControl_UpdateTime() == 1)
			{
				isDrawedFirstRender = 0;

				// 키 입력 받기
				// 매 프레임 마다 사용할 모든 키의 정보를 업데이트한다. (키 입력은 윈도우 메시지를 통해 구현했기 때문에 사용되지 않음)
				//input_update();

				// 현재 보여지고 있는 scene의 update, render를 호출
				Scene_Update(TimeControl_DeltaTime());
				Scene_Render();

				// 매 프레임이 끝날 때, 마우스의 입력 상태를 초기화한다.
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
		hMemDC = CreateCompatibleDC(hdc); // 메모리 DC를 만든다

		// 비트맵 속성으로 파일을 불러오고 HBITMAP으로 형변환해서 hImage에 저장한다
		// fuLoad 속성: 리소스 대신 파일명으로, 호환 비트맵이 아닌 DIB 섹션 비트맵으로 불러온다
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

		// hImage가 선택되기 전의 핸들을 저장해 둔다
		hOldBitmap = (HBITMAP)SelectObject(hMemDC, hImage);

		// 비트맵 정보를 알아낸다
		GetObject(hImage, sizeof(BITMAP), &bit);
		bx = bit.bmWidth;
		by = bit.bmHeight;

		// 화면의 (0, 0) 위치에 원본 크기로 원본의 (0, 0) 위치부터 추출하여 그린다
		BitBlt(hdc, 0, 0, bx, by, hMemDC, 0, 0, SRCCOPY);

		SelectObject(hMemDC, hOldBitmap); // hImage 선택을 해제하기 위해 hOldBitmap을 선택한다
		DeleteObject(hImage); // 선택 해제된 비트맵을 제거한다

		DeleteDC(hMemDC); // 메모리 DC를 제거한다
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