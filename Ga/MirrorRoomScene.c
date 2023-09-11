#include "MirrorRoomScene.h"
#include "GDIEngine.h"
#include "Scene.h"
#include "GameObject.h"
#include "Input.h"
#include "SoundPlayer.h"
#include "GameTimer.h"

#define MIRRORSCENE_GAMEOBJECT_ID_BACKGROUND 0
#define MIRRORSCENE_GAMEOBJECT_ID_MIRROR 1
#define MIRRORSCENE_GAMEOBJECT_ID_PENTAGRAM 2

#define MIRRORSCENE_GAMEOBJECT_ID_GHOST01 3
#define MIRRORSCENE_GAMEOBJECT_ID_GHOST02 4
#define MIRRORSCENE_GAMEOBJECT_ID_GHOST03 5
#define MIRRORSCENE_GAMEOBJECT_ID_GHOST04 6

#define MIRRORSCENE_GAMEOBJECT_ID_TEXTBOX 7

#define MIRRORSCENE_GAMEOBJECT_ID_CUTSCENE01 8
#define MIRRORSCENE_GAMEOBJECT_ID_CUTSCENE02 9
#define MIRRORSCENE_GAMEOBJECT_ID_CUTSCENE03 10
#define MIRRORSCENE_GAMEOBJECT_ID_CUTSCENE04 11

#define MIRRORSCENE_GAMEOBJECT_ID_MAINCHARACTERBACK 12
#define MIRRORSCENE_GAMEOBJECT_ID_MAINCHARACTERFRONT 13

#define MIRRORSCENE_GAMEOBJECT_ID_GAMEOVERIMAGE 14

#define MIRRORSCENE_GAMEOBJECT_ID_CENTERTEXT01 15
#define MIRRORSCENE_GAMEOBJECT_ID_CENTERTEXT02 16

#define MIRRORSCENE_GAMEOBJECT_ID_BLACKSCREEN 17

#define MIRRORSCENE_GAMEOBJECT_SIZE 18

Scene mirrorScene;

GameObject mirrorScene_object[MIRRORSCENE_GAMEOBJECT_SIZE];
int mirrorScene_clickCount[MIRRORSCENE_GAMEOBJECT_SIZE];

int mirrorScene_lastMouseLeftDownObject;
int mirrorScene_lastMouseLeftUpObject;

enum mirrorScene_state
{
	STATE_READY,
	STATE_RUNNING_GHOST,
	STATE_RUNNING_CUTSCENE01,
	STATE_RUNNING_CUTSCENE02,
	STATE_RUNNING_CUTSCENE03,
	STATE_RUNNING_CUTSCENE04,
	STATE_RUNNING_MAINCHARACTER_BACK,
	STATE_RUNNING_MAINCHARACTER_BACK_CLOSEUP,
	STATE_RUNNING_MAINCHARACTER_FRONT,
	STATE_RUNNING_GAMEOVER,
	STATE_RUNNING_FIRSTMIRROR,
	STATE_RUNNING_SECONDMIRROR,
	STATE_RUNNING_BLACKSCREEN
};

const int EVENT_ID_GHOST = STATE_RUNNING_GHOST;
const int EVENT_ID_CUTSCENE01 = STATE_RUNNING_CUTSCENE01;
const int EVENT_ID_CUTSCENE02 = STATE_RUNNING_CUTSCENE02;
const int EVENT_ID_CUTSCENE03 = STATE_RUNNING_CUTSCENE03;
const int EVENT_ID_CUTSCENE04 = STATE_RUNNING_CUTSCENE04;
const int EVENT_ID_MAINCHARACTER_BACK = STATE_RUNNING_MAINCHARACTER_BACK;
const int EVENT_ID_MAINCHARACTER_BACK_CLOSEUP = STATE_RUNNING_MAINCHARACTER_BACK_CLOSEUP;
const int EVENT_ID_MAINCHARACTER_FRONT = STATE_RUNNING_MAINCHARACTER_FRONT;
const int EVENT_ID_GAMEOVER = STATE_RUNNING_GAMEOVER;
const int EVENT_ID_FIRSTMIRROR = STATE_RUNNING_FIRSTMIRROR;
const int EVENT_ID_SECONDMIRROR = STATE_RUNNING_SECONDMIRROR;
const int EVENT_ID_BLACKSCREEN = STATE_RUNNING_BLACKSCREEN;

