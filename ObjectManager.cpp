#include "stdafx.h"
#include "ObjectManager.h"


void ObjectManager::Init()
{
	for (int i = 0; i < MAX_OBJECT_SIZE; i++)
		m_Object.insert(make_pair(OBJECT_STATE(i), new vector<Object*>));
}

void ObjectManager::ComponentUpdate()
{
	for (auto iter : m_Object)
	{
		for (auto _iter : *(iter.second))
			for (auto c_iter : _iter->M_GetComponent())
				c_iter.second->Update();
	}
}

void ObjectManager::Update()
{
	for (auto iter : m_Object)
	{
		for (auto _iter = iter.second->begin(); _iter != iter.second->end(); )
		{
			if ((*_iter)->GetActive() == false)
			{
				SAFE_RELEASE((*_iter)); SAFE_DELETE((*_iter));
				_iter = iter.second->erase(_iter);
			}
			else
			{
				(*_iter)->Update();
				_iter++;
			}
		}
	}
}

void ObjectManager::Render()
{
	for (auto iter : m_Object)
	{
		for (auto _iter : *(iter.second))
			for (auto c_iter : _iter->M_GetComponent())
				c_iter.second->Render();
	}
	for (auto iter : m_Object)
		for_each(iter.second->begin(), iter.second->end(), [](Object *obj) { obj->Render(); });
}

void ObjectManager::Release()
{
	for (auto iter : m_Object)
	{
		for (auto _iter : *(iter.second))
		{
			SAFE_RELEASE(_iter);
			SAFE_DELETE(_iter);
		}
		iter.second->clear();
	}
	m_Object.clear();
}

Object *ObjectManager::AddObject(OBJECT_STATE state, Object * obj)
{
	auto iter = m_Object.find(state);
	if (iter == m_Object.end()) return nullptr;
	
	obj->Init();
	iter->second->push_back(obj);

	return obj;
}

ObjectManager::ObjectManager()
{
}


ObjectManager::~ObjectManager()
{
	Release();
}
