#pragma once
class Grid
{
public:
	Grid();

	void Setup( int tileNum = 15, float interval = 1.0f );
	void Draw();

private:
	std::vector<PC_VERTEX> vertices;
	std::vector<class Gizmo*> gizmoPtrs;
};

