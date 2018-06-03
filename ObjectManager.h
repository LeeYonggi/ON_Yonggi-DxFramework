#pragma once
#include "SingleTon.h"

#define MAX_OBJECT_SIZE 5

enum OBJECT_STATE
{
	OBJ_BACK		= 0,
	OBJ_BACKGROUND	= 1,
	OBJ_CHARACTER	= 2,
	OBJ_EFFECT		= 3,
	OBJ_UI			= 4
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