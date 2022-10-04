// header.h: 표준 시스템 포함 파일
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
#include <memory>

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

#define SYNTHESIZE(varType, varName, funcName) \
	protected: varType varName; \
	public: \
	inline varType Get##funcName(void) const {return varName;} \
	inline void Set##funcName(varType var) {varName = var;} \
	
#define SYNTHESIZE_PASS_BY_REF(varType, varName, funcName) \
	protected: varType varName; \
	public: \
	inline varType& Get##funcName(void) {return varName;} \
	inline void Set##funcName(varType& var) {varName = var;} \

#define SAFE_ADD_REF(p) {if(p) p->AddRef();}

#define SYNTHESIZE_ADD_REF(varType, varName, funcName) \
	protected: varType varName; \
	public: \
	inline varType Get##funcName(void) const {return varName;} \
	inline void Set##funcName(varType var) { \
		if(varName != var) { \
			SAFE_ADD_REF(var); \
			SAFE_RELEASE(varName); \
			varName = var; \
		} \
	} \


struct PC_VERTEX	//PointAndColor
{
	D3DXVECTOR3 p;
	D3DCOLOR c;

	// 아래 순서와 위의 자료형 순서가 같아야 함
	enum
	{
		FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE
	};
};

struct PNT_VERTEX	//PointAndTexture
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	D3DXVECTOR2 t;

	// 아래 순서와 위의 자료형 순서가 같아야 함
	enum
	{
		FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1
	};
};

struct PT_VERTEX	//PointAndTexture
{
	D3DXVECTOR3 p;
	D3DXVECTOR2 t;

	// 아래 순서와 위의 자료형 순서가 같아야 함
	enum
	{
		FVF = D3DFVF_XYZ | D3DFVF_TEX1
	};
};


#include "DeviceManager.h"
#include "ObjectManager.h"
#include "Object.h"
#include "TextureManager.h"
