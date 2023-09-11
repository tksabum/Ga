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
#define SecondInnerRoomScene_GAMEOBJECT_ID_FOUR_DOLLS 2           // �Ѹ��� ������, ó���� ��������
#define SecondInnerRoomScene_GAMEOBJECT_ID_ONEDOLL_WITH_MSG 3 
#define SecondInnerRoomScene_GAMEOBJECT_ID_FIVE_DOLLS 4 
#define SecondInnerRoomScene_GAMEOBJECT_ID_GHOST 5     // â���� �� ���� ������ ������Ʈ

//////////////////////////////////////////////////////////////////////////// �ٷ� ���� ���� ��ġ�� ������� ���ε�?
#define SecondInnerRoomScene_GAMEOBJECT_ID_GHOST_WITH_BROKEN_WINDOW 6     // â���� ���� ������ ������Ʈ  /////////////////////////

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

#define SecondInnerRoomScene_GAMEOBJECT_ID_FOUR_DOLLS_COMPLETE 17 // �÷��̾��� ������� �°����� �ϼ��� ��������
#define SecondInnerRoomScene_GAMEOBJECT_ID_BACKGROUND_WINDOW_BROKEN 18

#define SecondInnerRoomScene_GAMEOBJECT_SIZE 19

Scene secondInnerRoomScene;

GameObject secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_SIZE];

/// ///////////////////////////////////////////////////////////////////////////////////
// �ʱ�ȭ�� �̰����� �ϸ� �ȵǰ� init���� �ؾ��Ѵ�

float startTime;   // �������ڸ���, �� �� ������ 3�� �ڿ� �ؽ�Ʈ ����ϱ� ���� ���� ����
float currentTime;

int doItOnce;  // �� ó��, ���� �� ������ �ƹ��͵� ���ص� �ؽ�Ʈ �� �� �߰� ���ֱ� ���� ���� ����

int doItOnce_ZoomInGhost; // �ҳ� �ͽ��� Ȯ��� ������, �� ������ 1�� ���� �Ʒ����� �� �ö���ٰ�, ���� ��ǥ�� �����ϸ� 0���� �ٲ�� �����.

int getKnife;   // ������������ ��ȣ�ۿ뿡�� Ŀ��Į�� ȹ���ߴ� �� ���ο� ���� ���� ����

int counter_DollWithMSG;  // ħ�븦 �� �� Ŭ���ߴ���, �ѹ� Ŭ���ߴ���, �� ���θ� �˱� ���� ī��Ʈ �ϴ� ����

int counter_FourDolls;  // �߾� ���������� ù��° ��ȣ�ۿ�����, �ι�°������ �Ǵ����ִ� ī����

int getOneDollWithMsg;

int fiveSentence;

float forNextSceneTimeCount; // ������ �߾� �ؽ�Ʈ ��� ��, 2�� �ڿ� ���� �̷��� ������ �Ѿ�� �ϱ� ���� �ð� ���� ����
float gameOverAfterGhost; // �ҳ�ͽ��� Ȯ��Ǿ� �����ϰ�, 2�� �ڿ� ���ӿ������� ������ �ϱ����� Ÿ�� ī��Ʈ ����
float silenceTimeCount;  // 5���� ���� ��� ��, "........" �ؽ�Ʈ�� ���� ���� �ð��� ��� ���� ��������
float ghostTimeCount;    // ������ ���ȰŸ� ��, �� �� �ڿ� �ͽ��� �����Ű�� ���� ��������

int message; // ������ ���� �ִ� �� ���� ��, Ȯ���ϴ� ����

int prescriptionCount; // ó������ 2��° Ŭ�����ʹ�, �ؽ�Ʈ ��¾��� Ȯ������� ���´�.

//sceneList�� secondInnerRoomScene�� ��� secondInnerRoomScene�� �Լ� �����͵��� �ʱ�ȭ(�Լ��� �ּҰ��� ��´�) �Ѵ�.
void SecondInnerRoomScene_Ready()
{
	sceneList[SCENE_ID_SECONDINNERROOM] = &secondInnerRoomScene;
	secondInnerRoomScene.func_init = SecondInnerRoomScene_Init;
	secondInnerRoomScene.func_update = SecondInnerRoomScene_Update;
	secondInnerRoomScene.func_render = SecondInnerRoomScene_Render;
}


