#pragma once
#include <windows.h>


void MirrorRoomScene_Ready();

void MirrorRoomScene_Init();

void MirrorRoomScene_Update(float deltaTime);

void MirrorRoomScene_Render();

// mousePos ��ġ�� ������Ʈ�� ��ȣ(object �迭������ �ε���)�� ��ȯ�Ѵ�.
// ���� ������Ʈ�� Ŭ������ �ʾҴٸ� -1�� �����Ѵ�.
int mirrorRoomScene_clickedObject(POINT mousePos);

void mirrorRoomScene_objectClickEvent(int objectID);

void mirrorRoomScene_startSceneEvent(int eventID, float defaultTimer);
void mirrorRoomScene_playSceneEvent(float deltaTime);