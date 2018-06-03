#include "stdafx.h"
#include "MainProc.h"


void MainProc::Init()
{
	OBJECTMANAGER->Init();
	windowAct = true;
	SCENEMANAGER->AddScene(new MainScene);
}

void MainProc::Update()
{
	SOUNDMANAGER->Update();
	OBJECTMANAGER->Update();
	SCENEMANAGER->Update();
	INPUTMANAGER->Update();
}

void MainProc::Render()
{
	RENDERINGMANAGER->View();
	OBJECTMANAGER->Render();
	SCENEMANAGER->Render();
}

void MainProc::Release()
{
	RENDERINGMANAGER->Release();
	OBJECTMANAGER->ReleaseSingleton();
	//manager delete
	RENDERINGMANAGER->ReleaseSingleton();
	SCENEMANAGER->ReleaseSingleton();
	TIMEMANAGER->ReleaseSingleton();
	INPUTMANAGER->ReleaseSingleton();
	SOUNDMANAGER->ReleaseSingleton();
}

MainProc::MainProc()
{
}


MainProc::~MainProc()
{
}
