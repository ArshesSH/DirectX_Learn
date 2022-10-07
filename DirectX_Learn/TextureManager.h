#pragma once

#include <map>

#define g_pTextureManager TextureManager::GetInstance()

class TextureManager
{
public:
	LPDIRECT3DTEXTURE9 GetTexture( const char* szFullPath );
	LPDIRECT3DTEXTURE9 GetTexture( const std::string& szFullPath );
	void Destroy();

private:
	SINGLETON( TextureManager )
		
private:
	std::map < std::string, LPDIRECT3DTEXTURE9 > textureMap;
};

