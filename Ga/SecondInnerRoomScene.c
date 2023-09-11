#include "SecondInnerRoomScene.h"
#include "GDIEngine.h"
#include "Scene.h"
#include "GameObject.h"
#include "Input.h"
#include "SoundPlayer.h"
#include "GameTimer.h"
#include <time.h>



#define SecondInnerRoomScene_GAMEOBJECT_ID_BACKGROUND 0
#define SecondInnerRoomScene_GAMEOBJECT_ID_PRESCRIPTION 1 
#define SecondInnerRoomScene_GAMEOBJECT_ID_FOUR_DOLLS 2           // 한명이 부족한, 처음의 인형가족
#define SecondInnerRoomScene_GAMEOBJECT_ID_ONEDOLL_WITH_MSG 3 
#define SecondInnerRoomScene_GAMEOBJECT_ID_FIVE_DOLLS 4 
#define SecondInnerRoomScene_GAMEOBJECT_ID_GHOST 5     // 창문이 안 깨진 상태의 오브젝트

//////////////////////////////////////////////////////////////////////////// 바로 위에 꺼와 겹치는 쓸모없는 것인듯?
#define SecondInnerRoomScene_GAMEOBJECT_ID_GHOST_WITH_BROKEN_WINDOW 6     // 창문이 깨진 상태의 오브젝트  /////////////////////////

#define SecondInnerRoomScene_GAMEOBJECT_ID_CLOSET 7
#define SecondInnerRoomScene_GAMEOBJECT_ID_DOOR 8

#define SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_Prescription 9
#define SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_FOUR_DOLLS 10
#define SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_FOUR_DOLLS_LEFT_KNIFE 11
#define SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_ONEDOLL_WITH_MSG 12
#define SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_IN_CLOSET 13
#define SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_LAST_TEXT 14
#define SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_GHOST_FROM_BOTTOM 15


#define SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX 16

#define SecondInnerRoomScene_GAMEOBJECT_ID_FOUR_DOLLS_COMPLETE 17 // 플레이어의 노력으로 온가족이 완성된 인형무리
#define SecondInnerRoomScene_GAMEOBJECT_ID_BACKGROUND_WINDOW_BROKEN 18

#define SecondInnerRoomScene_GAMEOBJECT_SIZE 19

Scene secondInnerRoomScene;

GameObject secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_SIZE];

/// ///////////////////////////////////////////////////////////////////////////////////
// 초기화는 이곳에서 하면 안되고 init에서 해야한다

float startTime;   // 시작하자마자, 문 쾅 닫히고 3초 뒤에 텍스트 출력하기 위한 전역 변수
float currentTime;

int doItOnce;  // 맨 처음, 문이 쾅 닫히고 아무것도 안해도 텍스트 한 번 뜨게 해주기 위한 전역 변수

int doItOnce_ZoomInGhost; // 소녀 귀신의 확대된 사진이, 이 변수가 1일 때는 아래에서 쭉 올라오다가, 일정 좌표에 도달하면 0으로 바뀌어 멈춘다.

int getKnife;   // 인형무리와의 상호작용에서 커터칼을 획득했는 지 여부에 대한 전역 변수

int counter_DollWithMSG;  // 침대를 두 번 클릭했는지, 한번 클릭했는지, 그 여부를 알기 위해 카운트 하는 변수

int counter_FourDolls;  // 중앙 인형무리의 첫번째 상호작용인지, 두번째인지를 판단해주는 카운터

int getOneDollWithMsg;

int fiveSentence;

float forNextSceneTimeCount; // 마지막 중앙 텍스트 출력 후, 2초 뒤에 다음 미러룸 씬으로 넘어가게 하기 위한 시간 측정 변수
float gameOverAfterGhost; // 소녀귀신이 확대되어 등장하고, 2초 뒤에 게임오버씬이 나오게 하기위한 타임 카운트 변수
float silenceTimeCount;  // 5문장 연속 출력 뒤, "........" 텍스트가 나온 후의 시간을 재기 위한 전역변수
float ghostTimeCount;    // 옷장이 덜컹거린 뒤, 몇 초 뒤에 귀신을 등장시키기 위한 전역변수

int message; // 쪽지를 갖고 있는 지 없는 지, 확인하는 변수

int prescriptionCount; // 처방전의 2번째 클릭부터는, 텍스트 출력없이 확대사진만 나온다.

//sceneList에 secondInnerRoomScene을 담고 secondInnerRoomScene의 함수 포인터들을 초기화(함수의 주소값을 담는다) 한다.
void SecondInnerRoomScene_Ready()
{
	sceneList[SCENE_ID_SECONDINNERROOM] = &secondInnerRoomScene;
	secondInnerRoomScene.func_init = SecondInnerRoomScene_Init;
	secondInnerRoomScene.func_update = SecondInnerRoomScene_Update;
	secondInnerRoomScene.func_render = SecondInnerRoomScene_Render;
}