//scene ��ȯ�� ���� ��, �ش� scene�� �ʱ�ȭ
void SecondInnerRoomScene_Init()
{

	startTime = clock();


	doItOnce = 1;  // �� ó��, ���� �� ������ �ƹ��͵� ���ص� �ؽ�Ʈ �� �� �߰� ���ֱ� ���� ���� ����

	doItOnce_ZoomInGhost = 1;

	getKnife = 0;   // ������������ ��ȣ�ۿ뿡�� Ŀ��Į�� ȹ���ߴ� �� ���ο� ���� ���� ����

	counter_DollWithMSG = 0;  // ħ�븦 �� �� Ŭ���ߴ���, �ѹ� Ŭ���ߴ���, �� ���θ� �˱� ���� ī��Ʈ �ϴ� ����

	counter_FourDolls = 0;  // �߾� ���������� ù��° ��ȣ�ۿ�����, �ι�°������ �Ǵ����ִ� ī����

	getOneDollWithMsg = 0;

	fiveSentence = 0;

	message = 0;

	prescriptionCount = 0;


	// ��� ������Ʈ�� X,Y division�� imageNumber �ʱ�ȭ
	for (int i = 0; i < SecondInnerRoomScene_GAMEOBJECT_SIZE; i++)
	{
		secondInnerRoom_object[i].Xdivision = 1;
		secondInnerRoom_object[i].Ydivision = 1;
		secondInnerRoom_object[i].imageNumber = 0;		
		
		secondInnerRoom_object[i].scalePivot.x = 0.0f;  // �������� �̹����� ũ�⸦ ���� �� �� �ִ�.
		secondInnerRoom_object[i].scalePivot.y = 0.0f;	// scale����� �ʿ��ϸ� printType�� TRANSPARENT�� ALPHABLEND�̾�� �ϰ�, scalePivot�� �߽������ؼ� scale����ŭ ũ�Ⱑ ��ȭ�մϴ�
		secondInnerRoom_object[i].scale = 1.0;			// scale�� 0.5�� ũ�Ⱑ ����.  2.0�̸� �ι谡 �ȴ�.

		secondInnerRoom_object[i].imagePos.x = 0;  // �⺻������ �̹����� 0,0���� �����µ� �긦 ���ϴ� ���� ���������ν� �̹����� ������ ��ġ�� ������ �� �ִ�. 
		secondInnerRoom_object[i].imagePos.y = 0;  // �⺻������ �̹����� 0,0���� �����µ� �긦 ���ϴ� ���� ���������ν� �̹����� ������ ��ġ�� ������ �� �ִ�.
	}


	// ��׶��� ������ �س��Ҵ�.
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_BACKGROUND].printType = TYPE_TRANSPARENT;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_BACKGROUND].position.x = 0;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_BACKGROUND].position.y = 0;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_BACKGROUND].size.x = 1600;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_BACKGROUND].size.y = 900;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_BACKGROUND].isVisible = 1;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_BACKGROUND].layer = LAYER_BACKGROUND;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_BACKGROUND].imagePath = TEXT("images/stage3/stage3normal.bmp");

	// �ҳ�ͽ��� Ȯ��ɶ�, â�� ���� ������ ��׶��� �̹���
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_BACKGROUND_WINDOW_BROKEN].printType = TYPE_TRANSPARENT;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_BACKGROUND_WINDOW_BROKEN].position.x = 0;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_BACKGROUND_WINDOW_BROKEN].position.y = 0;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_BACKGROUND_WINDOW_BROKEN].size.x = 1600;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_BACKGROUND_WINDOW_BROKEN].size.y = 900;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_BACKGROUND_WINDOW_BROKEN].isVisible = 0;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_BACKGROUND_WINDOW_BROKEN].layer = LAYER_BACKGROUND;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_BACKGROUND_WINDOW_BROKEN].imagePath = TEXT("images/stage3/��������3_�������ɾ_���ö���_���.bmp");

	//������ ���� ó������ ��ġ. ��ȣ�ۿ� ������ �ڽ��� �������.
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_PRESCRIPTION].printType = TYPE_BASE;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_PRESCRIPTION].position.x = 1303;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_PRESCRIPTION].position.y = 525;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_PRESCRIPTION].size.x = 101;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_PRESCRIPTION].size.y = 22;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_PRESCRIPTION].isVisible = 1;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_PRESCRIPTION].layer = LAYER_BOTTOM;

	/////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////      ���� �Ⱦ��ٰ� ����. ���߿� ���� �ڵ��� ���� �ʿ�
	// ���� ���������� ���� ���� ��ġ.
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_DOOR].printType = TYPE_BASE;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_DOOR].position.x = 1500;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_DOOR].position.y = 400;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_DOOR].size.x = 100;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_DOOR].size.y = 100;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_DOOR].isVisible = 0;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_DOOR].layer = LAYER_BOTTOM;

	//�� �߾ӿ� ���ִ�, ���� 4���� ��ġ, ������ �ϳ� ������ �� ó���� ���
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_FOUR_DOLLS].printType = TYPE_BASE;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_FOUR_DOLLS].position.x = 761;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_FOUR_DOLLS].position.y = 728;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_FOUR_DOLLS].size.x = 159;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_FOUR_DOLLS].size.y = 99;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_FOUR_DOLLS].isVisible = 1;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_FOUR_DOLLS].layer = LAYER_BOTTOM;

	//�� ���� ħ�� ����, ������ ����(�޼���) ��ġ
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ONEDOLL_WITH_MSG].printType = TYPE_BASE;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ONEDOLL_WITH_MSG].position.x = 108;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ONEDOLL_WITH_MSG].position.y = 501;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ONEDOLL_WITH_MSG].size.x = 368;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ONEDOLL_WITH_MSG].size.y = 271;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ONEDOLL_WITH_MSG].isVisible = 1;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ONEDOLL_WITH_MSG].layer = LAYER_BOTTOM;

	//ħ�� ��, â���� �ͽ�.
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_GHOST].printType = TYPE_TRANSPARENT;  
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_GHOST].position.x = 0;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_GHOST].position.y = 90;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_GHOST].size.x = 150;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_GHOST].size.y = 350;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_GHOST].isVisible = 0;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_GHOST].layer = LAYER_BOTTOM;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_GHOST].imagePath = TEXT("images/stage3/S3_Ghost_include_background.bmp");


	//����. ������ ���� ����� ����, ��ȣ�ۿ밡��.   
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_CLOSET].printType = TYPE_TRANSPARENT; 
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_CLOSET].position.x = 642;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_CLOSET].position.y = 206;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_CLOSET].size.x = 362;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_CLOSET].size.y = 489;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_CLOSET].isVisible = 0;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_CLOSET].layer = LAYER_BOTTOM;

	// ǥ�� �ؽ�Ʈ �ڽ� ����
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


	// ��ȣ�ۿ��� �ϸ�, ȭ�� �߾ӿ� �� ó���� Ȯ�� ������ ��ġ�� ũ��
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_Prescription].printType = TYPE_TRANSPARENT;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_Prescription].position.x = 510;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_Prescription].position.y = 70;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_Prescription].size.x = 570;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_Prescription].size.y = 780;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_Prescription].isVisible = 0;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_Prescription].layer = LAYER_MID;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_Prescription].imagePath = TEXT("images/stage3/���ܼ�������2.bmp");


	// ��ȣ�ۿ��� �ϸ�, ȭ�� �߾ӿ� �� �������� Ȯ�� ������ ��ġ�� ũ��
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_FOUR_DOLLS].printType = TYPE_TRANSPARENT;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_FOUR_DOLLS].position.x = 550;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_FOUR_DOLLS].position.y = 270;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_FOUR_DOLLS].size.x = 500;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_FOUR_DOLLS].size.y = 330;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_FOUR_DOLLS].isVisible = 0;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_FOUR_DOLLS].layer = LAYER_MID;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_FOUR_DOLLS].imagePath = TEXT("images/stage3/Obj_Fourdolls_2.bmp");


	// �ټ� ������ ������ ��������
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_FIVE_DOLLS].printType = TYPE_TRANSPARENT;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_FIVE_DOLLS].position.x = 700;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_FIVE_DOLLS].position.y = 300;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_FIVE_DOLLS].size.x = 100;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_FIVE_DOLLS].size.y = 100;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_FIVE_DOLLS].isVisible = 0;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_FIVE_DOLLS].layer = LAYER_BOTTOM;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_FIVE_DOLLS].imagePath = TEXT("images/stage3/dolls.bmp");



	//////////////////////////////////////////////////////////////////////////                
	//////////////////////////////////////////////////////////////////////////                �ٷ� ���� FIVE DOLLS �� ��ġ�� �� ����..... �� ���� �� ����
	//������ ���������� ���� ����
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_FOUR_DOLLS_COMPLETE].printType = TYPE_BASE;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_FOUR_DOLLS_COMPLETE].position.x = 600;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_FOUR_DOLLS_COMPLETE].position.y = 150;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_FOUR_DOLLS_COMPLETE].size.x = 400;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_FOUR_DOLLS_COMPLETE].size.y = 400;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_FOUR_DOLLS_COMPLETE].isVisible = 0;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_FOUR_DOLLS_COMPLETE].layer = LAYER_MID;

	// ���ε� ���� ���� ��������, Ŀ��Į�� �� ������ �κ�
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_FOUR_DOLLS_LEFT_KNIFE].printType = TYPE_BASE;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_FOUR_DOLLS_LEFT_KNIFE].position.x = 550;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_FOUR_DOLLS_LEFT_KNIFE].position.y = 270;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_FOUR_DOLLS_LEFT_KNIFE].size.x = 500;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_FOUR_DOLLS_LEFT_KNIFE].size.y = 330;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_FOUR_DOLLS_LEFT_KNIFE].isVisible = 0;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_FOUR_DOLLS_LEFT_KNIFE].layer = LAYER_TOP;

	// Ȯ���, ������ ������ ����
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_ONEDOLL_WITH_MSG].printType = TYPE_TRANSPARENT;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_ONEDOLL_WITH_MSG].position.x = 400;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_ONEDOLL_WITH_MSG].position.y = 120;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_ONEDOLL_WITH_MSG].size.x = 850;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_ONEDOLL_WITH_MSG].size.y = 500;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_ONEDOLL_WITH_MSG].isVisible = 0;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_ONEDOLL_WITH_MSG].layer = LAYER_MID;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_ONEDOLL_WITH_MSG].imagePath = TEXT("images/stage3/stage3_��������Ȯ���.bmp");


	// ������ Ŭ���ϸ�, Ȯ��Ǿ� ��Ÿ���� ����
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_IN_CLOSET].printType = TYPE_TRANSPARENT;  
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_IN_CLOSET].position.x = 400;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_IN_CLOSET].position.y = 200;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_IN_CLOSET].size.x = 770;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_IN_CLOSET].size.y = 450;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_IN_CLOSET].isVisible = 0;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_IN_CLOSET].layer = LAYER_MID;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_IN_CLOSET].imagePath = TEXT("images/stage3/Obj_Manphotoincloset.bmp");

	// �������� �������� �����ϴ� �ؽ�Ʈ �̹���
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_LAST_TEXT].printType = TYPE_TRANSPARENT;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_LAST_TEXT].position.x = 400;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_LAST_TEXT].position.y = 200;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_LAST_TEXT].size.x = 770;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_LAST_TEXT].size.y = 450;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_LAST_TEXT].isVisible = 0;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_LAST_TEXT].layer = LAYER_MID;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_LAST_TEXT].imagePath = TEXT("images/stage3/�ؽ�Ʈ Ȯ���.bmp");

	// �Ʒ��������� �ö����, �ͽ��� Ȯ��� ����

	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_GHOST_FROM_BOTTOM].printType = TYPE_TRANSPARENT;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_GHOST_FROM_BOTTOM].position.x = 400;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_GHOST_FROM_BOTTOM].position.y = 200;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_GHOST_FROM_BOTTOM].size.x = 1600;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_GHOST_FROM_BOTTOM].size.y = 900;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_GHOST_FROM_BOTTOM].isVisible = 0;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_GHOST_FROM_BOTTOM].layer = LAYER_TOP;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_GHOST_FROM_BOTTOM].imagePath = TEXT("images/stage3/test4.bmp");
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_GHOST_FROM_BOTTOM].scale = 0.7f;
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_GHOST_FROM_BOTTOM].imagePos.x = 200;  // �⺻������ �̹����� 0,0���� �����µ� �긦 ���ϴ� ���� ���������ν� �̹����� ������ ��ġ�� ������ �� �ִ�. 
	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_GHOST_FROM_BOTTOM].imagePos.y = 910;  // �̹����� �� �Ʒ����� 100 ������ �ö�;��Ѵ�.

	SoundPlayer_Play(SOUND_BGM_MAIN);

}

