#include "FirstInnerRoomScene.h"
#include "GDIEngine.h"
#include "Scene.h"
#include "GameObject.h"
#include "Input.h"
#include "SoundPlayer.h"
#include "GameTimer.h"


// 스테이지2 안방1

// 처음부터 있는 애들
#define FIRSTINNERSCENE_GAMEOBJECT_ID_BACKGROUND 0
#define FIRSTINNERSCENE_GAMEOBJECT_ID_STUDENTRECORD 1
#define FIRSTINNERSCENE_GAMEOBJECT_ID_DIARY 2
#define FIRSTINNERSCENE_GAMEOBJECT_ID_PHOTO 3
#define FIRSTINNERSCENE_GAMEOBJECT_ID_BED 4

// 나중에 생기는
#define FIRSTINNERSCENE_GAMEOBJECT_ID_PAPER 5
#define FIRSTINNERSCENE_GAMEOBJECT_ID_GHOST 6
#define FIRSTINNERSCENE_GAMEOBJECT_ID_GHOSTPHOTO 7

#define FIRSTINNERSCENE_GAMEOBJECT_ID_CLOSEUPRECORD 8
#define FIRSTINNERSCENE_GAMEOBJECT_ID_CLOSEUPDIARY 9
#define FIRSTINNERSCENE_GAMEOBJECT_ID_CLOSEUPPHOTO 10
#define FIRSTINNERSCENE_GAMEOBJECT_ID_CLOSEUPPAPER 11
#define FIRSTINNERSCENE_GAMEOBJECT_ID_BEHINDTHEBED 12

#define FIRSTINNERSCENE_GAMEOBJECT_ID_TEXTBOX 13
#define FIRSTINNERSCENE_GAMEOBJECT_ID_CLOSEUPTEXT 14
#define FIRSTINNERSCENE_GAMEOBJECT_ID_JUMPSCARE 15

#define FIRSTINNERSCENE_GAMEOBJECT_SIZE 16

Scene firstInnerScene;

GameObject firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_SIZE];

int recordCount;
int diaryCount;
int framephotoCount;
int bedCount;
int paperCount;
int behindbedCount;

int photoCount;

int photoEvent;
int paperEvent;
int paperEventEnd;

int popupEvent;
int gameover;
int scenechange;
int gameclear;

float gameOverTime;


void FirstInnerRoomScene_Ready()
{
	sceneList[SCENE_ID_FIRSTINNERROOM] = &firstInnerScene;
	firstInnerScene.func_init = FirstInnerRoomScene_Init;
	firstInnerScene.func_update = FirstInnerRoomScene_Update;
	firstInnerScene.func_render = FirstInnerRoomScene_Render;
}

