#pragma once

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
const float MAX_SIZE_DIVISION = -SCREEN_HEIGHT;

#define SAFE_DELETE(p) { if(p) delete (p); (p)= nullptr;}
#define SAFE_RELEASE(p) { if (p) p->Release(); }

class MainProc;
class Winmain
{
private:
	RECT rc;
	LPDIRECT3D9 d3d9;

public:
	HWND InitWindow(HINSTANCE hInstance);
	void InitWindowRect();
	void Directx9Set();
	HRESULT Directx3D9Set();

	Winmain();
	virtual ~Winmain();
};

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPervInstance, LPSTR lpCmdLine, int nCmdShow);