#pragma once

#include <Windows.h>


// 매 프레임 render 후 실행되어 입력에 관한 정보를 초기화한다.
void Input_Init();

// WinProc에서 호출하여 마우스의 클릭 정보를 저장한다.
// 마우스 왼쪽 버튼 눌림
void Input_SetMouseLeftDown(int x, int y);

// 마우스 왼쪽 버튼 떨어짐
void Input_SetMouseLeftUp(int x, int y);

// 마우스 오른쪽 버튼 눌림
void Input_SetMouseRightDown(int x, int y);

// 마우스 오른쪽 버튼 떨어짐
void Input_SetMouseRightUp(int x, int y);


// Update에서 호출하여 마우스 입력값을 얻는데 사용한다.

// 마우스 왼쪽 버튼이 마지막으로 눌렸던 위치 반환
POINT Input_GetMouseLeftDownPosition();

// 마우스 왼쪽 버튼이 마지막으로 떨어졌던 위치 반환
POINT Input_GetMouseLeftUpPosition();

// 마우스 오른쪽 버튼이 마지막으로 눌렸던 위치 반환
POINT Input_GetMouseRightDownPosition();

// 마우스 오른쪽 버튼이 마지막으로 떨어졌던 위치 반환
POINT Input_GetMouseRightUpPosition();


// 이번 프레임에 마우스 왼쪽 버튼이 눌렸는가를 반환
int Input_GetMouseLeftDownNow();

// 이번 프레임에 마우스 왼쪽 버튼이 떨어졌는가를 반환
int Input_GetMouseLeftUpNow();

// 이번 프레임에 마우스 오른쪽 버튼이 눌렸는가를 반환
int Input_GetMouseRightDownNow();

// 이번 프레임에 마우스 오른쪽 버튼이 떨어졌는가를 반환
int Input_GetMouseRightUpNow();



// 마우스 왼쪽 버튼이 눌렸는가를 반환
int Input_GetMouseLeftDown();

// 마우스 왼쪽 버튼이 떨어졌는가를 반환
int Input_GetMouseLeftUp();

// 마우스 오른쪽 버튼이 눌렸는가를 반환
int Input_GetMouseRightDown();

// 마우스 오른쪽 버튼이 떨어졌는가를 반환
int Input_GetMouseRightUp();
