#include "SettingScene.h"
#include "GDIEngine.h"
#include "GameObject.h"
#include "Scene.h"
#include "Input.h"
#include "SoundPlayer.h"

#define SETTINGSCENE_GAMEOBJECT_ID_BACKGROUND 0
#define SETTINGSCENE_GAMEOBJECT_ID_BGMSOUNDBAR 1
#define SETTINGSCENE_GAMEOBJECT_ID_EFFECTSOUNDBAR 2
#define SETTINGSCENE_GAMEOBJECT_ID_MUTEBUTTON 3
#define SETTINGSCENE_GAMEOBJECT_ID_BGMSOUNDUPBUTTON 4
#define SETTINGSCENE_GAMEOBJECT_ID_BGMSOUNDDOWNBUTTON 5
#define SETTINGSCENE_GAMEOBJECT_ID_EFFECTSOUNDUPBUTTON 6
#define SETTINGSCENE_GAMEOBJECT_ID_EFFECTSOUNDDOWNBUTTON 7
#define SETTINGSCENE_GAMEOBJECT_ID_BACKBUTTON 8
#define SETTINGSCENE_GAMEOBJECT_ID_BGM_SQUARE 9
#define SETTINGSCENE_GAMEOBJECT_ID_EFFECT_SOUND_SQUARE 10

#define SETTINGSCENE_GAMEOBJECT_SIZE 11

Scene settingScene;

GameObject settingScene_object[SETTINGSCENE_GAMEOBJECT_SIZE];

int settingScene_lastMouseLeftDownObject;
int settingScene_lastMouseLeftUpObject;

// 490 ~ 1100
const int SETTING_SQUARE_LEFT_POS = 490;
const int SETTING_SQUARE_RIGHT_POS = 1100;

void SettingScene_Ready()
{
	sceneList[SCENE_ID_SETTING] = &settingScene;
	settingScene.func_init = SettingScene_Init;
	settingScene.func_update = SettingScene_Update;
	settingScene.func_render = SettingScene_Render;
}

