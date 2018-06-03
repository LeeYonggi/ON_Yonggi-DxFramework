#include "stdafx.h"
#include "MainProc.h"


HWND hWnd;
LPD3DXSPRITE lp_sprite = NULL;
LPDIRECT3DDEVICE9 lpd3dDevice = NULL;
IDirect3DDevice9 *d3dxdevice = 0;


HWND Winmain::InitWindow(HINSTANCE hInstance)
{
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = "WindowClass";

	RegisterClassEx(&wc);
	
	return CreateWindowEx(NULL,
		"WindowClass",
		"DirectX9 FrameWork Base",
		WS_OVERLAPPEDWINDOW,
		GetSystemMetrics(SM_CXSCREEN) / 2 - SCREEN_WIDTH / 2, 0,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);
}

void Winmain::InitWindowRect()
{
	RECT rc = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	SetWindowPos(hWnd, NULL, 0, 0, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER | SWP_NOMOVE);
}

void Winmain::Directx9Set() //정익선배 프레임워크
{
	d3d9 = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.Flags = 0;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = TRUE;

	d3d9->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_MIXED_VERTEXPROCESSING,
		&d3dpp,
		&d3dxdevice);
	d3d9->Release();
	d3d9 = NULL;

}

HRESULT Winmain::Directx3D9Set() //내꺼
{
	IDirect3D9 *_d3d9;
	_d3d9 = Direct3DCreate9(D3D_SDK_VERSION);

	D3DCAPS9 caps;
	_d3d9->GetDeviceCaps(D3DADAPTER_DEFAULT, //기본 디스플레이 어댑터를 표기한다.
		D3DDEVTYPE_HAL, //장치 타입을 지정한다. 보통은 D3DDEVTYPE_HAL이다
		&caps); //기본 디스플레이 어댑터의 특성으로 채워진 D3DCAPS9 구조체를 리턴한다.

	//하드웨어 버텍스 프로세싱을 이용할 수 있는가?
	int vp = 0;
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		//그렇다. 하드웨어 버텍스 프로세싱이 지원된다는 사실을
		//'vp'에 저장한다.
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		//그렇지 않다. 소프트웨어 버텍스 프로세싱을 이용해야 한다는
		//사실을 'vp'에 저장한다.
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	D3DPRESENT_PARAMETERS _d3d9pp;
	_d3d9pp.BackBufferWidth = SCREEN_WIDTH;
	_d3d9pp.BackBufferHeight = SCREEN_HEIGHT;
	_d3d9pp.BackBufferFormat = D3DFMT_A8R8G8B8;
	_d3d9pp.BackBufferCount = 1;
	_d3d9pp.MultiSampleType = D3DMULTISAMPLE_NONE;
	_d3d9pp.MultiSampleQuality = 0;
	_d3d9pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	_d3d9pp.hDeviceWindow = hWnd;
	_d3d9pp.Windowed = TRUE;
	_d3d9pp.EnableAutoDepthStencil = TRUE;
	_d3d9pp.AutoDepthStencilFormat = D3DFMT_D24S8;
	_d3d9pp.Flags = 0;
	_d3d9pp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	_d3d9pp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	HRESULT hr;
	hr = _d3d9->CreateDevice(D3DADAPTER_DEFAULT, //기본 어댑터
		D3DDEVTYPE_HAL,						     //장치 타입
		hWnd,								     //장치와 연결된 핸들
		D3DCREATE_HARDWARE_VERTEXPROCESSING,     //버텍스 프로세싱 타입
		&_d3d9pp,							     //시연 인자
		&d3dxdevice);						     //생성된 장치

	if (hr == S_FALSE)
	{
		::MessageBox(0, "CreateDevice() - FAILED", 0, 0);
		return S_FALSE;
	}
	return S_OK;
}


LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			DestroyWindow(hWnd);
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPervInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	Winmain winmain;
	MainProc main;

	hWnd = winmain.InitWindow(hInstance);
	winmain.InitWindowRect();
	winmain.Directx3D9Set();

	main.Init();
	
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	RENDERINGMANAGER->Createbuffer();
	RENDERINGMANAGER->Init();
	RENDERINGMANAGER->View();

	MSG msg;

	const float frame = 1000 / 60;

	TIMEMANAGER->AddLastTime();

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if (GetMessage(&msg, NULL, 0, 0))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				return (int)msg.wParam;
			}
		}
		else if (main.GetWAct())
		{
			TIMEMANAGER->AddNowTime();
			if (TIMEMANAGER->GetDeltaTime() > frame)
			{
				main.Update();

				d3dxdevice->Clear(0, NULL, D3DCLEAR_STENCIL | D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xff0000ff, 1.0f, 0);
				d3dxdevice->BeginScene();

				main.Render();
				d3dxdevice->EndScene();
				d3dxdevice->Present(0, 0, 0, 0);
				TIMEMANAGER->AddLastTime();
			}
		}
		if (msg.message == WM_QUIT)
			break;
	}
	if (d3dxdevice)
		d3dxdevice->Release();
	d3dxdevice = nullptr;

	TIMEMANAGER->ReleaseSingleton();

	main.Release();

	return msg.wParam;
}

Winmain::Winmain()
{
}


Winmain::~Winmain()
{
}
