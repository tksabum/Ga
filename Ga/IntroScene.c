#include "IntroScene.h"
#include "GDIEngine.h"
#include "Scene.h"
#include "GameObject.h"
#include "Input.h"
#include "SoundPlayer.h"
#include <time.h>

// ��Ʈ��

#define INTROSCENE_GAMEOBJECT_ID_BACKGROUND 0
#define INTROSCENE_GAMEOBJECT_ID_NEWSPAPER 1
#define INTROSCENE_GAMEOBJECT_ID_HOUSE 2
#define INTROSCENE_GAMEOBJECT_ID_LADDER 3
#define INTROSCENE_GAMEOBJECT_ID_TEXT 4
#define INTROSCENE_GAMEOBJECT_ID_BLACKSCREEN 5
#define INTROSCENE_GAMEOBJECT_ID_BLACKSCREEN2 6
#define INTROSCENE_GAMEOBJECT_ID_TEXTBOX 7

#define INTROSCENE_GAMEOBJECT_SIZE 8


Scene IntroScene;

GameObject objectI[INTROSCENE_GAMEOBJECT_SIZE];
int backgroundCount;
int newspaperCount;
int houseCount;
int blackscreenCount;
int housetextCount;

int introOnce;

float introStartTime;
float introTime1;
float introTime2;
float backgroundTime;
float newspaperTime;
float houseTime;

float newspaperText; // �Ź��� �ڵ��ؽ�Ʈ
float black2Count;   // ����ȭ��2 �ڵ��ؽ�Ʈ


void IntroScene_Ready()
{
	sceneList[SCENE_ID_INTRO] = &IntroScene;
	IntroScene.func_init = IntroScene_Init;
	IntroScene.func_update = IntroScene_Update;
	IntroScene.func_render = IntroScene_Render;
}

