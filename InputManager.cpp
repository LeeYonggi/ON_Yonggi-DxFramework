#include "stdafx.h"
#include "InputManager.h"


void InputManager::Init()
{
	memset(nowKey, false, sizeof(nowKey));
	memset(pastKey, false, sizeof(pastKey));

	cusor = { 0, 0 };
}

void InputManager::Update()
{
	memcpy(pastKey, nowKey, sizeof(pastKey));
	for (int i = 0; i < MAX_KEY; i++)
		nowKey[i] = GetAsyncKeyState(i) & 0x8000;

	GetCursorPos(&cusor);
	ScreenToClient(hWnd, &cusor);
}


InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}
