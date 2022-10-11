#include "framework.h"
#include "Frustum.h"

Frustum::Frustum()
{
}

Frustum::~Frustum()
{
}

void Frustum::Setup()
{
	/*--- Near ---*/
	projVertices.push_back( D3DXVECTOR3( -1.0f, -1.0f, 0.0f ) );	// Left Down
	projVertices.push_back( D3DXVECTOR3( -1.0f, 1.0f, 0.0f ) );		// Left Up
	projVertices.push_back( D3DXVECTOR3( 1.0f, 1.0f, 0.0f ) );		// Right UP
	projVertices.push_back( D3DXVECTOR3( 1.0f, -1.0f, 0.0f ) );		// Right Down

	/*--- Far ---*/
	projVertices.push_back( D3DXVECTOR3( -1.0f, -1.0f, 1.0f ) );	// Left Down
	projVertices.push_back( D3DXVECTOR3( -1.0f, 1.0f, 1.0f ) );		// Left Up
	projVertices.push_back( D3DXVECTOR3( 1.0f, 1.0f, 1.0f ) );		// Right UP
	projVertices.push_back( D3DXVECTOR3( 1.0f, -1.0f, 1.0f ) );		// Right Down

	planes.resize( 6 );
	worldVertices.resize( 8 );
}

void Frustum::Update()
{
	D3DXMATRIXA16 viewMat, projMat;
	g_pD3DDevice->GetTransform( D3DTS_PROJECTION, &projMat );
	g_pD3DDevice->GetTransform( D3DTS_VIEW, &viewMat );


	// Create Vertices Info
	for ( size_t i = 0; i < projVertices.size(); ++i )
	{
		D3DXVec3Unproject(
			&worldVertices[i],
			&projVertices[i],
			nullptr,
			&projMat,
			&viewMat,
			nullptr
		);
	}

	// Create Plane
	{
		/*--- Near Front ---*/
		D3DXPlaneFromPoints( &planes[0], &worldVertices[0], &worldVertices[1], &worldVertices[2] );
		/*--- Far Back ---*/
		D3DXPlaneFromPoints( &planes[1], &worldVertices[6], &worldVertices[5], &worldVertices[4] );
		/*--- Top ---*/
		D3DXPlaneFromPoints( &planes[2], &worldVertices[1], &worldVertices[5], &worldVertices[2] );
		/*--- Bottom ---*/
		D3DXPlaneFromPoints( &planes[3], &worldVertices[0], &worldVertices[3], &worldVertices[7] );
		/*--- Left ---*/
		D3DXPlaneFromPoints( &planes[4], &worldVertices[1], &worldVertices[0], &worldVertices[4] );
		/*--- Right ---*/
		D3DXPlaneFromPoints( &planes[5], &worldVertices[2], &worldVertices[6], &worldVertices[7] );
	}
}


bool Frustum::IsIn( const SPHERE* const pSphere ) const
{
	for ( const D3DXPLANE& p : planes )
	{
		if ( D3DXPlaneDotCoord( &p, &pSphere->centerPos ) > pSphere->radius )
		{
			return false;
		}
	}
	return true;
}
