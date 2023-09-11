#include "Scene.h"
#include "GameTimer.h"
#include "GDIEngine.h"

#include <stdio.h>
#pragma warning(disable: 4996) 

void Scene_Ready()
{
	currentScene = SCENE_ID_MAIN;

	sceneList[currentScene]->func_init();
}

void Scene_Update(float deltaTime)
{
	if (GameTimer_Update(deltaTime))
	{
		sceneList[currentScene]->func_update(deltaTime);
	}
}

void Scene_Render()
{
	GDIEngine_BeginPaint();

	sceneList[currentScene]->func_render();
	GameTimer_Render(currentScene);

#ifdef _DEBUG
	static RECT debugRect001 = { 0, 0, 100, 100 };

	char buffer[64];
	int ret = snprintf(buffer, sizeof buffer, "%f", GameTimer_GetRemainingTime());

	if (ret < 0) {
		return EXIT_FAILURE;
	}
	if (ret >= sizeof buffer) {
		
	}

	wchar_t wtext[64];
	mbstowcs(wtext, buffer, strlen(buffer) + 1);

	GDIEngine_PrintText(wtext, debugRect001);
#endif // DEBUG

	GDIEngine_EndPaint();
}

void Scene_ChangeScene(SceneID sceneID)
{
	currentScene = sceneID;

	// 변경된 씬을 초기화 한다.
	sceneList[currentScene]->func_init();
}

