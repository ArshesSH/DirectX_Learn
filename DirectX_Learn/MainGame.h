#pragma once
class MainGame
{
public:
	MainGame();
	MainGame( D3DCOLOR screenDefaultColor );
	~MainGame();

	void Setup();
	void Update();
	void Render();
	
private:
	LPDIRECT3D9			pD3D;
	LPDIRECT3DDEVICE9	pD3DDevice;
	D3DCOLOR screenDefaultColor;
};

