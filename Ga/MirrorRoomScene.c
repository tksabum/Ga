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

// ��� �Ҹ�
int isCrying;
float mirrorScene_crySound_lastPlayTime;
const float CRYSOUND_PERIOD = 16.0f;

//sceneList�� mirrorScene�� ��� mirrorScene�� �Լ� �����͵��� �ʱ�ȭ(�Լ��� �ּҰ��� ��´�) �Ѵ�.
void MirrorRoomScene_Ready()
{
	sceneList[SCENE_ID_MIRRORROOM] = &mirrorScene;
	mirrorScene.func_init = MirrorRoomScene_Init;
	mirrorScene.func_update = MirrorRoomScene_Update;
	mirrorScene.func_render = MirrorRoomScene_Render;
}

//scene ��ȯ�� ���� ��, �ش� scene�� �ʱ�ȭ
void MirrorRoomScene_Init()
{
	// ��� ������Ʈ�� X,Y division�� imageNumber �ʱ�ȭ
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

	// ������Ʈ���� �ʱⰪ ����
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
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_GHOST03].imagePath = TEXT("images/stage4/�ͽŽǷ翧.bmp");
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
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_GAMEOVERIMAGE].imagePath = TEXT("images/stage4/�������ɾ�.bmp");
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_GAMEOVERIMAGE].layer = LAYER_TOP;

	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CENTERTEXT01].printType = TYPE_TRANSPARENT;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CENTERTEXT01].position.x = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CENTERTEXT01].position.y = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CENTERTEXT01].size.x = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CENTERTEXT01].size.y = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CENTERTEXT01].isVisible = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CENTERTEXT01].imagePath = TEXT("images/stage4/�߾�����ؽ�Ʈ�̹���1.bmp");
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CENTERTEXT01].layer = LAYER_TOP;

	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CENTERTEXT02].printType = TYPE_TRANSPARENT;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CENTERTEXT02].position.x = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CENTERTEXT02].position.y = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CENTERTEXT02].size.x = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CENTERTEXT02].size.y = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CENTERTEXT02].isVisible = 0;
	mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_CENTERTEXT02].imagePath = TEXT("images/stage4/�߾�����ؽ�Ʈ�̹���2.bmp");
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

	// ���콺 Ŭ���� ���� ���� �ʱ�ȭ
	mirrorScene_lastMouseLeftDownObject = -1;
	mirrorScene_lastMouseLeftUpObject = -1;

	for (int i = 0; i < MIRRORSCENE_GAMEOBJECT_SIZE; i++)
	{
		mirrorScene_clickCount[i] = 0;
	}

	// �̺�Ʈ ������� �ʱ�ȭ
	mirrorScene_currentState = STATE_READY;

	// ��� �Ҹ� �ʱ�ȭ
	isCrying = 1;
	mirrorScene_crySound_lastPlayTime = CRYSOUND_PERIOD + 1.0f;

	// BGM ���
	SoundPlayer_Play(SOUND_BGM_MAIN);
}

