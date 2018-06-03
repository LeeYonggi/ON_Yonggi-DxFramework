#pragma once
#include "SingleTon.h"
#define MAX_KEY 156

class InputManager :
	public SingleTon<InputManager>
{
private:
	bool nowKey[MAX_KEY];
	bool pastKey[MAX_KEY];
	POINT cusor;

public:
	void Init();
	void Update();

	bool IsKeyDown(int key) { return (pastKey[key] == false && nowKey[key] == true) ? true : false; }
	bool IsKeyHold(int key) { return (pastKey[key] == true && nowKey[key] == true) ? true : false; }
	bool IsKeyUp(int key)	{ return (pastKey[key] == true && nowKey[key] == false) ? true : false; }
	POINT GetCusorPosition() { return cusor; }

	InputManager();
	virtual ~InputManager();
};

#define INPUTMANAGER InputManager::GetSingleton()