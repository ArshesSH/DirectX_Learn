#include "framework.h"
#include "DeviceManager.h"

DeviceManager::DeviceManager()
	:
	pD3D( nullptr ),
	pD3DDevice( nullptr ),
	screenDefaultColor( D3DCOLOR_XRGB( 0, 100, 255 ) )
{
	Init();
}

DeviceManager::~DeviceManager()
{

}

//DeviceManager::DeviceManager( D3DCOLOR screenDefaultColor = D3DCOLOR_XRGB( 0, 100, 255 ) )
//	:
//	pD3D( nullptr ),
//	pD3DDevice( nullptr ),
//	screenDefaultColor( screenDefaultColor )
//{
//	Init();
//}

LPDIRECT3DDEVICE9 DeviceManager::GetDevice()
{
	return pD3DDevice;
}

void DeviceManager::Destroy()
{
	SAFE_RELEASE( pD3DDevice );
	SAFE_RELEASE( pD3D );
}

void DeviceManager::Init()
{
	pD3D = Direct3DCreate9( D3D_SDK_VERSION );

	D3DCAPS9 caps;
	int nVertexProcessing;
	// 하드웨어 성능 체크
	pD3D->GetDeviceCaps( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps );
	if ( caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT )
	{
		//GPU가 처리
		nVertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		//CPU가 처리
		nVertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	D3DPRESENT_PARAMETERS d3dPP;
	ZeroMemory( &d3dPP, sizeof( D3DPRESENT_PARAMETERS ) );
	d3dPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dPP.Windowed = true;
	d3dPP.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dPP.EnableAutoDepthStencil = TRUE;
	d3dPP.AutoDepthStencilFormat = D3DFMT_D16;
	pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, nVertexProcessing, &d3dPP, &pD3DDevice );
}
