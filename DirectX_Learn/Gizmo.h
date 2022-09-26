#pragma once
class Gizmo
{
public:
	Gizmo();

	void Setup(D3DCOLOR c, D3DXMATRIXA16& mat);
	void Draw();

private:
	std::vector<PC_VERTEX> vertices;
	D3DXMATRIXA16 matRot;
};