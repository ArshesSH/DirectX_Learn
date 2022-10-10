#pragma once
#include "iMap.h"
class HeightMap : public iMap
{
public:
	HeightMap();
	virtual ~HeightMap();

	void Setup( const char* const szFolder, const char* const szRaw, const char* const szTex, DWORD dwBytePerPixel = 1 );
	virtual void Render() override;
	virtual bool GetHeight( IN float x, OUT float& y, IN float z )override;
	void Destroy();

private:
	LPD3DXMESH pMesh;
	LPDIRECT3DTEXTURE9 pTexture;
	std::vector<D3DXVECTOR3> vertices;
	D3DMATERIAL9 mtl;
	int nTile;
};

