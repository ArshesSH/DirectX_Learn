#pragma once
class CubePNT
{
public:
	CubePNT();
	virtual ~CubePNT();

	virtual void Setup();
	virtual void Update();
	virtual void Render();

protected:
	std::vector<PNT_VERTEX> vertices;

};