//secondInnerRoomScene�� ���� scene�� ��� update�� �����Ѵ�.
void SecondInnerRoomScene_Update(float deltaTime)
{
	currentTime = clock();

	silenceTimeCount += deltaTime;

	ghostTimeCount += deltaTime;

	gameOverAfterGhost += deltaTime;

	forNextSceneTimeCount += deltaTime;


	/// ���������� Ȯ���ϰ� �� �κ� �ּ��� ������.
	////���� ȭ���� ���۵ǰ� 3�� �ڿ� "�����ڸ��� ���� �� �ϰ� ������. �� �̻� ������� �ʾ�." �ؽ�Ʈ ��� + ���� �� ������ �Ҹ�
	//if (doItOnce == 1 && currentTime - startTime >= 2000)
	//{
	//	SoundPlayer_Play(SOUND_EFFECT_DOORCLOSE);

	//	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;
	//	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].text = TEXT("�����ڸ��� ���� �� �ϰ� ������. �� �̻� ������� �ʾ�.");

	//	doItOnce = 0; // �� �̻� �� ��Ʈ�� ��� ������Ʈ �Ǿ�, ȭ�鿡 �׷����� �ʵ��� �Ѵ�.
	//}


	//// ...... �� ��� �� ��, 2�� �Ŀ� ���忡�� ���� �Ҹ� �� ���尨 ���� BGM ������, �ؽ�Ʈ ���
	//if (silenceTimeCount >= 2.0f && fiveSentence == 6)
	//{
	//	SoundPlayer_Play(SOUND_EFFECT_CLOSETSOUND);
	//	SoundPlayer_Play(SOUND_EFFECT_CLOSETSOUND2);

	//	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;
	//	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].text = TEXT("���忡�� �ν����Ÿ��� �Ҹ��� �鸰��. �ƹ����� Ȯ���غ��� �� ���� �� ����.");

	//	secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_CLOSET].isVisible = 1;

	//	ghostTimeCount = 0.0f;

	//	fiveSentence = 7;

	//}

	if (fiveSentence == 6 && silenceTimeCount >= 2.0f)
	{
		SoundPlayer_Play(SOUND_EFFECT_CLOSETSOUND);
		SoundPlayer_Play(SOUND_EFFECT_CLOSETSOUND2);

		secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;
		secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].text = TEXT("���忡�� �ν����Ÿ��� �Ҹ��� �鸰��. �ƹ����� Ȯ���غ��� �� ���� �� ����.");
		
		secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_CLOSET].isVisible = 1;
		
		ghostTimeCount = 0.0f;

		fiveSentence = 7;
	}



	// ���忡�� ���ȰŸ��� �Ҹ��� �� ��, 3�� �Ŀ� â�������� �Ҹ� + �ͽ� ����
	if (ghostTimeCount >= 2.5f && fiveSentence == 7)
	{
		SoundPlayer_Play(SOUND_EFFECT_GLASSBREAK);

		secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_GHOST].isVisible = 1;

		fiveSentence = 8;

	}

	// â���� �ͽ��� Ŭ���ؼ�, Ȯ��� �ͽ��� visible�� ���°� �ٲ��,
	if (doItOnce_ZoomInGhost == 1 && secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_GHOST_FROM_BOTTOM].isVisible == 1)
	{	
		// y��ǥ�� 910���� 100����, �� �Ʒ��������� �޸��� �ö���� �Ѵ�.
		secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_GHOST_FROM_BOTTOM].imagePos.y = secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_GHOST_FROM_BOTTOM].imagePos.y - 5000*deltaTime;  

		// y��ǥ�� 100���� �۰ų� ���ٸ�, ��ǥ�� 100���� 
		if (secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_GHOST_FROM_BOTTOM].imagePos.y <= 100)
		{
			doItOnce_ZoomInGhost = 0;
			secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_GHOST_FROM_BOTTOM].imagePos.y = 100;
			gameOverAfterGhost = 0.0f;
		}
	}

	// �ҳ� �ͽ��� �Ʒ����� �� �ö����, 2�� �� �ڵ����� ���ӿ��� ������ ��ȯ�Ѵ�.
	if (secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_GHOST_FROM_BOTTOM].imagePos.y == 100)
	{
		if (gameOverAfterGhost >= 1.5f)
		{
			Scene_ChangeScene(SCENE_ID_GAMEOVER);
		}
	}

	// �� �׷���߸� �ߴ�?  �ؽ�Ʈ ���� �� 2�� �ڿ� ���� �̷��� ������ �̵�
	if (secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_LAST_TEXT].isVisible == 1)
	{
		if (forNextSceneTimeCount >= 3.0f)
		{
			GameTimer_AddExtraTime();
			Scene_ChangeScene(SCENE_ID_MIRRORROOM);
		}
	}

	// ȭ���� ó�� �����ϰ�, 3�� �ڿ� ���� ��! ���带 ���ְ�, �ؽ�Ʈ�� �����ش�.
	if (doItOnce == 1 && currentTime - startTime >= 1000)
	{
		SoundPlayer_Play(SOUND_EFFECT_DOORCLOSE);

		secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;
		secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].text = TEXT("�����ڸ��� ���� �� �ϰ� ������.\n\n�� �̻� ������� �ʴ�.");

		doItOnce = 0; // �� �̻� �� ��Ʈ�� ��� ������Ʈ �Ǿ�, ȭ�鿡 �׷����� �ʵ��� �Ѵ�.
	}


	// ó�� 5�� ������ ��� �Էµ� ���� ���ϰ� �Ѵ�. �ٷ� ���� �ؽ�Ʈ��, �÷��̾��� ���ǽ����� ���콺 Ŭ�� ������ ��ŵ���� �ʵ��� �ϱ� �����̴�.
	if (currentTime - startTime <= 3000)
	{
		
	}

	// �ٷ� ���� ���� ���� (currentTime - startTime) ����, �ٷ� �Ʒ��� silenceTimeCount ���� ������ �۴ٸ�, if�� else if �� ���� �ٲ���� �Ѵ�.
	// ��, �� ������ �ð��� ���ǰ��� ���� ���� else if�� ����Ѵ�.
	else if (silenceTimeCount <= 3.0f)
	{

	}

	else if (Input_GetMouseLeftDownNow())
	{
		// Ŭ�� �г�Ƽ ���
		GameTimer_SubPenaltyTime();

		SoundPlayer_Play(SOUND_EFFECT_BUTTON);
		int clickedObject = SecondInnerRoomScene_ClickedObject(Input_GetMouseLeftDownPosition());

		// ȭ�鿡 ���ε� ������ ���ִ� ���
		// ȭ�鿡 ���ε� ������ �߰��Ǹ�, ���ǿ� �߰������ �Ѵ� !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		if (secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_Prescription].isVisible == 1 || secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_FOUR_DOLLS].isVisible == 1 || secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_FOUR_DOLLS_LEFT_KNIFE].isVisible == 1 || secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_ONEDOLL_WITH_MSG].isVisible == 1 || secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_IN_CLOSET].isVisible == 1 || secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_LAST_TEXT].isVisible == 1 || secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_GHOST_FROM_BOTTOM].isVisible == 1)
		{
			//�ؽ�Ʈ�ڽ��� ȭ�鿡 ���̴� ���,
			if (secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].isVisible == 1)
			{
				secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].isVisible = 0;
			}

			//�ؽ�Ʈ�ڽ��� ȭ�鿡 ������ �ʴ� ���
			else
			{
				if (clickedObject == SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_FOUR_DOLLS_LEFT_KNIFE)
				{
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].text = TEXT("Ŀ��Į�� �����!");

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

					//////// ó���� Ȯ������� �����ְ�, �ؽ�Ʈ�� �ΰ��� ȭ������ ���ƿ��� �� ������ش�.
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].text = TEXT("���ھ��� ���ε� ���ھ����� ���ܼ��� �÷����ִ�.\n\n���� �����̻������� ������ �� ����.");

				}

				else if (clickedObject == SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_Prescription && prescriptionCount > 0)
				{
					SoundPlayer_Play(SOUND_EFFECT_PAPERGRAB);

					prescriptionCount = 1;

					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_Prescription].isVisible = 0;

				}

				// ���� ��, ���ΰ��� ���� ������ ������ Ŭ���ϸ�
				else if (clickedObject == SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_IN_CLOSET)
				{
					// ������ ������ ���ְ�, �� �׷���߸� �ߴ� ������ �ؽ�Ʈ�� ����ش�.
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_IN_CLOSET].isVisible = 0;
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_LAST_TEXT].isVisible = 1;

					forNextSceneTimeCount = 0.0f;

					// �Ҹ��� �鸮�鼭 ���� ���������� �Ѿ��.  ���� ���������� �Ѿ�� �߰� �ڵ� �ʿ�
					SoundPlayer_Play(SOUND_EFFECT_DOOROPEN);

					////////////////////////////////////////////////////////////////////////////////////////////////
					////////////////////////////////////////////////////////////////////////////////////////////////
					////////////////////////////////////////////////////////////////////////////////////////////////
					//	SoundPlayer_StopAllBGM();
					//	//Scene_ChangeScene(SCENE_ID_GAME);
					
					//secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_DOOR].isVisible = 1; ���� �Ⱦ���� �ߴ�.
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


				// 2�� ���� �帥 �ڿ� �ѱ���, Ŭ������ �ѱ��� ���ϰ� ��������!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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
				secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].text = TEXT("Ŀ��Į�� �����!");

				getKnife = 1;

				secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_FOUR_DOLLS_LEFT_KNIFE].isVisible = 0;
				secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_FOUR_DOLLS].isVisible = 0;

			}*/
		}

		// ������ ������ ���� ���
		else
		{
			//�ؽ�Ʈ�ڽ��� ȭ�鿡 ���̴� ���,
			if (secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].isVisible == 1)
			{
				///////////////////////////////////////////�ϴ� �ӽù������� �ؽ�Ʈ�� ���쵵�� �������. �Ʒ��� else �κп� �ڵ� �׽�Ʈ�� ���ؼ�
				///////////////////////////////////////////////////////////////////////////////// �ؽ�Ʈ�ڽ� ���°� ���������� �����ϸ� ��������
				secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].isVisible = 0;

				// OneDOLL_WITH_MSG�� Ŭ��������, ù��° �ؽ�Ʈ�� �� ������ ó��
				if (getOneDollWithMsg == 1)
				{
					getOneDollWithMsg = 0;

					SoundPlayer_Play(SOUND_EFFECT_CUTTINGBED);
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].text = TEXT("��Ʈ���� �ȿ� ������ ������ ����ִ�.");
					message = 1;

					// �� �̻� �ٷ� ���� �ؽ�Ʈ�� �ݺ� ��µ��� �ʵ��� ������ش�.
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ONEDOLL_WITH_MSG].isVisible = 0;

					// Ȯ��� ������ ���� ������ �����ش�.
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_ONEDOLL_WITH_MSG].isVisible = 1;

				}

				else if (fiveSentence == 1)
				{
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].text = TEXT("�� �� ������ ������ Į�� ��� ���� ���Ҵ�.");

					fiveSentence = 2;
				}

				else if (fiveSentence == 2)
				{
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].text = TEXT("�� �� ������ ���ھ��̰� ��ġ�� �¾� ���� ���Ҵ�.");

					fiveSentence = 3;
				}

				else if (fiveSentence == 3)
				{
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].text = TEXT("�� �� ������ �����̰� �̴߰ٸ� �Ҹ��ư�, �ϳ��� ���Ҵ�.");

					fiveSentence = 4;
				}

				else if (fiveSentence == 4)
				{
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].text = TEXT("������ �ϳ��� ���ٰ� �������.");

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


			//�ؽ�Ʈ�ڽ��� ȭ�鿡 ������ �ʴ� ���,
			else
			{
				//ó������ Ŭ���� ���
				if (clickedObject == SecondInnerRoomScene_GAMEOBJECT_ID_PRESCRIPTION)
				{
					SoundPlayer_Play(SOUND_EFFECT_PAPERGRAB);

					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_Prescription].isVisible = 1;

				}

				// ȭ�� �߾��� ���� ������ Ŭ���� ���. ù��° ��ȣ�ۿ�
				else if (clickedObject == SecondInnerRoomScene_GAMEOBJECT_ID_FOUR_DOLLS && counter_FourDolls == 0)
				{
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].text = TEXT("�� ������ Ŀ��Į�� �پ� �ִ� ����?");

					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_FOUR_DOLLS].isVisible = 1;
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_FOUR_DOLLS_LEFT_KNIFE].isVisible = 1;

				}

				//ȭ�� �߾��� ���� ������ Ŭ���� ���, �ι�° ��ȣ�ۿ�(������ ������ ���� ������)
				else if (clickedObject == SecondInnerRoomScene_GAMEOBJECT_ID_FOUR_DOLLS && counter_FourDolls == 1 && message == 1)
				{
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_FOUR_DOLLS].isVisible = 0;

					// �ټ� ������ ������ ���� ���� ������ �������� �Ѵ�.
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_FIVE_DOLLS].isVisible = 1;

					// �ؽ�Ʈ ����.
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].text = TEXT("�ټ� �� ������ �ƺ��� ���� ���� ���� ���Ҵ�.");

					fiveSentence = 1;
				}
				///////////////////////////////////////////////////////////////////////////////////////////////////////
				// ///////////////////////////////////////////////////////////////////////////////////////////////////
				// ///////////////////////////////////////////////////////////////////////////////////////////////////
				//ȭ�� �߾��� ���� ������ Ŭ���� ���, Į�� ����µ�, ħ�뿡�� ������ ������ ���� ���� ���, �ݺ��ؼ� �ؽ�Ʈ ��� 
				else if (clickedObject == SecondInnerRoomScene_GAMEOBJECT_ID_FOUR_DOLLS && getKnife == 1 && message == 0)
				{
					// �ؽ�Ʈ ����.
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].text = TEXT("����ó�� ���̴� �������̴�. ����� �����غ��δ�.");

				}


				// ȭ�� ������ ħ�� ��Ʈ���� ��, ������ ������ Ŭ���� ���
				else if (clickedObject == SecondInnerRoomScene_GAMEOBJECT_ID_ONEDOLL_WITH_MSG)
				{
					//Į�� ��� ������ ������ ���� ���ϴ� ���
					if (getKnife == 0)
					{
						secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;
						secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].text = TEXT("ħ�밡 ������ ��Ǯ�� �ִ� ��, ���ʿ� ���� ����ִ� �� ����.\n\n�ڸ� �� �ִ°� �ִٸ� Ȯ���� �� �� �ְ���?");
						secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].text = TEXT("ħ�밡 ������ ��Ǯ�� �ִ� ��, ���ʿ� ���� ����ִ� �� ����.\n\n�ڸ� �� �ִ°� �ִٸ� Ȯ���� �� �� �ְ���?");

					}

					//Į�� �־ ������ ������ ��� ���
					else if (getKnife == 1)
					{

						secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;
						secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].text = TEXT("ħ�밡 ������ ��Ǯ�� �ִ� ��, ���ʿ� ���� ����ִ� �� ����.\n\n�ڸ� �� �ִ°� �ִٸ� Ȯ���� �� �� �ְ���?");
						secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].text = TEXT("ħ�밡 ������ ��Ǯ�� �ִ� ��, ���ʿ� ���� ����ִ� �� ����.\n\n�ڸ� �� �ִ°� �ִٸ� Ȯ���� �� �� �ְ���?");

						getOneDollWithMsg = 1;

						//secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;
						//secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].text = TEXT("��Ʈ���� �ȿ� ������ ������ ����־���.");


					}
				}

				// ������ Ŭ���� ���
				else if (clickedObject == SecondInnerRoomScene_GAMEOBJECT_ID_CLOSET)
				{
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_CLOSET].isVisible = 0;

					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_IN_CLOSET].isVisible = 1;

					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].isVisible = 1;
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_TEXTBOX].text = TEXT("����? ���� ���� �ʹ����� ���� ����� ���� �ӿ� �ִ�.");

					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_PRESCRIPTION].isVisible = 1;
				}

				// ���� ���������� ���� ���� Ŭ���� ���
