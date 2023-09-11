#include "LivingRoomScene.h"
#include "GDIEngine.h"
#include "Scene.h"
#include "GameObject.h"
#include "Input.h"
#include "SoundPlayer.h"
#include "GameTimer.h"
#include <time.h>
// 스테이지1 거실



// 시작부터 놓여있는 오브젝트들
#define LIVINGROOMSCENE_GAMEOBJECT_ID_BACKGROUND 0
#define LIVINGROOMSCENE_GAMEOBJECT_ID_BLACKSCREEN 1 
#define LIVINGROOMSCENE_GAMEOBJECT_ID_DRAWER 2 
#define LIVINGROOMSCENE_GAMEOBJECT_ID_PHOTO 3 
#define LIVINGROOMSCENE_GAMEOBJECT_ID_DOOR 4 
#define LIVINGROOMSCENE_GAMEOBJECT_ID_SOFA 5
#define LIVINGROOMSCENE_GAMEOBJECT_ID_TRAMPALINE 6 
#define LIVINGROOMSCENE_GAMEOBJECT_ID_RIDES 7

// 따로 팝업되는 오브젝트들
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

//카운트명 선언
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

//sceneList에 mainScene을 담고 mainScene의 함수 포인터들을 초기화(함수의 주소값을 담는다) 한다.
void LivingRoomScene_Ready()
{
	sceneList[SCENE_ID_LIVINGROOM] = &livingScene;
	livingScene.func_init = LivingRoomScene_Init;
	livingScene.func_update = LivingRoomScene_Update;
	livingScene.func_render = LivingRoomScene_Render;
}

//scene 전환이 됬을 때, 해당 scene의 초기화
void LivingRoomScene_Init()
{
	// 게임 타이머 시작
	GameTimer_GameStart();

	startGame = clock();

	// 클릭마다 증가하는 카운트 초기화 
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

	// 모든 오브젝트의 X,Y division과 imageNumber 초기화
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
	// 가족사진 좌표....
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
	// PHOTO랑 뭐가 다른가요..??
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


//mainScene이 현재 scene인 경우 update를 진행한다.
void LivingRoomScene_Update(float deltaTime)
{
	familyAppearTime += deltaTime;
	// FAMILY가 등장후 2초가 지난후 사라지는 기능
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

		// BLACKSCREEN 페이드 아웃
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

	// BIGFACE 팝업하고 3초 지나면 게임 오버 기능
	if (bigfaceAppearTime >= 2.0f && objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_BIGFACE].isVisible == 1)
	{
		Scene_ChangeScene(SCENE_ID_GAMEOVER);
	}


	// 게임화면이 넘어간다음에 1초뒤에 텍스트 출력
	currentGameTime = clock();

	if (outOnce == 1 && currentGameTime - startGame >= 1000)
	{
		SoundPlayer_Play(SOUND_EFFECT_DOORCLOSE);

		objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;

		objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("!!!");

		outOnce = 0;
	}


	// 좌클릭시
	if (Input_GetMouseLeftDownNow())
	{
		// 클릭 패널티 계산
		GameTimer_SubPenaltyTime();

		SoundPlayer_Play(SOUND_EFFECT_BUTTON);

		//좌클릭한 오브젝트의 좌표값을 받는다
		int clickedObject = LivingRoomScene_ClickedObject(Input_GetMouseLeftDownPosition());

		// 검은화면
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

				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("문이 쾅 소리와 함께 스스로 닫혔다.");
			}

			else if (blackCount == 2)
			{
				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;

				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("??? : 뭐야, 이거 왜 자기 멋대로 닫히는거야?!\n\n갑자기 전파도 안잡혀, 여러분 제 목소리 들리세요?");
			}

			else if (blackCount == 3)
			{
				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;

				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("문을 열어보려 했지만 잠겨버린 것 같다.\n\n갑작스러운 상황에 공포감과 긴장감으로 식은땀이 몸을 타고 흐른다.");
			}

			else if (blackCount == 4)
			{
				blackDisappear = 0.0f;

				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;
				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("입구도 막히고 모든게 다 막혀있어 나갈 길이 없어보인다.\n\n일단 주변을 조사하며 이 방을 빠져나갈 방법을 찾아보도록 하자.");

				//objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_BLACKSCREEN].isVisible = 0;
			}
		}

		// 서랍장
		else if (clickedObject == LIVINGROOMSCENE_GAMEOBJECT_ID_DRAWER && objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_PHOTOCLOSEUP].isVisible == 0)
		{
			SoundPlayer_Play(SOUND_EFFECT_STAGE1DRAWER);

			drawerCount++;

			objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;

			objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("오랫동안 방치되어 매우 더러운 서럽장이다.\n\n안에는 아무것도 없는 것 같다.");

			if (drawerCount >= 2)
			{
				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("아무것도 없는 낡은 서랍장이다.");
			}

		}

		// 사진
		else if (clickedObject == LIVINGROOMSCENE_GAMEOBJECT_ID_PHOTO && objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_PHOTOCLOSEUP].isVisible == 0)
		{
			photoCount++;
			if (photoCount == 1)
			{
				SoundPlayer_Play(SOUND_EFFECT_PHOTOCLOSEUP);

				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;

				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("익숙한 느낌의 가족사진이다. 이상하게 방치되있던 사진인데도 멀쩡해 보인다.");
			}
			else if (photoCount >= 2)
			{
				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;


				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("...");
			}

			objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_PHOTOCLOSEUP].isVisible = 1;

			objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_PHOTO].imagePath = TEXT("images/stage1/stage1Photo.bmp");
		}
		// 사진 확대 (확대된 사진영역 밖을 클릭하면 오브젝트가 사라지는 것을 구현 필요!(구현 완))
