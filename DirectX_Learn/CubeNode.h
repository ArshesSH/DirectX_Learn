#pragma once
#include "CubePNT.h"
class CubeNode : public CubePNT
{
public:
	CubeNode();
	virtual ~CubeNode();

	virtual void AddChild( CubeNode* pChild );
	virtual void Destroy();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;

protected:
	D3DXVECTOR3 localPos;
	D3DXMATRIXA16 localTM;
	D3DXMATRIXA16 worldTM;

	std::vector<CubeNode*> childs;

	SYNTHESIZE( D3DXMATRIXA16*, pParentWorldTM, ParentWorldTM )
	SYNTHESIZE( float, rotDeltaX, RotDeltaX )

};

