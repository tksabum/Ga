#include "MainScene.h"
#include "GDIEngine.h"
#include "Scene.h"
#include "GameObject.h"
#include "Input.h"
#include "SoundPlayer.h"

#define MAINSCENE_GAMEOBJECT_ID_BACKGROUND 0
#define MAINSCENE_GAMEOBJECT_ID_STARTBUTTON 1 
#define MAINSCENE_GAMEOBJECT_ID_SETTINGBUTTON 2 
#define MAINSCENE_GAMEOBJECT_ID_QUITBUTTON 3 
#define MAINSCENE_GAMEOBJECT_ID_GABUTTON 4

#define MAINSCENE_GAMEOBJECT_SIZE 5

HWND hWnd;

Scene mainScene;

GameObject mainScene_object[MAINSCENE_GAMEOBJECT_SIZE];

int mainScene_lastMouseLeftDownObject;
int mainScene_lastMouseLeftUpObject;

//sceneList에 mainScene을 담고 mainScene의 함수 포인터들을 초기화(함수의 주소값을 담는다) 한다.
void MainScene_Ready(HWND hwnd)
{
	sceneList[SCENE_ID_MAIN] = &mainScene;
	mainScene.func_init = MainScene_Init;
	mainScene.func_update = MainScene_Update;
	mainScene.func_render = MainScene_Render;

	hWnd = hwnd;
}

