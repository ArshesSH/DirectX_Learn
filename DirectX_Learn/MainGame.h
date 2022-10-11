#pragma once

#include "Graphics.h"


class MainGame
{
public:
	MainGame();
	~MainGame();

	void Setup();
	void Update();
	void Render();
	void WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );

	void SetupLight();

	void SetupTexture();
	void DrawTexture();

	void SetupObj();
	void DrawObj();

	void SetupMap();
	void DrawMap();
	void SetupSurface();

	void SetupHeightMap();
	
	void SetupFrustum();
	void DrawFrustum();
	
private:
	void Draw();


	void SetupLine()
	{
		PC_VERTEX v;
		v.c = D3DCOLOR_XRGB( 255, 0, 0 );
		v.p = D3DXVECTOR3( 0, 2, 0 );
		lineVertices.push_back( v );

		v.p = D3DXVECTOR3( 0, -2, 0 );
		lineVertices.push_back( v);
	}
	void SetupTriangle()
	{
		PC_VERTEX v;

		v.c = D3DCOLOR_XRGB( 255, 0, 0 );
		v.p = D3DXVECTOR3( -1, -1, 0 );
		triVertices.push_back( v );

		v.c = D3DCOLOR_XRGB( 0, 255, 0 );
		v.p = D3DXVECTOR3( -1, 1, 0 );
		triVertices.push_back( v );

		v.c = D3DCOLOR_XRGB( 0, 0, 255 );
		v.p = D3DXVECTOR3( 1, 1, 0 );
		triVertices.push_back( v );

	}

	void DrawLine()
	{
		D3DXMATRIXA16 matWorld;
		D3DXMatrixIdentity( &matWorld );
		g_pD3DDevice->SetTransform( D3DTS_WORLD, &matWorld );
		g_pD3DDevice->SetFVF( PC_VERTEX::FVF );
		g_pD3DDevice->DrawPrimitiveUP( D3DPT_LINELIST, lineVertices.size() / 2, &lineVertices[0], sizeof( PC_VERTEX ) );
	}
	void DrawTriangle()
	{
		D3DXMATRIXA16 matWorld;
		D3DXMatrixIdentity( &matWorld );
		g_pD3DDevice->SetTransform( D3DTS_WORLD, &matWorld );
		g_pD3DDevice->SetFVF( PC_VERTEX::FVF );
		g_pD3DDevice->DrawPrimitiveUP( D3DPT_TRIANGLELIST, triVertices.size() / 3, &triVertices[0], sizeof( PC_VERTEX ) );
	}
	
private:
	Graphics gfx;

	//Draw Line
	std::vector<PC_VERTEX> lineVertices;
	//Draw Triangle
	std::vector<PC_VERTEX> triVertices;

	std::unique_ptr<class Camera> pCam;
	std::unique_ptr<class CubePC> pCubePC;
	std::unique_ptr<class Grid> pGrid;
	std::unique_ptr<class CubeMan> pCubeMan;

	// Texture
	LPDIRECT3DTEXTURE9 pTexture;
	std::vector<PT_VERTEX> textureVertices;

	// Obj
	std::vector<class ObjGroup*> pGroups;

	//Map
	std::vector<class ObjGroup*> pMapGroups;
	iMap* pMap;

	// HeightMap
	std::vector<class ObjGroup*> pHeightMapGroups;

	// Frustum Culling
	//std::vector<SPHERE*> frustumSpheres;
	std::vector<std::unique_ptr<SPHERE>> frustumSpheres;
	LPD3DXMESH pFrustumSphereMesh;
	D3DMATERIAL9 frustumMtl;
	class Frustum* pFrustum;

};

