#pragma once

void GameTimer_GameStart();

void GameTimer_GameEnd();

int GameTimer_Update(float deltaTime);

void GameTimer_Render(int currentScene);

void GameTimer_AddExtraTime();

void GameTimer_SubPenaltyTime();

float GameTimer_GetRemainingTime();