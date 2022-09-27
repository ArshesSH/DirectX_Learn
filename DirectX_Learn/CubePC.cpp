#include "framework.h"
#include "CubePC.h"

CubePC::CubePC()
	:
	vPosition(0,0,0),
	vDirection(0,0,1),
	fRotY(0.0f)
{
	D3DXMatrixIdentity( &matWorld );
}

void CubePC::Setup()
{
	PC_VERTEX v;


	//Front ClockWise
	{
		v.c = D3DCOLOR_XRGB( rand() % 256, rand() % 256, rand() % 256 );
		v.p = D3DXVECTOR3( -1.0f, -1.0f, -1.0f );
		vertices.push_back( v );
		v.p = D3DXVECTOR3( -1.0f, 1.0f, -1.0f );
		vertices.push_back( v );
		v.p = D3DXVECTOR3( 1.0f, 1.0f, -1.0f );
		vertices.push_back( v );

		v.p = D3DXVECTOR3( -1.0f, -1.0f, -1.0f );
		vertices.push_back( v );
		v.p = D3DXVECTOR3( 1.0f, 1.0f, -1.0f );
		vertices.push_back( v );
		v.p = D3DXVECTOR3( 1.0f, -1.0f, -1.0f );
		vertices.push_back( v );
	}
	// Back
	{
		v.c = D3DCOLOR_XRGB( rand() % 256, rand() % 256, rand() % 256 );
		v.p = D3DXVECTOR3( -1.0f, -1.0f, 1.0f );
		vertices.push_back( v );
		v.p = D3DXVECTOR3( 1.0f, 1.0f, 1.0f );
		vertices.push_back( v );
		v.p = D3DXVECTOR3( -1.0f, 1.0f, 1.0f );
		vertices.push_back( v );

		v.p = D3DXVECTOR3( -1.0f, -1.0f, 1.0f );
		vertices.push_back( v );
		v.p = D3DXVECTOR3( 1.0f, -1.0f, 1.0f );
		vertices.push_back( v );
		v.p = D3DXVECTOR3( 1.0f, 1.0f, 1.0f );
		vertices.push_back( v );
	}

	// Left
	{
		v.c = D3DCOLOR_XRGB( rand() % 256, rand() % 256, rand() % 256 );
		v.p = D3DXVECTOR3( -1.0f, -1.0f, 1.0f );
		vertices.push_back( v );
		v.p = D3DXVECTOR3( -1.0f, 1.0f, 1.0f );
		vertices.push_back( v );
		v.p = D3DXVECTOR3( -1.0f, 1.0f, -1.0f );
		vertices.push_back( v );

		v.p = D3DXVECTOR3( -1.0f, -1.0f, 1.0f );
		vertices.push_back( v );
		v.p = D3DXVECTOR3( -1.0f, -1.0f, -1.0f );
		vertices.push_back( v );
		v.p = D3DXVECTOR3( -1.0f, 1.0f, -1.0f );
		vertices.push_back( v );
	}

	// Right
	{
		v.c = D3DCOLOR_XRGB( rand() % 256, rand() % 256, rand() % 256 );
		v.p = D3DXVECTOR3( 1.0f, -1.0f, -1.0f );
		vertices.push_back( v );
		v.p = D3DXVECTOR3( 1.0f, 1.0f, -1.0f );
		vertices.push_back( v );
		v.p = D3DXVECTOR3( 1.0f, 1.0f, 1.0f );
		vertices.push_back( v );

		v.p = D3DXVECTOR3( 1.0f, -1.0f, -1.0f );
		vertices.push_back( v );
		v.p = D3DXVECTOR3( 1.0f, 1.0f, 1.0f );
		vertices.push_back( v );
		v.p = D3DXVECTOR3( 1.0f, -1.0f, 1.0f );
		vertices.push_back( v );
	}
	//Top
	{
		v.c = D3DCOLOR_XRGB( rand() % 256, rand() % 256, rand() % 256 );
		v.p = D3DXVECTOR3( -1.0f, 1.0f, -1.0f );
		vertices.push_back( v );
		v.p = D3DXVECTOR3( -1.0f, 1.0f, 1.0f );
		vertices.push_back( v );
		v.p = D3DXVECTOR3( 1.0f, 1.0f, 1.0f );
		vertices.push_back( v );

		v.p = D3DXVECTOR3( -1.0f, 1.0f, -1.0f );
		vertices.push_back( v );
		v.p = D3DXVECTOR3( 1.0f, 1.0f, 1.0f );
		vertices.push_back( v );
		v.p = D3DXVECTOR3( 1.0f, 1.0f, -1.0f );
		vertices.push_back( v );
	}
	//Bottom
	{
		v.c = D3DCOLOR_XRGB( rand() % 256, rand() % 256, rand() % 256 );
		v.p = D3DXVECTOR3( -1.0f, -1.0f, 1.0f );
		vertices.push_back( v );
		v.p = D3DXVECTOR3( -1.0f, -1.0f, -1.0f );
		vertices.push_back( v );
		v.p = D3DXVECTOR3( 1.0f, -1.0f, -1.0f );
		vertices.push_back( v );

		v.p = D3DXVECTOR3( -1.0f, -1.0f, 1.0f );
		vertices.push_back( v );
		v.p = D3DXVECTOR3( 1.0f, -1.0f, -1.0f );
		vertices.push_back( v );
		v.p = D3DXVECTOR3( 1.0f, -1.0f, 1.0f );
		vertices.push_back( v );
	}
}

void CubePC::Update()
{
	if ( GetAsyncKeyState( 'W' ) & 0x8000 )
	{
		vPosition += (vDirection * 0.1f);
	}
	if ( GetAsyncKeyState( 'S' ) & 0x8000 )
	{
		vPosition -= (vDirection * 0.1f);
	}
	if ( GetAsyncKeyState( 'A' ) & 0x8000 )
	{
		fRotY -= 0.1f;
	}
	if ( GetAsyncKeyState( 'D' ) & 0x8000 )
	{
		fRotY += 0.1f;
	}

	RECT rc;
	GetClientRect( g_hWnd, &rc );

	D3DXMATRIXA16 matR, matT;

	// Create Rotateion by Angle
	D3DXMatrixRotationY( &matR, fRotY );
	vDirection = D3DXVECTOR3( 0, 0, 1 );
	D3DXVec3TransformNormal( &vDirection, &vDirection, &matR );

	D3DXMatrixTranslation( &matT, vPosition.x, vPosition.y, vPosition.z );
	matWorld = matR * matT;
}

void CubePC::Render()
{
	g_pD3DDevice->SetRenderState( D3DRS_CULLMODE, false );
	g_pD3DDevice->SetTransform( D3DTS_WORLD, &matWorld );
	g_pD3DDevice->SetFVF( PC_VERTEX::FVF );
	g_pD3DDevice->DrawPrimitiveUP( D3DPT_TRIANGLELIST, vertices.size() / 3, &vertices[0], sizeof( PC_VERTEX ) );
}

D3DXVECTOR3& CubePC::GetPosition()
{
	return vPosition;
}
