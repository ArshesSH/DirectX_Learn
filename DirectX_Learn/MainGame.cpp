#include "framework.h"
#include "DeviceManager.h"
#include "MainGame.h"

#include "Camera.h"
#include "CubePC.h"
#include "Grid.h"
#include "CubeMan.h"
#include "ObjLoader.h"
#include "ObjGroup.h"
#include "ObjMap.h"
#include "HeightMap.h"
#include "Frustum.h"

MainGame::MainGame()
	:
	pCubePC( std::make_unique<CubePC>() ),
	pGrid( std::make_unique<Grid>() ),
	pCam( std::make_unique<Camera>() ),
	pCubeMan( std::make_unique<CubeMan>() ),
	pTexture( nullptr ),
	pMap( nullptr ),
	pFrustum(nullptr)
{
}

MainGame::~MainGame()
{
	SAFE_DELETE( pFrustum );
	SAFE_DELETE( pMap );
	SAFE_RELEASE( pTexture );
	g_pDeviceManager->Destroy();
}

void MainGame::Setup()
{
	SetupLine();
	SetupTriangle();

	SetupLight();

	pGrid->Setup();

	SetupHeightMap();

	SetupFrustum();

	pCubePC->Setup();
	pCubeMan->Setup();
	//SetupObj();

	//SetupMap();
	//SetupSurface();



	pCam->Setup(&pCubeMan->GetPosition());

	SetupTexture();

	g_pD3DDevice->SetRenderState( D3DRS_LIGHTING, false );
}

