#include "stdafx.h"
#include "ObjectManager.h"


void ObjectManager::Init()
{
	for (int i = 0; i < MAX_OBJECT_SIZE; i++)
		m_Object.insert(make_pair(OBJECT_KIND(i), new vector<Object*>));
}

void ObjectManager::ComponentUpdate()
{

	for (auto iter : m_Object)
	{
		for (auto objects : (*iter.second))
			for (auto components : objects->GetComponents())
				if (objects->GetActive()) components.second->Update();
	}
}

void ObjectManager::Update()
{
	ComponentUpdate();
	for (auto iter : m_Object)
	{
		for (auto _iter = iter.second->begin(); _iter != iter.second->end(); )
		{
			if ((*_iter)->GetDestroy())
			{
				SAFE_RELEASE((*_iter)); 
				SAFE_DELETE((*_iter));
				_iter = iter.second->erase(_iter);
			}
			else
			{
				if((*_iter)->GetActive())
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
		for (auto objects : (*iter.second))
			for(auto components : objects->GetComponents())
				if (objects->GetActive()) components.second->Render();
	}
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

Object *ObjectManager::AddObject(OBJECT_KIND state, Object * obj)
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
