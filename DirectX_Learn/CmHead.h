#pragma once
#include "CubeManbodyParts.h"
class CmHead : public CubeManBodyParts
{
public:
	CmHead() {}
	~CmHead() {}

	void Setup() override;

private:
	static constexpr float sizeX = 0.4f;
	static constexpr float sizeY = 0.4f;
	static constexpr float sizeZ = 0.4f;

	static constexpr float axisX = 0.0f;
	static constexpr float axisY = 0.0f;
	static constexpr float axisZ = 0.0f;

	static constexpr float localPosY = 0.5f;
};