void FirstInnerRoomScene_Init()
{
	//GameTimer_GameStart();

	// 클릭마다 증가하는 카운트 초기화 
	recordCount = 0;
	diaryCount = 0;
	framephotoCount = 0;
	bedCount = 0;
	paperCount = 0;
	behindbedCount = 0;

	photoCount = 0;

	photoEvent = 0;
	paperEvent = 0;
	paperEventEnd = 0;
	popupEvent = 0;
	gameover = 0;
	gameclear = 0;

	gameOverTime = 0.0f;

	// gdi엔진에서 예외처리용..?
	for (int i = 0; i < FIRSTINNERSCENE_GAMEOBJECT_SIZE; i++)
	{
		firstInnerScene_object[i].Xdivision = 1;
		firstInnerScene_object[i].Ydivision = 1;
		firstInnerScene_object[i].imageNumber = 0;
		firstInnerScene_object[i].scalePivot.x = 0.0f;
		firstInnerScene_object[i].scalePivot.y = 0.0f;
		firstInnerScene_object[i].scale = 1.0f;
		firstInnerScene_object[i].imagePos.x = 0;
		firstInnerScene_object[i].imagePos.y = 0;
	}

	// BACKGROUND
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_BACKGROUND].printType = TYPE_TRANSPARENT;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_BACKGROUND].position.x = 0;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_BACKGROUND].position.y = 0;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_BACKGROUND].size.x = 1600;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_BACKGROUND].size.y = 900;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_BACKGROUND].isVisible = 1;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_BACKGROUND].layer = LAYER_BACKGROUND;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_BACKGROUND].imagePath = TEXT("images/stage2/Stage2_Background.bmp");

	// STUDENTRECORD
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_STUDENTRECORD].printType = TYPE_TRANSPARENT;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_STUDENTRECORD].position.x = 1138;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_STUDENTRECORD].position.y = 449;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_STUDENTRECORD].size.x = 100;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_STUDENTRECORD].size.y = 54;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_STUDENTRECORD].isVisible = 1;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_STUDENTRECORD].layer = LAYER_BOTTOM;

	// DIARY
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_DIARY].printType = TYPE_TRANSPARENT;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_DIARY].position.x = 801;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_DIARY].position.y = 331;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_DIARY].size.x = 89;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_DIARY].size.y = 64;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_DIARY].isVisible = 1;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_DIARY].layer = LAYER_BOTTOM;

	// PHOTO
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_PHOTO].position.x = 984;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_PHOTO].position.y = 101;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_PHOTO].size.x = 140;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_PHOTO].size.y = 187;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_PHOTO].isVisible = 1;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_PHOTO].layer = LAYER_BOTTOM;

	// BED
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_BED].position.x = 53;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_BED].position.y = 601;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_BED].size.x = 678;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_BED].size.y = 183;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_BED].isVisible = 1;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_BED].layer = LAYER_BOTTOM;


	// 나중에 나오는 오브젝트들

	// PAPER
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_PAPER].printType = TYPE_TRANSPARENT;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_PAPER].position.x = 470;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_PAPER].position.y = 600;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_PAPER].size.x = 135;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_PAPER].size.y = 40;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_PAPER].isVisible = 0;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_PAPER].layer = LAYER_MID;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_PAPER].imagePath = TEXT("images/stage2/stage2_paper.bmp");

	//GHOST
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_GHOST].printType = TYPE_TRANSPARENT;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_GHOST].position.x = 1079;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_GHOST].position.y = 500;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_GHOST].size.x = 203;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_GHOST].size.y = 250;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_GHOST].isVisible = 0;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_GHOST].layer = LAYER_MID;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_GHOST].imagePath = TEXT("images/stage2/stage2_ghost.bmp");


	// GHOSTPHOTO
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_GHOSTPHOTO].printType = TYPE_TRANSPARENT;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_GHOSTPHOTO].position.x = 0;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_GHOSTPHOTO].position.y = 0;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_GHOSTPHOTO].size.x = 1600;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_GHOSTPHOTO].size.y = 900;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_GHOSTPHOTO].isVisible = 0;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_GHOSTPHOTO].layer = LAYER_MID;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_GHOSTPHOTO].imagePath = TEXT("images/stage2/stage2_photo.bmp");

	// CLOSEUPRECORD
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_CLOSEUPRECORD].printType = TYPE_TRANSPARENT;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_CLOSEUPRECORD].position.x = 0;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_CLOSEUPRECORD].position.y = 0;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_CLOSEUPRECORD].size.x = 1600;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_CLOSEUPRECORD].size.y = 900;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_CLOSEUPRECORD].isVisible = 0;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_CLOSEUPRECORD].layer = LAYER_MID;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_CLOSEUPRECORD].imagePath = TEXT("images/stage2/stage2_closeuprecord.bmp");

	// CLOSEUPDIARY
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_CLOSEUPDIARY].printType = TYPE_TRANSPARENT;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_CLOSEUPDIARY].position.x = 0;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_CLOSEUPDIARY].position.y = 0;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_CLOSEUPDIARY].size.x = 1600;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_CLOSEUPDIARY].size.y = 900;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_CLOSEUPDIARY].isVisible = 0;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_CLOSEUPDIARY].layer = LAYER_MID;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_CLOSEUPDIARY].imagePath = TEXT("images/stage2/closeupDiary.bmp");

	// CLOSEUPPHOTO
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_CLOSEUPPHOTO].position.x = 700;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_CLOSEUPPHOTO].position.y = 50;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_CLOSEUPPHOTO].size.x = 200;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_CLOSEUPPHOTO].size.y = 300;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_CLOSEUPPHOTO].isVisible = 0;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_CLOSEUPPHOTO].layer = LAYER_MID;

	// CLOSEUPPAPER
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_CLOSEUPPAPER].printType = TYPE_TRANSPARENT;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_CLOSEUPPAPER].position.x = 0;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_CLOSEUPPAPER].position.y = 0;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_CLOSEUPPAPER].size.x = 1600;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_CLOSEUPPAPER].size.y = 900;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_CLOSEUPPAPER].isVisible = 0;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_CLOSEUPPAPER].layer = LAYER_TOP;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_CLOSEUPPAPER].imagePath = TEXT("images/stage2/stage2_closeuppaper.bmp");

	// UNDERTHEBED
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_BEHINDTHEBED].position.x = 0;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_BEHINDTHEBED].position.y = 453;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_BEHINDTHEBED].size.x = 727;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_BEHINDTHEBED].size.y = 386;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_BEHINDTHEBED].isVisible = 0;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_BEHINDTHEBED].layer = LAYER_TOP;

	// 중앙텍스트
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_CLOSEUPTEXT].printType = TYPE_TRANSPARENT;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_CLOSEUPTEXT].position.x = 0;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_CLOSEUPTEXT].position.y = 0;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_CLOSEUPTEXT].size.x = 1600;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_CLOSEUPTEXT].size.y = 900;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_CLOSEUPTEXT].isVisible = 0;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_CLOSEUPTEXT].layer = LAYER_TOP;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_CLOSEUPTEXT].imagePath = TEXT("images/stage2/stage2_text.bmp");

	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_JUMPSCARE].printType = TYPE_TRANSPARENT;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_JUMPSCARE].position.x = 0;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_JUMPSCARE].position.y = 0;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_JUMPSCARE].size.x = 1600;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_JUMPSCARE].size.y = 900;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_JUMPSCARE].isVisible = 0;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_JUMPSCARE].layer = LAYER_TOP;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_JUMPSCARE].imagePath = TEXT("images/stage2/stage2_jumpscare.bmp");


	// TEXTBOX
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_TEXTBOX].printType = TYPE_ALPHABLEND | TYPE_TEXT;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_TEXTBOX].blendFunction.BlendOp = 0;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_TEXTBOX].blendFunction.BlendFlags = 0;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_TEXTBOX].blendFunction.AlphaFormat = 0;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_TEXTBOX].blendFunction.SourceConstantAlpha = 220;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_TEXTBOX].size.x = 1100;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_TEXTBOX].size.y = 300;
	//firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_TEXTBOX].position.x = 420;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_TEXTBOX].position.y = 755;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_TEXTBOX].textBoxSize.x = 1600;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_TEXTBOX].textBoxSize.y = 900;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_TEXTBOX].textBoxPos.x = 0;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_TEXTBOX].textBoxPos.y = 0;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_TEXTBOX].imagePos.x = 300;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_TEXTBOX].imagePos.y = 725;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 0;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_TEXTBOX].text = NULL;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_TEXTBOX].layer = LAYER_TOP;
	firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_TEXTBOX].imagePath = TEXT("images/test1.bmp");

	SoundPlayer_Play(SOUND_BGM_MAIN);
}