//mirrorScene�� ���� scene�� ��� update�� �����Ѵ�.
void MirrorRoomScene_Update(float deltaTime)
{
	mirrorScene_crySound_lastPlayTime += deltaTime;

	if (isCrying == 1 && mirrorScene_crySound_lastPlayTime > CRYSOUND_PERIOD)
	{
		mirrorScene_crySound_lastPlayTime = mirrorScene_crySound_lastPlayTime - CRYSOUND_PERIOD;
		SoundPlayer_Play(SOUND_EFFECT_STAGE4_WOMAN_CRYING);
	}

	mirrorRoomScene_playSceneEvent(deltaTime);

	// ���콺 ���� ��ư�� �������� ��
	if (Input_GetMouseLeftDownNow())
	{
		// Ŭ�� �г�Ƽ ���
		GameTimer_SubPenaltyTime();

		SoundPlayer_Play(SOUND_EFFECT_BUTTON);

		// Ŭ���� ��ġ�� �����Ѵ�.
		mirrorScene_lastMouseLeftDownObject = mirrorRoomScene_clickedObject(Input_GetMouseLeftDownPosition());
	}

	// ���콺 ���� ��ư�� �ö�� ��
	if (Input_GetMouseLeftUpNow())
	{
		// Ŭ���� ��ġ�� �����Ѵ�.
		mirrorScene_lastMouseLeftUpObject = mirrorRoomScene_clickedObject(Input_GetMouseLeftUpPosition());

		// �ؽ�Ʈ �ڽ��� �����ִٸ� �ݰ�, �׷��� �ʴٸ� ���콺�� Ŭ���� ������Ʈ�� �Ǵ��Ͽ� �̺�Ʈ�� ����
		if (mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible == 1)
		{
			// textbox�� �̺�Ʈ�� �������� �ƴҶ��� �����Ѵ�.
			if (mirrorScene_currentState == STATE_READY)
			{
				mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 0;
			}
		}
		else
		{
			// ���콺�� Ư�� ������Ʈ�� Ŭ���� ���
			if (mirrorScene_lastMouseLeftUpObject != -1 && mirrorScene_lastMouseLeftDownObject == mirrorScene_lastMouseLeftUpObject)
			{
				// �ٸ� �̺�Ʈ�� �������̸鼭 �ͽ��� Ŭ���� ���� �ƴϸ� Ŭ�� �̺�Ʈ�� �������� �ʴ´�.
				if (!(mirrorScene_currentState != STATE_READY && mirrorScene_lastMouseLeftUpObject != MIRRORSCENE_GAMEOBJECT_ID_GHOST03))
				{
					// ������Ʈ Ŭ�� �̺�Ʈ�� ����
					mirrorRoomScene_objectClickEvent(mirrorScene_lastMouseLeftUpObject);
				}
			}
		}
	}
}

void MirrorRoomScene_Render()
{
	// isVisible : true�� ȭ���� ���, false�� �����
	// layer : 0, 1, 2, 3������ ȭ���� ���
	for (int i = 0; i < LAYER_SIZE; i++)
	{
		for (int j = 0; j < MIRRORSCENE_GAMEOBJECT_SIZE; j++)
		{
			// layer�� isVisible�� ���� �Ǵ��� �Ѵ�
			if (mirrorScene_object[j].isVisible == 1 && mirrorScene_object[j].layer == i)
			{
				GDIEngine_PrintObject(mirrorScene_object[j]);
			}
		}
	}
}

// mousePos ��ġ�� ������Ʈ�� ��ȣ(object �迭������ �ε���)�� ��ȯ�Ѵ�.
// ���� ������Ʈ�� Ŭ������ �ʾҴٸ� -1�� �����Ѵ�.
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

		// �Ѱܹ��� ���콺�� ��ǥ�� ���� � ���� ������Ʈ�� Ŭ�� ������� �Ǵ��Ͽ� �����Ѵ�
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

// �̺�Ʈ�� �����Ѵ�.
void mirrorRoomScene_startSceneEvent(int eventID, float defaultTimer)
{
	// Ready���¿����� ���� ������ �̺�Ʈ
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
			mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("��ﳪ���ȴ�....");
			mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;
			mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_BLACKSCREEN].isVisible = 1;
		}

		mirrorScene_eventTimer = defaultTimer;
	}
	
	// ���¿� ������� �̺�Ʈ
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

// �̺�Ʈ�� �����Ѵ�.
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
				// ���ӿ��������� �̵��ϵ��� ���� �ʿ�
				Scene_ChangeScene(SCENE_ID_ENDING);
			}
		}
	}
}

// ������Ʈ�� Ŭ���� �� �߻��ϴ� �̺�Ʈ�� �����Ѵ�.
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
		mirrorScene_object[MIRRORSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("�Ⱬ������ �ź�ο� ������ ������ �ٴڿ� �׷����ִ�.\n\n���������� ������ ������ ���� ����Ǵ� ������ ���.");
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