#pragma once
#include "iMap.h"
class ObjMap : public iMap
{
public:
	ObjMap( IN char* szFolder, IN char* szFile, IN D3DXMATRIXA16* pMat = nullptr );
	~ObjMap(void);

	void Load( IN char* szFolder, IN char* szFile, IN D3DXMATRIXA16* pMat = nullptr );
	virtual bool GetHeight( IN float x, OUT float& y, IN float z );

private:
	std::vector<D3DXVECTOR3> surfaces;
};

