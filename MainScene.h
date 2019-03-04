#pragma once
class MainScene :
	public BaseScene
{
private:
	float camangle;
public:
	void Init();
	void Update();
	void Render();
	void Release();

	MainScene();
	virtual ~MainScene();
};

