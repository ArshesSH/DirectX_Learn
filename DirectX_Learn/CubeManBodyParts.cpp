#include "framework.h"
#include "CubeManBodyParts.h"

void CubeManBodyParts::Setup( D3DXVECTOR3 size, D3DXVECTOR3 axisPos, D3DXVECTOR3 relPos )
{
	CubeNode::Setup();

	D3DXMATRIXA16 matS, matT, mat;
	D3DXMatrixScaling( &matS, size.x, size.y, size.z );
	D3DXMatrixTranslation( &matT, axisPos.x, axisPos.y, axisPos.z );
	mat = matS * matT;

	for ( size_t i = 0; i < vertices.size(); ++i )
	{
		D3DXVec3TransformCoord( &vertices[i].p, &vertices[i].p, &mat );
	}

	localPos.y = relPos.y;
}
