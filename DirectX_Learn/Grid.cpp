#include "framework.h"
#include "Gizmo.h"
#include "Grid.h"

Grid::Grid()
{
	
}

void Grid::Setup( int tileNum, float interval )
{
	float fMax = tileNum * interval;
	float fMin = -tileNum * interval;

	// Grid
	PC_VERTEX v;
	for ( auto i = 1; i <= tileNum; ++i )
	{
		if ( i % 5 == 0 )
		{
			v.c = D3DCOLOR_XRGB( 255, 255, 255 );
		}
		else
		{
			v.c = D3DCOLOR_XRGB( 128, 128, 128 );
		}

		v.p = D3DXVECTOR3( fMin, 0, i * interval );
		vertices.push_back( v );
		v.p = D3DXVECTOR3( fMax, 0, i * interval );
		vertices.push_back( v );

		v.p = D3DXVECTOR3( fMin, 0, -i * interval );
		vertices.push_back( v );
		v.p = D3DXVECTOR3( fMax, 0, -i * interval );
		vertices.push_back( v );

		v.p = D3DXVECTOR3( i* interval, 0, fMin );
		vertices.push_back( v );
		v.p = D3DXVECTOR3( i * interval, 0, fMax );
		vertices.push_back( v );

		v.p = D3DXVECTOR3( -i * interval, 0, fMin );
		vertices.push_back( v );
		v.p = D3DXVECTOR3( -i * interval, 0, fMax );
		vertices.push_back( v );
	}

	// Axis
	{
		v.c = D3DCOLOR_XRGB( 255, 0, 0 );
		v.p = D3DXVECTOR3( fMin, 0, 0 );
		vertices.push_back( v );
		v.p = D3DXVECTOR3( fMax, 0, 0 );
		vertices.push_back( v );

		v.c = D3DCOLOR_XRGB( 0, 255, 0 );
		v.p = D3DXVECTOR3( 0, fMin, 0 );
		vertices.push_back( v );
		v.p = D3DXVECTOR3( 0, fMax, 0 );
		vertices.push_back( v );

		v.c = D3DCOLOR_XRGB( 0, 0, 255 );
		v.p = D3DXVECTOR3( 0, 0, fMin );
		vertices.push_back( v );
		v.p = D3DXVECTOR3( 0, 0, fMax );
		vertices.push_back( v );
	}

	// Gizmo
	{
		D3DXMATRIXA16 matR;
		Gizmo* pGizmo;
		pGizmo = new Gizmo();
		D3DXMatrixRotationZ( &matR, D3DX_PI / 2.0f );
		pGizmo->Setup( D3DCOLOR_XRGB( 255, 0, 0 ), matR );
		gizmoPtrs.push_back(  pGizmo  );

		pGizmo = new Gizmo();
		D3DXMatrixRotationZ( &matR, D3DX_PI );
		pGizmo->Setup( D3DCOLOR_XRGB( 0, 255, 0 ), matR );
		gizmoPtrs.push_back( pGizmo );

		pGizmo = new Gizmo();
		D3DXMatrixRotationX( &matR, -D3DX_PI / 2.0f );
		pGizmo->Setup( D3DCOLOR_XRGB( 0, 0, 255 ), matR );
		gizmoPtrs.push_back( pGizmo );
	}
}

void Grid::Draw()
{
	g_pD3DDevice->SetRenderState( D3DRS_LIGHTING, false );
	D3DXMATRIXA16 matI;
	D3DXMatrixIdentity( &matI );
	g_pD3DDevice->SetTransform( D3DTS_WORLD, &matI );
	g_pD3DDevice->SetFVF( PC_VERTEX::FVF );
	g_pD3DDevice->DrawPrimitiveUP( D3DPT_LINELIST, vertices.size() / 2, &vertices[0], sizeof( PC_VERTEX ) );
	
	for ( const auto pGizmo : gizmoPtrs )
	{
		pGizmo->Draw();
	}
}
