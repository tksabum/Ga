#include "LivingRoomScene.h"
#include "GDIEngine.h"
#include "Scene.h"
#include "GameObject.h"
#include "Input.h"
#include "SoundPlayer.h"
#include "GameTimer.h"
#include <time.h>
// ��������1 �Ž�



// ���ۺ��� �����ִ� ������Ʈ��
#define LIVINGROOMSCENE_GAMEOBJECT_ID_BACKGROUND 0
#define LIVINGROOMSCENE_GAMEOBJECT_ID_BLACKSCREEN 1 
#define LIVINGROOMSCENE_GAMEOBJECT_ID_DRAWER 2 
#define LIVINGROOMSCENE_GAMEOBJECT_ID_PHOTO 3 
#define LIVINGROOMSCENE_GAMEOBJECT_ID_DOOR 4 
#define LIVINGROOMSCENE_GAMEOBJECT_ID_SOFA 5
#define LIVINGROOMSCENE_GAMEOBJECT_ID_TRAMPALINE 6 
#define LIVINGROOMSCENE_GAMEOBJECT_ID_RIDES 7

// ���� �˾��Ǵ� ������Ʈ��
#define LIVINGROOMSCENE_GAMEOBJECT_ID_CRAWBAR 8
#define LIVINGROOMSCENE_GAMEOBJECT_ID_GHOST 9 
#define LIVINGROOMSCENE_GAMEOBJECT_ID_PHOTOCLOSEUP 10 
#define LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX 11 
#define LIVINGROOMSCENE_GAMEOBJECT_ID_EMPTYBOX 12
#define LIVINGROOMSCENE_GAMEOBJECT_ID_FAMILY 13
#define LIVINGROOMSCENE_GAMEOBJECT_ID_BIGFACE 14

#define LIVINGROOMSCENE_GAMEOBJECT_SIZE 15

Scene livingScene;

GameObject objectL[LIVINGROOMSCENE_GAMEOBJECT_SIZE];

//ī��Ʈ�� ����
int blackCount;
int drawerCount;
int photoCount;
int doorCount;
int sofaCount;
int trampalineCount;
int rideCount;
int ghostCount;
int closeupCount;
int familyCount;
int bigfaceCount;
int outOnce;

float startGame;
float currentGameTime;
float familyAppearTime;
float blackDisappear;
float bigfaceAppearTime;

//sceneList�� mainScene�� ��� mainScene�� �Լ� �����͵��� �ʱ�ȭ(�Լ��� �ּҰ��� ��´�) �Ѵ�.
void LivingRoomScene_Ready()
{
	sceneList[SCENE_ID_LIVINGROOM] = &livingScene;
	livingScene.func_init = LivingRoomScene_Init;
	livingScene.func_update = LivingRoomScene_Update;
	livingScene.func_render = LivingRoomScene_Render;
}

