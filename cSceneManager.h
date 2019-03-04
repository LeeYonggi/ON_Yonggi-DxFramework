#pragma once


class cSceneManager :
	public SingleTon<cSceneManager>
{
private:
	vector<BaseScene*> scenes;
	int updateScene;
	int pastScene;

public:
	void AddScene(BaseScene *tempScene);
	void Update();
	void Render();
	void Release();

	cSceneManager();
	virtual ~cSceneManager();
};

#define SCENEMANAGER cSceneManager::GetSingleton()