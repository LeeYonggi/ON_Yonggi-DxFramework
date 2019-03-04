#pragma once
#include "SingleTon.h"

#define MAX_OBJECT_SIZE 6

enum OBJECT_STATE
{
	OBJ_CAMERA,
	OBJ_BACK,
	OBJ_BACKGROUND,
	OBJ_CHARACTER,
	OBJ_EFFECT,
	OBJ_UI		
};

class ObjectManager :
	public SingleTon<ObjectManager>
{
private:
	map<OBJECT_STATE, vector<Object*>*> m_Object;
public:
	void Init();
	void ComponentUpdate();
	void Update();
	void Render();
	void Release();

	Object *AddObject(OBJECT_STATE state, Object *obj);

	ObjectManager();
	virtual ~ObjectManager();
};

#define OBJECTMANAGER ObjectManager::GetSingleton()