//scene ��ȯ�� ���� ��, �ش� scene�� �ʱ�ȭ
void LivingRoomScene_Init()
{
	// ���� Ÿ�̸� ����
	GameTimer_GameStart();

	startGame = clock();

	// Ŭ������ �����ϴ� ī��Ʈ �ʱ�ȭ 
	blackCount = 0;
	drawerCount = 0;
	photoCount = 0;
	doorCount = 0;
	sofaCount = 0;
	trampalineCount = 0;
	rideCount = 0;
	ghostCount = 0;
	closeupCount = 0;
	familyCount = 0;
	bigfaceCount = 0;

	outOnce = 1;

	//startGame = 0.0f;
	//currentGameTime = 0.0f;
	familyAppearTime = 0.0f;
	blackDisappear = 0.0f;
	bigfaceAppearTime = 0.0f;

	// ��� ������Ʈ�� X,Y division�� imageNumber �ʱ�ȭ
	for (int i = 0; i < LIVINGROOMSCENE_GAMEOBJECT_SIZE; i++)
	{
		objectL[i].Xdivision = 1;
		objectL[i].Ydivision = 1;
		objectL[i].imageNumber = 0;
		objectL[i].scalePivot.x = 0.0f;
		objectL[i].scalePivot.y = 0.0f;
		objectL[i].scale = 1.0f;
		objectL[i].imagePos.x = 0;
		objectL[i].imagePos.y = 0;
	}

	// BACKGROUND
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_BACKGROUND].printType = TYPE_TRANSPARENT;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_BACKGROUND].size.x = 1600;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_BACKGROUND].size.y = 900;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_BACKGROUND].position.x = 0;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_BACKGROUND].position.y = 0;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_BACKGROUND].isVisible = 1;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_BACKGROUND].layer = LAYER_BACKGROUND;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_BACKGROUND].imagePath = TEXT("images/stage1/Stage1Normal.bmp");

	// BLACKSCREEN
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_BLACKSCREEN].printType = TYPE_ALPHABLEND;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_BLACKSCREEN].blendFunction.BlendOp = 0;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_BLACKSCREEN].blendFunction.BlendFlags = 0;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_BLACKSCREEN].blendFunction.AlphaFormat = 0;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_BLACKSCREEN].blendFunction.SourceConstantAlpha = 255;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_BLACKSCREEN].size.x = 1600;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_BLACKSCREEN].size.y = 900;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_BLACKSCREEN].position.x = 0;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_BLACKSCREEN].position.y = 0;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_BLACKSCREEN].isVisible = 1;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_BLACKSCREEN].layer = LAYER_TOP;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_BLACKSCREEN].imagePath = TEXT("images/stage1/blackscreen.bmp");

	// DRAWER 
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_DRAWER].printType = TYPE_BASE;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_DRAWER].size.x = 298;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_DRAWER].size.y = 176;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_DRAWER].position.x = 370;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_DRAWER].position.y = 459;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_DRAWER].isVisible = 1;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_DRAWER].layer = LAYER_BOTTOM;

	// PHOTO
	// �������� ��ǥ....
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_PHOTO].printType = TYPE_TRANSPARENT;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_PHOTO].size.x = 156;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_PHOTO].size.y = 156;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_PHOTO].position.x = 415;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_PHOTO].position.y = 299;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_PHOTO].isVisible = 1;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_PHOTO].layer = LAYER_BOTTOM;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_PHOTO].imagePath = TEXT("");

	// DOOR
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_DOOR].printType = TYPE_BASE;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_DOOR].size.x = 195;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_DOOR].size.y = 900;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_DOOR].position.x = 0;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_DOOR].position.y = 0;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_DOOR].isVisible = 1;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_DOOR].layer = LAYER_BOTTOM;

	// SOFA
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_SOFA].printType = TYPE_BASE;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_SOFA].size.x = 402;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_SOFA].size.y = 250;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_SOFA].position.x = 1098;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_SOFA].position.y = 600;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_SOFA].isVisible = 1;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_SOFA].layer = LAYER_BOTTOM;

	// FAMILY
	// PHOTO�� ���� �ٸ�����..??
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_FAMILY].printType = TYPE_ALPHABLEND;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_FAMILY].blendFunction.BlendOp = 0;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_FAMILY].blendFunction.BlendFlags = 0;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_FAMILY].blendFunction.AlphaFormat = 0;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_FAMILY].blendFunction.SourceConstantAlpha = 150;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_FAMILY].size.x = 1600;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_FAMILY].size.y = 900;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_FAMILY].position.x = 0;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_FAMILY].position.y = 0;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_FAMILY].isVisible = 0;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_FAMILY].layer = LAYER_TOP;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_FAMILY].imagePath = TEXT("images/stage1/S1ghost.bmp");


	// TRAMPALINE
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TRAMPALINE].printType = TYPE_BASE;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TRAMPALINE].size.x = 350;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TRAMPALINE].size.y = 150;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TRAMPALINE].position.x = 700;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TRAMPALINE].position.y = 730;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TRAMPALINE].isVisible = 1;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TRAMPALINE].layer = LAYER_BOTTOM;

	// RIDES
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_RIDES].printType = TYPE_BASE;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_RIDES].size.x = 170;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_RIDES].size.y = 220;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_RIDES].position.x = 889;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_RIDES].position.y = 433;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_RIDES].isVisible = 1;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_RIDES].layer = LAYER_BOTTOM;

	// CRAWBAR
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_CRAWBAR].printType = TYPE_BASE;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_CRAWBAR].size.x = 50;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_CRAWBAR].size.y = 50;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_CRAWBAR].position.x = 0;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_CRAWBAR].position.y = 800;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_CRAWBAR].isVisible = 0;

	// EMPTYBOX
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_EMPTYBOX].printType = TYPE_BASE;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_EMPTYBOX].size.x = 100;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_EMPTYBOX].size.y = 100;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_EMPTYBOX].position.x = 0;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_EMPTYBOX].position.y = 800;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_EMPTYBOX].isVisible = 1;

	// GHOST
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_GHOST].printType = TYPE_TRANSPARENT;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_GHOST].size.x = 150;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_GHOST].size.y = 400;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_GHOST].position.x = 680;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_GHOST].position.y = 120;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_GHOST].isVisible = 0;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_GHOST].layer = LAYER_MID;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_GHOST].imagePath = TEXT("images/stage1/S1_Ghost.bmp");

	// PHOTOCLOSEUP
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_PHOTOCLOSEUP].printType = TYPE_TRANSPARENT;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_PHOTOCLOSEUP].size.x = 500;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_PHOTOCLOSEUP].size.y = 500;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_PHOTOCLOSEUP].position.x = 550;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_PHOTOCLOSEUP].position.y = 200;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_PHOTOCLOSEUP].isVisible = 0;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_PHOTOCLOSEUP].layer = LAYER_TOP;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_PHOTOCLOSEUP].imagePath = TEXT("images/stage1/Stage1PhotoCloseUp.bmp");

	// TEXTBOX
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].printType = TYPE_ALPHABLEND | TYPE_TEXT;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].blendFunction.BlendOp = 0;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].blendFunction.BlendFlags = 0;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].blendFunction.AlphaFormat = 0;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].blendFunction.SourceConstantAlpha = 220;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].size.x = 1100;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].size.y = 300;
	//objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].position.x = 335;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].position.y = 755;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].textBoxSize.x = 1600;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].textBoxSize.y = 900;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].textBoxPos.x = 0;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].textBoxPos.y = 0;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].imagePos.x = 300;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].imagePos.y = 725;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 0;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].text = NULL;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].layer = LAYER_TOP;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].imagePath = TEXT("images/test1.bmp");

	// BIGFACE
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_BIGFACE].printType = TYPE_TRANSPARENT;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_BIGFACE].size.x = 1600;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_BIGFACE].size.y = 900;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_BIGFACE].position.x = 0;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_BIGFACE].position.y = 0;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_BIGFACE].isVisible = 0;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_BIGFACE].layer = LAYER_TOP;
	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_BIGFACE].imagePath = TEXT("images/stage1/bigface.bmp");


	SoundPlayer_Play(SOUND_BGM_MAIN);
}


