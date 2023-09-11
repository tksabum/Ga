#include "GameOverScene.h"
#include "GDIEngine.h"
#include "Scene.h"
#include "GameObject.h"
#include "Input.h"
#include "SoundPlayer.h"
#include "GameTimer.h"

// ���� ���� ��

//���� ���� ȭ�鿡 �ʿ��� ������Ʈ
#define GAMEOVERSCENE_GAMEOBJECT_ID_BACKGROUND 0
#define GAMEOVERSCENE_GAMEOBJECT_ID_SELECTION1 1
#define GAMEOVERSCENE_GAMEOBJECT_ID_SELECTION2 2

#define GAMEOVERSCENE_GAMEOBJECT_SIZE 3

Scene gameoverScene;

GameObject objectGO[GAMEOVERSCENE_GAMEOBJECT_SIZE];



void GameOverScene_Ready()
{
	sceneList[SCENE_ID_GAMEOVER] = &gameoverScene;
	gameoverScene.func_init = GameOverScene_Init;
	gameoverScene.func_update = GameOverScene_Update;
	gameoverScene.func_render = GameOverScene_Render;
}

//scene ��ȯ�� ���� ��, �ش� scene�� �ʱ�ȭ
void GameOverScene_Init()
{
	// ���� Ÿ�̸� ����
	GameTimer_GameEnd();

	for (int i = 0; i < GAMEOVERSCENE_GAMEOBJECT_SIZE; i++)
	{
		objectGO[i].Xdivision = 1;
		objectGO[i].Ydivision = 1;
		objectGO[i].imageNumber = 0;
		objectGO[i].scalePivot.x = 0.0f;
		objectGO[i].scalePivot.y = 0.0f;
		objectGO[i].scale = 1.0f;
		objectGO[i].imagePos.x = 0;
		objectGO[i].imagePos.y = 0;
	}

	// BACKGROUND
	objectGO[GAMEOVERSCENE_GAMEOBJECT_ID_BACKGROUND].printType = TYPE_TRANSPARENT;
	objectGO[GAMEOVERSCENE_GAMEOBJECT_ID_BACKGROUND].size.x = 1600;
	objectGO[GAMEOVERSCENE_GAMEOBJECT_ID_BACKGROUND].size.y = 900;
	objectGO[GAMEOVERSCENE_GAMEOBJECT_ID_BACKGROUND].position.x = 0;
	objectGO[GAMEOVERSCENE_GAMEOBJECT_ID_BACKGROUND].position.y = 0;
	objectGO[GAMEOVERSCENE_GAMEOBJECT_ID_BACKGROUND].isVisible = 1;
	objectGO[GAMEOVERSCENE_GAMEOBJECT_ID_BACKGROUND].layer = LAYER_BACKGROUND;
	objectGO[GAMEOVERSCENE_GAMEOBJECT_ID_BACKGROUND].imagePath = TEXT("images/GameOver.bmp");

	// SELECTION1
	objectGO[GAMEOVERSCENE_GAMEOBJECT_ID_SELECTION1].printType = TYPE_BASE;
	objectGO[GAMEOVERSCENE_GAMEOBJECT_ID_SELECTION1].size.x = 200;
	objectGO[GAMEOVERSCENE_GAMEOBJECT_ID_SELECTION1].size.y = 70;
	objectGO[GAMEOVERSCENE_GAMEOBJECT_ID_SELECTION1].position.x = 398;
	objectGO[GAMEOVERSCENE_GAMEOBJECT_ID_SELECTION1].position.y = 746;
	objectGO[GAMEOVERSCENE_GAMEOBJECT_ID_SELECTION1].isVisible = 1;
	objectGO[GAMEOVERSCENE_GAMEOBJECT_ID_SELECTION1].layer = LAYER_BOTTOM;

	// SELECTION2
	objectGO[GAMEOVERSCENE_GAMEOBJECT_ID_SELECTION2].printType = TYPE_BASE;
	objectGO[GAMEOVERSCENE_GAMEOBJECT_ID_SELECTION2].size.x = 200;
	objectGO[GAMEOVERSCENE_GAMEOBJECT_ID_SELECTION2].size.y = 70;
	objectGO[GAMEOVERSCENE_GAMEOBJECT_ID_SELECTION2].position.x = 999;
	objectGO[GAMEOVERSCENE_GAMEOBJECT_ID_SELECTION2].position.y = 746;
	objectGO[GAMEOVERSCENE_GAMEOBJECT_ID_SELECTION2].isVisible = 1;
	objectGO[GAMEOVERSCENE_GAMEOBJECT_ID_SELECTION2].layer = LAYER_BOTTOM;

	SoundPlayer_StopAllBGM();
	SoundPlayer_Play(SOUND_EFFECT_GAMEOVER);
}

void GameOverScene_Update(float deltaTime)
{
	if (Input_GetMouseLeftDownNow())
	{
		int clickedObject = GameOverScene_ClickedObject(Input_GetMouseLeftDownPosition());

		SoundPlayer_Play(SOUND_EFFECT_BUTTON);

		SoundPlayer_StopAllBGM();

		// SELECTION1 Ŭ���� �÷����ϴ� ������ �����Ѵ�
		if (clickedObject == GAMEOVERSCENE_GAMEOBJECT_ID_SELECTION1)
		{
			Scene_ChangeScene(SCENE_ID_LIVINGROOM);
		}

		// SELECTION2 Ŭ���� ���ξ����� �Ѿ��
		else if (clickedObject == GAMEOVERSCENE_GAMEOBJECT_ID_SELECTION2)
		{
			Scene_ChangeScene(SCENE_ID_MAIN);
		}
	}
}
void GameOverScene_Render()
{
	// isVisible : true�� ȭ���� ���, false�� �����
	// layer : 0, 1, 2, 3������ ȭ���� ���
	for (int i = 0; i < LAYER_SIZE; i++)
	{
		for (int j = 0; j < GAMEOVERSCENE_GAMEOBJECT_SIZE; j++)
		{
			// layer�� isVisible�� ���� �Ǵ��� �Ѵ�
			if (objectGO[j].isVisible == 1 && objectGO[j].layer == i)
			{
				//GDIEngine_Rectangle(objectGO[j].position.x, objectGO[j].position.y, objectGO[j].size.x, objectGO[j].size.y);
				//GDIEngine_PrintObjectText(objectGO[j]);
				GDIEngine_PrintObject(objectGO[j]);

			}
		}
	}
}


int GameOverScene_ClickedObject(POINT mousePos)
{
	int result = -1;
	int maxLayer = -1;

	for (int i = 0; i < 12; i++)
	{
		int objVisible = objectGO[i].isVisible;
		int objPosX1 = objectGO[i].position.x;
		int objPosY1 = objectGO[i].position.y;
		int objPosX2 = objectGO[i].position.x + objectGO[i].size.x;
		int objPosY2 = objectGO[i].position.y + objectGO[i].size.y;

		// �Ѱܹ��� ���콺�� ��ǥ�� ���� � ���� ������Ʈ�� Ŭ�� ������� �Ǵ��Ͽ� �����Ѵ�
		if (objVisible == 1 && objPosX1 < mousePos.x && mousePos.x < objPosX2 && objPosY1 < mousePos.y && mousePos.y < objPosY2)
		{
			if (maxLayer < objectGO[i].layer)
			{					 
				result = i;		 
				maxLayer = objectGO[i].layer;
			}
		}
	}

	return result;
}