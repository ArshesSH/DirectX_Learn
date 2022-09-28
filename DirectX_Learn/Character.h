#pragma once
class Character
{
public:
	Character();
	virtual ~Character();

	virtual void Setup();
	virtual void Update();
	virtual void Draw();
	virtual D3DXVECTOR3& GetPosition();

protected:
	float rotY;
	D3DXVECTOR3 direction;
	D3DXVECTOR3 position;
	D3DXMATRIXA16 worldMat;
};

