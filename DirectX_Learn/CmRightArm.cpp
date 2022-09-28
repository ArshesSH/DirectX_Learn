#include "framework.h"
#include "CmRightArm.h"

void CmRightArm::Setup()
{
	CubeManBodyParts::Setup( { sizeX, sizeY, sizeZ }, { axisX, axisY, axisZ }, { 0.0f, localPosY, 0.0f } );

	//CubeNode::Setup();

	//D3DXMATRIXA16 matS, matT, mat;
	//D3DXMatrixScaling( &matS, sizeX, sizeY, sizeZ );
	//D3DXMatrixTranslation( &matT, -0.3f, -0.3f, 0.0f );
	//mat = matS * matT;

	//for ( size_t i = 0; i < vertices.size(); ++i )
	//{
	//	D3DXVec3TransformCoord( &vertices[i].p, &vertices[i].p, &mat );
	//}

	//localPos.y = localPosY;
}
