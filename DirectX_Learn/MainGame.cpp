#include "framework.h"
#include "DeviceManager.h"
#include "MainGame.h"

#include "Camera.h"
#include "CubePC.h"
#include "Grid.h"
#include "CubeMan.h"

MainGame::MainGame( )
	:
	pCubePC( std::make_unique<CubePC>() ),
	pGrid(std::make_unique<Grid>()),
	pCam(std::make_unique<Camera>()),
	pCubeMan(std::make_unique<CubeMan>())
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

	SetupLight();

	pGrid->Setup();
	pCubePC->Setup();
	pCubeMan->Setup();
	pCam->Setup(&pCubeMan->GetPosition());

	g_pD3DDevice->SetRenderState( D3DRS_LIGHTING, false );
}

void MainGame::Update()
{
	//if ( pCubePC )
	//{
	//	pCubePC->Update();
	//}
	if ( pCubeMan )
	{
		pCubeMan->Update();
	}

	// 카메라는 항상 나중에 업데이트
	if ( pCam )
	{
		pCam->Update();
	}
}

void MainGame::Render()
{
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, g_pDeviceManager->screenDefaultColor, 1.0f, 0);

	g_pD3DDevice->BeginScene();

	Draw();

	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present( NULL, NULL, NULL, NULL );
}

void MainGame::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	if ( pCam )
	{
		pCam->WndProc( hWnd, message, wParam, lParam );
	}
}

void MainGame::SetupLight()
{
	D3DLIGHT9 light;
	ZeroMemory( &light, sizeof( D3DLIGHT9 ) );
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Ambient = D3DXCOLOR( 0.8f, 0.8f, 0.8f, 1.0f );
	light.Diffuse = D3DXCOLOR( 0.8f, 0.8f, 0.8f, 1.0f );
	light.Specular = D3DXCOLOR( 0.8f, 0.8f, 0.8f, 1.0f );
	D3DXVECTOR3 dir( 1.0f, -1.0f, 1.0f );
	D3DXVec3Normalize( &dir, &dir );
	light.Direction = dir;
	g_pD3DDevice->SetLight( 0, &light );
	g_pD3DDevice->LightEnable( 0, true );
}

void MainGame::Draw()
{
	
	/* //Draw Line and Triangle
	{
		gfx.DrawLine( lineVertices );
		gfx.DrawTriangle( triVertices );
	}
	*/

	// Draw Grid
	{
		pGrid->Draw();
	}

	// Draw Cube
	{
		//pCubePC->Render();
	}

	// Draw CubeMan
	{
		pCubeMan->Draw();
	}

}
