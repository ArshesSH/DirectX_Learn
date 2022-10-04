#include "framework.h"
#include "MtlTex.h"

MtlTex::MtlTex()
	:
	pTexture(nullptr)
{
	ZeroMemory( &mtl, sizeof( D3DMATERIAL9 ) );
}

MtlTex::~MtlTex()
{
	SAFE_RELEASE( pTexture );
}
