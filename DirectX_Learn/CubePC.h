#pragma once
class CubePC
{
public:
	CubePC();

	void Setup();
	void Update();
	void Render();
	D3DXVECTOR3& GetPosition();

private:
	std::vector<PC_VERTEX> vertices;
	float fRotY;
	D3DXVECTOR3 vDirection;
	D3DXVECTOR3	vPosition;
	D3DXMATRIXA16 matWorld;
};