void MainGame::Update()
{
	//if ( pCubePC )
	//{
	//	pCubePC->Update();
	//}

	/*
	if ( pCubeMan )
	{
		pCubeMan->Update(pMap);
	}
	*/

	if ( pFrustum )
	{
		pFrustum->Update();
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

	switch ( message )
	{
	case WM_MBUTTONDOWN:
		{
			for ( const auto& pSphere : frustumSpheres )
			{
				if ( pFrustum->IsIn( pSphere.get() ) )
				{
					pSphere->isPicked = true;
				}
				else
				{
					pSphere->isPicked = false;
				}
			}
		}
		break;
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

void MainGame::SetupTexture()
{
	D3DXCreateTextureFromFile( g_pD3DDevice, L"Data/Textures/Steve.png", &pTexture );
	PT_VERTEX v;
	v.p = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	v.t = D3DXVECTOR2( 0.0f, 1.0f );
	textureVertices.push_back( v );

	v.p = D3DXVECTOR3( 0.0f, 2.0f, 0.0f );
	v.t = D3DXVECTOR2( 0.0f, 0.0f );
	textureVertices.push_back( v );

	v.p = D3DXVECTOR3( 2.0f, 2.0f, 0.0f );
	v.t = D3DXVECTOR2( 1.0f, 0.0f );
	textureVertices.push_back( v );

	v.p = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	v.t = D3DXVECTOR2( 0.0f, 1.0f );
	textureVertices.push_back( v );

	v.p = D3DXVECTOR3( -2.0f, 2.0f, 0.0f );
	v.t = D3DXVECTOR2( 1.0f, 0.0f );
	textureVertices.push_back( v );

	v.p = D3DXVECTOR3( 0.0f, 2.0f, 0.0f );
	v.t = D3DXVECTOR2( 0.0f, 0.0f );
	textureVertices.push_back( v );


}

void MainGame::DrawTexture()
{
	if ( g_pD3DDevice )
	{
		g_pD3DDevice->SetRenderState( D3DRS_LIGHTING, false );

		D3DXMATRIXA16 worldMat;
		D3DXMatrixIdentity( &worldMat );
		g_pD3DDevice->SetTransform( D3DTS_WORLD, &worldMat );

		g_pD3DDevice->SetTexture( 0, pTexture );
		g_pD3DDevice->SetFVF( PT_VERTEX::FVF );

		g_pD3DDevice->DrawPrimitiveUP( D3DPT_TRIANGLELIST, textureVertices.size() / 3, &textureVertices[0], sizeof( PT_VERTEX ) );

		g_pD3DDevice->SetTexture( 0, nullptr );
	}
}

void MainGame::SetupObj()
{
	ObjLoader loader;
	loader.Load( pGroups, (char*)"Data/Models", (char*)"box.obj" );
}

void MainGame::DrawObj()
{
	D3DXMATRIXA16 matWorld, matS, matR;
	D3DXMatrixScaling( &matS, 0.1f, 0.1f, 0.1f );
	D3DXMatrixRotationX( &matR, -D3DX_PI / 2.0f );
	matWorld = matS * matR;

	g_pD3DDevice->SetTransform( D3DTS_WORLD, &matWorld );
	for ( auto p : pGroups )
	{
		p->Render();
	}
}

void MainGame::SetupMap()
{
	ObjLoader loader;
	loader.Load( pMapGroups, (char*)"Data/Models", (char*)"Map.obj" );
}

void MainGame::DrawMap()
{
	D3DXMATRIXA16 matWorld, matS, matR;
	D3DXMatrixScaling( &matS, 0.01f, 0.01f, 0.01f );
	D3DXMatrixRotationX( &matR, -D3DX_PI / 2.0f );
	matWorld = matS * matR;

	g_pD3DDevice->SetTransform( D3DTS_WORLD, &matWorld );
	for ( auto p : pMapGroups )
	{
		p->Render();
	}
}

void MainGame::SetupSurface()
{
	D3DXMATRIXA16 matWorld, matS, matR;
	D3DXMatrixScaling( &matS, 0.01f, 0.01f, 0.01f );
	D3DXMatrixRotationX( &matR, -D3DX_PI / 2.0f );
	matWorld = matS * matR;

	pMap = new ObjMap( (char*)"Data/Models", (char*)"map_surface.obj", &matWorld );
}

void MainGame::SetupHeightMap()
{
	HeightMap* pHeightMap = new HeightMap;

	pHeightMap->Setup( "Data/Models/HeightMapData/", "HeightMap.raw", "terrain.jpg" );
	pMap = pHeightMap;
}

void MainGame::SetupFrustum()
{
	D3DXCreateSphere( g_pD3DDevice, 0.5f, 10, 10, &pFrustumSphereMesh, nullptr );
	for ( int z = -20; z <= 20; ++z )
	{
		for ( int y = -20; y <= 20; ++y )
		{
			for ( int x = -20; x <= 20; ++x )
			{
				std::unique_ptr<SPHERE> pSphere = std::make_unique<SPHERE>();
				pSphere->radius = 0.5f;
				pSphere->centerPos = D3DXVECTOR3( (float)x, (float)y, (float)z );
				pSphere->isPicked = true;
				frustumSpheres.push_back( std::move( pSphere ) );
			}
		}
	}

	ZeroMemory( &frustumMtl, sizeof( D3DMATERIAL9 ) );
	frustumMtl.Ambient = D3DXCOLOR( 0.7f, 0.2f, 0.7f, 1.0f );
	frustumMtl.Diffuse = D3DXCOLOR( 0.7f, 0.2f, 0.7f, 1.0f );
	frustumMtl.Specular = D3DXCOLOR( 0.7f, 0.2f, 0.7f, 1.0f );

	pFrustum = new Frustum;
	pFrustum->Setup();
}

void MainGame::DrawFrustum()
{
	D3DXMATRIXA16 worldMat;
	D3DXMatrixIdentity( &worldMat );

	g_pD3DDevice->SetTransform( D3DTS_WORLD, &worldMat );

	for ( const auto& pSphere : frustumSpheres )
	{
		if ( pSphere->isPicked )
		{
			D3DXMatrixIdentity( &worldMat );
			worldMat._41 = pSphere->centerPos.x;
			worldMat._42 = pSphere->centerPos.y;
			worldMat._43 = pSphere->centerPos.z;
			g_pD3DDevice->SetTransform( D3DTS_WORLD, &worldMat );
			g_pD3DDevice->SetMaterial( &frustumMtl );
			pFrustumSphereMesh->DrawSubset( 0 );
		}
	}
}

void MainGame::Draw()
{
	
	/* //Draw Line and Triangle
	{
		gfx.DrawLine( lineVertices );
		gfx.DrawTriangle( triVertices );
	}
	*/

	/*
	// Draw Grid
	{
		if ( pGrid )
		{
			pGrid->Draw();
		}
	}

	// Draw Cube
	{
		//pCubePC->Render();
	}

	// DrawHeightMap();
	{
		if ( pMap )
		{
			pMap->Render();
		}
	}

	// Draw CubeMan
	{
		if ( pCubeMan )
		{
			pCubeMan->Draw();
		}
	}

	//Draw TestTexture
	{
		//DrawTexture();
	}

	//Draw Obj
	{
		//DrawObj();
	}

	//Draw Map
	{
		//DrawMap();
	}
	*/

	//Draw Frustum
	{
		if ( pFrustum )
		{
			DrawFrustum();
		}
	}
}
