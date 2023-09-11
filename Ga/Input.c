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


//���콺 ��ư�� �� ��������, ó�� ���������� ��ȯ�ϴ� �Լ�. 
void Input_Init()
{
	leftButtonDownNow = 0;
	leftButtonUpNow = 0;
	rightButtonDownNow = 0;
	rightButtonUpNow = 0;

}

// WinProc���� ȣ���Ͽ� ���콺�� Ŭ�� ������ �����Ѵ�.
// ���콺 ���� ��ư ����
void Input_SetMouseLeftDown(int x, int y)
{
	leftButtonDownNow = 1;
	leftButtonDown = 1;

	leftButtonUp = 0;

	mouseLeftDownPosition.x = x;  // ���콺 x ��ǥ
	mouseLeftDownPosition.y = y;  // ���콺 y ��ǥ
}

// ���콺 ���� ��ư ������
void Input_SetMouseLeftUp(int x, int y)
{
	leftButtonUpNow = 1;
	leftButtonUp = 1;

	leftButtonDown = 0;  // ��ư�� ����, false ���·� �ٲ���� �Ѵ�.  

	mouseLeftUpPosition.x = x;
	mouseLeftUpPosition.y = y;
}

// ���콺 ������ ��ư ����
void Input_SetMouseRightDown(int x, int y)
{
	rightButtonDownNow = 1;
	rightButtonDown = 1;

	rightButtonUp = 0;

	mouseRightDownPosition.x = x;
	mouseRightDownPosition.y = y;
}

// ���콺 ������ ��ư ������
void Input_SetMouseRightUp(int x, int y)
{
	rightButtonUpNow = 1;
	rightButtonUp = 1;

	rightButtonDown = 0;

	mouseRightUpPosition.x = x;
	mouseRightUpPosition.y = y;
}




// �̹� �����ӿ� ���콺 ���� ��ư�� ���ȴ°��� ��ȯ
int Input_GetMouseLeftDownNow()
{
	return leftButtonDownNow;
}

// �̹� �����ӿ� ���콺 ���� ��ư�� �������°��� ��ȯ
int Input_GetMouseLeftUpNow()
{
	return leftButtonUpNow;
}

// �̹� �����ӿ� ���콺 ������ ��ư�� ���ȴ°��� ��ȯ
int Input_GetMouseRightDownNow()
{
	return rightButtonDownNow;
}

// �̹� �����ӿ� ���콺 ������ ��ư�� �������°��� ��ȯ
int Input_GetMouseRightUpNow()
{
	return rightButtonUpNow;
}



// ���콺 ���� ��ư�� ���ȴ°��� ��ȯ
int Input_GetMouseLeftDown()
{
	return leftButtonDown;
}

// ���콺 ���� ��ư�� �������°��� ��ȯ
int Input_GetMouseLeftUp()
{
	return leftButtonUp;
}

// ���콺 ������ ��ư�� ���ȴ°��� ��ȯ
int Input_GetMouseRightDown()
{
	return rightButtonDown;
}

// ���콺 ������ ��ư�� �������°��� ��ȯ
int Input_GetMouseRightUp()
{
	return rightButtonUp;
}


// ���콺 ���� ��ư�� ���������� ���ȴ� ��ġ ��ȯ
POINT Input_GetMouseLeftDownPosition()
{
	return mouseLeftDownPosition;
}

// ���콺 ���� ��ư�� ���������� �������� ��ġ ��ȯ
POINT Input_GetMouseLeftUpPosition()
{
	return mouseLeftUpPosition;
}

// ���콺 ������ ��ư�� ���������� ���ȴ� ��ġ ��ȯ
POINT Input_GetMouseRightDownPosition()
{
	return mouseRightDownPosition;
}

// ���콺 ������ ��ư�� ���������� �������� ��ġ ��ȯ
POINT Input_GetMouseRightUpPosition()
{
	return mouseRightUpPosition;
}