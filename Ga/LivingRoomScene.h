#pragma once
#include <windows.h>

void LivingRoomScene_Ready();

void LivingRoomScene_Init();

void LivingRoomScene_Update(float deltaTime);

void LivingRoomScene_Render();

int LivingRoomScene_ClickedObject(POINT mousePos);