const float EVENT_DELAY_FIRSTMIRROR = 2.0f;
const float EVENT_DELAY_SECONDMIRROR = 2.0f;

const float EVENT_DELAY_GHOST = 0.0f;
const float EVENT_DELAY_CUTSCENE01 = 0.3f;
const float EVENT_DELAY_CUTSCENE02 = 0.3f;
const float EVENT_DELAY_CUTSCENE03 = 0.3f;
const float EVENT_DELAY_CUTSCENE04 = 0.3f;

const float EVENT_DELAY_MAINCHARACTER_BACK = 2.0f;
const float EVENT_DELAY_MAINCHARACTER_BACK_CLOSEUP = 3.0f;
const float EVENT_DELAY_MAINCHARACTER_FRONT = 2.0f;

const float EVENT_DELAY_BLACKSCREEN = 2.0f;

const float EVENT_DELAY_GAMEOVER = 1.0f;

const float MAINCHARACTER_CLOSEUP_SPEED = 0.2f;

int mirrorScene_currentState;
float mirrorScene_eventTimer;

// 우는 소리
int isCrying;
float mirrorScene_crySound_lastPlayTime;
const float CRYSOUND_PERIOD = 16.0f;

//sceneList에 mirrorScene을 담고 mirrorScene의 함수 포인터들을 초기화(함수의 주소값을 담는다) 한다.
void MirrorRoomScene_Ready()
{
	sceneList[SCENE_ID_MIRRORROOM] = &mirrorScene;
	mirrorScene.func_init = MirrorRoomScene_Init;
	mirrorScene.func_update = MirrorRoomScene_Update;
	mirrorScene.func_render = MirrorRoomScene_Render;
}