void SettingScene_Init()
{
	// 모든 오브젝트의 X,Y division과 imageNumber 초기화
	for (int i = 0; i < SETTINGSCENE_GAMEOBJECT_SIZE; i++)
	{
		settingScene_object[i].Xdivision = 1;
		settingScene_object[i].Ydivision = 1;
		settingScene_object[i].imageNumber = 0;
		settingScene_object[i].scalePivot.x = 0.0f;
		settingScene_object[i].scalePivot.y = 0.0f;
		settingScene_object[i].scale = 1.0f;
		settingScene_object[i].imagePos.x = 0;
		settingScene_object[i].imagePos.y = 0;
	}

	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BACKGROUND].printType = TYPE_TRANSPARENT;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BACKGROUND].position.x = 0;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BACKGROUND].position.y = 0;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BACKGROUND].size.x = 1600;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BACKGROUND].size.y = 900;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BACKGROUND].isVisible = 1;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BACKGROUND].textBoxPos.x = 0;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BACKGROUND].textBoxPos.y = 0;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BACKGROUND].textBoxSize.x = 100;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BACKGROUND].textBoxSize.y = 100;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BACKGROUND].text = TEXT("");
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BACKGROUND].layer = LAYER_BACKGROUND;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BACKGROUND].imagePath = TEXT("images/환경설정창.bmp");


	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BGMSOUNDBAR].printType = TYPE_BASE;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BGMSOUNDBAR].position.x = 250;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BGMSOUNDBAR].position.y = 330;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BGMSOUNDBAR].size.x = 600;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BGMSOUNDBAR].size.y = 30;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BGMSOUNDBAR].isVisible = 0;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BGMSOUNDBAR].textBoxPos.x = 0;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BGMSOUNDBAR].textBoxPos.y = 0;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BGMSOUNDBAR].textBoxSize.x = 200;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BGMSOUNDBAR].textBoxSize.y = 200;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BGMSOUNDBAR].text = TEXT("BGM BAR");
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BGMSOUNDBAR].layer = LAYER_BOTTOM;

	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_EFFECTSOUNDBAR].printType = TYPE_BASE;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_EFFECTSOUNDBAR].position.x = 100;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_EFFECTSOUNDBAR].position.y = 400;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_EFFECTSOUNDBAR].size.x = 600;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_EFFECTSOUNDBAR].size.y = 30;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_EFFECTSOUNDBAR].isVisible = 0;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_EFFECTSOUNDBAR].textBoxPos.x = 0;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_EFFECTSOUNDBAR].textBoxPos.y = 0;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_EFFECTSOUNDBAR].textBoxSize.x = 200;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_EFFECTSOUNDBAR].textBoxSize.y = 200;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_EFFECTSOUNDBAR].text = TEXT("EFFECT BAR");
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_EFFECTSOUNDBAR].layer = LAYER_BOTTOM;

	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BGMSOUNDDOWNBUTTON].printType = TYPE_BASE;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BGMSOUNDDOWNBUTTON].position.x = 1184;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BGMSOUNDDOWNBUTTON].position.y = 443;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BGMSOUNDDOWNBUTTON].size.x = 45;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BGMSOUNDDOWNBUTTON].size.y = 45;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BGMSOUNDDOWNBUTTON].isVisible = 1;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BGMSOUNDDOWNBUTTON].textBoxPos.x = 0;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BGMSOUNDDOWNBUTTON].textBoxPos.y = 0;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BGMSOUNDDOWNBUTTON].textBoxSize.x = 50;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BGMSOUNDDOWNBUTTON].textBoxSize.y = 50;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BGMSOUNDDOWNBUTTON].text = TEXT("BGM DOWN");
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BGMSOUNDDOWNBUTTON].layer = LAYER_BOTTOM;

	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BGMSOUNDUPBUTTON].printType = TYPE_BASE;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BGMSOUNDUPBUTTON].position.x = 1252;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BGMSOUNDUPBUTTON].position.y = 443;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BGMSOUNDUPBUTTON].size.x = 45;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BGMSOUNDUPBUTTON].size.y = 45;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BGMSOUNDUPBUTTON].isVisible = 1;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BGMSOUNDUPBUTTON].textBoxPos.x = 0;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BGMSOUNDUPBUTTON].textBoxPos.y = 0;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BGMSOUNDUPBUTTON].textBoxSize.x = 50;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BGMSOUNDUPBUTTON].textBoxSize.y = 50;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BGMSOUNDUPBUTTON].text = TEXT("BGM UP");
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BGMSOUNDUPBUTTON].layer = LAYER_BOTTOM;

	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_EFFECTSOUNDDOWNBUTTON].printType = TYPE_BASE;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_EFFECTSOUNDDOWNBUTTON].position.x = 1179;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_EFFECTSOUNDDOWNBUTTON].position.y = 600;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_EFFECTSOUNDDOWNBUTTON].size.x = 45;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_EFFECTSOUNDDOWNBUTTON].size.y = 45;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_EFFECTSOUNDDOWNBUTTON].isVisible = 1;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_EFFECTSOUNDDOWNBUTTON].textBoxPos.x = 0;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_EFFECTSOUNDDOWNBUTTON].textBoxPos.y = 0;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_EFFECTSOUNDDOWNBUTTON].textBoxSize.x = 50;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_EFFECTSOUNDDOWNBUTTON].textBoxSize.y = 50;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_EFFECTSOUNDDOWNBUTTON].text = TEXT("EFFECT DOWN");
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_EFFECTSOUNDDOWNBUTTON].layer = LAYER_BOTTOM;

	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_EFFECTSOUNDUPBUTTON].printType = TYPE_BASE;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_EFFECTSOUNDUPBUTTON].position.x = 1252;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_EFFECTSOUNDUPBUTTON].position.y = 600;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_EFFECTSOUNDUPBUTTON].size.x = 45;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_EFFECTSOUNDUPBUTTON].size.y = 45;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_EFFECTSOUNDUPBUTTON].isVisible = 1;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_EFFECTSOUNDUPBUTTON].textBoxPos.x = 0;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_EFFECTSOUNDUPBUTTON].textBoxPos.y = 0;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_EFFECTSOUNDUPBUTTON].textBoxSize.x = 100;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_EFFECTSOUNDUPBUTTON].textBoxSize.y = 100;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_EFFECTSOUNDUPBUTTON].text = TEXT("EFFECT UP");
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_EFFECTSOUNDUPBUTTON].layer = LAYER_BOTTOM;

	//음소거 버튼 안 씀 -> visible을 0으로 하면 클릭 불가
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_MUTEBUTTON].printType = TYPE_BASE;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_MUTEBUTTON].position.x = 0;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_MUTEBUTTON].position.y = 0;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_MUTEBUTTON].size.x = 200;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_MUTEBUTTON].size.y = 80;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_MUTEBUTTON].isVisible = 0;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_MUTEBUTTON].textBoxPos.x = 0;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_MUTEBUTTON].textBoxPos.y = 0;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_MUTEBUTTON].textBoxSize.x = 100;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_MUTEBUTTON].textBoxSize.y = 100;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_MUTEBUTTON].text = TEXT("MUTE");
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_MUTEBUTTON].layer = LAYER_BOTTOM;

	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BACKBUTTON].printType = TYPE_BASE;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BACKBUTTON].position.x = 53;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BACKBUTTON].position.y = 784;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BACKBUTTON].size.x = 75;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BACKBUTTON].size.y = 75;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BACKBUTTON].isVisible = 1;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BACKBUTTON].textBoxPos.x = 0;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BACKBUTTON].textBoxPos.y = 0;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BACKBUTTON].textBoxSize.x = 100;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BACKBUTTON].textBoxSize.y = 100;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BACKBUTTON].text = TEXT("BACK");
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BACKBUTTON].layer = LAYER_BOTTOM;

	//// 배경음에서 움직이는 사각형 490 ~ 1100
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BGM_SQUARE].printType = TYPE_TRANSPARENT;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BGM_SQUARE].position.x = 0;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BGM_SQUARE].position.y = 0;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BGM_SQUARE].size.x = 0;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BGM_SQUARE].size.y = 0;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BGM_SQUARE].isVisible = 1;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BGM_SQUARE].imagePos.x = SETTING_SQUARE_LEFT_POS + (SETTING_SQUARE_RIGHT_POS - SETTING_SQUARE_LEFT_POS) * SoundPlayer_GetBgmVolume();
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BGM_SQUARE].imagePos.y = 460;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BGM_SQUARE].text = TEXT("BGM DOWN");
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BGM_SQUARE].layer = LAYER_BOTTOM;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BGM_SQUARE].imagePath = TEXT("images/사운드버튼.bmp");


	// 효과음에서 움직이는 사각형 490 ~ 1100
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_EFFECT_SOUND_SQUARE].printType = TYPE_TRANSPARENT;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_EFFECT_SOUND_SQUARE].position.x = 0;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_EFFECT_SOUND_SQUARE].position.y = 0;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_EFFECT_SOUND_SQUARE].size.x = 0;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_EFFECT_SOUND_SQUARE].size.y = 0;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_EFFECT_SOUND_SQUARE].isVisible = 1;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_EFFECT_SOUND_SQUARE].imagePos.x = SETTING_SQUARE_LEFT_POS + (SETTING_SQUARE_RIGHT_POS - SETTING_SQUARE_LEFT_POS) * SoundPlayer_GetEffectVolume();
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_EFFECT_SOUND_SQUARE].imagePos.y = 618;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_EFFECT_SOUND_SQUARE].text = TEXT("BGM DOWN");
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_EFFECT_SOUND_SQUARE].layer = LAYER_BOTTOM;
	settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_EFFECT_SOUND_SQUARE].imagePath = TEXT("images/사운드버튼1.bmp");

	SoundPlayer_Play(SOUND_BGM_MAINMENU);
}

