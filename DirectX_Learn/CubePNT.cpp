#include "framework.h"
#include "CubePNT.h"

CubePNT::CubePNT()
{
}

CubePNT::~CubePNT()
{
}

void CubePNT::Setup()
{
	std::vector<PNT_VERTEX> _vertices;
	_vertices.resize( 8 );

	_vertices[0].p.x = -0.5f; _vertices[0].p.y = -0.5f; _vertices[0].p.z = -0.5f;
	_vertices[1].p.x = -0.5f; _vertices[1].p.y = 0.5f; _vertices[1].p.z = -0.5f;
	_vertices[2].p.x = 0.5f; _vertices[2].p.y = 0.5f; _vertices[2].p.z = -0.5f;
	_vertices[3].p.x = 0.5f; _vertices[3].p.y = -0.5f; _vertices[3].p.z = -0.5f;

	_vertices[4].p.x = -0.5f;	_vertices[4].p.y = -0.5f;	_vertices[4].p.z = 0.5f;
	_vertices[5].p.x = -0.5f;	_vertices[5].p.y = 0.5f;	_vertices[5].p.z = 0.5f;
	_vertices[6].p.x = 0.5f;	_vertices[6].p.y = 0.5f;	_vertices[6].p.z = 0.5f;
	_vertices[7].p.x = 0.5f;	_vertices[7].p.y = -0.5f;	_vertices[7].p.z = 0.5f;

	std::vector<DWORD> indices;
	// Front;
	indices.push_back( 0 );	indices.push_back( 1 );	indices.push_back( 2 );
	indices.push_back( 0 );	indices.push_back( 2 );	indices.push_back( 3 );
	// Back
	indices.push_back( 4 );	indices.push_back( 6 );	indices.push_back( 5 );
	indices.push_back( 4 );	indices.push_back( 7 );	indices.push_back( 6 );
	// Left
	indices.push_back( 4 );	indices.push_back( 5 );	indices.push_back( 1 );
	indices.push_back( 4 );	indices.push_back( 1 );	indices.push_back( 0 );
	// Right
	indices.push_back( 3 );	indices.push_back( 2 );	indices.push_back( 6 );
	indices.push_back( 3 );	indices.push_back( 6 );	indices.push_back( 7 );
	// Top
	indices.push_back( 1 );	indices.push_back( 5 );	indices.push_back( 6 );
	indices.push_back( 1 );	indices.push_back( 6 );	indices.push_back( 2 );
	// Bottom
	indices.push_back( 4 );	indices.push_back( 0 );	indices.push_back( 3 );
	indices.push_back( 4 );	indices.push_back( 3 );	indices.push_back( 7 );

	vertices.resize( 36 );
	for ( size_t i = 0; i < indices.size(); i += 3 )
	{
		vertices[i + 0] = _vertices[indices[i + 0]];
		vertices[i + 1] = _vertices[indices[i + 1]];
		vertices[i + 2] = _vertices[indices[i + 2]];
	}

	D3DXVECTOR3 u, v, n;
	for ( int i = 0; i < 36; i += 3 )
	{
		u = vertices[i + 1].p - vertices[i].p;
		v = vertices[i + 2].p - vertices[i].p;

		D3DXVec3Cross( &n, &u, &v );
		D3DXVec3Normalize( &n, &n );

		vertices[i + 0].n = n;
		vertices[i + 1].n = n;
		vertices[i + 2].n = n;
	}
}

void CubePNT::Update()
{
}

void CubePNT::Render()
{
	g_pD3DDevice->SetFVF( PNT_VERTEX::FVF );
	g_pD3DDevice->DrawPrimitiveUP( D3DPT_TRIANGLELIST, vertices.size() / 3, &vertices[0], sizeof( PNT_VERTEX ) );
}
