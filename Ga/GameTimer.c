#include "GameTimer.h"
#include "Scene.h"
#include "GDIEngine.h"
#include "GameObject.h"
#include "SoundPlayer.h"

int isRunningTimer = 0;
float runningTime = 0.0f;
float limitTime = 0.0f;

float clickTimer = 0.0f; // ������ Ŭ������ ���� ���� �ð��� ���

const float DEFAULT_LIMIT_TIME = 80.0f;
const float EXTRA_TIME = 60.0f;
const float PENALTY_TIME = 1.0f;
const float ALLOWED_CLICK_PERIOD = 0.8f; // ������ �ð��ȿ� �ٽ��ѹ� Ŭ���ϸ� �г�Ƽ�� ����

const float DANGER_TIME = 30.0f;
const float VERY_DANGER_TIME = 15.0f;

const float GAMEOVER_TIME = 2.0f;

GameObject dangerTimeObject;
GameObject gameOverObject;

void GameTimer_GameStart()
{
	isRunningTimer = 1;
	runningTime = 0.0f;
	limitTime = DEFAULT_LIMIT_TIME;
	clickTimer = ALLOWED_CLICK_PERIOD + 1.0f;

	dangerTimeObject.Xdivision = 1;
	dangerTimeObject.Ydivision = 1;
	dangerTimeObject.imageNumber = 0;
	dangerTimeObject.scalePivot.x = 0.0f;
	dangerTimeObject.scalePivot.y = 0.0f;
	dangerTimeObject.scale = 1.0f;
	dangerTimeObject.imagePos.x = 0;
	dangerTimeObject.imagePos.y = 0;
	dangerTimeObject.printType = TYPE_ALPHABLEND;
	dangerTimeObject.position.x = 0;
	dangerTimeObject.position.y = 0;
	dangerTimeObject.size.x = 1600;
	dangerTimeObject.size.y = 900;
	dangerTimeObject.isVisible = 0;
	dangerTimeObject.blendFunction.BlendOp = 0;
	dangerTimeObject.blendFunction.BlendFlags = 0;
	dangerTimeObject.blendFunction.AlphaFormat = 0;
	dangerTimeObject.blendFunction.SourceConstantAlpha = 100;
	dangerTimeObject.imagePath = TEXT("images/VeryDangerTime.bmp");
	dangerTimeObject.layer = LAYER_BACKGROUND;

	gameOverObject.Xdivision = 1;
	gameOverObject.Ydivision = 1;
	gameOverObject.imageNumber = 0;
	gameOverObject.scalePivot.x = 0.0f;
	gameOverObject.scalePivot.y = 0.0f;
	gameOverObject.scale = 1.0f;
	gameOverObject.imagePos.x = 0;
	gameOverObject.imagePos.y = 0;
	gameOverObject.printType = TYPE_TRANSPARENT;
	gameOverObject.position.x = 0;
	gameOverObject.position.y = 0;
	gameOverObject.size.x = 1600;
	gameOverObject.size.y = 900;
	gameOverObject.isVisible = 0;
	gameOverObject.imagePath = TEXT("images/15acfd6fa29d9424.bmp");
	gameOverObject.layer = LAYER_BACKGROUND;
}

void GameTimer_GameEnd()
{
	isRunningTimer = 0;
	dangerTimeObject.isVisible = 0;
	gameOverObject.isVisible = 0;
	SoundPlayer_StopAllBGM();
}

// scene�� update ���θ� ����
int GameTimer_Update(float deltaTime)
{
	if (isRunningTimer == 0)
	{
		return 1;
	}

	float lastTime = runningTime;
	runningTime += deltaTime;
	clickTimer += deltaTime;

	float t1 = limitTime - lastTime;
	float t2 = limitTime - runningTime;

	//DANGER TIME�� �� ��
	if ((DANGER_TIME - t1) * (DANGER_TIME - t2) < 0 && limitTime - runningTime < DANGER_TIME)
	{
		// ����� ���
		SoundPlayer_Play(SOUND_EFFECT_DANGERTIME);
	}

	//VERY DANGER TIME�� �� ��
	if ((VERY_DANGER_TIME - t1) * (VERY_DANGER_TIME - t2) < 0 && limitTime - runningTime < VERY_DANGER_TIME)
	{
		dangerTimeObject.isVisible = 1;

		// Very Danger Time�� ������� ���
		SoundPlayer_Play(SOUND_BGM_VERYDANGERTIME);
	}

	// �ð��ʰ� �������ɾ�
	if (t1 * t2 < 0 && limitTime < runningTime)
	{
		SoundPlayer_StopAll();
		SoundPlayer_Play(SOUND_EFFECT_GHOST1);
		gameOverObject.isVisible = 1;
	}

	if (limitTime < runningTime && runningTime <= limitTime + GAMEOVER_TIME)
	{
		// �ð��� �ʰ��� ������ scene�� update�� �������� ����
		return 0;
	}

	if (limitTime + GAMEOVER_TIME <= runningTime)
	{
		Scene_ChangeScene(SCENE_ID_GAMEOVER);
	}

	return 1;
}

void GameTimer_Render(int currentScene)
{
	if (dangerTimeObject.isVisible == 1)
	{
		GDIEngine_PrintObject(dangerTimeObject);
	}

	if (gameOverObject.isVisible == 1)
	{
		if (currentScene == SCENE_ID_LIVINGROOM)
		{
			gameOverObject.imagePath = TEXT("images/��������1�������ɾ�BG.bmp");
		}
		else if (currentScene == SCENE_ID_FIRSTINNERROOM)
		{
			gameOverObject.imagePath = TEXT("images/��������2�������ɾ�BG.bmp");
		}
		else if (currentScene == SCENE_ID_SECONDINNERROOM)
		{
			gameOverObject.imagePath = TEXT("images/��������3�������ɾ�BG.bmp");
		}
		else if (currentScene == SCENE_ID_MIRRORROOM)
		{
			gameOverObject.imagePath = TEXT("images/��������4�������ɾ�BG.bmp");
		}
		GDIEngine_PrintObject(gameOverObject);
	}
}

void GameTimer_AddExtraTime()
{
	float t1 = limitTime - runningTime;
	float t2 = limitTime + EXTRA_TIME - runningTime;

	//DANGER TIME���� ��� ��
	if ((DANGER_TIME - t1) * (DANGER_TIME - t2) < 0 && limitTime + EXTRA_TIME - runningTime > DANGER_TIME)
	{

	}

	//VERY DANGER TIME���� ��� ��
	if ((VERY_DANGER_TIME - t1) * (VERY_DANGER_TIME - t2) < 0 && limitTime + EXTRA_TIME - runningTime > VERY_DANGER_TIME)
	{
		dangerTimeObject.isVisible = 0;

		// �⺻������� �ٽ� ���
		SoundPlayer_Play(SOUND_BGM_MAIN);
	}

	limitTime += EXTRA_TIME;
}

void GameTimer_SubPenaltyTime()
{
	if (clickTimer < ALLOWED_CLICK_PERIOD)
	{
		// DangerTime�� ���� �ʴ� ������ �г�Ƽ �ο�
		if (limitTime - runningTime > DANGER_TIME + PENALTY_TIME)
		{
			limitTime -= PENALTY_TIME;
		}
	}

	// Ŭ��Ÿ�̸� �ʱ�ȭ
	clickTimer = 0.0f;
}

float GameTimer_GetRemainingTime()
{
	return limitTime - runningTime;
}