void SettingScene_Update(float deltaTime)
{
	// 마우스 왼쪽 버튼이 내려갔을 때
	if (Input_GetMouseLeftDownNow())
	{
		SoundPlayer_Play(SOUND_EFFECT_BUTTON);

		// 클릭한 위치를 저장한다.
		settingScene_lastMouseLeftDownObject = SettingScene_ClickedObject(Input_GetMouseLeftDownPosition());
	}

	// 마우스 왼쪽 버튼이 올라올 때
	if (Input_GetMouseLeftUpNow())
	{
		// 클릭한 위치를 저장한다.
		settingScene_lastMouseLeftUpObject = SettingScene_ClickedObject(Input_GetMouseLeftUpPosition());

		// 마우스가 특정 오브젝트를 클릭한 경우
		if (settingScene_lastMouseLeftUpObject != -1 && settingScene_lastMouseLeftDownObject == settingScene_lastMouseLeftUpObject)
		{
			// 오브젝트 클릭 이벤트를 진행
			if (settingScene_lastMouseLeftDownObject == SETTINGSCENE_GAMEOBJECT_ID_MUTEBUTTON)
			{
				SoundPlayer_SetBgmVolume(0.0f);
				SoundPlayer_SetEffectVolume(0.0f);
			}
			else if (settingScene_lastMouseLeftDownObject == SETTINGSCENE_GAMEOBJECT_ID_BGMSOUNDUPBUTTON)
			{
				SoundPlayer_BgmVolumeUp();
			}
			else if (settingScene_lastMouseLeftDownObject == SETTINGSCENE_GAMEOBJECT_ID_BGMSOUNDDOWNBUTTON)
			{
				SoundPlayer_BgmVolumeDown();
			}
			else if (settingScene_lastMouseLeftDownObject == SETTINGSCENE_GAMEOBJECT_ID_EFFECTSOUNDUPBUTTON)
			{
				SoundPlayer_EffectVolumeUp();
			}
			else if (settingScene_lastMouseLeftDownObject == SETTINGSCENE_GAMEOBJECT_ID_EFFECTSOUNDDOWNBUTTON)
			{
				SoundPlayer_EffectVolumeDown();
			}
			else if (settingScene_lastMouseLeftDownObject == SETTINGSCENE_GAMEOBJECT_ID_BACKBUTTON)
			{
				Scene_ChangeScene(SCENE_ID_MAIN);
			}

			settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_BGM_SQUARE].imagePos.x = SETTING_SQUARE_LEFT_POS + (SETTING_SQUARE_RIGHT_POS - SETTING_SQUARE_LEFT_POS) * SoundPlayer_GetBgmVolume();
			settingScene_object[SETTINGSCENE_GAMEOBJECT_ID_EFFECT_SOUND_SQUARE].imagePos.x = SETTING_SQUARE_LEFT_POS + (SETTING_SQUARE_RIGHT_POS - SETTING_SQUARE_LEFT_POS) * SoundPlayer_GetEffectVolume();
		}
	}
}