//scene 전환이 됬을 때, 해당 scene의 초기화
void SecondInnerRoomScene_Init()
{

	startTime = clock();


	doItOnce = 1;  // 맨 처음, 문이 쾅 닫히고 아무것도 안해도 텍스트 한 번 뜨게 해주기 위한 전역 변수

	doItOnce_ZoomInGhost = 1;

	getKnife = 0;   // 인형무리와의 상호작용에서 커터칼을 획득했는 지 여부에 대한 전역 변수

	counter_DollWithMSG = 0;  // 침대를 두 번 클릭했는지, 한번 클릭했는지, 그 여부를 알기 위해 카운트 하는 변수

	counter_FourDolls = 0;  // 중앙 인형무리의 첫번째 상호작용인지, 두번째인지를 판단해주는 카운터

	getOneDollWithMsg = 0;

	fiveSentence = 0;

	message = 0;

	prescriptionCount = 0;


	// 모든 오브젝트의 X,Y division과 imageNumber 초기화
	for (int i = 0; i < SecondInnerRoomScene_GAMEOBJECT_SIZE; i++)
	{
		secondInnerRoom_object[i].Xdivision = 1;
		secondInnerRoom_object[i].Ydivision = 1;
		secondInnerRoom_object[i].imageNumber = 0;		
		
		secondInnerRoom_object[i].scalePivot.x = 0.0f;  // 스케일은 이미지의 크기를 조절 할 수 있다.
		secondInnerRoom_object[i].scalePivot.y = 0.0f;	// scale기능이 필요하면 printType이 TRANSPARENT나 ALPHABLEND이어야 하고, scalePivot을 중심으로해서 scale값만큼 크기가 변화합니다
		secondInnerRoom_object[i].scale = 1.0;			// scale이 0.5면 크기가 절반.  2.0이면 두배가 된다.

		secondInnerRoom_object[i].imagePos.x = 0;  // 기본적으로 이미지가 0,0에서 나오는데 얘를 원하는 데로 설정함으로써 이미지가 나오는 위치를 조정할 수 있다. 
		secondInnerRoom_object[i].imagePos.y = 0;  // 기본적으로 이미지가 0,0에서 나오는데 얘를 원하는 데로 설정함으로써 이미지가 나오는 위치를 조정할 수 있다.
	}


	// 백그라운드 설정을 해놓았다.
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_BACKGROUND].printType = TYPE_TRANSPARENT;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_BACKGROUND].position.x = 0;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_BACKGROUND].position.y = 0;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_BACKGROUND].size.x = 1600;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_BACKGROUND].size.y = 900;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_BACKGROUND].isVisible = 1;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_BACKGROUND].layer = LAYER_BACKGROUND;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_BACKGROUND].imagePath = TEXT("images/stage3/stage3normal.bmp");

	// 소녀귀신이 확대될때, 창문 깨진 상태의 백그라운드 이미지
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_BACKGROUND_WINDOW_BROKEN].printType = TYPE_TRANSPARENT;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_BACKGROUND_WINDOW_BROKEN].position.x = 0;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_BACKGROUND_WINDOW_BROKEN].position.y = 0;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_BACKGROUND_WINDOW_BROKEN].size.x = 1600;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_BACKGROUND_WINDOW_BROKEN].size.y = 900;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_BACKGROUND_WINDOW_BROKEN].isVisible = 0;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_BACKGROUND_WINDOW_BROKEN].layer = LAYER_BACKGROUND;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_BACKGROUND_WINDOW_BROKEN].imagePath = TEXT("images/stage3/스테이지3_점프스케어가_나올때의_배경.bmp");

	//오른쪽 구석 처방전의 위치. 상호작용 가능한 박스를 만들었다.
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_PRESCRIPTION].printType = TYPE_BASE;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_PRESCRIPTION].position.x = 1303;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_PRESCRIPTION].position.y = 525;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_PRESCRIPTION].size.x = 101;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_PRESCRIPTION].size.y = 22;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_PRESCRIPTION].isVisible = 1;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_PRESCRIPTION].layer = LAYER_BOTTOM;

	/////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////      문은 안쓴다고 했음. 나중에 관련 코딩들 삭제 필요
	// 다음 스테이지를 위한 문의 위치.
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_DOOR].printType = TYPE_BASE;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_DOOR].position.x = 1500;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_DOOR].position.y = 400;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_DOOR].size.x = 100;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_DOOR].size.y = 100;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_DOOR].isVisible = 0;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_DOOR].layer = LAYER_BOTTOM;

	//방 중앙에 모여있는, 인형 4개의 위치, 인형이 하나 부족한 맨 처음의 모습
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_FOUR_DOLLS].printType = TYPE_BASE;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_FOUR_DOLLS].position.x = 761;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_FOUR_DOLLS].position.y = 728;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_FOUR_DOLLS].size.x = 159;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_FOUR_DOLLS].size.y = 99;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_FOUR_DOLLS].isVisible = 1;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_FOUR_DOLLS].layer = LAYER_BOTTOM;

	//방 왼쪽 침대 위에, 인형과 쪽지(메세지) 위치
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ONEDOLL_WITH_MSG].printType = TYPE_BASE;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ONEDOLL_WITH_MSG].position.x = 108;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ONEDOLL_WITH_MSG].position.y = 501;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ONEDOLL_WITH_MSG].size.x = 368;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ONEDOLL_WITH_MSG].size.y = 271;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ONEDOLL_WITH_MSG].isVisible = 1;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ONEDOLL_WITH_MSG].layer = LAYER_BOTTOM;

	//침대 위, 창가에 귀신.
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_GHOST].printType = TYPE_TRANSPARENT;  
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_GHOST].position.x = 0;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_GHOST].position.y = 90;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_GHOST].size.x = 150;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_GHOST].size.y = 350;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_GHOST].isVisible = 0;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_GHOST].layer = LAYER_BOTTOM;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_GHOST].imagePath = TEXT("images/stage3/S3_Ghost_include_background.bmp");


	//옷장. 게임이 일정 진행된 이후, 상호작용가능.   
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_CLOSET].printType = TYPE_TRANSPARENT; 
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_CLOSET].position.x = 642;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_CLOSET].position.y = 206;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_CLOSET].size.x = 362;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_CLOSET].size.y = 489;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_CLOSET].isVisible = 0;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_CLOSET].layer = LAYER_BOTTOM;

	// 표준 텍스트 박스 규정
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].printType = TYPE_TEXT | TYPE_ALPHABLEND;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].blendFunction.BlendOp = 0;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].blendFunction.BlendFlags = 0;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].blendFunction.AlphaFormat = 0;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].blendFunction.SourceConstantAlpha = 220;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].position.x = 0;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].position.y = 755;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].size.x = 1600;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].size.y = 300;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].textBoxPos.x = 0;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].textBoxPos.y = 0;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].textBoxSize.x = 1600;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].textBoxSize.y = 900;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].imagePos.x = 300;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].imagePos.y = 725;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].isVisible = 0;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].layer = LAYER_TOP;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].imagePath = TEXT("images/test1.bmp");


	// 상호작용을 하면, 화면 중앙에 뜰 처방전 확대 사진의 위치와 크기
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_Prescription].printType = TYPE_TRANSPARENT;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_Prescription].position.x = 510;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_Prescription].position.y = 70;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_Prescription].size.x = 570;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_Prescription].size.y = 780;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_Prescription].isVisible = 0;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_Prescription].layer = LAYER_MID;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_Prescription].imagePath = TEXT("images/stage3/진단서조정본2.bmp");


	// 상호작용을 하면, 화면 중앙에 뜰 인형무리 확대 사진의 위치와 크기
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_FOUR_DOLLS].printType = TYPE_TRANSPARENT;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_FOUR_DOLLS].position.x = 550;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_FOUR_DOLLS].position.y = 270;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_FOUR_DOLLS].size.x = 500;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_FOUR_DOLLS].size.y = 330;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_FOUR_DOLLS].isVisible = 0;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_FOUR_DOLLS].layer = LAYER_MID;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_FOUR_DOLLS].imagePath = TEXT("images/stage3/Obj_Fourdolls_2.bmp");


	// 다섯 마리의 온전한 인형무리
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_FIVE_DOLLS].printType = TYPE_TRANSPARENT;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_FIVE_DOLLS].position.x = 700;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_FIVE_DOLLS].position.y = 300;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_FIVE_DOLLS].size.x = 100;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_FIVE_DOLLS].size.y = 100;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_FIVE_DOLLS].isVisible = 0;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_FIVE_DOLLS].layer = LAYER_BOTTOM;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_FIVE_DOLLS].imagePath = TEXT("images/stage3/dolls.bmp");



	//////////////////////////////////////////////////////////////////////////                
	//////////////////////////////////////////////////////////////////////////                바로 위에 FIVE DOLLS 와 겹치는 거 같다..... 안 쓰는 거 같다
	//온전한 인형가족이 모인 사진
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_FOUR_DOLLS_COMPLETE].printType = TYPE_BASE;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_FOUR_DOLLS_COMPLETE].position.x = 600;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_FOUR_DOLLS_COMPLETE].position.y = 150;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_FOUR_DOLLS_COMPLETE].size.x = 400;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_FOUR_DOLLS_COMPLETE].size.y = 400;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_FOUR_DOLLS_COMPLETE].isVisible = 0;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_FOUR_DOLLS_COMPLETE].layer = LAYER_MID;

	// 줌인된 인형 가족 사진에서, 커터칼을 든 인형의 부분
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_FOUR_DOLLS_LEFT_KNIFE].printType = TYPE_BASE;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_FOUR_DOLLS_LEFT_KNIFE].position.x = 550;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_FOUR_DOLLS_LEFT_KNIFE].position.y = 270;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_FOUR_DOLLS_LEFT_KNIFE].size.x = 500;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_FOUR_DOLLS_LEFT_KNIFE].size.y = 330;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_FOUR_DOLLS_LEFT_KNIFE].isVisible = 0;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_FOUR_DOLLS_LEFT_KNIFE].layer = LAYER_TOP;

	// 확대된, 쪽지와 인형의 사진
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_ONEDOLL_WITH_MSG].printType = TYPE_TRANSPARENT;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_ONEDOLL_WITH_MSG].position.x = 400;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_ONEDOLL_WITH_MSG].position.y = 120;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_ONEDOLL_WITH_MSG].size.x = 850;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_ONEDOLL_WITH_MSG].size.y = 500;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_ONEDOLL_WITH_MSG].isVisible = 0;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_ONEDOLL_WITH_MSG].layer = LAYER_MID;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_ONEDOLL_WITH_MSG].imagePath = TEXT("images/stage3/stage3_인형쪽지확대씬.bmp");


	// 옷장을 클릭하면, 확대되어 나타나는 사진
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_IN_CLOSET].printType = TYPE_TRANSPARENT;  
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_IN_CLOSET].position.x = 400;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_IN_CLOSET].position.y = 200;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_IN_CLOSET].size.x = 770;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_IN_CLOSET].size.y = 450;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_IN_CLOSET].isVisible = 0;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_IN_CLOSET].layer = LAYER_MID;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_IN_CLOSET].imagePath = TEXT("images/stage3/Obj_Manphotoincloset.bmp");

	// 스테이지 마지막에 등장하는 텍스트 이미지
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_LAST_TEXT].printType = TYPE_TRANSPARENT;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_LAST_TEXT].position.x = 400;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_LAST_TEXT].position.y = 200;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_LAST_TEXT].size.x = 770;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_LAST_TEXT].size.y = 450;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_LAST_TEXT].isVisible = 0;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_LAST_TEXT].layer = LAYER_MID;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_LAST_TEXT].imagePath = TEXT("images/stage3/텍스트 확대씬.bmp");

	// 아래에서부터 올라오는, 귀신의 확대된 사진

	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_GHOST_FROM_BOTTOM].printType = TYPE_TRANSPARENT;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_GHOST_FROM_BOTTOM].position.x = 400;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_GHOST_FROM_BOTTOM].position.y = 200;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_GHOST_FROM_BOTTOM].size.x = 1600;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_GHOST_FROM_BOTTOM].size.y = 900;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_GHOST_FROM_BOTTOM].isVisible = 0;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_GHOST_FROM_BOTTOM].layer = LAYER_TOP;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_GHOST_FROM_BOTTOM].imagePath = TEXT("images/stage3/test4.bmp");
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_GHOST_FROM_BOTTOM].scale = 0.7f;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_GHOST_FROM_BOTTOM].imagePos.x = 200;  // 기본적으로 이미지가 0,0에서 나오는데 얘를 원하는 데로 설정함으로써 이미지가 나오는 위치를 조정할 수 있다. 
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_GHOST_FROM_BOTTOM].imagePos.y = 910;  // 이미지가 저 아래에서 100 까지만 올라와야한다.

	SoundPlayer_Play(SOUND_BGM_MAIN);

}

