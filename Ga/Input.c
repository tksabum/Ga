#include "Input.h"


int leftButtonDownNow = 0;
int leftButtonDown = 0;
int leftButtonUpNow = 0;
int leftButtonUp = 0;

int rightButtonDownNow = 0;
int rightButtonDown = 0;
int rightButtonUpNow = 0;
int rightButtonUp = 0;

POINT mouseLeftDownPosition;
POINT mouseLeftUpPosition;
POINT mouseRightDownPosition;
POINT mouseRightUpPosition;


//마우스 버튼을 꾹 눌렀을때, 처음 눌렀을떄만 반환하는 함수. 
void Input_Init()
{
	leftButtonDownNow = 0;
	leftButtonUpNow = 0;
	rightButtonDownNow = 0;
	rightButtonUpNow = 0;

}

// WinProc에서 호출하여 마우스의 클릭 정보를 저장한다.
// 마우스 왼쪽 버튼 눌림
void Input_SetMouseLeftDown(int x, int y)
{
	leftButtonDownNow = 1;
	leftButtonDown = 1;

	leftButtonUp = 0;

	mouseLeftDownPosition.x = x;  // 마우스 x 좌표
	mouseLeftDownPosition.y = y;  // 마우스 y 좌표
}

// 마우스 왼쪽 버튼 떨어짐
void Input_SetMouseLeftUp(int x, int y)
{
	leftButtonUpNow = 1;
	leftButtonUp = 1;

	leftButtonDown = 0;  // 버튼을 떼면, false 상태로 바꿔줘야 한다.  

	mouseLeftUpPosition.x = x;
	mouseLeftUpPosition.y = y;
}

// 마우스 오른쪽 버튼 눌림
void Input_SetMouseRightDown(int x, int y)
{
	rightButtonDownNow = 1;
	rightButtonDown = 1;

	rightButtonUp = 0;

	mouseRightDownPosition.x = x;
	mouseRightDownPosition.y = y;
}

// 마우스 오른쪽 버튼 떨어짐
void Input_SetMouseRightUp(int x, int y)
{
	rightButtonUpNow = 1;
	rightButtonUp = 1;

	rightButtonDown = 0;

	mouseRightUpPosition.x = x;
	mouseRightUpPosition.y = y;
}




// 이번 프레임에 마우스 왼쪽 버튼이 눌렸는가를 반환
int Input_GetMouseLeftDownNow()
{
	return leftButtonDownNow;
}

// 이번 프레임에 마우스 왼쪽 버튼이 떨어졌는가를 반환
int Input_GetMouseLeftUpNow()
{
	return leftButtonUpNow;
}

// 이번 프레임에 마우스 오른쪽 버튼이 눌렸는가를 반환
int Input_GetMouseRightDownNow()
{
	return rightButtonDownNow;
}

// 이번 프레임에 마우스 오른쪽 버튼이 떨어졌는가를 반환
int Input_GetMouseRightUpNow()
{
	return rightButtonUpNow;
}



// 마우스 왼쪽 버튼이 눌렸는가를 반환
int Input_GetMouseLeftDown()
{
	return leftButtonDown;
}

// 마우스 왼쪽 버튼이 떨어졌는가를 반환
int Input_GetMouseLeftUp()
{
	return leftButtonUp;
}

// 마우스 오른쪽 버튼이 눌렸는가를 반환
int Input_GetMouseRightDown()
{
	return rightButtonDown;
}

// 마우스 오른쪽 버튼이 떨어졌는가를 반환
int Input_GetMouseRightUp()
{
	return rightButtonUp;
}


// 마우스 왼쪽 버튼이 마지막으로 눌렸던 위치 반환
POINT Input_GetMouseLeftDownPosition()
{
	return mouseLeftDownPosition;
}

// 마우스 왼쪽 버튼이 마지막으로 떨어졌던 위치 반환
POINT Input_GetMouseLeftUpPosition()
{
	return mouseLeftUpPosition;
}

// 마우스 오른쪽 버튼이 마지막으로 눌렸던 위치 반환
POINT Input_GetMouseRightDownPosition()
{
	return mouseRightDownPosition;
}

// 마우스 오른쪽 버튼이 마지막으로 떨어졌던 위치 반환
POINT Input_GetMouseRightUpPosition()
{
	return mouseRightUpPosition;
}