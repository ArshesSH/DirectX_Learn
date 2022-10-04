#include "framework.h"
#include "ObjGroup.h"

ObjGroup::ObjGroup()
	:
	pMtlTex(nullptr)
{
}

ObjGroup::~ObjGroup()
{
	SAFE_RELEASE( pMtlTex );
}

void ObjGroup::Render()
{
	if ( pMtlTex )
	{
		g_pD3DDevice->SetTexture( 0, pMtlTex->GetTexture() );
		g_pD3DDevice->SetMaterial( &pMtlTex->GetMaterial() );
	}

	g_pD3DDevice->SetFVF( PNT_VERTEX::FVF );
	g_pD3DDevice->DrawPrimitiveUP( D3DPT_TRIANGLELIST, vertices.size() / 3, &vertices[0], sizeof( PNT_VERTEX ) );
}
