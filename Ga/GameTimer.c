#include "GameTimer.h"
#include "Scene.h"
#include "GDIEngine.h"
#include "GameObject.h"
#include "SoundPlayer.h"

int isRunningTimer = 0;
float runningTime = 0.0f;
float limitTime = 0.0f;

float clickTimer = 0.0f; // 지난번 클릭으로 부터 지난 시간을 기록

const float DEFAULT_LIMIT_TIME = 80.0f;
const float EXTRA_TIME = 60.0f;
const float PENALTY_TIME = 1.0f;
const float ALLOWED_CLICK_PERIOD = 0.8f; // 설정된 시간안에 다시한번 클릭하면 패널티를 받음

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

// scene의 update 여부를 리턴
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

	//DANGER TIME이 될 때
	if ((DANGER_TIME - t1) * (DANGER_TIME - t2) < 0 && limitTime - runningTime < DANGER_TIME)
	{
		// 경고음 재생
		SoundPlayer_Play(SOUND_EFFECT_DANGERTIME);
	}

	//VERY DANGER TIME이 될 때
	if ((VERY_DANGER_TIME - t1) * (VERY_DANGER_TIME - t2) < 0 && limitTime - runningTime < VERY_DANGER_TIME)
	{
		dangerTimeObject.isVisible = 1;

		// Very Danger Time의 배경음을 재생
		SoundPlayer_Play(SOUND_BGM_VERYDANGERTIME);
	}

	// 시간초과 점프스케어
	if (t1 * t2 < 0 && limitTime < runningTime)
	{
		SoundPlayer_StopAll();
		SoundPlayer_Play(SOUND_EFFECT_GHOST1);
		gameOverObject.isVisible = 1;
	}

	if (limitTime < runningTime && runningTime <= limitTime + GAMEOVER_TIME)
	{
		// 시간이 초과된 동안은 scene의 update를 진행하지 않음
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
			gameOverObject.imagePath = TEXT("images/스테이지1점프스케어BG.bmp");
		}
		else if (currentScene == SCENE_ID_FIRSTINNERROOM)
		{
			gameOverObject.imagePath = TEXT("images/스테이지2점프스케어BG.bmp");
		}
		else if (currentScene == SCENE_ID_SECONDINNERROOM)
		{
			gameOverObject.imagePath = TEXT("images/스테이지3점프스케어BG.bmp");
		}
		else if (currentScene == SCENE_ID_MIRRORROOM)
		{
			gameOverObject.imagePath = TEXT("images/스테이지4점프스케어BG.bmp");
		}
		GDIEngine_PrintObject(gameOverObject);
	}
}

void GameTimer_AddExtraTime()
{
	float t1 = limitTime - runningTime;
	float t2 = limitTime + EXTRA_TIME - runningTime;

	//DANGER TIME에서 벗어날 때
	if ((DANGER_TIME - t1) * (DANGER_TIME - t2) < 0 && limitTime + EXTRA_TIME - runningTime > DANGER_TIME)
	{

	}

	//VERY DANGER TIME에서 벗어날 때
	if ((VERY_DANGER_TIME - t1) * (VERY_DANGER_TIME - t2) < 0 && limitTime + EXTRA_TIME - runningTime > VERY_DANGER_TIME)
	{
		dangerTimeObject.isVisible = 0;

		// 기본배경음을 다시 재생
		SoundPlayer_Play(SOUND_BGM_MAIN);
	}

	limitTime += EXTRA_TIME;
}

void GameTimer_SubPenaltyTime()
{
	if (clickTimer < ALLOWED_CLICK_PERIOD)
	{
		// DangerTime이 되지 않는 선에서 패널티 부여
		if (limitTime - runningTime > DANGER_TIME + PENALTY_TIME)
		{
			limitTime -= PENALTY_TIME;
		}
	}

	// 클릭타이머 초기화
	clickTimer = 0.0f;
}

float GameTimer_GetRemainingTime()
{
	return limitTime - runningTime;
}