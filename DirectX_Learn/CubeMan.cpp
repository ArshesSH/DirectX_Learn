#include "framework.h"
#include "CubeMan.h"
#include "CubeNode.h"

#include "CmBody.h"
#include "CmHead.h"
#include "CmLeftArm.h"
#include "CmLeftLeg.h"
#include "CmRightArm.h"
#include "CmRightLeg.h"

CubeMan::CubeMan()
{
}

CubeMan::~CubeMan()
{
}

void CubeMan::Setup()
{
	Character::Setup();

	// Material
	ZeroMemory( &stMtl, sizeof( D3DMATERIAL9 ) );
	stMtl.Ambient = D3DXCOLOR( 0.7f, 0.7f, 0.7f, 1.0f );
	stMtl.Diffuse = D3DXCOLOR( 0.7f, 0.7f, 0.7f, 1.0f );
	stMtl.Specular = D3DXCOLOR( 0.7f, 0.7f, 0.7f, 1.0f );


	CmBody* pBody = new CmBody;
	pBody->Setup();
	pBody->SetParentWorldTM( &worldMat );
	pRoot = pBody;

	CmHead* pHead = new CmHead;
	pHead->Setup();
	pRoot->AddChild( pHead );

	CmLeftArm* pLeftArm = new CmLeftArm;
	pLeftArm->Setup();
	pRoot->AddChild( pLeftArm );

	CmRightArm* pRightArm = new CmRightArm;
	pRightArm->Setup();
	pRoot->AddChild( pRightArm );

	CmLeftLeg* pLeftLeg = new CmLeftLeg;
	pLeftLeg->Setup();
	pRoot->AddChild( pLeftLeg );

	CmRightLeg* pRightLeg = new CmRightLeg;
	pRightLeg->Setup();
	pRoot->AddChild( pRightLeg );
}

void CubeMan::Update()
{
	Character::Update();
	if ( pRoot )
	{
		pRoot->Update();
	}
}

void CubeMan::Draw()
{
	if ( g_pD3DDevice )
	{
		g_pD3DDevice->SetRenderState( D3DRS_LIGHTING, true );
		g_pD3DDevice->SetMaterial( &stMtl );

		Character::Draw();

		D3DXMATRIXA16 worldMat;
		D3DXMatrixIdentity( &worldMat );
		g_pD3DDevice->SetTransform( D3DTS_WORLD, &worldMat );
		if ( pRoot )
		{
			pRoot->Render();
		}
		g_pD3DDevice->SetRenderState( D3DRS_LIGHTING, false );
	}
}