//scene 전환이 됬을 때, 해당 scene의 초기화
void MirrorRoomScene_Init()
{
	// 모든 오브젝트의 X,Y division과 imageNumber 초기화
	for (int i = 0; i < MIRRORSCENE_GAMEOBJECT_SIZE; i++)
	{
		mirrorScene_object[i].Xdivision = 1;
		mirrorScene_object[i].Ydivision = 1;
		mirrorScene_object[i].imageNumber = 0;
		mirrorScene_object[i].scalePivot.x = 0.0f;
		mirrorScene_object[i].scalePivot.y = 0.0f;
		mirrorScene_object[i].scale = 1.0f;
		mirrorScene_object[i].imagePos.x = 0;
		mirrorScene_object[i].imagePos.y = 0;
	}

	// 오브젝트들의 초기값 설정
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_BACKGROUND].printType = TYPE_TRANSPARENT;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_BACKGROUND].position.x = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_BACKGROUND].position.y = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_BACKGROUND].size.x = 1600;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_BACKGROUND].size.y = 900;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_BACKGROUND].isVisible = 1;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_BACKGROUND].imagePath = TEXT("images/BgNObj_Stage4_BMP.bmp");
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_BACKGROUND].layer = LAYER_BACKGROUND;

	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_MIRROR].printType = TYPE_BASE;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_MIRROR].position.x = 770;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_MIRROR].position.y = 340;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_MIRROR].size.x = 130;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_MIRROR].size.y = 230;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_MIRROR].isVisible = 1;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_MIRROR].layer = LAYER_BOTTOM;
	
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_PENTAGRAM].printType = TYPE_BASE;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_PENTAGRAM].position.x = 740;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_PENTAGRAM].position.y = 600;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_PENTAGRAM].size.x = 180;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_PENTAGRAM].size.y = 80;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_PENTAGRAM].isVisible = 1;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_PENTAGRAM].layer = LAYER_BOTTOM;

	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_GHOST04].printType = TYPE_TRANSPARENT;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_GHOST04].position.x = 150;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_GHOST04].position.y = 100;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_GHOST04].size.x = 80;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_GHOST04].size.y = 300;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_GHOST04].isVisible = 1;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_GHOST04].layer = LAYER_BOTTOM;

	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_GHOST03].printType = TYPE_TRANSPARENT;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_GHOST03].position.x = 500;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_GHOST03].position.y = 330;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_GHOST03].size.x = 80;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_GHOST03].size.y = 220;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_GHOST03].isVisible = 1;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_GHOST03].imagePath = TEXT("images/stage4/귀신실루엣.bmp");
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_GHOST03].layer = LAYER_BOTTOM;

	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_GHOST02].printType = TYPE_TRANSPARENT;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_GHOST02].position.x = 1100;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_GHOST02].position.y = 100;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_GHOST02].size.x = 80;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_GHOST02].size.y = 300;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_GHOST02].isVisible = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_GHOST02].layer = LAYER_BOTTOM;

	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_GHOST01].printType = TYPE_TRANSPARENT;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_GHOST01].position.x = 1350;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_GHOST01].position.y = 100;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_GHOST01].size.x = 80;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_GHOST01].size.y = 300;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_GHOST01].isVisible = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_GHOST01].layer = LAYER_BOTTOM;

	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CUTSCENE01].printType = TYPE_TRANSPARENT;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CUTSCENE01].position.x = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CUTSCENE01].position.y = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CUTSCENE01].size.x = 1600;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CUTSCENE01].size.y = 900;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CUTSCENE01].isVisible = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CUTSCENE01].imagePath = TEXT("images/stage4/4__1.bmp");
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CUTSCENE01].layer = LAYER_MID;

	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CUTSCENE02].printType = TYPE_TRANSPARENT;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CUTSCENE02].position.x = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CUTSCENE02].position.y = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CUTSCENE02].size.x = 1600;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CUTSCENE02].size.y = 900;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CUTSCENE02].isVisible = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CUTSCENE02].imagePath = TEXT("images/stage4/4__2.bmp");
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CUTSCENE02].layer = LAYER_MID;

	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CUTSCENE03].printType = TYPE_TRANSPARENT;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CUTSCENE03].position.x = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CUTSCENE03].position.y = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CUTSCENE03].size.x = 1600;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CUTSCENE03].size.y = 900;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CUTSCENE03].isVisible = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CUTSCENE03].imagePath = TEXT("images/stage4/4__3.bmp");
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CUTSCENE03].layer = LAYER_MID;

	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CUTSCENE04].printType = TYPE_TRANSPARENT;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CUTSCENE04].position.x = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CUTSCENE04].position.y = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CUTSCENE04].size.x = 1600;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CUTSCENE04].size.y = 900;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CUTSCENE04].isVisible = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CUTSCENE04].imagePath = TEXT("images/stage4/4__4.bmp");
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CUTSCENE04].layer = LAYER_MID;

	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_MAINCHARACTERBACK].printType = TYPE_TRANSPARENT;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_MAINCHARACTERBACK].position.x = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_MAINCHARACTERBACK].position.y = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_MAINCHARACTERBACK].size.x = 1600;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_MAINCHARACTERBACK].size.y = 900;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_MAINCHARACTERBACK].isVisible = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_MAINCHARACTERBACK].scalePivot.x = 800.0f;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_MAINCHARACTERBACK].scalePivot.y = 500.0f;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_MAINCHARACTERBACK].imagePath = TEXT("images/stage4/2.bmp");
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_MAINCHARACTERBACK].imageNumber = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_MAINCHARACTERBACK].layer = LAYER_MID;

	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_MAINCHARACTERFRONT].printType = TYPE_TRANSPARENT;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_MAINCHARACTERFRONT].position.x = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_MAINCHARACTERFRONT].position.y = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_MAINCHARACTERFRONT].size.x = 1600;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_MAINCHARACTERFRONT].size.y = 900;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_MAINCHARACTERFRONT].isVisible = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_MAINCHARACTERFRONT].scalePivot.x = 800.0f;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_MAINCHARACTERFRONT].scalePivot.y = 500.0f;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_MAINCHARACTERFRONT].imagePath = TEXT("images/stage4/1.bmp");
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_MAINCHARACTERFRONT].scale = 1.0f + MAINCHARACTER_CLOSEUP_SPEED * EVENT_DELAY_MAINCHARACTER_BACK_CLOSEUP;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_MAINCHARACTERFRONT].layer = LAYER_MID;

	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_GAMEOVERIMAGE].printType = TYPE_TRANSPARENT;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_GAMEOVERIMAGE].position.x = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_GAMEOVERIMAGE].position.y = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_GAMEOVERIMAGE].size.x = 1600;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_GAMEOVERIMAGE].size.y = 900;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_GAMEOVERIMAGE].isVisible = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_GAMEOVERIMAGE].imagePath = TEXT("images/stage4/점프스케어.bmp");
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_GAMEOVERIMAGE].layer = LAYER_TOP;

	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CENTERTEXT01].printType = TYPE_TRANSPARENT;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CENTERTEXT01].position.x = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CENTERTEXT01].position.y = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CENTERTEXT01].size.x = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CENTERTEXT01].size.y = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CENTERTEXT01].isVisible = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CENTERTEXT01].imagePath = TEXT("images/stage4/중앙출력텍스트이미지1.bmp");
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CENTERTEXT01].layer = LAYER_TOP;

	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CENTERTEXT02].printType = TYPE_TRANSPARENT;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CENTERTEXT02].position.x = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CENTERTEXT02].position.y = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CENTERTEXT02].size.x = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CENTERTEXT02].size.y = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CENTERTEXT02].isVisible = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CENTERTEXT02].imagePath = TEXT("images/stage4/중앙출력텍스트이미지2.bmp");
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CENTERTEXT02].layer = LAYER_TOP;
	
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_BLACKSCREEN].printType = TYPE_TRANSPARENT;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_BLACKSCREEN].position.x = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_BLACKSCREEN].position.y = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_BLACKSCREEN].size.x = 1600;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_BLACKSCREEN].size.y = 900;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_BLACKSCREEN].isVisible = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_BLACKSCREEN].imagePath = TEXT("images/stage4/blackscreen.bmp");
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_BLACKSCREEN].layer = LAYER_MID;


	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_TEXTBOX].printType = TYPE_TEXT | TYPE_ALPHABLEND;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_TEXTBOX].blendFunction.BlendOp = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_TEXTBOX].blendFunction.BlendFlags = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_TEXTBOX].blendFunction.AlphaFormat = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_TEXTBOX].blendFunction.SourceConstantAlpha = 220;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_TEXTBOX].position.x = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_TEXTBOX].position.y = 755;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_TEXTBOX].size.x = 1100;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_TEXTBOX].size.y = 300;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_TEXTBOX].textBoxPos.x = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_TEXTBOX].textBoxPos.y = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_TEXTBOX].textBoxSize.x = 1600;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_TEXTBOX].textBoxSize.y = 900;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_TEXTBOX].imagePos.x = 300;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_TEXTBOX].imagePos.y = 725;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("");
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_TEXTBOX].imagePath = TEXT("images/test1.bmp");
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_TEXTBOX].layer = LAYER_TOP;

	// 마우스 클릭에 대한 정보 초기화
	mirrorScene_lastMouseLeftDownObject = -1;
	mirrorScene_lastMouseLeftUpObject = -1;

	for (int i = 0; i < MIRRORSCENE_GAMEOBJECT_SIZE; i++)
	{
		mirrorScene_clickCount[i] = 0;
	}

	// 이벤트 진행상태 초기화
	mirrorScene_currentState = STATE_READY;

	// 우는 소리 초기화
	isCrying = 1;
	mirrorScene_crySound_lastPlayTime = CRYSOUND_PERIOD + 1.0f;

	// BGM 재생
	SoundPlayer_Play(SOUND_BGM_MAIN);
}