void SettingScene_Render()
{
	// isVisible : true면 화면을 출력, false면 비출력
	// layer : 0, 1, 2, 3순으로 화면을 출력
	for (int i = 0; i < LAYER_SIZE; i++)
	{
		for (int j = 0; j < SETTINGSCENE_GAMEOBJECT_SIZE; j++)
		{
			// layer와 isVisible에 대한 판단을 한다
			if (settingScene_object[j].isVisible == 1 && settingScene_object[j].layer == i)
			{
				GDIEngine_PrintObject(settingScene_object[j]);
			}
		}
	}
}

// mousePos 위치의 오브젝트의 번호(object 배열에서의 인덱스)를 반환한다.
// 만약 오브젝트가 클릭되지 않았다면 -1을 리턴한다.
int SettingScene_ClickedObject(POINT mousePos)
{
	int result = -1;
	int maxLayer = -1;

	for (int i = 0; i < SETTINGSCENE_GAMEOBJECT_SIZE; i++)
	{
		int objVisible = settingScene_object[i].isVisible;
		int objPosX1 = settingScene_object[i].position.x;
		int objPosY1 = settingScene_object[i].position.y;
		int objPosX2 = settingScene_object[i].position.x + settingScene_object[i].size.x;
		int objPosY2 = settingScene_object[i].position.y + settingScene_object[i].size.y;

		// 넘겨받은 마우스의 좌표에 따라서 어떤 게임 오브젝트가 클릭 됬는지를 판단하여 리턴한다
		if (objVisible == 1 && objPosX1 < mousePos.x && mousePos.x < objPosX2 && objPosY1 < mousePos.y && mousePos.y < objPosY2)
		{
			if (maxLayer < settingScene_object[i].layer)
			{
				result = i;
				maxLayer = settingScene_object[i].layer;
			}
		}
	}

	return result;
}