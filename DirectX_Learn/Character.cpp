#include "framework.h"
#include "Character.h"

Character::Character()
	:
	position( 0, 0, 0 ),
	direction( 0, 0, 1 ),
	rotY( 0.0f )
{
	D3DXMatrixIdentity( &worldMat );
}

Character::~Character()
{
}

void Character::Setup()
{
}

void Character::Update()
{
	if ( GetAsyncKeyState( 'W' ) & 0x8000 )
	{
		position += (direction * 0.1f);
	}
	if ( GetAsyncKeyState( 'S' ) & 0x8000 )
	{
		position -= (direction * 0.1f);
	}
	if ( GetAsyncKeyState( 'A' ) & 0x8000 )
	{
		rotY -= 0.1f;
	}
	if ( GetAsyncKeyState( 'D' ) & 0x8000 )
	{
		rotY += 0.1f;
	}

	RECT rc;
	GetClientRect( g_hWnd, &rc );

	D3DXMATRIXA16 matR, matT;

	// Create Rotateion by Angle
	D3DXMatrixRotationY( &matR, rotY );
	direction = D3DXVECTOR3( 0, 0, 1 );
	D3DXVec3TransformNormal( &direction, &direction, &matR );

	D3DXMatrixTranslation( &matT, position.x, position.y, position.z );
	worldMat = matR * matT;
}

void Character::Draw()
{
}

D3DXVECTOR3& Character::GetPosition()
{
	return position;
}
