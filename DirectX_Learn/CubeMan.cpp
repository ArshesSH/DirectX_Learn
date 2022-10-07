#include "framework.h"
#include "CubeMan.h"
#include "iMap.h"
#include "CubeNode.h"

#include "CmBody.h"
#include "CmHead.h"
#include "CmLeftArm.h"
#include "CmLeftLeg.h"
#include "CmRightArm.h"
#include "CmRightLeg.h"

CubeMan::CubeMan()
	:
	pRoot(nullptr),
	pTexture(nullptr)
{
}

CubeMan::~CubeMan()
{
	SAFE_RELEASE( pTexture );
}

void CubeMan::Setup()
{
	Character::Setup();

	// Material
	ZeroMemory( &stMtl, sizeof( D3DMATERIAL9 ) );
	stMtl.Ambient = D3DXCOLOR( 0.7f, 0.7f, 0.7f, 1.0f );
	stMtl.Diffuse = D3DXCOLOR( 0.7f, 0.7f, 0.7f, 1.0f );
	stMtl.Specular = D3DXCOLOR( 0.7f, 0.7f, 0.7f, 1.0f );

	D3DXCreateTextureFromFile( g_pD3DDevice, L"Data/Textures/Steve.png", &pTexture );


	CmBody* pBody = new CmBody;
	pBody->Setup();
	pBody->SetParentWorldTM( &worldMat );
	pRoot = pBody;

	CmHead* pHead = new CmHead;
	pHead->Setup();
	pRoot->AddChild( pHead );

	CmLeftArm* pLeftArm = new CmLeftArm;
	pLeftArm->Setup();
	pLeftArm->SetRotDeltaX( 0.1f );
	pRoot->AddChild( pLeftArm );

	CmRightArm* pRightArm = new CmRightArm;
	pRightArm->Setup();
	pRightArm->SetRotDeltaX( -0.1f );
	pRoot->AddChild( pRightArm );

	CmLeftLeg* pLeftLeg = new CmLeftLeg;
	pLeftLeg->Setup();
	pLeftLeg->SetRotDeltaX( -0.1f );
	pRoot->AddChild( pLeftLeg );

	CmRightLeg* pRightLeg = new CmRightLeg;
	pRightLeg->Setup();
	pRightLeg->SetRotDeltaX( 0.1f );
	pRoot->AddChild( pRightLeg );
}

void CubeMan::Update(iMap* pMap)
{
	Character::Update(pMap);
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
		g_pD3DDevice->SetTexture( 0, pTexture );
		if ( pRoot )
		{
			pRoot->Render();
			g_pD3DDevice->SetTexture( 0, nullptr );
		}
		g_pD3DDevice->SetRenderState( D3DRS_LIGHTING, false );
	}
}
