#pragma once
class Frustum
{
public:
	Frustum();
	~Frustum();
	void Setup();
	void Update();
	bool IsIn( const SPHERE* const pSphere ) const;

private:
	std::vector<D3DXVECTOR3> projVertices;
	std::vector<D3DXVECTOR3> worldVertices;
	std::vector<D3DXPLANE> planes;
};

