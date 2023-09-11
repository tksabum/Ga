#pragma once
#include <windows.h>

void GameOverScene_Ready();

void GameOverScene_Init();

void GameOverScene_Update(float deltaTime);

void GameOverScene_Render();

int GameOverScene_ClickedObject(POINT mousePos);