// 				else if (clickedObject == SecondInnerRoomScene_GAMEOBJECT_ID_DOOR)
// 				{
// 					SoundPlayer_StopAllBGM();
// 
// 					Scene_ChangeScene(SCENE_ID_MIRRORROOM);
// 				}


				// â�� �ͽ��� Ŭ���� ���
				else if (clickedObject == SecondInnerRoomScene_GAMEOBJECT_ID_GHOST)
				{
					///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					// ����� ���ӿ��� ����� ���� ����. �ͽ��� �Ʒ����� ���� Ƣ��´�. ���� game over ȭ�� ǥ��
					//Scene_ChangeScene(SCENE_ID_MAIN);

					SoundPlayer_Play(SOUND_EFFECT_GHOSTJUMPSCARE);

					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_GHOST_FROM_BOTTOM].isVisible = 1;
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_BACKGROUND].isVisible = 0;
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_BACKGROUND_WINDOW_BROKEN].isVisible = 1;
					secondInnerRoom_object[SecondInnerRoomScene_GAMEOBJECT_ID_GHOST].isVisible = 0;

				}

				// ó���� ������Ʈ Ŭ����, ��Ÿ���� Ȯ��� ó���� ����
				else if (clickedObject == SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_Prescription)
				{

				}

				// Ŀ��Į�� ��� �ִ� ���������� Ȯ��� ����
				else if (clickedObject == SecondInnerRoomScene_GAMEOBJECT_ID_ZoomInPhoto_FOUR_DOLLS)
				{

				}

				// ������ ���� ������ ����� Ŭ�� ��
				else if (clickedObject == SecondInnerRoomScene_GAMEOBJECT_ID_FOUR_DOLLS_COMPLETE)
				{

				}
			}
		}



	}
}

