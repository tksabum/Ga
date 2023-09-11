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

// Scene�� ����ϱ����� ȣ���ؾ��ϴ� �Լ�, currentScene���� ���� �ʱ�ȭ�մϴ�.
void Scene_Ready();

// currentScene�� Update�� ȣ���մϴ�.
void Scene_Update(float deltaTime);

// currentScene�� Render�� ȣ���մϴ�.
void Scene_Render();

// currentScene�� sceneID�� �����մϴ�.
void Scene_ChangeScene(SceneID sceneID);

// ���� �������� scene�� ��ġ�� �����ؼ� ����� ���� �� ����� scene���� �����Ѵ�.
