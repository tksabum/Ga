#pragma once

#include <windows.h>

void SettingScene_Ready();

void SettingScene_Init();

void SettingScene_Update(float deltaTime);

void SettingScene_Render();

int SettingScene_ClickedObject(POINT mousePos);