void SecondInnerRoomScene_Render()
{
	

	// isVisible : true�� ȭ���� ���, false�� �����
	// layer : 0, 1, 2, 3������ ȭ���� ���
	for (int i = 0; i < LAYER_SIZE; i++)
	{
		for (int j = 0; j < SecondInnerRoomScene_GAMEOBJECT_SIZE; j++)
		{
			// layer�� isVisible�� ���� �Ǵ��� �Ѵ�
			if (secondInnerRoom_object[j].isVisible == 1 && secondInnerRoom_object[j].layer == i)
			{
				//GDIEngine_Rectangle(secondInnerRoom_object[j].position.x, secondInnerRoom_object[j].position.y, secondInnerRoom_object[j].size.x, secondInnerRoom_object[j].size.y);

				GDIEngine_PrintObject(secondInnerRoom_object[j]);
				GDIEngine_PrintObjectText(secondInnerRoom_object[j]);

			}
		}
	}
	
}


// mousePos ��ġ�� ������Ʈ�� ��ȣ(object �迭������ �ε���)�� ��ȯ�Ѵ�.
// ���� ������Ʈ�� Ŭ������ �ʾҴٸ� -1�� �����Ѵ�.
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

		// �Ѱܹ��� ���콺�� ��ǥ�� ���� � ���� ������Ʈ�� Ŭ�� ������� �Ǵ��Ͽ� �����Ѵ�
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