//scene 전환이 됬을 때, 해당 scene의 초기화
void MainScene_Init()
{
	for (int i = 0; i < MAINSCENE_GAMEOBJECT_SIZE; i++)
	{
		mainScene_object[i].Xdivision = 1;
		mainScene_object[i].Ydivision = 1;
		mainScene_object[i].imageNumber = 0;
		mainScene_object[i].scalePivot.x = 0.0f;
		mainScene_object[i].scalePivot.y = 0.0f;
		mainScene_object[i].scale = 1.0f;
		mainScene_object[i].imagePos.x = 0;
		mainScene_object[i].imagePos.y = 0;
	}

	mainScene_object[MAINSCENE_GAMEOBJECT_ID_BACKGROUND].printType = TYPE_TRANSPARENT;
	mainScene_object[MAINSCENE_GAMEOBJECT_ID_BACKGROUND].position.x = 0;
	mainScene_object[MAINSCENE_GAMEOBJECT_ID_BACKGROUND].position.y = 0;
	mainScene_object[MAINSCENE_GAMEOBJECT_ID_BACKGROUND].size.x = 1600;
	mainScene_object[MAINSCENE_GAMEOBJECT_ID_BACKGROUND].size.y = 900;
	mainScene_object[MAINSCENE_GAMEOBJECT_ID_BACKGROUND].isVisible = 1;
	mainScene_object[MAINSCENE_GAMEOBJECT_ID_BACKGROUND].layer = LAYER_BACKGROUND;
	mainScene_object[MAINSCENE_GAMEOBJECT_ID_BACKGROUND].imagePath = TEXT("images/mainMenu.bmp");

	mainScene_object[MAINSCENE_GAMEOBJECT_ID_STARTBUTTON].printType = TYPE_BASE;
	mainScene_object[MAINSCENE_GAMEOBJECT_ID_STARTBUTTON].position.x = 139;
	mainScene_object[MAINSCENE_GAMEOBJECT_ID_STARTBUTTON].position.y = 743;
	mainScene_object[MAINSCENE_GAMEOBJECT_ID_STARTBUTTON].size.x = 205;
	mainScene_object[MAINSCENE_GAMEOBJECT_ID_STARTBUTTON].size.y = 90;
	mainScene_object[MAINSCENE_GAMEOBJECT_ID_STARTBUTTON].isVisible = 1;
	mainScene_object[MAINSCENE_GAMEOBJECT_ID_STARTBUTTON].text = TEXT("시작");
	mainScene_object[MAINSCENE_GAMEOBJECT_ID_STARTBUTTON].textBoxPos.x = 10;
	mainScene_object[MAINSCENE_GAMEOBJECT_ID_STARTBUTTON].textBoxPos.y = 10;
	mainScene_object[MAINSCENE_GAMEOBJECT_ID_STARTBUTTON].textBoxSize.x = 80;
	mainScene_object[MAINSCENE_GAMEOBJECT_ID_STARTBUTTON].textBoxSize.y = 30;
	mainScene_object[MAINSCENE_GAMEOBJECT_ID_STARTBUTTON].layer = LAYER_TOP;

	mainScene_object[MAINSCENE_GAMEOBJECT_ID_SETTINGBUTTON].printType = TYPE_BASE;
	mainScene_object[MAINSCENE_GAMEOBJECT_ID_SETTINGBUTTON].position.x = 714;
	mainScene_object[MAINSCENE_GAMEOBJECT_ID_SETTINGBUTTON].position.y = 750;
	mainScene_object[MAINSCENE_GAMEOBJECT_ID_SETTINGBUTTON].size.x = 205;
	mainScene_object[MAINSCENE_GAMEOBJECT_ID_SETTINGBUTTON].size.y = 90;
	mainScene_object[MAINSCENE_GAMEOBJECT_ID_SETTINGBUTTON].isVisible = 1;
	mainScene_object[MAINSCENE_GAMEOBJECT_ID_SETTINGBUTTON].text = TEXT("설정");
	mainScene_object[MAINSCENE_GAMEOBJECT_ID_SETTINGBUTTON].textBoxPos.x = 10;
	mainScene_object[MAINSCENE_GAMEOBJECT_ID_SETTINGBUTTON].textBoxPos.y = 10;
	mainScene_object[MAINSCENE_GAMEOBJECT_ID_SETTINGBUTTON].textBoxSize.x = 80;
	mainScene_object[MAINSCENE_GAMEOBJECT_ID_SETTINGBUTTON].textBoxSize.y = 30;
	mainScene_object[MAINSCENE_GAMEOBJECT_ID_SETTINGBUTTON].layer = LAYER_TOP;

	mainScene_object[MAINSCENE_GAMEOBJECT_ID_QUITBUTTON].printType = TYPE_BASE;
	mainScene_object[MAINSCENE_GAMEOBJECT_ID_QUITBUTTON].position.x = 1260;
	mainScene_object[MAINSCENE_GAMEOBJECT_ID_QUITBUTTON].position.y = 750;
	mainScene_object[MAINSCENE_GAMEOBJECT_ID_QUITBUTTON].size.x = 205;
	mainScene_object[MAINSCENE_GAMEOBJECT_ID_QUITBUTTON].size.y = 90;
	mainScene_object[MAINSCENE_GAMEOBJECT_ID_QUITBUTTON].isVisible = 1;
	mainScene_object[MAINSCENE_GAMEOBJECT_ID_QUITBUTTON].text = TEXT("종료");
	mainScene_object[MAINSCENE_GAMEOBJECT_ID_QUITBUTTON].textBoxPos.x = 10;
	mainScene_object[MAINSCENE_GAMEOBJECT_ID_QUITBUTTON].textBoxPos.y = 10;
	mainScene_object[MAINSCENE_GAMEOBJECT_ID_QUITBUTTON].textBoxSize.x = 80;
	mainScene_object[MAINSCENE_GAMEOBJECT_ID_QUITBUTTON].textBoxSize.y = 30;
	mainScene_object[MAINSCENE_GAMEOBJECT_ID_QUITBUTTON].layer = LAYER_TOP;

	mainScene_object[MAINSCENE_GAMEOBJECT_ID_GABUTTON].printType = TYPE_BASE;
	mainScene_object[MAINSCENE_GAMEOBJECT_ID_GABUTTON].position.x = 1250;
	mainScene_object[MAINSCENE_GAMEOBJECT_ID_GABUTTON].position.y = 80;
	mainScene_object[MAINSCENE_GAMEOBJECT_ID_GABUTTON].size.x = 250;
	mainScene_object[MAINSCENE_GAMEOBJECT_ID_GABUTTON].size.y = 320;
	mainScene_object[MAINSCENE_GAMEOBJECT_ID_GABUTTON].isVisible = 1;
	mainScene_object[MAINSCENE_GAMEOBJECT_ID_GABUTTON].layer = LAYER_TOP;

	SoundPlayer_Play(SOUND_BGM_MAINMENU);
}

