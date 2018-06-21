#include "stdafx.h"
#include "MainProc.h"


#ifdef _DEBUG
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")
#define new new(_CLIENT_BLOCK,__FILE__,__LINE)
#endif // _DEBUG

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
	wc.lpszClassName = L"WindowClass";

	RegisterClassEx(&wc);
	
	return CreateWindowEx(NULL,
		L"WindowClass",
		L"DirectX9 FrameWork Base",
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

void Winmain::Directx9Set() 
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

HRESULT Winmain::Directx3D9Set() //����
{
	IDirect3D9 *_d3d9;
	_d3d9 = Direct3DCreate9(D3D_SDK_VERSION);

	D3DCAPS9 caps;
	_d3d9->GetDeviceCaps(D3DADAPTER_DEFAULT, //�⺻ ���÷��� ����͸� ǥ���Ѵ�.
		D3DDEVTYPE_HAL, //��ġ Ÿ���� �����Ѵ�. ������ D3DDEVTYPE_HAL�̴�
		&caps); //�⺻ ���÷��� ������� Ư������ ä���� D3DCAPS9 ����ü�� �����Ѵ�.

	//�ϵ���� ���ؽ� ���μ����� �̿��� �� �ִ°�?
	int vp = 0;
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		//�׷���. �ϵ���� ���ؽ� ���μ����� �����ȴٴ� �����
		//'vp'�� �����Ѵ�.
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		//�׷��� �ʴ�. ����Ʈ���� ���ؽ� ���μ����� �̿��ؾ� �Ѵٴ�
		//����� 'vp'�� �����Ѵ�.
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
	hr = _d3d9->CreateDevice(D3DADAPTER_DEFAULT, //�⺻ �����
		D3DDEVTYPE_HAL,						     //��ġ Ÿ��
		hWnd,								     //��ġ�� ����� �ڵ�
		D3DCREATE_HARDWARE_VERTEXPROCESSING,     //���ؽ� ���μ��� Ÿ��
		&_d3d9pp,							     //�ÿ� ����
		&d3dxdevice);						     //������ ��ġ

	if (hr == S_FALSE)
	{
		::MessageBox(0, L"CreateDevice() - FAILED", 0, 0);
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

	D3DXCreateSprite(DEVICE, &lp_sprite);

	main.Init();
	
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;

	const float frame = 1.0f / 60.0f;

	INT64 lastTime = 0.0f;
	INT64 nowTime = 0.0f;
	double timeElapsed = 0.0f;

	lastTime = timeGetTime();
	float deltatime = 0.0f;

	float fpstime = timeGetTime();
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
			nowTime = timeGetTime();
			TIMEMANAGER->SetDeltaTime((nowTime - lastTime) * 0.001f);

			if(TIMEMANAGER->GetDeltaTime() >= frame)
			{
				main.Update();

				d3dxdevice->Clear(0, NULL, D3DCLEAR_STENCIL | D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xff0000ff, 1.0f, 0);
				d3dxdevice->BeginScene();

				main.Render();
				d3dxdevice->EndScene();
				d3dxdevice->Present(0, 0, 0, 0);
				TIMEMANAGER->AddCount();

				lastTime = timeGetTime();
			}
		}
#ifdef _DEBUG
			TIMEMANAGER->Drawfps();
#endif
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
