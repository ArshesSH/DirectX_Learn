#include "framework.h"
#include "DeviceManager.h"
#include "MainGame.h"

MainGame::MainGame( )
{
}

MainGame::~MainGame()
{
	g_pDeviceManager->Destroy();
}

void MainGame::Setup()
{
	SetupLine();
	SetupTriangle();
	g_pD3DDevice->SetRenderState( D3DRS_LIGHTING, false );
}

void MainGame::Update()
{
	RECT rc;
	GetClientRect( g_hWnd, &rc );

	D3DXVECTOR3 vEye = D3DXVECTOR3( 0, 0, -5.0f );
	D3DXVECTOR3 vLookAt = D3DXVECTOR3( 0, 0, 0 );
	D3DXVECTOR3 vUp = D3DXVECTOR3( 0, 1, 0 );
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH( &matView, &vEye, &vLookAt, &vUp );
	g_pD3DDevice->SetTransform( D3DTS_VIEW, &matView );

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI / 4.0f, (float)rc.right / (float)rc.bottom, 1.0f, 1000.0f );
	g_pD3DDevice->SetTransform( D3DTS_PROJECTION, &matProj );
}

void MainGame::Render()
{
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, g_pDeviceManager->screenDefaultColor, 1.0f, 0);

	g_pD3DDevice->BeginScene();

	Draw();

	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present( NULL, NULL, NULL, NULL );
}

void MainGame::Draw()
{
	gfx.DrawLine( lineVertices );
	gfx.DrawTriangle( triVertices );
	//DrawLine();
	//DrawTriangle();
}
