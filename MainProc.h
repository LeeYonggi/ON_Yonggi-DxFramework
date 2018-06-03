#pragma once


class MainProc
{
private:
	bool windowAct;
public:
	void Init();
	void Update();
	void Render();
	void Release();
	bool GetWAct() { return windowAct; }

	MainProc();
	virtual ~MainProc();
};