//secondInnerRoomScene이 현재 scene인 경우 update를 진행한다.
void SecondInnerRoomScene_Update(float deltaTime)
{
	currentTime = clock();

	silenceTimeCount += deltaTime;

	ghostTimeCount += deltaTime;

	gameOverAfterGhost += deltaTime;

	forNextSceneTimeCount += deltaTime;


	/// 마지막까지 확인하고 이 부분 주석은 지우자.
	////게임 화면이 시작되고 3초 뒤에 "들어오자마자 문이 쾅 하고 닫혔다. 더 이상 놀랍지도 않아." 텍스트 출력 + 문이 쾅 닫히는 소리
	//if (doItOnce == 1 && currentTime - startTime >= 2000)
	//{
	//	SoundPlayer_Play(SOUND_EFFECT_DOORCLOSE);

	//	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;
	//	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].text = TEXT("들어오자마자 문이 쾅 하고 닫혔다. 더 이상 놀랍지도 않아.");

	//	doItOnce = 0; // 더 이상 이 멘트가 계속 업데이트 되어, 화면에 그려지지 않도록 한다.
	//}


	//// ...... 이 출력 된 뒤, 2초 후에 옷장에서 덜컹 소리 및 긴장감 유발 BGM 나오고, 텍스트 출력
	//if (silenceTimeCount >= 2.0f && fiveSentence == 6)
	//{
	//	SoundPlayer_Play(SOUND_EFFECT_CLOSETSOUND);
	//	SoundPlayer_Play(SOUND_EFFECT_CLOSETSOUND2);

	//	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;
	//	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].text = TEXT("옷장에서 부스럭거리는 소리가 들린다. 아무래도 확인해보는 게 좋을 것 같다.");

	//	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_CLOSET].isVisible = 1;

	//	ghostTimeCount = 0.0f;

	//	fiveSentence = 7;

	//}

	if (fiveSentence == 6 && silenceTimeCount >= 2.0f)
	{
		SoundPlayer_Play(SOUND_EFFECT_CLOSETSOUND);
		SoundPlayer_Play(SOUND_EFFECT_CLOSETSOUND2);

		secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;
		secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].text = TEXT("옷장에서 부스럭거리는 소리가 들린다. 아무래도 확인해보는 게 좋을 것 같다.");
		
		secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_CLOSET].isVisible = 1;
		
		ghostTimeCount = 0.0f;

		fiveSentence = 7;
	}



	// 옷장에서 덜컹거리는 소리가 난 뒤, 3초 후에 창문깨지는 소리 + 귀신 등장
	if (ghostTimeCount >= 2.5f && fiveSentence == 7)
	{
		SoundPlayer_Play(SOUND_EFFECT_GLASSBREAK);

		secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_GHOST].isVisible = 1;

		fiveSentence = 8;

	}

	// 창가의 귀신을 클릭해서, 확대된 귀신이 visible로 상태가 바뀌면,
	if (doItOnce_ZoomInGhost == 1 && secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_GHOST_FROM_BOTTOM].isVisible == 1)
	{	
		// y좌표가 910부터 100까지, 즉 아래에서부터 쭈르륵 올라오게 한다.
		secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_GHOST_FROM_BOTTOM].imagePos.y = secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_GHOST_FROM_BOTTOM].imagePos.y - 5000*deltaTime;  

		// y좌표가 100보다 작거나 같다면, 좌표를 100으로 
		if (secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_GHOST_FROM_BOTTOM].imagePos.y <= 100)
		{
			doItOnce_ZoomInGhost = 0;
			secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_GHOST_FROM_BOTTOM].imagePos.y = 100;
			gameOverAfterGhost = 0.0f;
		}
	}

	// 소녀 귀신이 아래에서 다 올라오면, 2초 뒤 자동으로 게임오버 씬으로 전환한다.
	if (secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_GHOST_FROM_BOTTOM].imagePos.y == 100)
	{
		if (gameOverAfterGhost >= 1.5f)
		{
			Scene_ChangeScene(SCENE_ID_GAMEOVER);
		}
	}

	// 꼭 그랬어야만 했니?  텍스트 등장 후 2초 뒤에 다음 미러룸 씬으로 이동
	if (secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_LAST_TEXT].isVisible == 1)
	{
		if (forNextSceneTimeCount >= 3.0f)
		{
			GameTimer_AddExtraTime();
			Scene_ChangeScene(SCENE_ID_MIRRORROOM);
		}
	}

	// 화면이 처음 시작하고, 3초 뒤에 문이 쾅! 사운드를 내주고, 텍스트를 보여준다.
	if (doItOnce == 1 && currentTime - startTime >= 1000)
	{
		SoundPlayer_Play(SOUND_EFFECT_DOORCLOSE);

		secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;
		secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].text = TEXT("들어오자마자 문이 쾅 하고 닫혔다.\n\n더 이상 놀랍지도 않다.");

		doItOnce = 0; // 더 이상 이 멘트가 계속 업데이트 되어, 화면에 그려지지 않도록 한다.
	}


	// 처음 5초 동안은 어떠한 입력도 받지 못하게 한다. 바로 위의 텍스트가, 플레이어의 무의식적인 마우스 클릭 때문에 스킵되지 않도록 하기 위함이다.
	if (currentTime - startTime <= 3000)
	{
		
	}

	// 바로 위에 조건 값인 (currentTime - startTime) 값이, 바로 아래의 silenceTimeCount 조건 값보다 작다면, if와 else if 를 서로 바꿔줘야 한다.
	// 즉, 더 빡빡한 시간의 조건값을 가진 놈을 else if로 써야한다.
	else if (silenceTimeCount <= 3.0f)
	{

	}

	else if (Input_GetMouseLeftDownNow())
	{
		// 클릭 패널티 계산
		GameTimer_SubPenaltyTime();

		SoundPlayer_Play(SOUND_EFFECT_BUTTON);
		int clickedObject = SecondInnerRoomScene_ClickedObject(Input_GetMouseLeftDownPosition());

		// 화면에 줌인된 사진이 떠있는 경우
		// 화면에 줌인된 사진이 추가되면, 조건에 추가해줘야 한다 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		if (secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_Prescription].isVisible == 1 || secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_FOUR_DOLLS].isVisible == 1 || secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_FOUR_DOLLS_LEFT_KNIFE].isVisible == 1 || secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_ONEDOLL_WITH_MSG].isVisible == 1 || secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_IN_CLOSET].isVisible == 1 || secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_LAST_TEXT].isVisible == 1 || secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_GHOST_FROM_BOTTOM].isVisible == 1)
		{
			//텍스트박스가 화면에 보이는 경우,
			if (secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].isVisible == 1)
			{
				secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].isVisible = 0;
			}

			//텍스트박스가 화면에 보이지 않는 경우
			else
			{
				if (clickedObject == SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_FOUR_DOLLS_LEFT_KNIFE)
				{
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].text = TEXT("커터칼을 얻었다!");

					getKnife = 1;
					counter_FourDolls = 1;

					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_FOUR_DOLLS_LEFT_KNIFE].isVisible = 0;
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_FOUR_DOLLS].isVisible = 0;

				}

				else if (clickedObject == SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_ONEDOLL_WITH_MSG)
				{
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_ONEDOLL_WITH_MSG].isVisible = 0;
				}


				else if (clickedObject == SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_FOUR_DOLLS)
				{
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_FOUR_DOLLS].isVisible = 0;
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_FOUR_DOLLS_LEFT_KNIFE].isVisible = 0;
				}

				else if (clickedObject == SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_Prescription && prescriptionCount == 0)
				{
					SoundPlayer_Play(SOUND_EFFECT_PAPERGRAB);

					prescriptionCount = 1;

					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_Prescription].isVisible = 0;

					//////// 처방전 확대사진만 보여주고, 텍스트는 인게임 화면으로 돌아왔을 때 출력해준다.
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].text = TEXT("여자아이 방인데 남자아이의 진단서가 올려져있다.\n\n심한 정신이상증세를 보였던 것 같다.");

				}

				else if (clickedObject == SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_Prescription && prescriptionCount > 0)
				{
					SoundPlayer_Play(SOUND_EFFECT_PAPERGRAB);

					prescriptionCount = 1;

					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_Prescription].isVisible = 0;

				}

				// 옷장 속, 주인공을 닮은 남자의 사진을 클릭하면
				else if (clickedObject == SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_IN_CLOSET)
				{
					// 남자의 사진을 없애고, 꼭 그랬어야만 했니 마지막 텍스트를 띄어준다.
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_IN_CLOSET].isVisible = 0;
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_LAST_TEXT].isVisible = 1;

					forNextSceneTimeCount = 0.0f;

					// 소리가 들리면서 다음 스테이지로 넘어간다.  다음 스테이지로 넘어가는 추가 코딩 필요
					SoundPlayer_Play(SOUND_EFFECT_DOOROPEN);

					////////////////////////////////////////////////////////////////////////////////////////////////
					////////////////////////////////////////////////////////////////////////////////////////////////
					////////////////////////////////////////////////////////////////////////////////////////////////
					//	SoundPlayer_StopAllBGM();
					//	//Scene_ChangeScene(SCENE_ID_GAME);
					
					//secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_DOOR].isVisible = 1; 문은 안쓰기로 했다.
				}

				else if (clickedObject == SecondInnerRoomScene_GAMEOBJECT_ID_GHOST && secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_IN_CLOSET].isVisible == 1)
				{					
					SoundPlayer_Play(SOUND_EFFECT_GHOSTJUMPSCARE);

					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_GHOST_FROM_BOTTOM].isVisible = 1;
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_BACKGROUND].isVisible = 0;
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_BACKGROUND_WINDOW_BROKEN].isVisible = 1;
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_GHOST].isVisible = 0;

					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_IN_CLOSET].size.x = 0;
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_IN_CLOSET].size.y = 0;
				}

				else if (clickedObject == SecondInnerRoomScene_GAMEOBJECT_ID_GHOST && secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_Prescription].isVisible == 1)
				{
					SoundPlayer_Play(SOUND_EFFECT_GHOSTJUMPSCARE);

					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_GHOST_FROM_BOTTOM].isVisible = 1;
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_BACKGROUND].isVisible = 0;
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_BACKGROUND_WINDOW_BROKEN].isVisible = 1;
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_GHOST].isVisible = 0;
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_PRESCRIPTION].isVisible = 0;

					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_Prescription].size.x = 0;
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_Prescription].size.y = 0;

				}


				// 2초 정도 흐른 뒤에 넘길지, 클릭으로 넘길지 정하고 수정하자!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				///////////////////////////////////////////////////////////////////////////////////////////////////////
				///////////////////////////////////////////////////////////////////////////////////////////////////////
				/*else if (clickedObject == SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_GHOST_FROM_BOTTOM || clickedObject != SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_GHOST_FROM_BOTTOM)
				{
					Scene_ChangeScene(SCENE_ID_GAMEOVER);
				}*/
			}



			/*if (clickedObject == SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_FOUR_DOLLS_LEFT_KNIFE)
			{
				secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;
				secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].text = TEXT("커터칼을 얻었다!");

				getKnife = 1;

				secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_FOUR_DOLLS_LEFT_KNIFE].isVisible = 0;
				secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_FOUR_DOLLS].isVisible = 0;

			}*/
		}

		// 사진이 떠있지 않은 경우
		else
		{
			//텍스트박스가 화면에 보이는 경우,
			if (secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].isVisible == 1)
			{
				///////////////////////////////////////////일단 임시방편으로 텍스트를 지우도록 만들었다. 아래쪽 else 부분에 코드 테스트를 위해서
				///////////////////////////////////////////////////////////////////////////////// 텍스트박스 상태가 떠있을때를 구현하면 지워야함
				secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].isVisible = 0;

				// OneDOLL_WITH_MSG를 클릭했을때, 첫번째 텍스트가 뜬 상태의 처리
				if (getOneDollWithMsg == 1)
				{
					getOneDollWithMsg = 0;

					SoundPlayer_Play(SOUND_EFFECT_CUTTINGBED);
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].text = TEXT("매트리스 안에 쪽지와 인형이 들어있다.");
					message = 1;

					// 더 이상 바로 위에 텍스트가 반복 출력되지 않도록 만들어준다.
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ONEDOLL_WITH_MSG].isVisible = 0;

					// 확대된 쪽지와 인형 사진을 보여준다.
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_ONEDOLL_WITH_MSG].isVisible = 1;

				}

				else if (fiveSentence == 1)
				{
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].text = TEXT("네 명 가족의 엄마가 칼에 찔려 셋이 남았다.");

					fiveSentence = 2;
				}

				else if (fiveSentence == 2)
				{
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].text = TEXT("세 명 가족의 남자아이가 망치에 맞아 둘이 남았다.");

					fiveSentence = 3;
				}

				else if (fiveSentence == 3)
				{
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].text = TEXT("두 명 가족의 딸아이가 뜨겁다며 소리쳤고, 하나가 남았다.");

					fiveSentence = 4;
				}

				else if (fiveSentence == 4)
				{
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].text = TEXT("마지막 하나는 웃다가 사라졌다.");

					fiveSentence = 5;
				}

				else if (fiveSentence == 5)
				{
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].text = TEXT("........");
					silenceTimeCount = 0.0f;

					fiveSentence = 6;
				}


			}


			//텍스트박스가 화면에 보이지 않는 경우,
			else
			{
				//처방전을 클릭한 경우
				if (clickedObject == SecondInnerRoomScene_GAMEOBJECT_ID_PRESCRIPTION)
				{
					SoundPlayer_Play(SOUND_EFFECT_PAPERGRAB);

					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_Prescription].isVisible = 1;

				}

				// 화면 중앙의 인형 무리를 클릭한 경우. 첫번째 상호작용
				else if (clickedObject == SecondInnerRoomScene_GAMEOBJECT_ID_FOUR_DOLLS && counter_FourDolls == 0)
				{
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].text = TEXT("왜 인형에 커터칼이 붙어 있는 거지?");

					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_FOUR_DOLLS].isVisible = 1;
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_FOUR_DOLLS_LEFT_KNIFE].isVisible = 1;

				}

				//화면 중앙의 인형 무리를 클릭한 경우, 두번째 상호작용(온전한 가족이 모인 인형들)
				else if (clickedObject == SecondInnerRoomScene_GAMEOBJECT_ID_FOUR_DOLLS && counter_FourDolls == 1 && message == 1)
				{
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_FOUR_DOLLS].isVisible = 0;

					// 다섯 마리의 완전한 인형 무리 사진이 보여지게 한다.
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_FIVE_DOLLS].isVisible = 1;

					// 텍스트 띄운다.
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].text = TEXT("다섯 명 가족의 아빠가 목이 졸려 넷이 남았다.");

					fiveSentence = 1;
				}
				///////////////////////////////////////////////////////////////////////////////////////////////////////
				// ///////////////////////////////////////////////////////////////////////////////////////////////////
				// ///////////////////////////////////////////////////////////////////////////////////////////////////
				//화면 중앙의 인형 무리를 클릭한 경우, 칼은 얻었는데, 침대에서 인형과 쪽지를 얻지 못한 경우, 반복해서 텍스트 출력 
				else if (clickedObject == SecondInnerRoomScene_GAMEOBJECT_ID_FOUR_DOLLS && getKnife == 1 && message == 0)
				{
					// 텍스트 띄운다.
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].text = TEXT("가족처럼 보이는 인형들이다. 어딘지 허전해보인다.");

				}


				// 화면 왼쪽의 침대 매트리스 속, 인형과 쪽지를 클릭한 경우
				else if (clickedObject == SecondInnerRoomScene_GAMEOBJECT_ID_ONEDOLL_WITH_MSG)
				{
					//칼이 없어서 쪽지와 인형을 얻지 못하는 경우
					if (getKnife == 0)
					{
						secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;
						secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].text = TEXT("침대가 유난히 부풀어 있는 게, 안쪽에 무언가 들어있는 거 같다.\n\n자를 수 있는게 있다면 확인해 볼 수 있겠지?");
						secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].text = TEXT("침대가 유난히 부풀어 있는 게, 안쪽에 무언가 들어있는 거 같다.\n\n자를 수 있는게 있다면 확인해 볼 수 있겠지?");

					}

					//칼이 있어서 쪽지와 인형을 얻는 경우
					else if (getKnife == 1)
					{

						secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;
						secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].text = TEXT("침대가 유난히 부풀어 있는 게, 안쪽에 무언가 들어있는 거 같다.\n\n자를 수 있는게 있다면 확인해 볼 수 있겠지?");
						secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].text = TEXT("침대가 유난히 부풀어 있는 게, 안쪽에 무언가 들어있는 거 같다.\n\n자를 수 있는게 있다면 확인해 볼 수 있겠지?");

						getOneDollWithMsg = 1;

						//secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;
						//secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].text = TEXT("매트리스 안에 쪽지와 인형이 들어있었다.");


					}
				}

				// 옷장을 클릭한 경우
				else if (clickedObject == SecondInnerRoomScene_GAMEOBJECT_ID_CLOSET)
				{
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_CLOSET].isVisible = 0;

					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_IN_CLOSET].isVisible = 1;

					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].text = TEXT("뭐지? 나랑 얼굴이 너무나도 닮은 사람이 사진 속에 있다.");

					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_PRESCRIPTION].isVisible = 1;
				}

				// 다음 스테이지를 위한 문을 클릭한 경우
