// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once


#include "targetver.h"

#define WIN32_LEAN_AND_MEAN
// Windows ��� ����:
#include <windows.h>

// C, C++
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <iostream>
#include <timeapi.h>
#include <vector>
#include <map>
#include <time.h>
#include <algorithm>
#include <list>
#include<MMSystem.h>

using namespace std;

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "msimg32.lib")

#include <Digitalv.h>

//Dx
#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "./x86/d3d9.lib")
#pragma comment(lib, "./x86/d3dx9.lib")

//FrameWork
#include "SingleTon.h"
#include "Object.h"
#include "Component.h"
#include "DataManager.h"
#include "TexVertexRenderer.h"
#include "cCamera.h"
//#include "RenderingManager.h"
#include "ObjectManager.h"
#include "SpriteRenderer.h"
#include "InputManager.h"
#include "cTime.h"
#include "SoundManager.h"
#include "TextManager.h"
#include "BaseScene.h"
#include "cSceneManager.h"

//custom
#include "Camera01.h"
#include "Character.h"
#include "WinMain.h"
#include "MainScene.h"

extern LPD3DXSPRITE lp_sprite;
extern HWND hWnd;
extern IDirect3DDevice9 *d3dxdevice;
#define DEVICE d3dxdevice