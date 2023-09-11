#pragma once
#include <windows.h>


void MainScene_Ready(HWND hwnd);

void MainScene_Init();

void MainScene_Update(float deltaTime);

void MainScene_Render();

int MainScene_ClickedObject(POINT mousePosition);
