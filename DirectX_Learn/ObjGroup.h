#pragma once
#include "Object.h"

#include "MtlTex.h"

class ObjGroup : public Object
{
public:
	ObjGroup();
	~ObjGroup();

	void Render();
	
private:
	SYNTHESIZE_PASS_BY_REF( std::vector<PNT_VERTEX>, vertices, Vertices )
	SYNTHESIZE_ADD_REF( MtlTex*, pMtlTex, MaterialTexture )

private:

};

