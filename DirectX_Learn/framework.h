﻿// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <vector>
#include <string>
#include <cassert>

// DirectX9
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

extern HWND g_hWnd;
#define SAFE_RELEASE(p) { if(p)p->Release(); p = NULL;}	//directX 메모리 해제는 Release를 사용해서함
#define SAFE_DELETE(p){if(p)delete p; p = NULL;}
#define SINGLETON(class_name) \
		private: \
			class_name(void); \
			~class_name(void); \
		public: \
			static class_name* GetInstance() \
			{ \
				static class_name instance; \
				return &instance; \
			}\

struct PC_VERTEX
{
	D3DXVECTOR3 p;
	D3DCOLOR c;

	// 아래 순서와 위의 자료형 순서가 같아야 함
	enum
	{
		FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE
	};
};


#include "DeviceManager.h"