//mirrorScene이 현재 scene인 경우 update를 진행한다.
void MirrorRoomScene_Update(float deltaTime)
{
	mirrorScene_crySound_lastPlayTime += deltaTime;

	if (isCrying == 1 && mirrorScene_crySound_lastPlayTime > CRYSOUND_PERIOD)
	{
		mirrorScene_crySound_lastPlayTime = mirrorScene_crySound_lastPlayTime - CRYSOUND_PERIOD;
		SoundPlayer_Play(SOUND_EFFECT_STAGE4_WOMAN_CRYING);
	}

	mirrorRoomScene_playSceneEvent(deltaTime);

	// 마우스 왼쪽 버튼이 내려갔을 때
	if (Input_GetMouseLeftDownNow())
	{
		// 클릭 패널티 계산
		GameTimer_SubPenaltyTime();

		SoundPlayer_Play(SOUND_EFFECT_BUTTON);

		// 클릭한 위치를 저장한다.
		mirrorScene_lastMouseLeftDownObject = mirrorRoomScene_clickedObject(Input_GetMouseLeftDownPosition());
	}

	// 마우스 왼쪽 버튼이 올라올 때
	if (Input_GetMouseLeftUpNow())
	{
		// 클릭한 위치를 저장한다.
		mirrorScene_lastMouseLeftUpObject = mirrorRoomScene_clickedObject(Input_GetMouseLeftUpPosition());

		// 텍스트 박스가 켜져있다면 닫고, 그렇지 않다면 마우스가 클릭한 오브젝트를 판단하여 이벤트를 실행
		if (mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible == 1)
		{
			// textbox는 이벤트가 진행중이 아닐때만 제거한다.
			if (mirrorScene_currentState == STATE_READY)
			{
				mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 0;
			}
		}
		else
		{
			// 마우스가 특정 오브젝트를 클릭한 경우
			if (mirrorScene_lastMouseLeftUpObject != -1 && mirrorScene_lastMouseLeftDownObject == mirrorScene_lastMouseLeftUpObject)
			{
				// 다른 이벤트가 진행중이면서 귀신을 클릭한 것이 아니면 클릭 이벤트를 진행하지 않는다.
				if (!(mirrorScene_currentState != STATE_READY && mirrorScene_lastMouseLeftUpObject != MIRRORSCENE_GAMEOBJECT_ID_GHOST03))
				{
					// 오브젝트 클릭 이벤트를 진행
					mirrorRoomScene_objectClickEvent(mirrorScene_lastMouseLeftUpObject);
				}
			}
		}
	}
}

