#include "stdafx.h"
#include "cSceneManager.h"


void cSceneManager::AddScene(BaseScene * tempScene)
{
	scenes.push_back(tempScene);
	updateScene = scenes.size() - 1;
}

void cSceneManager::Update()
{
	if (updateScene != pastScene)
	{
		if(pastScene != -1)
			scenes[pastScene]->Release();
		scenes[updateScene]->Init();
		scenes[updateScene]->Update();
		pastScene = updateScene;
	}
	else
		scenes[updateScene]->Update();
}

void cSceneManager::Render()
{
	scenes[pastScene]->Render();
}

void cSceneManager::Release()
{
	for (auto iter : scenes)
	{
		SAFE_DELETE(iter);
	}
	scenes.clear();
}

cSceneManager::cSceneManager()
{
	updateScene = 0;
	pastScene = -1;
}


cSceneManager::~cSceneManager()
{
	Release();
}
