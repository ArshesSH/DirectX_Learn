#pragma once

#include <map>

class MtlTex;
class ObjGroup;

class ObjLoader
{
public:
	ObjLoader();
	~ObjLoader();

	void Load( OUT std::vector<ObjGroup*>& pGroups, IN char* szFolder, IN char* szFile );
	void LoadMtlLib( char* szFolder, char* szFile );
	void LoadSurface( OUT std::vector<D3DXVECTOR3>& surfaces, IN char* szFolder, IN char* szFile, IN D3DXMATRIXA16* pMat );

private:
	std::map<std::string, MtlTex*> mtlTexMap;
};

