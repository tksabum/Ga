#include "EndingScene.h"
#include "GDIEngine.h"
#include "Scene.h"
#include "GameObject.h"
#include "Input.h"
#include "SoundPlayer.h"
#include "GameTimer.h"

#define ENDINGSCENE_GAMEOBJECT_ID_BACKGROUND 0

#define ENDINGSCENE_GAMEOBJECT_SIZE 1

Scene endingScene;

GameObject endingScene_object[ENDINGSCENE_GAMEOBJECT_SIZE];

const float ENDING_SPEED = -100.0f;
const float ENDING_MIN_POS = -2250.0f;

void EndingScene_Ready()
{
	sceneList[SCENE_ID_ENDING] = &endingScene;
	endingScene.func_init = EndingScene_Init;
	endingScene.func_update = EndingScene_Update;
	endingScene.func_render = EndingScene_Render;
}

void EndingScene_Init()
{
	// 모든 오브젝트의 X,Y division과 imageNumber 초기화
	for (int i = 0; i < ENDINGSCENE_GAMEOBJECT_SIZE; i++)
	{
		endingScene_object[i].Xdivision = 1;
		endingScene_object[i].Ydivision = 1;
		endingScene_object[i].imageNumber = 0;
		endingScene_object[i].scalePivot.x = 0.0f;
		endingScene_object[i].scalePivot.y = 0.0f;
		endingScene_object[i].scale = 1.0f;
		endingScene_object[i].imagePos.x = 0;
		endingScene_object[i].imagePos.y = 0;
	}

	// 오브젝트들의 초기값 설정
	endingScene_object[ENDINGSCENE_GAMEOBJECT_ID_BACKGROUND].printType = TYPE_TRANSPARENT;
	endingScene_object[ENDINGSCENE_GAMEOBJECT_ID_BACKGROUND].position.x = 0;
	endingScene_object[ENDINGSCENE_GAMEOBJECT_ID_BACKGROUND].position.y = 0;
	endingScene_object[ENDINGSCENE_GAMEOBJECT_ID_BACKGROUND].size.x = 0;
	endingScene_object[ENDINGSCENE_GAMEOBJECT_ID_BACKGROUND].size.y = 0;
	endingScene_object[ENDINGSCENE_GAMEOBJECT_ID_BACKGROUND].isVisible = 1;
	endingScene_object[ENDINGSCENE_GAMEOBJECT_ID_BACKGROUND].imagePath = TEXT("images/크레딧.bmp");
	endingScene_object[ENDINGSCENE_GAMEOBJECT_ID_BACKGROUND].layer = LAYER_BACKGROUND;

	SoundPlayer_Play(SOUND_BGM_ENDING);
}

void EndingScene_Update(float deltaTime)
{
	if (endingScene_object[ENDINGSCENE_GAMEOBJECT_ID_BACKGROUND].imagePos.y > ENDING_MIN_POS)
	{
		endingScene_object[ENDINGSCENE_GAMEOBJECT_ID_BACKGROUND].imagePos.y += ENDING_SPEED * deltaTime;
	}
	else
	{
		endingScene_object[ENDINGSCENE_GAMEOBJECT_ID_BACKGROUND].imagePos.y = ENDING_MIN_POS;
		if (Input_GetMouseLeftUpNow())
		{
			Scene_ChangeScene(SCENE_ID_MAIN);
		}
	}
}

void EndingScene_Render()
{
	// isVisible : true면 화면을 출력, false면 비출력
	// layer : 0, 1, 2, 3순으로 화면을 출력
	for (int i = 0; i < LAYER_SIZE; i++)
	{
		for (int j = 0; j < ENDINGSCENE_GAMEOBJECT_SIZE; j++)
		{
			// layer와 isVisible에 대한 판단을 한다
			if (endingScene_object[j].isVisible == 1 && endingScene_object[j].layer == i)
			{
				GDIEngine_PrintObject(endingScene_object[j]);
			}
		}
	}
}
