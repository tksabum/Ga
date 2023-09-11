#include "IntroScene.h"
#include "GDIEngine.h"
#include "Scene.h"
#include "GameObject.h"
#include "Input.h"
#include "SoundPlayer.h"
#include <time.h>

// 인트로

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

float newspaperText; // 신문지 자동텍스트
float black2Count;   // 검정화면2 자동텍스트


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

	// 알파블랜드용
	backgroundTime = 0.0f;
	newspaperTime = 0.0f;
	houseTime = 0.0f;



	// 시간차 텍스트 출력
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

	// 게임 시작 2초 후 화면 페이드아웃
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

	// 신문 클릭시 화면 페이드 아웃
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

				objectI[INTROSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("[ 2012년 11월 10일 발생한 미제의 화재로 5인 가족 사상 및 실종 사건 ]");
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

				objectI[INTROSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("[ 현재 2022년 11월10일 밤 11시 ]");
			}
		}
	}


	if (Input_GetMouseLeftDownNow())
	{
		SoundPlayer_Play(SOUND_EFFECT_BUTTON);

		//좌클릭한 오브젝트의 좌표값을 받는다
		int clickedObject = IntroScene_ClickedObject(Input_GetMouseLeftDownPosition());


		// 배경화면을 클릭시 신문지 팝업
		if (clickedObject == INTROSCENE_GAMEOBJECT_ID_BACKGROUND)
		{
			backgroundCount++;

			//backgroundTime = 0.0f;
		}





		// 신문지 클릭시 폐가 등장
		if (clickedObject == INTROSCENE_GAMEOBJECT_ID_NEWSPAPER)
		{
			newspaperCount++;

			//newspaperText = 0.0f;


			objectI[INTROSCENE_GAMEOBJECT_ID_LADDER].isVisible = 1;

		
			if (newspaperCount == 1)
			{
				objectI[INTROSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;

				objectI[INTROSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("화재로 인해 4명이 사망하고 1명은 실종된 미스테리한 사건이다.");
			}
			else if (newspaperCount == 2)
			{
				objectI[INTROSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;

				objectI[INTROSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("그런데 최근 들어 그곳에서 밤마다 수상한 소리와 함께 이상한 현상이 일어난다는 소문이 돌고 있다.");
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
// 				objectI[INTROSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("[ 현재 2022년 11월10일 밤 11시 ]");
// 			}

			if (blackscreenCount == 1)
			{
				objectI[INTROSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;

				objectI[INTROSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("??? : 오늘 방송 콘텐츠는 바로 이 폐가 체험입니다!\n\n 여러분, 구독과 좋아요 한 번씩 눌러주세요~");
			}

			else if (blackscreenCount == 2)
			{
				objectI[INTROSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;

				objectI[INTROSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("??? : 입구부터 위압감이 엄청난데... \n\n그래도 시간 끌 것 없이 일단 바로 들어가보겠습니다!");
			}

			else
			{
				objectI[INTROSCENE_GAMEOBJECT_ID_BLACKSCREEN2].isVisible = 0;
				objectI[INTROSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 0;
				objectI[INTROSCENE_GAMEOBJECT_ID_HOUSE].isVisible = 1;
			}
		}

		// 폐가이미지에 있는 사다리 클릭시 스테이지 1 진입
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

				objectI[INTROSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("이상하게 익숙한 느낌이 물씬 드는데.. \n\n창문은 아무래도 들어가지 못하게 누군가 의도적으로 막아 놓은것 같다.");
			}

			else if (housetextCount == 2)
			{
				objectI[INTROSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;

				objectI[INTROSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("사다리를 통해 내부로 들어갈 수 있을 것 같다. \n\n저기 있는 사다리를 이용해보자.");
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
	// isVisible : true면 화면을 출력, false면 비출력
	// layer : 0, 1, 2, 3순으로 화면을 출력
	for (int i = 0; i < LAYER_SIZE; i++)
	{
		for (int j = 0; j < INTROSCENE_GAMEOBJECT_SIZE; j++)
		{
			// layer와 isVisible에 대한 판단을 한다
			if (objectI[j].isVisible == 1 && objectI[j].layer == i)
			{
				//GDIEngine_Rectangle(objectI[j].position.x, objectI[j].position.y, objectI[j].size.x, objectI[j].size.y);
				GDIEngine_PrintObject(objectI[j]);
				//GDIEngine_PrintObjectText(objectI[j]);
			}
		}
	}
}

// mousePos 위치의 오브젝트의 번호(object 배열에서의 인덱스)를 반환한다.
// 만약 오브젝트가 클릭되지 않았다면 -1을 리턴한다.
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

		// 넘겨받은 마우스의 좌표에 따라서 어떤 게임 오브젝트가 클릭 됬는지를 판단하여 리턴한다
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