// 				else if (clickedObject == SecondInnerRoomScene_GAMEOBJECT_ID_DOOR)
// 				{
// 					SoundPlayer_StopAllBGM();
// 
// 					Scene_ChangeScene(SCENE_ID_MIRRORROOM);
// 				}


				// 창가 귀신을 클릭한 경우
				else if (clickedObject == SecondInnerRoomScene_GAMEOBJECT_ID_GHOST)
				{
					///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					// 여기는 게임오버 장면을 넣을 예정. 귀신이 아래에서 위로 튀어나온다. 이후 game over 화면 표시
					//Scene_ChangeScene(SCENE_ID_MAIN);

					SoundPlayer_Play(SOUND_EFFECT_GHOSTJUMPSCARE);

					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_GHOST_FROM_BOTTOM].isVisible = 1;
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_BACKGROUND].isVisible = 0;
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_BACKGROUND_WINDOW_BROKEN].isVisible = 1;
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_GHOST].isVisible = 0;

				}

				// 처방전 오브젝트 클릭시, 나타나는 확대된 처방전 사진
				else if (clickedObject == SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_Prescription)
				{

				}

				// 커터칼을 들고 있는 인형무리의 확대된 사진
				else if (clickedObject == SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_FOUR_DOLLS)
				{

				}

				// 온전한 인형 가족의 모습을 클릭 시
				else if (clickedObject == SecondInnerRoomScene_GAMEOBJECT_ID_FOUR_DOLLS_COMPLETE)
				{

				}
			}
		}



	}
}

