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

	std::unique_ptr<class CubePC> pCubePC;
	std::unique_ptr<class Grid> pGrid;
};

