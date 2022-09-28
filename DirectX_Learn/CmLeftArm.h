#pragma once
#include "CubeManbodyParts.h"
class CmLeftArm : public CubeManBodyParts
{
public:
	CmLeftArm() {}
	~CmLeftArm() {}

	void Setup() override;

private:
	static constexpr float sizeX = 0.2f;
	static constexpr float sizeY = 0.6f;
	static constexpr float sizeZ = 0.2f;

	static constexpr float axisX = -0.3f;
	static constexpr float axisY = -0.3f;
	static constexpr float axisZ = 0.0f;

	static constexpr float localPosY = 0.3f;
};