//mainScene�� ���� scene�� ��� update�� �����Ѵ�.
void LivingRoomScene_Update(float deltaTime)
{
	familyAppearTime += deltaTime;
	// FAMILY�� ������ 2�ʰ� ������ ������� ���
	if (familyCount == 1)
	{
		familyAppearTime += deltaTime;

		if (objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_FAMILY].isVisible == 1)
		{
			if (familyAppearTime > 2.0f)
			{
				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_FAMILY].isVisible = 0;
			}
			else
			{
				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_FAMILY].blendFunction.SourceConstantAlpha = (BYTE)(150.0f - (150.0f / 2.0f) * familyAppearTime);
			}
		}
	}
	// 	if (objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_FAMILY].isVisible == 1 && familyAppearTime >= 2.0f)
	// 	{
	// 		objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_FAMILY].isVisible = 0;
	// 	}

		// BLACKSCREEN ���̵� �ƿ�
	if (blackCount >= 4)
	{
		blackDisappear += deltaTime;

		if (objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_BLACKSCREEN].isVisible == 1)
		{
			if (blackDisappear > 1.5f)
			{
				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_BLACKSCREEN].isVisible = 0;
			}
			else
			{
				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_BLACKSCREEN].blendFunction.SourceConstantAlpha = (BYTE)(255.0f - (255.0f / 1.5f) * blackDisappear);
			}
		}

		//if (objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_BLACKSCREEN].isVisible == 1 && blackDisappear >= 1.5f )
		//{
		//	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_BLACKSCREEN].blendFunction.SourceConstantAlpha = 0;
		//}
		//
		//else if (objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_BLACKSCREEN].isVisible == 1 && blackDisappear >= 1.2f)
		//{
		//	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_BLACKSCREEN].blendFunction.SourceConstantAlpha = 50;
		//}

		//else if (objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_BLACKSCREEN].isVisible == 1 && blackDisappear >= 0.9f)
		//{
		//	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_BLACKSCREEN].blendFunction.SourceConstantAlpha = 100;
		//}

		//else if (objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_BLACKSCREEN].isVisible == 1 && blackDisappear >= 0.6f)
		//{
		//	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_BLACKSCREEN].blendFunction.SourceConstantAlpha = 150;
		//}

		//else if (objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_BLACKSCREEN].isVisible == 1 && blackDisappear >= 0.3f)
		//{
		//	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_BLACKSCREEN].blendFunction.SourceConstantAlpha = 200;
		//}

		//if (objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_BLACKSCREEN].blendFunction.SourceConstantAlpha == 0)
		//{
		//	objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_BLACKSCREEN].isVisible = 0;
		//}

	}


	bigfaceAppearTime += deltaTime;

	// BIGFACE �˾��ϰ� 3�� ������ ���� ���� ���
	if (bigfaceAppearTime >= 2.0f && objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_BIGFACE].isVisible == 1)
	{
		Scene_ChangeScene(SCENE_ID_GAMEOVER);
	}


	// ����ȭ���� �Ѿ������ 1�ʵڿ� �ؽ�Ʈ ���
	currentGameTime = clock();

	if (outOnce == 1 && currentGameTime - startGame >= 1000)
	{
		SoundPlayer_Play(SOUND_EFFECT_DOORCLOSE);

		objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;

		objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("!!!");

		outOnce = 0;
	}


	// ��Ŭ����
	if (Input_GetMouseLeftDownNow())
	{
		// Ŭ�� �г�Ƽ ���
		GameTimer_SubPenaltyTime();

		SoundPlayer_Play(SOUND_EFFECT_BUTTON);

		//��Ŭ���� ������Ʈ�� ��ǥ���� �޴´�
		int clickedObject = LivingRoomScene_ClickedObject(Input_GetMouseLeftDownPosition());

		// ����ȭ��
		if (clickedObject == LIVINGROOMSCENE_GAMEOBJECT_ID_BLACKSCREEN)
		{
			blackCount++;
			//objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;
			//blackDisappear += deltaTime;



// 			if (blackCount == 1)
// 			{
// 				SoundPlayer_Play(SOUND_EFFECT_DOORCLOSE);
// 
// 				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;
// 
// 				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("!!!");
// 			}


			if (blackCount == 1)
			{
				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;

				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("���� �� �Ҹ��� �Բ� ������ ������.");
			}

			else if (blackCount == 2)
			{
				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;

				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("??? : ����, �̰� �� �ڱ� �ڴ�� �����°ž�?!\n\n���ڱ� ���ĵ� ������, ������ �� ��Ҹ� �鸮����?");
			}

			else if (blackCount == 3)
			{
				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;

				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("���� ����� ������ ��ܹ��� �� ����.\n\n���۽����� ��Ȳ�� �������� ���尨���� �������� ���� Ÿ�� �帥��.");
			}

			else if (blackCount == 4)
			{
				blackDisappear = 0.0f;

				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;
				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("�Ա��� ������ ���� �� �����־� ���� ���� ����δ�.\n\n�ϴ� �ֺ��� �����ϸ� �� ���� �������� ����� ã�ƺ����� ����.");

				//objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_BLACKSCREEN].isVisible = 0;
			}
		}

		// ������
		else if (clickedObject == LIVINGROOMSCENE_GAMEOBJECT_ID_DRAWER && objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_PHOTOCLOSEUP].isVisible == 0)
		{
			SoundPlayer_Play(SOUND_EFFECT_STAGE1DRAWER);

			drawerCount++;

			objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;

			objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("�������� ��ġ�Ǿ� �ſ� ������ �������̴�.\n\n�ȿ��� �ƹ��͵� ���� �� ����.");

			if (drawerCount >= 2)
			{
				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("�ƹ��͵� ���� ���� �������̴�.");
			}

		}

		// ����
		else if (clickedObject == LIVINGROOMSCENE_GAMEOBJECT_ID_PHOTO && objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_PHOTOCLOSEUP].isVisible == 0)
		{
			photoCount++;
			if (photoCount == 1)
			{
				SoundPlayer_Play(SOUND_EFFECT_PHOTOCLOSEUP);

				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;

				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("�ͼ��� ������ ���������̴�. �̻��ϰ� ��ġ���ִ� �����ε��� ������ ���δ�.");
			}
			else if (photoCount >= 2)
			{
				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;


				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("...");
			}

			objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_PHOTOCLOSEUP].isVisible = 1;

			objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_PHOTO].imagePath = TEXT("images/stage1/stage1Photo.bmp");
		}
		// ���� Ȯ�� (Ȯ��� �������� ���� Ŭ���ϸ� ������Ʈ�� ������� ���� ���� �ʿ�!(���� ��))