void MirrorRoomScene_Render()
{
	// isVisible : true면 화면을 출력, false면 비출력
	// layer : 0, 1, 2, 3순으로 화면을 출력
	for (int i = 0; i < LAYER_SIZE; i++)
	{
		for (int j = 0; j < MIRRORSCENE_GAMEOBJECT_SIZE; j++)
		{
			// layer와 isVisible에 대한 판단을 한다
			if (mirrorScene_object[j].isVisible == 1 && mirrorScene_object[j].layer == i)
			{
				GDIEngine_PrintObject(mirrorScene_object[j]);
			}
		}
	}
}

// mousePos 위치의 오브젝트의 번호(object 배열에서의 인덱스)를 반환한다.
// 만약 오브젝트가 클릭되지 않았다면 -1을 리턴한다.
int mirrorRoomScene_clickedObject(POINT mousePos)
{
	int result = -1;
	int maxLayer = -1;

	for (int i = 0; i < MIRRORSCENE_GAMEOBJECT_SIZE; i++)
	{
		int objVisible = mirrorScene_object[i].isVisible;
		int objPosX1 = mirrorScene_object[i].position.x;
		int objPosY1 = mirrorScene_object[i].position.y;
		int objPosX2 = mirrorScene_object[i].position.x + mirrorScene_object[i].size.x;
		int objPosY2 = mirrorScene_object[i].position.y + mirrorScene_object[i].size.y;

		// 넘겨받은 마우스의 좌표에 따라서 어떤 게임 오브젝트가 클릭 됬는지를 판단하여 리턴한다
		if (objVisible == 1 && objPosX1 < mousePos.x && mousePos.x < objPosX2 && objPosY1 < mousePos.y && mousePos.y < objPosY2)
		{
			if (maxLayer < mirrorScene_object[i].layer)
			{
				result = i;
				maxLayer = mirrorScene_object[i].layer;
			}
		}
	}

	return result;
}

