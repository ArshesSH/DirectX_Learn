#pragma once
#include "Character.h"

class CubeNode;

class CubeMan : public Character
{
public:
	CubeMan();
	virtual ~CubeMan();

	void Setup() override;
	void Update(class iMap* pMap) override;
	void Draw() override;

protected:
	CubeNode* pRoot;
	D3DMATERIAL9 stMtl;

	LPDIRECT3DTEXTURE9 pTexture;
};