void FirstInnerRoomScene_Update(float deltaTime)
{
	gameOverTime += deltaTime;

	if (gameOverTime >= 2.0f && gameover > 0)
	{
		Scene_ChangeScene(SCENE_ID_GAMEOVER);
	}

	if (Input_GetMouseLeftDownNow())
	{
		// 클릭 패널티 계산
		GameTimer_SubPenaltyTime();

		SoundPlayer_Play(SOUND_EFFECT_BUTTON);

		int clickedObject = FirstInnerRoomScene_ClickedObject(Input_GetMouseLeftDownPosition());

		if (clickedObject == FIRSTINNERSCENE_GAMEOBJECT_ID_STUDENTRECORD)
		{
			SoundPlayer_Play(SOUND_EFFECT_NEWSPAPER);

			recordCount = 1;

			firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_CLOSEUPRECORD].isVisible = 1;

			firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;
			firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("의문의 생활기록부이다. 정상적인 내용이 아니다.\n\n누군가 심하게 훼손해놓았다.");
		}

		else if (clickedObject == FIRSTINNERSCENE_GAMEOBJECT_ID_DIARY)
		{
			SoundPlayer_Play(SOUND_EFFECT_NEWSPAPER);

			diaryCount = 1;

			firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_CLOSEUPDIARY].isVisible = 1;

			firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;
			firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("어린 아이가 쓴 듯한 일기다.\n\n내용을 보아하니 가족 중에 누군가 심하게 병을 앓고 있던 거 같다.");
		}

		else if (clickedObject == FIRSTINNERSCENE_GAMEOBJECT_ID_PHOTO)
		{
			photoCount++;

			firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_CLOSEUPPHOTO].isVisible = 1;
			firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_STUDENTRECORD].isVisible = 1;

			firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;
			firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("사진이 나를 응시하는 듯한 느낌이 든다.\n\n내 착각일까?");

			if (recordCount == 1 && diaryCount == 1 && photoCount > 1)
			{
				SoundPlayer_Play(SOUND_EFFECT_PHOTOCHANGE);

				photoEvent++;

				firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_GHOSTPHOTO].isVisible = 1;


				firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;
				firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("뭐…뭐지?\n\n뭔가 달라진 것 같은데 잘못 본건가?");

				firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_GHOST].isVisible = 1;
				firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_PAPER].isVisible = 1;
			}
		}

		else if (clickedObject == FIRSTINNERSCENE_GAMEOBJECT_ID_BED)
		{
			bedCount++;

			if (bedCount == 1)
			{
				firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;
				firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("더럽고 낡은 침대이나 누군가 최근까지 있었던 것처럼 정돈되어 있다.");
			}

			else if (bedCount >= 1)
			{
				firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;
				firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("별 볼 일 없는 침대다.");
			}
		}

		//else if (clickedObject == FIRSTINNERSCENE_GAMEOBJECT_ID_PAPER)
		else if (clickedObject == FIRSTINNERSCENE_GAMEOBJECT_ID_PAPER && paperEventEnd == 0)
		{
			SoundPlayer_Play(SOUND_EFFECT_NEWSPAPER);

			firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_CLOSEUPPAPER].isVisible = 1;

			firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;
			firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_TEXTBOX].text = TEXT("원래 여기에 없었던거 같은데…\n\n이 쪽지는 뭐지?");

			paperEventEnd++;
		}

		else if (paperEventEnd == 1)
		{
			SoundPlayer_Play(SOUND_EFFECT_CLOSEUPTEXT);

			firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_CLOSEUPTEXT].isVisible = 1;
			firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_CLOSEUPPAPER].isVisible = 0;
			firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 0;

			paperEventEnd++;
			popupEvent = 1;
		}

		else if (popupEvent == 1)
		{
			firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_CLOSEUPTEXT].isVisible = 0;

			firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_BEHINDTHEBED].isVisible = 1;

			if (clickedObject == FIRSTINNERSCENE_GAMEOBJECT_ID_BEHINDTHEBED)
			{
				SoundPlayer_Play(SOUND_EFFECT_JUMPSCAREJ);

				firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_JUMPSCARE].isVisible = 1;
				gameclear++;
				popupEvent++;
			}

			else if (clickedObject == FIRSTINNERSCENE_GAMEOBJECT_ID_GHOST)
			{
				SoundPlayer_Play(SOUND_EFFECT_JUMPSCAREJ);

				gameOverTime = 0.0f;

				firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_JUMPSCARE].isVisible = 1;
				gameover++;
			}

			else
			{
				popupEvent = 1;
			}
		}

		else if (clickedObject == FIRSTINNERSCENE_GAMEOBJECT_ID_GHOST)
		{
			SoundPlayer_Play(SOUND_EFFECT_JUMPSCAREJ);

			gameOverTime = 0.0f;

			firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_JUMPSCARE].isVisible = 1;

			gameover++;
		}



		
		//else if (gameover == 1)
		//{
		//	Scene_ChangeScene(SCENE_ID_GAMEOVER);
		//}

		else if (gameclear == 1)
		{
			GameTimer_AddExtraTime();
			Scene_ChangeScene(SCENE_ID_SECONDINNERROOM);
		}

		// 텍스트박스 외의 영역을 클릭하면, 텍스트박스, 확대 이미지가 사라지는 기능
		else if (clickedObject != FIRSTINNERSCENE_GAMEOBJECT_ID_TEXTBOX)
		{
			firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_TEXTBOX].isVisible = 0;
			firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_CLOSEUPRECORD].isVisible = 0;
			firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_CLOSEUPDIARY].isVisible = 0;
			firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_CLOSEUPPAPER].isVisible = 0;
			firstInnerScene_object[FIRSTINNERSCENE_GAMEOBJECT_ID_CLOSEUPTEXT].isVisible = 0;
		}
	}
}

