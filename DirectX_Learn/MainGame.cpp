#include "framework.h"

#include "MainGame.h"

MainGame::MainGame( )
	:
	pD3D( nullptr ),
	pD3DDevice( nullptr ),
	screenDefaultColor(D3DCOLOR_XRGB( 0, 100, 255 ))
{
}
MainGame::MainGame(D3DCOLOR screenDefaultColor = D3DCOLOR_XRGB(0,100,255) )
	:
	pD3D(nullptr),
	pD3DDevice(nullptr),
	screenDefaultColor( screenDefaultColor )
{
}

MainGame::~MainGame()
{
	SAFE_RELEASE( pD3D );
	SAFE_RELEASE( pD3DDevice );
}

void MainGame::Setup()
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

void MainGame::Update()
{
}

void MainGame::Render()
{
	pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, screenDefaultColor, 1.0f, 0);

	pD3DDevice->BeginScene();

	pD3DDevice->EndScene();

	pD3DDevice->Present( NULL, NULL, NULL, NULL );
}