// 이벤트를 시작한다.
void mirrorRoomScene_startSceneEvent(int eventID, float defaultTimer)
{
	// Ready상태에서만 시작 가능한 이벤트
	if (mirrorScene_currentState == STATE_READY)
	{
		mirrorScene_currentState = eventID;

		if (eventID == EVENT_ID_GHOST)
		{
			SoundPlayer_StopAll();
			isCrying = 0;
		}
		else if (eventID == EVENT_ID_CUTSCENE01)
		{
			SoundPlayer_StopAll();
			SoundPlayer_Play(SOUND_EFFECT_STAGE4_CUTSCENE01);
			mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CUTSCENE01].isVisible = 1;
		}
		else if (eventID == EVENT_ID_CUTSCENE02)
		{
			SoundPlayer_StopAll();
			SoundPlayer_Play(SOUND_EFFECT_STAGE4_CUTSCENE02);
			mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CUTSCENE02].isVisible = 1;
		}
		else if (eventID == EVENT_ID_CUTSCENE03)
		{
			SoundPlayer_StopAll();
			SoundPlayer_Play(SOUND_EFFECT_STAGE4_CUTSCENE03);
			mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CUTSCENE03].isVisible = 1;
		}
		else if (eventID == EVENT_ID_CUTSCENE04)
		{
			SoundPlayer_StopAll();
			SoundPlayer_Play(SOUND_EFFECT_STAGE4_CUTSCENE04);
			mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CUTSCENE04].isVisible = 1;
		}
		else if (eventID == EVENT_ID_MAINCHARACTER_BACK)
		{
			SoundPlayer_StopAll();
			SoundPlayer_Play(SOUND_EFFECT_STAGE4_CLOSEUP);
			mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_MAINCHARACTERBACK].isVisible = 1;
		}
		else if (eventID == EVENT_ID_MAINCHARACTER_BACK_CLOSEUP)
		{
			mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_MAINCHARACTERBACK].isVisible = 1;
		}
		else if (eventID == EVENT_ID_MAINCHARACTER_FRONT)
		{
			SoundPlayer_StopAll();
			SoundPlayer_Play(SOUND_EFFECT_STAGE4_FRONT);
			mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_MAINCHARACTERFRONT].isVisible = 1;
		}
		else if (eventID == EVENT_ID_FIRSTMIRROR)
		{
			mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CENTERTEXT01].isVisible = 1;
		}
		else if (eventID == EVENT_ID_SECONDMIRROR)
		{
			mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CENTERTEXT02].isVisible = 1;
		}
		else if (eventID == EVENT_ID_BLACKSCREEN)
		{
			mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("기억나버렸다....");
			mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;
			mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_BLACKSCREEN].isVisible = 1;
		}

		mirrorScene_eventTimer = defaultTimer;
	}
	
	// 상태에 상관없는 이벤트
	if (eventID == EVENT_ID_GAMEOVER)
	{
		mirrorScene_currentState = eventID;

		SoundPlayer_StopAll();
		SoundPlayer_Play(SOUND_EFFECT_GHOSTJUMPSCARE);
		mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CENTERTEXT01].isVisible = 0;
		mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CENTERTEXT02].isVisible = 0;
		mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_GAMEOVERIMAGE].isVisible = 1;

		mirrorScene_eventTimer = defaultTimer;
	}
}

