#pragma once

typedef int SceneID;
#define SCENE_ID_MAIN 0
#define SCENE_ID_GAME 1
#define SCENE_ID_SETTING 2
#define SCENE_ID_MIRRORROOM 3
#define SCENE_ID_LIVINGROOM 4
#define SCENE_ID_FIRSTINNERROOM 5
#define SCENE_ID_SECONDINNERROOM 6
#define SCENE_ID_GAMEOVER 7
#define SCENE_ID_INTRO 8
#define SCENE_ID_ENDING 9

#define NUMBER_OF_SCENE 10


//#define NUMBER_OF_SCENE 8

typedef struct _Scene
{
	SceneID id;

	void (*func_init)();
	void (*func_update)(float deltaTime);
	void (*func_render)();
} Scene;

SceneID currentScene;
//SceneID currentScene;
Scene* sceneList[NUMBER_OF_SCENE];

// Scene을 사용하기전에 호출해야하는 함수, currentScene등의 값을 초기화합니다.
void Scene_Ready();

// currentScene의 Update를 호출합니다.
void Scene_Update(float deltaTime);

// currentScene의 Render를 호출합니다.
void Scene_Render();

// currentScene을 sceneID로 변경합니다.
void Scene_ChangeScene(SceneID sceneID);

// 현재 진행중인 scene의 위치를 저장해서 재시작 했을 때 저장된 scene에서 시작한다.