// 		else if (clickedObject == LIVINGROOMSCENE_GAMEOBJECT_ID_PHOTOCLOSEUP)
// 		{
// 			closeupCount++;
// 
// 			objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;
// 
// 			/*objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("익숙한 느낌의 가족사진이다. 이상하게 방치되있던 사진인데도 멀쩡해 보인다.");*/
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


		// 문
		else if (clickedObject == LIVINGROOMSCENE_GAMEOBJECT_ID_DOOR && objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_PHOTOCLOSEUP].isVisible == 0)
		{
			doorCount++;

			objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;

			if (doorCount == 1 && objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_EMPTYBOX].isVisible == 1)
			{
				SoundPlayer_Play(SOUND_EFFECT_LOCKEDDOOR);

				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("문의 걸쇠가 고장나서 열리지 않는다.\n\n무언가로 내리쳐 부시면 강제로 열 수 있을 것 같다.");
			}

			else if (doorCount == 1 && objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_CRAWBAR].isVisible == 1)
			{
				SoundPlayer_Play(SOUND_EFFECT_CRAWBAR);

				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("빠루로 문의 걸쇠를 내리쳐 부쉈다.\n\n이제 이동할 수 있을 것 같다.");

				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_CRAWBAR].isVisible = 0;

			}

			else if (doorCount >= 2 && objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_EMPTYBOX].isVisible == 1)
			{
				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("부술만한 무언가가 필요해.");
			}

			// 빠루 획득시
			else if (doorCount >= 2 && objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_CRAWBAR].isVisible == 1)
			{
				SoundPlayer_Play(SOUND_EFFECT_CRAWBAR);

				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("빠루로 문의 걸쇠를 내리쳐 부쉈다. 이제 이동할 수 있을 것 같다.\n\n다른 방도 둘러보자.");

				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_CRAWBAR].isVisible = 0;
			}

			// 이 후 다음 스테이지로 넘어가는 기능
			else if (doorCount >= 2 && objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_CRAWBAR].isVisible == 0 && objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_EMPTYBOX].isVisible == 0)
			{
				SoundPlayer_Play(SOUND_EFFECT_DOOROPEN);

				SoundPlayer_StopAllBGM();

				GameTimer_AddExtraTime();
				Scene_ChangeScene(SCENE_ID_FIRSTINNERROOM);
			}
		}

		// 소파
		else if (clickedObject == LIVINGROOMSCENE_GAMEOBJECT_ID_SOFA && objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_PHOTOCLOSEUP].isVisible == 0)
		{
			sofaCount++;

			familyCount++;

			familyAppearTime = 0.0f;

			objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;

			objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("무엇인가 음침한 기분이 든다.\n\n이 곳에 나 혼자가 아닌 듯한 느낌...");

			objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_FAMILY].isVisible = 1;

			if (sofaCount == 1)
			{
				SoundPlayer_Play(SOUND_EFFECT_SOFAGHOST);
			}

			if (sofaCount >= 2)
			{
				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("오랫동안 방치된 듯한 쇼파다.");
			}

			if (familyCount >= 2)
			{
				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_FAMILY].isVisible = 0;
			}
		}


		// 트램펄린
		else if (clickedObject == LIVINGROOMSCENE_GAMEOBJECT_ID_TRAMPALINE && objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_PHOTOCLOSEUP].isVisible == 0)
		{
			SoundPlayer_Play(SOUND_EFFECT_MOVINGOBJECT);

			trampalineCount++;

			objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;

			objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("매우 낡고 오래 방치된 듯한 트램펄린이다.\n\n밑에 무엇인가 있는것 같다. 확인해보자.");

			// 재클릭시 빠루 흭득
			if (trampalineCount == 2)
			{
				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_CRAWBAR].isVisible = 1;

				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_EMPTYBOX].isVisible = 0;

				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_GHOST].isVisible = 1;

				SoundPlayer_Play(SOUND_EFFECT_GHOST1);

				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("트램펄린 밑에서 '빠루'를 획득하였다.");
			}

			if (trampalineCount >= 3)
			{
				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("트램펄린에는 더 이상 확인할 것이 없는 것 같다.");
			}
		}

		// 놀이기구
		else if (clickedObject == LIVINGROOMSCENE_GAMEOBJECT_ID_RIDES && objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_PHOTOCLOSEUP].isVisible == 0)
		{
			SoundPlayer_Play(SOUND_EFFECT_MOVINGOBJECT);

			rideCount++;

			objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;

			objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("오랫동안 방치된 듯한 아이들이 타고 노는 평범한 미끄럼틀이다.\n\n딱히 확인할 것은 없는 것 같다.");

			if (rideCount >= 2)
			{
				objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("미끄럼틀에는 더 이상 확인 할 것이 없는 것 같다.");
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



		// 텍스트박스와 그 외의 영역을 클릭하면, 텍스트박스가 사라지는 기능
		else
		{
			objectL[LIVINGROOMSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 0;
		}
	}
}

void LivingRoomScene_Render()
{
	// isVisible : true면 화면을 출력, false면 비출력
	// layer : 0, 1, 2, 3순으로 화면을 출력
	for (int i = 0; i < LAYER_SIZE; i++)
	{
		for (int j = 0; j < LIVINGROOMSCENE_GAMEOBJECT_SIZE; j++)
		{
			// layer와 isVisible에 대한 판단을 한다
			if (objectL[j].isVisible == 1 && objectL[j].layer == i)
			{
				//GDIEngine_Rectangle(objectL[j].position.x, objectL[j].position.y, objectL[j].size.x, objectL[j].size.y);
				//GDIEngine_PrintObjectText(objectL[j]);
				GDIEngine_PrintObject(objectL[j]);
			}
		}
	}
}

// mousePos 위치의 오브젝트의 번호(object 배열에서의 인덱스)를 반환한다.
// 만약 오브젝트가 클릭되지 않았다면 -1을 리턴한다.
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

		// 넘겨받은 마우스의 좌표에 따라서 어떤 게임 오브젝트가 클릭 됬는지를 판단하여 리턴한다
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
