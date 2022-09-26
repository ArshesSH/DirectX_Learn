#include "framework.h"
#include "Gizmo.h"

Gizmo::Gizmo()
{
	D3DXMatrixIdentity( &matRot );
}

void Gizmo::Setup( D3DCOLOR c, D3DXMATRIXA16& mat )
{
	matRot = mat;

	PC_VERTEX v;

	v.c = c;

	//Front
	{
		v.p = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
		vertices.push_back( v );
		v.p = D3DXVECTOR3( 1.0f, -1.0f, -1.0f );
		vertices.push_back( v );
		v.p = D3DXVECTOR3( -1.0f, -1.0f, -1.0f );
		vertices.push_back( v );
	}
	//Right
	{
		v.p = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
		vertices.push_back( v );
		v.p = D3DXVECTOR3( 1.0f, -1.0f, 1.0f );
		vertices.push_back( v );
		v.p = D3DXVECTOR3( 1.0f, -1.0f, -1.0f );
		vertices.push_back( v );
	}
	//Back
	{
		v.p = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
		vertices.push_back( v );
		v.p = D3DXVECTOR3( -1.0f, -1.0f, 1.0f );
		vertices.push_back( v );
		v.p = D3DXVECTOR3( 1.0f, -1.0f, 1.0f );
		vertices.push_back( v );
	}
	//Left
	{
		v.p = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
		vertices.push_back( v );
		v.p = D3DXVECTOR3( -1.0f, -1.0f, 1.0f );
		vertices.push_back( v );
		v.p = D3DXVECTOR3( -1.0f, -1.0f, 1.0f );
		vertices.push_back( v );
	}
	//bottom
	{
		v.p = D3DXVECTOR3( -1.0f, -1.0f, -1.0f );
		vertices.push_back( v );
		v.p = D3DXVECTOR3( 1.0f, -1.0f, -1.0f );
		vertices.push_back( v );
		v.p = D3DXVECTOR3( 1.0f, -1.0f, 1.0f );
		vertices.push_back( v );

		v.p = D3DXVECTOR3( -1.0f, -1.0f, -1.0f );
		vertices.push_back( v );
		v.p = D3DXVECTOR3( 1.0f, -1.0f, 1.0f );
		vertices.push_back( v );
		v.p = D3DXVECTOR3( -1.0f, -1.0f, 1.0f );
		vertices.push_back( v );
	}
}

void Gizmo::Draw()
{
	D3DXMATRIXA16 matWorld, matS;
	D3DXMatrixScaling( &matS, 0.1f, 2.0f, 0.1f );
	D3DXMatrixIdentity( &matWorld );
	matWorld = matS * matRot;

	g_pD3DDevice->SetTransform( D3DTS_WORLD, &matWorld );
	g_pD3DDevice->SetFVF( PC_VERTEX::FVF );
	g_pD3DDevice->DrawPrimitiveUP( D3DPT_TRIANGLELIST, vertices.size() / 3, &vertices[0], sizeof( PC_VERTEX ) );
}
