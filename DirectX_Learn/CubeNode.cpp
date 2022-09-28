#include "framework.h"
#include "CubeNode.h"

CubeNode::CubeNode()
	:
	rotDeltaX(0.0f),
	pParentWorldTM(nullptr),
	localPos(0.0f, 0.0f, 0.0f)
{
	D3DXMatrixIdentity( &localTM );
	D3DXMatrixIdentity( &worldTM );
}

CubeNode::~CubeNode()
{
}

void CubeNode::AddChild( CubeNode* pChild )
{
	pChild->pParentWorldTM = &worldTM;
	childs.push_back( pChild );
}

void CubeNode::Destroy()
{
	for ( auto p : childs )
	{
		p->Destroy();
	}
	delete this;
}

void CubeNode::Setup()
{
	CubePNT::Setup();
}

void CubeNode::Update()
{
	CubePNT::Update();

	D3DXMATRIXA16 matR, matT;
	D3DXMatrixIdentity( &matR );
	D3DXMatrixIdentity( &matT );

	D3DXMatrixTranslation( &matT, localPos.x, localPos.y, localPos.z );
	localTM = matR * matT;
	worldTM = localTM;
	if ( pParentWorldTM )
	{
		worldTM *= *pParentWorldTM;
	}
	for ( const auto& p : childs )
	{
		p->Update();
	}
}

void CubeNode::Render()
{
	g_pD3DDevice->SetTransform( D3DTS_WORLD, &worldTM );
	CubePNT::Render();

	for ( const auto& p : childs )
	{
		p->Render();
	}
}