void FirstInnerRoomScene_Render()
{
	// isVisible : true면 화면을 출력, false면 비출력
	// layer : 0, 1, 2, 3순으로 화면을 출력
	for (int i = 0; i < LAYER_SIZE; i++)
	{
		for (int j = 0; j < FIRSTINNERSCENE_GAMEOBJECT_SIZE; j++)
		{
			// layer와 isVisible에 대한 판단을 한다
			if (firstInnerScene_object[j].isVisible == 1 && firstInnerScene_object[j].layer == i)
			{
				GDIEngine_PrintObject(firstInnerScene_object[j]);
			}
		}
	}
}

int FirstInnerRoomScene_ClickedObject(POINT mousePos)
{
	int result = -1;
	int maxLayer = -1;

	for (int i = 0; i < FIRSTINNERSCENE_GAMEOBJECT_SIZE; i++)
	{
		int objVisible = firstInnerScene_object[i].isVisible;
		int objPosX1 = firstInnerScene_object[i].position.x;
		int objPosY1 = firstInnerScene_object[i].position.y;
		int objPosX2 = firstInnerScene_object[i].position.x + firstInnerScene_object[i].size.x;
		int objPosY2 = firstInnerScene_object[i].position.y + firstInnerScene_object[i].size.y;

		// 넘겨받은 마우스의 좌표에 따라서 어떤 게임 오브젝트가 클릭 됬는지를 판단하여 리턴한다
		if (objVisible == 1 && objPosX1 < mousePos.x && mousePos.x < objPosX2 && objPosY1 < mousePos.y && mousePos.y < objPosY2)
		{
			if (maxLayer < firstInnerScene_object[i].layer)
			{
				result = i;
				maxLayer = firstInnerScene_object[i].layer;
			}
		}
	}

	return result;
}