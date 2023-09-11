#pragma once
#include <windows.h>

void IntroScene_Ready();

void IntroScene_Init();

void IntroScene_Update(float deltaTime);

void IntroScene_Render();

int IntroScene_ClickedObject(POINT mousePos);
