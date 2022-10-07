#include "framework.h"
#include "ObjMap.h"
#include "ObjLoader.h"

ObjMap::ObjMap( IN char* szFolder, IN char* szFile, IN D3DXMATRIXA16* pMat )
{
	Load( szFolder, szFile, pMat );
}

ObjMap::~ObjMap( void )
{
}

void ObjMap::Load( IN char* szFolder, IN char* szFile, IN D3DXMATRIXA16* pMat )
{
	ObjLoader loader;
	loader.LoadSurface( surfaces, szFolder, szFile, pMat );
}

bool ObjMap::GetHeight( IN float x, OUT float& y, IN float z )
{
	D3DXVECTOR3 rayPos( x, 1000.0f, z );
	D3DXVECTOR3 rayDir( 0.0f, -1.0f, 0.0f );
	for ( size_t i = 0; i < surfaces.size(); i += 3 )
	{
		float u, v, f;
		if ( D3DXIntersectTri(
			&surfaces[i + 0],
			&surfaces[i + 1],
			&surfaces[i + 2],
			&rayPos,
			&rayDir,
			&u, &v, &f )
			)
		{
			y = 1000 - f;
			return true;
		}
	}

	return false;
}