void IntroScene_Init()
{
	backgroundCount = 0;
	newspaperCount = 0;
	houseCount = 0;
	blackscreenCount = 0;
	housetextCount = 0;

	// ���ĺ����
	backgroundTime = 0.0f;
	newspaperTime = 0.0f;
	houseTime = 0.0f;



	// �ð��� �ؽ�Ʈ ���
	introStartTime = clock();
	introOnce = 1;

	newspaperText = 0.0f;
	black2Count = 0.0f;

	for (int i = 0; i < INTROSCENE_GAMEOBJECT_SIZE; i++)
	{
		objectI[i].Xdivision = 1;
		objectI[i].Ydivision = 1;
		objectI[i].imageNumber = 0;
		objectI[i].scalePivot.x = 0.0f;
		objectI[i].scalePivot.y = 0.0f;
		objectI[i].scale = 1.0f;
		objectI[i].imagePos.x = 0;
		objectI[i].imagePos.y = 0;
	}

	// BACKGROUND
	objectI[INTROSCENE_GAMEOBJECT_ID_BACKGROUND].printType = TYPE_ALPHABLEND;
	objectI[INTROSCENE_GAMEOBJECT_ID_BACKGROUND].blendFunction.BlendOp = 0;
	objectI[INTROSCENE_GAMEOBJECT_ID_BACKGROUND].blendFunction.BlendFlags = 0;
	objectI[INTROSCENE_GAMEOBJECT_ID_BACKGROUND].blendFunction.AlphaFormat = 0;
	objectI[INTROSCENE_GAMEOBJECT_ID_BACKGROUND].blendFunction.SourceConstantAlpha = 255;
	objectI[INTROSCENE_GAMEOBJECT_ID_BACKGROUND].size.x = 1600;
	objectI[INTROSCENE_GAMEOBJECT_ID_BACKGROUND].size.y = 900;
	objectI[INTROSCENE_GAMEOBJECT_ID_BACKGROUND].position.x = 0;
	objectI[INTROSCENE_GAMEOBJECT_ID_BACKGROUND].position.y = 0;
	objectI[INTROSCENE_GAMEOBJECT_ID_BACKGROUND].isVisible = 1;
	objectI[INTROSCENE_GAMEOBJECT_ID_BACKGROUND].layer = LAYER_BACKGROUND;
	objectI[INTROSCENE_GAMEOBJECT_ID_BACKGROUND].imagePath = TEXT("images/stage1/blackscreen.bmp");


	// NEWSPAPER
	objectI[INTROSCENE_GAMEOBJECT_ID_NEWSPAPER].printType = TYPE_ALPHABLEND;
	objectI[INTROSCENE_GAMEOBJECT_ID_NEWSPAPER].blendFunction.BlendOp = 0;
	objectI[INTROSCENE_GAMEOBJECT_ID_NEWSPAPER].blendFunction.BlendFlags = 0;
	objectI[INTROSCENE_GAMEOBJECT_ID_NEWSPAPER].blendFunction.AlphaFormat = 0;
	objectI[INTROSCENE_GAMEOBJECT_ID_NEWSPAPER].blendFunction.SourceConstantAlpha = 255;
	objectI[INTROSCENE_GAMEOBJECT_ID_NEWSPAPER].size.x = 1600;
	objectI[INTROSCENE_GAMEOBJECT_ID_NEWSPAPER].size.y = 900;
	objectI[INTROSCENE_GAMEOBJECT_ID_NEWSPAPER].position.x = 0;
	objectI[INTROSCENE_GAMEOBJECT_ID_NEWSPAPER].position.y = 0;
	objectI[INTROSCENE_GAMEOBJECT_ID_NEWSPAPER].isVisible = 0;
	objectI[INTROSCENE_GAMEOBJECT_ID_NEWSPAPER].layer = LAYER_MID;
	objectI[INTROSCENE_GAMEOBJECT_ID_NEWSPAPER].imagePath = TEXT("images/intro/introNewspaper2.bmp");

	// HOUSE
	objectI[INTROSCENE_GAMEOBJECT_ID_HOUSE].printType = TYPE_ALPHABLEND;
	objectI[INTROSCENE_GAMEOBJECT_ID_HOUSE].blendFunction.BlendOp = 0;
	objectI[INTROSCENE_GAMEOBJECT_ID_HOUSE].blendFunction.BlendFlags = 0;
	objectI[INTROSCENE_GAMEOBJECT_ID_HOUSE].blendFunction.AlphaFormat = 0;
	objectI[INTROSCENE_GAMEOBJECT_ID_HOUSE].blendFunction.SourceConstantAlpha = 255;
	objectI[INTROSCENE_GAMEOBJECT_ID_HOUSE].size.x = 1600;
	objectI[INTROSCENE_GAMEOBJECT_ID_HOUSE].size.y = 900;
	objectI[INTROSCENE_GAMEOBJECT_ID_HOUSE].position.x = 0;
	objectI[INTROSCENE_GAMEOBJECT_ID_HOUSE].position.y = 0;
	objectI[INTROSCENE_GAMEOBJECT_ID_HOUSE].isVisible = 0;
	objectI[INTROSCENE_GAMEOBJECT_ID_HOUSE].layer = LAYER_BOTTOM;
	objectI[INTROSCENE_GAMEOBJECT_ID_HOUSE].imagePath = TEXT("images/intro/Intro_Abandoedhouse.bmp");

	// LADDER
	objectI[INTROSCENE_GAMEOBJECT_ID_LADDER].printType = TYPE_TRANSPARENT;
	objectI[INTROSCENE_GAMEOBJECT_ID_LADDER].size.x = 100;
	objectI[INTROSCENE_GAMEOBJECT_ID_LADDER].size.y = 300;
	objectI[INTROSCENE_GAMEOBJECT_ID_LADDER].position.x = 1400;
	objectI[INTROSCENE_GAMEOBJECT_ID_LADDER].position.y = 500;
	objectI[INTROSCENE_GAMEOBJECT_ID_LADDER].isVisible = 0;
	objectI[INTROSCENE_GAMEOBJECT_ID_LADDER].layer = LAYER_TOP;

	// TEXT
	objectI[INTROSCENE_GAMEOBJECT_ID_TEXT].printType = TYPE_TRANSPARENT;
	objectI[INTROSCENE_GAMEOBJECT_ID_TEXT].size.x = 1600;
	objectI[INTROSCENE_GAMEOBJECT_ID_TEXT].size.y = 900;
	objectI[INTROSCENE_GAMEOBJECT_ID_TEXT].position.x = 0;
	objectI[INTROSCENE_GAMEOBJECT_ID_TEXT].position.y = 0;
	objectI[INTROSCENE_GAMEOBJECT_ID_TEXT].isVisible = 0;
	objectI[INTROSCENE_GAMEOBJECT_ID_TEXT].layer = LAYER_MID;
	objectI[INTROSCENE_GAMEOBJECT_ID_TEXT].imagePath = TEXT("images/intro/introText.bmp");

	// BLACKSCREEN
	objectI[INTROSCENE_GAMEOBJECT_ID_BLACKSCREEN].printType = TYPE_ALPHABLEND;
	objectI[INTROSCENE_GAMEOBJECT_ID_BLACKSCREEN].blendFunction.BlendOp = 0;
	objectI[INTROSCENE_GAMEOBJECT_ID_BLACKSCREEN].blendFunction.BlendFlags = 0;
	objectI[INTROSCENE_GAMEOBJECT_ID_BLACKSCREEN].blendFunction.AlphaFormat = 0;
	objectI[INTROSCENE_GAMEOBJECT_ID_BLACKSCREEN].blendFunction.SourceConstantAlpha = 0;
	objectI[INTROSCENE_GAMEOBJECT_ID_BLACKSCREEN].size.x = 1600;
	objectI[INTROSCENE_GAMEOBJECT_ID_BLACKSCREEN].size.y = 900;
	objectI[INTROSCENE_GAMEOBJECT_ID_BLACKSCREEN].position.x = 0;
	objectI[INTROSCENE_GAMEOBJECT_ID_BLACKSCREEN].position.y = 0;
	objectI[INTROSCENE_GAMEOBJECT_ID_BLACKSCREEN].isVisible = 0;
	objectI[INTROSCENE_GAMEOBJECT_ID_BLACKSCREEN].layer = LAYER_TOP;
	objectI[INTROSCENE_GAMEOBJECT_ID_BLACKSCREEN].imagePath = TEXT("images/stage1/blackscreen.bmp");

	// BLACKSCREEN2
	objectI[INTROSCENE_GAMEOBJECT_ID_BLACKSCREEN2].printType = TYPE_TRANSPARENT;
	objectI[INTROSCENE_GAMEOBJECT_ID_BLACKSCREEN2].size.x = 1600;
	objectI[INTROSCENE_GAMEOBJECT_ID_BLACKSCREEN2].size.y = 900;
	objectI[INTROSCENE_GAMEOBJECT_ID_BLACKSCREEN2].position.x = 0;
	objectI[INTROSCENE_GAMEOBJECT_ID_BLACKSCREEN2].position.y = 0;
	objectI[INTROSCENE_GAMEOBJECT_ID_BLACKSCREEN2].isVisible = 0;
	objectI[INTROSCENE_GAMEOBJECT_ID_BLACKSCREEN2].layer = LAYER_MID;
	objectI[INTROSCENE_GAMEOBJECT_ID_BLACKSCREEN2].imagePath = TEXT("images/stage1/blackscreen.bmp");

	// TEXTBOX
	objectI[INTROSCENE_GAMEOBJECT_ID_TEXTBOX].printType = TYPE_ALPHABLEND | TYPE_TEXT;
	objectI[INTROSCENE_GAMEOBJECT_ID_TEXTBOX].blendFunction.BlendOp = 0;
	objectI[INTROSCENE_GAMEOBJECT_ID_TEXTBOX].blendFunction.BlendFlags = 0;
	objectI[INTROSCENE_GAMEOBJECT_ID_TEXTBOX].blendFunction.AlphaFormat = 0;
	objectI[INTROSCENE_GAMEOBJECT_ID_TEXTBOX].blendFunction.SourceConstantAlpha = 220;
	objectI[INTROSCENE_GAMEOBJECT_ID_TEXTBOX].size.x = 1100;
	objectI[INTROSCENE_GAMEOBJECT_ID_TEXTBOX].size.y = 300;
	//objectI[INTROSCENE_GAMEOBJECT_ID_TEXTBOX].position.x = 335;
	objectI[INTROSCENE_GAMEOBJECT_ID_TEXTBOX].position.y = 755;
	objectI[INTROSCENE_GAMEOBJECT_ID_TEXTBOX].textBoxSize.x = 1600;
	objectI[INTROSCENE_GAMEOBJECT_ID_TEXTBOX].textBoxSize.y = 900;
	objectI[INTROSCENE_GAMEOBJECT_ID_TEXTBOX].textBoxPos.x = 0;
	objectI[INTROSCENE_GAMEOBJECT_ID_TEXTBOX].textBoxPos.y = 0;
	objectI[INTROSCENE_GAMEOBJECT_ID_TEXTBOX].imagePos.x = 300;
	objectI[INTROSCENE_GAMEOBJECT_ID_TEXTBOX].imagePos.y = 725;
	objectI[INTROSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 0;
	objectI[INTROSCENE_GAMEOBJECT_ID_TEXTBOX].text = NULL;
	objectI[INTROSCENE_GAMEOBJECT_ID_TEXTBOX].layer = LAYER_TOP;
	objectI[INTROSCENE_GAMEOBJECT_ID_TEXTBOX].imagePath = TEXT("images/test1.bmp");

	SoundPlayer_Play(SOUND_BGM_MAIN);
}

void IntroScene_Update(float deltaTime)
{
	introTime1 = clock();

	// ���� ���� 2�� �� ȭ�� ���̵�ƿ�
	if (introOnce == 1 && introTime1 - introStartTime >= 2000)
	{
		backgroundTime += deltaTime;

		if (objectI[INTROSCENE_GAMEOBJECT_ID_BACKGROUND].isVisible == 1)
		{
			if (backgroundTime >= 1.5f)
			{
				newspaperText = 0.0f;
				objectI[INTROSCENE_GAMEOBJECT_ID_BACKGROUND].isVisible = 0;
				objectI[INTROSCENE_GAMEOBJECT_ID_NEWSPAPER].isVisible = 1;
			}
			else
			{
				objectI[INTROSCENE_GAMEOBJECT_ID_BACKGROUND].blendFunction.SourceConstantAlpha = (BYTE)(255.0f - (255.0f / 1.5f) * backgroundTime);
			}
		}
	}

	// �Ź� Ŭ���� ȭ�� ���̵� �ƿ�
	if (newspaperCount >= 3)
	{
		newspaperTime += deltaTime;

		if (objectI[INTROSCENE_GAMEOBJECT_ID_NEWSPAPER].isVisible == 1)
		{

			if (newspaperTime >= 1.5f)
			{
				objectI[INTROSCENE_GAMEOBJECT_ID_NEWSPAPER].isVisible = 0;
				objectI[INTROSCENE_GAMEOBJECT_ID_BLACKSCREEN2].isVisible = 1;

				black2Count = 0.0f;
				//objectI[INTROSCENE_GAMEOBJECT_ID_HOUSE].isVisible = 1;
				//objectI[INTROSCENE_GAMEOBJECT_ID_LADDER].isVisible = 1;
				//objectI[INTROSCENE_GAMEOBJECT_ID_BLACKSCREEN].isVisible = 0;
				objectI[INTROSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 0;


			}
			else
			{
				objectI[INTROSCENE_GAMEOBJECT_ID_NEWSPAPER].blendFunction.SourceConstantAlpha = (BYTE)(255.0f - (255.0f / 1.5f) * newspaperTime);
				//objectI[INTROSCENE_GAMEOBJECT_ID_BLACKSCREEN].blendFunction.SourceConstantAlpha = (BYTE)(0.0f + (255.0f / 1.5f) * newspaperTime);

			}
		}
	}

	if (houseCount >= 1)
	{
		houseTime += deltaTime;

		if (objectI[INTROSCENE_GAMEOBJECT_ID_HOUSE].isVisible == 1)
		{
			if (houseTime >= 1.5f)
			{
				objectI[INTROSCENE_GAMEOBJECT_ID_HOUSE].isVisible = 0;

				objectI[INTROSCENE_GAMEOBJECT_ID_LADDER].isVisible = 0;

				objectI[INTROSCENE_GAMEOBJECT_ID_BLACKSCREEN].isVisible = 0;

				SoundPlayer_StopAllBGM();

				Scene_ChangeScene(SCENE_ID_LIVINGROOM);

			}
			else
			{
				objectI[INTROSCENE_GAMEOBJECT_ID_BLACKSCREEN].blendFunction.SourceConstantAlpha = (BYTE)(0.0f + (255.0f / 1.5f) * houseTime);
			}
		}
	}

	if (newspaperCount == 0)
	{
		newspaperText += deltaTime;
		if (objectI[INTROSCENE_GAMEOBJECT_ID_NEWSPAPER].isVisible == 1)
		{
			if (newspaperText >= 0.5f)
			{
				objectI[INTROSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;

				objectI[INTROSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("[ 2012�� 11�� 10�� �߻��� ������ ȭ��� 5�� ���� ��� �� ���� ��� ]");
			}
		}
	}

	if (blackscreenCount == 0)
	{
		black2Count += deltaTime;

		if (objectI[INTROSCENE_GAMEOBJECT_ID_BLACKSCREEN2].isVisible == 1)
		{
			if (black2Count >= 0.5f)
			{
				objectI[INTROSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;

				objectI[INTROSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("[ ���� 2022�� 11��10�� �� 11�� ]");
			}
		}
	}


	if (Input_GetMouseLeftDownNow())
	{
		SoundPlayer_Play(SOUND_EFFECT_BUTTON);

		//��Ŭ���� ������Ʈ�� ��ǥ���� �޴´�
		int clickedObject = IntroScene_ClickedObject(Input_GetMouseLeftDownPosition());


		// ���ȭ���� Ŭ���� �Ź��� �˾�
		if (clickedObject == INTROSCENE_GAMEOBJECT_ID_BACKGROUND)
		{
			backgroundCount++;

			//backgroundTime = 0.0f;
		}





		// �Ź��� Ŭ���� �� ����
		if (clickedObject == INTROSCENE_GAMEOBJECT_ID_NEWSPAPER)
		{
			newspaperCount++;

			//newspaperText = 0.0f;


			objectI[INTROSCENE_GAMEOBJECT_ID_LADDER].isVisible = 1;

		
			if (newspaperCount == 1)
			{
				objectI[INTROSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;

				objectI[INTROSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("ȭ��� ���� 4���� ����ϰ� 1���� ������ �̽��׸��� ����̴�.");
			}
			else if (newspaperCount == 2)
			{
				objectI[INTROSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;

				objectI[INTROSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("�׷��� �ֱ� ��� �װ����� �㸶�� ������ �Ҹ��� �Բ� �̻��� ������ �Ͼ�ٴ� �ҹ��� ���� �ִ�.");
			}
			SoundPlayer_Play(SOUND_EFFECT_NEWSPAPER);
		}


		else if (clickedObject == INTROSCENE_GAMEOBJECT_ID_BLACKSCREEN2)
		{
			blackscreenCount++;

// 			if (blackscreenCount == 1)
// 			{
// 				objectI[INTROSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;
// 
// 				objectI[INTROSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("[ ���� 2022�� 11��10�� �� 11�� ]");
// 			}

			if (blackscreenCount == 1)
			{
				objectI[INTROSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;

				objectI[INTROSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("??? : ���� ��� �������� �ٷ� �� �� ü���Դϴ�!\n\n ������, ������ ���ƿ� �� ���� �����ּ���~");
			}

			else if (blackscreenCount == 2)
			{
				objectI[INTROSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;

				objectI[INTROSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("??? : �Ա����� ���а��� ��û����... \n\n�׷��� �ð� �� �� ���� �ϴ� �ٷ� �����ڽ��ϴ�!");
			}

			else
			{
				objectI[INTROSCENE_GAMEOBJECT_ID_BLACKSCREEN2].isVisible = 0;
				objectI[INTROSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 0;
				objectI[INTROSCENE_GAMEOBJECT_ID_HOUSE].isVisible = 1;
			}
		}

		// ���̹����� �ִ� ��ٸ� Ŭ���� �������� 1 ����
		else if (clickedObject == INTROSCENE_GAMEOBJECT_ID_LADDER && objectI[INTROSCENE_GAMEOBJECT_ID_HOUSE].isVisible == 1 && objectI[INTROSCENE_GAMEOBJECT_ID_LADDER].isVisible == 1)
		{
			houseCount++;
			objectI[INTROSCENE_GAMEOBJECT_ID_BLACKSCREEN].isVisible = 1;

			if (houseCount == 1)
			{
				SoundPlayer_Play(SOUND_EFFECT_STEPIN);
			}
		}

		if (objectI[INTROSCENE_GAMEOBJECT_ID_HOUSE].isVisible == 1 && clickedObject == INTROSCENE_GAMEOBJECT_ID_HOUSE)
		{
			housetextCount++;

			if (housetextCount == 1)
			{
				objectI[INTROSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;

				objectI[INTROSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("�̻��ϰ� �ͼ��� ������ ���� ��µ�.. \n\nâ���� �ƹ����� ���� ���ϰ� ������ �ǵ������� ���� ������ ����.");
			}

			else if (housetextCount == 2)
			{
				objectI[INTROSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;

				objectI[INTROSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("��ٸ��� ���� ���η� �� �� ���� �� ����. \n\n���� �ִ� ��ٸ��� �̿��غ���.");
			}

// 			else if (housetextCount == 3)
// 			{
// 				objectI[INTROSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 0;
// 
// 			}
// 			else if (housetextCount == 4)
// 			{
// 				objectI[INTROSCENE_GAMEOBJECT_ID_TEXT].isVisible = 1;
// 			}
		}
	}
}

void IntroScene_Render()
{
	// isVisible : true�� ȭ���� ���, false�� �����
	// layer : 0, 1, 2, 3������ ȭ���� ���
	for (int i = 0; i < LAYER_SIZE; i++)
	{
		for (int j = 0; j < INTROSCENE_GAMEOBJECT_SIZE; j++)
		{
			// layer�� isVisible�� ���� �Ǵ��� �Ѵ�
			if (objectI[j].isVisible == 1 && objectI[j].layer == i)
			{
				//GDIEngine_Rectangle(objectI[j].position.x, objectI[j].position.y, objectI[j].size.x, objectI[j].size.y);
				GDIEngine_PrintObject(objectI[j]);
				//GDIEngine_PrintObjectText(objectI[j]);
			}
		}
	}
}

// mousePos ��ġ�� ������Ʈ�� ��ȣ(object �迭������ �ε���)�� ��ȯ�Ѵ�.
// ���� ������Ʈ�� Ŭ������ �ʾҴٸ� -1�� �����Ѵ�.
int IntroScene_ClickedObject(POINT mousePos)
{
	int result = -1;
	int maxLayer = -1;

	for (int i = 0; i < INTROSCENE_GAMEOBJECT_SIZE; i++)
	{
		int objVisible = objectI[i].isVisible;
		int objPosX1 = objectI[i].position.x;
		int objPosY1 = objectI[i].position.y;
		int objPosX2 = objectI[i].position.x + objectI[i].size.x;
		int objPosY2 = objectI[i].position.y + objectI[i].size.y;

		// �Ѱܹ��� ���콺�� ��ǥ�� ���� � ���� ������Ʈ�� Ŭ�� ������� �Ǵ��Ͽ� �����Ѵ�
		if (objVisible == 1 && objPosX1 < mousePos.x && mousePos.x < objPosX2 && objPosY1 < mousePos.y && mousePos.y < objPosY2)
		{
			if (maxLayer < objectI[i].layer)
			{
				result = i;
				maxLayer = objectI[i].layer;
			}
		}
	}

	return result;
}
