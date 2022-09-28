#pragma once
#include "CubeManbodyParts.h"
class CmBody : public CubeManBodyParts
{
public:
	CmBody() {}
	~CmBody() {}
	
	void Setup() override;

private:
	static constexpr float sizeX = 0.4f;
	static constexpr float sizeY = 0.6f;
	static constexpr float sizeZ = 0.2f;

};