// 		else if (clickedObject == LIVINGROOMSCENE_GAMEOBJECT_ID_PHOTOCLOSEUP)
// 		{
// 			closeupCount++;
// 
// 			objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;
// 
// 			/*objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("�ͼ��� ������ ���������̴�. �̻��ϰ� ��ġ���ִ� �����ε��� ������ ���δ�.");*/
// 
// // 			if (closeupCount >= 2)
// // 			{
// // 				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("...");
// // 			}
// 		}

		else if (objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible == 0 && objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_PHOTOCLOSEUP].isVisible == 1 && clickedObject != LIVINGROOMSCENE_GAMEOBJECT_ID_PHOTOCLOSEUP)
		{
			objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_PHOTOCLOSEUP].isVisible = 0;
		}


		// ��
		else if (clickedObject == LIVINGROOMSCENE_GAMEOBJECT_ID_DOOR && objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_PHOTOCLOSEUP].isVisible == 0)
		{
			doorCount++;

			objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;

			if (doorCount == 1 && objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_EMPTYBOX].isVisible == 1)
			{
				SoundPlayer_Play(SOUND_EFFECT_LOCKEDDOOR);

				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("���� �ɼ谡 ���峪�� ������ �ʴ´�.\n\n���𰡷� ������ �νø� ������ �� �� ���� �� ����.");
			}

			else if (doorCount == 1 && objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_CRAWBAR].isVisible == 1)
			{
				SoundPlayer_Play(SOUND_EFFECT_CRAWBAR);

				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("����� ���� �ɼ踦 ������ �ν���.\n\n���� �̵��� �� ���� �� ����.");

				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_CRAWBAR].isVisible = 0;

			}

			else if (doorCount >= 2 && objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_EMPTYBOX].isVisible == 1)
			{
				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("�μ����� ���𰡰� �ʿ���.");
			}

			// ���� ȹ���
			else if (doorCount >= 2 && objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_CRAWBAR].isVisible == 1)
			{
				SoundPlayer_Play(SOUND_EFFECT_CRAWBAR);

				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("����� ���� �ɼ踦 ������ �ν���. ���� �̵��� �� ���� �� ����.\n\n�ٸ� �浵 �ѷ�����.");

				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_CRAWBAR].isVisible = 0;
			}

			// �� �� ���� ���������� �Ѿ�� ���
			else if (doorCount >= 2 && objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_CRAWBAR].isVisible == 0 && objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_EMPTYBOX].isVisible == 0)
			{
				SoundPlayer_Play(SOUND_EFFECT_DOOROPEN);

				SoundPlayer_StopAllBGM();

				GameTimer_AddExtraTime();
				Scene_ChangeScene(SCENE_ID_FIRSTINNERROOM);
			}
		}

		// ����
		else if (clickedObject == LIVINGROOMSCENE_GAMEOBJECT_ID_SOFA && objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_PHOTOCLOSEUP].isVisible == 0)
		{
			sofaCount++;

			familyCount++;

			familyAppearTime = 0.0f;

			objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;

			objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("�����ΰ� ��ħ�� ����� ���.\n\n�� ���� �� ȥ�ڰ� �ƴ� ���� ����...");

			objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_FAMILY].isVisible = 1;

			if (sofaCount == 1)
			{
				SoundPlayer_Play(SOUND_EFFECT_SOFAGHOST);
			}

			if (sofaCount >= 2)
			{
				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("�������� ��ġ�� ���� ���Ĵ�.");
			}

			if (familyCount >= 2)
			{
				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_FAMILY].isVisible = 0;
			}
		}


		// Ʈ���޸�
		else if (clickedObject == LIVINGROOMSCENE_GAMEOBJECT_ID_TRAMPALINE && objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_PHOTOCLOSEUP].isVisible == 0)
		{
			SoundPlayer_Play(SOUND_EFFECT_MOVINGOBJECT);

			trampalineCount++;

			objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;

			objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("�ſ� ���� ���� ��ġ�� ���� Ʈ���޸��̴�.\n\n�ؿ� �����ΰ� �ִ°� ����. Ȯ���غ���.");

			// ��Ŭ���� ���� ŉ��
			if (trampalineCount == 2)
			{
				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_CRAWBAR].isVisible = 1;

				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_EMPTYBOX].isVisible = 0;

				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_GHOST].isVisible = 1;

				SoundPlayer_Play(SOUND_EFFECT_GHOST1);

				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("Ʈ���޸� �ؿ��� '����'�� ȹ���Ͽ���.");
			}

			if (trampalineCount >= 3)
			{
				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("Ʈ���޸����� �� �̻� Ȯ���� ���� ���� �� ����.");
			}
		}

		// ���̱ⱸ
		else if (clickedObject == LIVINGROOMSCENE_GAMEOBJECT_ID_RIDES && objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_PHOTOCLOSEUP].isVisible == 0)
		{
			SoundPlayer_Play(SOUND_EFFECT_MOVINGOBJECT);

			rideCount++;

			objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;

			objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("�������� ��ġ�� ���� ���̵��� Ÿ�� ��� ����� �̲���Ʋ�̴�.\n\n���� Ȯ���� ���� ���� �� ����.");

			if (rideCount >= 2)
			{
				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("�̲���Ʋ���� �� �̻� Ȯ�� �� ���� ���� �� ����.");
			}
		}

		else if (clickedObject == LIVINGROOMSCENE_GAMEOBJECT_ID_GHOST && objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_PHOTOCLOSEUP].isVisible == 0)
		{
			ghostCount++;

			if (ghostCount == 1)
			{
				bigfaceAppearTime = 0.0f;

				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_BIGFACE].isVisible = 1;

				SoundPlayer_Play(SOUND_EFFECT_STAGE1BIGFACE);
			}

		}



		// �ؽ�Ʈ�ڽ��� �� ���� ������ Ŭ���ϸ�, �ؽ�Ʈ�ڽ��� ������� ���
		else
		{
			objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 0;
		}
	}
}