// 이벤트를 진행한다.
void mirrorRoomScene_playSceneEvent(float deltaTime)
{
	mirrorScene_eventTimer += deltaTime;

	if (mirrorScene_currentState != STATE_READY)
	{
		if (mirrorScene_currentState == EVENT_ID_GHOST)
		{
			if (mirrorScene_eventTimer > EVENT_DELAY_GHOST)
			{
				mirrorScene_currentState = STATE_READY;
				mirrorRoomScene_startSceneEvent(EVENT_ID_CUTSCENE04, mirrorScene_eventTimer - EVENT_DELAY_GHOST);
			}
		}
		else if (mirrorScene_currentState == EVENT_ID_CUTSCENE01)
		{
			if (mirrorScene_eventTimer > EVENT_DELAY_CUTSCENE01)
			{
				mirrorScene_currentState = STATE_READY;
				mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CUTSCENE01].isVisible = 0;
				mirrorRoomScene_startSceneEvent(EVENT_ID_MAINCHARACTER_BACK, mirrorScene_eventTimer - EVENT_DELAY_CUTSCENE01);
			}
		}
		else if (mirrorScene_currentState == EVENT_ID_CUTSCENE02)
		{
			if (mirrorScene_eventTimer > EVENT_DELAY_CUTSCENE02)
			{
				mirrorScene_currentState = STATE_READY;
				mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CUTSCENE02].isVisible = 0;
				mirrorRoomScene_startSceneEvent(EVENT_ID_CUTSCENE01, mirrorScene_eventTimer - EVENT_DELAY_CUTSCENE02);
			}
		}
		else if (mirrorScene_currentState == EVENT_ID_CUTSCENE03)
		{
			if (mirrorScene_eventTimer > EVENT_DELAY_CUTSCENE03)
			{
				mirrorScene_currentState = STATE_READY;
				mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CUTSCENE03].isVisible = 0;
				mirrorRoomScene_startSceneEvent(EVENT_ID_CUTSCENE02, mirrorScene_eventTimer - EVENT_DELAY_CUTSCENE03);
			}
		}
		else if (mirrorScene_currentState == EVENT_ID_CUTSCENE04)
		{
			if (mirrorScene_eventTimer > EVENT_DELAY_CUTSCENE04)
			{
				mirrorScene_currentState = STATE_READY;
				mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CUTSCENE04].isVisible = 0;
				mirrorRoomScene_startSceneEvent(EVENT_ID_CUTSCENE03, mirrorScene_eventTimer - EVENT_DELAY_CUTSCENE04);
			}
		}
		else if (mirrorScene_currentState == EVENT_ID_MAINCHARACTER_BACK)
		{
			if (mirrorScene_eventTimer > EVENT_DELAY_MAINCHARACTER_BACK)
			{
				mirrorScene_currentState = STATE_READY;
				mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_MAINCHARACTERBACK].isVisible = 0;
				mirrorRoomScene_startSceneEvent(EVENT_ID_MAINCHARACTER_BACK_CLOSEUP, mirrorScene_eventTimer - EVENT_DELAY_MAINCHARACTER_BACK);
			}
		}
		else if (mirrorScene_currentState == EVENT_ID_MAINCHARACTER_BACK_CLOSEUP)
		{
			// closeUp
			mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_MAINCHARACTERBACK].scale += MAINCHARACTER_CLOSEUP_SPEED * deltaTime;

			if (mirrorScene_eventTimer > EVENT_DELAY_MAINCHARACTER_BACK_CLOSEUP)
			{
				mirrorScene_currentState = STATE_READY;
				mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_MAINCHARACTERBACK].isVisible = 0;
				mirrorRoomScene_startSceneEvent(EVENT_ID_MAINCHARACTER_FRONT, mirrorScene_eventTimer - EVENT_DELAY_MAINCHARACTER_BACK_CLOSEUP);
			}
		}
		else if (mirrorScene_currentState == EVENT_ID_MAINCHARACTER_FRONT)
		{
			if (mirrorScene_eventTimer > EVENT_DELAY_MAINCHARACTER_FRONT)
			{
				mirrorScene_currentState = STATE_READY;

				mirrorRoomScene_startSceneEvent(EVENT_ID_BLACKSCREEN, mirrorScene_eventTimer - EVENT_DELAY_MAINCHARACTER_FRONT);
			}
		}
		else if (mirrorScene_currentState == EVENT_ID_GAMEOVER)
		{
			if (mirrorScene_eventTimer > EVENT_DELAY_GAMEOVER)
			{
				Scene_ChangeScene(SCENE_ID_GAMEOVER);
			}
		}
		else if (mirrorScene_currentState == EVENT_ID_FIRSTMIRROR)
		{
			if (mirrorScene_eventTimer > EVENT_DELAY_FIRSTMIRROR)
			{
				mirrorScene_currentState = STATE_READY;
				mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CENTERTEXT01].isVisible = 0;
				mirrorRoomScene_startSceneEvent(EVENT_ID_SECONDMIRROR, mirrorScene_eventTimer - EVENT_DELAY_FIRSTMIRROR);
			}
		}
		else if (mirrorScene_currentState == EVENT_ID_SECONDMIRROR)
		{
			if (mirrorScene_eventTimer > EVENT_DELAY_SECONDMIRROR)
			{
				mirrorScene_currentState = STATE_READY;
				mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CENTERTEXT02].isVisible = 0;
			}
		}
		else if (mirrorScene_currentState == EVENT_ID_BLACKSCREEN)
		{
			if (mirrorScene_eventTimer > EVENT_DELAY_BLACKSCREEN)
			{
				mirrorScene_currentState = STATE_READY;
				mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_BLACKSCREEN].isVisible = 0;

				SoundPlayer_StopAll();
				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				// 게임엔딩씬으로 이동하도록 수정 필요
				Scene_ChangeScene(SCENE_ID_ENDING);
			}
		}
	}
}