//mainScene이 현재 scene인 경우 update를 진행한다.
void MainScene_Update(float deltaTime)
{
	// 마우스 왼쪽 버튼이 내려갔을 때
	if (Input_GetMouseLeftDownNow())
	{
		// 클릭한 위치를 저장한다.
		mainScene_lastMouseLeftDownObject = MainScene_ClickedObject(Input_GetMouseLeftDownPosition());
	}

	// 마우스 왼쪽 버튼이 올라올 때
	if (Input_GetMouseLeftUpNow())
	{
		// 클릭한 위치를 저장한다.
		mainScene_lastMouseLeftUpObject = MainScene_ClickedObject(Input_GetMouseLeftUpPosition());

		// 마우스가 특정 오브젝트를 클릭한 경우
		if (mainScene_lastMouseLeftUpObject != -1 && mainScene_lastMouseLeftDownObject == mainScene_lastMouseLeftUpObject)
		{
			// 오브젝트 클릭 이벤트를 진행
			if (mainScene_lastMouseLeftDownObject == MAINSCENE_GAMEOBJECT_ID_STARTBUTTON)
			{
				SoundPlayer_Play(SOUND_EFFECT_STARTGAME);

				Scene_ChangeScene(SCENE_ID_INTRO);
			}
			else if (mainScene_lastMouseLeftDownObject == MAINSCENE_GAMEOBJECT_ID_SETTINGBUTTON)
			{
				Scene_ChangeScene(SCENE_ID_SETTING);
			}
			else if (mainScene_lastMouseLeftDownObject == MAINSCENE_GAMEOBJECT_ID_QUITBUTTON)
			{
				DestroyWindow(hWnd);
			}
			else if (mainScene_lastMouseLeftDownObject == MAINSCENE_GAMEOBJECT_ID_GABUTTON)
			{
				Scene_ChangeScene(SCENE_ID_ENDING);
			}
		}
	}
}

void MainScene_Render()
{
	// isVisible : true면 화면을 출력, false면 비출력
	// layer : 0, 1, 2, 3순으로 화면을 출력
	for (int i = 0; i < LAYER_SIZE; i++)
	{
		for (int j = 0; j < MAINSCENE_GAMEOBJECT_SIZE; j++)
		{
			// layer와 isVisible에 대한 판단을 한다
			if (mainScene_object[j].isVisible == 1 && mainScene_object[j].layer == i)
			{
				GDIEngine_PrintObject(mainScene_object[j]);
			}
		}
	}
}

// mousePos 위치의 오브젝트의 번호(object 배열에서의 인덱스)를 반환한다.
// 만약 오브젝트가 클릭되지 않았다면 -1을 리턴한다.
int MainScene_ClickedObject(POINT mousePos)
{
	int result = -1;
	int maxLayer = -1;
	
	for (int i = 0; i < MAINSCENE_GAMEOBJECT_SIZE; i++)
	{
		int objVisible = mainScene_object[i].isVisible;
		int objPosX1 = mainScene_object[i].position.x;
		int objPosY1 = mainScene_object[i].position.y;
		int objPosX2 = mainScene_object[i].position.x + mainScene_object[i].size.x;
		int objPosY2 = mainScene_object[i].position.y + mainScene_object[i].size.y;

		// 넘겨받은 마우스의 좌표에 따라서 어떤 게임 오브젝트가 클릭 됬는지를 판단하여 리턴한다
		if (objVisible == 1 && objPosX1 < mousePos.x && mousePos.x < objPosX2 && objPosY1 < mousePos.y && mousePos.y < objPosY2)
		{
			if (maxLayer < mainScene_object[i].layer)
			{
				result = i;
				maxLayer = mainScene_object[i].layer;
			}
		}
	}

	return result;
}