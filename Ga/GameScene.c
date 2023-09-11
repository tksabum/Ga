#include "GameScene.h"
#include "GDIEngine.h"
#include "GameObject.h"
#include "Scene.h"
#include "Input.h"
#include "SoundPlayer.h"

Scene gameScene;

GameObject box;

float timeCounter;

const int BIGBOX_POS_X = 100;
const int BIGBOX_POS_Y = 100;
const int BIGBOX_SIZE_X = 1000;
const int BIGBOX_SIZE_Y = 500;

void GameScene_Ready()
{
	sceneList[SCENE_ID_GAME] = &gameScene;
	gameScene.func_init = GameScene_Init;
	gameScene.func_update = GameScene_Update;
	gameScene.func_render = GameScene_Render;
}

void GameScene_Init()
{
	timeCounter = 0.0f;

	box.position.x = 100;
	box.position.y = 100;
	box.size.x = 60;
	box.size.y = 80;
	box.isVisible = 1;
	box.layer = LAYER_BACKGROUND;
	box.imagePath = TEXT("image.bmp");
	box.Xdivision = 4;
	box.Ydivision = 4;
	box.imageNumber = 0;

	box.textBoxPos.x = 100;
	box.textBoxPos.y = 100;
	box.textBoxSize.x = 200;
	box.textBoxSize.y = 200;

	box.text = TEXT("´ÔÀº °¬½À´Ï´Ù.¾Æ¾Æ »ç¶ûÇÏ´Â ³ªÀÇ ´ÔÀº °¬½À´Ï´Ù. Çª¸¥ »êºûÀ» ±úÄ¡°í ´ÜÇ³³ª¹« ½£À» ÇâÇÏ¿© ³­ ÀÛÀº ±æÀ» °É¾î¼­");
	SoundPlayer_Play(SOUND_BGM_ROOM1);
}

void GameScene_Update(float deltaTime)
{
	// ¸¶¿ì½º ÁÂÅ¬¸¯À» ÇÏ¸é ¾ÀÀ» Main¾ÀÀ¸·Î º¯°æÇÑ´Ù.
	if (Input_GetMouseLeftDownNow())
	{
		SoundPlayer_StopAllBGM();
		Scene_ChangeScene(SCENE_ID_SETTING);
	}

	timeCounter += deltaTime;

	if (timeCounter > 0.12f)
	{
		timeCounter -= 0.12f;
		box.position.x += 3;
		timeCounter -= 0.12f;
		box.imageNumber = (box.imageNumber + 1) % 4;
	}
}

void GameScene_Render()
{
	GDIEngine_PrintObject(box);
	GDIEngine_PrintObjectText(box);

	//GDIEngine_Rectangle(box);
}