// 오브젝트를 클릭할 시 발생하는 이벤트를 진행한다.
void mirrorRoomScene_objectClickEvent(int objectID)
{
	if (objectID == MIRRORSCENE_GAMEOBJECT_ID_MIRROR)
	{
		if (mirrorScene_clickCount[MIRRORSCENE_GAMEOBJECT_ID_PENTAGRAM] == 0 || mirrorScene_clickCount[MIRRORSCENE_GAMEOBJECT_ID_MIRROR] == 0)
		{
			mirrorRoomScene_startSceneEvent(EVENT_ID_FIRSTMIRROR, 0.0f);
		}
		else
		{
			GameTimer_GameEnd();
			mirrorRoomScene_startSceneEvent(EVENT_ID_GHOST, 0.0f);
		}
	}
	else if (objectID == MIRRORSCENE_GAMEOBJECT_ID_PENTAGRAM)
	{
		mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("기괴하지만 신비로운 느낌의 문양이 바닥에 그려져있다.\n\n보고있으니 이질감 때문에 몸이 마비되는 느낌이 든다.");
		mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;
	}
	else if (objectID == MIRRORSCENE_GAMEOBJECT_ID_GHOST01)
	{
		mirrorRoomScene_startSceneEvent(EVENT_ID_GAMEOVER, 0.0f);
	}
	else if (objectID == MIRRORSCENE_GAMEOBJECT_ID_GHOST02)
	{
		mirrorRoomScene_startSceneEvent(EVENT_ID_GAMEOVER, 0.0f);
	}
	else if (objectID == MIRRORSCENE_GAMEOBJECT_ID_GHOST03)
	{
		mirrorRoomScene_startSceneEvent(EVENT_ID_GAMEOVER, 0.0f);
	}
	else if (objectID == MIRRORSCENE_GAMEOBJECT_ID_GHOST04)
	{
		mirrorRoomScene_startSceneEvent(EVENT_ID_GAMEOVER, 0.0f);
	}

	mirrorScene_clickCount[objectID] += 1;
}