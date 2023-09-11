#pragma once
#include <windows.h>


void MirrorRoomScene_Ready();

void MirrorRoomScene_Init();

void MirrorRoomScene_Update(float deltaTime);

void MirrorRoomScene_Render();

// mousePos 위치의 오브젝트의 번호(object 배열에서의 인덱스)를 반환한다.
// 만약 오브젝트가 클릭되지 않았다면 -1을 리턴한다.
int mirrorRoomScene_clickedObject(POINT mousePos);

void mirrorRoomScene_objectClickEvent(int objectID);

void mirrorRoomScene_startSceneEvent(int eventID, float defaultTimer);
void mirrorRoomScene_playSceneEvent(float deltaTime);