#pragma once
#include "Character.h"

class CubeNode;

class CubeMan : public Character
{
public:
	CubeMan();
	virtual ~CubeMan();

	void Setup() override;
	void Update() override;
	void Draw() override;

protected:
	CubeNode* pRoot;

};