void SecondInnerRoomScene_Render()
{
	

	// isVisible : true면 화면을 출력, false면 비출력
	// layer : 0, 1, 2, 3순으로 화면을 출력
	for (int i = 0; i < LAYER_SIZE; i++)
	{
		for (int j = 0; j < SecondInnerRoomScene_GAMEOBJECT_SIZE; j++)
		{
			// layer와 isVisible에 대한 판단을 한다
			if (secondInnerRoom_object[j].isVisible == 1 && secondInnerRoom_object[j].layer == i)
			{
				//GDIEngine_Rectangle(secondInnerRoom_object[j].position.x, secondInnerRoom_object[j].position.y, secondInnerRoom_object[j].size.x, secondInnerRoom_object[j].size.y);

				GDIEngine_PrintObject(secondInnerRoom_object[j]);
				GDIEngine_PrintObjectText(secondInnerRoom_object[j]);

			}
		}
	}
	
}


// mousePos 위치의 오브젝트의 번호(object 배열에서의 인덱스)를 반환한다.
// 만약 오브젝트가 클릭되지 않았다면 -1을 리턴한다.
int SecondInnerRoomScene_ClickedObject(POINT mousePos)
{
	int result = -1;
	int maxLayer = -1;

	for (int i = 0; i < SecondInnerRoomScene_GAMEOBJECT_SIZE; i++)
	{
		int objVisible = secondInnerRoom_object[i].isVisible;
		int objPosX1 = secondInnerRoom_object[i].position.x;
		int objPosY1 = secondInnerRoom_object[i].position.y;
		int objPosX2 = secondInnerRoom_object[i].position.x + secondInnerRoom_object[i].size.x;
		int objPosY2 = secondInnerRoom_object[i].position.y + secondInnerRoom_object[i].size.y;

		// 넘겨받은 마우스의 좌표에 따라서 어떤 게임 오브젝트가 클릭 됬는지를 판단하여 리턴한다
		if (objVisible == 1 && objPosX1 < mousePos.x && mousePos.x < objPosX2 && objPosY1 < mousePos.y && mousePos.y < objPosY2)
		{
			if (maxLayer < secondInnerRoom_object[i].layer)
			{
				result = i;
				maxLayer = secondInnerRoom_object[i].layer;
			}
		}
	}

	return result;
}