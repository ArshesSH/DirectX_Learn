#include "framework.h"
#include "TextureManager.h"

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}

LPDIRECT3DTEXTURE9 TextureManager::GetTexture( const char* szFullPath )
{
	if ( textureMap.find( szFullPath ) == textureMap.end() )
	{
		D3DXCreateTextureFromFileA( g_pD3DDevice, szFullPath, &textureMap[szFullPath] );
	}
	return textureMap[szFullPath];
}

LPDIRECT3DTEXTURE9 TextureManager::GetTexture( const std::string& szFullPath )
{
	return GetTexture( (char*)szFullPath.c_str() );
}

void TextureManager::Destroy()
{
	for ( auto t : textureMap )
	{
		SAFE_RELEASE( t.second );
	}
	textureMap.clear();
}