void LivingRoomScene_Render()
{
	// isVisible : true�� ȭ���� ���, false�� �����
	// layer : 0, 1, 2, 3������ ȭ���� ���
	for (int i = 0; i < LAYER_SIZE; i++)
	{
		for (int j = 0; j < LIVINGROOMSCENE_GAMEOBJECT_SIZE; j++)
		{
			// layer�� isVisible�� ���� �Ǵ��� �Ѵ�
			if (objectL[j].isVisible == 1 && objectL[j].layer == i)
			{
				//GDIEngine_Rectangle(objectL[j].position.x, objectL[j].position.y, objectL[j].size.x, objectL[j].size.y);
				//GDIEngine_PrintObjectText(objectL[j]);
				GDIEngine_PrintObject(objectL[j]);
			}
		}
	}
}

// mousePos ��ġ�� ������Ʈ�� ��ȣ(object �迭������ �ε���)�� ��ȯ�Ѵ�.
// ���� ������Ʈ�� Ŭ������ �ʾҴٸ� -1�� �����Ѵ�.
int LivingRoomScene_ClickedObject(POINT mousePos)
{
	int result = -1;
	int maxLayer = -1;

	for (int i = 0; i < 12; i++)
	{
		int objVisible = objectL[i].isVisible;
		int objPosX1 = objectL[i].position.x;
		int objPosY1 = objectL[i].position.y;
		int objPosX2 = objectL[i].position.x + objectL[i].size.x;
		int objPosY2 = objectL[i].position.y + objectL[i].size.y;

		// �Ѱܹ��� ���콺�� ��ǥ�� ���� � ���� ������Ʈ�� Ŭ�� ������� �Ǵ��Ͽ� �����Ѵ�
		if (objVisible == 1 && objPosX1 < mousePos.x && mousePos.x < objPosX2 && objPosY1 < mousePos.y && mousePos.y < objPosY2)
		{
			if (maxLayer < objectL[i].layer)
			{
				result = i;
				maxLayer = objectL[i].layer;
			}
		}
	}

	return result;
}
