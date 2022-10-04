#pragma once
#include "Object.h"

class MtlTex : public Object
{
public:
	MtlTex();
	~MtlTex();
private:
	SYNTHESIZE_PASS_BY_REF( D3DMATERIAL9, mtl, Material )
	SYNTHESIZE_ADD_REF( LPDIRECT3DTEXTURE9, pTexture, Texture )
};

