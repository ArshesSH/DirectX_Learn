#pragma once
#include "CubeNode.h"
class CubeManBodyParts : public CubeNode
{
public:
	CubeManBodyParts()
	{}
	virtual ~CubeManBodyParts() {}

	virtual void Setup( D3DXVECTOR3 size, D3DXVECTOR3 axisPos, D3DXVECTOR3 relPos );

private:
	D3DXVECTOR3 size;
	D3DXVECTOR3 axisPos;
	D3DXVECTOR3 relPos;

};

