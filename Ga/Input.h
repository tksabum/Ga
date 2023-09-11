#pragma once

#include <Windows.h>


// �� ������ render �� ����Ǿ� �Է¿� ���� ������ �ʱ�ȭ�Ѵ�.
void Input_Init();

// WinProc���� ȣ���Ͽ� ���콺�� Ŭ�� ������ �����Ѵ�.
// ���콺 ���� ��ư ����
void Input_SetMouseLeftDown(int x, int y);

// ���콺 ���� ��ư ������
void Input_SetMouseLeftUp(int x, int y);

// ���콺 ������ ��ư ����
void Input_SetMouseRightDown(int x, int y);

// ���콺 ������ ��ư ������
void Input_SetMouseRightUp(int x, int y);


// Update���� ȣ���Ͽ� ���콺 �Է°��� ��µ� ����Ѵ�.

// ���콺 ���� ��ư�� ���������� ���ȴ� ��ġ ��ȯ
POINT Input_GetMouseLeftDownPosition();

// ���콺 ���� ��ư�� ���������� �������� ��ġ ��ȯ
POINT Input_GetMouseLeftUpPosition();

// ���콺 ������ ��ư�� ���������� ���ȴ� ��ġ ��ȯ
POINT Input_GetMouseRightDownPosition();

// ���콺 ������ ��ư�� ���������� �������� ��ġ ��ȯ
POINT Input_GetMouseRightUpPosition();


// �̹� �����ӿ� ���콺 ���� ��ư�� ���ȴ°��� ��ȯ
int Input_GetMouseLeftDownNow();

// �̹� �����ӿ� ���콺 ���� ��ư�� �������°��� ��ȯ
int Input_GetMouseLeftUpNow();

// �̹� �����ӿ� ���콺 ������ ��ư�� ���ȴ°��� ��ȯ
int Input_GetMouseRightDownNow();

// �̹� �����ӿ� ���콺 ������ ��ư�� �������°��� ��ȯ
int Input_GetMouseRightUpNow();



// ���콺 ���� ��ư�� ���ȴ°��� ��ȯ
int Input_GetMouseLeftDown();

// ���콺 ���� ��ư�� �������°��� ��ȯ
int Input_GetMouseLeftUp();

// ���콺 ������ ��ư�� ���ȴ°��� ��ȯ
int Input_GetMouseRightDown();

// ���콺 ������ ��ư�� �������°��� ��ȯ
int Input_GetMouseRightUp();
